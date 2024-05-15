from conan import ConanFile
from conan.tools.build import can_run
from conan.tools.cmake import CMake, cmake_layout
import os


class TestPackage(ConanFile):
    settings = "os", "arch", "compiler", "build_type"
    generators = "CMakeToolchain", "CMakeDeps", "VirtualRunEnv"

    def layout(self):
        cmake_layout(self)

    def requirements(self):
        self.requires(self.tested_reference_str)
        self.requires("libxml2/[>=2.10.0]")

    def build(self):
        cmake = CMake(self)
        cmake.configure()
        cmake.build()

    def test(self):
        if can_run(self):
            bin_path = os.path.join(self.cpp.build.bindirs[0], "test_package")
            arg_path1 = os.path.join(self.recipe_folder, "example.xsl")
            arg_path2 = os.path.join(self.recipe_folder, "example.xml")
            self.run(f"{bin_path} {arg_path1} {arg_path2}", env="conanrun")
