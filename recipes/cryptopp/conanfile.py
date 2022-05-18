# -*- coding: utf-8 -*-
from conans import ConanFile
from conans import tools
from conans import CMake
import shutil
import os


class ConanRecipe(ConanFile):
    python_requires = 'common/1.0.0@mevislab/stable'
    python_requires_extend = 'common.CommonRecipe'
    exports_sources = ["CMakeLists.txt", "CMakeLists.txt.*"]

    _cmake = None

    def source(self):
        self.default_source()
        shutil.copy('CMakeLists.txt.%s' % self.version, "sources/CMakeLists.txt")
        tools.save("sources/cryptopp-config.cmake", 'include("${CMAKE_CURRENT_LIST_DIR}/cryptopp-targets.cmake")')


    def _configure_cmake(self):
        if not self._cmake:
            self._cmake = CMake(self)
            self._cmake.definitions["CMAKE_DEBUG_POSTFIX"] = "d"
            self._cmake.definitions["CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS"] = True
            self._cmake.definitions["BUILD_STATIC"] = True
            self._cmake.definitions["BUILD_SHARED"] = False
            self._cmake.definitions['CMAKE_POSITION_INDEPENDENT_CODE'] = True
            self._cmake.definitions["BUILD_TESTING"] = False
            self._cmake.definitions["BUILD_DOCUMENTATION"] = False
            self._cmake.configure()
        return self._cmake


    def build(self):
        cmake = self._configure_cmake()
        cmake.build()


    def package(self):
        cmake = self._configure_cmake()
        cmake.install()

        shutil.rmtree(os.path.join(self.package_folder, "lib", "cmake"))

        self.default_package()
