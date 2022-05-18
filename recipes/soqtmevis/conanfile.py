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

    def system_requirements(self):
        installer = tools.SystemPackageTool()
        packages = []

        if tools.os_info.linux_distro in ["ubuntu", "debian"]:
            packages.append('libglu1-mesa-dev')
            packages.append('libfreetype6-dev')
            packages.append('libfontconfig-dev')

        if packages:
            installer.install_packages(packages)

    def requirements(self):
        channel = "@mevislab/stable"
        self.requires("glew/[>=2.0.0]" + channel)
        self.requires('openinventor/[>=2.5.1]' + channel)
        self.requires("qt5/[>=5.12.7]" + channel)


    def _configure_cmake(self):
        if not self._cmake:
            self._cmake = CMake(self)

            self._cmake.definitions["CMAKE_DEBUG_POSTFIX"] = "d"
            self._cmake.definitions["BUILD_SHARED_LIBS"] = True
            self._cmake.configure(source_folder="sources")
        return self._cmake


    def build(self):
        cmake = self._configure_cmake()
        cmake.build()


    def package(self):
        cmake = self._configure_cmake()
        cmake.install()
        self.patch_binaries()
        self.default_package()
