# -*- coding: utf-8 -*-
from conans import ConanFile
from conans import AutoToolsBuildEnvironment
from conans import tools
import os

class ConanRecipe(ConanFile):
    python_requires = 'common/1.0.0@mevislab/stable'
    python_requires_extend = 'common.CommonRecipe'

    settings = "os", "compiler", "arch"

    def package_id(self):
        # Deleting the entire self.info.settings.compiler is not correct.
        # Imagine this package is built with GCC x and GCC y, where GCC x is
        # based on Ubuntu 20.04, but GCC y is based on Ubuntu 21.04. If the
        # whole self.info.settings.compiler was deleted, both packages will
        # result in the same ID. Now, if the package was first built on
        # Ubuntu 21.04, that is also the package for all other systems.
        # However, it is not guaranteed to run on other, especially older,
        # Linux distributions - e.g. because it requires a newer glibc.
        # So you either have to make sure that such a package is always built
        # on the oldest available platform, or you build it on all platforms -
        # but then you must not delete self.info.settings.compiler.
        del self.info.settings.build_type
        if self.settings.compiler == "Visual Studio":
            del self.info.settings.compiler.runtime


    def build(self):
        if self.settings.os == "Windows":
            # asking for python3 on Windows returns a 'fake' executable that once executed prints:
            # "Python was not found but can be installed from the Microsoft Store: [...]" *gr*
            python = tools.which('python')
        else:
            python = tools.which('python3')
            if not python:
                python = tools.which('python')

        with tools.chdir("sources"):
            if self.settings.os == "Windows":
                with tools.vcvars(self.settings, filter_known_paths=False):
                    self.run('"%s" configure.py --bootstrap' % python)
            else:
                cxx = os.environ.get("CXX", "g++")
                if self.settings.os == "Linux":
                    cxx += " -m64"
                env_build = AutoToolsBuildEnvironment(self)
                env_build_vars = env_build.vars
                env_build_vars.update({'CXX': cxx})
                with tools.environment_append(env_build_vars):
                    self.run("%s configure.py --bootstrap" % python)


    def package(self):
        self.copy(pattern="ninja*", dst="bin", src="sources")
        self.default_package()


    def package_info(self):
        # ensure ninja is executable
        if self.settings.os in ["Linux", "Macos"]:
            name = os.path.join(self.package_folder, "bin", "ninja")
            os.chmod(name, os.stat(name).st_mode | 0o111)
        self.env_info.PATH.append(os.path.join(self.package_folder, "bin"))
        self.env_info.CONAN_CMAKE_GENERATOR = "Ninja"
