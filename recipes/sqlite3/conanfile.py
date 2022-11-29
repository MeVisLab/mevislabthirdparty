# -*- coding: utf-8 -*-
from conans import ConanFile
from conans import tools
from conans import CMake
import os


class ConanRecipe(ConanFile):
    python_requires = 'common/1.0.0@mevislab/stable'
    python_requires_extend = 'common.CommonRecipe'

    _cmake = None


    def build_requirements(self):
        channel = "@{0}/{1}".format(self.user, self.channel)
        self.build_requires("zlib/[>=1.2.11]" + channel)


    def _configure_cmake(self):
        if not self._cmake:
            self._cmake = CMake(self)
            self._cmake.definitions["CMAKE_DEBUG_POSTFIX"] = "d"
            self._cmake.definitions["BUILD_SHARED_LIBS"] = True
            self._cmake.definitions["HAVE_LOCALTIME_R"] = True
            self._cmake.definitions["HAVE_POSIX_FALLOCATE"] = True

            if self.settings.os == "Windows":
                self._cmake.definitions["HAVE_LOCALTIME_R"] = False
                self._cmake.definitions["HAVE_POSIX_FALLOCATE"] = False

            if self.settings.os == "Macos":
                self._cmake.definitions["HAVE_POSIX_FALLOCATE"] = False

            self._cmake.configure()
        return self._cmake


    def build(self):
        cmake = self._configure_cmake()
        cmake.build()


    def package(self):
        header = tools.load(os.path.join("sources", "sqlite3.h"))
        license_content = header[3:header.find("***", 1)]
        tools.save("LICENSE", license_content)
        self.copy("LICENSE", dst="licenses")

        cmake = self._configure_cmake()
        cmake.install()

        self.copy("*.pdb", src="bin", dst="bin")

        self.patch_binaries()
        self.default_package()


    def package_info(self):
        self.default_package_info()
        if self.settings.os == "Linux":
            self.cpp_info.system_libs.extend(["m", "dl", "pthread"])
