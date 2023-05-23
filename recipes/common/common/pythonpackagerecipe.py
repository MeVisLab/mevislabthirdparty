# -*- coding: utf-8 -*-
from conans import tools
from conans.errors import ConanException
from common import commonrecipe
import os


class PythonPackageRecipe(commonrecipe.CommonRecipe):
    generators = "pkg_config"
    parallel_make = True
    strip_patch = 0
    generate_cmake = False  # Python add-ons usually don't need a cmake file

    def relative_site_package_folder(self):
        if "python" not in self.deps_cpp_info.deps:
            raise ConanException("Python dependency not found. Does this recipe depend on python?")

        pv = tools.Version(self.deps_cpp_info["python"].version)

        if tools.os_info.is_windows:
            return "Lib/site-packages"

        return f"lib/python{pv.major}.{pv.minor}/site-packages"

    @property
    def prefer_setup_py(self):
        """Returns if setup.py is used even if pyproject.toml exists."""
        return False

    def requirements(self):
        self.default_requirements()

    def default_requirements(self):
        channel = "@{0}/{1}".format(self.user, self.channel)
        self.requires("python/[>=3.9.7]" + channel)

    def build(self):
        self.default_build()

    def default_build(self, args=None, env_vars=None):
        env_vars = env_vars or {}
        py = tools.get_env("MEVIS_PYTHON_CMD")
        if not py:
            raise ConanException("environment variable MEVIS_PYTHON_CMD not set.")

        with tools.vcvars(self.settings) if tools.os_info.is_windows else tools.no_op():
            sitepackage = os.path.join(self.package_folder, self.relative_site_package_folder())
            tools.mkdir(sitepackage)

            cpucount = tools.cpu_count() if self.parallel_make else 1
            build_args = [f"-j {cpucount}"]
            if self.settings.build_type == "Debug":
                build_args += ["-g"]

            if args:
                build_args += args

            python_path = sitepackage
            if tools.get_env("PYTHONPATH"):
                python_path += (os.pathsep + tools.get_env("PYTHONPATH"))
            env_vars.update({
                "SETUPTOOLS_SCM_PRETEND_VERSION": self.version,
                # prevent setuptools_scm from trying to determine the version itself, which fails
                "PKG_CONFIG_PATH": self.build_folder,
                "MAKEFLAGS": ("-j%d" % cpucount),
                "MAKEOPTS": ("-j%d" % cpucount),
                "PYTHONPATH": python_path
            })
            if self.settings.build_type == 'Debug':
                # This utilizes a patch we do to setuptools to work around
                # a shortcoming of pyproject.toml support:
                env_vars["SETUPTOOLS_BUILD_DEBUG"] = "1"

            with tools.environment_append(env_vars):
                with tools.chdir('sources'):
                    if not self.prefer_setup_py and os.path.exists("pyproject.toml"):
                        build_args = [f'--install-option="{arg}"' for arg in build_args]
                        cmd = (f"{py} -m pip install --no-index -v --no-deps --no-build-isolation "
                               f"{' '.join(build_args)} --target {sitepackage}"
                               f" {os.path.join(self.build_folder, 'sources')}")
                        self.run(cmd, run_environment=True)
                    else:
                        self.run(f"{py} setup.py build {' '.join(build_args)}", run_environment=True)
                        self.run(f'{py} setup.py install --verbose --optimize=1 '
                                 f'--skip-build --root={os.sep} --prefix="{self.package_folder}"',
                                 run_environment=True)

    def default_package_info(self):
        super().default_package_info()

        bin_dir = os.path.join(self.package_folder, "bin")
        if os.path.exists(bin_dir):
            self.output.info("Appending PATH env var with: " + bin_dir)
            self.env_info.PATH.append(os.path.join(self.package_folder, "bin"))

        script_dir = os.path.join(self.package_folder, "Scripts")
        if os.path.exists(script_dir):
            self.output.info("Appending PATH env var with: " + script_dir)
            self.env_info.PATH.append(script_dir)

        # MEVIS_PYTHON_SITE_PACKAGES_FOLDER
        self.output.info(
            'Creating MEVIS_PYTHON_SITE_PACKAGES_FOLDER environment variable: %s' % self.relative_site_package_folder())
        self.env_info.MEVIS_PYTHON_SITE_PACKAGES_FOLDER = self.relative_site_package_folder()

        # extend PYTHONPATH with site-package folder of this recipe
        sp_dir = os.path.join(self.package_folder, self.relative_site_package_folder())
        if os.path.exists(sp_dir):
            self.output.info("Appending PYTHONPATH env var with: " + sp_dir)
            self.env_info.PYTHONPATH.append(sp_dir)
