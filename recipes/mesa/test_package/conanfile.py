import ctypes
import os

from conan import ConanFile
from conan.errors import ConanException
from conan.tools.build import can_run
from conan.tools.layout import basic_layout


class TestPackage(ConanFile):
    settings = "os", "arch", "compiler", "build_type"
    test_type = "explicit"

    def layout(self):
        basic_layout(self)

    def requirements(self):
        self.requires(self.tested_reference_str)

    def test(self):
        if self.settings.os != "Windows" or not can_run(self):
            return
        opengl32 = os.path.join(self.dependencies["mesa"].package_folder, "bin", "opengl32.dll")
        if not os.path.isfile(opengl32) or os.path.getsize(opengl32) == 0:
            raise ConanException(f"missing or empty file: {opengl32}")
        library = ctypes.WinDLL(opengl32)
        for symbol in ("wglGetProcAddress", "glGetString"):
            if not hasattr(library, symbol):
                raise ConanException(f"{opengl32} does not export {symbol}")
