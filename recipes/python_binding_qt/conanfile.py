# -*- coding: utf-8 -*-
from conans import ConanFile
from conans import CMake
from conans import tools
from conans.errors import ConanException
import os


class ConanRecipe(ConanFile):
    python_requires = 'common/1.0.0@mevislab/stable'
    python_requires_extend = 'common.CommonRecipe'

    _cmake = None

    def requirements(self):
        channel = "@mevislab/stable"
        self.requires("qt5/[>=5.12.7]" + channel)
        self.requires("python/[>=3.9.7]" + channel)
        self.requires("pythonqt/[>=3.4.1]" + channel)

        if "arm" not in self.settings.arch:
            self.requires("qtwebkit/[>=5.212.0-alpha4]" + channel)


    def _configure_cmake(self):
        if not self._cmake:
            self._cmake = CMake(self)

            python_package = self.deps_cpp_info['python']
            version = python_package.version.split('.')
            major, minor = version[0], version[1]

            self._cmake.definitions["CMAKE_DEBUG_POSTFIX"] = "_d"
            self._cmake.definitions["BUILD_SHARED_LIBS"] = True
            self._cmake.definitions["python_VERSION_MAJOR"] = major
            self._cmake.definitions["python_VERSION_MINOR"] = minor
            self._cmake.definitions["MEVIS_PYTHON_SITE_PACKAGES_FOLDER"] = os.environ['MEVIS_PYTHON_SITE_PACKAGES_FOLDER']

            if "arm" in self.settings.arch:
                self._cmake.definitions["BUILD_WEBKIT_BINDING"] =  False

            self._cmake.configure(source_folder="sources")
        return self._cmake


    def build(self):
        cmake = self._configure_cmake()
        cmake.build()


    def package(self):
        cmake = self._configure_cmake()
        cmake.install()
        self.default_package()
