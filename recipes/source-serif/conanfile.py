import os
from conan import ConanFile
from conan.tools.files import copy, get

required_conan_version = ">=2.2.2"


class ConanRecipe(ConanFile):
    name = "source-serif"
    version = "4.005"
    homepage = "https://github.com/adobe-fonts/source-serif"
    description = "Serif font family for user interface environments"
    license = "OFL-1.1"
    package_type = "build-scripts"

    mlab_hooks = {"test_package.skip": True, "folders.exclude": ["fonts"]}

    def source(self):
        get(
            self,
            sha256="549fdb8f9a682bd06944298621404969f6de77c2e422ff3b8244a1dcd6a0c425",
            url=f"https://github.com/adobe-fonts/source-serif/releases/download/{self.version}R/source-serif-{self.version}_Desktop.zip",
            strip_root=False,
        )

    def package(self):
        source_folder = os.path.join(self.source_folder, f"source-serif-{self.version}_Desktop")
        copy(self, "LICENSE.md", src=source_folder, dst=os.path.join(self.package_folder, "licenses"))
        copy(
            self,
            "SourceSerif4-Regular.ttf",
            src=os.path.join(source_folder, "TTF"),
            dst=os.path.join(self.package_folder, "fonts", self.name),
        )

    def package_info(self):
        self.cpp_info.includedirs = []
