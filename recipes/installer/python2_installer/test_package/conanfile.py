# -*- coding: utf-8 -*-
from conans import ConanFile
from conans import tools
from conans.errors import ConanException


class TestPackage(ConanFile):
    python_requires = 'common/1.0.0@mevislab/stable'
    python_requires_extend = 'common.CommonTest'

    def test(self):
        self.check_license()

        py2 = tools.which("python2.exe")
        if not py2:
            raise ConanException("No instance of python2.exe could be found on %PATH%")

        self.output.info("using python2.exe from: " + py2)
        self.run('python2.exe -V')
