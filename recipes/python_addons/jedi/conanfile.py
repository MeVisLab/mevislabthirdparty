from conan import ConanFile
from conan.tools.files import get, patch

required_conan_version = ">=2.2.2"


class ConanRecipe(ConanFile):
    name = "jedi"
    version = "0.8.1"
    homepage = "https://github.com/davidhalter/jedi"
    description = "Awesome autocompletion, static analysis and refactoring library for python"
    license = "MIT"
    python_requires = "python_package/[>=1.0.0]"
    python_requires_extend = "python_package.PythonPackageRecipe"
    package_type = "application"

    @property
    def license_path(self):
        return "LICENSE.txt"

    def configure(self):
        self.settings.rm_safe("compiler.libcxx")
        self.settings.rm_safe("compiler.cppstd")

    def source(self):
        get(self,
            url=f"https://github.com/davidhalter/jedi/archive/v{self.version}.tar.gz",
            sha256="3964b52366cc1700a438ca2d08d956a8b758953bd719cb8f7b0159186a84c44e",
            strip_root=True)
        patch(self, patch_file="patches/001-adapt_jedi_for_use_in_MATE.patch")
        patch(self, patch_file="patches/002-support_for_autocompletion_on_python_properties.patch")
