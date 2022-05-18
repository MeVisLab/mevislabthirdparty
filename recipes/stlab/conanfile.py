# -*- coding: utf-8 -*-
from conans import ConanFile
from conans import CMake
from conans import tools
import os


class ConanRecipe(ConanFile):
    python_requires = 'common/1.0.0@mevislab/stable'
    python_requires_extend = 'common.CommonRecipe'

    _cmake = None

    def source(self):
        self.default_source()
        tools.replace_in_file("sources/CMakeLists.txt",
          "include( InstallRequiredSystemLibraries )", "# include( InstallRequiredSystemLibraries )")

    def _configure_cmake(self):
        if not self._cmake:
            self.create_cmake_wrapper()
            self._cmake = CMake(self)
            self._cmake.configure()

        return self._cmake


    def build(self):
        cmake = self._configure_cmake()
        cmake.build()


    def package(self):
        cmake = self._configure_cmake()
        cmake.install()

        tools.rmdir(os.path.join(self.package_folder, 'share'))

        self.default_package()


    def package_info(self):
        self.default_package_info()
        if self.settings.os == "Linux":
            self.cpp_info.libs.extend(["pthread"])
