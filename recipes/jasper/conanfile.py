from conan import ConanFile
from conan.tools.cmake import CMake, CMakeDeps, CMakeToolchain, cmake_layout
from conan.tools.files import collect_libs, replace_in_file
from conan.tools.files import get, copy, rmdir
from pathlib import Path
import os

required_conan_version = ">=2.2.2"


class ConanRecipe(ConanFile):
    name = "jasper"
    version = "4.2.5"
    homepage = "https://jasper-software.github.io/jasper/"
    description = "Implementation of the codec specified in the JPEG-2000 Part-1 standard"
    license = "JasPer-2.0"
    package_type = "shared-library"
    settings = "os", "arch", "compiler", "build_type"

    def configure(self):
        self.settings.rm_safe("compiler.libcxx")
        self.settings.rm_safe("compiler.cppstd")

    def layout(self):
        cmake_layout(self, src_folder="src")

    def requirements(self):
        self.requires("libjpeg-turbo/[>=2.1.5]")

    def source(self):
        get(
            self,
            sha256="31a72ba9da49b8f6f83c0c72e319fc4e4a5ec9529a1f3d2cff48a501d330b09a",
            url=f"https://github.com/jasper-software/jasper/archive/version-{self.version}.zip",
            strip_root=True,
        )
        replace_in_file(self, os.path.join(self.source_folder, "CMakeLists.txt"), "set(CMAKE_INSTALL_RPATH", "set(__CMAKE_INSTALL_RPATH")

    def generate(self):
        cd = CMakeDeps(self)
        cd.generate()
        tc = CMakeToolchain(self)
        tc.variables["CMAKE_DEBUG_POSTFIX"] = "_d"
        tc.variables["BUILD_SHARED_LIBS"] = True
        tc.variables["CMAKE_INSTALL_RPATH"] = "$ORIGIN;$ORIGIN/../lib"
        tc.variables["CMAKE_INSTALL_RPATH_USE_LINK_PATH"] = False
        tc.variables["JAS_ENABLE_DOC"] = False
        tc.variables["JAS_ENABLE_PROGRAMS"] = False
        tc.variables["JAS_ENABLE_SHARED"] = True
        tc.variables["JAS_LIBJPEG_REQUIRED"] = "REQUIRED"
        tc.variables["JAS_ENABLE_OPENGL"] = False
        tc.variables["ALLOW_IN_SOURCE_BUILD"] = True
        tc.variables["JAS_ENABLE_AUTOMATIC_DEPENDENCIES"] = False
        tc.variables["JAS_ENABLE_LIBHEIF"] = False
        tc.generate()

    def build(self):
        cmake = CMake(self)
        cmake.configure()
        cmake.build()

    def package(self):
        cmake = CMake(self)
        cmake.install()
        copy(self, "LICENSE.txt", src=self.source_folder, dst=os.path.join(self.package_folder, "licenses"))
        rmdir(self, os.path.join(self.package_folder, "lib", "cmake"))
        rmdir(self, os.path.join(self.package_folder, "lib", "pkgconfig"))
        rmdir(self, os.path.join(self.package_folder, "share"))
        if self.settings.os == "Windows":
            copy(self, "*.pdb", src=self.build_path, dst=os.path.join(self.package_folder, "bin"), keep_path=False, excludes="*vc*.pdb")
            for dll_file in (Path(self.package_path) / "bin").glob("*.dll"):
                if dll_file.name.startswith(("concrt", "msvcp", "vcruntime")):
                    dll_file.unlink()

    def package_info(self):
        self.cpp_info.set_property("cpe", "cpe:2.3:a:jasper_project:jasper:*:*:*:*:*:*:*:*")
        self.cpp_info.set_property("purl", f"pkg:github/jasper-software/jasper@version-{self.version}")
        self.cpp_info.set_property("cmake_find_mode", "both")
        self.cpp_info.set_property("cmake_file_name", "Jasper")
        self.cpp_info.set_property("cmake_target_name", "Jasper::Jasper")
        self.cpp_info.set_property("pkg_config_name", "jasper")
        self.cpp_info.libs = collect_libs(self)

        if self.settings.os == "Linux":
            self.cpp_info.system_libs.append("m")
