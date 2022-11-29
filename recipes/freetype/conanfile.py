# -*- coding: utf-8 -*-
from conans import ConanFile
from conans import CMake
from conans import tools
from conans.errors import ConanInvalidConfiguration
import os

class ConanRecipe(ConanFile):
    python_requires = 'common/1.0.0@mevislab/stable'
    python_requires_extend = 'common.CommonRecipe'

    _cmake = None


    def validate(self):
        if tools.os_info.is_linux:
            raise ConanInvalidConfiguration(f"{self.name} is not supported on Linux. Please use the one provided by the system.")


    def requirements(self):
        channel = "@{0}/{1}".format(self.user, self.channel)
        self.requires("zlib/[>=1.2.11]" + channel)
        self.requires("bzip2/[>=1.0.8]" + channel)
        self.requires("libpng/[>=1.6.36]" + channel)


    def source(self):
        self.default_source()
        tools.replace_in_file(os.path.join("sources", "CMakeLists.txt"), 'if ("${CMAKE_BINARY_DIR}" STREQUAL "${CMAKE_SOURCE_DIR}")', 'if (0)')
        os.rename(os.path.join("sources", "docs", "FTL.TXT"), os.path.join("sources", "LICENSE"))


    def _configure_cmake(self):
        if not self._cmake:
            self._cmake = CMake(self)
            self._cmake.definitions["CMAKE_DEBUG_POSTFIX"] = "d"
            self._cmake.definitions["BUILD_SHARED_LIBS"] = True

            self._cmake.definitions["PROJECT_VERSION"] = self.conan_data["sources"][self.version]['libtool_version']

            self._cmake.definitions["FT_REQUIRE_ZLIB"] = True if 'zlib' in self.deps_cpp_info.deps else False
            self._cmake.definitions["FT_DISABLE_ZLIB"] = False if 'zlib' in self.deps_cpp_info.deps else True

            self._cmake.definitions["FT_REQUIRE_PNG"] = True if 'libpng' in self.deps_cpp_info.deps else False
            self._cmake.definitions["FT_DISABLE_PNG"] = False if 'libpng' in self.deps_cpp_info.deps else True

            self._cmake.definitions["FT_REQUIRE_BZIP2"] = True if 'bzip2' in self.deps_cpp_info.deps else False
            self._cmake.definitions["FT_DISABLE_BZIP2"] = False if 'bzip2' in self.deps_cpp_info.deps else True

            # TODO: Harfbuzz can be added as an option as soon as it is available.
            self._cmake.definitions["FT_REQUIRE_HARFBUZZ"] = True if 'harfbuzz' in self.deps_cpp_info.deps else False
            self._cmake.definitions["FT_DISABLE_HARFBUZZ"] = False if 'harfbuzz' in self.deps_cpp_info.deps else True

            # TODO: Brotli (WOFF2 format) can be added as an option as soon as it is available.
            self._cmake.definitions["FT_REQUIRE_BROTLI"] = True if 'brotli' in self.deps_cpp_info.deps else False
            self._cmake.definitions["FT_DISABLE_BROTLI"] = False if 'brotli' in self.deps_cpp_info.deps else True

            self._cmake.configure()
        return self._cmake


    def build(self):
        cmake = self._configure_cmake()
        cmake.build()


    def package(self):
        cmake = self._configure_cmake()
        cmake.install()

        self.copy("*.pdb", src="bin", dst="bin")

        tools.rmdir(os.path.join(self.package_folder, "lib", "cmake"))
        tools.rmdir(os.path.join(self.package_folder, "lib", "pkgconfig"))

        self.patch_binaries()
        self.default_package()


    def package_info(self):
        self.default_package_info()
        self.cpp_info.names["pkg_config"] = "freetype2"

        self.cpp_info.includedirs.append(os.path.join("include", "freetype2"))
        if self.settings.os == "Linux":
            self.cpp_info.system_libs.append("m")
