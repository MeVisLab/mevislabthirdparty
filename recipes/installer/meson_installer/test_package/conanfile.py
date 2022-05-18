# -*- coding: utf-8 -*-
from conans import ConanFile
from conans import Meson
import os


class TestPackage(ConanFile):
    python_requires = 'common/1.0.0@mevislab/stable'
    python_requires_extend = 'common.CommonTest'

    def build(self):
        meson = Meson(self)
        meson.configure(build_folder="build")
        meson.build()


    def test(self):
        self.check_license()
        self.run("meson --version")
        self.run(os.path.join("build", "test_package"), run_environment=True)
