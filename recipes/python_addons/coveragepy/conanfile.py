from conan import ConanFile
from conan.tools.files import get

required_conan_version = ">=2.2.2"


class ConanRecipe(ConanFile):
    name = "coveragepy"
    version = "7.6.7"
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
            sha256="c3515c03cfcae95d1db1f474d219cbd258bf5fb3d7f5fc3b394c59f210922434",
            url=f"https://github.com/nedbat/coveragepy/archive/refs/tags/{self.version}.tar.gz",
            strip_root=True,
        )

    def package_info(self):
        super().package_info()
        # self.cpp_info.set_property("cpe", "")  # No CPE (yet)?
        self.cpp_info.set_property("base_purl", "github/nedbat/coveragepy")
