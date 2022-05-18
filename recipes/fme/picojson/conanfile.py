# -*- coding: utf-8 -*-
from conans import ConanFile


class ConanRecipe(ConanFile):
    python_requires = 'common/1.0.0@mevislab/stable'
    python_requires_extend = 'common.CommonRecipe'

    def package(self):
        self.copy("picojson.h", src="sources", dst="include")
        self.default_package()
