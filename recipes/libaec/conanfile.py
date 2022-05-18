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
            self._cmake = CMake(self, parallel=not(tools.os_info.is_windows and self.settings.build_type == "Debug"))
            self._cmake.definitions["BUILD_TESTING"] = False
            self._cmake.configure(build_folder='build')
        return self._cmake


    def build(self):
        cmake = self._configure_cmake()
        cmake.build()


    def package(self):
        cmake = self._configure_cmake()
        cmake.install()

        self.copy("*.pdb", src="build/bin", dst="bin")

        tools.rmdir(os.path.join(self.package_folder, 'cmake'))
        tools.rmdir(os.path.join(self.package_folder, 'share'))

        self.patch_binaries()
        self.default_package()
