from conan import ConanFile
from conan.tools.cmake import CMake, cmake_layout, CMakeToolchain
from conan.tools.files import copy, get, rmdir
import os

required_conan_version = ">=2.2.2"


class EigenConan(ConanFile):
    name = "eigen"
    version = "3.4.1"
    homepage = "https://eigen.tuxfamily.org"
    description = "Eigen is a C++ template library for linear algebra: matrices, vectors, numerical solvers, and related algorithms"
    license = "MPL-2.0"
    settings = "os", "arch", "compiler", "build_type"
    package_type = "header-library"
    exports_sources = "patches/*.patch"

    def layout(self):
        cmake_layout(self, src_folder="src")

    def package_id(self):
        self.info.clear()

    def source(self):
        get(
            self,
            sha256="b93c667d1b69265cdb4d9f30ec21f8facbbe8b307cf34c0b9942834c6d4fdbe2",
            url=f"https://gitlab.com/libeigen/eigen/-/archive/{self.version}/eigen-{self.version}.tar.gz",
            destination=self.source_folder,
            strip_root=True,
        )

    def generate(self):
        tc = CMakeToolchain(self)
        tc.variables["BUILD_TESTING"] = False
        tc.variables["EIGEN_BUILD_DOC"] = False
        tc.variables["EIGEN_BUILD_DEMOS"] = False
        tc.variables["EIGEN_BUILD_CMAKE_PACKAGE"] = False
        tc.variables["EIGEN_TEST_NOQT"] = True
        tc.variables["EIGEN_BUILD_PKGCONFIG"] = False
        tc.variables["EIGEN_BUILD_BLAS"] = False
        tc.variables["EIGEN_BUILD_LAPACK"] = False
        tc.generate()

    def build(self):
        cmake = CMake(self)
        cmake.configure()
        cmake.build()

    def package(self):
        cmake = CMake(self)
        cmake.install()
        copy(self, "COPYING.*", self.source_folder, os.path.join(self.package_folder, "licenses"))
        rmdir(self, os.path.join(self.package_folder, "share"))

    def package_info(self):
        # self.cpp_info.set_property("cpe", "")  # No CPE yet?
        self.cpp_info.set_property(
            "purl", "pkg:gitlab/libeigen/eigen@{self.version}"
        )  # gitlab not really defined per standard?
        self.cpp_info.set_property("cmake_file_name", "Eigen3")
        self.cpp_info.set_property("cmake_target_name", "Eigen3::Eigen")
        self.cpp_info.set_property("cmake_target_aliases", ["Eigen3::Eigen3"])
        self.cpp_info.set_property("display_name", "Eigen")
        self.cpp_info.set_property("pkg_config_name", "eigen3")

        self.cpp_info.bindirs = []
        self.cpp_info.libdirs = []
        self.cpp_info.includedirs.append("include/eigen3")
        self.cpp_info.defines = ["EIGEN_MPL2_ONLY", "EIGEN_MALLOC_ALREADY_ALIGNED=1", "EIGEN_MAX_ALIGN_BYTES=16"]

        if self.settings.os in ["Linux"]:
            self.cpp_info.system_libs = ["m"]
