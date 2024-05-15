from conan import ConanFile

class TestPackage(ConanFile):
    python_requires = "qt_package/1.0.0"
    python_requires_extend = "qt_package.QtTestPackage"
