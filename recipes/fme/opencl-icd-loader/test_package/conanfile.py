import os

from conan import ConanFile
from conan.tools.build import can_run
from conan.tools.cmake import CMake, cmake_layout


class TestPackage(ConanFile):
    settings = "os", "arch", "compiler", "build_type"
    generators = "CMakeToolchain", "CMakeDeps", "VirtualRunEnv"

    def layout(self):
        cmake_layout(self)

    def requirements(self):
        self.requires(self.tested_reference_str)
        self.requires("opencl-headers/[>=2021.06.30]")

    def build(self):
        cmake = CMake(self)
        cmake.configure()
        cmake.build()

    def test(self):
        if can_run(self):
            self.run(os.path.join(self.cpp.build.bindirs[0], "test_package"), env="conanrun")
