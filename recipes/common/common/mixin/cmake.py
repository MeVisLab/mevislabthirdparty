# -*- coding: utf-8 -*-

import io
import os
from typing import Optional

from conans import ConanFile


class CMake(object):
    def create_cmake_wrapper(self:ConanFile, path:Optional[str]=None, add_subdirectory:str='sources', cxx_std:Optional[str]=None, *args):
        path = self.source_folder if not path else os.path.join(self.source_folder, path)
        with io.open(os.path.join(path, 'CMakeLists.txt'), mode='w', encoding='utf8') as f:
            print("cmake_minimum_required(VERSION 3.19)", file=f)
            print(f"project(conan-wrapper-{self.name})\n", file=f)
            print("include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)", file=f)
            print("conan_basic_setup()\n", file=f)
            print("set(_UNUSED ${CMAKE_EXPORT_NO_PACKAGE_REGISTRY} ${CMAKE_INSTALL_BINDIR} ${CMAKE_INSTALL_DATAROOTDIR} ${CMAKE_INSTALL_INCLUDEDIR} ${CMAKE_INSTALL_LIBDIR} ${CMAKE_INSTALL_LIBEXECDIR} ${CMAKE_INSTALL_OLDINCLUDEDIR} ${CMAKE_INSTALL_SBINDIR} ${CMAKE_DEBUG_POSTFIX})\n", file=f)

            if cxx_std:
                print(f"set(CMAKE_CXX_STANDARD {cxx_std})", file=f)
                print(f"set(CMAKE_CXX_STANDARD_REQUIRED ON)\n", file=f)

            for x in args:
                print(x, file=f)

            print(f"add_subdirectory({add_subdirectory})", file=f)
