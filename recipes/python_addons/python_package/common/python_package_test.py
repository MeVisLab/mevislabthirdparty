import os
import textwrap

from conan.errors import ConanException

from common.python_package_base import PythonPackageBase
from conan.tools.env import Environment
from conan.tools.layout import basic_layout
from conan.tools.files import mkdir, save


class PythonPackageTest(PythonPackageBase):
    settings = "os", "compiler", "arch", "build_type"

    def requirements(self):
        self.requires(self.tested_reference_str)

    def layout(self):
        basic_layout(self)

    def _python_test_dll_directories(self):
        pkg_bin_path = os.path.join(self.site_packages_path, "bin")
        dll_directories = [self.mlab_build_path, self.site_packages_path, pkg_bin_path]
        for dep in self.dependencies.host.values():
            for bindir in dep.cpp_info.bindirs:
                dll_directory = bindir if os.path.isabs(bindir) else os.path.join(dep.package_folder, bindir)
                dll_directories.append(dll_directory)
        return list(dict.fromkeys(os.path.normpath(path) for path in dll_directories))

    def _generate_python_test_sitecustomize(self):
        sitecustomize_dir = os.path.join(self.build_folder, "python_test_startup")
        mkdir(self, sitecustomize_dir)

        sitecustomize = textwrap.dedent(f"""\
            import os
            import sys

            if sys.platform == "win32":
                for directory in {self._python_test_dll_directories()!r}:
                    if os.path.isdir(directory):
                        os.add_dll_directory(directory)
            """)
        save(self, os.path.join(sitecustomize_dir, "sitecustomize.py"), sitecustomize)
        return sitecustomize_dir

    def test(self):
        with self.install_packages(os.path.join(self.source_folder, "requirements.txt")):
            if not os.path.exists(os.path.join(self.source_folder, "test.py")):
                raise ConanException("test.py not found")

            sitecustomize_dir = self._generate_python_test_sitecustomize()
            env = Environment()
            env.prepend_path("PYTHONPATH", sitecustomize_dir)
            env.append_path("PYTHONPATH", self.site_packages_path)
            with env.vars(self).apply():
                self.run(f"{self.py_command} -B -t -u {os.path.join(self.source_folder, 'test.py')}", env="conanrun")
