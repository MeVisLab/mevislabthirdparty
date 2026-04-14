from conan import ConanFile
from conan.tools.files import copy, get
from conan.tools.layout import basic_layout
import os

required_conan_version = ">=2.2.2"


class ConanRecipe(ConanFile):
    name = "jquery-ui"
    version = "1.14.2"
    homepage = "https://jqueryui.com"
    description = "A curated set of user interface interactions, effects, widgets, and themes built on top of the jQuery JavaScript Library"
    package_type = "build-scripts"
    license = "MIT"
    settings = None

    mlab_hooks = {"test_package.skip": True, "folders.skip": True}

    def layout(self):
        basic_layout(self, src_folder="src")

    def source(self):
        get(
            self,
            sha256="c60c08b6fa9d38ae51f142c12872808c28cd2af22353a22b9e8e2a7e678ceef4",
            url=f"https://jqueryui.com/resources/download/jquery-ui-{self.version}.zip",
            strip_root=True,
        )
        get(
            self,
            sha256="6bce2c336dde5c170855e7c6be7f9335d37a0e39555bdb52d21171297f5b7878",
            url=f"https://jqueryui.com/resources/download/jquery-ui-themes-{self.version}.zip",
            strip_root=True,
        )

    def package(self):
        copy(self, "*", src=self.source_folder, dst=os.path.join(self.package_folder, "web", self.name))
        copy(self, "LICENSE.txt", src=self.source_folder, dst=os.path.join(self.package_folder, "licenses"))

    def package_info(self):
        self.cpp_info.set_property("cpe", f"cpe:2.3:a:jqueryui:jquery_ui:{self.version}:*:*:*:*:jquery:*:*")
        self.cpp_info.set_property("purl", f"pkg:github/jquery/jquery-ui@{self.version}")
        self.cpp_info.includedirs.clear()
        self.cpp_info.set_property("cmake_find_mode", "none")
