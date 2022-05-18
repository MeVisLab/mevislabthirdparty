# -*- coding: utf-8 -*-
from conans import ConanFile
from conans import tools
import os

class ConanRecipe(ConanFile):
    python_requires = 'common/1.0.0@mevislab/stable'
    python_requires_extend = 'common.PythonPackageRecipe'
    strip_patch = 1

    def source(self):
        self.default_source()

        # docutils is newer than sphinx and so this patch is necessary
        tools.replace_in_file(os.path.join("sources/sphinx", "environment.py"), "kwds['handle_io_errors'] = False", "# kwds['handle_io_errors'] = False")
