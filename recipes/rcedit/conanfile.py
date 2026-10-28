from conan import ConanFile
from conan.tools.cmake import CMake, CMakeToolchain, cmake_layout
from conan.errors import ConanInvalidConfiguration
from conan.tools.files import patch, copy, get
import os

required_conan_version = ">=2.32.0"


class ConanRecipe(ConanFile):
    name = "rcedit"
    version = "2.0.0"
    homepage = "https://github.com/electron/rcedit"
    description = "Command line tool to edit resources of exe"
    license = "MIT"
    settings = "os", "arch", "compiler", "build_type"
    exports_sources = "patches/*.patch"
    package_type = "application"

    def configure(self):
        if self.settings.os != "Windows":
            raise ConanInvalidConfiguration(f"{self.name} is only supported on Windows")

    def validate(self):
        if self.settings.os != "Windows":
            raise ConanInvalidConfiguration(f"{self.name} is only supported on Windows")

    def validate_build(self):
        if self.settings.build_type != "Release":
            raise ConanInvalidConfiguration(f"{self.name} is built in release mode only.")

    def layout(self):
        cmake_layout(self, src_folder="src")

    def source(self):
        get(
            self,
            sha256="2a55a176fc11cc563cd827ef3f55a7afe2aa0dca1ecc8d8d53b1b5afd5cffa20",
            url=f"https://github.com/electron/rcedit/archive/refs/tags/v{self.version}.tar.gz",
            strip_root=True,
        )
        patch(self, patch_file="patches/001-empty_values.patch")
        patch(self, patch_file="patches/002-return_value.patch")

    def generate(self):
        tc = CMakeToolchain(self)
        tc.preprocessor_definitions["_SILENCE_CXX17_CODECVT_HEADER_DEPRECATION_WARNING"] = 1
        tc.generate()

    def build(self):
        cmake = CMake(self)
        cmake.configure()
        cmake.build()

    def package(self):
        copy(self, "LICENSE", src=self.source_folder, dst=os.path.join(self.package_folder, "licenses"))
        copy(
            self,
            pattern="rcedit.exe",
            src=os.path.join(self.build_folder, "Release"),
            dst=os.path.join(self.package_folder, "bin"),
            keep_path=False,
        )

    def package_info(self):
        self.cpp_info.set_property("purl", f"pkg:github/electron/rcedit@v{self.version}")
        self.cpp_info.includedirs.clear()
        self.cpp_info.libdirs.clear()
