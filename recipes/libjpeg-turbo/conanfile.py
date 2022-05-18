# -*- coding: utf-8 -*-
from conans import ConanFile
from conans import tools
from conans import CMake
import os


class ConanRecipe(ConanFile):
    python_requires = 'common/1.0.0@mevislab/stable'
    python_requires_extend = 'common.CommonRecipe'

    _cmake = None

    def build_requirements(self):
        channel = "@{0}/{1}".format(self.user, self.channel)
        if self.settings.os == 'Windows':
            self.build_requires("nasm_installer/[>=2.14]" + channel)


    def _configure_cmake(self):
        if not self._cmake:
            self.create_cmake_wrapper()
            self._cmake = CMake(self)
            self._cmake.definitions["CMAKE_DEBUG_POSTFIX"] = "d"
            self._cmake.definitions["CMAKE_POSITION_INDEPENDENT_CODE"] = True
            self._cmake.definitions["BUILD_SHARED_LIBS"] = True
            self._cmake.definitions["ENABLE_STATIC"] = False
            self._cmake.definitions["ENABLE_SHARED"] = True
            self._cmake.definitions["REQUIRE_SIMD"] = True  # no simd -> error!
            self._cmake.configure()
        return self._cmake


    def build(self):
        cmake = self._configure_cmake()
        cmake.build()


    def package(self):
        cmake = self._configure_cmake()
        cmake.install()

        tools.rmdir(os.path.join(self.package_folder, "lib", "pkgconfig"))
        tools.rmdir(os.path.join(self.package_folder, "lib", "cmake"))
        tools.rmdir(os.path.join(self.package_folder, "share"))

        self.patch_binaries()
        self.default_package()


    def package_info(self):
        self.default_package_info()
        self.cpp_info.names["pkg_config"] = "libturbojpeg"
