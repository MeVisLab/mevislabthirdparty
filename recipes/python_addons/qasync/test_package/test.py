import os

os.environ["QT_API"] = "pythonqt"

try:
    import qasync

    _ = qasync
except ModuleNotFoundError as e:
    if e.name != "PythonQt":
        raise e
