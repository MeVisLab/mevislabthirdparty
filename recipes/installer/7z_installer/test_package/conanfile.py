# -*- coding: utf-8 -*-
from conans import ConanFile
from conans import tools
from conans.errors import ConanException


class TestPackage(ConanFile):
    python_requires = 'common/1.0.0@mevislab/stable'
    python_requires_extend = 'common.CommonTest'

    def test(self):
        self.check_license()

        szip = tools.which("7za.exe")
        if not szip:
            raise ConanException("No instance of 7za.exe could be found on %PATH%")

        self.output.info("using 7za.exe from: " + szip)
        self.run('7za.exe -h')
