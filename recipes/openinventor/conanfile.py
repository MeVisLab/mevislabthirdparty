from conan import ConanFile
from conan.tools.cmake import CMake, CMakeDeps, CMakeToolchain, cmake_layout
from conan.tools.files import copy, collect_libs
import os

required_conan_version = ">=2.2.2"


class ConanRecipe(ConanFile):
    name = "openinventor"
    version = "2.5.2"
    license = "LGPL-2.1-only"
    homepage = "https://www.mevislab.de/mevislab/features/open-inventor"
    description = "An extensible 3D rendering toolkit"
    settings = "os", "arch", "compiler", "build_type"
    package_type = "shared-library"
    exports_sources = "sources/*"

    mlab_hooks = {
        "folders.exclude": ["doxygen"],
        "dependencies.system_libs": [
            "libfontconfig.so.1",
            "libfreetype.so.6",
            "libGLU.so.1",
        ],
    }

    def export_sources(self):
        copy(self, "sources", self.recipe_folder, self.export_sources_folder)

    def requirements(self):
        self.requires("glew/[>=2.0.0]")
        self.requires("libjpeg-turbo/[>=2.1.5]")

        if self.settings.os == "Windows":
            self.requires("libiconv/[>=1.16]")

        if self.settings.os != "Linux":
            self.requires("freetype/[>=2.10.4]")

    def layout(self):
        cmake_layout(self, src_folder="sources")

    def generate(self):
        deps = CMakeDeps(self)
        deps.generate()
        tc = CMakeToolchain(self)
        tc.variables["CMAKE_DEBUG_POSTFIX"] = "_d"
        tc.variables["BUILD_SHARED_LIBS"] = True
        tc.variables["CMAKE_INSTALL_RPATH"] = "$ORIGIN;$ORIGIN/../lib"
        tc.generate()

    def build(self):
        cmake = CMake(self)
        cmake.configure()
        cmake.build()

    def package(self):
        copy(self, "COPYING", src=self.source_folder, dst=os.path.join(self.package_folder, "licenses"))
        cmake = CMake(self)
        cmake.install()

    def package_info(self):
        self.cpp_info.set_property("cmake_find_mode", "both")
        self.cpp_info.set_property("cmake_file_name", "OpenInventor")
        self.cpp_info.set_property("cmake_target_name", "OpenInventor::OpenInventor")
        self.cpp_info.libs = collect_libs(self)
        self.cpp_info.defines.append("SGIOIV")
        self.cpp_info.defines.append("IV_STRICT")
