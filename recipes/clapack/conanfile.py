# -*- coding: utf-8 -*-
from conans import ConanFile
from conans import CMake

class ConanRecipe(ConanFile):
    python_requires = 'common/1.0.0@mevislab/stable'
    python_requires_extend = 'common.CommonRecipe'


    def build(self):
        cmake = CMake(self)
        cmake.definitions["CMAKE_DEBUG_POSTFIX"] = "d"
        cmake.definitions["BUILD_SHARED_LIBS"] = False
        cmake.definitions['CMAKE_POSITION_INDEPENDENT_CODE'] = True
        cmake.configure()
        cmake.build()


    def package(self):
        self.copy("*.h", dst="include", src="sources/INCLUDE", keep_path=False)
        self.copy("*.lib", dst="lib", keep_path=False)
        self.copy("*.dll", dst="bin", keep_path=False)
        self.copy("*.so*", dst="lib", keep_path=False, symlinks=True)
        self.copy("*.dylib", dst="lib", keep_path=False)
        self.copy("*.a", dst="lib", keep_path=False)

        self.copy("*.pdb", src="lib", dst="bin")

        self.default_package()


    def package_info(self):
        super().package_info()

        self.cpp_info.libs = ['lapack', 'blas']
        self.cpp_info.libs.append('libf2c' if self.settings.os == "Windows" else 'f2c')

        if self.settings.build_type == "Debug":
            self.cpp_info.libs = [x + "d" for x in self.cpp_info.libs]

        if self.settings.os == "Linux":
            self.cpp_info.system_libs.append("m")

