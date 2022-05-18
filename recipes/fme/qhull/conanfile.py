# -*- coding: utf-8 -*-
from conans import ConanFile
from conans import CMake
from conans import tools
from pathlib import Path
import glob
import os

class ConanRecipe(ConanFile):
    python_requires = 'common/1.0.0@mevislab/stable'
    python_requires_extend = 'common.CommonRecipe'


    def source(self):
        self.default_source()

        # we say we don't want static libs, but we need static qhullcpp (but only that)
        tools.replace_in_file(os.path.join('sources', 'CMakeLists.txt'),
            'set_target_properties(${qhull_CPP} PROPERTIES EXCLUDE_FROM_ALL TRUE)',
            '')
        tools.replace_in_file(os.path.join('sources', 'CMakeLists.txt'),
            'list(APPEND qhull_TARGETS_INSTALL ${qhull_TARGETS_SHARED})',
            'list(APPEND qhull_TARGETS_INSTALL ${qhull_TARGETS_SHARED} ${qhull_CPP})')

    _cmake = None

    def _configure_cmake(self):
        if not self._cmake:
            self.create_cmake_wrapper()
            self._cmake = CMake(self)
            # qhull add's d postfix itself, no need for CMAKE_DEBUG_POSTFIX
            #self._cmake.definitions["CMAKE_DEBUG_POSTFIX"] = "d"
            self._cmake.definitions["BUILD_STATIC_LIBS"] = False
            self._cmake.definitions["BUILD_SHARED_LIBS"] = True
            self._cmake.configure()

        return self._cmake


    def build(self):
        cmake = self._configure_cmake()
        cmake.build()


    def package(self):
        cmake = self._configure_cmake()
        cmake.install()

        for dll in glob.glob(self.package_folder + "/bin/*.dll"):
            self.copy(Path(dll).stem + ".pdb", src="bin", dst="bin")

        tools.rmdir(os.path.join(self.package_folder, "lib", "cmake"))
        tools.rmdir(os.path.join(self.package_folder, "lib", "pkgconfig"))
        tools.rmdir(os.path.join(self.package_folder, "share"))

        self.patch_binaries()
        self.default_package()


    def package_info(self):
        self.default_package_info()

        if self.settings.os == "Linux":
            self.cpp_info.system_libs = ["m"]

        if self.settings.compiler == "Visual Studio":
            self.cpp_info.defines.extend(["qh_dllimport"])
