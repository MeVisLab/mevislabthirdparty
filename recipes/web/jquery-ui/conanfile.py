from conan import ConanFile
from conan.tools.files import copy, get

required_conan_version = ">=2.2.2"


class ConanRecipe(ConanFile):
    name = "jquery-ui"
    version = "1.13.2"
    homepage = "https://jqueryui.com"
    description = "A curated set of user interface interactions, effects, widgets, and themes built on top of the jQuery JavaScript Library"
    package_type = "build-scripts"
    license = "MIT"
    settings = None

    mlab_hooks = {
        'test_package.skip': True,
        'folders.skip': True
    }

    def source(self):
        get(self,
            sha256="f73762976d178159a1592a643f297609f2cf4a2af2d2d90068086f2cbdbe5777",
            url=f"https://jqueryui.com/resources/download/jquery-ui-{self.version}.zip",
            strip_root=True
        )
        get(self,
            sha256="60a08a7f7d71db54796e82ed4cfafbbaa96ca8635fe3da331867d1061ae2e1f2",
            url=f"https://jqueryui.com/resources/download/jquery-ui-themes-{self.version}.zip",
            strip_root=True
        )

    def package(self):
        copy(self, "*", src=self.source_path, dst=self.package_path / f"web/{self.name}", excludes=["*conan*"])
        copy(self, "LICENSE.txt", src=self.source_path, dst=self.package_path / "licenses")

    def package_info(self):
        self.cpp_info.includedirs.clear()
        self.cpp_info.set_property("cmake_find_mode", "none")
