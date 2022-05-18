# -*- coding: utf-8 -*-
from conans import ConanFile
from conans import CMake

class ConanRecipe(ConanFile):
    python_requires = 'common/1.0.0@mevislab/stable'
    python_requires_extend = 'common.CommonRecipe'


    def build(self):
        self.create_cmake_wrapper()
        cmake = CMake(self)
        cmake.definitions["CMAKE_DEBUG_POSTFIX"] = "d"
        cmake.definitions["BUILD_SHARED_LIBS"] = False
        cmake.definitions["SKIP_INSTALL_FILES"] = True
        cmake.definitions['CMAKE_POSITION_INDEPENDENT_CODE'] = True
        cmake.definitions['CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS'] = True
        cmake.definitions["CMAKE_C_VISIBILITY_PRESET"] = 'default'
        cmake.definitions["CMAKE_CXX_VISIBILITY_PRESET"] = 'default'
        cmake.definitions["CMAKE_VISIBILITY_INLINES_HIDDEN"] = False
        cmake.configure()
        cmake.build(target='zlibstatic')


    def package(self):
        self.default_package()
        self.copy("zconf.h", dst="include", src="sources", keep_path=False)
        self.copy("zlib.h", dst="include", src="sources", keep_path=False)
        self.copy("*.lib", dst="lib", keep_path=False)
        self.copy("*.pdb", dst="bin", keep_path=False)
        self.copy("*.a", dst="lib", keep_path=False)
