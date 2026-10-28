from conan import ConanFile
from conan.tools.cmake import CMake, CMakeToolchain, cmake_layout
from conan.tools.files import copy, get, collect_libs
import os

required_conan_version = ">=2.32.0"


class ConanRecipe(ConanFile):
    name = "7zip"
    version = "26.04"
    license = "LGPL-2.1-or-later AND BSD-3-Clause"
    homepage = "https://www.7-zip.org"
    description = "7-Zip file archiver and LZMA SDK"
    package_type = "static-library"
    settings = "os", "arch", "compiler", "build_type"
    exports_sources = "CMakeLists.txt"

    def configure(self):
        self.settings.rm_safe("compiler.libcxx")
        self.settings.rm_safe("compiler.cppstd")

    def layout(self):
        cmake_layout(self, src_folder="src")

    def source(self):
        get(
            self,
            sha256="48fdc6dfe879ee2db867bb07f19c4a9406bfea01d51f48785b6c7a137881e25c",
            url=f"https://github.com/ip7z/7zip/archive/refs/tags/{self.version}.tar.gz",
            strip_root=True,
        )

    def generate(self):
        tc = CMakeToolchain(self)
        tc.variables["CMAKE_DEBUG_POSTFIX"] = "_d"
        tc.variables["BUILD_SHARED_LIBS"] = False
        tc.variables["CMAKE_POSITION_INDEPENDENT_CODE"] = True
        tc.cache_variables["CONAN_LZMA_VERSION"] = f"{self.version}"
        tc.generate()

    def build(self):
        cmake = CMake(self)
        cmake.configure(build_script_folder=os.path.dirname(self.source_folder))
        cmake.build()

    def package(self):
        cmake = CMake(self)
        cmake.install()

        copy(
            self,
            "License.txt",
            dst=os.path.join(self.package_folder, "licenses"),
            src=os.path.join(self.source_folder, "DOC"),
        )
        copy(
            self,
            "unRarLicense.txt",
            dst=os.path.join(self.package_folder, "licenses"),
            src=os.path.join(self.source_folder, "DOC"),
        )

    def package_info(self):
        self.cpp_info.set_property("cpe", f"cpe:2.3:a:7-zip:7-zip:{self.version}:*:*:*:*:*:*:*")
        self.cpp_info.set_property("purl", f"pkg:github/ip7z/7zip@{self.version}")
        self.cpp_info.set_property("display_name", "7-Zip")
        self.cpp_info.set_property("cmake_file_name", "lzma_sdk")
        self.cpp_info.set_property("cmake_target_name", "lzma_sdk::lzma_sdk")
        self.cpp_info.libs = collect_libs(self)
        self.cpp_info.includedirs = ["include", "include/C"]
