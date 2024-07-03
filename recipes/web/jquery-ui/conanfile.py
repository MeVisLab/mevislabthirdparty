from conan import ConanFile
from conan.tools.files import copy, get

required_conan_version = ">=2.2.2"


class ConanRecipe(ConanFile):
    name = "jquery-ui"
    version = "1.13.3"
    homepage = "https://jqueryui.com"
    description = "A curated set of user interface interactions, effects, widgets, and themes built on top of the jQuery JavaScript Library"
    package_type = "build-scripts"
    license = "MIT"
    settings = None

    mlab_hooks = {"test_package.skip": True, "folders.skip": True}

    def source(self):
        get(
            self,
            sha256="c0aca08c5dd54095d80869cf63f0178e7f1840910867634c66a6b237bb5ad2b7",
            url=f"https://jqueryui.com/resources/download/jquery-ui-{self.version}.zip",
            strip_root=True,
        )
        get(
            self,
            sha256="134653ced831789abe0d819376e87fea4028b0d1628f0dd040434a86a705e5b9",
            url=f"https://jqueryui.com/resources/download/jquery-ui-themes-{self.version}.zip",
            strip_root=True,
        )

    def package(self):
        copy(self, "*", src=self.source_path, dst=self.package_path / f"web/{self.name}", excludes=["*conan*"])
        copy(self, "LICENSE.txt", src=self.source_path, dst=self.package_path / "licenses")

    def package_info(self):
        self.cpp_info.includedirs.clear()
        self.cpp_info.set_property("cmake_find_mode", "none")
