from conan import ConanFile
from conan.tools.cmake import CMake, CMakeToolchain, cmake_layout
from conan.tools.files import collect_libs, get, copy
import os

required_conan_version = ">=2.2.2"


class ConanRecipe(ConanFile):
    name = "hunspell"
    version = "1.7.2"
    homepage = "http://hunspell.github.io"
    description = "Hunspell spell checker - an improved replacement for myspell"
    license = "MPL-1.1"
    package_type = "shared-library"
    settings = "os", "arch", "compiler", "build_type"
    exports_sources = "CMakeLists.txt"

    def layout(self):
        cmake_layout(self, src_folder="src")

    def source(self):
        sha256 = "11ddfa39afe28c28539fe65fc4f1592d410c1e9b6dd7d8a91ca25d85e9ec65b8"
        url = f"https://github.com/hunspell/hunspell/releases/download/v{self.version}/hunspell-{self.version}.tar.gz"
        get(self, sha256=sha256, url=url, strip_root=True)

    def generate(self):
        tc = CMakeToolchain(self)
        tc.variables["BUILD_SHARED_LIBS"] = True
        tc.variables["CMAKE_DEBUG_POSTFIX"] = "_d"
        tc.cache_variables["CONAN_PROJECT_VERSION"] = f"{self.version}"
        tc.generate()

    def build(self):
        cmake = CMake(self)
        cmake.configure(build_script_folder=os.path.dirname(self.source_folder))
        cmake.build()

    def package(self):
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

    def package_info(self):
        self.cpp_info.set_property("cpe", "cpe:2.3:a:hunspell_project:hunspell:*:*:*:*:*:*:*:*")
        self.cpp_info.set_property("purl", f"pkg:github/hunspell/hunspell@v{self.version}")
        self.cpp_info.set_property("cmake_file_name", "Hunspell")
        self.cpp_info.set_property("cmake_target_name", "Hunspell::Hunspell")
        self.cpp_info.includedirs = ["include", "include/hunspell"]
        self.cpp_info.libs = collect_libs(self)
