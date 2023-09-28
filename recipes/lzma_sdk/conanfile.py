# -*- coding: utf-8 -*-
from conans import ConanFile
from conans import CMake
from conans import tools
from conans.errors import ConanException
import os
import shutil

class ConanRecipe(ConanFile):
    python_requires = 'common/1.0.0@mevislab/stable'
    python_requires_extend = 'common.CommonRecipe'

    _cmake = None

    def build_requirements(self):
        channel = "@{0}/{1}".format(self.user, self.channel)
        if self.settings.os == "Windows":
            self.build_requires("7z_installer/23.01" + channel)

    def source(self):
        self.default_source()
        zipFile = f"lzma1900.7z"
        self.run(f"7za x {zipFile} -osources")
        shutil.copy('sources/DOC/lzma-sdk.txt', 'sources/LICENSE')
        os.remove(zipFile)

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
        self.default_package()

    def package_info(self):
        super().package_info()
        self.cpp_info.includedirs = ["include", "include/C"]
