# -*- coding: utf-8 -*-
from conans import ConanFile
from conans import tools
from conans import CMake
import os

class ConanRecipe(ConanFile):
    python_requires = 'common/1.0.0@mevislab/stable'
    python_requires_extend = 'common.CommonRecipe'

    def package(self):
        self.copy(src="sources/CDT/include", dst="include/CDT", pattern="*.h*", keep_path=True)
        self.default_package()
