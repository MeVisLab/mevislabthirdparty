# -*- coding: utf-8 -*-
from conans import ConanFile
import shutil
import os


class TestPackage(ConanFile):
    python_requires = 'common/1.0.0@mevislab/stable'
    python_requires_extend = 'common.CommonTest'

    def test(self):
        shutil.copy(os.path.join(self.source_folder, "logo.png"), '.')
        self.default_test()
