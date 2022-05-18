# -*- coding: utf-8 -*-
from conans import ConanFile
from conans import RunEnvironment
from conans import CMake
from conans import tools
from conans.errors import ConanException


class TestPackage(ConanFile):
    python_requires = 'common/1.0.0@mevislab/stable'
    python_requires_extend = 'common.CommonTest'

    def build(self):
        cmake = CMake(self)
        cmake.configure()
        cmake.build()

    def test(self):
        self.check_license()

        for cmd in ['bison.exe', 'flex.exe', 'win_flex.exe', 'win_bison.exe']:
            if not tools.which(cmd):
                raise ConanException("No instance of {} could be found on %PATH%".format(cmd))
            self.run("%s --version" % cmd)

        with tools.environment_append(RunEnvironment(self).vars):
            cmake = CMake(self)
            cmake.test()
