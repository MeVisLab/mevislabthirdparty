# -*- coding: utf-8 -*-
from conans import ConanFile
from conans import CMake
from conans import tools
import glob
import os


class ConanRecipe(ConanFile):
    python_requires = 'common/1.0.0@mevislab/stable'
    python_requires_extend = 'common.CommonRecipe'

    _cmake = None


    def system_requirements(self):
        installer = tools.SystemPackageTool()
        packages = []

        if tools.os_info.linux_distro in ["ubuntu", "debian"]:
            packages.append('libxi-dev')
            packages.append('libxcursor-dev')
            packages.append('libxrandr-dev')
            packages.append('libxinerama-dev')

        if packages:
            installer.install_packages(packages)


    def _configure_cmake(self):
        if not self._cmake:
            self.create_cmake_wrapper()
            self._cmake = CMake(self)
            self._cmake.definitions["BUILD_SHARED_LIBS"] = True
            self._cmake.definitions["GLFW_BUILD_EXAMPLES"] = False
            self._cmake.definitions["GLFW_BUILD_TESTS"] = False
            self._cmake.definitions["GLFW_BUILD_DOCS"] = False
            self._cmake.configure()
        return self._cmake


    def build(self):
        cmake = self._configure_cmake()
        cmake.build()

        if self.settings.os == "Macos":
            with tools.chdir(os.path.join('sources', 'src')):
                for filename in glob.glob('*.dylib'):
                    self.run('install_name_tool -id {filename} {filename}'.format(filename=filename))


    def package(self):
        cmake = self._configure_cmake()
        cmake.install()

        self.copy("*.pdb", src="bin", dst="bin")

        tools.rmdir(os.path.join(self.package_folder, "lib", "cmake"))
        tools.rmdir(os.path.join(self.package_folder, "lib", "pkgconfig"))

        self.patch_binaries()
        self.default_package()


    def package_info(self):
        self.default_package_info()

        self.cpp_info.libs = tools.collect_libs(self)
        if self.settings.os == "Linux":
            self.cpp_info.system_libs.extend(['m', 'dl', 'pthread'])
            self.cpp_info.exelinkflags.append("-lrt -lm -ldl")
        elif self.settings.os == "Macos":
            self.cpp_info.frameworks.extend(["Cocoa", "IOKit", "CoreVideo"])
