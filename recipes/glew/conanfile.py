import os

from conan import ConanFile
from conan.tools.cmake import CMake, CMakeToolchain, cmake_layout
from conan.tools.files import replace_in_file, collect_libs, copy, get, patch, rmdir

required_conan_version = ">=2.2.2"


class ConanRecipe(ConanFile):
    name = "glew"
    version = "2.2.0"
    homepage = "https://github.com/nigels-com/glew"
    description = "The OpenGL Extension Wrangler Library"
    license = "MIT AND BSD-3-Clause"
    package_type = "shared-library"
    settings = "os", "arch", "compiler", "build_type"
    exports_sources = "patches/*.patch"

    def configure(self):
        self.settings.rm_safe("compiler.libcxx")
        self.settings.rm_safe("compiler.cppstd")

    def layout(self):
        cmake_layout(self, src_folder="src")

    def source(self):
        get(self,
            url=f"https://github.com/nigels-com/glew/releases/download/glew-{self.version}/glew-{self.version}.tgz",
            sha256="d4fc82893cfb00109578d0a1a2337fb8ca335b3ceccf97b97e5cc7f08e4353e1",
            destination=self.source_folder,
            strip_root=True)
        replace_in_file(self, self.source_path / "build" / "cmake" / "CMakeLists.txt", 'set(CMAKE_DEBUG_POSTFIX d)', '')
        replace_in_file(self, self.source_path / "build" / "cmake" / "CMakeLists.txt", '${OPENGL_LIBRARIES}', 'OpenGL::GL')

        # Fix cmake_minimum_required() before project():
        patch(self, patch_file="patches/001-fix-cmake_minimum_required.patch")

    def generate(self):
        tc = CMakeToolchain(self)
        tc.variables["BUILD_UTILS"] = (self.settings.build_type != "Debug")
        tc.variables["BUILD_SHARED_LIBS"] = True
        tc.variables["CMAKE_DEBUG_POSTFIX"] = "_d"
        tc.variables["CMAKE_POSITION_INDEPENDENT_CODE"] = self.settings.os != "Windows"
        tc.variables["OpenGL_GL_PREFERENCE"] = "LEGACY"
        if self.settings.os == 'Windows':
            tc.variables["GLEW_STATIC"] = True
        tc.generate()

    def build(self):
        cmake = CMake(self)
        cmake.configure(build_script_folder=os.path.join(self.source_folder, "build", "cmake"))
        cmake.build()

    def package(self):
        copy(self, "LICENSE.txt", src=self.source_path, dst=self.package_path / "licenses")
        copy(self, "*.pdb", src=self.build_path, dst=self.package_path / "bin", keep_path=False, excludes="*vc???.pdb")
        cmake = CMake(self)
        cmake.install()
        rmdir(self, self.package_path / "lib" / "pkgconfig")
        rmdir(self, self.package_path / "lib" / "cmake")
        for pdb in (self.package_path / "lib").glob("*.pdb"):
            pdb.unlink()

    def package_info(self):
        # self.cpp_info.set_property("cpe", "")  # No CPE yet?
        self.cpp_info.set_property("base_purl", "github/nigels-com/glew")
        self.cpp_info.set_property("cmake_file_name", "GLEW")
        self.cpp_info.set_property("cmake_target_name", "GLEW::GLEW")
        self.cpp_info.set_property("cmake_target_aliases", ["GLEW::glew"])
        self.cpp_info.set_property("pkg_config_name", "glew")
        self.cpp_info.libs = collect_libs(self)

        if self.settings.os == "Macos":
            self.cpp_info.defines.append("GL_SILENCE_DEPRECATION=1")
            self.cpp_info.frameworks.append("OpenGL")
        elif self.settings.os == "Windows":
            self.cpp_info.system_libs.append("opengl32")
        elif self.settings.os == "Linux":
            self.cpp_info.system_libs.append("GL")
