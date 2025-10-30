from conan import ConanFile
from conan.tools.cmake import CMakeToolchain, CMakeDeps, CMake
from conan.tools.files import copy, collect_libs, replace_in_file, get
import os

required_conan_version = ">=2.2.2"


class ConanRecipe(ConanFile):
    name = "xylib"
    version = "1.6.0"
    homepage = "https://github.com/wojdyr/xylib"
    description = (
        "library for reading files with x-y data from powder diffraction, "
        "spectroscopy, or other experimental methods"
    )
    license = "LGPL-2.1-or-later"
    package_type = "shared-library"
    settings = "os", "arch", "compiler", "build_type"

    def requirements(self):
        self.requires("boost/[>=1.75.0]")
        self.requires("bzip2/[>=1.0.8]")
        self.requires("zlib/[>=1.2.11]")

    def source(self):
        major, minor = self.version.split(".")[:2]
        get(
            self,
            sha256="b641cb33fa01732b8203356e0978384f9551bf415cfbae5989b3a233b3cb0ec7",
            url=f"https://github.com/wojdyr/xylib/releases/download/v{major}.{minor}/xylib-{major}.{minor}.tar.bz2",
            strip_root=True,
        )
        replace_in_file(
            self, os.path.join(self.source_folder, "xylib", "util.h"), "#if __cplusplus-0 < 201103L", "#if 0"
        )
        replace_in_file(
            self,
            os.path.join(self.source_folder, "CMakeLists.txt"),
            "cmake_policy(SET CMP0042 OLD)",
            "#cmake_policy(SET CMP0042 OLD)",
        )

    def generate(self):
        tc = CMakeToolchain(self)
        tc.variables["CMAKE_DEBUG_POSTFIX"] = "_d"
        tc.variables["BUILD_SHARED_LIBS"] = True

        tc.variables["USE_ZLIB"] = True
        tc.variables["DOWNLOAD_ZLIB"] = False
        tc.variables["USE_BZIP2"] = True
        tc.variables["GUI"] = False

        tc.variables["Boost_NO_SYSTEM_PATHS"] = True
        boost_info = self.dependencies["boost"].cpp_info
        tc.variables["BOOST_INCLUDEDIR"] = ";".join([d.replace("\\", "/") for d in boost_info.includedirs])
        tc.variables["BOOST_LIBRARYDIR"] = ";".join([d.replace("\\", "/") for d in boost_info.libdirs])
        tc.generate()

        cd = CMakeDeps(self)
        cd.generate()

    def build(self):
        cmake = CMake(self)
        cmake4_compat = {"CMAKE_POLICY_VERSION_MINIMUM": "3.5"}  # FIXME required for compatibility with CMake 4.0+
        cmake.configure(variables=cmake4_compat)
        cmake.build()

    def package(self):
        cmake = CMake(self)
        cmake.install()
        copy(
            self,
            "*.pdb",
            src=self.source_folder,
            dst=os.path.join(self.package_folder, "bin"),
            keep_path=False,
            excludes="*vc???.pdb",
        )
        copy(self, "COPYING", src=self.source_folder, dst=os.path.join(self.package_folder, "licenses"))

    def package_info(self):
        # self.cpp_info.set_property("cpe", "")  # No CPE (yet)?
        major, minor = self.version.split(".")[:2]
        self.cpp_info.set_property("purl", f"pkg:github/wojdyr/xylib@v{major}.{minor}")
        self.cpp_info.set_property("cmake_file_name", "xylib")
        self.cpp_info.set_property("cmake_target_name", "xylib::xylib")
        self.cpp_info.set_property("mevislab_prosdk_exclude", True)
        self.cpp_info.libs = collect_libs(self)
