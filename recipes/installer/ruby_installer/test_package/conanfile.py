# -*- coding: utf-8 -*-
from conans import ConanFile
from conans import tools
from conans.errors import ConanException


class TestPackage(ConanFile):
    python_requires = 'common/1.0.0@mevislab/stable'
    python_requires_extend = 'common.CommonTest'

    def test(self):
        self.check_license()

        ruby = tools.which("ruby.exe")
        if not ruby:
            raise ConanException("No instance of ruby.exe could be found on %PATH%")

        self.output.info("using ruby.exe from: " + ruby)
        self.run('ruby.exe --version')
