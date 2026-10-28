import os

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
        jquery = self.dependencies["jquery"]
        web_folder = os.path.join(jquery.package_folder, "web", "jquery")
        for file_name in ("jquery.js", "jquery.min.js", "jquery.min.map", "jquery.slim.min.js"):
            path = os.path.join(web_folder, file_name)
            if not os.path.isfile(path) or os.path.getsize(path) == 0:
                raise ConanException(f"missing or empty file: {path}")
        with open(os.path.join(web_folder, "jquery.min.js"), encoding="utf-8") as script:
            header = script.read(100)
        if f"jQuery v{jquery.ref.version}" not in header:
            raise ConanException(f"unexpected jquery.min.js header: {header!r}")
