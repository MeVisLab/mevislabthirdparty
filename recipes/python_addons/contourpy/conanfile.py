from conan import ConanFile
from conan.tools.files import get
from conan.tools.gnu import PkgConfigDeps
from conan.tools.meson import MesonToolchain

required_conan_version = ">=2.2.2"


class ConanRecipe(ConanFile):
    name = "contourpy"
    version = "1.3.3"
    homepage = "https://contourpy.readthedocs.io"
    description = "Python library for calculating contours of 2D quadrilateral grids"
    license = "BSD-3-Clause"
    python_requires = "python_package/[>=1.0.0]"
    python_requires_extend = "python_package.PythonPackageRecipe"
    exports_sources = "requirements.txt"
    package_type = "shared-library"

    @property
    def license_path(self):
        return "LICENSE"

    def python_requirements(self):
        self.requires("numpy/[>=1.23.0]")

    def generate(self):
        super().generate()
        deps = PkgConfigDeps(self)
        deps.generate()
        tc = MesonToolchain(self)
        tc.generate()

    def source(self):
        get(
            self,
            sha256="c1e4d622e9d4f3081dbdb438b403e50557be7284a41d9a21316414405848ba62",
            url=f"https://github.com/contourpy/contourpy/archive/refs/tags/v{self.version}.tar.gz",
            strip_root=True,
        )

    def package_info(self):
        super().package_info()
        self.cpp_info.set_property("cpe", "")
        self.cpp_info.set_property("purl", f"pkg:github/contourpy/contourpy@v{self.version}")
