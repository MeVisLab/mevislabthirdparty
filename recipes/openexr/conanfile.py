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
        self.requires("imath/[>=3.1.3]" + channel)
        self.requires("zlib/[>=1.2.11]" + channel)


    def _configure_cmake(self):
        if not self._cmake:
            self.create_cmake_wrapper()
            self._cmake = CMake(self)
            self._cmake.definitions["BUILD_SHARED_LIBS"] = True
            self._cmake.definitions["OPENEXR_INSTALL_PKG_CONFIG"] = False
            self._cmake.definitions["OPENEXR_LIB_SUFFIX"] = ""
            self._cmake.configure()
        return self._cmake


    def build(self):
        cmake = self._configure_cmake()
        cmake.build()


    def package(self):
        cmake = self._configure_cmake()
        cmake.install()

        self.copy("*.pdb", src="bin", dst="bin", excludes="*Test.pdb")

        tools.rmdir(os.path.join(self.package_folder, "lib", "pkgconfig"))
        tools.rmdir(os.path.join(self.package_folder, 'lib', 'cmake'))
        tools.rmdir(os.path.join(self.package_folder, "share"))

        self.patch_binaries(executables=['exr2aces', 'exrenvmap', 'exrheader', 'exrinfo', 'exrmakepreview', 'exrmaketiled', 'exrmultipart', 'exrmultiview', 'exrstdattr'])
        self.default_package()


    def package_info(self):
        self.default_package_info()

        if self.settings.os == "Windows":
            self.cpp_info.defines.append("OPENEXR_DLL")

        if self.settings.os != "Windows":
            self.cpp_info.cxxflags = ["-pthread"]
