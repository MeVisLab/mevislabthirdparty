# -*- coding: utf-8 -*-
from conans import ConanFile


class ConanRecipe(ConanFile):
    python_requires = 'common/1.0.0@mevislab/stable'
    python_requires_extend = 'common.PythonPackageRecipe'

    def build_requirements(self):
        self.build_requires(f"flit_core/[>=3.7.1]@{self.user}/{self.channel}")
        self.build_requires(f"wheel/[>=0.37.0]@{self.user}/{self.channel}")
