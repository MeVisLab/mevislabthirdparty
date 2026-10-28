import os

from conan import ConanFile
from conan.tools.files import copy, get
from conan.tools.layout import basic_layout

required_conan_version = ">=2.32.0"


class ConanRecipe(ConanFile):
    name = "ms-gsl"
    version = "5.0.1"
    homepage = "https://github.com/microsoft/GSL"
    description = (
        "Guideline Support Library suggested for use by the C++ Core Guidelines and implementation by Microsoft"
    )
    license = "MIT"
    package_type = "static-library"
    settings = "os", "arch", "compiler", "build_type"

    def package_id(self):
        self.info.clear()

    def layout(self):
        basic_layout(self, src_folder="src")

    def source(self):
        get(
            self,
            sha256="733a87a7eea56db075ee060735ba7616a27c1c55955f264d5473bf9e83294ad0",
            url=f"https://github.com/microsoft/GSL/archive/v{self.version}.tar.gz",
            strip_root=True,
        )

    def package(self):
        copy(self, "LICENSE", src=self.source_folder, dst=os.path.join(self.package_folder, "licenses"))
        copy(
            self, "*", src=os.path.join(self.source_folder, "include"), dst=os.path.join(self.package_folder, "include")
        )

    def package_info(self):
        self.cpp_info.set_property("cmake_file_name", "Microsoft.GSL")
        self.cpp_info.set_property("cmake_target_name", "Microsoft.GSL::GSL")
        self.cpp_info.bindirs = []
        self.cpp_info.libdirs = []
