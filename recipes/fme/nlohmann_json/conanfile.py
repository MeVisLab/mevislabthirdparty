# -*- coding: utf-8 -*-
from conans import ConanFile
from conans import CMake
from conans import tools
import os

class ConanRecipe(ConanFile):
    python_requires = 'common/1.0.0@mevislab/stable'
    python_requires_extend = 'common.CommonRecipe'

    _cmake = None

    def _configure_cmake(self):
        if not self._cmake:
            self.create_cmake_wrapper()
            self._cmake = CMake(self)
            self._cmake.definitions["JSON_Install"] = True

            self._cmake.configure()
        return self._cmake


    def source(self):
        self.default_source()
        os.rename(os.path.join("sources", "LICENSE.MIT"), os.path.join("sources", "LICENSE"))


    def build(self):
        cmake = self._configure_cmake()
        cmake.build()


    def package(self):
        cmake = self._configure_cmake()
        cmake.install()

        tools.rmdir(os.path.join(self.package_folder, "lib"))

        self.default_package()
