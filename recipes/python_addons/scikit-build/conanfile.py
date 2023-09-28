# -*- coding: utf-8 -*-
from conans import ConanFile
from conans import tools
import os

class ConanRecipe(ConanFile):
    python_requires = 'common/1.0.0@mevislab/stable'
    python_requires_extend = 'common.PythonPackageRecipe'

    sanitizer = { 'cmake': False }

    def build_requirements(self):
        self.build_requires(f"setuptools_scm/[>=7.0.5]@{self.user}/{self.channel}")

    def requirements(self):
        self.default_requirements()

        self.requires(f"packaging/[>=21.3]@{self.user}/{self.channel}")
        self.requires(f"pyparsing/[>=3.0.0]@{self.user}/{self.channel}")
        self.requires(f"wheel/[>=0.37.0]@{self.user}/{self.channel}")


    def package(self):
        self.default_package()
        v = tools.Version(self.requires["python"].ref.version)
        tools.rmdir(os.path.join(self.package_folder, 'lib', f'python{v.major}.{v.minor}', 'site-packages', 'skbuild', 'resources', 'cmake'))
