from conan import ConanFile
from conan.tools.cmake import CMake, CMakeToolchain, cmake_layout
from conan.tools.files import collect_libs, copy, get, rmdir
import os

required_conan_version = ">=2.32.0"


class ConanRecipe(ConanFile):
    name = "c-ares"
    version = "1.34.8"
    homepage = "https://www.c-ares.org"
    description = "A C library for asynchronous DNS requests"
    license = "MIT"
    settings = "os", "arch", "compiler", "build_type"
    package_type = "shared-library"

    def configure(self):
        self.settings.rm_safe("compiler.cppstd")
        self.settings.rm_safe("compiler.libcxx")

    def layout(self):
        cmake_layout(self, src_folder="src")

    def source(self):
        get(
            self,
            sha256="c222b6d681096f9444d2c4863d2c1174019e27cacca0a4a5c114d36dd7d7bf78",
            url=f"https://github.com/c-ares/c-ares/releases/download/v{self.version}/c-ares-{self.version}.tar.gz",
            strip_root=True,
        )

    def generate(self):
        tc = CMakeToolchain(self)
        tc.variables["CMAKE_DEBUG_POSTFIX"] = "_d"
        tc.variables["CARES_STATIC"] = False
        tc.variables["CARES_SHARED"] = True
        tc.variables["CARES_BUILD_TESTS"] = False
        tc.variables["CARES_MSVC_STATIC_RUNTIME"] = False
        tc.variables["CARES_BUILD_TOOLS"] = True
        tc.variables["CARES_THREADS"] = True
        tc.generate()

    def build(self):
        cmake = CMake(self)
        cmake.configure()
        cmake.build()

    def package(self):
        copy(self, "LICENSE.md", src=self.source_folder, dst=os.path.join(self.package_folder, "licenses"))
        cmake = CMake(self)
        cmake.install()
        rmdir(self, os.path.join(self.package_folder, "lib", "cmake"))
        rmdir(self, os.path.join(self.package_folder, "lib", "pkgconfig"))
        rmdir(self, os.path.join(self.package_folder, "share"))

    def package_info(self):
        self.cpp_info.set_property("cpe", f"cpe:2.3:a:c-ares:c-ares:{self.version}:*:*:*:*:*:*:*")
        self.cpp_info.set_property("purl", f"pkg:github/c-ares/c-ares@v{self.version}")

        self.cpp_info.set_property("pkg_config_name", "libcares")
        self.cpp_info.set_property("cmake_file_name", "c-ares")
        self.cpp_info.set_property("cmake_target_name", "c-ares::cares")
        self.cpp_info.set_property("cmake_target_aliases", ["Cares::cares", "c-ares::c-ares", "cares::cares"])

        self.cpp_info.libs = collect_libs(self)
        if self.settings.os == "Linux":
            self.cpp_info.system_libs.append("rt")
            self.cpp_info.system_libs.append("pthread")
        elif self.settings.os == "Windows":
            self.cpp_info.system_libs.extend(["ws2_32", "advapi32"])
            self.cpp_info.system_libs.append("iphlpapi")
