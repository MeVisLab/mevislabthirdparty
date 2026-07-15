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

    def build(self):
        cmake = CMake(self)
        cmake.configure()
        cmake.build()

    def test(self):
        if can_run(self):
            bin_path = os.path.join(self.cpp.build.bindirs[0], "test_package")
            aff_file = os.path.join(self.source_folder, "test.aff")
            dic_file = os.path.join(self.source_folder, "test.dic")
            self.run(f"{bin_path} {aff_file} {dic_file}", env="conanrun")
