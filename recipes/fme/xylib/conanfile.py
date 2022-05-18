# -*- coding: utf-8 -*-
from conans import ConanFile
from conans import CMake
from conans import tools
import glob
import os

class ConanRecipe(ConanFile):
    python_requires = 'common/1.0.0@mevislab/stable'
    python_requires_extend = 'common.CommonRecipe'

    _cmake = None

    def requirements(self):
        channel = f"@{self.user}/{self.channel}"
        self.requires("boost/[>=1.75.0]" + channel)
        self.requires("bzip2/[>=1.0.8]" + channel)
        self.requires("zlib/[>=1.2.11]" + channel)


    def _configure_cmake(self):
        if not self._cmake:
            self.create_cmake_wrapper()
            self._cmake = CMake(self)
            self._cmake.definitions["CMAKE_DEBUG_POSTFIX"] = "d"
            self._cmake.definitions["BUILD_SHARED_LIBS"] = True

            self._cmake.definitions["USE_ZLIB"] = True
            self._cmake.definitions["DOWNLOAD_ZLIB"] = False
            self._cmake.definitions["USE_BZIP2"] = True
            self._cmake.definitions["GUI"] = False

            self._cmake.definitions["Boost_NO_SYSTEM_PATHS"] = True
            self._cmake.definitions["BOOST_INCLUDEDIR"] = ";".join(self.deps_cpp_info["boost"].include_paths)
            self._cmake.definitions["BOOST_LIBRARYDIR"] = ";".join(self.deps_cpp_info["boost"].lib_paths)

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
