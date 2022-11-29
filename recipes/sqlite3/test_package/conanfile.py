# -*- coding: utf-8 -*-
from conans import ConanFile
from conans import CMake

class TestPackage(ConanFile):
    python_requires = 'common/1.0.0@mevislab/stable'
    python_requires_extend = 'common.CommonTest'

    def build(self):
        cmake = CMake(self)
        cmake.definitions['EXPECTED_SQLITE3_VERSION'] = f"{self.deps_cpp_info['sqlite3'].version}"
        cmake.configure()
        cmake.build()
