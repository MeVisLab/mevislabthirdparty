from conan import ConanFile
from conan.tools.cmake import CMake, CMakeToolchain, cmake_layout
from conan.tools.env import VirtualRunEnv
from conan.tools.files import copy, get
import os

required_conan_version = ">=2.2.2"


class ConanRecipe(ConanFile):
    name = "pythonqt_generator"
    version = "3.6.1"
    homepage = "https://mevislab.github.io/pythonqt"
    description = "PythonQtGenerator creates source files from Qt Python binding for Qt"
    license = "LGPL-2.1-only"
    package_type = "application"
    settings = "os", "arch", "compiler", "build_type"
    exports_sources = "sources/**", "LICENSE"

    def layout(self):
        cmake_layout(self, src_folder="src")

    def requirements(self):
        self.requires("qtbase/[>=6.9]")
        self.requires("qt5compat/[>=6.9]")

    def source(self):
        get(
            self,
            sha256="22691217991a36692155006ff875bf6408bfaad9fee8d8153511bf25e98a5e73",
            url=f"https://github.com/MeVisLab/pythonqt/archive/refs/tags/v{self.version}.zip",
            pattern="*/generator/*",
            strip_root=True,
        )
        copy(self, "**", src=os.path.join(self.export_sources_folder, "sources"), dst=self.source_folder)

    def generate(self):
        env = VirtualRunEnv(self)
        env.generate(scope="build")
        tc = CMakeToolchain(self)
        tc.generate()

    def build(self):
        cmake = CMake(self)
        cmake.configure()
        cmake.build()

    def package(self):
        copy(self, "LICENSE", src=self.export_sources_folder, dst=os.path.join(self.package_folder, "licenses"))
        cmake = CMake(self)
        cmake.install()

    def package_info(self):
        # self.cpp_info.set_property("cpe", "")  # No CPE (yet)?
        self.cpp_info.set_property("purl", f"pkg:github/MeVisLab/pythonqt@v{self.version}")
        self.cpp_info.includedirs.clear()
        self.cpp_info.set_property("cmake_find_mode", "none")
