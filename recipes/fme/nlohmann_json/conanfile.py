from conan import ConanFile
from conan.tools.cmake import CMakeToolchain, CMake, cmake_layout
from conan.tools.files import get, copy, rmdir, rm

required_conan_version = ">=2.2.2"


class ConanRecipe(ConanFile):
    name = "nlohmann_json"
    version = "3.12.0"
    homepage = "https://github.com/nlohmann/json"
    description = "A C++11 header-only JSON library with intuitive syntax, trivial integration and serious testing"
    license = "MIT"
    package_type = "header-library"
    settings = "os", "arch", "compiler", "build_type"
    package_type = "header-library"
    exports_sources = ["patches/*"]

    def configure(self):
        self.settings.rm_safe("compiler.libcxx")
        self.settings.rm_safe("compiler.cppstd")

    def layout(self):
        cmake_layout(self, src_folder="src")

    def source(self):
        get(
            self,
            sha256="4b92eb0c06d10683f7447ce9406cb97cd4b453be18d7279320f7b2f025c10187",
            url=f"https://github.com/nlohmann/json/archive/v{self.version}.tar.gz",
            strip_root=True,
        )

    def generate(self):
        tc = CMakeToolchain(self)
        tc.variables["BUILD_TESTING"] = False
        tc.variables["JSON_BuildTests"] = False
        tc.variables["JSON_Install"] = True
        tc.generate()

    def build(self):
        cmake = CMake(self)
        cmake.configure()
        cmake.build()

    def package(self):
        cmake = CMake(self)
        cmake.install()
        copy(self, "LICENSE.MIT", src=self.source_path, dst=self.package_path / "licenses")
        rmdir(self, self.package_path / "lib")
        rmdir(self, self.package_path / "share")
        rm(self, pattern="nlohmann_json.natvis", folder=self.package_folder)

    def package_info(self):
        self.cpp_info.set_property("cpe", "cpe:2.3:a:json-for-modern-cpp_project:json-for-modern-cpp:*:*:*:*:*:*:*:*")
        self.cpp_info.set_property("purl", f"pkg:github/nlohmann/json@v{self.version}")
        self.cpp_info.set_property("cmake_file_name", "nlohmann_json")
        self.cpp_info.set_property("cmake_target_name", "nlohmann_json::nlohmann_json")
        self.cpp_info.set_property("display_name", "JSON for Modern C++")
        self.cpp_info.set_property("mevislab_prosdk_exclude", True)
