# -*- coding: utf-8 -*-
from conans import ConanFile
from conans.errors import ConanInvalidConfiguration
from conans import tools
from conans import CMake
import os


class ConanRecipe(ConanFile):
    python_requires = 'common/1.0.0@mevislab/stable'
    python_requires_extend = 'common.CommonRecipe'

    _cmake = None


    def package_id(self):
        del self.info.settings.build_type


    def validate(self):
        if self.settings.os not in ["Linux", "Macos"]:
            raise ConanInvalidConfiguration(f"{self.name} is only supported on Linux and macOS")


    def validate_build(self):
        if self.settings.build_type != "Release":
            raise ConanInvalidConfiguration(f"{self.name} is built in release mode only.")


    def _configure_cmake(self):
        if not self._cmake:
            self.create_cmake_wrapper()
            self._cmake = CMake(self)

            self._cmake.definitions["OPENMP_STANDALONE_BUILD"] = True
            self._cmake.definitions["LIBOMP_ENABLE_SHARED"] = True
            self._cmake.definitions["LIBOMP_INSTALL_ALIASES"] = False

            if self.settings.os == "Linux":
                self._cmake.definitions["OPENMP_ENABLE_LIBOMPTARGET"] = True

            self._cmake.configure()

        return self._cmake


    def build(self):
        cmake = self._configure_cmake()
        cmake.build()


    def package(self):
        cmake = self._configure_cmake()
        cmake.install()

        self.patch_binaries()
        self.default_package()


    def package_info(self):
        self.cpp_info.name = "OpenMP"

        self.cpp_info.components["OpenMP_C"].libs =tools.collect_libs(self)
        self.cpp_info.components["OpenMP_CXX"].libs =tools.collect_libs(self)

        if self.settings.compiler == "clang" or self.settings.compiler == "apple-clang":
            self.cpp_info.components["OpenMP_C"].cxxflags = ["-Xpreprocessor", "-fopenmp"]
            self.cpp_info.components["OpenMP_CXX"].cxxflags = ["-Xpreprocessor", "-fopenmp"]

        elif self.settings.compiler == 'gcc':
            self.cpp_info.components["OpenMP_C"].cxxflags = ["-fopenmp"]
            self.cpp_info.components["OpenMP_CXX"].cxxflags = ["-fopenmp"]

        if self.settings.os == "Linux":
            self.cpp_info.components["OpenMP_C"].system_libs = ["dl", "m", "pthread"]
            self.cpp_info.components["OpenMP_CXX"].system_libs = ["dl", "m", "pthread"]
