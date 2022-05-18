# -*- coding: utf-8 -*-
from conans import ConanFile
import os

class ConanRecipe(ConanFile):
    python_requires = 'common/1.0.0@mevislab/stable'
    python_requires_extend = 'common.CommonRecipe'

    no_copy_source = True


    def package(self):
        self.copy("*", src=os.path.join("sources", "CL"), dst=os.path.join("include", "CL"))
        self.default_package()
