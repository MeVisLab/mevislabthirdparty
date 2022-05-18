# -*- coding: utf-8 -*-
from conans import ConanFile
from conans import tools
from conans import AutoToolsBuildEnvironment
import shutil
import os


class ConanRecipe(ConanFile):
    python_requires = 'common/1.0.0@mevislab/stable'
    python_requires_extend = 'common.CommonRecipe'

    exports_sources = ["Win32.Mak", "LICENSE", "patches/*"]


    def source(self):
        self.default_source()

        # change rpath
        tools.replace_in_file("sources/configure", '-install_name \$rpath/\$soname', '-install_name \$soname')


    def build(self):
        if self.settings.compiler == "Visual Studio":
            self._build_nmake()
        else:
            self._build_configure()


    def package(self):
        if self.settings.compiler == "Visual Studio":
            for filename in ['jpeglib.h', 'jerror.h', 'jconfig.h', 'jmorecfg.h']:
                self.copy(pattern=filename, dst="include", src="sources", keep_path=False)
            self.copy(pattern="*.lib", dst="lib", src="sources", keep_path=False)
            self.copy(pattern="*.dll", dst="lib", src="sources", keep_path=False)

        tools.rmdir(os.path.join(self.package_folder, 'lib', 'pkgconfig'))
        tools.rmdir(os.path.join(self.package_folder, 'share'))
        if not tools.os_info.is_windows:
            tools.rmdir(os.path.join(self.package_folder, "bin"))

        if os.path.exists(os.path.join(self.package_folder, "lib", "libjpeg.la")):
            os.unlink(os.path.join(self.package_folder, "lib", "libjpeg.la"))

        self.patch_binaries()
        self.default_package()


    def _build_nmake(self):
        if self.settings.compiler == 'Visual Studio':
            shutil.copy('Win32.Mak', os.path.join("sources", 'Win32.Mak'))
        with tools.chdir("sources"):
            shutil.copy('jconfig.vc', 'jconfig.h')
            vcvars_command = tools.vcvars_command(self.settings)
            params = "nodebug=1" if self.settings.build_type == 'Release' else ""

            # set flags directly in makefile.vc
            # cflags are critical for the library.
            # ldflags and ldlibs are only for binaries
            if self.settings.compiler.runtime in ["MD", "MDd"]:
                tools.replace_in_file('makefile.vc', '(cvars)', '(cvarsdll)')
                tools.replace_in_file('makefile.vc', '(conlibs)', '(conlibsdll)')
            else:
                tools.replace_in_file('makefile.vc', '(cvars)', '(cvarsmt)')
                tools.replace_in_file('makefile.vc', '(conlibs)', '(conlibsmt)')
            self.run('%s && nmake -f makefile.vc %s libjpeg.lib' % (vcvars_command, params))


    def _build_configure(self):
        env_build = AutoToolsBuildEnvironment(self, win_bash=self.settings.os == 'Windows')
        env_build.fpic = True
        config_args = ["--enable-shared=yes", "--enable-static=no"]
        if self.settings.build_type == 'Debug':
            config_args.append("--program-suffix=d")

        prefix = os.path.abspath(self.package_folder)
        if self.settings.os == 'Windows':
            prefix = tools.unix_path(prefix)
        config_args.append("--prefix=%s" % prefix)

        env_build.configure(configure_dir="sources", args=config_args)
        env_build.make()
        env_build.install()
