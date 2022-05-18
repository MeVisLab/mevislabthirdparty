# -*- coding: utf-8 -*-
from conans import ConanFile
import os


class TestPackage(ConanFile):
    python_requires = 'common/1.0.0@mevislab/stable'
    python_requires_extend = 'common.CommonTest'

    def test(self):
        self.check_license()
        self.run("ninja --version")
