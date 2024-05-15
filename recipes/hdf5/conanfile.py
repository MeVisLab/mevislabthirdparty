import os
from conan import ConanFile
from conan.tools.cmake import CMake, CMakeDeps, CMakeToolchain, cmake_layout
from conan.tools.files import copy, get, rm, rmdir
from conan.tools.scm import Version

required_conan_version = ">=2.2.2"


class ConanRecipe(ConanFile):
    name = "hdf5"
    version = "1.14.3"
    homepage = "http://www.hdfgroup.org/HDF5"
    description = "General purpose library and file format for storing scientific data"
    license = "BSD-3-Clause"
    package_type = "shared-library"
    settings = "os", "arch", "compiler", "build_type"

    def layout(self):
        cmake_layout(self, src_folder="src")

    def requirements(self):
        self.requires("zlib/[>=1.2.13]")
        self.requires("libaec/[>=1.0.6]")

    def source(self):
        v = Version(self.version)
        get(self,
            sha256="df5ee33c74d5efb59738075ef96f4201588e1f1eeb233f047ac7fd1072dee1f6",
            url=f"https://github.com/HDFGroup/hdf5/archive/refs/tags/hdf5-{v.major}_{v.minor}_{v.patch}.tar.gz",
            strip_root=True
        )

    def generate(self):
        cmakedeps = CMakeDeps(self)
        cmakedeps.generate()
        tc = CMakeToolchain(self)
        tc.variables["CMAKE_DEBUG_POSTFIX"] = "_d"
        tc.variables["CMAKE_INSTALL_RPATH"] = "$ORIGIN;$ORIGIN/../lib"
        tc.variables["HDF5_EXTERNALLY_CONFIGURED"] = True
        tc.variables["HDF5_USE_FOLDERS"] = False
        tc.variables["USE_LIBAEC"] = True
        tc.variables["HDF5_NO_PACKAGES"] = True
        tc.variables["ONLY_SHARED_LIBS"] = True
        tc.variables["BUILD_STATIC_LIBS"] = False
        tc.variables["BUILD_STATIC_EXECS"] = False
        tc.variables["HDF5_ENABLE_Z_LIB_SUPPORT"] = True
        tc.variables["HDF5_ENABLE_SZIP_SUPPORT"] = True
        tc.variables["HDF5_ENABLE_SZIP_ENCODING"] = True
        tc.variables["BUILD_TESTING"] = False
        tc.variables["HDF5_INSTALL_INCLUDE_DIR"] = "include/hdf5"
        tc.variables["HDF5_BUILD_TOOLS"] = False
        tc.variables["HDF5_BUILD_UTILS"] = False
        tc.variables["HDF5_BUILD_EXAMPLES"] = False
        tc.variables["HDF5_BUILD_CPP_LIB"] = True
        tc.variables["HDF5_BUILD_JAVA"] = False
        tc.variables["HDF5_BUILD_FORTRAN"] = False
        tc.generate()

    def build(self):
        cmake = CMake(self)
        cmake.configure()
        cmake.build()

    def package(self):
        copy(self, "COPYING", src=self.source_path, dst=self.package_path / "licenses")
        cmake = CMake(self)
        cmake.install()
        rmdir(self, self.package_path / "lib" / "pkgconfig")
        rm(self, "libhdf5.settings", self.package_path / "lib")

    def package_info(self):
        self.cpp_info.set_property("cmake_find_mode", "both")
        self.cpp_info.set_property("cmake_file_name", "HDF5")
        self.cpp_info.set_property("cmake_target_name", "HDF5::HDF5")

        d = "_d" if self.settings.build_type == "Debug" else ""
        self.cpp_info.components["hdf5"].set_property("cmake_target_name", "hdf5::hdf5")
        self.cpp_info.components["hdf5"].set_property("cmake_target_aliases", ["hdf5::hdf5_c"])
        self.cpp_info.components["hdf5"].set_property("pkg_config_name", "hdf5")
        self.cpp_info.components["hdf5"].libs = [f"hdf5{d}"]
        self.cpp_info.components["hdf5"].includedirs.append(os.path.join("include", "hdf5"))
        self.cpp_info.components["hdf5"].defines.append("H5_BUILT_AS_DYNAMIC_LIB")
        self.cpp_info.components["hdf5"].requires = ["zlib::zlib", "libaec::libaec"]
        if self.settings.os == "Linux":
            self.cpp_info.components["hdf5"].system_libs.extend(["dl", "m", "pthread"])
        self.cpp_info.components["hdf5_hl"].set_property("cmake_target_name", "hdf5::hdf5_hl")
        self.cpp_info.components["hdf5_hl"].set_property("pkg_config_name", "hdf5_hl")
        self.cpp_info.components["hdf5_hl"].libs = [f"hdf5_hl{d}"]
        self.cpp_info.components["hdf5_hl"].requires = ["hdf5"]
        self.cpp_info.components["hdf5_cpp"].set_property("cmake_target_name", "hdf5::hdf5_cpp")
        self.cpp_info.components["hdf5_cpp"].set_property("pkg_config_name", "hdf5_cpp")
        self.cpp_info.components["hdf5_cpp"].libs = [f"hdf5_cpp{d}"]
        self.cpp_info.components["hdf5_cpp"].requires = ["hdf5"]
        self.cpp_info.components["hdf5_hl_cpp"].set_property("cmake_target_name", "hdf5::hdf5_hl_cpp")
        self.cpp_info.components["hdf5_hl_cpp"].set_property("pkg_config_name", "hdf5_hl_cpp")
        self.cpp_info.components["hdf5_hl_cpp"].libs = [f"hdf5_hl_cpp{d}"]
        self.cpp_info.components["hdf5_hl_cpp"].requires = ["hdf5", "hdf5_cpp", "hdf5_hl"]

