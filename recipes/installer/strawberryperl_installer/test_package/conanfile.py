# -*- coding: utf-8 -*-
from conans import ConanFile
from conans import tools
from conans.errors import ConanException


class TestPackage(ConanFile):
    python_requires = 'common/1.0.0@mevislab/stable'
    python_requires_extend = 'common.CommonTest'

    def test(self):
        self.check_license()

        perl = tools.which("perl.exe")
        if not perl:
            raise ConanException("No instance of perl.exe could be found on %PATH%")

        self.run("perl --version")
