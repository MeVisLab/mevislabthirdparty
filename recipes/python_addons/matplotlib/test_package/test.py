import os
import sys

if sys.platform == 'win32':
    os.add_dll_directory(os.getcwd())

import matplotlib