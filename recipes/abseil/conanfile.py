import json
import re
from conan import ConanFile
from conan.errors import ConanInvalidConfiguration
from conan.tools.cmake import CMake, CMakeToolchain, cmake_layout
from conan.tools.files import copy, get, rmdir, load, save
import os

required_conan_version = ">=2.32.0"


class ConanRecipe(ConanFile):
    name = "abseil"
    version = "20260817.0"
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
            sha256="f7e05179df39c45434cad433f5783840bb3788ef322976f9138bc6b72b3a107d",
            url=f"https://github.com/abseil/abseil-cpp/archive/refs/tags/{self.version}.tar.gz",
            strip_root=True,
        )

    def generate(self):
        tc = CMakeToolchain(self)
        tc.variables["CMAKE_DEBUG_POSTFIX"] = "_d"
        tc.variables["BUILD_SHARED_LIBS"] = False
        tc.variables["CMAKE_POSITION_INDEPENDENT_CODE"] = True
        tc.variables["ABSL_MSVC_STATIC_RUNTIME"] = False
        tc.variables["ABSL_ENABLE_INSTALL"] = True
        tc.variables["ABSL_PROPAGATE_CXX_STD"] = True
        tc.variables["ABSL_USE_SYSTEM_INCLUDES"] = True
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

    @staticmethod
    def _extract_absl_targets(value):
        """
        extract Abseil CMake targets from plain link dependencies and from CMake generator expressions.
        E.g:
            absl::strings
            $<LINK_ONLY:absl::throw_delegate>
            $<$<BOOL:...>:absl::base>
        """
        return list(dict.fromkeys(re.findall(r"absl::[A-Za-z0-9_]+", value)))

    @staticmethod
    def _append_unique(container, key, value):
        values = container.setdefault(key, [])
        if value not in values:
            values.append(value)

    def _create_components_file(self):
        components = {}
        dbg = "_d" if self.settings.build_type == "Debug" else ""

        targets_file = os.path.join(self.package_folder, "lib", "cmake", "absl", "abslTargets.cmake")
        absl_targets_content = load(self, targets_file).replace("\r\n", "\n")

        cmake_functions = re.findall(
            r"(?P<func>add_library|set_target_properties)" r"[\n\s]*" r"\(" r"[\n\s]*" r"(?P<args>[^)]*)" r"\)",
            absl_targets_content,
        )

        for cmake_function_name, cmake_function_args in cmake_functions:
            function_args = re.split(r"[\s\n]+", cmake_function_args.strip(), maxsplit=2)
            if len(function_args) < 2:
                continue

            cmake_imported_target_name = function_args[0]
            if not cmake_imported_target_name.startswith("absl::"):
                continue

            cmake_target_nonamespace = cmake_imported_target_name.replace("absl::", "", 1)
            component_name = f"absl_{cmake_target_nonamespace}"
            component = components.setdefault(component_name, {"cmake_target": cmake_target_nonamespace})

            if cmake_function_name == "add_library":
                cmake_imported_target_type = function_args[1]
                if cmake_imported_target_type in ("STATIC", "SHARED"):
                    if cmake_target_nonamespace == "abseil_dll":
                        library_name = f"abseil_dll{dbg}"
                    else:
                        library_name = f"{component_name}{dbg}"
                    component["libs"] = [library_name]
                continue

            if cmake_function_name != "set_target_properties":
                continue

            if len(function_args) < 3:
                continue

            properties_content = function_args[2]

            target_properties = re.findall(
                r"(?P<property>"
                r"INTERFACE_COMPILE_DEFINITIONS|"
                r"INTERFACE_INCLUDE_DIRECTORIES|"
                r"INTERFACE_LINK_LIBRARIES"
                r")"
                r"[\n\s]+"
                r"(?P<values>.+)",
                properties_content,
            )

            for property_type, property_values in target_properties:
                if property_type == "INTERFACE_LINK_LIBRARIES":
                    values_list = property_values.replace('"', "").split(";")
                    for dependency in values_list:
                        dependency = dependency.strip()
                        if not dependency:
                            continue

                        absl_targets = self._extract_absl_targets(dependency)
                        for absl_target in absl_targets:
                            if absl_target == "absl::test_instance_tracker":
                                continue

                            dependency_component = absl_target.replace("absl::", "absl_", 1)

                            # components must not depend on themselves
                            if dependency_component == component_name:
                                continue

                            self._append_unique(component, "requires", dependency_component)

                        # If the expression contains Abseil targets, the dependency has already been processed.
                        if absl_targets:
                            continue

                        if self.settings.os == "Linux":
                            if "Threads::Threads" in dependency:
                                self._append_unique(component, "system_libs", "pthread")

                            if re.search(r"(^|[\s:>,])-lm($|[\s>,])", dependency):
                                self._append_unique(component, "system_libs", "m")

                            if re.search(r"(^|[\s:>,])-lrt($|[\s>,])", dependency):
                                self._append_unique(component, "system_libs", "rt")

                        elif self.settings.os == "Windows":
                            for system_lib in ("bcrypt", "advapi32", "dbghelp"):
                                if system_lib in dependency:
                                    self._append_unique(component, "system_libs", system_lib)

                elif property_type == "INTERFACE_COMPILE_DEFINITIONS":
                    values_list = property_values.replace('"', "").split(";")

                    for definition in values_list:
                        definition = definition.strip()
                        if not definition:
                            continue

                        if definition == (r"\$<\$<PLATFORM_ID:AIX>:" r"_LINUX_SOURCE_COMPAT>"):
                            continue

                        self._append_unique(component, "defines", definition)

        # Perform a final defensive cleanup before writing the JSON file.
        for component_name, component in components.items():
            requires = component.get("requires", [])
            cleaned_requires = [requirement for requirement in dict.fromkeys(requires) if requirement != component_name]

            if cleaned_requires:
                component["requires"] = cleaned_requires
            else:
                component.pop("requires", None)

            for list_property in ("libs", "system_libs", "defines"):
                values = component.get(list_property)

                if values:
                    component[list_property] = list(dict.fromkeys(values))
                else:
                    component.pop(list_property, None)

        content = json.dumps(components, indent=4, sort_keys=True)
        components_file = os.path.join(self.package_folder, "lib", "abseil_components.json")
        save(self, components_file, content)

    def package_info(self):
        # self.cpp_info.set_property("cpe", "")  # No CPE yet?
        self.cpp_info.set_property("purl", f"pkg:github/abseil/abseil-cpp@{self.version}")
        self.cpp_info.set_property("cmake_file_name", "absl")

        components_file = os.path.join(self.package_folder, "lib", "abseil_components.json")
        abseil_components = json.loads(load(self, components_file))
        component_names = set(abseil_components)
        for component_name, values in abseil_components.items():
            cmake_target = values["cmake_target"]
            requires = values.get("requires", [])
            missing_components = [requirement for requirement in requires if requirement not in component_names]
            if missing_components:
                raise ConanInvalidConfiguration(
                    f"Component '{component_name}' references missing components: {', '.join(missing_components)}"
                )

            component = self.cpp_info.components[component_name]
            component.set_property("cmake_target_name", f"absl::{cmake_target}")
            component.set_property("pkg_config_name", component_name)
            component.libs = values.get("libs", [])
            component.requires = requires
            component.defines = values.get("defines", [])
            component.system_libs = values.get("system_libs", [])
