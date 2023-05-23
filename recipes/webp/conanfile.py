# -*- coding: utf-8 -*-
from conans import ConanFile
from conans import tools
from conans import CMake
import os


class ConanRecipe(ConanFile):
    python_requires = 'common/1.0.0@mevislab/stable'
    python_requires_extend = 'common.CommonRecipe'

    _cmake = None

    def _configure_cmake(self):
        if not self._cmake:
            self.create_cmake_wrapper()
            self._cmake = CMake(self)
            self._cmake.definitions["CMAKE_DEBUG_POSTFIX"] = "d"
            self._cmake.definitions["BUILD_SHARED_LIBS"] = True
            self._cmake.definitions["WEBP_ENABLE_SIMD"] = True
            self._cmake.definitions["WEBP_BUILD_ANIM_UTILS"] = False
            self._cmake.definitions["WEBP_BUILD_CWEBP"] = False
            self._cmake.definitions["WEBP_BUILD_DWEBP"] = False
            self._cmake.definitions["WEBP_BUILD_GIF2WEBP"] = False
            self._cmake.definitions["WEBP_BUILD_IMG2WEBP"] = False
            self._cmake.definitions["WEBP_BUILD_VWEBP"] = False
            self._cmake.definitions["WEBP_BUILD_WEBPINFO"] = False
            self._cmake.definitions["WEBP_BUILD_WEBPMUX"] = False
            self._cmake.definitions["WEBP_BUILD_EXTRAS"] = False
            self._cmake.definitions["WEBP_BUILD_WEBP_JS"] = False
            self._cmake.definitions["WEBP_NEAR_LOSSLESS"] = True
            self._cmake.definitions["WEBP_ENABLE_SWAP_16BIT_CSP"] = False
            self._cmake.definitions['CMAKE_DISABLE_FIND_PACKAGE_GIF'] = True
            self._cmake.definitions['CMAKE_DISABLE_FIND_PACKAGE_PNG'] = True
            self._cmake.definitions['CMAKE_DISABLE_FIND_PACKAGE_TIFF'] = True
            self._cmake.definitions['CMAKE_DISABLE_FIND_PACKAGE_JPEG'] = True
            self._cmake.definitions['CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS'] = True

            self._cmake.configure()

        return self._cmake


    def build(self):
        cmake = self._configure_cmake()
        cmake.build()


    def package(self):
        cmake = self._configure_cmake()
        cmake.install()

        self.copy("*.pdb", src="bin", dst="bin")

        tools.rmdir(os.path.join(self.package_folder, "lib", "pkgconfig"))
        tools.rmdir(os.path.join(self.package_folder, "share"))

        self.patch_binaries()
        self.default_package()


    def package_info(self):
        libname = lambda name: ("lib" if tools.os_info.is_windows else "") + (name + "d" if self.settings.build_type == 'Debug' else name)

        self.cpp_info.names["cmake_find_package"] = "WebP"
        self.cpp_info.names["cmake_find_package_multi"] = "WebP"

        # webpdecoder
        self.cpp_info.components["webpdecoder"].names["cmake_find_package"] = "webpdecoder"
        self.cpp_info.components["webpdecoder"].names["cmake_find_package_multi"] = "webpdecoder"
        self.cpp_info.components["webpdecoder"].names["pkg_config"] = "libwebpdecoder"
        self.cpp_info.components["webpdecoder"].libs = [libname("webpdecoder")]

        if tools.os_info.is_linux:
            self.cpp_info.components["webpdecoder"].system_libs = ["pthread"]

        # webp
        self.cpp_info.components["webp-lib"].names["cmake_find_package"] = "webp"
        self.cpp_info.components["webp-lib"].names["cmake_find_package_multi"] = "webp"
        self.cpp_info.components["webp-lib"].names["pkg_config"] = "libwebp"
        self.cpp_info.components["webp-lib"].libs = [libname("webp")]

        if tools.os_info.is_linux:
            self.cpp_info.components["webp-lib"].system_libs = ["m", "pthread"]

        # webpdemux
        self.cpp_info.components["webpdemux"].names["cmake_find_package"] = "webpdemux"
        self.cpp_info.components["webpdemux"].names["cmake_find_package_multi"] = "webpdemux"
        self.cpp_info.components["webpdemux"].names["pkg_config"] = "libwebpdemux"
        self.cpp_info.components["webpdemux"].libs = [libname("webpdemux")]
        self.cpp_info.components["webpdemux"].requires = ["webp-lib"]

        # webpmux
        self.cpp_info.components["webpmux"].names["cmake_find_package"] = "libwebpmux"
        self.cpp_info.components["webpmux"].names["cmake_find_package_multi"] = "libwebpmux"
        self.cpp_info.components["webpmux"].names["pkg_config"] = "libwebpmux"
        self.cpp_info.components["webpmux"].libs = [libname("webpmux")]
        self.cpp_info.components["webpmux"].requires = ["webp-lib"]

        if tools.os_info.is_linux:
            self.cpp_info.components["webpmux"].system_libs = ["m"]
