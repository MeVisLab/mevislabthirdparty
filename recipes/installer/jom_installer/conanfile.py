# -*- coding: utf-8 -*-
from conans import ConanFile
from conans.errors import ConanInvalidConfiguration
import os

class ConanRecipe(ConanFile):
    python_requires = 'common/1.0.0@mevislab/stable'
    python_requires_extend = 'common.CommonRecipe'

    settings = "os"


    def validate(self):
        if self.settings.os != "Windows":
            raise ConanInvalidConfiguration(f"{self.name} is only supported on Windows")


    def package(self):
        self.copy("*.exe", dst="bin", src="")
        self.default_package()


    def package_info(self):
        self.env_info.path.append(os.path.join(self.package_folder, "bin"))
