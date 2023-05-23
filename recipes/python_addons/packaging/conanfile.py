# -*- coding: utf-8 -*-
from conans import ConanFile

class ConanRecipe(ConanFile):
    python_requires = 'common/1.0.0@mevislab/stable'
    python_requires_extend = 'common.PythonPackageRecipe'

    def requirements(self):
        self.default_requirements()
        self.requires(f"pyparsing/[>=2.0.2]@{self.user}/{self.channel}")

    def build_requirements(self):
        self.build_requires(f"flit_core/[>=3.3]@{self.user}/{self.channel}")
        self.build_requires(f"wheel/[>=0.37.0]@{self.user}/{self.channel}")
