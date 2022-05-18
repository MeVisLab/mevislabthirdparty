# -*- coding: utf-8 -*-

import glob
import os
import subprocess
from pathlib import Path
from common import binutils
from typing import Union, List
from conans import ConanFile
from conans import tools
from conans.errors import ConanException

class Sanitize(object):
    sanitizer = {}

    def _sanitizer_disabled(self, key:str) -> bool:
        if not self.sanitizer:
            return False
        return not self.sanitizer.get(key, False)


    def sanitize_package(self: ConanFile):
        self.sanitize_package_contains_license()
        self.sanitize_package_adhere_license()
        self.sanitize_package_msvc_runtime()
        self.sanitize_package_opengl()
        self.sanitize_package_cmake()
        self.sanitize_package_pkgconfig()
        self.sanitize_package_symlinks()
        self.sanitize_package_binaries()


    def sanitize_package_license(self: ConanFile):
        if self._sanitizer_disabled('license'):
            self.output.info("sanitize_package_license: disabled")
            return

        self.sanitize_package_contains_license()
        self.sanitize_package_adhere_license()


    def sanitize_package_adhere_license(self: ConanFile, allow=None):
        if "GPL" in self.license:
            if self._sanitizer_disabled('adhere_license'):
                self.output.info("sanitize_package_adhere_license: disabled")
                return

            self.output.info("sanitize_package_adhere_license: checking (L)GPL package for existing static libraries...")

            if tools.os_info.is_windows:
                allow = [] if not allow else [allow] if isinstance(allow, str) else allow
                dlls = [Path(item).stem for item in glob.glob(self.package_folder + "/**/*.dll")]
                libs = [Path(item).stem for item in glob.glob(self.package_folder + "/**/*.lib")]
                res = [item for item in libs if item not in dlls and item not in allow]

                if res:
                    self.output.error("Found static libary in LGPL licensed package: " + ", ".join(res))
                    raise ConanException("Found static libary in LGPL licensed package")
            else:
                res = glob.glob(self.package_folder + "/**/*.a", recursive=True)
                if res:
                    self.output.error("Found static libary in LGPL licensed package: " + ", ".join(res))
                    raise ConanException("Found static libary in LGPL licensed package")


    def sanitize_package_contains_license(self:ConanFile):
        if self._sanitizer_disabled('contains_license'):
            self.output.info("sanitize_package_contains_license: disabled")
            return

        self.output.info("sanitize_package_contains_license: checking presence of a LICENSE file...")

        licenseFile = os.path.join(self.package_folder, 'licenses', 'LICENSE')
        if not os.path.isfile(licenseFile):
            if self.license.lower() == 'publicdomain':
                self.output.warn("No LICENSE file found.")
                self.output.info("The project is under 'Public Domain', but a LICENSE file is nevertheless recommended.")
            else:
                self.output.error("Package LICENSE file not found!")
                raise ConanException("LICENSE file not found!")


    def sanitize_package_msvc_runtime(self:ConanFile):
        if not tools.os_info.is_windows:
            return

        if self._sanitizer_disabled('msvc_runtime'):
            self.output.info("sanitize_package_msvc_runtime: disabled")
            return

        self.output.info("sanitize_package_msvc_runtime: checking for MSVC runtime artifacts...")

        for pattern in ["msvc*.dll", "concrt*.dll", "vccorlib*.dll", "vcruntime*.dll", "vcamp*.dll", "vcomp*.dll", "vc_redist*.exe", "vcredist_*.exe"]:
            res = glob.glob(self.package_folder + f"/**/{pattern}")
            if res:
                self.output.error("Found MSVC runtime libaries in package: " + ", ".join(res))
                raise ConanException("Found MSVC runtime libaries in package")


    def sanitize_package_opengl(self:ConanFile):
        if not tools.os_info.is_linux:
            return

        if self._sanitizer_disabled('opengl'):
            self.output.info("sanitize_package_opengl: disabled")
            return

        self.output.info("sanitize_package_opengl: checking for libraries linking libopengl.so instead of libGL.so...")

        for p in Path(self.package_folder).rglob('*.so*'):
            if p.is_file() and not p.is_symlink() and not p.suffix == ".debug":
                r = subprocess.run(["objdump", "-p", os.path.join(p.parent, p.name)], capture_output=True)
                if r.returncode != 0:
                    self.output.error("Failed to run objdump: " + r.stderr.decode())
                    raise ConanException("Failed to run objdump")

                for line in r.stdout.decode().splitlines():
                    if line.strip().startswith("NEEDED"):
                        if "libopengl.so" in line.lower():
                            self.output.error(f"{p.name} links to libopengl.so instead of libGL.so")
                            raise ConanException(f"{p.name} links to libopengl.so instead of libGL.so")


    def sanitize_package_cmake(self:ConanFile):
        if self._sanitizer_disabled('cmake'):
            self.output.info("sanitize_package_cmake: disabled")
            return

        self.output.info("sanitize_package_cmake: checking for cmake files...")

        for pattern in ["*.cmake", "*.cmake.in", "CMakeLists.txt"]:
            res = glob.glob(self.package_folder + f"/**/{pattern}", recursive=True)
            if res:
                self.output.info("A typical package should not ship it's own CMake (CMakeLists.txt, *.cmake) files.")
                self.output.error("Found cmake files in package: " + ", ".join(res))
                raise ConanException("Found cmake files in package")


    def sanitize_package_pkgconfig(self:ConanFile):
        if self._sanitizer_disabled('pkgconfig'):
            self.output.info("sanitize_package_pkgconfig: disabled")
            return

        self.output.info("sanitize_package_pkgconfig: checking for pkgconfig files...")

        for pattern in ["*.pc", "*.la"]:
            res = glob.glob(self.package_folder + f"/**/{pattern}", recursive=True)
            if res:
                self.output.info("A typical package should not ship it's own pkg-config (*.pc, *.la) files.")
                self.output.error("Found pkgconfig files in package: " + ", ".join(res))
                raise ConanException("Found pkgconfig files in package")


    def sanitize_package_symlinks(self:ConanFile):
        if tools.os_info.is_windows:
            return

        if self._sanitizer_disabled('symlinks'):
            self.output.info("sanitize_package_symlinks: disabled")
            return

        self.output.info("sanitize_package_symlinks: checking for broken symlinks...")

        for it in glob.iglob(self.package_folder + "/**", recursive=True):
            if os.path.islink(it) and not os.path.exists(it):
                self.output.error(f"Found broken symlink: {it}")
                raise ConanException(f"Found broken symlink: {it}")


    def sanitize_package_binaries(self:ConanFile):
        if self._sanitizer_disabled('binaries'):
            self.output.info("sanitize_package_binaries: disabled")
            return

        self.sanitize_package_macho_id()
        self.sanitize_package_macho_dependencies()


    def sanitize_package_macho_id(self:ConanFile):
        if not tools.os_info.is_macos:
            return

        if self._sanitizer_disabled('macho_id'):
            self.output.info("sanitize_package_macho_id: disabled")
            return

        self.output.info("sanitize_package_macho_id: checking LC_ID_DYLIB...")

        for p in Path(self.package_folder).rglob('*.dylib*'):
            if p.is_file() and not p.is_symlink() and not p.suffix == ".dSYM":
                r = subprocess.run(["objdump", "--macho", "--dylib-id", os.path.join(p.parent, p.name)], capture_output=True)
                if r.returncode != 0:
                    self.output.error("Failed to run objdump: " + r.stderr.decode())
                    raise ConanException("Failed to run objdump")

                for line in r.stdout.decode().splitlines()[1:]:
                    line = line.strip()
                    if not line.startswith("@"):
                        self.output.error(f"{p.name}: invalid/absolute LC_ID_DYLIB '{line}' found")
                        raise ConanException(f"{p.name} invalid/absolute LC_ID_DYLIB '{line}' found")


    def sanitize_package_macho_dependencies(self:ConanFile):
        if not tools.os_info.is_macos:
            return

        if self._sanitizer_disabled('macho_dependencies'):
            self.output.info("sanitize_package_macho_dependencies: disabled")
            return

        self.output.info("sanitize_package_macho_dependencies: checking LC_LOAD_DYLIB...")

        for p in Path(self.package_folder).rglob('*.dylib*'):
            file = os.path.join(p.parent, p.name)
            macho = binutils.MachO(self, file)
            if not macho.is_binary:
                continue

            for lib in macho.dependencies:
                if lib.startswith("@"):
                    continue

                if lib.startswith("/usr/"):
                    continue

                if lib.startswith("/System/Library/"):
                    continue

                self.output.error(f"{p.name}: invalid/absolute LC_LOAD_DYLIB '{lib}' found")
                raise ConanException(f"{p.name} linvalid/absolute LC_LOAD_DYLIB '{lib}' found")
