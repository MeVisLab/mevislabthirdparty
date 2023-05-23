# -*- coding: utf-8 -*-
from conans import ConanFile
from conans import CMake
from conans import tools
import glob
import os

class ConanRecipe(ConanFile):
    python_requires = 'common/1.0.0@mevislab/stable'
    python_requires_extend = 'common.CommonRecipe'

    _cmake = None


    def requirements(self):
        channel = f"@{self.user}/{self.channel}"
        self.requires("lz4/[>=1.9.3]" + channel)
        self.requires("hdf5/[>=1.12.0]" + channel)


    def source(self):
        self.default_source()
        # remove embeded lz4
        tools.rmdir(os.path.join("sources", "src", "cpp", "flann", "ext"))


    def _configure_cmake(self):
        if not self._cmake:
            self.create_cmake_wrapper()
            self._cmake = CMake(self)
            self._cmake.definitions["CMAKE_DEBUG_POSTFIX"] = "d" if self.settings.build_type == "Debug" else ""
            self._cmake.definitions["USE_OPENMP"] = False
            self._cmake.definitions["BUILD_C_BINDINGS"] = True
            self._cmake.definitions["BUILD_DOC"] = False
            self._cmake.definitions["BUILD_EXAMPLES"] = False
            self._cmake.definitions["BUILD_TESTS"] = False
            self._cmake.definitions["BUILD_MATLAB_BINDINGS"] = False
            self._cmake.definitions["BUILD_PYTHON_BINDINGS"] = False

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

        # Remove MS runtime files
        for pattern in ["concrt*.dll", "msvcp*.dll", "vcruntime*.dll"]:
            for lib in glob.glob(os.path.join(self.package_folder, "bin", pattern)):
                os.remove(lib)

        # Remove static libraries
        static_libs = ["*flann_cpp_s.*", "*flann_cpp_sd.*", "*flann_s.*", "*flann_sd.*"]
        for pattern in static_libs:
            for lib in glob.glob(os.path.join(self.package_folder, "lib", pattern)):
                os.remove(lib)

        self.patch_binaries()
        self.default_package()


    def package_info(self):
        self.default_package_info()

        if self.settings.os == "Linux":
            self.cpp_info.system_libs = ["m"]
