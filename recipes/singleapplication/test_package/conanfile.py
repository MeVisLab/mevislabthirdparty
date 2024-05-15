import os

from conan import ConanFile
from conan.tools.env import VirtualRunEnv
from conan.tools.build import can_run
from conan.tools.cmake import CMake, CMakeDeps, CMakeToolchain, cmake_layout


class TestPackage(ConanFile):
    settings = "os", "arch", "compiler", "build_type"

    def layout(self):
        cmake_layout(self)

    def requirements(self):
        self.requires(self.tested_reference_str)

    def generate(self):
        env = VirtualRunEnv(self)
        env.generate(scope="build")
        tc = CMakeToolchain(self, generator="Ninja")
        tc.generate()
        deps = CMakeDeps(self)
        deps.generate()

    def build(self):
        cmake = CMake(self)
        cmake.configure()
        cmake.build()

    def test(self):
        # do not run in Jenkins (e.g. in a container) as we need a GUI context
        if can_run(self) and not os.getenv("JENKINS_URL"):
            cmake = CMake(self)
            cmake.test()
