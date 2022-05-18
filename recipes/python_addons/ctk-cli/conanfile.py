# -*- coding: utf-8 -*-
import os
from conans import ConanFile
import shutil
import os


class ConanRecipe(ConanFile):
    python_requires = 'common/1.0.0@mevislab/stable'
    python_requires_extend = 'common.PythonPackageRecipe'

    def source(self):
        self.default_source()
        shutil.copy(os.path.join("sources", "LICENSE_Apache_20"), os.path.join("sources", "LICENSE"))
