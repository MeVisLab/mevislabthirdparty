# pylint: skip-file
from conan import ConanFile

from common.python_package_recipe import *  # noqa
from common.python_package_test import *    # noqa

required_conan_version = ">=2.0"


class ConanRecipe(ConanFile):
    name = "python_package"
    version = "1.0.1"
    url = "https://github.com/MeVisLab/mevislabthirdparty"
    license = "MIT"
    package_type = "python-require"
    description = "Common recipes for Python packages"
    settings = None
    exports = "*.py"

    def package_id(self):
        self.info.clear()
