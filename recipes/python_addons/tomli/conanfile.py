# -*- coding: utf-8 -*-
from conans import ConanFile
from conans import tools
from conans.errors import ConanException

import os

class ConanRecipe(ConanFile):
    python_requires = 'common/1.0.0@mevislab/stable'
    python_requires_extend = 'common.PythonPackageRecipe'

    def requirements(self):
        self.default_requirements()

        self.requires(f"flit_core/[>=3.7.1]@{self.user}/{self.channel}")


    def build(self):
        # TODO move to common recipe
        py = tools.get_env("MEVIS_PYTHON_CMD", None)
        if not py:
            raise ConanException("environment variable MEVIS_PYTHON_CMD not set.")

        dist = os.path.join(self.build_folder, "dist", self.relative_site_package_folder())
        tools.mkdir(dist)

        os.rename('sources', self.name)

        build_arg = '--global-option=build --global-option=--debug' if self.settings.build_type == 'Debug' else ''
        cmd = f"{py} -m pip install --disable-pip-version-check -v --no-build-isolation --no-deps {build_arg} --target {dist} {os.path.join(self.build_folder, self.name)}"
        self.run(cmd, run_environment=True)


    def package(self):
        self.copy("*", src="dist", dst=".")
