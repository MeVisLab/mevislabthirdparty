# -*- coding: utf-8 -*-
from conans import ConanFile
from conans import tools
from conans import CMake
from conans.errors import ConanInvalidConfiguration
import os


class ConanRecipe(ConanFile):
    python_requires = 'common/1.0.0@mevislab/stable'
    python_requires_extend = 'common.CommonRecipe'

    _cmake = None


    def package_id(self):
        del self.info.settings.build_type


    def validate(self):
        if self.settings.os != "Windows":
            raise ConanInvalidConfiguration(f"{self.name} is only supported on Windows")


    def validate_build(self):
        if self.settings.build_type != "Release":
            raise ConanInvalidConfiguration(f"{self.name} is built in release mode only.")


    def requirements(self):
        channel = "@{0}/{1}".format(self.user, self.channel)
        self.requires("libxml2/[>=2.9.9]" + channel)


    def _configure_cmake(self):
        if not self._cmake:
            self._cmake = CMake(self)
            # see https://llvm.org/docs/CMake.html#options-and-variables

            self._cmake.definitions["CMAKE_VS_PLATFORM_TOOLSET_HOST_ARCHITECTURE"] = "x64"

            self._cmake.definitions["LLVM_TARGETS_TO_BUILD"] = "X86"
            self._cmake.definitions["LLVM_BUILD_EXAMPLES"] = False
            self._cmake.definitions["LLVM_INCLUDE_EXAMPLES"] = False
            self._cmake.definitions["LLVM_BUILD_TESTS"] = False
            self._cmake.definitions["LLVM_INCLUDE_TESTS"] = False
            self._cmake.definitions["LLVM_BUILD_BENCHMARKS"] = False
            self._cmake.definitions["LLVM_INCLUDE_BENCHMARKS"] = False
            self._cmake.definitions["LLVM_ENABLE_UNWIND_TABLES"] = False
            self._cmake.definitions["LLVM_ENABLE_FFI"] = False
            self._cmake.definitions["LLVM_ENABLE_LIBPFM"] = False
            self._cmake.definitions["LLVM_ENABLE_Z3_SOLVER"] = False
            self._cmake.definitions["LLVM_USE_CRT_DEBUG"] = "MTd"
            self._cmake.definitions["LLVM_USE_CRT_RELEASE"] = "MT"

            self._cmake.configure(source_folder='sources', build_folder='build')

        return self._cmake


    def build(self):
        cmake = self._configure_cmake()
        cmake.build()


    def package(self):
        cmake = self._configure_cmake()
        cmake.install()

        tools.rmdir(os.path.join(self.package_folder, 'share'))
        tools.rmdir(os.path.join(self.package_folder, 'lib', 'cmake'))

        self.default_package()


    def package_info(self):
        self.default_package_info()
        self.env_info.PATH.append(os.path.join(self.package_folder, "bin"))
