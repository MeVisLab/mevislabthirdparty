# -*- coding: utf-8 -*-
from conans import ConanFile
from conans import tools

class TestPackage(ConanFile):
    python_requires = 'common/1.0.0@mevislab/stable'
    python_requires_extend = 'common.CommonTest'


    def system_requirements(self):
        installer = tools.SystemPackageTool()
        packages = []

        if tools.os_info.linux_distro in ["ubuntu", "debian"]:
            packages.append('mesa-common-dev')

        if packages:
            installer.install_packages(packages)

