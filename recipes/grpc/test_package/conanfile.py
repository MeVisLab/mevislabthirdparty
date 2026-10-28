from conan import ConanFile
from conan.errors import ConanException
from conan.tools.build import can_run
from conan.tools.cmake import CMake, cmake_layout
import os


class TestPackage(ConanFile):
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
        plugin_suffix = ".exe" if self.settings.os == "Windows" else ""
        grpc_bindir = self.dependencies["grpc"].cpp_info.bindirs[0]
        for plugin in ("grpc_cpp_plugin", "grpc_python_plugin"):
            if not os.path.isfile(os.path.join(grpc_bindir, plugin + plugin_suffix)):
                raise ConanException(f"{plugin} not found in {grpc_bindir}")
        if can_run(self):
            bin_path = os.path.join(self.cpp.build.bindirs[0], "test_package")
            self.run(bin_path, env="conanrun")
