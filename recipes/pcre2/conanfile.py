# -*- coding: utf-8 -*-
from conans import ConanFile
from conans import CMake
from conans import tools
import os


class ConanRecipe(ConanFile):
    python_requires = 'common/1.0.0@mevislab/stable'
    python_requires_extend = 'common.CommonRecipe'

    _cmake = None


    def _configure_cmake(self):
        if not self._cmake:
            self._cmake = CMake(self)

            # fix GCC on Ubuntu (20.04)
            self._cmake.definitions["WITH_MSHSTK"] = tools.os_info.linux_distro == "ubuntu" and self.settings.compiler == "gcc"

            self._cmake.definitions["CMAKE_DEBUG_POSTFIX"] = "d"
            self._cmake.definitions["BUILD_SHARED_LIBS"] = True
            self._cmake.definitions["BUILD_STATIC_LIBS"] = False

            self._cmake.definitions["PCRE2_BUILD_PCRE2_8"] = True
            self._cmake.definitions["PCRE2_BUILD_PCRE2_16"] = True
            self._cmake.definitions["PCRE2_BUILD_PCRE2_32"] = True

            self._cmake.definitions["PCRE2_DEBUG"] = self.settings.build_type == "Debug"

            self._cmake.definitions["PCRE2_SUPPORT_LIBZ"] = False
            self._cmake.definitions["PCRE2_SUPPORT_LIBBZ2"] = False
            self._cmake.definitions["PCRE2_SUPPORT_LIBEDIT"] = False
            self._cmake.definitions["PCRE2_SUPPORT_LIBREADLINE"] = False
            self._cmake.definitions["PCRE2_BUILD_TESTS"] = False
            self._cmake.definitions["PCRE2_BUILD_PCRE2GREP"] = False
            self._cmake.definitions["PCRE2_SUPPORT_JIT"] = True
            self._cmake.definitions["PCRE2_SUPPORT_UNICODE"] = True

            self._cmake.configure()
        return self._cmake


    def build(self):
        cmake = self._configure_cmake()
        cmake.build()


    def package(self):
        cmake = self._configure_cmake()
        cmake.install()

        self.copy("*.pdb", src="bin", dst="bin")

        tools.rmdir(os.path.join(self.package_folder, "man"))
        tools.rmdir(os.path.join(self.package_folder, "cmake"))
        tools.rmdir(os.path.join(self.package_folder, "share"))
        tools.rmdir(os.path.join(self.package_folder, "lib", "pkgconfig"))

        self.patch_binaries()
        self.default_package()
