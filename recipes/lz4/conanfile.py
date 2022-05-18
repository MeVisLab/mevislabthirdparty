# -*- coding: utf-8 -*-
from conans import ConanFile
from conans import CMake


class ConanRecipe(ConanFile):
    python_requires = 'common/1.0.0@mevislab/stable'
    python_requires_extend = 'common.CommonRecipe'


    def build(self):
        cmake = CMake(self)
        cmake.definitions["CMAKE_DEBUG_POSTFIX"] = "d"
        cmake.configure()
        cmake.build()


    def package(self):
        self.copy("lz4.h", dst="include", src="sources/lib")
        self.copy("lz4frame.h", dst="include", src="sources/lib")
        self.copy("lz4frame_static.h", dst="include", src="sources/lib")
        self.copy("lz4hc.h", dst="include", src="sources/lib")

        self.copy("*.lib", dst="lib", keep_path=False)
        self.copy("*.dll", dst="bin", keep_path=False)
        self.copy("*.pdb", src="lib", dst="bin")

        self.copy("*.so*", dst="lib", keep_path=False)
        self.copy("*.dylib*", dst="lib", keep_path=False)
        self.copy("*.a*", dst="lib", keep_path=False)

        self.default_package()
