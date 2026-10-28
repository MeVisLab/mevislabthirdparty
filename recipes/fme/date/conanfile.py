import os

from conan import ConanFile
from conan.tools.cmake import CMake, CMakeToolchain, cmake_layout
from conan.tools.files import copy, get

required_conan_version = ">=2.32.0"


class ConanRecipe(ConanFile):
    name = "date"
    version = "3.0.5"
    homepage = "https://github.com/HowardHinnant/date"
    description = "A date and time library based on the C++11/14/17 <chrono> header"
    license = "MIT"
    package_type = "static-library"
    settings = "os", "arch", "compiler", "build_type"

    def package_id(self):
        self.info.clear()

    def layout(self):
        cmake_layout(self, src_folder="src")

    def source(self):
        get(
            self,
            sha256="ef786edc203daec76475825640b3af247bd08e31fc52217e5ce8f76107b4bb05",
            url=f"https://github.com/HowardHinnant/date/archive/refs/tags/v{self.version}.tar.gz",
            strip_root=True,
        )

    def generate(self):
        tc = CMakeToolchain(self)
        tc.variables["CMAKE_CXX_STANDARD"] = 20
        tc.variables["CMAKE_DEBUG_POSTFIX"] = "_d"
        tc.variables["BUILD_SHARED_LIBS"] = False
        tc.variables["CMAKE_POSITION_INDEPENDENT_CODE"] = True
        tc.variables["ENABLE_DATE_TESTING"] = False
        tc.variables["USE_SYSTEM_TZ_DB"] = False
        tc.variables["USE_TZ_DB_IN_DOT"] = False
        tc.variables["BUILD_TZ_LIB"] = False
        tc.generate()

    def build(self):
        cmake = CMake(self)
        cmake.configure()
        cmake.build()

    def package(self):
        copy(self, "LICENSE.txt", src=self.source_folder, dst=os.path.join(self.package_folder, "licenses"))
        copy(
            self,
            "*.h",
            src=os.path.join(self.source_folder, "include", "date"),
            dst=os.path.join(self.package_folder, "include", "date"),
        )

    def package_info(self):
        self.cpp_info.set_property("cmake_file_name", "date")
        self.cpp_info.set_property("cmake_target_name", "date::date")

        self.cpp_info.bindirs = []
        self.cpp_info.libdirs = []
        self.cpp_info.defines.append("DATE_HEADER_ONLY")
