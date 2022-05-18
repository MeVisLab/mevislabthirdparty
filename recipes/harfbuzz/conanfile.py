# -*- coding: utf-8 -*-
from conans import ConanFile
from conans import tools
from conans import CMake
import os


class ConanRecipe(ConanFile):
    python_requires = 'common/1.0.0@mevislab/stable'
    python_requires_extend = 'common.CommonRecipe'

    _cmake = None


    def _configure_cmake(self):
        if not self._cmake:
            self._cmake = CMake(self)
            self._cmake.definitions["BUILD_SHARED_LIBS"] = True
            self._cmake.configure()
        return self._cmake


    def build(self):
        # allow in-source builds
        tools.replace_in_file(os.path.join("sources", "CMakeLists.txt"), 'if (NOT MSVC AND "${PROJECT_BINARY_DIR}"', 'if (FALSE AND NOT MSVC AND "${PROJECT_BINARY_DIR}"')

        cmake = self._configure_cmake()
        cmake.build()


    def package(self):
        cmake = self._configure_cmake()
        cmake.install()

        tools.rmdir(os.path.join(self.package_folder, "lib", "cmake"))

        self.copy("*.pdb", src="bin", dst="bin")

        # some projects also include this file:
        self.copy('hb-ft.h', dst=os.path.join('include', 'harfbuzz'), src=os.path.join('sources', 'src'), keep_path=False)

        self.patch_binaries()
        self.default_package()
