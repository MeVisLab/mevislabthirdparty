import os
import sys

if sys.platform == "win32":
    for p in os.getenv("PATH").split(os.pathsep):
        if os.path.exists(p):
            os.add_dll_directory(p)

os.environ["QT_API"] = "pythonqt"

try:
    import qasync
except ModuleNotFoundError as e:
    if e.name != 'PythonQt':
        raise e
