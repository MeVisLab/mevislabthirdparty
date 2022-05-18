# -*- coding: utf-8 -*-
from conans import ConanFile
from conans.errors import ConanInvalidConfiguration
import os


class ConanRecipe(ConanFile):
    python_requires = 'common/1.0.0@mevislab/stable'
    python_requires_extend = 'common.CommonRecipe'

    settings = "os"

    def validate(self):
        if self.settings.os != "Linux":
            raise ConanInvalidConfiguration(f"{self.name} is only supported on Linux")


    def package(self):
        self.copy("*", dst="MeVis/ThirdParty/Resources/Linux", src="sources", keep_path=True)
        self.default_package()


    def package_info(self):
        self.cpp_info.libdirs = []
        self.cpp_info.includedirs = []
