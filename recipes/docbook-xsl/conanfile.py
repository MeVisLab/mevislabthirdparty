import os
from conan import ConanFile
from conan.tools.files import copy, get
from conan.tools.layout import basic_layout

required_conan_version = ">=2.32.0"


class ConanRecipe(ConanFile):
    name = "docbook-xsl"
    version = "1.73.2"
    homepage = "https://docbook.org"
    description = "XSL stylesheets to transform DocBook documents into HTML and other formats"
    package_type = "build-scripts"
    license = "DocBook-XML"
    settings = None

    mlab_hooks = {"folders.exclude": ["xsl"]}

    def layout(self):
        basic_layout(self, src_folder="src")

    def source(self):
        get(
            self,
            sha256="d678d9c97b95cc5adf1dba13b12caf23c71225de284c6578fdc00a0f36b26f99",
            url=f"https://sourceforge.net/projects/docbook/files/docbook-xsl/{self.version}/docbook-xsl-{self.version}.tar.bz2",
            strip_root=True,
        )

    def package(self):
        copy(
            self,
            "*",
            src=self.source_folder,
            dst=os.path.join(self.package_folder, "xsl", self.name),
            excludes=["doc/*"],
        )
        copy(self, "COPYING", src=self.source_folder, dst=os.path.join(self.package_folder, "licenses"))

    def package_info(self):
        self.cpp_info.includedirs.clear()
        self.cpp_info.set_property("cmake_find_mode", "none")
