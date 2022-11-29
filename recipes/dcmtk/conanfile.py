# -*- coding: utf-8 -*-
from conans import ConanFile
from conans import tools
from conans import CMake
from pathlib import Path
import glob
import os

class ConanRecipe(ConanFile):
    python_requires = 'common/1.0.0@mevislab/stable'
    python_requires_extend = 'common.CommonRecipe'
    generators = "cmake", "cmake_find_package"

    _modules = [
        "ofstd",     "oflog",        "dcmdata",     "dcmimgle",
        "dcmimage",  "dcmjpeg",      "dcmjpls",     "dcmtls",
        "dcmnet",    "dcmsr",        "dcmsign",     "dcmwlm",
        "dcmqrdb",   "dcmpstat",     "dcmrt",       "dcmiod",
        "dcmfg",     "dcmseg",       "dcmtract",    "dcmpmap"
    ]

    _cmake = None

    def requirements(self):
        channel = f"@{self.user}/{self.channel}"

        self.requires("zlib/[>=1.2.11]" + channel, private=True)
        self.requires("libpng/[>=1.6.37]" + channel)
        self.requires("libxml2/[>=2.9.12]" + channel)
        self.requires("libpng/[>=1.6.37]" + channel)
        self.requires("tiff/[>=4.1.0]" + channel)
        # self.requires("openssl/1.1.1s" + channel)
        self.requires("libjpeg/9e" + channel)

        if not tools.os_info.is_macos:
            self.requires("libiconv/[>=1.16]" + channel)


    def _configure_cmake(self):
        if not self._cmake:
            self.create_cmake_wrapper()
            self._cmake = CMake(self)
            self._cmake.definitions["CMAKE_DEBUG_POSTFIX"] = "d"
            self._cmake.definitions["CMAKE_INSTALL_RPATH_USE_LINK_PATH"] = False
            self._cmake.definitions["BUILD_SHARED_LIBS"] = True
            self._cmake.definitions["BUILD_APPS"] = True
            self._cmake.definitions["DCMTK_WITH_DOXYGEN"] = False
            self._cmake.definitions["DCMTK_USE_FIND_PACKAGE"] = True
            self._cmake.definitions["DCMTK_WITH_THREADS"] = True
            self._cmake.definitions["DCMTK_ENABLE_PRIVATE_TAGS"] = True
            self._cmake.definitions["DCMTK_ENABLE_CXX11"] = True

            self._cmake.definitions["DCMTK_DEFAULT_DICT"] = "builtin"
            self._cmake.definitions["DCMTK_USE_DCMDICTPATH"] = False

            self._cmake.definitions["DCMTK_WIDE_CHAR_FILE_IO_FUNCTIONS"] = True
            self._cmake.definitions["DCMTK_WIDE_CHAR_MAIN_FUNCTION"] = True

            self._cmake.definitions["DCMTK_WITH_XML"] = True
            self._cmake.definitions["DCMTK_WITH_PNG"] = True
            self._cmake.definitions["DCMTK_WITH_TIFF"] = True
            self._cmake.definitions["DCMTK_WITH_ZLIB"] = True
            self._cmake.definitions["DCMTK_WITH_ICU"] = False
            self._cmake.definitions["DCMTK_WITH_OPENSSL"] = False    # FIXME DCMTK has it's own logic to detect openssl, but for some reason it fails to detect openssl 1.1
            self._cmake.definitions["DCMTK_WITH_OPENJPEG"] = False
            self._cmake.definitions["DCMTK_WITH_SNDFILE"] = False
            self._cmake.definitions["DCMTK_WITH_WRAP"] = False
            self._cmake.definitions["DCMTK_WITH_ICONV"] = True

            self._cmake.definitions["DCMTK_MODULES"] = ';'.join(self._modules)

            if not tools.os_info.is_macos:
                lib_postfix = "d" if self.settings.build_type == "Debug" else ""
                iconv_lib_path = self.deps_cpp_info["libiconv"].lib_paths[0]
                iconv_include_path = self.deps_cpp_info["libiconv"].include_paths[0]

                if tools.os_info.is_windows:
                    iconv_lib = iconv_lib_path + f"/libiconv{lib_postfix}.lib"
                    charset_lib = iconv_lib_path + f"/libcharset{lib_postfix}.lib"
                else:
                    iconv_lib = iconv_lib_path + f"/libiconv{lib_postfix}.so"
                    charset_lib = iconv_lib_path + f"/libcharset{lib_postfix}.so"

                self._cmake.definitions["Iconv_LIBRARY"] = iconv_lib
                self._cmake.definitions["Iconv_INCLUDE_DIR"] = iconv_include_path
                self._cmake.definitions["LIBICONV_LIBDIR"] = iconv_include_path

                self._cmake.definitions["LIBCHARSET_LIBRARY"] = charset_lib
                self._cmake.definitions["LIBCHARSET_INCLUDE_DIR"] = iconv_include_path

            self._cmake.configure()

        return self._cmake


    def build(self):
        cmake = self._configure_cmake()
        cmake.build()


    def package(self):
        cmake = self._configure_cmake()
        cmake.install()

        for dll in glob.glob(self.package_folder + "/bin/*.dll"):
            self.copy(Path(dll).stem + ".pdb", src="bin", dst="bin")

        tools.rmdir(os.path.join(self.package_folder, 'lib', 'cmake'))
        tools.rmdir(os.path.join(self.package_folder, 'lib', 'pkgconfig'))
        tools.rmdir(os.path.join(self.package_folder, 'cmake'))
        tools.rmdir(os.path.join(self.package_folder, 'share'))
        tools.rmdir(os.path.join(self.package_folder, 'etc'))

        self.patch_binaries()
        self.default_package()

    def package_info(self):
        self.default_package_info()
        if tools.os_info.is_linux:
            self.cpp_info.system_libs = ['dl']
