# -*- coding: utf-8 -*-
from conans import ConanFile
from conans import CMake
from conans import tools
import os


class ConanRecipe(ConanFile):
    python_requires = 'common/1.0.0@mevislab/stable'
    python_requires_extend = 'common.CommonRecipe'

    _cmake = None


    def requirements(self):
        channel = "@{0}/{1}".format(self.user, self.channel)
        self.requires("zlib/[>=1.2.11]" + channel)


    def _configure_cmake(self):
        if not self._cmake:
            self._cmake = CMake(self)
            self._cmake.definitions["CMAKE_DEBUG_POSTFIX"] = "d"
            self._cmake.definitions["BUILD_SHARED_LIBS"] = True
            self._cmake.definitions["CMAKE_C_VISIBILITY_PRESET"] = 'default'
            self._cmake.definitions["CMAKE_CXX_VISIBILITY_PRESET"] = 'default'
            self._cmake.definitions["CMAKE_VISIBILITY_INLINES_HIDDEN"] = False
            self._cmake.configure()
        return self._cmake


    def build(self):
        cmake = self._configure_cmake()
        cmake.build()


    def package(self):
        cmake = self._configure_cmake()
        cmake.install()

        self.copy("*.pdb", src="bin", dst="bin")

        self.patch_binaries()
        self.default_package()


    def package_info(self):
        self.default_package_info()
        self.cpp_info.includedirs = ["include", "include/minizip"]
