import os

from conan import ConanFile
from conan.tools.cmake import CMake, CMakeToolchain
from conan.tools.files import copy, collect_libs

required_conan_version = ">=2.2.2"


class ConanRecipe(ConanFile):
    name = "lzf"
    version = "3.5.0"
    description = "Fast LZ compression library"
    homepage = "https://oldhome.schmorp.de/marc/liblzf.html"
    license = "BSD-2-Clause"
    package_type = "static-library"
    settings = "os", "arch", "compiler", "build_type"
    exports_sources = "LICENSE", "sources/**"

    def generate(self):
        tc = CMakeToolchain(self)
        tc.variables["CMAKE_DEBUG_POSTFIX"] = "_d"
        tc.variables["BUILD_SHARED_LIBS"] = False
        tc.variables['CMAKE_POSITION_INDEPENDENT_CODE'] = True
        tc.cache_variables['CONAN_LZF_VERSION'] = f"{self.version}"
        tc.generate()

    def build(self):
        cmake = CMake(self)
        cmake.configure(build_script_folder=os.path.join(self.source_folder, "sources"))
        cmake.build()

    def package(self):
        copy(self, "LICENSE", src=self.source_path, dst=self.package_path / "licenses")
        cmake = CMake(self)
        cmake.install()

    def package_info(self):
        # self.cpp_info.set_property("cpe", "")  # No CPE (yet)?
        # self.cpp_info.set_property("base_purl", "")  # Official repository is at http://oldhome.schmorp.de/marc/liblzf.html
        self.cpp_info.set_property("cmake_find_mode", "both")
        self.cpp_info.set_property("cmake_file_name", "LZF")
        self.cpp_info.set_property("cmake_target_name", "LZF::LZF")
        self.cpp_info.set_property("pkg_config_name", "LZF")
        self.cpp_info.libs = collect_libs(self)
