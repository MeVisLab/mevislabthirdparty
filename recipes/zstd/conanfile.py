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
            self.create_cmake_wrapper(add_subdirectory='sources/build/cmake')
            self._cmake = CMake(self)
            self._cmake.definitions["CMAKE_INSTALL_LIBDIR"] = "lib"
            self._cmake.definitions['CMAKE_POSITION_INDEPENDENT_CODE'] = self.settings.compiler != 'Visual Studio'
            self._cmake.definitions["ZSTD_BUILD_PROGRAMS"] = False
            self._cmake.definitions["ZSTD_BUILD_STATIC"] = True
            self._cmake.definitions["ZSTD_BUILD_SHARED"] = False
            self._cmake.definitions["ZSTD_LEGACY_SUPPORT"] = True
            self._cmake.configure()

        return self._cmake


    def build(self):
        cmake = self._configure_cmake()
        cmake.build()


    def package(self):
        cmake = self._configure_cmake()
        cmake.install()

        self.copy("*.pdb", dst="bin", keep_path=False)

        tools.rmdir(os.path.join(self.package_folder, 'lib', 'cmake'))
        tools.rmdir(os.path.join(self.package_folder, 'lib', 'pkgconfig'))

        self.default_package()


    def package_info(self):
        self.default_package_info()
        if self.settings.os == "Linux":
            self.cpp_info.system_libs.extend(["pthread"])
