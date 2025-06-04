from conan import ConanFile
from conan.tools.cmake import CMake, CMakeToolchain, cmake_layout
from conan.tools.files import copy, get, rmdir
import os

required_conan_version = ">=2.2.2"


class ConanRecipe(ConanFile):
    name = "brotli"
    version = "1.1.0"
    homepage = "https://github.com/google/brotli"
    description = "Generic-purpose lossless compression algorithm"
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
        get(self,
            sha256="e720a6ca29428b803f4ad165371771f5398faba397edf6778837a18599ea13ff",
            url=f"https://github.com/google/brotli/archive/refs/tags/v{self.version}.tar.gz",
            strip_root=True
        )

    def generate(self):
        tc = CMakeToolchain(self)
        tc.variables["BUILD_SHARED_LIBS"] = True

        tc.variables["CMAKE_DEBUG_POSTFIX"] = "_d"
        tc.variables['CMAKE_POSITION_INDEPENDENT_CODE'] = True
        tc.variables['CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS'] = True
        tc.variables["CMAKE_INSTALL_RPATH"] = "$ORIGIN;$ORIGIN/../lib"

        tc.variables["BROTLI_BUNDLED_MODE"] = False
        tc.variables["BROTLI_DISABLE_TESTS"] = True

        tc.preprocessor_definitions["BROTLI_BUILD_64_BIT"] = 1
        tc.preprocessor_definitions["BROTLI_BUILD_PORTABLE"] = 1

        tc.generate()

    def build(self):
        cmake = CMake(self)
        cmake.configure()
        cmake.build()

    def package(self):
        copy(self, "LICENSE", src=self.source_folder, dst=os.path.join(self.package_folder, "licenses"))
        cmake = CMake(self)
        cmake.install()
        rmdir(self, os.path.join(self.package_folder, "lib", "pkgconfig"))

    def package_info(self):
        self.cpp_info.set_property("cpe", "cpe:2.3:a:google:brotli:*:*:*:*:*:*:*:*")
        self.cpp_info.set_property("purl", f"pkg:github/google/brotli@v{self.version}")

        incdir = os.path.join("include", "brotli")
        suffix = '_d' if self.settings.build_type == 'Debug' else ''

        # brotlicommon
        self.cpp_info.components["brotlicommon"].set_property("pkg_config_name", "libbrotlicommon")
        self.cpp_info.components["brotlicommon"].includedirs.append(incdir)
        self.cpp_info.components["brotlicommon"].libs = [f"brotlicommon{suffix}"]
        if self.settings.os == "Windows":
            self.cpp_info.components["brotlicommon"].defines.append("BROTLI_SHARED_COMPILATION")

        # brotlidec
        self.cpp_info.components["brotlidec"].set_property("pkg_config_name", "libbrotlidec")
        self.cpp_info.components["brotlidec"].includedirs.append(incdir)
        self.cpp_info.components["brotlidec"].libs = [f"brotlidec{suffix}"]
        self.cpp_info.components["brotlidec"].requires = ["brotlicommon"]

        # brotlienc
        self.cpp_info.components["brotlienc"].set_property("pkg_config_name", "libbrotlienc")
        self.cpp_info.components["brotlienc"].includedirs.append(incdir)
        self.cpp_info.components["brotlienc"].libs = [f"brotlienc{suffix}"]
        self.cpp_info.components["brotlienc"].requires = ["brotlicommon"]
        if self.settings.os == "Linux":
            self.cpp_info.components["brotlienc"].system_libs = ["m"]
