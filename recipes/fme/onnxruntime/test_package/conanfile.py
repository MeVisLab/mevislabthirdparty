import os

from conan import ConanFile
from conan.tools.build import can_run
from conan.tools.cmake import CMake, cmake_layout


class TestPackage(ConanFile):
    settings = "os", "arch", "compiler", "build_type"
    generators = "CMakeToolchain", "CMakeDeps"
    python_requires = "python_package/[>=1.0.0]"
    python_requires_extend = "python_package.PythonPackageTest"

    @property
    def has_requirements_txt(self):
        return True

    def layout(self):
        cmake_layout(self)

    def build(self):
        cmake = CMake(self)
        cmake.configure()
        cmake.build()

    def test(self):
        if can_run(self):
            fbs_path = os.path.join(self.source_folder, "monster.fbs")
            bin_path = os.path.join(self.cpp.build.bindirs[0], "test_package")
            self.run(f"{bin_path} {fbs_path}", env="conanrun")
            super().test()
