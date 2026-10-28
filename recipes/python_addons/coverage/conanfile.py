from conan import ConanFile
from conan.tools.files import get

required_conan_version = ">=2.32.0"


class ConanRecipe(ConanFile):
    name = "coverage"
    version = "7.16.2"
    homepage = "https://coverage.readthedocs.io"
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
            sha256="d4f5d82461b7ea40a2486ba6b9d48987408edd2bf6fe98cc98966de159333eb9",
            url=f"https://github.com/nedbat/coveragepy/archive/refs/tags/{self.version}.tar.gz",
            strip_root=True,
        )

    def package_info(self):
        super().package_info()
        # self.cpp_info.set_property("cpe", "")  # No CPE (yet)?
        self.cpp_info.set_property("purl", f"pkg:github/nedbat/coveragepy@{self.version}")
