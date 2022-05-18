import sys
if sys.platform != 'win32':
    # This test does not work on Windows, because the new revised library loading
    # mechanism of Python (since 3.7) ignores the PATH variable. The import will
    # work in MeVisLab, because we use AddDllDirectory to add the required paths.
    import zmq

    print(zmq.pyzmq_version())