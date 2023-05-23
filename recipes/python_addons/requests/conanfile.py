# -*- coding: utf-8 -*-
from conans import ConanFile

class ConanRecipe(ConanFile):
    python_requires = 'common/1.0.0@mevislab/stable'
    python_requires_extend = 'common.PythonPackageRecipe'


    def requirements(self):
        self.default_requirements()

        self.requires(f"idna/[>=3.3]@{self.user}/{self.channel}")
        self.requires(f"certifi/[>=2022.06.15]@{self.user}/{self.channel}")
        self.requires(f"chardet/[>=4.0.0]@{self.user}/{self.channel}")
        self.requires(f"urllib3/[>=1.26.7]@{self.user}/{self.channel}")

    def build_requirements(self):
        self.build_requires(f"wheel/[>=0.37.0]@{self.user}/{self.channel}")
