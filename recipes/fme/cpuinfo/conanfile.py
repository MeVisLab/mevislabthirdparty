from conan import ConanFile
from conan.tools.cmake import CMake, CMakeToolchain, cmake_layout
from conan.tools.files import copy, get, collect_libs, rmdir
import os

required_conan_version = ">=2.32.0"


class CpuinfoConan(ConanFile):
    name = "cpuinfo"
    version = "20260519"
    description = "CPU INFOrmation library"
    license = "BSD-2-Clause"
    homepage = "https://github.com/pytorch/cpuinfo"
    package_type = "static-library"
    settings = "os", "arch", "compiler", "build_type"

    def configure(self):
        self.settings.rm_safe("compiler.cppstd")
        self.settings.rm_safe("compiler.libcxx")

    def layout(self):
        cmake_layout(self, src_folder="src")

    def source(self):
        get(
            self,
            sha256="3be1c1b6e7cdad27646303590b760ecdd7883398856135a853ed16de7e52530a",
            url=f"https://github.com/pytorch/cpuinfo/archive/ea6b9f1bb6e1001d8b21574d5bc78ddef62e499d.tar.gz",
            strip_root=True,
        )

    def generate(self):
        tc = CMakeToolchain(self)
        tc.variables["CMAKE_DEBUG_POSTFIX"] = "_d"
        tc.variables["BUILD_SHARED_LIBS"] = False
        tc.variables["CPUINFO_LOG_TO_STDIO"] = True
        tc.variables["CPUINFO_BUILD_TOOLS"] = False
        tc.variables["CPUINFO_BUILD_UNIT_TESTS"] = False
        tc.variables["CPUINFO_BUILD_MOCK_TESTS"] = False
        tc.variables["CPUINFO_BUILD_BENCHMARKS"] = False
        tc.variables["CPUINFO_BUILD_PKG_CONFIG"] = False
        tc.variables["CLOG_RUNTIME_TYPE"] = "static"
        tc.variables["CLOG_LOG_TO_STDIO"] = True
        tc.variables["CLOG_BUILD_TESTS"] = False
        tc.variables["USE_SYSTEM_LIBS"] = True
        tc.variables["CMAKE_POSITION_INDEPENDENT_CODE"] = True
        tc.generate()

    def build(self):
        cmake = CMake(self)
        cmake.configure()
        cmake.build()

    def package(self):
        copy(self, "LICENSE", src=self.source_folder, dst=os.path.join(self.package_folder, "licenses"))
        cmake = CMake(self)
        cmake.install()
        rmdir(self, os.path.join(self.package_folder, "share"))
        rmdir(self, os.path.join(self.package_folder, "lib", "pkgconfig"))

    def package_info(self):
        # self.cpp_info.set_property("cpe", "")  # No CPE (yet)?
        self.cpp_info.set_property("purl", "pkg:github/pytorch/cpuinfo")
        self.cpp_info.set_property("cmake_file_name", "cpuinfo")
        self.cpp_info.set_property("cmake_target_name", "cpuinfo::cpuinfo")
        self.cpp_info.set_property("pkg_config_name", "libcpuinfo")
        self.cpp_info.libs = collect_libs(self)
