import io
import os

from conan import ConanFile
from conan.errors import ConanException
from conan.tools.build import can_run
from conan.tools.cmake import CMake, cmake_layout


class TestPackage(ConanFile):
    settings = "os", "arch", "compiler", "build_type"
    generators = "CMakeToolchain", "VirtualRunEnv"

    def layout(self):
        cmake_layout(self)

    def requirements(self):
        self.requires(self.tested_reference_str)

    def build(self):
        if self.settings.build_type == "Release" and can_run(self):
            llvm_config = os.path.join(self.dependencies["llvm"].cpp_info.bindirs[0], "llvm-config")
            cmake = CMake(self)
            cmake.configure(variables={"LLVM_CONFIG_EXECUTABLE": llvm_config})
            cmake.build()

    def test(self):
        if can_run(self):
            version = str(self.dependencies["llvm"].ref.version)
            for command, expected in (
                ("llvm-config --version", version),
                ("clang --version", f"clang version {version}"),
            ):
                output = io.StringIO()
                self.run(command, stdout=output, env="conanrun")
                if expected not in output.getvalue():
                    raise ConanException(f"'{command}' did not report version {version}: {output.getvalue()!r}")
            if self.settings.build_type == "Release":
                bin_path = os.path.join(self.cpp.build.bindirs[0], "test_package")
                self.run(bin_path, env="conanrun")
