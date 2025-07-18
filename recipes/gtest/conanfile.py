from conan import ConanFile
from conan.tools.cmake import CMake, CMakeToolchain, cmake_layout
from conan.tools.files import collect_libs, copy, get, rmdir
from conan.tools.microsoft import is_msvc
import pathlib
import os

required_conan_version = ">=2.2.2"


class ConanRecipe(ConanFile):
    name = "gtest"
    display_name = "GTest"
    version = "1.17.0"
    homepage = "https://github.com/google/googletest"
    description = "Google Testing and Mocking Framework"
    license = "BSD-3-Clause"
    package_type = "shared-library"
    settings = "os", "arch", "compiler", "build_type"

    def layout(self):
        cmake_layout(self, src_folder="src")

    def source(self):
        get(
            self,
            sha256="65fab701d9829d38cb77c14acdc431d2108bfdbf8979e40eb8ae567edf10b27c",
            url=f"https://github.com/google/googletest/archive/refs/tags/v{self.version}.tar.gz",
            destination=self.source_folder,
            strip_root=True,
        )

    def generate(self):
        tc = CMakeToolchain(self)
        if is_msvc(self) and "MD" in str(self.settings.compiler.runtime):
            tc.variables["gtest_force_shared_crt"] = "ON"
        tc.variables["CMAKE_DEBUG_POSTFIX"] = "_d"
        tc.variables["BUILD_SHARED_LIBS"] = True
        tc.variables["CMAKE_POSITION_INDEPENDENT_CODE"] = True
        tc.generate()

    def build(self):
        cmake = CMake(self)
        cmake.configure()
        cmake.build()

    def package(self):
        copy(self, "LICENSE", src=self.source_folder, dst=os.path.join(self.package_folder, "licenses"))
        copy(self, "*.pdb", src=self.build_folder, dst=os.path.join(self.package_folder, "bin"), keep_path=False)
        cmake = CMake(self)
        cmake.install()
        rmdir(self, os.path.join(self.package_folder, "lib", "pkgconfig"))
        rmdir(self, os.path.join(self.package_folder, "lib", "cmake"))
        for pdb in pathlib.Path(os.path.join(self.package_folder, "lib")).glob("*.pdb"):
            pdb.unlink()

    def package_info(self):
        self.cpp_info.set_property("cpe", "cpe:2.3:a:google:google_test:*:*:*:*:*:*:*:*")
        self.cpp_info.set_property("purl", f"pkg:github/google/googletest@v{self.version}")
        self.cpp_info.set_property("cmake_find_mode", "config")
        self.cpp_info.set_property("cmake_file_name", "GTest")
        self.cpp_info.set_property("cmake_target_name", "GTest::GTest")
        self.cpp_info.set_property("pkg_config_name", "gtest")
        self.cpp_info.libs = collect_libs(self)

        for lib in collect_libs(self):
            if lib.endswith(f".{self.version}"):
                continue

            comp = lib[:-2] if self.settings.build_type == "Debug" else lib
            if not comp.endswith("_main"):
                comp += "_lib"
            self.cpp_info.components[comp].libs = [lib]
            self.cpp_info.components[comp].set_property("cmake_target_name", f"GTest::{comp}")
