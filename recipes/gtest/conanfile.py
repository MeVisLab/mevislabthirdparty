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
            if self.settings.compiler == "Visual Studio" and "MD" in str(self.settings.compiler.runtime):
                self._cmake.definitions["gtest_force_shared_crt"] = "ON"
            self._cmake.definitions["CMAKE_DEBUG_POSTFIX"] = 'd'
            self._cmake.definitions["BUILD_SHARED_LIBS"] = True
            self._cmake.definitions["CMAKE_POSITION_INDEPENDENT_CODE"] = True
            self._cmake.configure()
        return self._cmake


    def build(self):
        cmake = self._configure_cmake()
        cmake.build()


    def package(self):
        cmake = self._configure_cmake()
        cmake.install()

        tools.rmdir(os.path.join(self.package_folder, "lib", "cmake"))
        tools.rmdir(os.path.join(self.package_folder, "lib", "pkgconfig"))

        self.copy("*.pdb", src="bin/Debug", dst="bin")

        self.patch_binaries()
        self.default_package()


    def package_info(self):
        self.cpp_info.name = "GTest"
        for lib in tools.collect_libs(self):
            if lib.endswith(f".{self.version}"):
                continue

            comp = lib[:-1] if self.settings.build_type == "Debug" else lib
            if comp.endswith("main"):
                #self.output.info(f"creating gtest component {comp} -> {lib}")
                self.cpp_info.components[comp].libs = [lib]
            else:
                #self.output.info(f"creating gtest component {comp}_lib -> {lib}")
                self.cpp_info.components[comp + "_lib"].libs = [lib]
