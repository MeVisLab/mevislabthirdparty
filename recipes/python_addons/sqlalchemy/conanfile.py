from conan import ConanFile
from conan.tools.files import get

required_conan_version = ">=2.2.2"


class ConanRecipe(ConanFile):
    name = "sqlalchemy"
    version = "2.0.32"
    homepage = "https://www.sqlalchemy.org"
    description = (
        "SQLAlchemy is the Python SQL toolkit and Object Relational Mapper "
        "that gives application developers the full power and flexibility of SQL"
    )
    license = "MIT"
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
        version = self.version.replace(".", "_")
        get(
            self,
            sha256="8e9069eca2f97cdeb83d0774c735d5de5cbcc07ccd4cffcd87f0509419257eb8",
            url=f"https://github.com/sqlalchemy/sqlalchemy/archive/refs/tags/rel_{version}.tar.gz",
            strip_root=True,
        )
