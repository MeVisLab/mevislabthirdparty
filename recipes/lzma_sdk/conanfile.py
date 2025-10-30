from conan import ConanFile
from conan.tools.cmake import CMake, CMakeToolchain, cmake_layout
from conan.tools.files import get, collect_libs, load, save
from conan.tools.scm import Version
from conan.errors import ConanException
import os

required_conan_version = ">=2.2.2"


class ConanRecipe(ConanFile):
    name = "lzma_sdk"
    version = "25.01"
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
            sha256="249d7847ee2932705c8e157552e481cf8b7cd16ec70243ce98184b5d48b7a998",
            url=f"https://github.com/sisong/lzma/archive/refs/tags/v{v.major}.{minor}.tar.gz",
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

        # extract license text:
        text = load(self, os.path.join(self.source_folder, "DOC", "lzma-sdk.txt"))
        license_pos = text.find("LICENSE")
        if license_pos == -1:
            raise ConanException("License text not found")
        license_end = text.find("\n\n\n", license_pos)  # two empty lines mark end of license
        if license_end == -1:
            # try Windows line end:
            license_end = text.find("\r\n\r\n\r\n", license_pos)
        if license_end == -1:
            raise ConanException("End of license text not found")
        save(self, os.path.join(self.package_folder, "licenses", "LICENSE"), text[license_pos : license_end + 2])

    def package_info(self):
        # self.cpp_info.set_property("cpe", "")  # No CPE (yet)?
        self.cpp_info.set_property(
            "purl", f"pkg:github/sisong/lzma@v{self.version}"
        )  # Official repository is at https://www.7-zip.org/sdk.html
        self.cpp_info.set_property("display_name", "LZMA SDK")
        self.cpp_info.libs = collect_libs(self)
        self.cpp_info.includedirs = ["include", "include/C"]
