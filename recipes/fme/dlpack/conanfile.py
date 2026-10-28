import os

from conan import ConanFile
from conan.tools.files import copy, get
from conan.tools.layout import basic_layout

required_conan_version = ">=2.32.0"


class ConanRecipe(ConanFile):
    name = "dlpack"
    version = "1.3"
    homepage = "https://github.com/dmlc/dlpack"
    description = "common in-memory tensor structure"
    license = "Apache-2.0"
    package_type = "header-library"
    settings = "os", "arch", "compiler", "build_type"

    def package_id(self):
        self.info.clear()

    def layout(self):
        basic_layout(self, src_folder="src")

    def source(self):
        get(
            self,
            sha256="f3d567f885f6c142183afc91a58873b31d0e0b36faa2e45c232b98c74596404f",
            url=f"https://github.com/dmlc/dlpack/archive/refs/tags/v{self.version}.tar.gz",
            strip_root=True,
        )

    def package(self):
        copy(self, "LICENSE", src=self.source_folder, dst=os.path.join(self.package_folder, "licenses"))
        copy(
            self,
            "*.h",
            src=os.path.join(self.source_folder, "include"),
            dst=os.path.join(self.package_folder, "include"),
        )

    def package_info(self):
        self.cpp_info.set_property("cmake_file_name", "dlpack")
        self.cpp_info.set_property("cmake_target_name", "dlpack::dlpack")
        self.cpp_info.set_property("purl", f"pkg:github/dmlc/dlpack@v{self.version}")
        self.cpp_info.bindirs = []
        self.cpp_info.libdirs = []
