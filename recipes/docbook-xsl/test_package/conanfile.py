import os
import xml.etree.ElementTree as ElementTree

from conan import ConanFile
from conan.errors import ConanException
from conan.tools.layout import basic_layout


class TestPackage(ConanFile):
    test_type = "explicit"

    def layout(self):
        basic_layout(self)

    def requirements(self):
        self.requires(self.tested_reference_str)

    def test(self):
        dependency = self.dependencies["docbook-xsl"]
        stylesheets_folder = os.path.join(dependency.package_folder, "xsl", "docbook-xsl")
        for stylesheet in (
            "html/chunkfast.xsl",
            "html/onechunk.xsl",
            "htmlhelp/htmlhelp.xsl",
            "extensions/xalan27.jar",
        ):
            stylesheet_path = os.path.join(stylesheets_folder, stylesheet)
            if not os.path.isfile(stylesheet_path) or os.path.getsize(stylesheet_path) == 0:
                raise ConanException(f"missing or empty file: {stylesheet_path}")

        version_element = ElementTree.parse(os.path.join(stylesheets_folder, "VERSION")).find(
            ".//{http://freshmeat.net/projects/freshmeat-submit/}Version"
        )
        if version_element is None or version_element.text != str(dependency.ref.version):
            found_version = None if version_element is None else version_element.text
            raise ConanException(f"VERSION file reports {found_version}, expected {dependency.ref.version}")
