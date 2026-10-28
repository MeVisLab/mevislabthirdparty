from conan import ConanFile
from conan.tools.files import get

required_conan_version = ">=2.32.0"


class ConanRecipe(ConanFile):
    name = "kiwisolver"
    version = "1.5.1"
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
        get(
            self,
            sha256="dffda5b3207852201ab66f82364ec6cf06c3285eb13cf688ae90b12a99445d9d",
            url=f"https://github.com/nucleic/kiwi/archive/refs/tags/{self.version}.tar.gz",
            strip_root=True,
        )

    def package_info(self):
        super().package_info()
        # self.cpp_info.set_property("cpe", "")  # No CPE (yet)?
        self.cpp_info.set_property("purl", f"pkg:github/nucleic/kiwi@{self.version}")
