# -*- coding: utf-8 -*-
from conans import ConanFile
from conans.errors import ConanInvalidConfiguration

class ConanRecipe(ConanFile):
    python_requires = 'common/1.0.0@mevislab/stable'
    python_requires_extend = 'common.PythonPackageRecipe'


    def validate(self):
        if self.settings.os != "Windows":
            raise ConanInvalidConfiguration(f"{self.name} is only supported on Windows")
