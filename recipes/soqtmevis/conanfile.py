from conan import ConanFile
from conan.tools.cmake import CMake, CMakeDeps, CMakeToolchain, cmake_layout
from conan.tools.files import copy, collect_libs
from conan.tools.env import VirtualRunEnv

required_conan_version = ">=2.2.2"


class ConanRecipe(ConanFile):
    name = "soqtmevis"
    version = "1.2.0"
    license = "LGPL-2.1-only"
    homepage = "https://mevislab.de"
    description = "Qt Inventor Binding"
    settings = "os", "arch", "compiler", "build_type"
    package_type = "shared-library"
    exports_sources = "sources/*", "LICENSE"

    mlab_hooks = {
        'dependencies.system_libs': [
            'libfontconfig.so.1',
            'libGLU.so.1',
        ]
    }

    def requirements(self):
        self.requires("glew/[>=2.0.0]")
        self.requires("openinventor/[>=2.5.1]", transitive_headers=True)
        self.requires("qtbase/[>=6.5]")

    def layout(self):
        cmake_layout(self, src_folder="sources")

    def generate(self):
        env = VirtualRunEnv(self)
        env.generate(scope="build")

        deps = CMakeDeps(self)
        deps.generate()
        tc = CMakeToolchain(self)
        tc.variables["CMAKE_DEBUG_POSTFIX"] = "_d"
        tc.variables["BUILD_SHARED_LIBS"] = True
        tc.variables["CMAKE_INSTALL_RPATH"] = "$ORIGIN;$ORIGIN/../lib"
        tc.variables["OpenGL_GL_PREFERENCE"] = "LEGACY"
        tc.generate()

    def build(self):
        cmake = CMake(self)
        cmake.configure()
        cmake.build()

    def package(self):
        copy(self, "LICENSE", src=self.source_path.parent, dst=self.package_path / "licenses")
        cmake = CMake(self)
        cmake.install()

    def package_info(self):
        self.cpp_info.set_property("cmake_find_mode", "both")
        self.cpp_info.set_property("cmake_file_name", "SoQtMeVis")
        self.cpp_info.set_property("cmake_target_name", "SoQtMeVis::SoQtMeVis")
        self.cpp_info.libs = collect_libs(self)
