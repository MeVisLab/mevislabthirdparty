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
        self.requires(self.tested_reference_str, run=True)

    @property
    def _is_windows_release(self):
        return self.settings.os == "Windows" and self.settings.build_type == "Release"

    def build(self):
        if self._is_windows_release:
            cmake = CMake(self)
            cmake.configure()
            cmake.build()

    def test(self):
        if self._is_windows_release and can_run(self):
            self.run("crashpad_handler --help", env="conanrun")
            bin_path = os.path.join(self.cpp.build.bindirs[0], "test_package")
            self.run(bin_path, env="conanrun")
