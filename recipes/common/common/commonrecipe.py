# -*- coding: utf-8 -*-

import os
import io
import glob

from typing import Optional

from conans import ConanFile
from conans import tools
from conans.errors import ConanException
from datetime import datetime

from common import utils
from common import mixin


class CommonRecipe(mixin.CMake, mixin.Debug, mixin.Download, mixin.License, mixin.Metadata, mixin.Patch, mixin.BinaryPatcher, mixin.Sanitize):
    url = "http://mms-build.mevis.lokal"
    settings = "os", "compiler", "arch", "build_type"
    generators = "cmake"
    author = "MeVis Medical Solutions AG"
    exports_sources = ["CMakeLists.txt", "files/*", "patches/*", "sources/*", "LICENSE", "library.mli"]
    default_user = "mevislab"
    default_channel = "stable"
    pure_c = None
    header_only = None
    upstream_version = None
    display_name = None
    generate_cmake = True


    def init(self):
        if not self.conan_data:
            self.output.warn("No 'conandata.yml' found")
        else:
            self.pure_c = self.conan_data.get('type', self.pure_c) in ["c", "pure_c", "header", "header_only"]
            self.header_only = self.conan_data.get('type', self.header_only) in ["header", "header_only", "installer"]
            self.name = self.conan_data.get('name', self.name)
            self.display_name = self.conan_data.get('display_name', self.display_name)
            self.version = self.conan_data.get('version', self.version)
            self.upstream_version = self.conan_data.get('upstream_version', self.upstream_version)
            self.homepage = self.conan_data.get('homepage', self.homepage)
            self.license = self.conan_data.get('license', self.license)
            self.description = self.conan_data.get('description', self.description)


    def package_id(self):
        self.default_package_id()


    def configure(self):
        self.default_configure()


    def source(self):
        self.default_source()


    def package(self):
        self.default_package()


    def package_info(self):
        self.default_package_info()



    #
    # default implementation
    #

    def default_package_id(self):
        if self.header_only:
            self.info.header_only()


    def default_configure(self):
        if self.pure_c:
            try:
                del self.settings.compiler.libcxx
            except:
                pass
            try:
                del self.settings.compiler.cppstd
            except:
                pass


    def default_source(self, rename_from=None, rename_to=None, apply_patches=True, strip=1, fuzz=None, source_data=None):
        """Download the source files as defined in conandata.yml"""

        # some packages have no sources
        if not source_data and (not self.conan_data or not self.conan_data.get('sources', None)):
            return

        srcs_name = "conandata.yml" if not source_data else "source_data"

        # this may be correct, but still worth a warning
        pkg = {}
        if source_data:
            if source_data.get(self.version, None):
                pkg = source_data[self.version]
            else:
                pkg = source_data
        else:
            pkg = self.conan_data.get('sources', {}).get(self.version)

        if not pkg:
            self.output.warn(f"No download information found in {srcs_name}")
            return

        # now we really need a download URL
        url = utils.substitute(self, pkg.get('url', None))
        if not url:
            self.output.error(f"No download url found in {srcs_name}")
            raise ConanException(f"No download url found in {srcs_name}")

        # a checksum should always be specified
        sha256 = pkg.get('sha256', None)
        if sha256 is None:
            self.output.error(f"No sha256 checksum specified in {srcs_name}. In rare cases it is not possible to specify one. In this case please specify 'False'")
            raise ConanException(f"No sha256 checksum specified in {srcs_name}. In rare cases it is not possible to specify one. In this case please specify 'False'")

        # get the filename or try to derive the name from the given URL
        fileName = utils.substitute(self, pkg.get('filename', None))
        if not fileName:
            for ext in ['.tar.gz', '.tar', '.tzb2', '.tar.bz2', '.tgz', '.txz', '.tar.xz', '.zip', '.xz', '.7z', '.exe', '.msi', '.js', '.whl']:
                u = url.lower()
                # sf.net download links look like https://sourceforge.net/projects/ftgl/files/FTGL Source/2.13.1/ftgl-2.13.1.tar.gz/download
                if u.endswith(f"{ext}/download"):
                    u = u[:-len("/download")]

                if u.endswith(ext):
                    fn = u.split('/')[-1]

                    if not fn.endswith(ext):
                        raise ConanException("internal logic error")

                    if not self.version in fn:
                        fn = f"{self.version}-{fn}"

                    n = (self.name[:-len("_installer")] if self.name.endswith("_installer") else self.name).lower()
                    if not n in fn.lower():
                            fn = f"{n}-{fn}"

                    fileName = fn
                    break

        if not fileName:
            self.output.error(f"Could not derive file name from URL 'url'. Please set the 'filename' attribute")
            raise ConanException("Could not derive file name from URL. Please set the 'filename' attribute")

        # are we going to decompress the file?
        uncompress = pkg.get('uncompress', None)
        if uncompress is None:
            if fileName.endswith(('.exe', '.msi', '.jar', '.js', '.whl', '.7z')):
                uncompress = False
                self.output.info("Disable automatic decompression for this file type")
            else:
                uncompress = True
                self.output.info("Enable automatic decompression for this file type")
        else:
            self.output.info("decompression enabled" if uncompress else "decompression disabled")

        # cache the download?
        cache = pkg.get('cache', True)

        if not rename_from:
            rename_from = utils.substitute(self, pkg.get('base_path', None))

        if not rename_to:
            rename_to = utils.substitute(self, pkg.get('target_path', 'sources'))

        baseFolder = rename_to if rename_from == "" else None

        # finally download the file
        self.download_distfile(url=url, sha256=sha256, fileName=fileName, uncompress=uncompress, baseFolder=baseFolder, cache=cache)

        if rename_from:
            os.rename(rename_from, rename_to)

        if apply_patches:
            self.apply_patches(rename_to, strip, fuzz)


    def default_package(self, split_debug=True, sanitize=True):
        if split_debug:
            self.split_debug()

        self.install_metadata()

        if sanitize:
            self.sanitize_package()


    def default_package_info(self):
        self.cpp_info.libs = tools.collect_libs(self)

        cmake_name = self.conan_data.get('cmake_name', None)
        if cmake_name:
            self.cpp_info.names["cmake"] = cmake_name
            self.cpp_info.names["cmake_multi"] = cmake_name
            self.cpp_info.names["cmake_find_package"] = cmake_name
            self.cpp_info.names["cmake_find_package_multi"] = cmake_name
            self.cpp_info.names["cmake_paths"] = cmake_name

        cmake_filename = self.conan_data.get('cmake_filename', None)
        if cmake_filename:
            self.cpp_info.filenames["cmake_find_package"] = cmake_filename
            self.cpp_info.filenames["cmake_find_package_multi"] = cmake_filename

        pkg_config_name = self.conan_data.get('pkg_config_name', None)
        if pkg_config_name:
            self.cpp_info.names["pkg_config"] = pkg_config_name

        # necessary for generating the mli files through a generator:
        mli_name = self.conan_data.get('mli_name', None)
        if mli_name:
            self.cpp_info.set_property("mli_name", mli_name)

        # tell mevislab generator whether to create cmake files for this project
        self.cpp_info.set_property("generate_cmake", self.generate_cmake)
