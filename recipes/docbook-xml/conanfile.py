import os
import re
from conan import ConanFile
from conan.errors import ConanException
from conan.tools.files import copy, get, load, save
from conan.tools.layout import basic_layout

required_conan_version = ">=2.32.0"


class ConanRecipe(ConanFile):
    name = "docbook-xml"
    version = "4.5"
    homepage = "https://docbook.org"
    description = "DocBook XML DTD and the XML catalog that maps its public and system identifiers"
    package_type = "build-scripts"
    license = "DocBook-DTD"
    settings = None

    mlab_hooks = {"folders.exclude": ["dtd"]}

    def layout(self):
        basic_layout(self, src_folder="src")

    def source(self):
        get(
            self,
            sha256="4e4e037a2b83c98c6c94818390d4bdd3f6e10f6ec62dd79188594e26190dc7b4",
            url=f"https://docs.oasis-open.org/docbook/xml/{self.version}/docbook-xml-{self.version}.zip",
            strip_root=False,
        )

    def package(self):
        copy(self, "*", src=self.source_folder, dst=os.path.join(self.package_folder, "dtd", self.name))
        dtd_content = load(self, os.path.join(self.source_folder, "docbookx.dtd"))
        license_match = re.search(r"<!-- (Copyright .*?)-->", dtd_content, re.DOTALL)
        if not license_match:
            raise ConanException("failed to find the license text in docbookx.dtd")
        save(self, os.path.join(self.package_folder, "licenses", "LICENSE"), license_match.group(1))

    def package_info(self):
        self.cpp_info.includedirs.clear()
        self.cpp_info.set_property("cmake_find_mode", "none")
