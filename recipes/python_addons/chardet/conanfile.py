# -*- coding: utf-8 -*-
from conans import ConanFile
from conans import tools
import os

class ConanRecipe(ConanFile):
    python_requires = 'common/1.0.0@mevislab/stable'
    python_requires_extend = 'common.PythonPackageRecipe'

    # def source(self):
    #     self.default_source()
    #     # remove GPL only code
    #     tools.rmdir(os.path.join(self.source_folder, "sources", "tools", "editor"))
