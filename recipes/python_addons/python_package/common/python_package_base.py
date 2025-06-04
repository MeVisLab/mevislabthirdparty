import os
import sys
from contextlib import contextmanager
from conan.tools.env import VirtualRunEnv
from conan.errors import ConanException
from conan.tools.env.virtualrunenv import runenv_from_cpp_info
from conan.tools.files import copy
from conan import ConanFile


class PythonPackageBase(ConanFile):

    @property
    def has_requirements_txt(self):
        return False

    @property
    def mlab_build_path(self):
        return os.path.join(self.build_folder, "mlab")

    @property
    def site_packages_path(self):
        return os.path.join(self.mlab_build_path, self.relative_site_package_folder())

    @property
    def py_command(self):
        py = self.dependencies["python"].buildenv_info.vars(self).get("MEVIS_PYTHON_CMD")
        if not py:
            raise ConanException("environment variable MEVIS_PYTHON_CMD not set.")
        return (
            os.path.join(self.mlab_build_path, py)
            if sys.platform == "win32"
            else os.path.join(self.mlab_build_path, "bin", py)
        )

    def generate(self):
        # needed to be able to use the Python version with SSL DLLs (for pip)
        copy(self, "*", src=self.recipe_folder, dst=self.mlab_build_path)
        copy(self, "*.dll", src="bin", dst=self.mlab_build_path)
        for dep in ("python", "openssl"):
            src = self.dependencies[dep].package_folder
            copy(self, "*", src=src, dst=self.mlab_build_path)
            copy(self, "*.dll", src=os.path.join(src, "bin"), dst=self.mlab_build_path)

        run_info = runenv_from_cpp_info(self.dependencies["python"], self.settings.get_safe("os"))
        run_info.prepend("PYTHONPATH", self.site_packages_path, os.pathsep)
        run_info.prepend("PATH", os.path.join(self.site_packages_path, "bin"), os.pathsep)

        envvars = run_info.vars(self, scope="build")
        envvars.save_script("build_envs")
        envvars = run_info.vars(self, scope="run")
        envvars.save_script("run_envs")

    @contextmanager
    def install_packages(self, requirements_path):
        """Temporarily install packages needed for build/test"""
        if not self.has_requirements_txt:
            yield
            return

        env = VirtualRunEnv(self)
        env.generate()
        # install a current version of setuptools to be able to handle newer packaging specs
        # TODO: remove this once we have current Python/pip versions
        self.run(
            f"{self.py_command} -m pip install -U setuptools",
            scope="run",
        )
        self.run(
            f"{self.py_command} -m pip install --disable-pip-version-check --no-deps -r "
            f"{requirements_path} -t {self.site_packages_path}",
            scope="run",
        )
        try:
            yield
        finally:
            self.run(
                f"{self.py_command} -m pip uninstall --yes --disable-pip-version-check -r {requirements_path}",
                scope="run",
            )

    def relative_site_package_folder(self):
        if sys.platform == "win32":
            return "Lib/site-packages"

        try:
            pv = self.dependencies["python"].ref.version
        except KeyError:
            raise ConanException("Python dependency not found. Does this recipe depend on python?")

        return f"lib/python{pv.major}.{pv.minor}/site-packages"
