# -*- coding: utf-8 -*-
from conans import ConanFile
from conans import tools
from conans import CMake
from conan.tools.cmake import CMake, CMakeToolchain, cmake_layout
import os


class ConanRecipe(ConanFile):
    python_requires = 'common/1.0.0@mevislab/stable'
    python_requires_extend = 'common.CommonRecipe'
    generators = "cmake_find_package"


    def build_requirements(self):
        channel = "@{0}/{1}".format(self.user, self.channel)
        if self.settings.os == 'Windows':
            self.build_requires("nasm_installer/[>=2.14]" + channel)


    def layout(self):
        cmake_layout(self)


    def generate(self):
        toolchain = CMakeToolchain(self)
        toolchain.variables["CMAKE_DEBUG_POSTFIX"] = "d"
        toolchain.variables["CMAKE_POSITION_INDEPENDENT_CODE"] = True
        toolchain.variables["BUILD_SHARED_LIBS"] = True
        toolchain.variables["ENABLE_STATIC"] = False
        toolchain.variables["ENABLE_SHARED"] = True
        toolchain.variables["REQUIRE_SIMD"] = True  # no simd -> error!
        toolchain.variables["CMAKE_INSTALL_DEFAULT_LIBDIR"] = 'lib'

        toolchain.generate()


    def build(self):
        cmake = CMake(self)
        cmake.configure(build_script_folder="sources")
        cmake.build()


    def package(self):
        cmake = CMake(self)
        cmake.install()

        tools.rmdir(os.path.join(self.package_folder, "lib", "pkgconfig"))
        tools.rmdir(os.path.join(self.package_folder, "lib", "cmake"))
        tools.rmdir(os.path.join(self.package_folder, "share"))

        self.patch_binaries()
        self.default_package()


    def package_info(self):
        self.default_package_info()
        self.cpp_info.names["pkg_config"] = "libturbojpeg"
