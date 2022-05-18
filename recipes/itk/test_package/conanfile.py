# -*- coding: utf-8 -*-
from conans import ConanFile
from conans import tools

class TestPackage(ConanFile):
    python_requires = 'common/1.0.0@mevislab/stable'
    python_requires_extend = 'common.CommonTest'
    test_allow_fail = tools.os_info.is_macos
