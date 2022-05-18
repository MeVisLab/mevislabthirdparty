# -*- coding: utf-8 -*-
from conans import ConanFile
from conans import tools
from conans.errors import ConanInvalidConfiguration
import os


class ConanRecipe(ConanFile):
    python_requires = 'common/1.0.0@mevislab/stable'
    python_requires_extend = 'common.CommonRecipe'

    settings = "os"
    no_copy_source = True

    sanitizer = { 'cmake': False }


    def validate(self):
        if self.settings.os != "Windows":
            raise ConanInvalidConfiguration(f"{self.name} is only supported on Windows")


    def package(self):
        self.copy("*", keep_path=True)
        self.default_package()


    def package_info(self):
        self.env_info.PATH.append(os.path.join(self.package_folder, "perl", "bin"))
