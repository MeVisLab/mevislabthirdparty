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
        package_folder = self.dependencies["source-serif"].package_folder
        font_path = os.path.join(package_folder, "fonts", "source-serif", "SourceSerif4-Regular.ttf")
        if not os.path.isfile(font_path) or os.path.getsize(font_path) == 0:
            raise ConanException(f"missing or empty file: {font_path}")
        with open(font_path, "rb") as font_file:
            magic = font_file.read(4)
        if magic not in (b"\x00\x01\x00\x00", b"true", b"OTTO"):
            raise ConanException(f"{font_path} is not a TrueType/OpenType font, magic bytes: {magic!r}")
