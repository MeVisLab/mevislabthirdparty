# -*- coding: utf-8 -*-
from conans import ConanFile
from conans import tools
from conans.errors import ConanException


class TestPackage(ConanFile):
    python_requires = 'common/1.0.0@mevislab/stable'
    python_requires_extend = 'common.CommonTest'


    def test(self):
        self.check_license()

        nasm = tools.which("nasm.exe")
        if not nasm:
            raise ConanException("No instance of nasm.exe could be found on %PATH%")

        self.output.info("using nasm.exe from: " + nasm)
        self.run('nasm --version')
