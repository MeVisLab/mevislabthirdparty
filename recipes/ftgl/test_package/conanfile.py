# -*- coding: utf-8 -*-
from conans import ConanFile
from conans import tools
import os

class TestPackage(ConanFile):
    python_requires = 'common/1.0.0@mevislab/stable'
    python_requires_extend = 'common.CommonTest'
    test_allow_fail = tools.os_info.is_windows or tools.os_info.is_macos

    def test(self):
        self.test_args = os.path.join(self.source_folder, "OpenSans-Bold.ttf")
        super(TestPackage, self).test()
