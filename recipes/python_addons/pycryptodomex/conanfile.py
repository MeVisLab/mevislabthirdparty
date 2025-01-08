import sys

from conan import ConanFile
from conan.tools.files import get

required_conan_version = ">=2.2.2"


class ConanRecipe(ConanFile):
    name = "pycryptodomex"
    display_name = "PyCryptodome"
    version = "3.21.0"
    homepage = "https://www.pycryptodome.org"
    description = "PyCryptodome is a self-contained Python package of low-level cryptographic primitives"
    license = "BSD-2-Clause"
    python_requires = "python_package/[>=1.0.0]"
    python_requires_extend = "python_package.PythonPackageRecipe"
    package_type = "application"
    exports_sources = "requirements.txt"
    parallel_make = sys.platform != "win32"

    @property
    def license_path(self):
        return "LICENSE.rst"

    def configure(self):
        self.settings.rm_safe("compiler.libcxx")
        self.settings.rm_safe("compiler.cppstd")

    def source(self):
        get(
            self,
            sha256="7762d1b658b47e989f21ed844a8bf9a527b130fecec26f0d5076656dc38c0558",
            url=f"https://github.com/Legrandin/pycryptodome/archive/refs/tags/v{self.version}x.tar.gz",
            strip_root=True,
        )

    def package_info(self):
        super().package_info()
        self.cpp_info.set_property("cpe", "cpe:2.3:a:pycryptodome:pycryptodomex:*:*:*:*:*:*:*:*")
        self.cpp_info.set_property("base_purl", "github/Legrandin/pycryptodome")
