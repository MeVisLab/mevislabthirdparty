import os

from conan import ConanFile
from conan.tools.cmake import CMake, CMakeToolchain, cmake_layout
from conan.tools.files import replace_in_file, copy, get, rmdir, patch

required_conan_version = ">=2.32.0"


class ConanRecipe(ConanFile):
    name = "nsync"
    version = "1.30.0"
    homepage = "https://github.com/google/nsync"
    description = "nsync is a C library that exports various synchronization primitives, such as mutexes"
    license = "Apache-2.0"
    package_type = "shared-library"
    settings = "os", "arch", "compiler", "build_type"
    exports_sources = "patches/*"

    def layout(self):
        cmake_layout(self, src_folder="src")

    def source(self):
        get(
            self,
            sha256="883a0b3f8ffc1950670425df3453c127c1a3f6ed997719ca1bbe7f474235b6cc",
            url=f"https://github.com/google/nsync/archive/{self.version}.tar.gz",
            strip_root=True,
        )
        patch(
            self,
            patch_file="patches/001-include_chrono.patch",
            patch_description="https://github.com/google/nsync/commit/f36c1e158477afc4877b8e348a1fd6a93f919a37",
        )
        replace_in_file(
            self, os.path.join(self.source_folder, "CMakeLists.txt"), "set (CMAKE_POSITION_INDEPENDENT_CODE ON)", ""
        )
        replace_in_file(
            self,
            os.path.join(self.source_folder, "CMakeLists.txt"),
            "ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR} COMPONENT Development",
            'ARCHIVE DESTINATION "${CMAKE_INSTALL_LIBDIR}"\nRUNTIME DESTINATION "${CMAKE_INSTALL_BINDIR}"',
        )

    def generate(self):
        tc = CMakeToolchain(self)
        tc.variables["CMAKE_CXX_STANDARD"] = 20
        tc.variables["CMAKE_DEBUG_POSTFIX"] = "_d"
        tc.variables["BUILD_SHARED_LIBS"] = True
        tc.variables["CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS"] = True
        tc.variables["NSYNC_ENABLE_TESTS"] = False
        tc.generate()

    def build(self):
        cmake = CMake(self)
        cmake4_compat = {"CMAKE_POLICY_VERSION_MINIMUM": "3.5"}  # FIXME required for compatibility with CMake 4.0+
        cmake.configure(variables=cmake4_compat)
        cmake.build()

    def package(self):
        copy(self, "LICENSE", src=self.source_folder, dst=os.path.join(self.package_folder, "licenses"))
        cmake = CMake(self)
        cmake.install()
        rmdir(self, os.path.join(self.package_folder, "lib", "cmake"))

    def package_info(self):
        d = "_d" if self.settings.build_type == "Debug" else ""
        self.cpp_info.components["nsync_c"].libs = [f"nsync{d}"]
        self.cpp_info.components["nsync_cpp"].libs = [f"nsync_cpp{d}"]
        if self.settings.os == "Linux":
            self.cpp_info.components["nsync_c"].system_libs.append("pthread")
            self.cpp_info.components["nsync_cpp"].system_libs.extend(["m", "pthread"])
