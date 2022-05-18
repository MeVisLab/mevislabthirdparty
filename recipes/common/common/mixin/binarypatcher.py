# -*- coding: utf-8 -*-

from common import binutils
from typing import Optional, Union, Any, Sequence
from conans import tools
from pathlib import Path
import os


class BinaryPatcher(object):
    def patch_binaries(self, exclude:Sequence[str]=(), executables:Sequence[str]=()):
        if tools.os_info.is_macos:
            self.patch_macho_id(exclude)
            self.patch_macho_rpath(exclude)
            self.patch_macho_dependencis(exclude)
        elif tools.os_info.is_linux:
            self.patch_elf_rpath(exclude)
            if executables:
                self.patch_elf_executables_rpath(executables)

    def __is_debug(self):
        return self.settings.build_type == "Debug"

    def __is_ignored(self, p:Path, exclude:Sequence[str]):
        if not p.is_file() or p.is_symlink() or p.suffix == ".debug":
            return True
        if exclude:
            name = p.name.split('.')[0]
            if self.__is_debug() and name.endswith('d'):
                name = name[:-1]
            if name in exclude:
                return True
        return False

    def _all_libraries(self, exclude:Sequence[str]=(), folder:Optional[str] = None):
        path = Path(self.package_folder)
        if folder:
            path = path.joinpath(folder)
        pattern = '*.dylib*' if tools.os_info.is_macos else '*.so*'
        return (p for p in path.rglob(pattern) if not self.__is_ignored(p, exclude))
        

    def patch_macho_id(self, exclude:Sequence[str], folder:Optional[str] = None):
        if not tools.os_info.is_macos:
            return

        for p in self._all_libraries(exclude, folder):

            file = os.path.join(p.parent, p.name)

            macho = binutils.MachO(self, file)
            if not macho.is_binary:
                continue

            id = macho.install_name_id
            if not id:
                self.output.info(f"FIX_RUNPATH: LC_ID_DYLIB '@rpath/{p.name}' added")
                macho.install_name_id = f"@rpath/{p.name}"
            elif not id.startswith("@"):
                name = Path(id).name
                self.output.info(f"FIX_RUNPATH: LC_ID_DYLIB changed from '{id}' to '@rpath/{name}'")
                macho.install_name_id = f"@rpath/{name}"


    def patch_macho_rpath(self, exclude:Sequence[str], folder:Optional[str] = None):
        pass


    def patch_macho_dependencis(self, exclude:Sequence[str], folder:Optional[str] = None):
        if not tools.os_info.is_macos:
            return

        # TODO handle executables as well?
        for p in self._all_libraries(exclude, folder):

            file = os.path.join(p.parent, p.name)
            macho = binutils.MachO(self, file)
            if not macho.is_binary:
                continue

            # change LC_LOAD_DYLIB so that relative path use @rpath/<path>
            libs = macho.dependencies
            for lib in libs:
                if lib.startswith("@") or lib.startswith("/"):
                    continue

                self.output.info(f"FIX_RUNPATH: LC_LOAD_DYLIB changed from '{lib}' to '@rpath/{lib}'")
                macho.change_dependency(lib, f"@rpath/{lib}")


    def __remove_absolute_paths(self, paths):
        return [p for p in paths if not p.startswith('/')]


    def patch_elf_rpath(self, exclude:Sequence[str], folder:Optional[str] = None):
        for p in self._all_libraries(exclude, folder):

            if "plugins" in p.parts:
                # nothing to do for Qt plugins
                continue
                
            file = os.path.join(p.parent, p.name)
            self.patch_elf_file_rpath(file, add_paths=["$ORIGIN"])


    # Executables are always assumed to be in the 'bin' folder
    def patch_elf_executables_rpath(self, executables:Sequence[str]):
        binFolder = os.path.join(self.package_folder, "bin")
        for exe in executables:
            file = os.path.join(binFolder, exe)
            if not os.path.exists(file) and self.__is_debug() and os.path.exists(file + 'd'):
                file += 'd'
            self.patch_elf_file_rpath(file, add_paths=["$ORIGIN/../lib"])


    def patch_elf_file_rpath(self, file, add_paths:Sequence[str]=(), remove_absolute_paths=True):
        elf = binutils.Elf(self, file)
        rpath = elf.rpath
        if remove_absolute_paths:
            rpath = self.__remove_absolute_paths(rpath)
        for p in add_paths:
            if not p in rpath:
                rpath.append(p)
        if rpath != elf.rpath:
            self.output.info(f"Setting runpath of {file} to {':'.join(rpath)}")
            elf.set_rpath(rpath)
        
