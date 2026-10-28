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
        requirejs = self.dependencies["requirejs"]
        web_folder = os.path.join(requirejs.package_folder, "web", "requirejs")
        for file_name in ("require.js", "r.js"):
            path = os.path.join(web_folder, file_name)
            if not os.path.isfile(path) or os.path.getsize(path) == 0:
                raise ConanException(f"missing or empty file: {path}")
            with open(path, encoding="utf-8") as script:
                header = script.read(200)
            if f"@license {'RequireJS' if file_name == 'require.js' else 'r.js'} {requirejs.ref.version}" not in header:
                raise ConanException(f"unexpected {file_name} header: {header!r}")
