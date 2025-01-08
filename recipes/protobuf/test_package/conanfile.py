from conan import ConanFile
from conan.tools.build import can_run
from conan.tools.cmake import CMake, cmake_layout
import os


class TestPackage(ConanFile):
    settings = "os", "arch", "compiler", "build_type"
    generators = "CMakeToolchain", "CMakeDeps", "VirtualBuildEnv", "VirtualRunEnv"

    def layout(self):
        cmake_layout(self)

    def requirements(self):
        self.requires(self.tested_reference_str)

    def build(self):
        cmake = CMake(self)
        cmake.configure(variables={"TESTPACKAGE_MODULE_MODE": "config"})
        cmake.build()

        cmake.configure(variables={"TESTPACKAGE_MODULE_MODE": "module"})
        cmake.build()

    def test(self):
        if can_run(self):
            self.run(os.path.join(self.cpp.build.bindirs[0], "test_package_config"), env="conanrun")
            self.run(os.path.join(self.cpp.build.bindirs[0], "test_package_module"), env="conanrun")
