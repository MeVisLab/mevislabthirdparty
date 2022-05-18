# -*- coding: utf-8 -*-
from conans import ConanFile
from conans import tools
from conans.errors import ConanException


class TestPackage(ConanFile):
    python_requires = 'common/1.0.0@mevislab/stable'
    python_requires_extend = 'common.CommonTest'

    def test(self):
        self.check_license()

        make = tools.get_env("CONAN_MAKE_PROGRAM", None)
        if not make:
            raise ConanException("environment variable CONAN_MAKE_PROGRAM not set.")

        self.output.info("using make from: " + make)
        self.run('%s --version' % make)
