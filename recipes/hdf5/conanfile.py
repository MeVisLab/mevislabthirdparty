import os
from conan import ConanFile
from conan.tools.cmake import CMake, CMakeDeps, CMakeToolchain, cmake_layout
from conan.tools.files import copy, get, rm, rmdir
from conan.tools.scm import Version

required_conan_version = ">=2.2.2"


class ConanRecipe(ConanFile):
    name = "hdf5"
    version = "2.0.0"
    homepage = "https://www.hdfgroup.org/solutions/hdf5/"
    description = "General purpose library and file format for storing scientific data"
    license = "BSD-3-Clause"
    package_type = "shared-library"
    settings = "os", "arch", "compiler", "build_type"

    def layout(self):
        cmake_layout(self, src_folder="src")

    def requirements(self):
        self.requires("zlib/[>=1.2.13]")
        self.requires("libaec/[>=1.0.6]")

    def hdf5_version(self):
        v = Version(self.version)
        return f"{v.major}.{v.minor}.{v.patch}-{v.micro}" if v.micro else f"{v.major}.{v.minor}.{v.patch}"

    def source(self):
        get(
            self,
            sha256="6e45a4213cb11bb5860e1b0a7645688ab55562cc2d55c6ff9bcb0984ed12b22b",
            url=f"https://github.com/HDFGroup/hdf5/releases/download/hdf5_{self.version}/hdf5-{self.hdf5_version()}.tar.gz",
            strip_root=True,
        )

    def generate(self):
        cmakedeps = CMakeDeps(self)
        cmakedeps.generate()
        tc = CMakeToolchain(self)
        tc.variables["CMAKE_DEBUG_POSTFIX"] = "_d"
        tc.variables["CMAKE_INSTALL_RPATH"] = "$ORIGIN;$ORIGIN/../lib"
        tc.variables["BUILD_TESTING"] = False
        tc.variables["BUILD_STATIC_LIBS"] = False
        tc.variables["BUILD_STATIC_EXECS"] = False
        tc.variables["BUILD_STATIC_TOOLS"] = False
        tc.variables["HDF5_ONLY_SHARED_LIBS"] = True
        tc.variables["HDF5_BUILD_CPP_LIB"] = True
        tc.variables["HDF5_BUILD_DOC"] = False
        tc.variables["HDF5_BUILD_EXAMPLES"] = False
        tc.variables["HDF5_BUILD_FORTRAN"] = False
        tc.variables["HDF5_BUILD_JAVA"] = False
        tc.variables["HDF5_BUILD_TOOLS"] = False
        tc.variables["HDF5_BUILD_UTILS"] = False
        tc.variables["HDF5_ENABLE_SZIP_ENCODING"] = True
        tc.variables["HDF5_ENABLE_SZIP_SUPPORT"] = True
        tc.variables["HDF5_ENABLE_ZLIB_SUPPORT"] = True
        tc.variables["HDF5_EXTERNALLY_CONFIGURED"] = True
        tc.variables["HDF5_INSTALL_INCLUDE_DIR"] = "include/hdf5"
        tc.variables["HDF5_NO_PACKAGES"] = True
        tc.variables["HDF5_USE_FOLDERS"] = False
        tc.generate()

    def build(self):
        cmake = CMake(self)
        cmake.configure(build_script_folder=os.path.join(self.source_folder, f"hdf5-{self.hdf5_version()}"))
        cmake.build()

    def package(self):
        copy(
            self,
            "LICENSE",
            src=os.path.join(self.source_folder, f"hdf5-{self.hdf5_version()}"),
            dst=os.path.join(self.package_folder, "licenses"),
        )
        cmake = CMake(self)
        cmake.install()
        rmdir(self, os.path.join(self.package_folder, "lib", "pkgconfig"))
        rm(self, "libhdf5.settings", os.path.join(self.package_folder, "lib"))

    def package_info(self):
        self.cpp_info.set_property("cpe", "cpe:2.3:a:hdfgroup:hdf5:*:*:*:*:*:*:*:*")
        self.cpp_info.set_property("purl", f"pkg:github/HDFGroup/hdf5@hdf5_{self.version}")
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
