# -*- coding: utf-8 -*-
from conans import ConanFile
from conans import AutoToolsBuildEnvironment
from conans import VisualStudioBuildEnvironment
from conans import tools
import glob
import os


class ConanRecipe(ConanFile):
    python_requires = 'common/1.0.0@mevislab/stable'
    python_requires_extend = 'common.CommonRecipe'


    def requirements(self):
        channel = "@{0}/{1}".format(self.user, self.channel)
        self.requires("libxml2/[>=2.9.0]" + channel)


    def imports(self):
        if tools.os_info.is_macos:
            self.copy("*.dylib*", src="lib", dst="lib")


    def build(self):
        if tools.os_info.is_windows:
            self._build_windows()
        else:
            self._build_autotools()


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
            os.unlink(os.path.join(self.package_folder, "lib", "libxslt_a.lib"))
            os.unlink(os.path.join(self.package_folder, "lib", "libexslt_a.lib"))

        for f in ["libxslt.la", "libexslt.la"]:
            la = os.path.join(self.package_folder, 'lib', f)
            if os.path.isfile(la):
                os.unlink(la)

        tools.rmdir(os.path.join(self.package_folder, "lib", "cmake"))
        tools.rmdir(os.path.join(self.package_folder, "lib", "pkgconfig"))
        tools.rmdir(os.path.join(self.package_folder, "lib", "libxslt-plugins"))
        tools.rmdir(os.path.join(self.package_folder, "share"))

        self.patch_binaries(executables=['xsltproc'])
        self.default_package()


    def package_info(self):
        self.default_package_info()

        self.cpp_info.includedirs.append(os.path.join("include", "libxslt"))

        if tools.os_info.is_windows:
            self.cpp_info.system_libs.append('ws2_32')
        else:
            self.cpp_info.system_libs.append('m')


    def _build_windows(self):
        with tools.chdir(os.path.join(self.source_folder, 'sources', 'win32')):
            with tools.vcvars(self.settings):
                args = ["cscript",
                        "configure.js",
                        "compiler=msvc",
                        "prefix=%s" % self.package_folder,
                        "cruntime=/%s" % self.settings.compiler.runtime,
                        "debug=%s" % ("yes" if self.settings.build_type == "Debug" else "no"),
                        "static=no",
                        'include="%s"' % ";".join(self.deps_cpp_info.include_paths),
                        'lib="%s"' % ";".join(self.deps_cpp_info.lib_paths),
                        'iconv=no',
                        'xslt_debug=no']

                configure_command = ' '.join(args)
                self.run(configure_command)

                def format_libs(package):
                    libs = []
                    for lib in self.deps_cpp_info[package].libs:
                        libname = lib
                        if not libname.endswith('.lib'):
                            libname += '.lib'
                        libs.append(libname)
                    for lib in self.deps_cpp_info[package].system_libs:
                        libname = lib
                        if not libname.endswith('.lib'):
                            libname += '.lib'
                        libs.append(libname)
                    return ' '.join(libs)

                tools.replace_in_file("Makefile.msvc", "libxml2.lib", format_libs("libxml2"))
                tools.replace_in_file("Makefile.msvc", "libxml2_a.lib", format_libs("libxml2"))

                with tools.environment_append(VisualStudioBuildEnvironment(self).vars):
                    self.run("nmake /f Makefile.msvc install")


    def _build_autotools(self):
        env_build = AutoToolsBuildEnvironment(self)

        if tools.os_info.is_macos:
            env_build.link_flags.append(f"-rpath {self.build_folder}/lib")

        args = []
        args.append('--enable-shared')
        args.append('--disable-static')
        args.append('--with-python=no')
        args.append('--prefix=%s' % tools.unix_path(self.package_folder))
        args.append("--with-libxml-src=" + tools.unix_path(self.deps_cpp_info["libxml2"].rootpath))

        env_vars = env_build.vars.copy()
        if tools.os_info.is_linux:
            if 'LD_LIBRARY_PATH' in env_vars:
                env_vars['LD_LIBRARY_PATH'] = ':'.join([env_vars['LD_LIBRARY_PATH']] + self.deps_cpp_info.libdirs)
            else:
                env_vars['LD_LIBRARY_PATH'] = ':'.join(self.deps_cpp_info.libdirs)

        with tools.environment_append(env_vars):
            env_build.configure(args=args, configure_dir=os.path.join(self.source_folder, 'sources'))
            env_build.make(args=["install", "V=1"])
