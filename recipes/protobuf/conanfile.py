# -*- coding: utf-8 -*-
from conans import ConanFile
from conans import tools
from conans import CMake
import shutil
import os


class ConanRecipe(ConanFile):
    python_requires = 'common/1.0.0@mevislab/stable'
    python_requires_extend = 'common.CommonRecipe'

    _cmake = None


    def requirements(self):
        channel = f"@{self.user}/{self.channel}"
        self.requires("zlib/[>=1.2.11]" + channel)


    def _configure_cmake(self):
        if not self._cmake:
            self._cmake = CMake(self)
            #self._cmake.definitions["CMAKE_DEBUG_POSTFIX"] = "d"
            self._cmake.definitions["BUILD_SHARED_LIBS"] = False
            self._cmake.definitions['CMAKE_POSITION_INDEPENDENT_CODE'] = True

            self._cmake.definitions["protobuf_BUILD_TESTS"] = False
            self._cmake.definitions["protobuf_WITH_ZLIB"] = True
            self._cmake.definitions["protobuf_BUILD_PROTOC_BINARIES"] = True

            if self.settings.compiler.get_safe("runtime"):
                self._cmake.definitions["protobuf_MSVC_STATIC_RUNTIME"] = str(self.settings.compiler.runtime) in ["MT", "MTd", "static"]

            self._cmake.configure()
        return self._cmake


    def build(self):
        cmake = self._configure_cmake()
        cmake.build()


    def package(self):
        cmake = self._configure_cmake()
        cmake.install()

        if self.settings.build_type == "Debug":
            bin_path = os.path.join(self.package_folder, "bin")
            if tools.os_info.is_windows:
                shutil.copy2(os.path.join(bin_path, "protocd.exe"), os.path.join(bin_path, "protoc.exe"))
            else:
                shutil.copy2(os.path.join(bin_path, "protocd"), os.path.join(bin_path, "protoc"), follow_symlinks=False)

        tools.rmdir(os.path.join(self.package_folder, "cmake"))
        tools.rmdir(os.path.join(self.package_folder, "lib", "cmake"))
        tools.rmdir(os.path.join(self.package_folder, "lib", "pkgconfig"))

        #self.copy("*.pdb", src="bin", dst="bin")

        #self.patch_binaries()
        self.default_package()
