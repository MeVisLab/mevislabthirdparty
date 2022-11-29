# -*- coding: utf-8 -*-
from conans import ConanFile
from conans import tools
from conans import CMake
from conans.errors import ConanException
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
            self.create_cmake_wrapper()
            self._cmake = CMake(self)
            self._cmake.definitions["CMAKE_DEBUG_POSTFIX"] = "d"
            self._cmake.definitions["BUILD_SHARED_LIBS"] = True
            self._cmake.definitions['CMAKE_INSTALL_LIBDIR'] = 'lib'
            self._cmake.definitions['CMAKE_INSTALL_BINDIR'] = 'bin'
            self._cmake.definitions['CMAKE_INSTALL_INCLUDEDIR'] = 'include'
            self._cmake.definitions["PNG_TESTS"] = False
            self._cmake.definitions["PNG_SHARED"] = True
            self._cmake.definitions["PNG_STATIC"] = False
            self._cmake.definitions["PNG_DEBUG"] = self.settings.build_type != "Release"

            self._cmake.configure()
        return self._cmake


    def build(self):
        cmake = self._configure_cmake()
        cmake.build()


    def package(self):
        cmake = self._configure_cmake()
        cmake.install()

        self.copy("libpng*.pdb", src="bin", dst="bin")

        tools.rmdir(os.path.join(self.package_folder, "lib", "pkgconfig"))
        tools.rmdir(os.path.join(self.package_folder, "lib", "libpng"))
        tools.rmdir(os.path.join(self.package_folder, "share"))

        self.patch_binaries(executables=['pngfix'])
        self.default_package()


    def package_info(self):
        self.default_package_info()
        if self.settings.os == "Linux":
            self.cpp_info.system_libs.append("m")
