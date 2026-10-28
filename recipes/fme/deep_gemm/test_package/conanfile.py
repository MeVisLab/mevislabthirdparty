import os
import shutil
from conan import ConanFile
from conan.tools.build import can_run
from conan.tools.cmake import CMake, CMakeToolchain, cmake_layout


class TestPackage(ConanFile):
    settings = "os", "arch", "compiler", "build_type"
    generators = "CMakeDeps", "VirtualRunEnv"

    def layout(self):
        cmake_layout(self, generator="Ninja")

    def requirements(self):
        self.requires(self.tested_reference_str)

    def generate(self):
        tc = CMakeToolchain(self, generator="Ninja")
        tc.variables["CMAKE_CUDA_ARCHITECTURES"] = "90-real"
        nvcc = os.environ.get("CUDACXX", shutil.which("nvcc"))
        if nvcc:
            tc.variables["CMAKE_CUDA_COMPILER"] = nvcc.replace("\\", "/")
        tc.generate()

    def build(self):
        cmake = CMake(self)
        cmake.configure()
        cmake.build()

    def test(self):
        if can_run(self):
            bin_path = os.path.join(self.cpp.build.bindirs[0], "test_package")
            self.run(f"{bin_path}", env="conanrun")
