# -*- coding: utf-8 -*-
from conans import ConanFile

class TestPackage(ConanFile):
    python_requires = 'common/1.0.0@mevislab/stable'
    python_requires_extend = 'common.PythonPackageTest'

    def imports(self):
        self.copy("*.dll", dst=".", src="bin")
