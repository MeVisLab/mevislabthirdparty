from conan import ConanFile
from conan.tools.cmake import CMake, CMakeDeps, CMakeToolchain, cmake_layout
from conan.tools.files import collect_libs
from conan.tools.files import get, copy, rmdir
import os

required_conan_version = ">=2.2.2"


class ConanRecipe(ConanFile):
    name = "libpng"
    version = "1.6.50"
    homepage = "http://www.libpng.org/pub/png/libpng.html"
    description = "Portable Network Graphics library"
    license = "Libpng"
    package_type = "shared-library"
    settings = "os", "arch", "compiler", "build_type"
    exports_sources = "patches/*.patch"

    def configure(self):
        self.settings.rm_safe("compiler.libcxx")
        self.settings.rm_safe("compiler.cppstd")

    def layout(self):
        cmake_layout(self, src_folder="src")

    def requirements(self):
        self.requires("zlib/[>=1.2.11]")

    def source(self):
        get(
            self,
            sha256="708f4398f996325819936d447f982e0db90b6b8212b7507e7672ea232210949a",
            url=f"https://download.sourceforge.net/libpng/libpng-{self.version}.tar.gz",
            strip_root=True,
        )

    def generate(self):
        tc = CMakeToolchain(self)
        tc.variables["CMAKE_DEBUG_POSTFIX"] = "_d"
        tc.variables["PNG_DEBUG_POSTFIX"] = "_d"
        tc.variables["BUILD_SHARED_LIBS"] = True
        tc.variables["CMAKE_INSTALL_RPATH"] = "$ORIGIN;$ORIGIN/../lib"
        tc.variables["CMAKE_INSTALL_LIBDIR"] = "lib"
        tc.variables["CMAKE_INSTALL_BINDIR"] = "bin"
        tc.variables["CMAKE_INSTALL_INCLUDEDIR"] = "include"
        tc.variables["PNG_TESTS"] = False
        tc.variables["PNG_SHARED"] = True
        tc.variables["PNG_STATIC"] = False
        tc.variables["PNG_DEBUG"] = self.settings.build_type != "Release"
        tc.generate()
        tc = CMakeDeps(self)
        tc.generate()

    def build(self):
        cmake = CMake(self)
        cmake.configure()
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
        rmdir(self, os.path.join(self.package_folder, "lib", "libpng"))  # cmake files
        rmdir(self, os.path.join(self.package_folder, "lib", "cmake"))
        rmdir(self, os.path.join(self.package_folder, "lib", "pkgconfig"))
        rmdir(self, os.path.join(self.package_folder, "share"))

    def package_info(self):
        self.cpp_info.set_property("cpe", "cpe:2.3:a:libpng:libpng:*:*:*:*:*:*:*:*")
        self.cpp_info.set_property("purl", f"pkg:github/pnggroup/libpng@v{self.version}")
        self.cpp_info.set_property("cmake_find_mode", "both")
        self.cpp_info.set_property("cmake_file_name", "PNG")
        self.cpp_info.set_property("cmake_target_name", "PNG::PNG")
        self.cpp_info.set_property("pkg_config_name", "libpng")
        self.cpp_info.libs = collect_libs(self)

        if self.settings.os == "Linux":
            self.cpp_info.system_libs.append("m")
