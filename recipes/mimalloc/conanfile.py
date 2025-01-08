import os
from conan import ConanFile
from conan.tools.cmake import CMake, CMakeToolchain, cmake_layout
from conan.tools.files import copy, get, rmdir, collect_libs

required_conan_version = ">=2.2.2"


class ConanRecipe(ConanFile):
    name = "mimalloc"
    version = "2.1.7"
    license = "MIT"
    homepage = "https://github.com/microsoft/mimalloc"
    description = "mimalloc is a compact general purpose allocator with excellent performance"
    settings = "os", "arch", "compiler", "build_type"
    package_type = "static-library"

    def configure(self):
        self.settings.rm_safe("compiler.libcxx")
        self.settings.rm_safe("compiler.cppstd")

    def layout(self):
        cmake_layout(self, src_folder="src")

    def source(self):
        get(
            self,
            sha256="0eed39319f139afde8515010ff59baf24de9e47ea316a315398e8027d198202d",
            url=f"https://github.com/microsoft/mimalloc/archive/v{self.version}.tar.gz",
            strip_root=True,
        )

    def generate(self):
        tc = CMakeToolchain(self)
        tc.variables["BUILD_SHARED_LIBS"] = False
        tc.variables["CMAKE_POSITION_INDEPENDENT_CODE"] = True
        tc.variables["CMAKE_DEBUG_POSTFIX"] = "_d"
        tc.variables["MI_BUILD_TESTS"] = False
        tc.variables["MI_BUILD_SHARED"] = False
        tc.variables["MI_BUILD_STATIC"] = True
        tc.variables["MI_WIN_REDIRECT"] = False
        tc.variables["MI_OVERRIDE"] = False
        tc.variables["MI_OSX_INTERPOSE"] = False
        tc.variables["MI_OSX_ZONE"] = False
        tc.variables["MI_WIN_REDIRECT"] = False
        tc.variables["MI_DEBUG_FULL"] = self.settings.build_type == "Debug"
        tc.variables["MI_INSTALL_TOPLEVEL"] = True
        tc.generate()

    def build(self):
        cmake = CMake(self)
        cmake.configure()
        cmake.build()

    def package(self):
        copy(self, pattern="LICENSE", dst=os.path.join(self.package_folder, "licenses"), src=self.source_folder)
        cmake = CMake(self)
        cmake.install()
        rmdir(self, os.path.join(self.package_folder, "cmake"))
        rmdir(self, os.path.join(self.package_folder, "lib", "cmake"))
        rmdir(self, os.path.join(self.package_folder, "lib", "pkgconfig"))
        rmdir(self, os.path.join(self.package_folder, "share"))

    def package_info(self):
        #self.cpp_info.set_property("cpe", "")
        self.cpp_info.set_property("base_purl", "github/microsoft/mimalloc")

        self.cpp_info.set_property("cmake_find_mode", "both")
        self.cpp_info.set_property("cmake_file_name", "mimalloc")
        self.cpp_info.set_property("cmake_target_name", "mimalloc::mimalloc")
        self.cpp_info.libs = collect_libs(self)
        if self.settings.os == "Linux":
            self.cpp_info.system_libs.extend(["pthread", "rt"])
        elif self.settings.os == "Windows":
            self.cpp_info.system_libs.extend(["psapi", "shell32", "user32", "bcrypt"])
        