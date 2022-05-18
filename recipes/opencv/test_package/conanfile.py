# -*- coding: utf-8 -*-
from conans import ConanFile, tools
import shutil
import os

class TestPackage(ConanFile):
    python_requires = 'common/1.0.0@mevislab/stable'
    python_requires_extend = 'common.CommonTest'

    test_with_environment = tools.os_info.is_linux

    def test(self):
        self.test_args = os.path.join(self.source_folder, "lena.jpg")
        super(TestPackage, self).test()
