# -*- coding: utf-8 -*-
from conans import ConanFile
from conans import CMake
from conans import tools
import os

class ConanRecipe(ConanFile):
    python_requires = 'common/1.0.0@mevislab/stable'
    python_requires_extend = 'common.CommonRecipe'

    _cmake = None


    def build_requirements(self):
        channel = "@{0}/{1}".format(self.user, self.channel)
        self.build_requires("zlib/[>=1.2.11]" + channel)


    def _configure_cmake(self):
        if not self._cmake:
            self.create_cmake_wrapper()
            self._cmake = CMake(self)
            self._cmake.definitions["CMAKE_DEBUG_POSTFIX"] = "d"
            self._cmake.definitions["BUILD_SHARED_LIBS"] = True
            self._cmake.definitions["ASSIMP_DOUBLE_PRECISION"] = False
            self._cmake.definitions["ASSIMP_BUILD_ASSIMP_TOOLS"] = False
            self._cmake.definitions["ASSIMP_BUILD_TESTS"] = False
            self._cmake.definitions["ASSIMP_INSTALL_PDB"] = False
            self._cmake.definitions["ASSIMP_IGNORE_GIT_HASH"] = True
            self._cmake.definitions["ASSIMP_BUILD_ZLIB"] = False
            self._cmake.definitions["ZLIB_INC_SEARCH_PATH"] = self.deps_cpp_info['zlib'].include_paths
            self._cmake.definitions["ZLIB_LIB_SEARCH_PATH"] = self.deps_cpp_info['zlib'].lib_paths

            self._cmake.configure()
        return self._cmake


    def build(self):
        cmake = self._configure_cmake()
        cmake.build()


    def package(self):
        cmake = cmake = self._configure_cmake()
        cmake.install()

        self.copy("*.pdb", src="bin", dst="bin")

        tools.rmdir(os.path.join(self.package_folder, "lib", "cmake"))
        tools.rmdir(os.path.join(self.package_folder, "lib", "pkgconfig"))

        self.patch_binaries()
        self.default_package()
