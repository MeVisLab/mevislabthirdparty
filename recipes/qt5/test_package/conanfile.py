# -*- coding: utf-8 -*-
from conans import ConanFile

class TestPackage(ConanFile):
    python_requires = 'common/1.0.0@mevislab/stable'
    python_requires_extend = 'common.CommonTest'
    test_command = None # compile test only
