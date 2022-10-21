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
            self._cmake.definitions["CMAKE_INSTALL_SYSTEM_RUNTIME_LIBS_SKIP"] = True

            self._cmake.definitions["BUILD_DOC"] = False
            self._cmake.definitions["BUILD_STATIC_LIBS"] = False
            self._cmake.definitions["BUILD_LUTS_GENERATOR"] = False
            self._cmake.definitions["BUILD_CODEC"] = False
            self._cmake.definitions["BUILD_JPIP"] = False
            self._cmake.definitions["BUILD_VIEWER"] = False
            self._cmake.definitions["BUILD_JAVA"] = False
            self._cmake.definitions["BUILD_TESTING"] = False
            self._cmake.definitions["BUILD_PKGCONFIG_FILES"] = False
            self._cmake.definitions["OPJ_DISABLE_TPSOT_FIX"] = False
            self._cmake.definitions["OPJ_USE_THREAD"] = True
            self._cmake.definitions["BUILD_THIRDPARTY"] = False

            self._cmake.configure()
        return self._cmake


    def build(self):
        cmake = self._configure_cmake()
        cmake.build()


    def package(self):
        cmake = self._configure_cmake()
        cmake.install()

        self.copy("*.pdb", src="bin", dst="bin")

        v = tools.Version(self.version)
        tools.rmdir(os.path.join(self.package_folder, "lib", f"openjpeg-{v.major}.{v.minor}"))

        self.patch_binaries()
        self.default_package()


    def package_info(self):
        self.default_package_info()

        self.cpp_info.names["pkg_config"] = "libopenjp2"

        v = tools.Version(self.version)
        self.cpp_info.includedirs.append(os.path.join("include", f"openjpeg-{v.major}.{v.minor}"))

        if self.settings.os == "Linux":
            self.cpp_info.system_libs = ["pthread", "m"]
