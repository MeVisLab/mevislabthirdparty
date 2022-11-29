# -*- coding: utf-8 -*-
from conans import ConanFile
from conans import tools
from conans import CMake
import os


class ConanRecipe(ConanFile):
    python_requires = 'common/1.0.0@mevislab/stable'
    python_requires_extend = 'common.CommonRecipe'

    _cmake = None


    def requirements(self):
        channel = "@{0}/{1}".format(self.user, self.channel)
        self.requires('libsodium/[>=1.0.18]' + channel)


    def _configure_cmake(self):
        if not self._cmake:
            self.create_cmake_wrapper()
            self._cmake = CMake(self)
            self._cmake.definitions['CMAKE_DEBUG_POSTFIX'] = "d"

            self._cmake.definitions['ENABLE_CURVE'] = True
            self._cmake.definitions['ENABLE_CPACK'] = False
            self._cmake.definitions['WITH_LIBSODIUM'] = True
            self._cmake.definitions['ZMQ_BUILD_TESTS'] = False
            self._cmake.definitions['WITH_PERF_TOOL'] = False
            self._cmake.definitions['BUILD_SHARED'] = True
            self._cmake.definitions['BUILD_STATIC'] = False
            self._cmake.configure()
        return self._cmake


    def build(self):
        cmake = self._configure_cmake()
        cmake.build()


    def package(self):
        cmake = self._configure_cmake()
        cmake.install()

        self.copy("*.pdb", src="bin", dst="bin")

        tools.rmdir(os.path.join(self.package_folder, "doc"))
        tools.rmdir(os.path.join(self.package_folder, "share"))
        tools.rmdir(os.path.join(self.package_folder, "CMake"))
        tools.rmdir(os.path.join(self.package_folder, "lib", "cmake"))
        tools.rmdir(os.path.join(self.package_folder, "lib", "pkgconfig"))

        self.patch_binaries()
        self.default_package()
