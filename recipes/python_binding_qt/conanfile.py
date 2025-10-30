import os

from conan import ConanFile
from conan.errors import ConanException
from conan.tools.cmake import cmake_layout, CMakeToolchain, CMakeDeps, CMake
from conan.tools.env import VirtualRunEnv
from conan.tools.files import copy, collect_libs, chdir

required_conan_version = ">=2.2.2"


class ConanRecipe(ConanFile):
    name = "python_binding_qt"
    version = "6.9.2"  # corresponds to the Qt version which is used for code generation
    homepage = "https://mevislab.de"
    description = "Python binding into Qt"
    license = "LGPL-2.1-only"
    settings = "os", "arch", "compiler", "build_type"
    package_type = "shared-library"
    exports_sources = "sources/*", "LICENSE"

    def requirements(self):
        self.requires("qtbase/[>=6.9]")
        self.requires("qtdeclarative/[>=6.9]")
        self.requires("qtmultimedia/[>=6.9]")
        self.requires("qtwebengine/[>=6.9]")
        self.requires("qtwebview/[>=6.9]")
        self.requires("pcre2/[>=10.34]")
        self.requires("python/[>=3.13]")
        self.requires("pythonqt/[>=3.6.0]")
        self.build_requires("pythonqt_generator/[>=3.6.0]", package_id_mode="full_mode")

    def validate(self):
        qtbase_version = self.dependencies["qtbase"].ref.version
        if qtbase_version != self.version:
            raise ConanException(
                f"Version mismatch - you need to update the version of this package to {qtbase_version}!"
            )

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
        tc.variables["OpenGL_GL_PREFERENCE"] = "LEGACY"
        tc.variables["CMAKE_INSTALL_RPATH"] = "$ORIGIN;$ORIGIN/../../../../lib/"
        tc.generate()
        cd = CMakeDeps(self)
        cd.generate()

    def build(self):
        self.generate_sources()
        cmake = CMake(self)
        cmake.configure()
        cmake.build()

    def generate_sources(self):
        generator_path = self.dependencies.build["pythonqt_generator"].cpp_info.bindirs[0]
        with chdir(self, generator_path):
            qt_includes = []
            for dep in (
                "qtbase",
                "qtmultimedia",
                "qtsvg",
                "qtdeclarative",
                "qtwebchannel",
                "qtwebengine",
                "qtwebsockets",
                "qtwebview",
            ):
                qt_includes.extend(self.dependencies[dep].cpp_info.includedirs)
            qtversion = self.dependencies["qtbase"].ref.version
            cmd_line = (
                f"PythonQtGenerator "
                f"--include-paths={os.pathsep.join(qt_includes)} "
                f"--output-directory={self.source_folder} "
                f"--qt-version={qtversion} "
                "--max-classes-per-file=1000 "
                "qtscript_masterinclude.h build_all.txt"
            )
            print(f"{cmd_line=}")
            self.run(cmd_line)

    def package(self):
        cmake = CMake(self)
        cmake.install()
        copy(self, "LICENSE", src=self.export_sources_folder, dst=os.path.join(self.package_folder, "licenses"))

    def package_info(self):
        self.cpp_info.set_property("cmake_file_name", "PythonBindingQt")
        self.cpp_info.set_property("cmake_target_name", "PythonBindingQt::PythonBindingQt")
        self.cpp_info.set_property("cmake_config_version_compat", "AnyNewerVersion")
        self.cpp_info.set_property(
            "optional_deps", "qtsvg,qtdeclarative,qtmultimedia,qtwebengine,qtwebsockets,qtwebchannel,qtwebview"
        )
        self.cpp_info.set_property("pkg_config_name", "PythonBindingQt")
        self.cpp_info.libs = collect_libs(self)
        self.cpp_info.includedirs.clear()
