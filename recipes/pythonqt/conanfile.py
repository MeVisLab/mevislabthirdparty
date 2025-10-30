from conan import ConanFile
from conan.tools.cmake import CMake, CMakeDeps, CMakeToolchain, cmake_layout
from conan.tools.env import VirtualRunEnv
from conan.tools.files import collect_libs, copy, get, chdir
import os

required_conan_version = ">=2.2.2"


class ConanRecipe(ConanFile):
    name = "pythonqt"
    version = "3.6.0"
    homepage = "https://mevislab.github.io/pythonqt"
    description = "PythonQt is a dynamic Python binding for Qt"
    license = "LGPL-2.1-only"
    package_type = "shared-library"
    settings = "os", "arch", "compiler", "build_type"
    exports_sources = "patches/*.patch", "sources/**", "LICENSE"

    def layout(self):
        cmake_layout(self, src_folder="src")

    def requirements(self):
        self.requires("qtbase/[>=6.9]")
        self.requires("python/[>=3.13]", transitive_headers=True)
        self.build_requires("pythonqt_generator/[>=3.6.0]")

    def source(self):
        get(
            self,
            sha256="7c3629cd4b97412ee6f6ffecb8a4b7e0b326d7c1ad0d095445b93605b31f97d0",
            url=f"https://github.com/MeVisLab/pythonqt/archive/refs/tags/v{self.version}.zip",
            strip_root=True,
        )
        copy(self, "**", src=os.path.join(self.export_sources_folder, "sources"), dst=self.source_folder)

    def generate(self):
        env = VirtualRunEnv(self)
        env.generate(scope="build")
        deps = CMakeDeps(self)
        deps.generate()
        tc = CMakeToolchain(self)
        tc.variables["CMAKE_DEBUG_POSTFIX"] = "_d"
        tc.variables["BUILD_SHARED_LIBS"] = True
        tc.variables["CMAKE_INSTALL_RPATH"] = "$ORIGIN;$ORIGIN/../lib"
        python_version = self.dependencies["python"].ref.version
        tc.variables["python_VERSION_MAJOR"] = python_version.major
        tc.variables["python_VERSION_MINOR"] = python_version.minor
        tc.variables["OpenGL_GL_PREFERENCE"] = "LEGACY"
        tc.generate()

    def build(self):
        self.generate_sources()
        cmake = CMake(self)
        cmake.configure()
        cmake.build()

    def generate_sources(self):
        generator_path = self.dependencies.build["pythonqt_generator"].cpp_info.bindirs[0]
        with chdir(self, generator_path):
            qtbase_includes = os.pathsep.join(self.dependencies["qtbase"].cpp_info.includedirs)
            qtversion = self.dependencies["qtbase"].ref.version
            cmd_line = (
                f"PythonQtGenerator "
                f"--include-paths={qtbase_includes} "
                f"--output-directory={self.source_folder} "
                f"--qt-version={qtversion} "
                "qtscript_masterinclude.h build_all.txt"
            )
            self.run(cmd_line)

    def package(self):
        copy(self, "LICENSE", src=self.export_sources_folder, dst=os.path.join(self.package_folder, "licenses"))
        cmake = CMake(self)
        cmake.install()

    def package_info(self):
        # self.cpp_info.set_property("cpe", "")  # No CPE (yet)?
        self.cpp_info.set_property("purl", f"pkg:github/MeVisLab/pythonqt@v{self.version}")
        self.cpp_info.set_property("cmake_file_name", "PythonQt")
        self.cpp_info.set_property("cmake_target_name", "PythonQt::PythonQt")
        self.cpp_info.set_property("pkg_config_name", "PythonQt")
        self.cpp_info.libs = collect_libs(self)
