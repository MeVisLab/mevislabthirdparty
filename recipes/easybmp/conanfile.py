# -*- coding: utf-8 -*-
from conans import ConanFile
from conans import tools
from conans import CMake
import os


class ConanRecipe(ConanFile):
    python_requires = 'common/1.0.0@mevislab/stable'
    python_requires_extend = 'common.CommonRecipe'
    _cmake = None


    def source(self):
        tools.mkdir('sources')
        with tools.chdir('sources'):
            self.default_source()
            tools.patch(base_path=".", patch_file=f"../patches/{self.version}-mevis.patch", strip=1)
            os.rename("BSD_(revised)_license.txt", "LICENSE")


    def _configure_cmake(self):
        if not self._cmake:
            self._cmake = CMake(self)
            self._cmake.definitions["CMAKE_DEBUG_POSTFIX"] = "d"
            self._cmake.definitions["BUILD_SHARED_LIBS"] = False
            self._cmake.definitions['CMAKE_POSITION_INDEPENDENT_CODE'] = True
            self._cmake.configure()
        return self._cmake


    def build(self):
        cmake = self._configure_cmake()
        cmake.build()


    def package(self):
        cmake = self._configure_cmake()
        cmake.install()

        self.copy("*.pdb", src="lib", dst="bin")

        self.default_package()
