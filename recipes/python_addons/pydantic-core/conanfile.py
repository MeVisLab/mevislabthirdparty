from conan import ConanFile
from conan.tools.files import get

required_conan_version = ">=2.32.0"


class ConanRecipe(ConanFile):
    name = "pydantic-core"
    version = "2.46.5"
    homepage = "https://github.com/pydantic/pydantic"
    description = "Core validation logic for pydantic written in rust"
    license = "MIT"
    python_requires = "python_package/[>=1.0.0]"
    python_requires_extend = "python_package.PythonPackageRecipe"
    exports_sources = "requirements.txt"
    package_type = "application"

    @property
    def license_path(self):
        return "LICENSE"

    def configure(self):
        self.settings.rm_safe("compiler.libcxx")
        self.settings.rm_safe("compiler.cppstd")

    def source(self):
        get(
            self,
            sha256="10416c15b8839ecc4ef4d0885da76da6fd0f67333a0eb8aff6d93c4b8f2910fc",
            url=f"https://files.pythonhosted.org/packages/source/p/pydantic_core/pydantic_core-{self.version}.tar.gz",
            strip_root=True,
        )

    def package_info(self):
        super().package_info()
        self.cpp_info.set_property("cpe", f"cpe:2.3:a:pydantic:pydantic:{self.version}:*:*:*:*:*:*:*")
        self.cpp_info.set_property("purl", f"pkg:github/pydantic/pydantic@{self.version}")
