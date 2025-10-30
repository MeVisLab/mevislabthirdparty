from conan import ConanFile
from conan.tools.cmake import CMakeToolchain, CMakeDeps, CMake, cmake_layout
from conan.tools.env import VirtualRunEnv
from conan.tools.files import copy, collect_libs, chdir
import os

required_conan_version = ">=2.2.2"


class ConanRecipe(ConanFile):
    name = "python_binding_inventor"
    version = "2024.12.27"
    homepage = "https://mevislab.de"
    description = "Python binding into Inventor"
    license = "LGPL-2.1-only"
    settings = "os", "arch", "compiler", "build_type"
    package_type = "shared-library"
    exports_sources = "sources/*", "LICENSE"
    generate_wrappers = os.environ.get("INVENTOR_BINDING_GENERATE_WRAPPERS", "False").lower() in ("1", "true")

    mlab_hooks = {
        "test_package.skip": True,
    }

    def requirements(self):
        self.requires("glew/[>=2.0.0]")
        self.requires("numpy/[>=1.17.5]")
        self.requires("openinventor/[>=2.5.1]")
        self.requires("qtbase/[>=6.5]")
        self.build_requires("pcre2/[>=10.34]")
        self.requires("python/[>=3.13]")
        self.requires("pythonqt/[>=3.4.2]")
        if self.generate_wrappers:
            self.build_requires("pythonqt_generator/[>=3.6.0]", package_id_mode="full_mode")

    def layout(self):
        cmake_layout(self, src_folder="sources")

    def generate(self):
        env = VirtualRunEnv(self)
        env.generate(scope="build")

        tc = CMakeToolchain(self)
        version = self.dependencies["python"].ref.version

        tc.variables["CMAKE_DEBUG_POSTFIX"] = "_d"
        tc.variables["BUILD_SHARED_LIBS"] = True
        tc.variables["python_VERSION_MAJOR"] = version.major
        tc.variables["python_VERSION_MINOR"] = version.minor
        tc.variables["CMAKE_INSTALL_RPATH"] = "$ORIGIN;$ORIGIN/../../../../lib/"
        tc.generate()
        cd = CMakeDeps(self)
        cd.generate()

    def generate_sources(self):
        generator_path = os.path.join(self.export_sources_folder, "sources", "generator")
        with chdir(self, generator_path):
            includes = self.dependencies["openinventor"].cpp_info.includedirs[0]
            qtversion = self.dependencies["qtbase"].ref.version
            cmd_line = (
                f"{self.dependencies.build['pythonqt_generator'].cpp_info.bindirs[0]}/PythonQtGenerator "
                f"--include-paths={includes} "
                f"--output-directory={self.source_folder} "
                f"--qt-version={qtversion} "
                "--max-classes-per-file=1000 "
                "global.h typesystem_Inventor_all.xml"
            )
            print(f"{cmd_line=}")
            self.run(cmd_line)

    def build(self):
        if self.generate_wrappers:
            self.generate_sources()
        cmake = CMake(self)
        cmake.configure()
        cmake.build()

    def package(self):
        cmake = CMake(self)
        cmake.install()
        copy(
            self, "LICENSE", src=os.path.dirname(self.source_folder), dst=os.path.join(self.package_folder, "licenses")
        )

    def package_info(self):
        self.cpp_info.set_property("cmake_file_name", "PythonBindingInventor")
        self.cpp_info.set_property("cmake_target_name", "PythonBindingInventor::PythonBindingInventor")
        self.cpp_info.set_property("cmake_config_version_compat", "AnyNewerVersion")
        self.cpp_info.set_property("pkg_config_name", "PythonBindingInventor")
        self.cpp_info.libs = collect_libs(self)
        self.cpp_info.includedirs.clear()
