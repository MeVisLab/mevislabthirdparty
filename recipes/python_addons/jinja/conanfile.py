# -*- coding: utf-8 -*-
from conans import ConanFile

class ConanRecipe(ConanFile):
    python_requires = 'common/1.0.0@mevislab/stable'
    python_requires_extend = 'common.PythonPackageRecipe'


    def requirements(self):
        self.default_requirements()

        self.requires(f"markupsafe/[>=2.0.1]@{self.user}/{self.channel}")
