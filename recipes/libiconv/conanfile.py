# -*- coding: utf-8 -*-
from conans import ConanFile
from conans import tools
from conans import CMake
from conans import AutoToolsBuildEnvironment
from conans.errors import ConanInvalidConfiguration
import os


class ConanRecipe(ConanFile):
    python_requires = 'common/1.0.0@mevislab/stable'
    python_requires_extend = 'common.CommonRecipe'

    _autotools = None
    _cmake = None


    def validate(self):
        if tools.os_info.is_macos:
            raise ConanInvalidConfiguration(f"{self.name} is not supported on macOS")


    def _configure_cmake(self):
        if not self._cmake:
            self._cmake = CMake(self)
            self._cmake.definitions["CMAKE_DEBUG_POSTFIX"] = "d"
            self._cmake.definitions["CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS"] = True

            self._cmake.configure()
        return self._cmake


    def _configure_autotools(self):
        if not self._autotools:
            if self.settings.build_type == "Debug":
                tools.replace_in_file('sources/lib/Makefile.in', "libiconv.la", "libiconvd.la")
                tools.replace_in_file('sources/src/Makefile.in', "libiconv.la", "libiconvd.la")
                tools.replace_in_file('sources/libcharset/lib/Makefile.in', "libcharset.la", "libcharsetd.la")

            self._autotools = AutoToolsBuildEnvironment(self)
            self._autotools.fpic = self.settings.os != "Windows"
            self._autotools.configure(args=["--enable-static=no", "--enable-shared=yes", "--enable-relocatable"], configure_dir="sources")
        return self._autotools


    def build(self):
        if self.settings.os == "Windows":
            cmake = self._configure_cmake()
            cmake.build()
        else:
            autotools = self._configure_autotools()
            autotools.make()


    def package(self):
        if self.settings.os == "Windows":
            cmake = self._configure_cmake()
            cmake.install()
        else:
            autotools = self._configure_autotools()
            autotools.install()

        for it in ['libcharset.la', 'libcharsetd.la', 'libiconv.la', 'libiconvd.la']:
            if os.path.exists(os.path.join(self.package_folder, "lib", it)):
                os.unlink(os.path.join(self.package_folder, "lib", it))

        if not tools.os_info.is_windows:
            tools.rmdir(os.path.join(self.package_folder, 'bin'))

        tools.rmdir(os.path.join(self.package_folder, 'share', 'doc'))
        tools.rmdir(os.path.join(self.package_folder, 'share', 'man'))

        self.default_package()
