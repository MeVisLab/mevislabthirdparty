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

        self.requires("zlib/[>=1.2.11]" + channel)
        self.requires("libpng/[>=1.6.37]" + channel)
        self.requires("tiff/[>=4.1.0]" + channel)
        self.requires("dcmtk/[>=3.6.5]" + channel)
        self.requires("libjpeg/9e" + channel)

        if self.version.split('.')[0] != "4":
            self.requires("hdf5/1.14.1-2" + channel)
            self.requires("double-conversion/[>=3.1.5]" + channel)


    def _configure_cmake(self):
        if not self._cmake:
            self._cmake = CMake(self)
            self._cmake.definitions["CMAKE_DEBUG_POSTFIX"] = "d"
            self._cmake.definitions["BUILD_SHARED_LIBS"] = True
            self._cmake.definitions["BUILD_EXAMPLES"] = False
            self._cmake.definitions["BUILD_TESTING"] = False

            self._cmake.definitions["ITK_WRAPPING"] = False
            self._cmake.definitions["ITK_WRAP_PYTHON"] = False
            self._cmake.definitions["ITK_BUILD_DEFAULT_MODULES"] = True

            self._cmake.definitions["ITKV3_COMPATIBILITY"] = True    # required by Elastix 4.7.0
            self._cmake.definitions["Module_ITKReview"] = True       # required by Elastix 4.7.0
            self._cmake.definitions["Module_ITKDeprecated"] = True   # required by Elastix 4.7.0


            self._cmake.definitions["ITK_USE_GPU"] = False  # requires OpenCL on all plattforms

            self._cmake.definitions["ITK_USE_SYSTEM_ZLIB"] = True
            self._cmake.definitions["ITK_USE_SYSTEM_DOUBLECONVERSION"] = self.version.split('.')[0] != "4" # FIXME
            self._cmake.definitions["ITK_USE_SYSTEM_HDF5"] = self.version.split('.')[0] != "4" # FIXME
            self._cmake.definitions["ITK_USE_SYSTEM_DCMTK"] = True
            self._cmake.definitions["ITK_USE_SYSTEM_JPEG"] = True
            self._cmake.definitions["ITK_USE_SYSTEM_PNG"] = True
            self._cmake.definitions["ITK_USE_SYSTEM_TIFF"] = True

            self._cmake.configure(build_folder='build')
        return self._cmake


    def build(self):
        cmake = self._configure_cmake()
        cmake.build()


    def package(self):
        cmake = self._configure_cmake()
        cmake.install()

        self.copy("*.pdb", src="build/bin", dst="bin")

        if not tools.os_info.is_windows:
            tools.rmdir(os.path.join(self.package_folder, 'bin'))
        tools.rmdir(os.path.join(self.package_folder, 'share'))
        tools.rmdir(os.path.join(self.package_folder, 'lib', 'cmake'))

        self.patch_binaries()
        self.default_package()


    def package_info(self):
        self.default_package_info()
        major, minor, patch = self.version.split('.')
        self.cpp_info.includedirs = ['include', f"include/ITK-{major}.{minor}"]
