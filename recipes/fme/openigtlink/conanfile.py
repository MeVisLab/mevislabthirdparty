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
            self._cmake.definitions["CMAKE_DEBUG_POSTFIX"] = "d"
            self._cmake.definitions["BUILD_SHARED_LIBS"] = True
            self._cmake.definitions["BUILD_TESTING"] = False

            self._cmake.definitions["CMAKE_CXX_VISIBILITY_PRESET"] = "default"
            self._cmake.definitions["CMAKE_C_VISIBILITY_PRESET"] = "default"

            self._cmake.definitions["OpenIGTLink_INSTALL_LIB_DIR"] = "lib"

            self._cmake.configure()
        return self._cmake


    def build(self):
        cmake = self._configure_cmake()
        cmake.build()


    def package(self):
        cmake = self._configure_cmake()
        cmake.install()

        tools.rmdir(os.path.join(self.package_folder, "lib", "cmake"))

        self.patch_binaries()
        self.default_package()


    def package_info(self):
        self.default_package_info()
        self.cpp_info.includedirs = ['include', f'include/igtl']
