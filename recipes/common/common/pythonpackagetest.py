# -*- coding: utf-8 -*-
from conans import ConanFile
from conans import tools
from conans.errors import ConanException
import os

class PythonPackageTest(ConanFile):
    settings = "os", "compiler", "arch", "build_type"
    default_user = "mevislab"
    default_channel = "stable"

    test_with_environment = True


    def test(self):
        self.default_test()


    def default_test(self):
        py = tools.get_env("MEVIS_PYTHON_CMD", None)
        if not py:
            raise ConanException("environment variable MEVIS_PYTHON_CMD not set.")

        testfile = os.path.join(self.source_folder, "test.py")
        if not os.path.exists(testfile):
            raise ConanException("test.py not found")

        self.run(f"{py} -B -t -u {testfile}", run_environment=self.test_with_environment)
