# -*- coding: utf-8 -*-
from conans import ConanFile
from conans import CMake
from conans import tools


class ConanRecipe(ConanFile):
    python_requires = 'common/1.0.0@mevislab/stable'
    python_requires_extend = 'common.CommonRecipe'

    _cmake = None


    def _configure_cmake(self):
        if not self._cmake:
            if tools.os_info.is_windows:
                self._cmake = CMake(self, toolset = "host=x64")
            else:
                self._cmake = CMake(self)

            self._cmake.definitions["VERSION"] = self.version
            self._cmake.definitions["ARCH"] = self.settings.arch

            self._cmake.definitions["CMAKE_DEBUG_POSTFIX"] = "d"

            self._cmake.definitions["BUILD_SHARED_LIBS"] = False
            self._cmake.definitions['CMAKE_POSITION_INDEPENDENT_CODE'] = True

            self._cmake.configure(build_folder='build')
        return self._cmake


    def build(self):
        cmake = self._configure_cmake()
        cmake.build()


    def package(self):
        cmake = self._configure_cmake()
        cmake.install()

        self.copy("*.pdb", dst="bin", keep_path=False, excludes="*vc*.pdb")

        self.default_package()


    def package_info(self):
        self.default_package_info()

        # only if statically linked
        self.cpp_info.defines = ["FFI_BUILDING"]
