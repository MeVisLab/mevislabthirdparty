import os
import sys

if sys.platform == 'win32':
    for p in os.getenv("PATH").split(os.pathsep):
        if os.path.exists(p):
            os.add_dll_directory(p)

from PIL import Image
