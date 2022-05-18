# -*- coding: utf-8 -*-
from conans import ConanFile
from conans import tools


class ConanRecipe(ConanFile):
    python_requires = 'common/1.0.0@mevislab/stable'
    python_requires_extend = 'common.PythonPackageRecipe'
    parallel_make = not tools.os_info.is_windows
    short_paths = True
