# -*- coding: utf-8 -*-
from conans import ConanFile


class ConanRecipe(ConanFile):
    python_requires = 'common/1.0.0@mevislab/stable'
    python_requires_extend = 'common.PythonPackageRecipe'

    def requirements(self):
        self.default_requirements()
        self.requires(f"imagesize/[>=1.4.1]@{self.user}/{self.channel}")
        self.requires(f"sphinxcontrib-applehelp/[>=1.0.3]@{self.user}/{self.channel}")
        self.requires(f"sphinxcontrib-devhelp/[>=1.0.2]@{self.user}/{self.channel}")
        self.requires(f"sphinxcontrib-htmlhelp/[>=2.0.0]@{self.user}/{self.channel}")
        self.requires(f"sphinxcontrib-jsmath/[>=1.0.1]@{self.user}/{self.channel}")
        self.requires(f"sphinxcontrib-qthelp/[>=1.0.3]@{self.user}/{self.channel}")
        self.requires(f"sphinxcontrib-serializinghtml/[>=1.1.5]@{self.user}/{self.channel}")

    def build_requirements(self):
        self.build_requires(f"flit_core/[>=3.7.1]@{self.user}/{self.channel}")
