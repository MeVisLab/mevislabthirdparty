from conan import ConanFile
from conan.tools.cmake import CMake, CMakeToolchain, cmake_layout
from conan.tools.files import get, collect_libs, copy
from conan.tools.scm import Version
import os

required_conan_version = ">=2.2.2"


class ConanRecipe(ConanFile):
    name = "lzma_sdk"
    version = "26.02"
    description = "LZMA SDK"
    homepage = "https://7-zip.de/sdk.html"
    license = "LZMA-SDK-9.22"
    package_type = "static-library"
    settings = "os", "arch", "compiler", "build_type"
    exports_sources = "CMakeLists.txt"

    def configure(self):
        self.settings.rm_safe("compiler.libcxx")
        self.settings.rm_safe("compiler.cppstd")

    def layout(self):
        cmake_layout(self, src_folder="src")

    def source(self):
        v = Version(self.version)
        minor = f"{v.minor}".zfill(2)
        get(
            self,
            sha256="7e5600ad0b21918bc41803bd84d0c2967e097fb7fbaa2e7aeb90beeb1121e54b",
            url=f"https://github.com/ip7z/7zip/archive/refs/tags/{v.major}.{minor}.tar.gz",
            strip_root=True,
        )

    def generate(self):
        tc = CMakeToolchain(self)
        tc.variables["CMAKE_DEBUG_POSTFIX"] = "_d"
        tc.variables["BUILD_SHARED_LIBS"] = False
        tc.variables["CMAKE_POSITION_INDEPENDENT_CODE"] = True
        tc.cache_variables["CONAN_LZMA_VERISON"] = f"{self.version}"
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
            src=os.path.join(self.source_folder, "DOC"),
            dst=os.path.join(self.package_folder, "licenses"),
        )

    def package_info(self):
        self.cpp_info.set_property("cpe", f"cpe:2.3:a:7-zip:7-zip:{self.version}:*:*:*:*:*:*:*")
        self.cpp_info.set_property("purl", f"pkg:github/ip7z/7zip@v{self.version}")
        self.cpp_info.set_property("display_name", "LZMA SDK")
        self.cpp_info.libs = collect_libs(self)
        self.cpp_info.includedirs = ["include", "include/C"]
