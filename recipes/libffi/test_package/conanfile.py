# -*- coding: utf-8 -*-
from conans import ConanFile
from conans import CMake
from conans import tools

class TestPackage(ConanFile):
    python_requires = 'common/1.0.0@mevislab/stable'
    python_requires_extend = 'common.CommonTest'


    def build(self):
        cmake = CMake(self, build_type="Release" if tools.os_info.is_windows else self.settings.build_type)
        cmake.configure()
        cmake.build()

