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
            packages.append('bison')

        if packages:
            installer.install_packages(packages)


    def build_requirements(self):
        channel = "@{0}/{1}".format(self.user, self.channel)
        if self.settings.os == 'Windows':
            self.build_requires("winflexbison_installer/[>=2.5.18]" + channel)


    def requirements(self):
        channel = "@{0}/{1}".format(self.user, self.channel)
        self.requires("glew/[>=2.0.0]" + channel)
        self.requires("libjpeg/9e" + channel)

        if tools.os_info.is_windows:
            self.requires("libiconv/[>=1.16]" + channel)

        if not tools.os_info.is_linux:
            self.requires("freetype/[>=2.10.4]" + channel)


    def _configure_cmake(self):
        if not self._cmake:
            self._cmake = CMake(self)
            self._cmake.definitions["CMAKE_DEBUG_POSTFIX"] = "d"
            self._cmake.definitions["BUILD_SHARED_LIBS"] = True
            self._cmake.configure(source_folder="sources")
        return self._cmake


    def build(self):
        # fix link name in header file
        tools.replace_in_file(os.path.join(self.build_folder, 'sources', 'include', 'Inventor', 'system', 'SbSystem.h'), '"Inventor_d.', '"Inventord.')
        cmake = self._configure_cmake()
        cmake.build()


    def package(self):
        cmake = self._configure_cmake()
        cmake.install()
        self.patch_binaries()
        self.default_package()


    def package_info(self):
        self.default_package_info()
        self.cpp_info.defines.append("SGIOIV")
        self.cpp_info.defines.append("IV_STRICT")
