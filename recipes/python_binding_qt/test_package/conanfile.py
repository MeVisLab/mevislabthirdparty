import os

from conan import ConanFile
from conan.tools.build import can_run
from conan.tools.cmake import CMake, CMakeDeps, CMakeToolchain, cmake_layout
from conan.tools.env import Environment, VirtualRunEnv


class TestPackage(ConanFile):
    settings = "os", "arch", "compiler", "build_type"

    def layout(self):
        cmake_layout(self)

    def requirements(self):
        self.requires(self.tested_reference_str)
        self.requires("pythonqt/[>=4.1.0]")

    def generate(self):
        env = VirtualRunEnv(self)
        env.generate()
        tc = CMakeToolchain(self, generator="Ninja")
        tc.generate()
        deps = CMakeDeps(self)
        deps.generate()

        python_version = self.dependencies["python"].ref.version
        if self.settings.os == "Windows":
            site_packages = os.path.join("Lib", "site-packages")
        else:
            site_packages = os.path.join("lib", f"python{python_version.major}.{python_version.minor}", "site-packages")
        env = Environment()
        env.prepend_path(
            "PYTHONPATH", os.path.join(self.dependencies["python_binding_qt"].package_folder, site_packages)
        )
        env.define("PYTHONDONTWRITEBYTECODE", "1")
        env.vars(self, scope="run").save_script("python_binding_qt_env")

    def build(self):
        cmake = CMake(self)
        cmake.configure()
        cmake.build()

    def test(self):
        if can_run(self):
            bin_path = os.path.join(self.cpp.build.bindirs[0], "test_package")
            self.run(f'"{bin_path}"', env="conanrun", ignore_errors=(self.settings.os == "Windows"))
