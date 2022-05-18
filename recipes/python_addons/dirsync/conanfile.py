# -*- coding: utf-8 -*-
from conans import ConanFile
from conans.errors import ConanException
from conans import tools
import os

class ConanRecipe(ConanFile):
    python_requires = 'common/1.0.0@mevislab/stable'
    python_requires_extend = 'common.PythonPackageRecipe'


    def requirements(self):
        self.default_requirements()

        self.requires(f"six/[>=1.16.0]@{self.user}/{self.channel}")


    def package(self):
        self.default_package()

        # remove (currently) not working starter script:
        if tools.os_info.is_windows:
            tools.rmdir(os.path.join(self.package_folder, "Scripts"))
        else:
            tools.rmdir(os.path.join(self.package_folder, "bin"))
        
        tools.rmdir(os.path.join(self.package_folder, self.relative_site_package_folder(), "tests"))
