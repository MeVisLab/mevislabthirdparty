# -*- coding: utf-8 -*-
from conans import ConanFile, tools, AutoToolsBuildEnvironment
from conans.errors import ConanInvalidConfiguration
import os


class ConanRecipe(ConanFile):
    python_requires = 'common/1.0.0@mevislab/stable'
    python_requires_extend = 'common.CommonRecipe'

    settings = "os"

    def validate(self):
        if self.settings.os != "Windows":
            raise ConanInvalidConfiguration(f"{self.name} is only supported on Windows")


    def build(self):
        with tools.chdir('sources'):
            if self.settings.os == "Windows":
                command = "build_w32.bat --without-guile"
            else:
                env_build = AutoToolsBuildEnvironment(self)
                env_build.configure()
                command = "./build.sh"
            with tools.vcvars(self.settings) if self.settings.os == "Windows" else tools.no_op():
                self.run(command)


    def package(self):
        self.copy(pattern="make", dst="bin", src='sources', keep_path=False)
        self.copy(pattern="*gnumake.exe", dst="bin", src='sources', keep_path=False)
        self.default_package()


    def package_info(self):
        make = "gnumake.exe" if self.settings.os == "Windows" else "make"
        make = os.path.join(self.package_folder, "bin", make)
        self.output.info('Creating CONAN_MAKE_PROGRAM environment variable: %s' % make)
        self.env_info.CONAN_MAKE_PROGRAM = make
