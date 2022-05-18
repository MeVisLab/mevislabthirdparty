# -*- coding: utf-8 -*-
from conans import ConanFile
from conans import CMake
from conans import tools
import shutil
import os


class ConanRecipe(ConanFile):
    python_requires = 'common/1.0.0@mevislab/stable'
    python_requires_extend = 'common.CommonRecipe'

    _cmake = None


    def _configure_cmake(self):
        if not self._cmake:
            self.create_cmake_wrapper(add_subdirectory='sources/expat')
            self._cmake = CMake(self)
            self._cmake.definitions["CMAKE_DEBUG_POSTFIX"] = "d"
            self._cmake.definitions['EXPAT_BUILD_DOCS'] = False
            self._cmake.definitions['EXPAT_BUILD_EXAMPLES'] = False
            self._cmake.definitions['EXPAT_BUILD_TESTS'] = False
            self._cmake.definitions['EXPAT_BUILD_TOOLS'] = False
            self._cmake.definitions['EXPAT_BUILD_PKGCONFIG'] = False
            self._cmake.definitions['EXPAT_SHARED_LIBS'] = True
            self._cmake.configure()

        return self._cmake


    def build(self):
        cmake = self._configure_cmake()
        cmake.build()
        shutil.move(os.path.join("sources", "expat", "COPYING"), os.path.join(".", "LICENSE"))


    def package(self):
        cmake = self._configure_cmake()
        cmake.install()

        self.copy("*.pdb", src="bin", dst="bin")

        tools.rmdir(os.path.join(self.package_folder, "lib", "cmake"))
        tools.rmdir(os.path.join(self.package_folder, "lib", "pkgconfig"))
        tools.rmdir(os.path.join(self.package_folder, "share"))

        self.patch_binaries()
        self.default_package()
