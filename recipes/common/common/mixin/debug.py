# -*- coding: utf-8 -*-

import os
from pathlib import Path
from typing import Optional
from conans import ConanFile
from conans import tools

class Debug(object):
    def __format_size(self, num:float):
        for unit in ['B','KiB','MiB','GiB']:
            if abs(num) < 1024.0:
                return "%3.1f%s" % (num, unit)
            num /= 1024.0
        return "%.1f%s" % (num, 'TiB')


    def split_debug(self, folder:Optional[str] = None):
        if tools.os_info.is_linux:
            path = Path(os.path.join(self.package_folder, folder)) if folder else Path(self.package_folder)
            for p in path.rglob('*.so*'):
                if p.is_file() and not p.is_symlink() and not p.suffix == ".debug":
                    initial_size = self.__format_size(p.stat().st_size)
                    lib_file = os.path.join(p.parent, p.name)
                    dbg_file = os.path.join(p.parent, p.name + ".debug")

                    self.run(f"objcopy --only-keep-debug --compress-debug-sections {lib_file} {dbg_file}")
                    self.run(f"strip --strip-debug --strip-unneeded {lib_file}")
                    self.run(f"objcopy --add-gnu-debuglink={dbg_file} {lib_file}")

                    new_size = self.__format_size(os.stat(f"{lib_file}").st_size)
                    dbg_size = self.__format_size(os.stat(f"{dbg_file}").st_size)

                    self.output.info(f"Removing debug informations from file {p.name} ({initial_size}). New file size is {new_size}, debug file is {dbg_size}.")
