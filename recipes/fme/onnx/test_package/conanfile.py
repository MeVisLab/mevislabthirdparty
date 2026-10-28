import os

from conan import ConanFile
from conan.tools.build import can_run
from conan.tools.cmake import CMake, cmake_layout
from conan.tools.env import Environment


class TestPackage(ConanFile):
    settings = "os", "arch", "compiler", "build_type"
    generators = "CMakeToolchain", "CMakeDeps", "VirtualBuildEnv"
    python_requires = "python_package/[>=1.0.0]"
    python_requires_extend = "python_package.PythonPackageBase"

    @property
    def has_requirements_txt(self):
        return True

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
            self.run(f"{os.path.join(self.cpp.build.bindirs[0], 'test_package')}", env="conanrun")
            with self.install_packages(os.path.join(self.source_folder, "requirements.txt")):
                env = Environment()
                env.append_path("PYTHONPATH", self.site_packages_path)
                with env.vars(self).apply():
                    self.run(f'"{self.py_command}" -B {os.path.join(self.source_folder, "test.py")}', env="conanrun")
