# -*- coding: utf-8 -*-
from conans import ConanFile
from conans import tools
from conans import CMake
import os


class ConanRecipe(ConanFile):
    python_requires = 'common/1.0.0@mevislab/stable'
    python_requires_extend = 'common.CommonRecipe'
    generators = "cmake", "cmake_find_package"

    _cmake = None


    def requirements(self):
        channel = "@{0}/{1}".format(self.user, self.channel)
        self.requires("glfw/[>=3.3.2]" + channel)
        self.requires("tbb/[>=2021.4.0]" + channel)
        self.requires("openexr/[>=2.5.3]" + channel)
        self.requires("boost/[>=1.74.0]" + channel)
        self.requires("c-blosc/[>=1.21.0]" + channel)


    def _configure_cmake(self):
        if not self._cmake:
            self._cmake = CMake(self)
            self._cmake.definitions["CMAKE_DEBUG_POSTFIX"] = "d"
            self._cmake.definitions["BLOSC_DEBUG_SUFFIX"] = "d"

            self._cmake.definitions["BUILD_SHARED_LIBS"] = True

            # OpenVDB sets absolute RPATH paths when this option is on, making OpenVDB no longer relocatable.
            # Therefore, we disable this option (ON by default) and do it ourselves. ;)
            self._cmake.definitions["OPENVDB_ENABLE_RPATH"] = False
            self._cmake.definitions["CMAKE_SKIP_BUILD_RPATH"] = False
            self._cmake.definitions["CMAKE_BUILD_WITH_INSTALL_RPATH"] = False
            self._cmake.definitions["CMAKE_INSTALL_RPATH_USE_LINK_PATH"] = False
            if tools.os_info.is_linux:
                self._cmake.definitions["CMAKE_INSTALL_RPATH"] = "\$ORIGIN"

            self._cmake.definitions["OPENVDB_CORE_STATIC"] = False
            self._cmake.definitions["USE_STATIC_DEPENDENCIES"] = False

            self._cmake.definitions["OPENVDB_FUTURE_DEPRECATION"] = False   # TODO: we should fix our code and enable this feature again
            self._cmake.definitions["OPENVDB_ENABLE_UNINSTALL"] = False

            # explicit instantiation doesn't work correctly in v9.0.0
            # on macOS release builds (building MeVisLab fails)
            self._cmake.definitions["USE_EXPLICIT_INSTANTIATION"] = not tools.os_info.is_macos

            self._cmake.definitions["OPENVDB_BUILD_UNITTESTS"] = False
            self._cmake.definitions["OPENVDB_BUILD_DOCS"] = False
            self._cmake.definitions["OPENVDB_BUILD_PYTHON_MODULE"] = False
            self._cmake.definitions["OPENVDB_BUILD_HOUDINI_SOPS"] = False
            self._cmake.definitions["OPENVDB_BUILD_MAYA_PLUGIN"] = False
            self._cmake.definitions["OPENVDB_INSTALL_CMAKE_MODULES"] = False
            #self._cmake.definitions["CONCURRENT_MALLOC"] = "Tbbmalloc"

            self._cmake.configure(build_folder='build')
        return self._cmake


    def build(self):
        if self.settings.build_type == "Debug":
            tools.replace_in_file(
                os.path.join('sources', 'cmake', 'FindIlmBase.cmake'),
                '"-${IlmBase_VERSION_MAJOR}_${IlmBase_VERSION_MINOR}',
                '"-${IlmBase_VERSION_MAJOR}_${IlmBase_VERSION_MINOR}_d'
            )
        cmake = self._configure_cmake()
        cmake.build()


    def package(self):
        cmake = self._configure_cmake()
        cmake.install()

        self.copy("*.pdb", src="build/bin", dst="bin", excludes="vdb_print*.pdb")

        if not tools.os_info.is_windows:
            tools.rmdir(os.path.join(self.package_folder, 'bin'))

        self.patch_binaries()
        self.default_package()


    def package_info(self):
        self.default_package_info()
        self.cpp_info.defines.append("OPENVDB_DLL")
