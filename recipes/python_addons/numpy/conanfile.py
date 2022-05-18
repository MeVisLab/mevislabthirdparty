# -*- coding: utf-8 -*-
from conans import ConanFile
from conans import tools
from conans.errors import ConanException
import glob
import os

class ConanRecipe(ConanFile):
    python_requires = 'common/1.0.0@mevislab/stable'
    python_requires_extend = 'common.PythonPackageRecipe'
    parallel_make = not tools.os_info.is_windows
    generate_cmake = True
    short_paths = True

    def requirements(self):
        self.default_requirements()
        self.requires(f"cython/[>=0.29.24]@{self.user}/{self.channel}", private=True)


    def package(self):
        self.default_package()

        try:
            srcdir = os.path.dirname(glob.glob('sources/build/*/numpy/core/include/numpy/_numpyconfig.h')[0])
        except:
            self.output.error("Expected Numpy include directory not found")
            raise ConanException("Expected Numpy include directory not found")

        dstdir=os.path.join(self.relative_site_package_folder(), 'numpy', 'core', 'include', 'numpy')
        self.copy('_numpyconfig.h', src=srcdir, dst=dstdir)
        self.copy('__ufunc_api.h', src=srcdir, dst=dstdir)
        self.copy('__multiarray_api.h', src=srcdir, dst=dstdir)


    def package_info(self):
        self.default_package_info()
        self.cpp_info.includedirs.append(os.path.join(self.relative_site_package_folder(), 'numpy', 'core', 'include'))
