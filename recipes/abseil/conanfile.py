from conan import ConanFile
from conan.tools.cmake import CMake, CMakeToolchain, cmake_layout
from conan.tools.files import copy, get, rmdir
import os

required_conan_version = ">=2.2.2"


class ConanRecipe(ConanFile):
    name = "abseil"
    version = "20240116.1"
    homepage = "https://abseil.io"
    description = "Collection of C++ libraries from Google"
    license = "Apache-2.0"
    settings = "os", "arch", "compiler", "build_type"
    exports_sources = "patches/*.patch"
    package_type = "static-library"

    mlab_hooks = {"cmake_files.exclude": ["lib/cmake/*.cmake"]}

    def layout(self):
        cmake_layout(self, src_folder="src")

    def source(self):
        get(
            self,
            sha256="3c743204df78366ad2eaf236d6631d83f6bc928d1705dd0000b872e53b73dc6a",
            url=f"https://github.com/abseil/abseil-cpp/archive/refs/tags/{self.version}.tar.gz",
            strip_root=True,
        )

    def generate(self):
        tc = CMakeToolchain(self)
        tc.variables["CMAKE_DEBUG_POSTFIX"] = "_d"
        tc.variables["BUILD_SHARED_LIBS"] = False
        tc.variables["CMAKE_POSITION_INDEPENDENT_CODE"] = True
        tc.variables["ABSL_ENABLE_INSTALL"] = True
        tc.variables["ABSL_PROPAGATE_CXX_STD"] = True
        tc.variables["BUILD_TESTING"] = False
        tc.generate()

    def build(self):
        cmake = CMake(self)
        cmake.configure()
        cmake.build()

    def package(self):
        copy(self, pattern="LICENSE", src=self.source_path, dst=self.package_path / "licenses")
        cmake = CMake(self)
        cmake.install()
        rmdir(self, self.package_path / "lib" / "pkgconfig")

    def package_info(self):
        self.cpp_info.builddirs.append(os.path.join("lib", "cmake"))
        self.cpp_info.set_property("cmake_find_mode", "none")  # do NOT generate cmake files, they are generated by abseil
        self.cpp_info.set_property("cmake_file_name", "absl")  # let CMake search for absl, not abseil (the package name)
        self.cpp_info.set_property(
            "cmake_target_name", "absl::base"
        )  # let CMake link to absl::base, not abseil::abseil (derived from the package name)