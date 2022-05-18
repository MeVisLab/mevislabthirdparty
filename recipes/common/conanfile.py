# -*- coding: utf-8 -*-
# pylint: skip-file
from conans import ConanFile

from common.commonrecipe import *
from common.pythonpackagerecipe import *

from common.commontest import *
from common.pythonpackagetest import *

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
