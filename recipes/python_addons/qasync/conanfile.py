from conan import ConanFile
from conan.tools.files import get, patch

required_conan_version = ">=2.32.0"


class ConanRecipe(ConanFile):
    name = "qasync"
    version = "0.28.0"
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
        get(
            self,
            sha256="1b80e2315663350b04c2c780d8ea0c76f5e4cf09fb55347e40cb16540e6411d7",
            url=f"https://github.com/CabbageDevelopment/qasync/archive/refs/tags/v{self.version}.tar.gz",
            strip_root=True,
        )
        patch(
            self,
            patch_file="patches/001-mevis_pythonqt_support.patch",
            patch_type="feature",
            patch_description="Add PythonQt support",
        )
        patch(
            self,
            patch_file="patches/002-fix_enum_namespace.patch",
            patch_type="compatibility",
            patch_description="Do not use enum type name in enum scope, not supported by PythonQt",
        )
        patch(
            self,
            patch_file="patches/003-fix_qsocketnotifier_signal.patch",
            patch_type="compatibility",
            patch_description="Use signal connection form supported by PythonQt",
        )

    def package_info(self):
        super().package_info()
        # self.cpp_info.set_property("cpe", "")  # No CPE (yet)?
        self.cpp_info.set_property("purl", f"pkg:github/CabbageDevelopment/qasync@v{self.version}")
