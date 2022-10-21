# -*- coding: utf-8 -*-
from conans import ConanFile
from conans.errors import ConanInvalidConfiguration
from conans import tools
import shutil
import os


class ConanRecipe(ConanFile):
    python_requires = 'common/1.0.0@mevislab/stable'
    python_requires_extend = 'common.CommonRecipe'
    no_copy_source = True
    settings = "os"

    exports_sources = ["QtInstallerFramework*.*"]


    def system_requirements(self):
        installer = tools.SystemPackageTool()
        packages = []

        if tools.os_info.linux_distro in ["ubuntu", "debian"]:
            packages.append('libgl1')
            packages.append('libxrender1')
            packages.append('libxkbcommon-x11-0')

        if packages:
            installer.install_packages(packages)


    @property
    def _source_url(self):
        return f"https://download.qt.io/official_releases/qt-installer-framework/{self.version}/{self._source_file}"


    @property
    def _source_file(self):
        if tools.os_info.is_windows:
            return f"QtInstallerFramework-windows-x86-{self.version}.exe"

        if tools.os_info.is_macos:
            return f"QtInstallerFramework-macOS-x86_64-{self.version}.dmg"

        return f"QtInstallerFramework-linux-x64-{self.version}.run"


    @property
    def _source_sha256(self):
        if tools.os_info.is_windows:
            return "85ef9117b66dae00d98553c46a20a44c80eb6e6c8b3f30d51383a95ed2c89c46"

        if tools.os_info.is_macos:
            return "ac1dfd687650e24f29d2b1190fda89d16a1c52069ed844bc44792ed486b2c2e7"

        return "c7784e6deb93d6de77a4794ebd76fcb366936f15678f349f38fab1a89e17cde3"


    def source(self):
        self.download_distfile(self._source_url, self._source_file, self._source_sha256, uncompress=False)


    def build(self):
        file = os.path.join(self.source_folder, self._source_file)

        with tools.environment_append({"QT_QPA_PLATFORM": "minimal"}):
            if tools.os_info.is_windows:
                self.run(f"{file} -c --al -t {self.build_folder}/install install")
            elif tools.os_info.is_macos:
                self.run(f'hdiutil attach {file} -mountpoint {self.build_folder}/dmg')
                installer_location = os.path.join(self.build_folder, 'dmg', 'QtInstallerFramework-mac-x64.app', 'Contents', 'MacOS', 'QtInstallerFramework-mac-x64')
                self.run(f"{installer_location} -c --al -t {self.build_folder}/install install")
                self.run(f'hdiutil detach {self.build_folder}/dmg')
            else:
                os.chmod(file, 0o770)
                self.run(f"{file} -c --al -t {self.build_folder}/install install")

        shutil.copy2(os.path.join('install', 'Licenses', 'LICENSE.GPL3-EXCEPT'), 'LICENSE')


    def package(self):
        self.copy("*", dst="bin", src=os.path.join(self.build_folder, 'install', 'bin'))
        self.default_package()


    def package_info(self):
        self.output.info("Appending PATH env var with: " + os.path.join(self.package_folder, "bin"))
        self.env_info.path.append(os.path.join(self.package_folder, "bin"))
        self.cpp_info.libdirs = []
        self.cpp_info.includedirs = []
