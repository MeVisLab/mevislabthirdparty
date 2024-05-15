from conan import ConanFile
from conan.tools.cmake import CMakeToolchain, CMake, cmake_layout
from conan.tools.files import copy, collect_libs

required_conan_version = ">=2.2.2"

class ConanRecipe(ConanFile):
    name = "spline"
    version = "1.0.0"
    homepage = "https://people.sc.fsu.edu/~jburkardt/cpp_src/spline/spline.html"
    description = "SPLINE, a C++ code which constructs and evaluates spline functions"
    license = "LGPL-3.0-or-later"
    package_type = "shared-library"
    settings = "os", "arch", "compiler", "build_type"
    exports_sources = ["sources/*", "LICENSE"]

    def layout(self):
        cmake_layout(self, src_folder="sources")

    def generate(self):
        tc = CMakeToolchain(self)
        tc.variables["CMAKE_DEBUG_POSTFIX"] = "_d"
        tc.variables["BUILD_SHARED_LIBS"] = True
        tc.generate()

    def build(self):
        cmake = CMake(self)
        cmake.configure()
        cmake.build()

    def package(self):
        cmake = CMake(self)
        cmake.install()

        copy(self, "LICENSE", src=self.export_sources_path, dst=self.package_path / "licenses")
        copy(self, "*.pdb", src=self.build_path, dst=self.package_path / "bin", keep_path=False, excludes="*vc???.pdb")

    def package_info(self):
        self.cpp_info.set_property("display_name", "SPLINE")
        self.cpp_info.set_property("mevislab_prosdk_exclude", True)
        self.cpp_info.libs = collect_libs(self)
