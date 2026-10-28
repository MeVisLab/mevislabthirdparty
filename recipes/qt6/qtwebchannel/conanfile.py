from conan import ConanFile
from conan.tools.files import rmdir
import os

required_conan_version = ">=2.32.0"


class ConanRecipe(ConanFile):
    python_requires = "qt_package/1.0.0"
    python_requires_extend = "qt_package.QtPackage"

    def package(self):
        super().package()
        rmdir(self, os.path.join(self.package_folder, "share"))
