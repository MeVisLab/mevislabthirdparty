import os
from Cython.Build import cythonize

build_dir = os.getcwd()
test_py = os.path.join(os.path.abspath(os.path.dirname(__file__)), "test.py")

cythonize(os.path.relpath(test_py,build_dir), build_dir=build_dir)