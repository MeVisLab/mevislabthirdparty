# -*- coding: utf-8 -*-
from conans import ConanFile
from conans import CMake
from conans import tools
import os

class ConanRecipe(ConanFile):
    python_requires = 'common/1.0.0@mevislab/stable'
    python_requires_extend = 'common.CommonRecipe'
    generators = "cmake", "cmake_find_package", "pkg_config"

    _cmake = None


    def requirements(self):
        channel = f"@{self.user}/{self.channel}"
        self.requires("boost/[>=1.75.0]" + channel)
        self.requires("hdf5/[>=1.12.0]" + channel)
        self.requires("libpng/[>=1.6.37]" + channel)
        self.requires("tiff/[>=4.1.0]" + channel)
        self.requires("zlib/[>=1.2.11]" + channel)

        self.requires("libjpeg/9e" + channel)


    def source(self):
        self.default_source()
        # rather use conan version of this file:
        os.remove("sources/config/FindHDF5.cmake")

    def _configure_cmake(self):
        if not self._cmake:
            self.create_cmake_wrapper()
            self._cmake = CMake(self)
            self._cmake.definitions["CMAKE_DEBUG_POSTFIX"] = "d"
            self._cmake.definitions["BUILD_SHARED_LIBS"] = True
            self._cmake.definitions["CREATE_CTEST_TARGETS"] = False

            self._cmake.definitions["CMAKE_DISABLE_FIND_PACKAGE_FFTW3"] = True
            self._cmake.definitions["CMAKE_DISABLE_FIND_PACKAGE_FFTW3F"] = True
            self._cmake.definitions["CMAKE_DISABLE_FIND_PACKAGE_Doxygen"] = True
            self._cmake.definitions["CMAKE_DISABLE_FIND_PACKAGE_PythonInterp"] = True

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
        tools.rmdir(os.path.join(self.package_folder, "lib", "vigra"))

        self.patch_binaries()
        self.default_package()


    def package_info(self):
        self.default_package_info()
        self.cpp_info.defines += ["HasHDF5"]
