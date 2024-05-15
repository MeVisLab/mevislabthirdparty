from conan import ConanFile
from conan.tools.files import get

required_conan_version = ">=2.2.2"


class ConanRecipe(ConanFile):
    name = "kiwisolver"
    version = "1.4.5"
    homepage = "https://github.com/nucleic/kiwi"
    description = "A fast implementation of the Cassowary constraint solver"
    license = "BSD-3-Clause"
    python_requires = "python_package/[>=1.0.0]"
    python_requires_extend = "python_package.PythonPackageRecipe"
    package_type = "application"
    exports_sources = "requirements.txt"

    @property
    def license_path(self):
        return "LICENSE"

    def configure(self):
        self.settings.rm_safe("compiler.libcxx")
        self.settings.rm_safe("compiler.cppstd")

    def source(self):
        get(self,
            sha256="2f3df2625993276a67a3ad312959f9c8333e23dfda0b7e5464b4927d34be6faa",
            url=f"https://github.com/nucleic/kiwi/archive/refs/tags/{self.version}.tar.gz",
            strip_root=True)
