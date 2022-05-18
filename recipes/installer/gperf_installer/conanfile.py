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
        self.copy("*", dst="bin", src="sources", keep_path=False)
        self.default_package()


    def package_info(self):
        self.output.info("Appending PATH env var with: " + os.path.join(self.package_folder, "bin"))
        self.env_info.path.append(os.path.join(self.package_folder, "bin"))
        self.cpp_info.libdirs = []
        self.cpp_info.includedirs = []
