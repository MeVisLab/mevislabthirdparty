# -*- coding: utf-8 -*-
from conans import ConanFile
import shutil
import os


class ConanRecipe(ConanFile):
    python_requires = 'common/1.0.0@mevislab/stable'
    python_requires_extend = 'common.PythonPackageRecipe'


    def source(self):
        super().source()
        if not os.path.exists('sources/COPYING'):
            shutil.copy2('sources/LICENSE.rst', 'sources/LICENSE')
