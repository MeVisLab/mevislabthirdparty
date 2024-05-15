import sys

from conan import ConanFile
import os

from conan.tools.build import can_run
from conan.tools.cmake import cmake_layout, CMake


class TestPackage(ConanFile):
    test_allow_fail = sys.platform in ("win32", "darwin")
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
            test_args = os.path.join(self.source_folder, "OpenSans-Bold.ttf")
            bin_path = os.path.join(self.cpp.build.bindirs[0], "test_package")
            self.run(f"{bin_path} {test_args}", env="conanrun", ignore_errors=self.settings.os == "Windows")
