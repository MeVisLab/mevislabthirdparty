# -*- coding: utf-8 -*-
from conans import ConanFile

class ConanRecipe(ConanFile):
    python_requires = 'common/1.0.0@mevislab/stable'
    python_requires_extend = 'common.PythonPackageRecipe'

    def requirements(self):
        self.default_requirements()

        #self.requires(f"typing-extensions/[>=4.3.0]@{self.user}/{self.channel}")
        self.requires(f"tomli/[>=2.0.0]@{self.user}/{self.channel}")
        self.requires(f"packaging/[>=20.0.0]@{self.user}/{self.channel}")