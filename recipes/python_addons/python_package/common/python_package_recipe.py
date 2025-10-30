import os
import sys
from pathlib import Path

from common.python_package_base import PythonPackageBase
from conan.tools.cmake import cmake_layout
from conan.tools.env import Environment
from conan.tools.files import mkdir, chdir, copy
from conan.errors import ConanException

if sys.version_info >= (3, 11):
    import tomllib as tomli
else:
    import tomli


class PythonPackageRecipe(PythonPackageBase):
    url = "http://mms-build.mevis.lokal"
    settings = "os", "compiler", "arch", "build_type"
    author = "MeVis Medical Solutions AG"
    exports_sources = "patches/*"
    strip_patch = 0
    parallel_make = True

    def layout(self):
        cmake_layout(self, src_folder="src")

    @property
    def prefer_setup_py(self):
        """Returns if setup.py is used even if pyproject.toml exists."""
        return False

    def requirements(self):
        self.default_requirements()
        self.python_requirements()

    def python_requirements(self):
        pass

    def default_requirements(self):
        self.requires("python/[>=3.13]")

    @property
    def has_requirements_txt(self):
        requirements_path = os.path.join(os.path.dirname(self.source_folder), "requirements.txt")
        return os.path.exists(requirements_path)

    def build_environment(self):
        env = Environment()
        env.define("SETUPTOOLS_SCM_PRETEND_VERSION", self.version)

        # prevent setuptools_scm from trying to determine the version itself, which fails
        env.define("PKG_CONFIG_PATH", self.folders.generators_folder)

        cpu_count = os.cpu_count() if self.parallel_make else 1
        env.define("MAKEFLAGS", f"-j{cpu_count}")
        env.define("MAKEOPTS", f"-j{cpu_count}")

        if self.settings.get_safe("build_type") == "Debug":
            # This utilizes a patch we do to setuptools to work around
            # a shortcoming of pyproject.toml support:
            env.define("SETUPTOOLS_BUILD_DEBUG", "1")

        return env

    def build(self):
        self.default_build()

    def pyproject_build(self, backend, build_args, config_settings, env, site_package):
        extra_pip_args = "--no-build-isolation --disable-pip-version-check --use-deprecated=legacy-certs"
        if backend == "setuptools.build_meta":
            self.run(f"{self.py_command} setup.py build {' '.join(build_args)}", env=env)
            cmd = f"{self.py_command} -m pip install -v --no-deps {extra_pip_args} --target {site_package} {self.source_folder}"
            self.run(cmd, env=env)
        else:
            # we assume Python only
            cmd = (
                f"{self.py_command} -m pip install -v --no-deps {extra_pip_args}"
                f" {''.join(map(lambda x: ' -C ' +x, config_settings))}"
                f" --target {site_package}"
                f" {self.source_folder}"
            )
            self.run(cmd, env=env)
        # the recipe needs to implement pyproject_build itself if it needs special handling

    def default_build(self, args=None, env="", config_settings=None):
        with self.install_packages(os.path.join(os.path.dirname(self.source_folder), "requirements.txt")):
            site_package = os.path.join(self.build_folder, self.relative_site_package_folder())
            mkdir(self, site_package)

            cpu_count = os.cpu_count() if self.parallel_make else 1
            build_args = [f"-j {cpu_count}"]
            if self.settings.get_safe("build_type") == "Debug":
                build_args += ["-g"]
            if args:
                build_args += args

            with chdir(self, self.source_folder):
                use_pyproject = not self.prefer_setup_py and os.path.exists("pyproject.toml")
                backend = ""
                if use_pyproject:
                    with open("pyproject.toml", "rb") as f:
                        toml_dict = tomli.load(f)
                        try:
                            backend = toml_dict["build-system"]["build-backend"]
                        except KeyError:
                            raise ConanException(f"Missing build backend in pyproject.toml")

                with self.build_environment().vars(self).apply():
                    if use_pyproject:
                        if config_settings is None:
                            config_settings = []
                        elif not isinstance(config_settings, (tuple, list)):
                            config_settings = [config_settings]
                        self.pyproject_build(backend, build_args, config_settings, env, site_package)
                    else:
                        self.run(f"{self.py_command} setup.py build {' '.join(build_args)}", env=env)
                        self.run(
                            f"{self.py_command} setup.py install --verbose --optimize=1 "
                            f'--skip-build --root={os.sep} --prefix="{self.build_folder}"',
                            env=env,
                        )

    @property
    def license_path(self):
        raise ConanException("License path is not configured")

    def default_package(self):
        copy(self, "Lib/*", src=self.build_folder, dst=self.package_folder, excludes="*__pycache__*")
        if not copy(
            self,
            self.license_path,
            src=self.source_folder,
            dst=os.path.join(self.package_folder, "licenses"),
            keep_path=False,
        ):
            raise ConanException("No license found")
        else:
            # Also copy license into .egg-info folder, so that the PythonPackageHelper tool doesn't complain
            # when creating the .mlinfo again
            egg_info_folders = list(
                (Path(self.package_folder) / self.relative_site_package_folder()).glob("*.egg-info")
            )
            if len(egg_info_folders) >= 1:
                copy(self, "*", src=Path(self.package_folder) / "licenses", dst=egg_info_folders[0], keep_path=False)

    def package(self):
        self.default_package()

    def package_info(self):
        site_packages_path = os.path.join(self.package_folder, self.relative_site_package_folder())
        self.cpp_info.set_property("cmake_find_mode", "none")
        self.cpp_info.includedirs = []
        self.buildenv_info.append_path("PYTHONPATH", site_packages_path)
        self.runenv_info.append_path("PYTHONPATH", site_packages_path)
