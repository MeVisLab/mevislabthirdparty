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


    def validate(self):
        if self.settings.os != "Windows":
            raise ConanInvalidConfiguration(f"{self.name} is only supported on Windows")


    def build_requirements(self):
        channel = "@{0}/{1}".format(self.user, self.channel)
        if self.settings.os == "Windows":
            self.build_requires("7z_installer/[>=19.0]" + channel)


    def source(self):
        self.default_source()
        zipFile = f"python2_installer-{self.version}.exe"
        self.run(f"7za x {zipFile}")
        os.remove(zipFile)
        os.rename(f"Portable Python-{self.version} x64", "sources")
        os.rename(os.path.join("sources", "App", "Python", "python.exe"), os.path.join("sources", "App", "Python", "python2.exe"))

        os.remove(os.path.join("sources", "App", "Python", "pythonw.exe"))

        shutil.rmtree(os.path.join("sources", "App", "PyScripter"), ignore_errors=True)
        shutil.rmtree(os.path.join("sources", "App", "Scripts"), ignore_errors=True)
        shutil.rmtree(os.path.join("sources", "App", "Python", "Doc"), ignore_errors=True)
        shutil.rmtree(os.path.join("sources", "App", "Python", "include"), ignore_errors=True)
        shutil.rmtree(os.path.join("sources", "App", "Python", "tcl"), ignore_errors=True)
        shutil.rmtree(os.path.join("sources", "App", "Python", "libs"), ignore_errors=True)


    def package(self):
        self.copy("*", src=os.path.join("sources", "App", "Python"), keep_path=True)
        self.default_package()


    def package_info(self):
        self.output.info("Appending PATH env var with: " + self.package_folder)
        self.env_info.path.append(self.package_folder)
        self.cpp_info.libdirs = []
        self.cpp_info.includedirs = []
