import json
import re
from conan import ConanFile
from conan.tools.cmake import CMake, CMakeToolchain, cmake_layout
from conan.tools.files import copy, get, rmdir, load, save, collect_libs
import os

required_conan_version = ">=2.2.2"


class ConanRecipe(ConanFile):
    name = "abseil"
    version = "20250127.1"
    homepage = "https://abseil.io"
    description = "Collection of C++ libraries from Google"
    license = "Apache-2.0"
    settings = "os", "arch", "compiler", "build_type"
    exports_sources = "patches/*.patch"
    package_type = "static-library"

    mlab_hooks = {"cmake_files.exclude": ["lib/cmake/*.cmake"]}

    def layout(self):
        cmake_layout(self, src_folder="src")

    def source(self):
        get(
            self,
            sha256="b396401fd29e2e679cace77867481d388c807671dc2acc602a0259eeb79b7811",
            url=f"https://github.com/abseil/abseil-cpp/archive/refs/tags/{self.version}.tar.gz",
            strip_root=True,
        )

    def generate(self):
        tc = CMakeToolchain(self)
        tc.variables["CMAKE_DEBUG_POSTFIX"] = "_d"
        tc.variables["BUILD_SHARED_LIBS"] = False
        tc.variables["CMAKE_POSITION_INDEPENDENT_CODE"] = True
        tc.variables["ABSL_ENABLE_INSTALL"] = True
        tc.variables["ABSL_PROPAGATE_CXX_STD"] = True
        tc.variables["BUILD_TESTING"] = False
        tc.generate()

    def build(self):
        cmake = CMake(self)
        cmake.configure()
        cmake.build()

    def package(self):
        copy(self, pattern="LICENSE", src=self.source_folder, dst=os.path.join(self.package_folder, "licenses"))
        cmake = CMake(self)
        cmake.install()
        self._create_components_file()
        rmdir(self, os.path.join(self.package_folder, "lib", "pkgconfig"))
        rmdir(self, os.path.join(self.package_folder, "lib", "cmake"))

    def _create_components_file(self):
        components = {}
        dbg = "_d" if self.settings.build_type == "Debug" else ""
        targets_file = os.path.join(self.package_folder, "lib", "cmake", "absl", "abslTargets.cmake")
        abs_target_content = load(self, targets_file).replace("\r\n", "\n")

        cmake_functions = re.findall(r"(?P<func>add_library|set_target_properties)[\n|\s]*\([\n|\s]*(?P<args>[^)]*)\)", abs_target_content)
        for cmake_function_name, cmake_function_args in cmake_functions:
            cmake_function_args = re.split(r"[\s|\n]+", cmake_function_args, maxsplit=2)
            cmake_imported_target_name = cmake_function_args[0]
            cmake_target_nonamespace = cmake_imported_target_name.replace("absl::", "")
            potential_lib_name = "absl_" + cmake_target_nonamespace
            components.setdefault(potential_lib_name, {"cmake_target": cmake_target_nonamespace})

            if cmake_function_name == "add_library":
                cmake_imported_target_type = cmake_function_args[1]
                if cmake_imported_target_type in ["STATIC", "SHARED"]:
                    components[potential_lib_name]["libs"] = [
                        f"{potential_lib_name}{dbg}" if cmake_target_nonamespace != "abseil_dll" else f"abseil_dll{dbg}"
                    ]
            elif cmake_function_name == "set_target_properties":
                target_properties = re.findall(
                    r"(?P<property>INTERFACE_COMPILE_DEFINITIONS|INTERFACE_INCLUDE_DIRECTORIES|INTERFACE_LINK_LIBRARIES)[\n|\s]+(?P<values>.+)",
                    cmake_function_args[2],
                )
                for target_property in target_properties:
                    property_type = target_property[0]
                    if property_type == "INTERFACE_LINK_LIBRARIES":
                        values_list = target_property[1].replace('"', "").split(";")
                        for dependency in values_list:
                            if dependency.startswith("absl::"):  # abseil targets
                                components[potential_lib_name].setdefault("requires", []).append(dependency.replace("absl::", "absl_"))
                            else:
                                if self.settings.os == "Linux":
                                    if dependency == "Threads::Threads":
                                        components[potential_lib_name].setdefault("system_libs", []).append("pthread")
                                    elif "-lm" in dependency:
                                        components[potential_lib_name].setdefault("system_libs", []).append("m")
                                    elif "-lrt" in dependency:
                                        components[potential_lib_name].setdefault("system_libs", []).append("rt")
                                elif self.settings.os == "Windows":
                                    for system_lib in ["bcrypt", "advapi32", "dbghelp"]:
                                        if system_lib in dependency:
                                            components[potential_lib_name].setdefault("system_libs", []).append(system_lib)
                    elif property_type == "INTERFACE_COMPILE_DEFINITIONS":
                        values_list = target_property[1].replace('"', "").split(";")
                        for definition in values_list:
                            if definition == r"\$<\$<PLATFORM_ID:AIX>:_LINUX_SOURCE_COMPAT>":
                                continue
                            components[potential_lib_name].setdefault("defines", []).append(definition)
        content = json.dumps(components, indent=4)
        save(self, os.path.join(self.package_folder, "lib", "abseil_components.json"), content)

    def package_info(self):
        # self.cpp_info.set_property("cpe", "")  # No CPE yet?
        self.cpp_info.set_property("purl", f"pkg:github/abseil/abseil-cpp@{self.version}")
        self.cpp_info.set_property("cmake_file_name", "absl")

        collect_libs(self)
        abseil_components = json.loads(load(self, os.path.join(self.package_folder, "lib", "abseil_components.json")))
        for pkgconfig_name, values in abseil_components.items():
            cmake_target = values["cmake_target"]
            self.cpp_info.components[pkgconfig_name].set_property("cmake_target_name", f"absl::{cmake_target}")
            self.cpp_info.components[pkgconfig_name].set_property("pkg_config_name", pkgconfig_name)
            self.cpp_info.components[pkgconfig_name].defines = values.get("defines", [])
            self.cpp_info.components[pkgconfig_name].system_libs = values.get("system_libs", [])
            self.cpp_info.components[pkgconfig_name].requires = values.get("requires", [])
            self.cpp_info.components[pkgconfig_name].libs = values.get("libs", [])
