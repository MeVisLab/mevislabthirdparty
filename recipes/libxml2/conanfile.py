# -*- coding: utf-8 -*-
from conans import ConanFile
from conans import AutoToolsBuildEnvironment
from conans import tools
import glob
import os


class ConanRecipe(ConanFile):
    python_requires = 'common/1.0.0@mevislab/stable'
    python_requires_extend = 'common.CommonRecipe'


    def requirements(self):
        channel = "@{0}/{1}".format(self.user, self.channel)
        self.requires("zlib/[>=1.2.11]" + channel)
        self.requires("icu/[>=68.2]" + channel)
        #self.requires("lzma/[>=5.2.4]" + channel)


    def build(self):
        if tools.os_info.is_windows:
            self._build_windows()
        else:
            self._build_autotools()


    def imports(self):
        if tools.os_info.is_macos:
            self.copy("*.dylib*", src="lib", dst="lib")


    def package(self):
        if tools.os_info.is_windows:
            # There is no way to avoid building the tests, but at least we don't want them in the package
            for prefix in ["run", "test"]:
                for test in glob.glob("%s/bin/%s*" % (self.package_folder, prefix)):
                    os.remove(test)

        for header in ["win32config.h", "wsockcompat.h"]:
            self.copy(pattern=header, src=os.path.join("sources", "include"),
                      dst=os.path.join("include", "libxml2"), keep_path=False)

        if tools.os_info.is_windows:
            # remove redundant libraries to avoid confusion
            os.unlink(os.path.join(self.package_folder, 'lib', 'libxml2_a_dll.lib'))
            os.unlink(os.path.join(self.package_folder, 'lib', 'libxml2_a.lib'))

        tools.rmdir(os.path.join(self.package_folder, "lib", "pkgconfig"))
        tools.rmdir(os.path.join(self.package_folder, "lib", "cmake"))
        tools.rmdir(os.path.join(self.package_folder, "share"))

        if os.path.exists(os.path.join(self.package_folder, "lib", "libxml2.la")):
            os.unlink(os.path.join(self.package_folder, "lib", "libxml2.la"))

        if os.path.exists(os.path.join(self.package_folder, "lib", "xml2Conf.sh")):
            os.unlink(os.path.join(self.package_folder, "lib", "xml2Conf.sh"))

        self.patch_binaries(executables=['xmlcatalog', 'xmllint'])
        self.default_package()


    def package_info(self):
        self.default_package_info()

        self.cpp_info.includedirs.append(os.path.join("include", "libxml2"))

        if tools.os_info.is_linux or tools.os_info.is_macos:
            self.cpp_info.libs.append('m')

        if tools.os_info.is_windows:
            self.cpp_info.libs.append('ws2_32')


    def _build_windows(self):
        with tools.chdir(os.path.join("sources", 'win32')):
            with tools.vcvars(self.settings):
                args = []
                args.append('cscript')
                args.append('configure.js')
                args.append('zlib=yes')
                args.append('lzma=no')
                args.append('icu=yes')
                args.append('iconv=no')
                args.append('compiler=msvc')
                args.append("cruntime=/%s" % self.settings.compiler.runtime)
                args.append("prefix=%s" % self.package_folder)
                #args.append("debug=%s" % ("yes" if self.settings.build_type == "Debug" else "no"))
                #args.append('static=no')
                args.append('include="%s"' % ";".join(self.deps_cpp_info.include_paths))
                args.append('lib="%s"' % ";".join(self.deps_cpp_info.lib_paths))

                self.output.info(' '.join(args))
                self.run(' '.join(args))

                # Fix library names because they can be not just zlib.lib
                def fix_library(package, old_libname):
                    libs = []
                    for lib in self.deps_cpp_info[package].libs:
                        libname = lib
                        if not libname.endswith('.lib'):
                            libname += '.lib'
                        libs.append(libname)
                    tools.replace_in_file("Makefile.msvc",
                                          "LIBS = $(LIBS) %s" % old_libname,
                                          "LIBS = $(LIBS) %s" % ' '.join(libs))

                fix_library('zlib', 'zlib.lib')
                #fix_library('lzma', 'liblzma.lib')
                fix_library('icu', 'advapi32.lib sicuuc.lib sicuin.lib sicudt.lib')
                fix_library('icu', 'icuuc.lib icuin.lib icudt.lib')

                self.run("nmake /f Makefile.msvc install")


    def _build_autotools(self):
        autotools = AutoToolsBuildEnvironment(self)
        env_vars = autotools.vars.copy()
        if tools.os_info.is_macos:
            autotools.link_flags.append(f"-rpath {self.build_folder}/lib")

        if tools.os_info.is_linux:
            if 'LD_LIBRARY_PATH' in env_vars:
                env_vars['LD_LIBRARY_PATH'] = ':'.join([env_vars['LD_LIBRARY_PATH']] + self.deps_cpp_info.libdirs)
            else:
                env_vars['LD_LIBRARY_PATH'] = ':'.join(self.deps_cpp_info.libdirs)

        args = ['--prefix=%s' % tools.unix_path(self.package_folder)]
        args.append('--with-python=no')
        args.append('--with-pic')
        args.append('--enable-shared')
        args.append('--disable-static')
        args.append('--with-zlib')
        args.append('--without-lzma')
        args.append('--without-iconv')
        args.append('--with-icu')

        with tools.environment_append(env_vars):
            autotools.configure(args=args, configure_dir='sources')
            autotools.make(args=["install"])
