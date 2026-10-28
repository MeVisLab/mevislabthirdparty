from conan import ConanFile
from conan.tools.cmake import CMake, CMakeToolchain, cmake_layout
from conan.tools.env import VirtualRunEnv
from conan.tools.files import copy, get
import os

required_conan_version = ">=2.32.0"


class ConanRecipe(ConanFile):
    name = "pythonqt_generator"
    version = "4.2.0"
    homepage = "https://mevislab.github.io/pythonqt"
    description = "PythonQtGenerator creates source files from Qt Python binding for Qt"
    license = "LGPL-2.1-only"
    package_type = "application"
    settings = "os", "arch", "compiler", "build_type"
    exports_sources = "sources/**", "LICENSE"

    def layout(self):
        cmake_layout(self, src_folder="src")

    def requirements(self):
        self.requires("qtbase/[>=6.10]")

    def source(self):
        get(
            self,
            sha256="74ee1a7605e29af95c443724c58132c4a147e56c89f6354c5e216ac0310f782f",
            url=f"https://github.com/mevislab/pythonqt/archive/refs/tags/v{self.version}.zip",
            pattern="*/generator/*",
            strip_root=True,
        )
        copy(self, "**", src=os.path.join(self.export_sources_folder, "sources"), dst=self.source_folder)

    def generate(self):
        env = VirtualRunEnv(self)
        env.generate(scope="build")
        tc = CMakeToolchain(self)
        tc.variables["QT_NO_PRIVATE_MODULE_WARNING"] = True
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
