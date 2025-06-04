from conan import ConanFile
from conan.tools.files import copy, get
import os

required_conan_version = ">=2.2.2"


class ConanRecipe(ConanFile):
    name = "jquery-ui"
    version = "1.14.1"
    homepage = "https://jqueryui.com"
    description = "A curated set of user interface interactions, effects, widgets, and themes built on top of the jQuery JavaScript Library"
    package_type = "build-scripts"
    license = "MIT"
    settings = None

    mlab_hooks = {"test_package.skip": True, "folders.skip": True}

    def source(self):
        get(
            self,
            sha256="e1d2031e6b33dcdc6b09e3cf1b838d9e0dfba20862e4cb248afb614dd4f04986",
            url=f"https://jqueryui.com/resources/download/jquery-ui-{self.version}.zip",
            strip_root=True,
        )
        get(
            self,
            sha256="3ab9779ecfe869ffb7172f8813a2c935184fa9f18c49363e1fbce6a6b935b4a3",
            url=f"https://jqueryui.com/resources/download/jquery-ui-themes-{self.version}.zip",
            strip_root=True,
        )

    def package(self):
        copy(self, "*", src=self.source_folder, dst=os.path.join(self.package_folder, "web", self.name), excludes=["*conan*"])
        copy(self, "LICENSE.txt", src=self.source_folder, dst=os.path.join(self.package_folder, "licenses"))

    def package_info(self):
        self.cpp_info.set_property("cpe", "cpe:2.3:a:jqueryui:jquery_ui:*:*:*:*:*:jquery:*:*")
        self.cpp_info.set_property("purl", f"pkg:github/jquery/jquery-ui@{self.version}")
        self.cpp_info.includedirs.clear()
        self.cpp_info.set_property("cmake_find_mode", "none")
