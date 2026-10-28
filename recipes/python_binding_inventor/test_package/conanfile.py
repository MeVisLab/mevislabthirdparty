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
        self.requires("pythonqt/[>=4.0.0]")

    def generate(self):
        env = VirtualRunEnv(self)
        env.generate()
        site_packages = self.dependencies["python"].runenv_info.vars(self).get("MEVIS_PYTHON_SITE_PACKAGES_FOLDER")
        pythonpath = Environment()
        pythonpath.append_path(
            "PYTHONPATH", os.path.join(self.dependencies["python_binding_inventor"].package_folder, site_packages)
        )
        pythonpath.define("PYTHONDONTWRITEBYTECODE", "1")
        pythonpath.vars(self, scope="run").save_script("pythonpath")
        tc = CMakeToolchain(self, generator="Ninja")
        tc.generate()
        deps = CMakeDeps(self)
        deps.generate()

    def build(self):
        cmake = CMake(self)
        cmake.configure()
        cmake.build()

    def test(self):
        if can_run(self):
            bin_path = os.path.join(self.cpp.build.bindirs[0], "test_package")
            test_script = os.path.join(self.source_folder, "test.py")
            self.run(f'"{bin_path}" "{test_script}"', env="conanrun", ignore_errors=(self.settings.os == "Windows"))
