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
        yui2 = self.dependencies["yui2"]
        web_folder = os.path.join(yui2.package_folder, "web", "yui2")
        for relative_path in (
            os.path.join("yahoo", "yahoo-min.js"),
            os.path.join("yahoo-dom-event", "yahoo-dom-event.js"),
            os.path.join("yuiloader", "yuiloader-min.js"),
            os.path.join("reset-fonts-grids", "reset-fonts-grids.css"),
        ):
            path = os.path.join(web_folder, relative_path)
            if not os.path.isfile(path) or os.path.getsize(path) == 0:
                raise ConanException(f"missing or empty file: {path}")
        with open(os.path.join(web_folder, "yahoo", "yahoo-min.js"), encoding="utf-8") as script:
            header = script.read(200)
        if f"version: {yui2.ref.version}" not in header:
            raise ConanException(f"unexpected yahoo-min.js header: {header!r}")
