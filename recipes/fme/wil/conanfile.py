import os

from conan import ConanFile
from conan.tools.files import copy, get
from conan.tools.layout import basic_layout
from conan.errors import ConanInvalidConfiguration

required_conan_version = ">=2.32.0"


class ConanRecipe(ConanFile):
    name = "wil"
    version = "1.0.260126.7"
    homepage = "https://github.com/microsoft/wil"
    description = "Windows Implementation Libraries (WIL) is a header-only C++ library created to make life easier for developers on Windows through readable type-safe C++ interfaces for common Windows coding patterns"
    license = "MIT"
    package_type = "header-library"
    settings = "os", "arch", "compiler", "build_type"

    def validate(self):
        if self.settings.os != "Windows":
            raise ConanInvalidConfiguration(f"{self.name} is only supported on Windows")

    def package_id(self):
        self.info.clear()

    def layout(self):
        basic_layout(self, src_folder="src")

    def source(self):
        get(
            self,
            sha256="de9e03b38ff0ff8d22048f00b111cb631d21c550328f12530ccba71c05c9e361",
            url=f"https://github.com/microsoft/wil/archive/refs/tags/v{self.version}.tar.gz",
            strip_root=True,
        )

    def package(self):
        copy(self, "LICENSE", src=self.source_folder, dst=os.path.join(self.package_folder, "licenses"))
        copy(
            self,
            pattern="*.h",
            dst=os.path.join(self.package_folder, "include"),
            src=os.path.join(self.source_folder, "include"),
        )

    def package_info(self):
        self.cpp_info.set_property("cmake_file_name", "wil")
        self.cpp_info.set_property("cmake_target_name", "WIL::WIL")
        self.cpp_info.bindirs = []
        self.cpp_info.libdirs = []
