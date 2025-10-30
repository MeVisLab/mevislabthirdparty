from conan import ConanFile
from conan.tools.cmake import CMake, CMakeToolchain, cmake_layout
from conan.tools.files import collect_libs, replace_in_file
from conan.tools.files import get, rmdir, copy
from conan.tools.scm import Version
import os

required_conan_version = ">=2.2.2"


class ConanRecipe(ConanFile):
    name = "glfw"
    version = "3.4"
    homepage = "https://github.com/glfw/glfw"
    description = "A multi-platform library for OpenGL, OpenGL ES, Vulkan, window and input"
    license = "Zlib"
    package_type = "shared-library"
    settings = "os", "arch", "compiler", "build_type"

    mlab_hooks = {"debug_suffix.exclude": ["glfw3ddll.lib", "glfw3d.dll"]}

    def configure(self):
        self.settings.rm_safe("compiler.libcxx")
        self.settings.rm_safe("compiler.cppstd")

    def layout(self):
        cmake_layout(self, src_folder="src")

    def source(self):
        v = Version(self.version)
        v_str = f"{v.major}.{v.minor}" + (f".{v.patch}" if v.patch and v.patch > 0 else "")
        get(
            self,
            sha256="c038d34200234d071fae9345bc455e4a8f2f544ab60150765d7704e08f3dac01",
            url=f"https://github.com/glfw/glfw/archive/{v_str}.tar.gz",
            strip_root=True,
        )
        replace_in_file(
            self,
            os.path.join(self.source_folder, "src", "CMakeLists.txt"),
            "set_target_properties(glfw PROPERTIES IMPORT_SUFFIX",
            "#set_target_properties(glfw PROPERTIES IMPORT_SUFFIX",
        )

    def generate(self):
        tc = CMakeToolchain(self)
        tc.variables["CMAKE_DEBUG_POSTFIX"] = "_d"
        tc.variables["BUILD_SHARED_LIBS"] = True
        tc.variables["GLFW_BUILD_EXAMPLES"] = False
        tc.variables["GLFW_BUILD_TESTS"] = False
        tc.variables["GLFW_BUILD_DOCS"] = False
        tc.variables["GLFW_BUILD_WAYLAND"] = False
        tc.variables["GLFW_INSTALL"] = True
        tc.generate()

    def build(self):
        cmake = CMake(self)
        cmake.configure()
        cmake.build()

    def package(self):
        copy(self, "LICENSE*", src=self.source_folder, dst=os.path.join(self.package_folder, "licenses"))
        copy(
            self,
            "*.pdb",
            src=self.build_folder,
            dst=os.path.join(self.package_folder, "bin"),
            keep_path=False,
            excludes="*vc???.pdb",
        )
        cmake = CMake(self)
        cmake.install()
        rmdir(self, os.path.join(self.package_folder, "lib", "cmake"))
        rmdir(self, os.path.join(self.package_folder, "lib", "pkgconfig"))

    def package_info(self):
        # self.cpp_info.set_property("cpe", "")  # No CPE (yet)?
        self.cpp_info.set_property("purl", f"pkg:github/glfw/glfw@{self.version}")
        self.cpp_info.set_property("cmake_file_name", "glfw3")
        self.cpp_info.set_property("cmake_target_name", "glfw")
        self.cpp_info.set_property("pkg_config_name", "glfw3")
        self.cpp_info.libs = collect_libs(self)
        if self.settings.os == "Linux":
            self.cpp_info.system_libs.extend(["m", "pthread", "dl", "rt"])
        elif self.settings.os == "Windows":
            self.cpp_info.defines.append("GLFW_DLL")
            self.cpp_info.system_libs.append("gdi32")
