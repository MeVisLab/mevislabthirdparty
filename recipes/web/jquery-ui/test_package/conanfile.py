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
        jquery_ui = self.dependencies["jquery-ui"]
        web_folder = os.path.join(jquery_ui.package_folder, "web", "jquery-ui")
        for relative_path in (
            "jquery-ui.js",
            "jquery-ui.min.js",
            "jquery-ui.min.css",
            "jquery-ui.structure.min.css",
            "jquery-ui.theme.min.css",
            os.path.join("images", "ui-icons_444444_256x240.png"),
            os.path.join("themes", "smoothness", "jquery-ui.min.css"),
        ):
            path = os.path.join(web_folder, relative_path)
            if not os.path.isfile(path) or os.path.getsize(path) == 0:
                raise ConanException(f"missing or empty file: {path}")
        with open(os.path.join(web_folder, "jquery-ui.min.js"), encoding="utf-8") as script:
            header = script.read(100)
        if f"jQuery UI - v{jquery_ui.ref.version}" not in header:
            raise ConanException(f"unexpected jquery-ui.min.js header: {header!r}")
