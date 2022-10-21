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
        channel = f"@{self.user}/{self.channel}"
        self.requires("xz-utils/[>=5.2.5]" + channel)
        self.requires("zlib/[>=1.2.11]" + channel)
        self.requires("zstd/[>=1.5.0]" + channel)
        #self.requires("webp/[>=1.2.0]" + channel)
        #self.requires("jbigkit/[>2.1]" + channel)
        self.requires("libjpeg/9e" + channel)


    def _configure_cmake(self):
        if not self._cmake:
            self.create_cmake_wrapper()
            self._cmake = CMake(self)
            self._cmake.definitions["CMAKE_DEBUG_POSTFIX"] = "d"
            self._cmake.definitions["BUILD_SHARED_LIBS"] = True
            self._cmake.definitions['CMAKE_INSTALL_LIBDIR'] = 'lib'
            self._cmake.definitions['CMAKE_INSTALL_BINDIR'] = 'bin'
            self._cmake.definitions['CMAKE_INSTALL_INCLUDEDIR'] = 'include'

            self._cmake.definitions['CMAKE_DISABLE_FIND_PACKAGE_OpenGL'] = True
            self._cmake.definitions['CMAKE_DISABLE_FIND_PACKAGE_GLUT'] = True

            self._cmake.definitions["lzma"] = "xz-utils" in self.deps_cpp_info.deps
            self._cmake.definitions["jpeg"] = "libjpeg" in self.deps_cpp_info.deps
            self._cmake.definitions["zlib"] = "zlib" in self.deps_cpp_info.deps
            self._cmake.definitions["webp"] = "webp" in self.deps_cpp_info.deps
            self._cmake.definitions["zstd"] = "zstd" in self.deps_cpp_info.deps
            self._cmake.definitions["jbig"] = "jbigkit" in self.deps_cpp_info.deps
            self._cmake.definitions["jpeg12"] = False
            self._cmake.definitions["cxx"] = False
            self._cmake.configure()
        return self._cmake


    def build(self):
        cmake = self._configure_cmake()
        cmake.build()


    def package(self):
        cmake = self._configure_cmake()
        cmake.install()

        self.copy("tiffd.pdb", src="bin", dst="bin")

        if not tools.os_info.is_windows:
            tools.rmdir(os.path.join(self.package_folder, 'bin'))

        tools.rmdir(os.path.join(self.package_folder, 'share'))
        tools.rmdir(os.path.join(self.package_folder, 'lib', 'cmake'))
        tools.rmdir(os.path.join(self.package_folder, 'lib', 'pkgconfig'))

        self.patch_binaries()
        self.default_package()


    def package_info(self):
        self.default_package_info()

        if self.settings.os == "Linux":
            self.cpp_info.libs.extend(["m"])
