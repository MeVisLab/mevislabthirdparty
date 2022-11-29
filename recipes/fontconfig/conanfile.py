# -*- coding: utf-8 -*-
from conans import ConanFile
from conans import tools
from conans import AutoToolsBuildEnvironment
from conans.errors import ConanInvalidConfiguration
import shutil
import os


class ConanRecipe(ConanFile):
    python_requires = 'common/1.0.0@mevislab/stable'
    python_requires_extend = 'common.CommonRecipe'


    def validate(self):
        if self.settings.os == "Windows":
            raise ConanInvalidConfiguration(f"{self.name} is not supported on Windows")


    def requirements(self):
        channel = "@{0}/{1}".format(self.user, self.channel)
        self.requires("freetype/[>=2.10.4]" + channel)
        self.requires("libxml2/[>=2.9.9]" + channel)


    def build(self):
        autotools = AutoToolsBuildEnvironment(self)
        env_vars = autotools.vars.copy()

        env_vars['FREETYPE_CFLAGS']=os.path.join(self.deps_cpp_info["freetype"].rootpath, "include", "freetype2")
        env_vars['FREETYPE_LIBS']="-L%s -l%s" % (self.deps_cpp_info["freetype"].lib_paths[0], 'freetyped' if self.settings.build_type == "Debug" else 'freetype')

        env_vars['LIBXML2_CFLAGS']=os.path.join(self.deps_cpp_info["libxml2"].rootpath, "include", "libxml2")
        env_vars['LIBXML2_LIBS']="-L%s -lxml2" % self.deps_cpp_info["libxml2"].lib_paths[0]

        # Configure script creates conftest that cannot execute without the shared libraries.
        # Ways to solve the problem:
        # 1. set *LD_LIBRARY_PATH (works with Linux but does not work on OS X 10.11 with SIP)
        # 2. copying dylib's to the build directory (fortunately works on OS X)
        # 3. set rpath (dangerous)
        if tools.os_info.is_macos:
            # copy all dependencies
            for dependency in self.deps_cpp_info.deps:
                imported_libs = os.listdir(self.deps_cpp_info[dependency].lib_paths[0])
                for imported_lib in imported_libs:
                    it = self.deps_cpp_info[dependency].lib_paths[0] + '/' + imported_lib
                    if os.path.isfile(it) or os.path.islink(it):
                        shutil.copy(it, '.')
        elif self.settings.os == "Linux":
            if 'LD_LIBRARY_PATH' in env_vars:
                env_vars['LD_LIBRARY_PATH'] = ':'.join([env_vars['LD_LIBRARY_PATH']] + self.deps_cpp_info.libdirs)
            else:
                env_vars['LD_LIBRARY_PATH'] = ':'.join(self.deps_cpp_info.libdirs)

        with tools.environment_append(env_vars):
            args=[]
            args.append("--enable-static=no")
            args.append("--enable-shared=yes")
            args.append("--disable-docs")
            args.append("--enable-libxml2")
            args.append("--disable-rpath")
            #args.append("--with-cache-dir='/var/cache/fontconfig'")
            #args.append("--with-templatedir=/usr/share/fontconfig/conf.avail")
            args.append("--with-baseconfigdir=/etc/fonts")

            autotools.configure(configure_dir="sources", args=args)
            tools.replace_in_file("Makefile", "po-conf test", "po-conf")
            autotools.make()
            autotools.install()


    def package(self):
        tools.rmdir(os.path.join(self.package_folder, "bin"))
        tools.rmdir(os.path.join(self.package_folder, "etc"))
        tools.rmdir(os.path.join(self.package_folder, "share"))
        tools.rmdir(os.path.join(self.package_folder, "var"))
        tools.rmdir(os.path.join(self.package_folder, "lib", "pkgconfig"))

        if os.path.exists(os.path.join(self.package_folder, "lib", "libfontconfig.la")):
            os.unlink(os.path.join(self.package_folder, "lib", "libfontconfig.la"))

        self.default_package()


    def package_info(self):
        self.default_package_info()

        if self.settings.os == "Linux":
            self.cpp_info.system_libs.extend(["m", "pthread"])
