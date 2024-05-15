from conan import ConanFile
from conan.tools.files import get, patch

required_conan_version = ">=2.2.2"


class ConanRecipe(ConanFile):
    name = "qasync"
    version = "0.27.1"
    homepage = "https://github.com/CabbageDevelopment/qasync"
    description = "Python library for using asyncio in Qt-based applications"
    license = "BSD-2-Clause"
    python_requires = "python_package/[>=1.0.0]"
    python_requires_extend = "python_package.PythonPackageRecipe"
    package_type = "application"
    exports_sources = "requirements.txt", "patches/*"

    @property
    def license_path(self):
        return "LICENSE"

    def configure(self):
        self.settings.rm_safe("compiler.libcxx")
        self.settings.rm_safe("compiler.cppstd")

    def source(self):
        get(self,
            url="https://github.com/CabbageDevelopment/qasync/archive/refs/tags/v0.27.1.tar.gz",
            sha256="9877cfe413308cfb83e532b624f7b30a4268d194c9a53bfd68a4f5f223a18a96",
            strip_root=True)
        patch(self, patch_file="patches/001-mevis_pythonqt_support.patch",
              patch_type="feature",
              patch_description="Add PythonQt support")
        patch(self, patch_file="patches/002-fix_enum_namespace.patch",
              patch_type="compatibility",
              patch_description="Do not use enum type name in enum scope, not supported by PythonQt")
        patch(self, patch_file="patches/003-fix_qsocketnotifier_signal.patch",
              patch_type="compatibility",
              patch_description="Use signal connection form supported by PythonQt")
