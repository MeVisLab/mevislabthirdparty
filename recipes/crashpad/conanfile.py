from conan import ConanFile
from conan.errors import ConanInvalidConfiguration
from conan.tools.cmake import CMake, CMakeToolchain, cmake_layout
from conan.tools.files import copy, get, collect_libs
import os

required_conan_version = ">=2.32.0"


class ConanRecipe(ConanFile):
    name = "crashpad"
    version = "0.3.0"
    license = "Apache-2.0"
    homepage = "https://github.com/backtrace-labs/crashpad"
    description = "crashpad"
    settings = "os", "arch", "compiler", "build_type"
    package_type = "static-library"

    def validate_build(self):
        if self.settings.build_type != "Release":
            raise ConanInvalidConfiguration(f"{self.name} is built in release mode only.")
        if self.settings.os == "Linux":
            raise ConanInvalidConfiguration(f"{self.name} is only built for windows.")

    def package_id(self):
        self.info.settings.rm_safe("build_type")
        self.info.settings.rm_safe("compiler.runtime_type")

    def layout(self):
        cmake_layout(self, src_folder="src")

    def requirements(self):
        self.requires("zlib/[>=1.2.13]")

    def source(self):
        get(
            self,
            sha256="9e9bd9b7ca88b02f227c7208d4fb7a286c55dbb7a54893bf51573882d60290b1",
            url=f"https://github.com/backtrace-labs/crashpad/archive/refs/tags/v{self.version}.tar.gz",
            strip_root=False,
        )
        get(
            self,
            sha256="eda09e54814b7396bfe7b4969afc9e3bca24775716d3c1d773575f1adcac9269",
            url=f"https://github.com/chromium/mini_chromium/archive/40dabd18facfcb07a633ce44c8d8c6c6b7479e54.zip",
            destination=os.path.join(
                self.source_folder, f"crashpad-{self.version}", "third_party", "mini_chromium", "mini_chromium"
            ),
            strip_root=True,
        )

    def generate(self):
        tc = CMakeToolchain(self)
        tc.variables["CMAKE_DEBUG_POSTFIX"] = "_d"
        tc.cache_variables["BUILD_SHARED_LIBS"] = False
        tc.cache_variables["CMAKE_POSITION_INDEPENDENT_CODE"] = True
        tc.generate()

    def build(self):
        cmake = CMake(self)
        cmake.configure(build_script_folder=f"crashpad-{self.version}")
        cmake.build()

    def package(self):
        copy(
            self,
            "LICENSE",
            src=os.path.join(self.source_folder, f"crashpad-{self.version}"),
            dst=os.path.join(self.package_folder, "licenses"),
            keep_path=False,
        )
        copy(
            self,
            pattern="*.h",
            src=os.path.join(self.source_folder, f"crashpad-{self.version}"),
            dst=os.path.join(self.package_folder, "include", "crashpad"),
        )
        copy(
            self, pattern="*.lib", src=self.build_folder, dst=os.path.join(self.package_folder, "lib"), keep_path=False
        )
        copy(
            self,
            pattern="*handler.exe",
            src=self.build_folder,
            dst=os.path.join(self.package_folder, "bin"),
            keep_path=False,
        )

    def package_info(self):
        # self.cpp_info.set_property("cpe", "")  # No CPE yet?
        self.cpp_info.set_property("purl", f"pkg:github/backtrace-labs/crashpad@v{self.version}")
        self.cpp_info.set_property("cmake_find_mode", "both")
        self.cpp_info.set_property("cmake_file_name", "CrashPad")
        self.cpp_info.set_property("cmake_target_name", "CrashPad::CrashPad")
        self.cpp_info.includedirs.append("include/crashpad")
        self.cpp_info.includedirs.append("include/crashpad/third_party/mini_chromium/mini_chromium")
        self.cpp_info.libs = collect_libs(self)
        if self.settings.os == "Linux":
            self.cpp_info.system_libs.extend(["curl"])
