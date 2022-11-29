# -*- coding: utf-8 -*-
from conans import ConanFile
from conans import AutoToolsBuildEnvironment
from conans import tools
from conans.errors import ConanInvalidConfiguration
import os


class ConanRecipe(ConanFile):
    python_requires = 'common/1.0.0@mevislab/stable'
    python_requires_extend = 'common.CommonRecipe'

    _autotools = None


    def validate(self):
        if self.settings.os != "Linux":
            raise ConanInvalidConfiguration(f"{self.name} is only supported on Linux")


    def _configure_autotools(self):
        if not self._autotools:
            self._autotools = AutoToolsBuildEnvironment(self)
            with tools.environment_append(self._autotools.vars):
                self.run("touch ltconfig")
                self.run("libtoolize --force --copy --automake")
                self.run("aclocal $ACLOCAL_FLAGS")
                self.run("autoheader")
                self.run("automake --foreign --copy --add-missing")
                self.run("touch depcomp")
                self.run("autoconf")
            self._autotools.configure(args=["--enable-static=no", "--enable-shared=yes", "--disable-python"])
        return self._autotools


    def build(self):
        with tools.chdir('sources'):
            autotools = self._configure_autotools()
            autotools.make()


    def package(self):
        with tools.chdir('sources'):
            autotools = self._configure_autotools()
            autotools.install()

        tools.rmdir(os.path.join(self.package_folder, "bin"))
        tools.rmdir(os.path.join(self.package_folder, "share"))
        tools.rmdir(os.path.join(self.package_folder, "lib", "pkgconfig"))

        for la in ['libasound.la', 'libatopology.la']:
            la_file = os.path.join(self.package_folder, "lib", la)
            if os.path.isfile(la_file):
                os.unlink(la_file)

        self.default_package()


    def package_info(self):
        self.default_package_info()
        self.cpp_info.system_libs = ["dl", "m", "rt", "pthread"]
        self.cpp_info.names['pkg_config'] = 'alsa'
