from conan import ConanFile
from conan.tools.cmake import CMake, CMakeDeps, CMakeToolchain, cmake_layout
from conan.tools.files import collect_libs
from conan.tools.files import get, copy
from conan.tools.scm import Version
import os

required_conan_version = ">=2.2.2"


class ConanRecipe(ConanFile):
    name = "minizip"
    version = "1.3.1"
    homepage = "https://zlib.net"
    description = "A Massively Spiffy Yet Delicately Unobtrusive Compression Library"
    license = "Zlib"
    package_type = "shared-library"
    settings = "os", "arch", "compiler", "build_type"
    exports_sources = "CMakeLists.txt", "minizip-win32.def", "patches/*.patch"

    def configure(self):
        self.settings.rm_safe("compiler.libcxx")
        self.settings.rm_safe("compiler.cppstd")

    def layout(self):
        cmake_layout(self, src_folder="src")

    def requirements(self):
        self.requires("zlib/[>=1.3.0]", transitive_headers=True)
        self.requires("bzip2/[>=1.0.8]", transitive_headers=True)

    def source(self):
        v = Version(self.version)
        vstr = f"{v.major}.{v.minor}" + ("" if v.patch == 0 else f".{v.patch}")
        get(
            self,
            sha256="9a93b2b7dfdac77ceba5a558a580e74667dd6fede4585b91eefb60f03b72df23",
            url=f"https://github.com/madler/zlib/releases/download/v{vstr}/zlib-{vstr}.tar.gz",
            strip_root=True,
        )

    def generate(self):
        tc = CMakeToolchain(self)
        tc.variables["CMAKE_DEBUG_POSTFIX"] = "_d"
        tc.variables["BUILD_SHARED_LIBS"] = True
        tc.variables["CMAKE_C_VISIBILITY_PRESET"] = "default"
        tc.variables["CMAKE_CXX_VISIBILITY_PRESET"] = "default"
        tc.variables["CMAKE_VISIBILITY_INLINES_HIDDEN"] = False
        tc.generate()
        tc = CMakeDeps(self)
        tc.generate()

    def build(self):
        cmake = CMake(self)
        cmake.configure(build_script_folder=os.path.dirname(self.source_folder))
        cmake.build()

    def package(self):
        cmake = CMake(self)
        cmake.install()
        copy(self, "LICENSE", src=self.source_folder, dst=os.path.join(self.package_folder, "licenses"))
        copy(
            self,
            "*.pdb",
            src=self.build_folder,
            dst=os.path.join(self.package_folder, "bin"),
            keep_path=False,
            excludes="*vc???.pdb",
        )

    def package_info(self):
        self.cpp_info.set_property("cpe", "cpe:2.3:a:zlib:zlib:*:*:*:*:*:*:*:*")
        self.cpp_info.set_property("purl", f"pkg:github/madler/zlib@v{self.version}")
        self.cpp_info.set_property("cmake_find_mode", "both")
        self.cpp_info.set_property("cmake_file_name", "Minizip")
        self.cpp_info.set_property("cmake_target_name", "Minizip::Minizip")
        self.cpp_info.libs = collect_libs(self)
        self.cpp_info.includedirs.append("include/minizip")

        if self.settings.os == "Linux":
            self.cpp_info.system_libs.append("m")
