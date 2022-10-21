# -*- coding: utf-8 -*-
# pylint: skip-file
from conans import ConanFile
from conans.errors import ConanInvalidConfiguration

from common.commonrecipe import *
from common.pythonpackagerecipe import *

from common.commontest import *
from common.pythonpackagetest import *

required_conan_version = ">=1.51.0"

class ConanRecipe(ConanFile):
    name = "common"
    version = "1.0.0"
    url = "http://mms-build.mevis.lokal"
    license = "MIT"
    description = "Common recipes for MeVisLab Conan packages"
    settings = None
    exports = "*.py"
    default_user = "mevislab"
    default_channel = "stable"


    def package_id(self):
        self.info.clear()
