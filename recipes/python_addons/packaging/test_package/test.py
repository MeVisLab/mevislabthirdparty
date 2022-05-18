import packaging
from packaging.version import Version

assert Version("1.0rc1").major == 1
assert Version("1.0rc1").minor == 0

print(Version("1.0rc1"))