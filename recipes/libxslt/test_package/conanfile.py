# -*- coding: utf-8 -*-
from conans import ConanFile
import shutil
import os

class TestPackage(ConanFile):
    python_requires = 'common/1.0.0@mevislab/stable'
    python_requires_extend = 'common.CommonTest'

    test_with_environment = True

    def imports(self):
        super(TestPackage, self).imports()
        self.copy("*.dll", dst=".", src="bin")
        self.copy("*.dylib*", dst=".", src="lib")
        self.copy("*.so*", dst=".", src="lib")


    def test(self):
        self.test_args = [os.path.join(self.source_folder, "example.xsl"), os.path.join(self.source_folder, "example.xml")]
        super(TestPackage, self).test()
