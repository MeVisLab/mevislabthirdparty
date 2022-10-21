# -*- coding: utf-8 -*-
from conans import ConanFile
from conans import tools
from conans.errors import ConanInvalidConfiguration
import os
import io

meson_sh = u"""#!/bin/sh
meson_dir=$(dirname "$0")
exec "$meson_dir/meson.py" "$@"
"""

meson_cmd = u"""
@echo off
CALL python %~dp0/meson.py %*
"""

class ConanRecipe(ConanFile):
    python_requires = 'common/1.0.0@mevislab/stable'
    python_requires_extend = 'common.CommonRecipe'

    settings = "os"
    no_copy_source = True

    sanitizer = { 'cmake': False }


    def requirements(self):
        channel = "@{0}/{1}".format(self.user, self.channel)
        self.requires("ninja_installer/[>=1.9.0]" + channel)


    def package(self):
        # create wrapper scripts
        with io.open(os.path.join(self.package_folder, "meson.cmd"), 'w', newline='\r\n') as f:
            f.write(meson_cmd)
        with io.open(os.path.join(self.package_folder, "meson"), 'w', newline='\n') as f:
            f.write(meson_sh)

        self.copy(pattern="*", dst=".", src="sources")

        tools.rmdir(os.path.join(self.package_folder, "ci"))
        tools.rmdir(os.path.join(self.package_folder, "docs"))
        tools.rmdir(os.path.join(self.package_folder, "graphics"))
        tools.rmdir(os.path.join(self.package_folder, "man"))
        tools.rmdir(os.path.join(self.package_folder, "manual tests"))
        tools.rmdir(os.path.join(self.package_folder, "test cases"))

        self.default_package()


    def package_info(self):
        self.env_info.PATH.append(self.package_folder)
        if os.name == 'posix':
            os.chmod(os.path.join(self.package_folder, "meson"), os.stat(os.path.join(self.package_folder, "meson")).st_mode | 0o111)
            os.chmod(os.path.join(self.package_folder, "meson.py"), os.stat(os.path.join(self.package_folder, "meson.py")).st_mode | 0o111)
