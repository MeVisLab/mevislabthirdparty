from conan import ConanFile
from conan.tools.cmake import CMake, CMakeToolchain, cmake_layout
from conan.tools.env import VirtualRunEnv
from conan.tools.files import copy, get

required_conan_version = ">=2.2.2"


class ConanRecipe(ConanFile):
    name = "pythonqt_generator"
    version = "3.5.6"
    homepage = "https://mevislab.github.io/pythonqt"
    description = "PythonQtGenerator creates source files from Qt Python binding for Qt"
    license = "LGPL-2.1-only"
    package_type = "application"
    settings = "os", "arch", "compiler", "build_type"
    exports_sources = "sources/**", "LICENSE"

    def layout(self):
        cmake_layout(self, src_folder="src")

    def requirements(self):
        self.requires("qtbase/[>=6.5]")
        self.requires("qt5compat/[>=6.5]")

    def source(self):
        get(
            self,
            sha256="8c034b9697dd9f619ff343a70485f41b409e8c52900853ab0ef6139cd01d8cfe",
            url=f"https://github.com/MeVisLab/pythonqt/archive/refs/tags/v{self.version}.zip",
            pattern="*/generator/*",
            strip_root=True
        )
        copy(self, "**", src=self.export_sources_path / "sources", dst=self.source_path)

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
        copy(self, "LICENSE", src=self.export_sources_path, dst=self.package_path / "licenses")
        cmake = CMake(self)
        cmake.install()

    def package_info(self):
        # self.cpp_info.set_property("cpe", "")  # No CPE (yet)?
        self.cpp_info.set_property("base_purl", "github/MeVisLab/pythonqt")
        self.cpp_info.includedirs.clear()
        self.cpp_info.set_property("cmake_find_mode", "none")
