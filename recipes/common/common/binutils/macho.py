# -*- coding: utf-8 -*-

from typing import cast, Any, AnyStr, IO, Iterator, List, Tuple, Union, Optional
from conans import ConanFile
from conans import tools
from conans.errors import ConanException
from six import StringIO
import re
import os


class MachO(object):
    def __init__(self, conanfile: ConanFile, file: str) -> None:
        self.xcrun = tools.which("xcrun")
        if not self.xcrun:
            raise ConanException("xcrun command not found")

        self.conanfile = conanfile
        self.file = file

        self.__is_binary:Optional[bool] = None
        self.__is_executable :Optional[bool]= None
        self.__install_name_id:Optional[str] = None
        self.__dependencies:Optional[List[str]] = None


    @property
    def install_name_id(self) -> str:
        if self.__install_name_id is not None:
            return self.__install_name_id

        self.__install_name_id = ""

        buf = StringIO()
        ret = self.conanfile.run(f"{self.xcrun} otool -D {self.file}", output=buf, ignore_errors=True)
        if ret == 0:
            l = buf.getvalue().splitlines()
            if len(l) > 1:
                self.__install_name_id = l[1].split(maxsplit=1)[0].strip()

        return cast(str, self.__install_name_id)


    @install_name_id.setter
    def install_name_id(self, id:str):
        self.__install_name_id = None
        self.conanfile.run(f'{self.xcrun} install_name_tool "{self.file}" -id {id}')


    @property
    def is_binary(self) -> bool:
        if self.__is_binary is not None:
            return self.__is_binary

        self.__is_binary = False

        if os.path.exists(self.file):
            buf = StringIO()
            ret = self.conanfile.run(f"{self.xcrun} otool -h {self.file}", output=buf, ignore_errors=True)
            self.__is_binary = ret == 0 and re.search("Mach header", buf.getvalue()) != None

        return cast(bool, self.__is_binary)


    @property
    def is_executable(self) -> bool:
        if self.__is_executable is not None:
            return self.__is_executable

        self.__is_executable = False

        if self.is_binary:
            buf = StringIO()
            ret = self.conanfile.run(f"{self.xcrun} otool -l {self.file}", output=buf, ignore_errors=True)
            self.__is_executable = re.search("Mach LC_MAIN", buf.getvalue()) != None

        return self.__is_executable


    @property
    def dependencies(self) -> List[str]:
        if self.__dependencies is not None:
            return self.__dependencies

        self.__dependencies = []

        if not self.is_binary:
            return self.__dependencies

        buf = StringIO()
        self.conanfile.run(f"{self.xcrun} otool -L {self.file}", output=buf)
        lines = buf.getvalue().splitlines()
        if len(lines) > 1:
            for line in lines[2 if self.install_name_id else 1:]:
                (self.__dependencies.append(line.split()[0].strip()) if len(line) > 0 else None)
        return self.__dependencies


    def change_dependency(self, old:str, new:str):
        self.conanfile.run(f'{self.xcrun} install_name_tool -change "{old}" "{new}" "{self.file}"')
