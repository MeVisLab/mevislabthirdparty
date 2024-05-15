from conan import ConanFile
from conan.tools.cmake import CMake, CMakeToolchain, cmake_layout
from conan.tools.env import VirtualBuildEnv
from conan.tools.files import copy, get, rmdir, patch, replace_in_file
from conan.tools.microsoft import is_msvc

required_conan_version = ">=2.2.2"


class ConanRecipe(ConanFile):
    name = "libjpeg-turbo"
    provides = "libjpeg"
    version = "3.0.2"
    description = "SIMD-accelerated libjpeg-compatible JPEG codec library"
    license = ("BSD-3-Clause", "IJG", "Zlib")
    homepage = "https://libjpeg-turbo.org"
    package_type = "shared-library"
    settings = "os", "arch", "compiler", "build_type"
    exports_sources = "patches/*.patch"

    def configure(self):
        self.settings.rm_safe("compiler.cppstd")
        self.settings.rm_safe("compiler.libcxx")

    def layout(self):
        cmake_layout(self, src_folder="src")

    def source(self):
        get(
            self,
            sha256="c2ce515a78d91b09023773ef2770d6b0df77d674e144de80d63e0389b3a15ca6",
            url=f"https://github.com/libjpeg-turbo/libjpeg-turbo/releases/download/{self.version}/libjpeg-turbo-{self.version}.tar.gz",
            strip_root=True,
        )
        patch(self, patch_file="patches/001-change_rpath.patch")
        patch(self, patch_file="patches/002-cmake_use_gnuinstalldirs.patch")
        replace_in_file(self, self.source_path / "sharedlib/CMakeLists.txt", " jpeg${SO_MAJOR_VERSION}", " jpeg")

    def generate(self):
        env = VirtualBuildEnv(self)
        env.generate()

        tc = CMakeToolchain(self)
        tc.variables["CMAKE_DEBUG_POSTFIX"] = "_d"
        # tc.variables["CMAKE_POSITION_INDEPENDENT_CODE"] = True
        tc.variables["ENABLE_STATIC"] = False
        tc.variables["ENABLE_SHARED"] = True
        tc.variables["WITH_SIMD"] = True
        tc.variables["REQUIRE_SIMD"] = True  # no simd -> error!
        tc.variables["WITH_ARITH_ENC"] = True
        tc.variables["WITH_ARITH_DEC"] = True
        tc.variables["WITH_JPEG7"] = True
        tc.variables["WITH_JPEG8"] = True
        tc.variables["WITH_MEM_SRCDST"] = True
        tc.variables["WITH_TURBOJPEG"] = True
        tc.variables["WITH_JAVA"] = False
        tc.variables["WITH_12BIT"] = False  # 12 bit is not compatible with Qt
        if is_msvc(self):
            tc.variables["WITH_CRT_DLL"] = True
        tc.generate()

    def build(self):
        cmake = CMake(self)
        cmake.configure()
        cmake.build()

    def package(self):
        copy(self, "LICENSE.md", src=self.source_path, dst=self.package_path / "licenses")
        cmake = CMake(self)
        cmake.install()
        rmdir(self, self.package_path / "share")
        rmdir(self, self.package_path / "lib" / "pkgconfig")
        rmdir(self, self.package_path / "lib" / "cmake")

    def package_info(self):
        self.cpp_info.set_property("cmake_find_mode", "both")
        self.cpp_info.set_property("cmake_module_file_name", "JPEG")
        self.cpp_info.set_property("cmake_file_name", "libjpeg-turbo")

        lib_suffix = "_d" if self.settings.build_type == "Debug" else ""
        self.cpp_info.components["jpeg"].set_property("cmake_module_target_name", "JPEG::JPEG")
        self.cpp_info.components["jpeg"].set_property("cmake_target_name", "libjpeg-turbo::jpeg")
        self.cpp_info.components["jpeg"].set_property("pkg_config_name", "libjpeg")
        self.cpp_info.components["jpeg"].libs = [f"jpeg{lib_suffix}"]

        self.cpp_info.components["turbojpeg"].set_property("cmake_target_name", "libjpeg-turbo::turbojpeg")
        self.cpp_info.components["turbojpeg"].set_property("pkg_config_name", "libturbojpeg")
        self.cpp_info.components["turbojpeg"].libs = [f"turbojpeg{lib_suffix}"]
