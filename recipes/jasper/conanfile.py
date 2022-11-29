# -*- coding: utf-8 -*-
from email import generator
from conans import ConanFile
from conans import tools
#from conans import CMake
import glob
import os

from conan.tools.cmake import CMake, CMakeToolchain, CMakeDeps

class ConanRecipe(ConanFile):
    python_requires = 'common/1.0.0@mevislab/stable'
    python_requires_extend = 'common.CommonRecipe'

    generators = "cmake_find_package"

    def system_requirements(self):
        installer = tools.SystemPackageTool()
        packages = []

        if tools.os_info.linux_distro in ["ubuntu", "debian"]:
            packages.append('libglu1-mesa-dev')

        if packages:
            installer.install_packages(packages)


    def requirements(self):
        channel = "@{0}/{1}".format(self.user, self.channel)
        self.requires("libjpeg/9e" + channel)


    def generate(self):
        toolchain = CMakeToolchain(self)
        toolchain.variables["CMAKE_DEBUG_POSTFIX"] = "d"
        toolchain.variables["BUILD_SHARED_LIBS"] = True
        toolchain.variables["JAS_ENABLE_DOC"] = False
        toolchain.variables["JAS_ENABLE_PROGRAMS"] = False
        toolchain.variables["JAS_ENABLE_SHARED"] = True
        toolchain.variables["JAS_LIBJPEG_REQUIRED"] = "REQUIRED"
        toolchain.variables["JAS_ENABLE_OPENGL"] = False
        toolchain.variables["ALLOW_IN_SOURCE_BUILD"] = True
        toolchain.variables["JAS_ENABLE_AUTOMATIC_DEPENDENCIES"] = False
        toolchain.variables["JAS_ENABLE_LIBHEIF"] = False

        toolchain.generate()


    def build(self):
        cmake = CMake(self)
        cmake.configure(build_script_folder="sources")
        cmake.build()


    def package(self):
        cmake = CMake(self)
        cmake.install()

        self.copy("*.pdb", dst="bin", keep_path=False, excludes="*vc*.pdb")

        tools.rmdir(os.path.join(self.package_folder, "share"))
        tools.rmdir(os.path.join(self.package_folder, "lib", "pkgconfig"))

        if self.settings.os == "Windows":
            for dll_file in glob.glob(os.path.join(self.package_folder, "bin", "*.dll")):
                if os.path.basename(dll_file).startswith(("concrt", "msvcp", "vcruntime")):
                    os.unlink(dll_file)

        self.patch_binaries()
        self.default_package()


    def package_info(self):
        self.default_package_info()
        if self.settings.os == "Linux":
            self.cpp_info.system_libs.append("m")
