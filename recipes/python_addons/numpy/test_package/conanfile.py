from pathlib import Path
from conan import ConanFile
from conan.tools.env import Environment


class TestPackage(ConanFile):
    python_requires = "python_package/[>=1.0.0]"
    python_requires_extend = "python_package.PythonPackageTest"

    def test(self):
        env = Environment()
        env.append("CONAN_TEST_DATA", str(Path(self.source_folder) / "load.npy"))
        with env.vars(self).apply():
            super().test()
