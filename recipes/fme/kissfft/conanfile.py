from conan import ConanFile
from conan.tools.cmake import CMakeToolchain, CMake, cmake_layout
from conan.tools.files import copy, rmdir, get, collect_libs
import os

required_conan_version = ">=2.2.2"


class ConanRecipe(ConanFile):
    name = "kissfft"
    version = "131.2.0"
    homepage = "https://github.com/mborgerding/kissfft"
    description = "A mixed-radix Fast Fourier Transform"
    license = "BSD-3-Clause"
    package_type = "shared-library"
    settings = "os", "arch", "compiler", "build_type"

    def layout(self):
        cmake_layout(self, src_folder="src")

    def generate(self):
        tc = CMakeToolchain(self)
        tc.variables["CMAKE_DEBUG_POSTFIX"] = "_d"
        tc.variables["BUILD_SHARED_LIBS"] = True

        tc.variables["KISSFFT_PKGCONFIG"] = False
        tc.variables["KISSFFT_TOOLS"] = False
        tc.variables["KISSFFT_TEST"] = False
        tc.generate()

    def source(self):
        get(
            self,
            sha256="205a8f6a448ef12b091f8ac6a514b5091bb5f6b0b543431ed75f673116cf5cbf",
            url=f"https://github.com/mborgerding/kissfft/archive/refs/tags/{self.version}.tar.gz",
            strip_root=True,
        )

    def build(self):
        cmake = CMake(self)
        cmake.configure()
        cmake.build()

    def package(self):
        cmake = CMake(self)
        cmake.install()
        copy(
            self,
            "*.pdb",
            src=self.build_folder,
            dst=os.path.join(self.package_folder, "bin"),
            keep_path=False,
            excludes="*vc???.pdb",
        )
        copy(
            self,
            "*",
            src=os.path.join(self.source_folder, "LICENSES"),
            dst=os.path.join(self.package_folder, "licenses"),
        )
        copy(self, "COPYING", src=self.source_folder, dst=os.path.join(self.package_folder, "licenses"))
        rmdir(self, os.path.join(self.package_folder, "lib", "cmake"))

    def package_info(self):
        # self.cpp_info.set_property("cpe", "")  # No CPE (yet)?
        self.cpp_info.set_property("purl", f"pkg:github/mborgerding/kissfft@{self.version}")
        self.cpp_info.set_property("cmake_file_name", "kissfft")
        self.cpp_info.set_property("cmake_target_name", "kissfft::kissfft")
        self.cpp_info.set_property("pkg_config_name", "kissfft")
        self.cpp_info.set_property("mevislab_prosdk_exclude", True)
        self.cpp_info.libs = collect_libs(self)
        self.cpp_info.includedirs.append("include/kissfft")
        if self.settings.os == "Linux":
            self.cpp_info.system_libs.append("m")
