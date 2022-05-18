# -*- coding: utf-8 -*-
from conans import ConanFile
from conans import CMake
import shutil
import os


class ConanRecipe(ConanFile):
    python_requires = 'common/1.0.0@mevislab/stable'
    python_requires_extend = 'common.CommonRecipe'

    _cmake = None

    def source(self):
        self.default_source()
        shutil.copy(os.path.join("sources", "COPYING-CMAKE-SCRIPTS"), os.path.join("sources", "LICENSE"))


    def _configure_cmake(self):
        if not self._cmake:
            self._cmake = CMake(self)
            self._cmake.definitions['BUILD_HTML_DOCS'] = False
            self._cmake.definitions['BUILD_QTHELP_DOCS'] = False
            self._cmake.definitions['CMAKE_DISABLE_FIND_PACKAGE_Sphinx'] = True
            self._cmake.definitions['CMAKE_DISABLE_FIND_PACKAGE_QCollectionGenerator'] = True
            self._cmake.definitions['CMAKE_DISABLE_FIND_PACKAGE_Qt5LinguistTools'] = True
            self._cmake.definitions['CMAKE_DISABLE_FIND_PACKAGE_Qt5Core'] = True
            self._cmake.definitions['CMAKE_DISABLE_FIND_PACKAGE_Qt5Gui'] = True
            self._cmake.definitions['CMAKE_DISABLE_FIND_PACKAGE_Qt5Qml'] = True
            self._cmake.definitions['CMAKE_DISABLE_FIND_PACKAGE_Qt5Quick'] = True
            self._cmake.definitions['CMAKE_DISABLE_FIND_PACKAGE_Qt5Network'] = True
            self._cmake.configure(args=["--no-warn-unused-cli"], source_dir="sources")
        return self._cmake


    def build(self):
        cmake = self._configure_cmake()
        cmake.build()


    def package(self):
        self.default_package()
        cmake = self._configure_cmake()
        cmake.install()


    def package_info(self):
        self.env_info.CMAKE_PREFIX_PATH.append(self.package_folder)
