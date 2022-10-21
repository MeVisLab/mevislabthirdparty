# -*- coding: utf-8 -*-
from conans import ConanFile
from conans import tools
from conans.errors import ConanException


class TestPackage(ConanFile):
    python_requires = 'common/1.0.0@mevislab/stable'
    python_requires_extend = 'common.CommonTest'


    def test(self):
        self.check_license()

        dep = tools.which("Dependencies.exe")
        if not dep:
            raise ConanException("No instance of Dependencies.exe could be found on %PATH%")

        self.output.info("found Dependencies.exe in: " + dep)
        self.run('Dependencies')
