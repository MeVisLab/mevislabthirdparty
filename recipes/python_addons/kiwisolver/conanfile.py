# -*- coding: utf-8 -*-
from conans import ConanFile


class ConanRecipe(ConanFile):
    python_requires = 'common/1.0.0@mevislab/stable'
    python_requires_extend = 'common.PythonPackageRecipe'

    def build_requirements(self):
        self.build_requires(f"setuptools_scm/[>=7.0.5]@{self.user}/{self.channel}")
		# pinned for Python 3.9, change for newer Python version
        self.build_requires(f"cppy/[==1.2.0]@{self.user}/{self.channel}")
        self.build_requires(f"wheel/[>=0.38.4]@{self.user}/{self.channel}")
