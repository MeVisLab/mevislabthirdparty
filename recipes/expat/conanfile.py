from conan import ConanFile
from conan.tools.cmake import CMake, CMakeToolchain, cmake_layout
from conan.tools.files import collect_libs, copy, get, rmdir
import os

required_conan_version = ">=2.2.2"


class ConanRecipe(ConanFile):
    name = "expat"
    version = "2.8.2"
    homepage = "https://libexpat.github.io"
    description = "Fast stream-oriented XML parser library"
    license = "MIT"
    package_type = "shared-library"
    settings = "os", "arch", "compiler", "build_type"

    def configure(self):
        self.settings.rm_safe("compiler.cppstd")
        self.settings.rm_safe("compiler.libcxx")

    def layout(self):
        cmake_layout(self, src_folder="src")

    def source(self):
        get(
            self,
            sha256="3ad89b8588e6644bd4e49981480d48b21289eebbcd4f0a1a4afb1c29f99b6ab4",
            url=f"https://github.com/libexpat/libexpat/releases/download/R_{self.version.replace('.', '_')}/expat-{self.version}.tar.xz",
            strip_root=True,
        )

    def generate(self):
        tc = CMakeToolchain(self)
        tc.variables["CMAKE_DEBUG_POSTFIX"] = "_d"
        tc.variables["EXPAT_DEBUG_POSTFIX"] = "_d"
        tc.variables["EXPAT_BUILD_DOCS"] = False
        tc.variables["EXPAT_BUILD_EXAMPLES"] = False
        tc.variables["EXPAT_SHARED_LIBS"] = True
        tc.variables["EXPAT_BUILD_TESTS"] = False
        tc.variables["EXPAT_BUILD_TOOLS"] = False
        tc.variables["EXPAT_BUILD_PKGCONFIG"] = False
        tc.generate()

    def build(self):
        cmake = CMake(self)
        cmake.configure()
        cmake.build()

    def package(self):
        copy(self, "COPYING", src=self.source_folder, dst=os.path.join(self.package_folder, "licenses"))
        copy(
            self,
            "*.pdb",
            src=self.build_folder,
            dst=os.path.join(self.package_folder, "bin"),
            keep_path=False,
            excludes="*vc???.pdb",
        )
        cmake = CMake(self)
        cmake.install()
        rmdir(self, os.path.join(self.package_folder, "lib", "cmake"))
        rmdir(self, os.path.join(self.package_folder, "lib", "pkgconfig"))
        rmdir(self, os.path.join(self.package_folder, "share"))

    def package_info(self):
        self.cpp_info.set_property("cpe", f"cpe:2.3:a:libexpat_project:libexpat:{self.version}:*:*:*:*:*:*:*")
        self.cpp_info.set_property("purl", f"pkg:github/libexpat/libexpat@R_{self.version.replace('.', '_')}")
        self.cpp_info.set_property("cmake_file_name", "EXPAT")
        self.cpp_info.set_property("cmake_target_name", "EXPAT::EXPAT")
        self.cpp_info.set_property("pkg_config_name", "expat")
        self.cpp_info.libs = collect_libs(self)
        if self.settings.os in ["Linux"]:
            self.cpp_info.system_libs.append("m")
