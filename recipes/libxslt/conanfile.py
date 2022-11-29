# -*- coding: utf-8 -*-
from conans import ConanFile
from conans import CMake
from conans import tools
import os


class ConanRecipe(ConanFile):
    python_requires = 'common/1.0.0@mevislab/stable'
    python_requires_extend = 'common.CommonRecipe'
    generators = "cmake", "cmake_find_package"

    _cmake = None

    def requirements(self):
        channel = "@{0}/{1}".format(self.user, self.channel)
        self.requires("libxml2/[>=2.9.0]" + channel)


    def _configure_cmake(self):
        if not self._cmake:
            self.create_cmake_wrapper()
            self._cmake = CMake(self)

            self._cmake.definitions["CMAKE_DEBUG_POSTFIX"] = "d"
            self._cmake.definitions["BUILD_SHARED_LIBS"] = True

            self._cmake.definitions["LIBXSLT_WITH_TESTS"] = False
            self._cmake.definitions["LIBXSLT_WITH_PYTHON"] = False

            self._cmake.configure()
        return self._cmake


    def build(self):
        cmake = self._configure_cmake()
        cmake.build()


    def package(self):
        cmake = self._configure_cmake()
        cmake.install()

        tools.rmdir(os.path.join(self.package_folder, "lib", "cmake"))
        tools.rmdir(os.path.join(self.package_folder, "lib", "pkgconfig"))
        tools.rmdir(os.path.join(self.package_folder, "share"))

        self.patch_binaries(executables=['xsltproc'])
        self.default_package()


    def package_info(self):
        self.default_package_info()

        self.cpp_info.includedirs.append(os.path.join("include", "libxslt"))

        if tools.os_info.is_windows:
            self.cpp_info.system_libs.append('ws2_32')
        else:
            self.cpp_info.system_libs.append('m')
