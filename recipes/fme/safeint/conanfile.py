import os

from conan import ConanFile
from conan.tools.files import copy, get
from conan.tools.layout import basic_layout

required_conan_version = ">=2.32.0"


class ConanRecipe(ConanFile):
    name = "safeint"
    version = "3.0.28"
    homepage = "https://github.com/dcleblanc/SafeInt"
    description = "SafeInt is a class library for C++ that manages integer overflows."
    license = "MIT"
    package_type = "header-library"
    settings = "os", "arch", "compiler", "build_type"

    def package_id(self):
        self.info.clear()

    def layout(self):
        basic_layout(self, src_folder="src")

    def source(self):
        get(
            self,
            sha256="9e652d065a3cef80623287d5dc61edcf6a95ddab38a9dfeb34f155261fc9cef7",
            url=f"https://github.com/dcleblanc/SafeInt/archive/refs/tags/{self.version}a.tar.gz",
            strip_root=True,
        )

    def package(self):
        copy(self, "LICENSE", src=self.source_folder, dst=os.path.join(self.package_folder, "licenses"))
        copy(self, "SafeInt.hpp", src=self.source_folder, dst=os.path.join(self.package_folder, "include"))

    def package_info(self):
        self.cpp_info.bindirs = []
        self.cpp_info.libdirs = []
