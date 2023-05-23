# -*- coding: utf-8 -*-
from conans import ConanFile
from conans import tools
import shutil
import os


class ConanRecipe(ConanFile):
    python_requires = 'common/1.0.0@mevislab/stable'
    python_requires_extend = 'common.PythonPackageRecipe'
    parallel_make = False


    def system_requirements(self):
        installer = tools.SystemPackageTool()
        packages = []

        if tools.os_info.linux_distro in ["ubuntu", "debian"]:
            packages.append('libfreetype6-dev')

        if packages:
            installer.install_packages(packages)


    def requirements(self):
        super().requirements()

        channel = "@{0}/{1}".format(self.user, self.channel)
        self.requires("six/[>=1.15.0]" + channel)
        self.requires("numpy/[>=1.16.4]" + channel)
        self.requires("dateutil/[>=2.4.2]" + channel)
        self.requires("pytz/[>=2015.4]" + channel)
        self.requires("pyparsing/[>=2.0.3]" + channel)
        self.requires("libpng/[>=1.6.37]" + channel)
        self.requires("zlib/[>=1.2.11]" + channel)
        self.requires("cycler/[>=0.11.0]" + channel)
        # current version does not work with newer versions of kiwisolver
        self.requires("kiwisolver/[==1.4.1]" + channel)

        if not tools.os_info.is_linux:
            self.requires("freetype/[>=2.10.2]" + channel)



    def source(self):
        self.default_source()
        shutil.move(os.path.join("sources", "LICENSE", "LICENSE"), os.path.join("sources", "COPYING"))
        # tools.replace_in_file('sources/setupext.py', "version = 'Failed to identify version.'", "version = None")
        tools.replace_in_file('sources/setupext.py', 'ext.extra_link_args.extend(["-mwindows"])', '')
        # Conan currently uses the library version for the pkg-config, but freetype should use the libtool version:
        tools.replace_in_file('sources/setupext.py', "atleast_version='9.11.3',", "atleast_version='2.3.0',")


    def build(self):
        d_suffix = "d" if self.settings.build_type=="Debug" else ""
        tools.replace_in_file('sources/setupext.py', "['png', 'z'] if os.name == 'posix' else",
            "['libpng16{d}', 'zlibstatic{d}'] if os.name == 'posix' else".format(d=d_suffix))
        tools.replace_in_file('sources/setupext.py', "[deplib('libpng16'), deplib('z')] if os.name == 'nt' else",
            "['libpng16{d}', 'zlibstatic{d}'] if os.name == 'nt' else".format(d=d_suffix))

        if tools.os_info.is_linux:
            tools.replace_in_file('sources/setupext.py', "default_libraries=['freetype', deplib('z')])",
                "default_libraries=['freetype', 'zlibstatic{d}', 'libpng16{d}'])".format(d=d_suffix))

        else:
            tools.replace_in_file('sources/setupext.py', "default_libraries=['freetype', deplib('z')])",
                "default_libraries=['freetype{d}', 'zlibstatic{d}', 'libpng16{d}'])".format(d=d_suffix))

        if tools.os_info.is_windows:
            extra_env = {
                "INCLUDE": os.pathsep.join(
                    [os.path.join(self.deps_cpp_info[dep].rootpath, x)
                        for dep in ("freetype", "libpng", "numpy") for x in self.deps_cpp_info[dep].includedirs]),
                "LIB": os.pathsep.join(
                    [os.path.join(self.deps_cpp_info[dep].rootpath, x)
                        for dep in ("freetype", "libpng", "zlib") for x in self.deps_cpp_info[dep].libdirs])
            }
        else:
            extra_env = {}

        with tools.environment_append(extra_env):
            super().build()
