import os

from conan import ConanFile
from conan.tools.cmake import CMake, CMakeToolchain, cmake_layout
from conan.tools.files import copy, get, rmdir

required_conan_version = ">=2.32.0"


class ConanRecipe(ConanFile):
    name = "sheenbidi"
    version = "3.0.0"
    homepage = "https://github.com/Tehreer/SheenBidi"
    description = "A lightweight, fast and stable implementation of the Unicode Bidirectional Algorithm"
    license = "Apache-2.0"
    settings = "os", "arch", "compiler", "build_type"
    package_type = "shared-library"

    def configure(self):
        self.settings.rm_safe("compiler.cppstd")
        self.settings.rm_safe("compiler.libcxx")

    def layout(self):
        cmake_layout(self, src_folder="src")

    def source(self):
        get(
            self,
            sha256="86c56014034739ba39a24c23eb00323b0bf6f737354f665786015fca842af786",
            url=f"https://github.com/Tehreer/SheenBidi/archive/refs/tags/v{self.version}.tar.gz",
            strip_root=True,
        )

    def generate(self):
        tc = CMakeToolchain(self)
        tc.variables["BUILD_SHARED_LIBS"] = True
        tc.variables["BUILD_TESTING"] = False
        tc.variables["BUILD_GENERATOR"] = False
        tc.variables["CMAKE_DEBUG_POSTFIX"] = "_d"
        tc.variables["CMAKE_INSTALL_RPATH"] = "$ORIGIN;$ORIGIN/../lib"
        tc.generate()

    def build(self):
        cmake = CMake(self)
        cmake.configure()
        cmake.build()

    def package(self):
        copy(self, "LICENSE", src=self.source_folder, dst=os.path.join(self.package_folder, "licenses"))
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
        rmdir(self, os.path.join(self.package_folder, "lib", "cmake"))
        rmdir(self, os.path.join(self.package_folder, "lib", "pkgconfig"))

    def package_info(self):
        # self.cpp_info.set_property("cpe", "")  # No CPE (yet)?
        self.cpp_info.set_property("purl", f"pkg:github/Tehreer/SheenBidi@v{self.version}")
        self.cpp_info.set_property("cmake_file_name", "SheenBidi")
        self.cpp_info.set_property("cmake_target_name", "SheenBidi::SheenBidi")
        # libraqm looks the library up as "sheenbidi" via pkg-config
        self.cpp_info.set_property("pkg_config_name", "sheenbidi")
        suffix = "_d" if self.settings.build_type == "Debug" else ""
        self.cpp_info.libs = [f"SheenBidi{suffix}"]
        if self.settings.os == "Windows":
            # matches the INTERFACE definition of the installed CMake target
            self.cpp_info.defines = ["SB_CONFIG_DLL_IMPORT"]
