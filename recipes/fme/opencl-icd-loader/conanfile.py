# -*- coding: utf-8 -*-
from conans import ConanFile
from conans import CMake
from conans import tools
import os

class ConanRecipe(ConanFile):
    python_requires = 'common/1.0.0@mevislab/stable'
    python_requires_extend = 'common.CommonRecipe'

    _cmake = None

    def requirements(self):
        channel = f"@{self.user}/{self.channel}"
        self.requires("opencl-headers/[>=2021.06.30]" + channel)


    def _configure_cmake(self):
        if not self._cmake:
            self.create_cmake_wrapper()
            self._cmake = CMake(self)
            self._cmake.definitions["CMAKE_DEBUG_POSTFIX"] = "d"
            self._cmake.definitions["BUILD_SHARED_LIBS"] = True
            self._cmake.definitions["OPENCL_ICD_LOADER_HEADERS_DIR"] = ";".join(self.deps_cpp_info["opencl-headers"].include_paths)
            self._cmake.configure()
        return self._cmake


    def build(self):
        cmake = self._configure_cmake()
        cmake.build()


    def package(self):
        cmake = self._configure_cmake()
        cmake.install()

        tools.rmdir(os.path.join(self.package_folder, "share"))

        self.copy("*.pdb", src="bin", dst="bin")

        self.patch_binaries()
        self.default_package()
