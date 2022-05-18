# -*- coding: utf-8 -*-

from typing import cast, Any, AnyStr, IO, Iterator, List, Tuple, Union, Optional
from conans import tools, ConanFile
from conans.errors import ConanException
from six import StringIO
import os

patchelf: str = None

class Elf(object):
    def __init__(self, conanfile: ConanFile, file: str) -> None:
        global patchelf
        self.conanfile = conanfile
        self.file = file

        self.__is_elf:Optional[bool] = None
        self.__rpath:Optional[str] = None

        if patchelf is None:
            patchelf = tools.which("patchelf")
            if not patchelf:
                raise ConanException("patchelf command not found")


    @property
    def is_elf(self) -> bool:
        if self.__is_elf is not None:
            return self.__is_elf

        self.__is_elf = False

        if os.path.exists(self.file):
            buf = StringIO()
            ret = self.conanfile.run(f"{patchelf} {self.file}", output=buf, ignore_errors=True)
            self.__is_elf = (ret == 0)

        return self.__is_elf


    @property
    def rpath(self) -> List[str]:
        if self.__rpath is not None:
            return self.__rpath

        self.__rpath = []

        buf = StringIO()
        self.conanfile.run(f"{patchelf} --print-rpath {self.file}", output=buf)
        values = buf.getvalue().split(':')
        self.__rpath = [v.strip() for v in values if v.strip()]
        return self.__rpath


    def set_rpath(self, rpath: List[str]):
        self.__rpath = rpath
        rpath = ":".join(rpath).replace('$', r'\$')
        self.conanfile.run(f'{patchelf} --set-rpath "{rpath}" "{self.file}"')
