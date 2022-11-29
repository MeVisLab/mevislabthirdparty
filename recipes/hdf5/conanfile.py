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
        channel = "@{0}/{1}".format(self.user, self.channel)
        self.requires("zlib/[>=1.2.11]" + channel)
        self.requires("libaec/[>=1.0.4]" + channel)


    def _configure_cmake(self):
        if not self._cmake:
            self._cmake = CMake(self)
            self._cmake.definitions["CMAKE_DEBUG_POSTFIX"] = "d"
            self._cmake.definitions["RECIPE_VERSION"] = self.version
            self._cmake.definitions["HDF5_EXTERNALLY_CONFIGURED"] = True
            self._cmake.definitions["HDF5_USE_FOLDERS"] = False
            self._cmake.definitions["HDF5_NO_PACKAGES"] = True
            self._cmake.definitions["ONLY_SHARED_LIBS"] = True
            self._cmake.definitions["HDF5_ENABLE_Z_LIB_SUPPORT"] = True
            self._cmake.definitions["HDF5_ENABLE_SZIP_SUPPORT"] = True
            self._cmake.definitions["HDF5_ENABLE_SZIP_ENCODING"] = True
            self._cmake.definitions["BUILD_TESTING"] = False
            self._cmake.definitions["HDF5_INSTALL_INCLUDE_DIR"] = os.path.join(self.package_folder, "include", "hdf5")
            self._cmake.definitions["HDF5_BUILD_TOOLS"] = False
            self._cmake.definitions["HDF5_BUILD_UTILS"] = False
            self._cmake.definitions["HDF5_BUILD_EXAMPLES"] = False
            self._cmake.definitions["HDF5_BUILD_CPP_LIB"] = True

            self._cmake.configure(build_folder='build')
        return self._cmake


    def build(self):
        cmake = self._configure_cmake()
        cmake.build()
        shutil.copy2(os.path.join(self.build_folder, "sources", f"hdf5-{self.version}", "COPYING"), self.build_folder)


    def package(self):
        cmake = self._configure_cmake()
        cmake.install()

        self.copy("hdf5*.pdb", src="build/bin", dst="bin")

        tools.rmdir(os.path.join(self.package_folder, "lib", "pkgconfig"))
        os.remove(os.path.join(self.package_folder, "lib", "libhdf5.settings"))

        self.default_package()


    def package_info(self):
        self.cpp_info.names["cmake_find_package"] = "HDF5"
        self.cpp_info.names["cmake_find_package_multi"] = "HDF5"

        self.cpp_info.libs = tools.collect_libs(self)

        self.cpp_info.includedirs.append(os.path.join(self.package_folder, "include", "hdf5"))
        self.cpp_info.defines.append("H5_BUILT_AS_DYNAMIC_LIB")
        if self.settings.os == "Linux":
            self.cpp_info.system_libs.extend(["dl", "m"])
