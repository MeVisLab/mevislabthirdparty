from conan import ConanFile
from conan.tools.cmake import CMake, CMakeToolchain, cmake_layout
from conan.tools.files import copy, get, rmdir

required_conan_version = ">=2.2.2"


class ConanRecipe(ConanFile):
    name = "libwebp"
    version = "1.5.0"
    description = "Library to encode and decode images in WebP format"
    homepage = "https://chromium.googlesource.com/webm/libwebp"
    license = "BSD-3-Clause"
    package_type = "shared-library"
    settings = "os", "arch", "compiler", "build_type"

    def configure(self):
        self.settings.rm_safe("compiler.cppstd")
        self.settings.rm_safe("compiler.libcxx")

    def layout(self):
        cmake_layout(self, src_folder="src")

    def source(self):
        get(
            self,
            sha256="7d6fab70cf844bf6769077bd5d7a74893f8ffd4dfb42861745750c63c2a5c92c",
            url=f"https://storage.googleapis.com/downloads.webmproject.org/releases/webp/libwebp-{self.version}.tar.gz",
            strip_root=True,
        )

    def generate(self):
        tc = CMakeToolchain(self)
        tc.variables["CMAKE_DEBUG_POSTFIX"] = "_d"
        tc.variables["BUILD_SHARED_LIBS"] = True
        tc.variables["WEBP_ENABLE_SIMD"] = True
        tc.variables["WEBP_BUILD_ANIM_UTILS"] = False
        tc.variables["WEBP_BUILD_CWEBP"] = False
        tc.variables["WEBP_BUILD_DWEBP"] = False
        tc.variables["WEBP_BUILD_GIF2WEBP"] = False
        tc.variables["WEBP_BUILD_IMG2WEBP"] = False
        tc.variables["WEBP_BUILD_VWEBP"] = False
        tc.variables["WEBP_BUILD_WEBPINFO"] = False
        tc.variables["WEBP_BUILD_WEBPMUX"] = False
        tc.variables["WEBP_BUILD_EXTRAS"] = False
        tc.variables["WEBP_BUILD_WEBP_JS"] = False
        tc.variables["WEBP_NEAR_LOSSLESS"] = True
        tc.variables["WEBP_BUILD_LIBWEBPMUX"] = True
        tc.variables["CMAKE_DISABLE_FIND_PACKAGE_GIF"] = True
        tc.variables["CMAKE_DISABLE_FIND_PACKAGE_PNG"] = True
        tc.variables["CMAKE_DISABLE_FIND_PACKAGE_TIFF"] = True
        tc.variables["CMAKE_DISABLE_FIND_PACKAGE_JPEG"] = True
        tc.variables["CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS"] = True
        tc.variables["CMAKE_INSTALL_RPATH"] = "$ORIGIN;$ORIGIN/../lib"
        tc.generate()

    def build(self):
        cmake = CMake(self)
        cmake.configure()
        cmake.build()

    def package(self):
        cmake = CMake(self)
        cmake.install()
        copy(self, "COPYING", src=self.source_path, dst=self.package_path / "licenses")
        copy(self, "*.pdb", src=self.build_path, dst=self.package_path / "bin", keep_path=False, excludes="*vc???.pdb")
        rmdir(self, self.package_path / "lib" / "pkgconfig")
        rmdir(self, self.package_path / "share")

    def package_info(self):
        self.cpp_info.set_property("cpe", "cpe:2.3:a:webmproject:libwebp:*:*:*:*:*:*:*:*")
        self.cpp_info.set_property("purl", f"pkg:github/webmproject/libwebp@v{self.version}")

        libname = lambda name: ("lib" if self.settings.os == "Windows" else "") + (
            name + "_d" if self.settings.build_type == "Debug" else name
        )

        self.cpp_info.set_property("cmake_file_name", "WebP")
        self.cpp_info.set_property("pkg_config_name", "libwebp-all-do-not-use")

        # webpdecoder
        self.cpp_info.components["webpdecoder"].set_property("cmake_target_name", "WebP::webpdecoder")
        self.cpp_info.components["webpdecoder"].set_property("pkg_config_name", "libwebpdecoder")
        self.cpp_info.components["webpdecoder"].libs = [libname("webpdecoder")]
        if self.settings.os == "Linux":
            self.cpp_info.components["webpdecoder"].system_libs = ["m", "pthread"]

        # webp
        self.cpp_info.components["webp"].set_property("cmake_target_name", "WebP::webp")
        self.cpp_info.components["webp"].set_property("pkg_config_name", "libwebp")
        self.cpp_info.components["webp"].libs = [libname("webp")]
        if self.settings.os == "Linux":
            self.cpp_info.components["webp"].system_libs = ["m", "pthread"]

        # sharpyuv
        self.cpp_info.components["sharpyuv"].set_property("cmake_target_name", "WebP::sharpyuv")
        self.cpp_info.components["sharpyuv"].set_property("pkg_config_name", "libsharpyuv")
        self.cpp_info.components["sharpyuv"].libs = [libname("sharpyuv")]
        if self.settings.os == "Linux":
            self.cpp_info.components["sharpyuv"].system_libs = ["m", "pthread"]
        self.cpp_info.components["webp"].requires = ["sharpyuv"]

        # webpdemux
        self.cpp_info.components["webpdemux"].set_property("cmake_target_name", "WebP::webpdemux")
        self.cpp_info.components["webpdemux"].set_property("pkg_config_name", "libwebpdemux")
        self.cpp_info.components["webpdemux"].libs = [libname("webpdemux")]
        self.cpp_info.components["webpdemux"].requires = ["webp"]

        # webpmux
        self.cpp_info.components["webpmux"].set_property("cmake_target_name", "WebP::libwebpmux")
        self.cpp_info.components["webpmux"].set_property("pkg_config_name", "libwebpmux")
        self.cpp_info.components["webpmux"].libs = [libname("webpmux")]
        self.cpp_info.components["webpmux"].requires = ["webp"]
        if self.settings.os == "Linux":
            self.cpp_info.components["webpmux"].system_libs = ["m"]
