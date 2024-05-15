import os

from conan.errors import ConanException

from common.python_package_base import PythonPackageBase
from conan.tools.env import Environment
from conan.tools.layout import basic_layout


class PythonPackageTest(PythonPackageBase):
    settings = "os", "compiler", "arch", "build_type"

    def requirements(self):
        self.requires(self.tested_reference_str)

    def layout(self):
        basic_layout(self)

    def test(self):
        with self.install_packages(os.path.join(self.source_folder, "requirements.txt")):
            if not os.path.exists(os.path.join(self.source_folder, "test.py")):
                raise ConanException("test.py not found")

            env = Environment()
            env.append_path("PYTHONPATH", self.site_packages_path)
            with env.vars(self).apply():
                self.run(f"{self.py_command} -B -t -u {os.path.join(self.source_folder, 'test.py')}", env="conanrun")
