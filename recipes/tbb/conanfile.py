# -*- coding: utf-8 -*-
from conans import ConanFile
from conans import tools
from conans import CMake
import os

class ConanRecipe(ConanFile):
    python_requires = 'common/1.0.0@mevislab/stable'
    python_requires_extend = 'common.CommonRecipe'
    generators = "cmake", "cmake_find_package"

    _cmake = None

    def _configure_cmake(self):
        if not self._cmake:
            self._cmake = CMake(self)

            self._cmake.definitions["CMAKE_DEBUG_POSTFIX"] = "debug"
            self._cmake.definitions['TBB_TEST'] = False
            self._cmake.definitions['TBB_EXAMPLES'] = False
            self._cmake.definitions['TBB_STRICT'] = False

            self._cmake.configure(build_folder='build')
        return self._cmake


    def build(self):
        cmake = self._configure_cmake()
        cmake.build()


    def package(self):
        cmake = self._configure_cmake()
        cmake.install()

        tools.rmdir(os.path.join(self.package_folder, "lib", "cmake"))
        tools.rmdir(os.path.join(self.package_folder, "lib", "pkgconfig"))

        self.patch_binaries()
        self.default_package()


    def package_info(self):
        self.cpp_info.names["cmake"] = "TBB"
        self.cpp_info.names["cmake_multi"] = "TBB"
        self.cpp_info.names["cmake_find_package"] = "TBB"
        self.cpp_info.names["cmake_find_package_multi"] = "TBB"
        self.cpp_info.names["cmake_paths"] = "TBB"

        for lib in tools.collect_libs(self):
            self.cpp_info.components["lib" + lib].libs = [lib]
            self.cpp_info.components["lib" + lib].includedirs = ['include']

            lname = lib[:-len('_debug')] if lib.endswith('_debug') else lib

            self.cpp_info.components["lib" + lib].names["cmake"] = lname
            self.cpp_info.components["lib" + lib].names["cmake_multi"] = lname
            self.cpp_info.components["lib" + lib].names["cmake_find_package"] = lname
            self.cpp_info.components["lib" + lib].names["cmake_find_package_multi"] = lname
            self.cpp_info.components["lib" + lib].names["cmake_paths"] = lname

            if self.settings.os == "Linux":
                self.cpp_info.components["lib" + lib].libs.append("pthread")
