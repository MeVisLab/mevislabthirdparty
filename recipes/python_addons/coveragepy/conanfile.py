from conan import ConanFile
from conan.tools.files import get

required_conan_version = ">=2.2.2"


class ConanRecipe(ConanFile):
    name = "coveragepy"
    version = "7.6.1"
    homepage = "https://coverage.readthedocs.io/"
    description = "Coverage.py is a tool for measuring code coverage of Python programs"
    license = "Apache-2.0"
    python_requires = "python_package/[>=1.0.0]"
    python_requires_extend = "python_package.PythonPackageRecipe"
    exports_sources = "requirements.txt"
    package_type = "application"
    parallel_make = False

    @property
    def license_path(self):
        return "LICENSE.txt"

    def configure(self):
        self.settings.rm_safe("compiler.libcxx")
        self.settings.rm_safe("compiler.cppstd")

    def source(self):
        get(
            self,
            sha256="314f56bb6b5f4e11e6260ad176b9b5188e3df4833000bbe5218e1d49e4fa87fb",
            url=f"https://github.com/nedbat/coveragepy/archive/refs/tags/{self.version}.tar.gz",
            strip_root=True,
        )
