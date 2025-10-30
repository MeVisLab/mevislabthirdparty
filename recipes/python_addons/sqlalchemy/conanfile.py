import os

from conan import ConanFile
from conan.tools.files import get, replace_in_file

required_conan_version = ">=2.2.2"


class ConanRecipe(ConanFile):
    name = "sqlalchemy"
    version = "2.0.43"
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
            sha256="1e4efbca2df9a0584d2c35c2b435008bb9cd3aece718a8b595b9c1edd5bbceab",
            url=f"https://github.com/sqlalchemy/sqlalchemy/archive/refs/tags/rel_{version}.tar.gz",
            strip_root=True,
        )
        replace_in_file(self, os.path.join(self.source_folder, "setup.cfg"), "tag_build = dev", "")

    def package_info(self):
        super().package_info()
        self.cpp_info.set_property("cpe", "cpe:2.3:a:sqlalchemy:sqlalchemy:*:*:*:*:*:*:*:*")
        self.cpp_info.set_property("purl", f"pkg:github/sqlalchemy/sqlalchemy@rel_{self.version.replace('.', '_')}")
