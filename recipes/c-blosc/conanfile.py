# -*- coding: utf-8 -*-
from conans import ConanFile
from conans import CMake
from conans import tools
import shutil
import os


class ConanRecipe(ConanFile):
    python_requires = 'common/1.0.0@mevislab/stable'
    python_requires_extend = 'common.CommonRecipe'

    _cmake = None

    def requirements(self):
        channel = "@{0}/{1}".format(self.user, self.channel)
        self.requires("lz4/[>=1.9.4]" + channel)
        self.requires("zlib/[>=1.2.11]" + channel)
        self.requires("zstd/[>=1.4.9]" + channel)

    def source(self):
        self.default_source()
        tools.rmdir(os.path.join("sources", "internal-complibs"))

    def _configure_cmake(self):
        if not self._cmake:
            self.create_cmake_wrapper()
            self._cmake = CMake(self)

            self._cmake.definitions["CMAKE_DEBUG_POSTFIX"] = "d"

            self._cmake.definitions["BLOSC_INSTALL"] = True

            self._cmake.definitions["BUILD_STATIC"] = False
            self._cmake.definitions["BUILD_SHARED"] = True
            self._cmake.definitions["BUILD_TESTS"] = False
            self._cmake.definitions["BUILD_FUZZERS"] = False
            self._cmake.definitions["BUILD_BENCHMARKS"] = False

            self._cmake.definitions["PREFER_EXTERNAL_LZ4"] = True
            self._cmake.definitions["PREFER_EXTERNAL_ZLIB"] = True
            self._cmake.definitions["PREFER_EXTERNAL_ZSTD"] = True

            self._cmake.definitions["DEACTIVATE_LZ4"] = False
            self._cmake.definitions["DEACTIVATE_SNAPPY"] = True
            self._cmake.definitions["DEACTIVATE_ZLIB"] = False
            self._cmake.definitions["DEACTIVATE_ZSTD"] = False

            self._cmake.configure()
        return self._cmake

    def build(self):
        cmake = self._configure_cmake()
        cmake.build()

    def package(self):
        cmake = self._configure_cmake()
        cmake.install()

        self.copy("*.pdb", src="bin", dst="bin")

        tools.rmdir(os.path.join(self.package_folder, "lib", "pkgconfig"))

        self.patch_binaries()
        self.default_package()

    def package_info(self):
        self.default_package_info()
        self.cpp_info.names["pkg_config"] = "blosc"

        if self.settings.os == "Linux":
            self.cpp_info.system_libs.extend(["pthread"])
