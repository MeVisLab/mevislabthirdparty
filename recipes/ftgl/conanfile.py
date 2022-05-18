# -*- coding: utf-8 -*-
from conans import ConanFile
from conans import CMake
from conans import tools

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

        if packages:
            installer.install_packages(packages)


    def requirements(self):
        channel = "@{0}/{1}".format(self.user, self.channel)

        if not tools.os_info.is_linux:
            self.requires("freetype/[>=2.10.4]" + channel)


    def _configure_cmake(self):
        if not self._cmake:
            self._cmake = CMake(self)
            self._cmake.definitions["CMAKE_DEBUG_POSTFIX"] = "d"
            self._cmake.definitions["BUILD_SHARED_LIBS"] = True
            self._cmake.definitions["CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS"] = True
            self._cmake.configure()
        return self._cmake


    def build(self):
        cmake = self._configure_cmake()
        cmake.build()


    def package(self):
        cmake = self._configure_cmake()
        cmake.install()
        self.copy("*pdb", src="bin", dst="bin")

        self.patch_binaries()
        self.default_package()


    def package_info(self):
        self.default_package_info()
        self.cpp_info.includedirs = ["include", "include/FTGL"]
