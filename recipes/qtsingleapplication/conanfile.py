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

        if packages:
            installer.install_packages(packages)


    def requirements(self):
        channel = "@mevislab/stable"
        self.requires("qt5/[>=5.12.7]" + channel)


    def _configure_cmake(self):
        if not self._cmake:
            self._cmake = CMake(self)
            self._cmake.definitions["CMAKE_DEBUG_POSTFIX"] = "d"
            self._cmake.definitions["BUILD_SHARED_LIBS"] = True
            self._cmake.definitions["CMAKE_POSITION_INDEPENDENT_CODE"] = True
            self._cmake.definitions["WITH_WIDGETS"] = True #self.options.widgets
            self._cmake.configure()
        return self._cmake


    def build(self):
        tools.replace_in_file("sources/src/qtlocalpeer.h", "class QtLocalPeer : public QObject", "class QT_QTLOCKEDFILE_EXPORT QtLocalPeer : public QObject")
        cmake = self._configure_cmake()
        cmake.build()


    def package(self):
        cmake = self._configure_cmake()
        cmake.install()

        self.copy("*.pdb", src="lib", dst="bin")

        self.default_package()


    def package_info(self):
        super().package_info()
        self.cpp_info.includedirs = ["include", "include/QtSolutions"]
