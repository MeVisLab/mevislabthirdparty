# -*- coding: utf-8 -*-
from conans import ConanFile

class ConanRecipe(ConanFile):
    python_requires = 'common/1.0.0@mevislab/stable'
    python_requires_extend = 'common.PythonPackageRecipe'

    def requirements(self):
        self.default_requirements()

        self.requires(f"requests/[>=2.26.0]@{self.user}/{self.channel}")
