import os
import textwrap

from conan import ConanFile
from conan.tools.cmake import CMake, CMakeDeps, CMakeToolchain, cmake_layout
from conan.tools.files import collect_libs, replace_in_file, copy, get, rmdir, save
from conan.tools.scm import Version

required_conan_version = ">=2.32.0"


class ConanRecipe(ConanFile):
    name = "flatbuffers"
    version = "25.12.19"
    homepage = "https://flatbuffers.dev"
    description = "Memory efficient serialization library"
    license = "Apache-2.0"
    package_type = "static-library"
    settings = "os", "arch", "compiler", "build_type"

    def layout(self):
        cmake_layout(self, src_folder="src")

    def source(self):
        get(
            self,
            sha256="f81c3162b1046fe8b84b9a0dbdd383e24fdbcf88583b9cb6028f90d04d90696a",
            url=f"https://github.com/google/flatbuffers/archive/refs/tags/v{self.version}.tar.gz",
            strip_root=True,
        )
        # don't call git, inject version from the recipe
        replace_in_file(self, os.path.join(self.source_folder, "CMakeLists.txt"), "include(CMake/Version.cmake)", "")

        # Install dll to bin folder
        replace_in_file(
            self,
            os.path.join(self.source_folder, "CMakeLists.txt"),
            "RUNTIME DESTINATION ${CMAKE_INSTALL_LIBDIR}",
            "RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}",
        )

    def generate(self):
        cd = CMakeDeps(self)
        cd.generate()
        tc = CMakeToolchain(self)
        tc.variables["CMAKE_CXX_STANDARD"] = 20
        tc.variables["CMAKE_DEBUG_POSTFIX"] = "_d"
        tc.variables["BUILD_SHARED_LIBS"] = False
        tc.variables["CMAKE_POSITION_INDEPENDENT_CODE"] = True
        tc.variables["FLATBUFFERS_BUILD_TESTS"] = False
        tc.variables["FLATBUFFERS_INSTALL"] = True
        tc.variables["FLATBUFFERS_BUILD_FLATLIB"] = True
        tc.variables["FLATBUFFERS_BUILD_FLATC"] = True
        tc.variables["FLATBUFFERS_STATIC_FLATC"] = True
        tc.variables["FLATBUFFERS_BUILD_FLATHASH"] = False
        tc.variables["FLATBUFFERS_BUILD_SHAREDLIB"] = False
        tc.variables["FLATBUFFERS_LIBCXX_WITH_CLANG"] = False
        version = Version(self.version)
        tc.cache_variables["VERSION_MAJOR"] = str(version.major)
        tc.cache_variables["VERSION_MINOR"] = str(version.minor or "0")
        tc.cache_variables["VERSION_PATCH"] = str(version.patch or "0")
        tc.generate()

    def build(self):
        cmake = CMake(self)
        cmake.configure()
        cmake.build()

    def package(self):
        copy(self, "LICENSE*", src=self.source_folder, dst=os.path.join(self.package_folder, "licenses"))
        cmake = CMake(self)
        cmake.install()
        rmdir(self, os.path.join(self.package_folder, "lib", "cmake"))
        rmdir(self, os.path.join(self.package_folder, "lib", "pkgconfig"))
        copy(
            self,
            "BuildFlatBuffers.cmake",
            src=os.path.join(self.source_folder, "CMake"),
            dst=os.path.join(self.package_folder, "lib", "cmake"),
        )
        content = textwrap.dedent("""\
            if(NOT TARGET flatbuffers::flatc)
                find_program(FLATBUFFERS_FLATC_EXECUTABLE NAMES flatc HINTS ${flatbuffers_BIN_DIRS_RELEASE} ${flatbuffers_BIN_DIRS_DEBUG})
                if(FLATBUFFERS_FLATC_EXECUTABLE)
                    get_filename_component(FLATBUFFERS_FLATC_EXECUTABLE "${FLATBUFFERS_FLATC_EXECUTABLE}" ABSOLUTE)
                    add_executable(flatbuffers::flatc IMPORTED)
                    set_property(TARGET flatbuffers::flatc PROPERTY IMPORTED_LOCATION ${FLATBUFFERS_FLATC_EXECUTABLE})
                endif()
            endif()
        """)
        save(self, os.path.join(self.package_folder, "lib", "cmake", "FlatcTargets.cmake"), content)

    def package_info(self):
        self.cpp_info.set_property("cpe", f"cpe:2.3:a:google:flatbuffers:{self.version}:*:*:*:*:*:*:*")
        self.cpp_info.set_property("purl", f"pkg:github/google/flatbuffers@{self.version}")

        self.cpp_info.set_property("cmake_find_mode", "both")
        self.cpp_info.set_property("cmake_module_file_name", "flatbuffers")
        self.cpp_info.set_property("cmake_file_name", "flatbuffers")
        self.cpp_info.set_property("cmake_target_name", "flatbuffers::flatbuffers")
        self.cpp_info.set_property("pkg_config_name", "flatbuffers")
        self.cpp_info.components["libflatbuffers"].libs = collect_libs(self)
        if self.settings.os == "Linux":
            self.cpp_info.components["libflatbuffers"].system_libs.append("m")

        build_modules = [
            os.path.join(os.path.join("lib", "cmake"), "FlatcTargets.cmake"),
            os.path.join(os.path.join("lib", "cmake"), "BuildFlatBuffers.cmake"),
        ]
        self.cpp_info.set_property("cmake_build_modules", build_modules)

        self.buildenv_info.prepend_path("PATH", os.path.join(self.package_folder, "bin"))
        self.runenv_info.prepend_path("PATH", os.path.join(self.package_folder, "bin"))
