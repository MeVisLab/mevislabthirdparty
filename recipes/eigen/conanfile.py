# -*- coding: utf-8 -*-
from conans import ConanFile
from conans import tools
from conans import CMake
from glob import glob
import shutil
import os


class ConanRecipe(ConanFile):
    python_requires = 'common/1.0.0@mevislab/stable'
    python_requires_extend = 'common.CommonRecipe'

    _cmake = None


    def _configure_cmake(self):
        if not self._cmake:
            self._cmake = CMake(self)
            self._cmake.definitions["BUILD_TESTING"] = False
            self._cmake.definitions["EIGEN_BUILD_PKGCONFIG"] = False
            self._cmake.configure(build_folder=os.path.join(self.build_folder, "build"))

        return self._cmake


    def build(self):
        cmake = self._configure_cmake()
        cmake.build()


    def package(self):
        cmake = self._configure_cmake()
        cmake.install()
        cmake.patch_config_paths()

        self.copy("COPYING.*", src="sources", dst="licenses", keep_path=False, ignore_case=True)
        shutil.copy(os.path.join(self.package_folder, "licenses", "COPYING.README"), os.path.join(self.package_folder, "licenses", "LICENSE"))
        shutil.rmtree(os.path.join(self.package_folder, "share"))

        self.default_package()


    def package_info(self):
        self.cpp_info.names["cmake"] = "Eigen3"
        self.cpp_info.names["cmake_multi"] = "Eigen3"
        self.cpp_info.names["cmake_find_package"] = "Eigen3"
        self.cpp_info.names["cmake_find_package_multi"] = "Eigen3"
        self.cpp_info.names["cmake_paths"] = "Eigen3"

        self.cpp_info.components['Eigen'].libs = tools.collect_libs(self)
        self.cpp_info.components['Eigen'].includedirs = ['include', 'include/eigen3']
        self.cpp_info.components['Eigen'].defines = ['EIGEN_MALLOC_ALREADY_ALIGNED=0']
        self.cpp_info.components['Eigen'].defines = ['EIGEN_MAX_ALIGN_BYTES=32']
