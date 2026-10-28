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
        bootstrap = self.dependencies["bootstrap"]
        web_folder = os.path.join(bootstrap.package_folder, "web", "bootstrap")
        for relative_path in (
            os.path.join("css", "bootstrap.min.css"),
            os.path.join("css", "bootstrap-theme.min.css"),
            os.path.join("js", "bootstrap.min.js"),
            os.path.join("fonts", "glyphicons-halflings-regular.woff"),
        ):
            path = os.path.join(web_folder, relative_path)
            if not os.path.isfile(path) or os.path.getsize(path) == 0:
                raise ConanException(f"missing or empty file: {path}")
        with open(os.path.join(web_folder, "js", "bootstrap.min.js"), encoding="utf-8") as script:
            header = script.read(200)
        if f"Bootstrap v{bootstrap.ref.version}" not in header:
            raise ConanException(f"unexpected bootstrap.min.js header: {header!r}")
