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
            packages.append('pkg-config')

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

        if not tools.os_info.is_linux:
            self.requires("freetype/[>=2.10.2]" + channel)



    def source(self):
        self.default_source()
        shutil.move(os.path.join("sources", "LICENSE", "LICENSE"), os.path.join("sources", "COPYING"))
        tools.replace_in_file('sources/setupext.py', "version = 'Failed to identify version.'", "version = None")
        tools.replace_in_file('sources/setupext.py', 'ext.extra_link_args.append("-mwindows")', '')


    def build(self):
        if tools.os_info.is_linux:
            tools.replace_in_file('sources/setupext.py', "default_libraries=['freetype', 'z'])", "default_libraries=['freetype', 'zlibstatic{d}', 'libpng16{d}'])".format(d="d" if self.settings.build_type=="Debug" else ""))
            tools.replace_in_file('sources/setupext.py', "default_libraries=['png', 'z'],", "default_libraries=['libpng16{d}', 'zlibstatic{d}'],".format(d="d" if self.settings.build_type=="Debug" else ""))

            extra_env = {
                "INCLUDE": ";".join([os.path.join(self.deps_cpp_info["libpng"].rootpath, x) for x in self.deps_cpp_info["libpng"].includedirs] + [os.path.join(self.deps_cpp_info["numpy"].rootpath, x) for x in self.deps_cpp_info["numpy"].includedirs]),
                "LIB": ";".join([os.path.join(self.deps_cpp_info["libpng"].rootpath, x) for x in self.deps_cpp_info["libpng"].libdirs] + [os.path.join(self.deps_cpp_info["zlib"].rootpath, x) for x in self.deps_cpp_info["zlib"].libdirs])
            }
        else:
            tools.replace_in_file('sources/setupext.py', "default_libraries=['freetype', 'z'])", "default_libraries=['freetype{d}', 'zlibstatic{d}', 'libpng16{d}'])".format(d="d" if self.settings.build_type=="Debug" else ""))
            tools.replace_in_file('sources/setupext.py', "default_libraries=['png', 'z'],", "default_libraries=['libpng16{d}', 'zlibstatic{d}'],".format(d="d" if self.settings.build_type=="Debug" else ""))
            extra_env = {"INCLUDE": ";".join(
                [os.path.join(self.deps_cpp_info["freetype"].rootpath, x) for x in self.deps_cpp_info["freetype"].includedirs]+
                [os.path.join(self.deps_cpp_info["libpng"].rootpath, x) for x in self.deps_cpp_info["libpng"].includedirs]+
                [os.path.join(self.deps_cpp_info["numpy"].rootpath, x) for x in self.deps_cpp_info["numpy"].includedirs]),
                "LIB": ";".join(
                [os.path.join(self.deps_cpp_info["freetype"].rootpath, x) for x in self.deps_cpp_info["freetype"].libdirs]+
                [os.path.join(self.deps_cpp_info["libpng"].rootpath, x) for x in self.deps_cpp_info["libpng"].libdirs]+
                [os.path.join(self.deps_cpp_info["zlib"].rootpath, x) for x in self.deps_cpp_info["zlib"].libdirs])
                }

        with tools.environment_append(extra_env) if tools.os_info.is_windows else tools.no_op():
            super().build()
