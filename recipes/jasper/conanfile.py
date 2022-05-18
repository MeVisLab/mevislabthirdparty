# -*- coding: utf-8 -*-
from conans import ConanFile
from conans import tools
from conans import CMake
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
            packages.append('libglu1-mesa-dev')

        if packages:
            installer.install_packages(packages)


    def requirements(self):
        channel = "@{0}/{1}".format(self.user, self.channel)
        self.requires("libjpeg/9e" + channel)


    def _configure_cmake(self):
        if not self._cmake:
            self._cmake = CMake(self)
            self._cmake.definitions["CMAKE_DEBUG_POSTFIX"] = "d"
            self._cmake.definitions["BUILD_SHARED_LIBS"] = True
            self._cmake.definitions["JAS_ENABLE_DOC"] = False
            self._cmake.definitions["JAS_ENABLE_PROGRAMS"] = False
            self._cmake.definitions["JAS_ENABLE_SHARED"] = True
            self._cmake.definitions["JAS_LIBJPEG_REQUIRED"] = "REQUIRED"
            self._cmake.definitions["JAS_ENABLE_OPENGL"] = False
            self._cmake.definitions["ALLOW_IN_SOURCE_BUILD"] = True
            self._cmake.definitions["JAS_ENABLE_AUTOMATIC_DEPENDENCIES"] = False

            self._cmake.configure()
        return self._cmake


    def build(self):
        cmake = self._configure_cmake()
        cmake.build()


    def package(self):
        cmake = self._configure_cmake()
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
            self.cpp_info.libs.append("m")
