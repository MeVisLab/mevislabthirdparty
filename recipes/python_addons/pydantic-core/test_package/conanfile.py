from conan import ConanFile


class TestPackage(ConanFile):
    python_requires = "python_package/[>=1.0.0]"
    python_requires_extend = "python_package.PythonPackageTest"

    @property
    def has_requirements_txt(self):
        return True
