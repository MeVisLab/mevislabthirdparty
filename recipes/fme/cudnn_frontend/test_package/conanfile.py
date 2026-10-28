import glob
import os

from conan import ConanFile
from conan.errors import ConanException
from conan.tools.build import can_run
from conan.tools.cmake import CMake, cmake_layout
from conan.tools.env import Environment


class TestPackage(ConanFile):
    settings = "os", "arch", "compiler", "build_type"
    generators = "CMakeToolchain", "CMakeDeps", "VirtualRunEnv"

    def layout(self):
        cmake_layout(self)

    def requirements(self):
        self.requires(self.tested_reference_str)

    def generate(self):
        if self.settings.os == "Windows":
            cudnn_root = os.environ.get("CUDNN_ROOT", "C:/Program Files/NVIDIA/CUDNN")
            dlls = sorted(glob.glob(os.path.join(cudnn_root, "**", "cudnn64_*.dll"), recursive=True))
            if not dlls:
                raise ConanException(f"cudnn64_*.dll not found below {cudnn_root}")
            env = Environment()
            env.prepend_path("PATH", os.path.dirname(dlls[-1]))
            env.vars(self, scope="run").save_script("cudnn_runenv")

    def build(self):
        cmake = CMake(self)
        cmake.configure()
        cmake.build()

    def test(self):
        if can_run(self):
            bin_path = os.path.join(self.cpp.build.bindirs[0], "test_package")
            self.run(f"{bin_path}", env="conanrun")
