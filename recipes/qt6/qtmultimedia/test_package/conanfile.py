from conan import ConanFile


class TestPackage(ConanFile):
    python_requires = "qt_package/1.0.0"
    python_requires_extend = "qt_package.QtTestPackage"

    def test(self):
        if self.settings.os != "Windows":
            super().test()
