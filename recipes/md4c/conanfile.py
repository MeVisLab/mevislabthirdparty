from conan import ConanFile
from conan.tools.cmake import CMake, CMakeToolchain, cmake_layout
from conan.tools.files import patch, copy, get, rmdir
import os

required_conan_version = ">=2.2.2"


class ConanRecipe(ConanFile):
    name = "md4c"
    version = "0.5.2"
    homepage = "https://github.com/mity/md4c"
    description = "C Markdown parser. Fast. SAX-like interface. Compliant to CommonMark specification."
    license = "MIT"
    settings = "os", "arch", "compiler", "build_type"
    exports_sources = "patches/*.patch"
    package_type = "shared-library"

    def configure(self):
        self.settings.rm_safe("compiler.cppstd")
        self.settings.rm_safe("compiler.libcxx")

    def layout(self):
        cmake_layout(self, src_folder="src")

    def source(self):
        get(
            self,
            sha256="55d0111d48fb11883aaee91465e642b8b640775a4d6993c2d0e7a8092758ef21",
            url=f"https://github.com/mity/md4c/archive/refs/tags/release-{self.version}.tar.gz",
            strip_root=True,
        )
        patch(self, patch_file="./patches/001-honor-vc-runtime.patch")

    def generate(self):
        tc = CMakeToolchain(self)
        tc.variables["BUILD_SHARED_LIBS"] = True
        tc.variables["CMAKE_DEBUG_POSTFIX"] = "_d"
        tc.variables["CMAKE_POSITION_INDEPENDENT_CODE"] = True
        tc.variables["CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS"] = True
        tc.preprocessor_definitions["MD4C_USE_UTF8"] = "1"
        tc.generate()

    def build(self):
        cmake = CMake(self)
        cmake.configure()
        cmake.build()

    def package(self):
        copy(self, pattern="LICENSE.md", dst=os.path.join(self.package_folder, "licenses"), src=self.source_folder)
        cmake = CMake(self)
        cmake.install()
        rmdir(self, os.path.join(self.package_folder, "lib", "cmake"))
        rmdir(self, os.path.join(self.package_folder, "lib", "pkgconfig"))
        rmdir(self, os.path.join(self.package_folder, "share"))

    def package_info(self):
        self.cpp_info.set_property("cpe", "cpe:2.3:a:md4c_project:md4c:*:*:*:*:*:*:*:*")
        self.cpp_info.set_property("base_purl", "github/mity/md4c")
        suffix = "_d" if self.settings.build_type == "Debug" else ""
        self.cpp_info.set_property("cmake_file_name", "md4c")
        self.cpp_info.components["_md4c"].set_property("cmake_target_name", "md4c::md4c")
        self.cpp_info.components["_md4c"].set_property("pkg_config_name", "md4c")
        self.cpp_info.components["_md4c"].libs = [f"md4c{suffix}"]

        self.cpp_info.components["md4c_html"].set_property("cmake_target_name", "md4c::md4c-html")
        self.cpp_info.components["md4c_html"].set_property("pkg_config_name", "md4c-html")
        self.cpp_info.components["md4c_html"].libs = [f"md4c-html{suffix}"]
        self.cpp_info.components["md4c_html"].requires = ["_md4c"]

        self.cpp_info.set_property("cmake_target_name", "md4c::md4c-html")
        self.cpp_info.set_property("pkg_config_name", "md4c-html")
