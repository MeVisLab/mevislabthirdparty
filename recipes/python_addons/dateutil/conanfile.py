# -*- coding: utf-8 -*-
from conans import ConanFile


class ConanRecipe(ConanFile):
    python_requires = 'common/1.0.0@mevislab/stable'
    python_requires_extend = 'common.PythonPackageRecipe'

    def requirements(self):
        self.default_requirements()
        self.requires(f"six/[>=1.16.0]@{self.user}/{self.channel}")

    def build_requirements(self):
        self.build_requires(f"wheel/[>=0.38.4]@{self.user}/{self.channel}")
        self.build_requires(f"setuptools_scm/[>=7.0.5]@{self.user}/{self.channel}")
