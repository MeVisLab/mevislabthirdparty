import os
from conan import ConanFile
from conan.tools.files import copy, get
from conan.tools.layout import basic_layout

required_conan_version = ">=2.32.0"


class ConanRecipe(ConanFile):
    name = "jquery"
    version = "4.0.0"
    homepage = "https://jquery.com"
    description = "A fast, small, and feature-rich JavaScript library"
    package_type = "build-scripts"
    license = "MIT"
    settings = None

    mlab_hooks = {"folders.skip": True}

    def layout(self):
        basic_layout(self, src_folder="src")

    def source(self):
        get(
            self,
            sha256="b2ea145a784c910e541665909952a38fd452352c3956541a730228d595c634f0",
            url=f"https://github.com/jquery/jquery/archive/{self.version}.zip",
            strip_root=True,
        )

    def package(self):
        copy(
            self,
            "*",
            src=os.path.join(self.source_folder, "dist"),
            dst=os.path.join(self.package_folder, "web", self.name),
        )
        copy(self, "LICENSE.txt", src=self.source_folder, dst=os.path.join(self.package_folder, "licenses"))

    def package_info(self):
        self.cpp_info.set_property("cpe", f"cpe:2.3:a:jquery:jquery:{self.version}:*:*:*:*:*:*:*")
        self.cpp_info.set_property("purl", f"pkg:github/jquery/jquery@{self.version}")
        self.cpp_info.includedirs.clear()
        self.cpp_info.set_property("cmake_find_mode", "none")
