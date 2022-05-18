# -*- coding: utf-8 -*-
from conans import ConanFile
from conans import CMake
from conans import tools
from conans.errors import ConanInvalidConfiguration
import shutil
import os


class ConanRecipe(ConanFile):
    python_requires = 'common/1.0.0@mevislab/stable'
    python_requires_extend = 'common.CommonRecipe'

    settings = "os"

    _cmake = None


    def validate(self):
        if self.settings.os != "Windows":
            raise ConanInvalidConfiguration(f"{self.name} is only supported on Windows")


    def _configure_cmake(self):
        if not self._cmake:
            self._cmake = CMake(self)
            self._cmake.configure()
        return self._cmake


    def build(self):
        # Generate license from header of a source file
        with open(os.path.join(self.source_folder, "sources", "bison", "data", "skeletons", "glr.cc")) as f:
            content_lines = f.readlines()
        license_content = []
        for i in range(2, 16):
            license_content.append(content_lines[i][2:-1])
        tools.save(os.path.join(self.source_folder, "LICENSE"), "\n".join(license_content))

        self._configure_cmake().build()


    def package(self):
        self.copy(pattern="data/*", dst="bin", src="sources/bison", keep_path=True)
        self.copy(pattern="*.exe", dst="bin", src="sources/bin/Release", keep_path=False)
        self.copy(pattern="*.exe", dst="bin", src="sources/bin/Debug", keep_path=False)
        self.copy(pattern="*.exe", dst="bin", src="bin", keep_path=False)

        shutil.copy2(os.path.join(self.package_folder, 'bin', 'win_flex.exe'), os.path.join(self.package_folder, 'bin', 'flex.exe'))
        shutil.copy2(os.path.join(self.package_folder, 'bin', 'win_bison.exe'), os.path.join(self.package_folder, 'bin', 'bison.exe'))

        self.default_package()


    def package_info(self):
        bindir = os.path.join(self.package_folder, "bin")
        self.output.info("Appending PATH environment variable: {}".format(bindir))
        self.env_info.PATH.append(bindir)
