# -*- coding: utf-8 -*-
from conans import ConanFile
from conans import CMake
from conans import tools
import glob
import os


class ConanRecipe(ConanFile):
    python_requires = 'common/1.0.0@mevislab/stable'
    python_requires_extend = 'common.CommonRecipe'
    generators = "cmake", "cmake_find_package"

    _cmake = None


    def requirements(self):
        channel = f"@{self.user}/{self.channel}"
        self.requires("boost/[>=1.75.0]" + channel)
        self.requires("eigen/[>=3.3.9]" + channel)
        self.requires("flann/[>=1.9.1]" + channel)
        self.requires("glew/[>=2.0.0]" + channel)
        self.requires("libpng/[>=1.6.37]" + channel)
        self.requires("qhull/[>=8.0.2]" + channel)
        #self.requires("vtk/[>=7.1.1]" + channel)
        self.requires("zlib/[>=1.2.11]" + channel)


    def _configure_cmake(self):
        if not self._cmake:
            self._cmake = CMake(self)
            self._cmake.definitions["CMAKE_DEBUG_POSTFIX"] = "d"
            self._cmake.definitions["PCL_SHARED_LIBS"] = True

            self._cmake.definitions["BUILD_tools"] = False
            self._cmake.definitions["BUILD_CUDA"] = False

            self._cmake.definitions["CMAKE_CXX_STANDARD"] = 17
            self._cmake.definitions["PCL_ENABLE_MARCHNATIVE"] = False

            self._cmake.definitions["PCL_DISABLE_GPU_TESTS"] = False
            self._cmake.definitions["PCL_DISABLE_VISUALIZATION_TESTS"] = False
            self._cmake.definitions["PCL_BUILD_WITH_BOOST_DYNAMIC_LINKING_WIN32"] = True

            self._cmake.definitions["WITH_DOCS"] = False
            self._cmake.definitions["WITH_TUTORIALS"] = False

            self._cmake.definitions["WITH_OPENMP"] = False
            self._cmake.definitions["WITH_LIBUSB"] = False
            self._cmake.definitions["WITH_PNG"] = True
            self._cmake.definitions["WITH_QHULL"] = True
            self._cmake.definitions["WITH_CUDA"] = False
            self._cmake.definitions["WITH_VTK"] = True
            self._cmake.definitions["WITH_QT"] = False
            self._cmake.definitions["WITH_PCAP"] = False
            self._cmake.definitions["WITH_OPENGL"] = True

            self._cmake.definitions["CMAKE_DISABLE_FIND_PACKAGE_VTK"] = True if 'vtk' not in self.deps_cpp_info.deps else False

            self._cmake.configure()

        return self._cmake


    def build(self):
        cmake = self._configure_cmake()
        cmake.build()


    def package(self):
        cmake = self._configure_cmake()
        cmake.install()

        tools.rmdir(os.path.join(self.package_folder, "cmake"))
        tools.rmdir(os.path.join(self.package_folder, "share"))
        tools.rmdir(os.path.join(self.package_folder, "lib", "pkgconfig"))

        # Remove MS runtime files
        for pattern in ["concrt*.dll", "msvcp*.dll", "vcruntime*.dll"]:
            for lib in glob.glob(os.path.join(self.package_folder, "bin", pattern)):
                os.remove(lib)

        self.patch_binaries()
        self.default_package()


    def package_info(self):
        self.default_package_info()

        v = tools.Version(self.version)
        self.cpp_info.includedirs = ['include', f'include/pcl-{v.major}.{v.minor}']
