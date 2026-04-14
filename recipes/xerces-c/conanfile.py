from pathlib import Path
from conan import ConanFile
from conan.tools.cmake import CMake, CMakeToolchain, CMakeDeps, cmake_layout
from conan.tools.files import collect_libs, copy, get, patch, save, rmdir
import os

required_conan_version = ">=2.2.2"


class ConanRecipe(ConanFile):
    name = "xerces-c"
    version = "3.3.0"
    homepage = "https://xml.apache.org/xerces-c"
    description = "A validating XML parser written in a portable subset of C++"
    license = "Apache-2.0"
    package_type = "shared-library"
    settings = "os", "arch", "compiler", "build_type"
    exports_sources = "CMakeLists.txt", "patches/*.patch"

    def requirements(self):
        self.requires("icu/[>=78.1]")

    def layout(self):
        cmake_layout(self, src_folder="src")

    def source(self):
        get(
            self,
            sha256="9555f1d06f82987fbb4658862705515740414fd34b4db6ad2ed76a2dc08d3bde",
            url=f"https://dlcdn.apache.org/xerces/c/3/sources/xerces-c-{self.version}.tar.gz",
            strip_root=True,
        )
        patch(self, patch_file="patches/001-debug_postfix.patch")
        patch(self, patch_file="patches/002-fix_utf16_str.patch")
        save(self, path=os.path.join(self.source_folder, "cmake", "XercesWarnings.cmake"), content="")
        save(self, path=os.path.join(self.source_folder, "doc", "CMakeLists.txt"), content="")

    def generate(self):
        tc = CMakeToolchain(self)
        tc.variables["BUILD_SHARED_LIBS"] = True
        tc.variables["CMAKE_DEBUG_POSTFIX"] = "_d"
        tc.variables["NSL_LIBRARY"] = "NSL_LIBRARY-NOTFOUND"
        tc.variables["network"] = False
        tc.generate()
        deps = CMakeDeps(self)
        deps.generate()

    def build(self):
        cmake = CMake(self)
        cmake.configure()
        cmake.build()

    def package(self):
        copy(self, "LICENSE", src=self.source_folder, dst=os.path.join(self.package_folder, "licenses"))
        cmake = CMake(self)
        cmake.install()
        bin_folder = os.path.join(self.package_folder, "bin")
        if self.settings.os == "Windows":
            [f.unlink() for f in Path(bin_folder).glob("*.exe") if f.is_file()]
        else:
            rmdir(self, bin_folder)
        copy(self, "*.pdb", src=self.build_folder, dst=bin_folder, keep_path=False, excludes="*vc???.pdb")
        rmdir(self, os.path.join(self.package_folder, "share"))
        rmdir(self, os.path.join(self.package_folder, "cmake"))
        rmdir(self, os.path.join(self.package_folder, "lib", "cmake"))
        rmdir(self, os.path.join(self.package_folder, "lib", "pkgconfig"))

    def package_info(self):
        self.cpp_info.set_property("cpe", f"cpe:2.3:a:apache:xerces-c\+\+:{self.version}:*:*:*:*:*:*:*")
        self.cpp_info.set_property("purl", f"pkg:github/apache/xerces-c@v{self.version}")
        self.cpp_info.set_property("cmake_file_name", "XercesC")
        self.cpp_info.set_property("cmake_target_name", "XercesC::XercesC")
        self.cpp_info.set_property("display_name", "Xerces-C++")
        self.cpp_info.set_property("pkg_config_name", "xerces-c")
        self.cpp_info.libs = collect_libs(self)
        if self.settings.os == "Linux":
            self.cpp_info.system_libs.extend(["pthread"])
