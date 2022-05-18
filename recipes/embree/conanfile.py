# -*- coding: utf-8 -*-
from conans import ConanFile
from conans import tools
from conans import CMake
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
            self._cmake.definitions['EMBREE_ISPC_SUPPORT'] = False
            self._cmake.definitions['EMBREE_TUTORIALS'] = False
            self._cmake.definitions['EMBREE_TASKING_SYSTEM'] = "INTERNAL"

            self._cmake.configure()

        return self._cmake


    def build(self):
        cmake = self._configure_cmake()
        cmake.build()


    def package(self):
        cmake = self._configure_cmake()
        cmake.install()

        self.copy("*.pdb", src="bin", dst="bin")

        tools.rmdir(os.path.join(self.package_folder, 'bin', 'models'))
        tools.rmdir(os.path.join(self.package_folder, 'lib', 'cmake'))
        tools.rmdir(os.path.join(self.package_folder, 'share'))

        for f in ["embree-config.cmake", "embree-config-version.cmake"]:
            ff = os.path.join(self.package_folder, f)
            if os.path.exists(ff):
                os.remove(ff)

        self.patch_binaries()
        self.default_package()
