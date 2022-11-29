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
        self.requires("zlib/[>=1.2.11]" + channel)
        self.requires("icu/[>=68.2]" + channel)


    def _configure_cmake(self):
        if not self._cmake:
            self.create_cmake_wrapper()
            self._cmake = CMake(self)

            self._cmake.definitions["CMAKE_DEBUG_POSTFIX"] = "d"
            self._cmake.definitions["BUILD_SHARED_LIBS"] = True

            self._cmake.definitions["LIBXML2_WITH_ICONV"] = False
            self._cmake.definitions["LIBXML2_WITH_ICU"] = True
            self._cmake.definitions["LIBXML2_WITH_LZMA"] = False
            self._cmake.definitions["LIBXML2_WITH_ZLIB"] = True

            self._cmake.definitions["LIBXML2_WITH_PYTHON"] = False
            self._cmake.definitions["LIBXML2_WITH_TESTS"] = False

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

        self.patch_binaries(executables=['xmlcatalog', 'xmllint'])
        self.default_package()


    def package_info(self):
        self.default_package_info()

        self.cpp_info.includedirs.append(os.path.join("include", "libxml2"))

        if tools.os_info.is_macos:
            self.cpp_info.system_libs.append('m')
        elif tools.os_info.is_linux:
            self.cpp_info.system_libs.extend(["m", "pthread"])
        elif tools.os_info.is_windows:
            self.cpp_info.system_libs.extend(["ws2_32", "wsock32"])
