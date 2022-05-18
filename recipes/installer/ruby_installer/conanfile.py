# -*- coding: utf-8 -*-
from conans import ConanFile
from conans.errors import ConanInvalidConfiguration
import shutil
import os


class ConanRecipe(ConanFile):
    python_requires = 'common/1.0.0@mevislab/stable'
    python_requires_extend = 'common.CommonRecipe'

    settings = "os"
    no_copy_source = True

    sanitizer = { 'pkgconfig': False }


    def validate(self):
        if self.settings.os != "Windows":
            raise ConanInvalidConfiguration(f"{self.name} is only supported on Windows")


    def build_requirements(self):
        channel = "@{0}/{1}".format(self.user, self.channel)
        if self.settings.os == "Windows":
            self.build_requires("7z_installer/[>=19.0]" + channel)


    def source(self):
        self.default_source()
        zipFile = f"ruby_installer-{self.version}.7z"
        self.run(f"7za x {zipFile}")
        os.remove(zipFile)
        os.rename(f"rubyinstaller-{self.version}-1-x64", "sources")
        shutil.rmtree(os.path.join("sources", "share"), ignore_errors=True)


    def package(self):
        self.copy('*', dst="bin", src=os.path.join("sources", "bin"))
        self.copy('*', dst="include", src=os.path.join("sources", "include"))
        self.copy('*', dst="lib", src=os.path.join("sources", "lib"))
        self.copy('*', dst="ssl", src=os.path.join("sources", "ssl"))

        self.default_package()


    def package_info(self):
        self.env_info.PATH.append(os.path.join(self.package_folder, "bin"))
        self.cpp_info.libs = []
        self.cpp_info.includedirs = []
        self.cpp_info.libdirs = []
        self.cpp_info.resdirs = []
        self.cpp_info.bindirs = []
