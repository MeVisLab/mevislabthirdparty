# -*- coding: utf-8 -*-
from conans import ConanFile
from conans import tools
from conans import CMake
import os


class ConanRecipe(ConanFile):
    python_requires = 'common/1.0.0@mevislab/stable'
    python_requires_extend = 'common.CommonRecipe'

    _cmake = None

    def requirements(self):
        self.requires(f"tbb/[>=2021.4.0]@{self.user}/{self.channel}")


    def _configure_cmake(self):
        if not self._cmake:
            self.create_cmake_wrapper()
            self._cmake = CMake(self)
            self._cmake.definitions["BUILD_SHARED_LIBS"] = True
            self._cmake.definitions['EMBREE_ISPC_SUPPORT'] = False
            self._cmake.definitions['EMBREE_TUTORIALS'] = False
            self._cmake.definitions['BUILD_DOC'] = False

            self._cmake.configure()

        return self._cmake


    def build(self):
        cmake = self._configure_cmake()
        cmake.build()


    def package(self):
        cmake = self._configure_cmake()
        cmake.install()

        tools.rmdir(os.path.join(self.package_folder, 'lib', 'cmake'))
        tools.rmdir(os.path.join(self.package_folder, 'share'))

        self.patch_binaries()
        self.default_package()
