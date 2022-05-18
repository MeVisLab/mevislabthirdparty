# -*- coding: utf-8 -*-
from conans import ConanFile
from conans import tools
from conans import CMake


class ConanRecipe(ConanFile):
    python_requires = 'common/1.0.0@mevislab/stable'
    python_requires_extend = 'common.CommonRecipe'

    _cmake = None


    def _configure_cmake(self):
        if not self._cmake:
            self.create_cmake_wrapper()
            self._cmake = CMake(self)
            if self.settings.compiler == "Visual Studio" and "MD" in str(self.settings.compiler.runtime):
                self._cmake.definitions["gtest_force_shared_crt"] = "ON"
            self._cmake.definitions["BUILD_SHARED_LIBS"] = True
            self._cmake.definitions["CMAKE_POSITION_INDEPENDENT_CODE"] = True
            self._cmake.configure()
        return self._cmake


    def build(self):
        cmake = self._configure_cmake()
        cmake.build()


    def package(self):
        self.copy("*", dst="include", src="sources/googletest/include", keep_path=True)
        self.copy("*", dst="include", src="sources/googlemock/include", keep_path=True)

        self.copy("*.lib", dst="lib", keep_path=False)
        self.copy("*.dll", dst="bin", keep_path=False)
        self.copy("*.so*", dst="lib", keep_path=False, symlinks=True)
        self.copy("*.dylib", dst="lib", keep_path=False)
        self.copy("*.a", dst="lib", keep_path=False)

        self.copy("*.pdb", src="bin/Debug", dst="bin")

        self.patch_binaries()
        self.default_package()


    def package_info(self):
        self.cpp_info.name = "GTest"
        for lib in tools.collect_libs(self):
            comp = lib[:-1] if self.settings.build_type == "Debug" else lib
            if comp.endswith("main"):
                self.cpp_info.components[comp].libs = [lib]
            else:
                self.cpp_info.components[comp + "_lib"].libs = [lib]
