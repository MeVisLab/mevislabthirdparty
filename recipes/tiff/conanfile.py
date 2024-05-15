from conan import ConanFile
from conan.tools.cmake import CMake, CMakeToolchain, CMakeDeps, cmake_layout
from conan.tools.files import get, copy, patch, rmdir, collect_libs, replace_in_file
from conan.tools.scm import Version

required_conan_version = ">=2.2.2"


class ConanRecipe(ConanFile):
    name = "tiff"
    version = "4.6.0"
    homepage = "http://simplesystems.org/libtiff"
    description = "Tag Image File Format (TIFF) library"
    license = "libtiff"
    package_type = "shared-library"
    settings = "os", "arch", "compiler", "build_type"
    exports_sources = "patches/*.patch"

    def configure(self):
        self.settings.rm_safe("compiler.libcxx")
        self.settings.rm_safe("compiler.cppstd")

    def layout(self):
        cmake_layout(self, src_folder="src")

    def requirements(self):
        self.requires("libjpeg-turbo/[>=2.1]")
        self.requires("libwebp/[>=1.3]")
        self.requires("xz-utils/[>=5.2]")
        self.requires("zlib/[>=1.3]")
        self.requires("zstd/[>=1.5]")

    def source(self):
        get(self,
            sha256="88b3979e6d5c7e32b50d7ec72fb15af724f6ab2cbf7e10880c360a77e4b5d99a",
            url=f"https://download.osgeo.org/libtiff/tiff-{self.version}.tar.gz",
            strip_root=True)
        # work-around for https://github.com/conan-io/conan/issues/12180:
        patch(self, patch_file="patches/cmake-dependencies.patch")
        replace_in_file(self, self.source_path / "cmake" / "WindowsSupport.cmake", 'set(CMAKE_DEBUG_POSTFIX "d")', '#set(CMAKE_DEBUG_POSTFIX "d")')
        replace_in_file(self, self.source_path / "cmake" / "Findliblzma.cmake", 'find_library(LIBLZMA_LIBRARY_DEBUG NAMES lzmad liblzmad', 'find_library(LIBLZMA_LIBRARY_DEBUG NAMES lzmad lzma_d liblzmad liblzma_d')

    def generate(self):
        deps = CMakeDeps(self)
        deps.generate()
        tc = CMakeToolchain(self)
        tc.variables["CMAKE_DEBUG_POSTFIX"] = "_d"
        tc.variables["BUILD_SHARED_LIBS"] = "ON"
        tc.variables["CMAKE_INSTALL_RPATH"] = "$ORIGIN;$ORIGIN/../lib"
        tc.variables['CMAKE_INSTALL_LIBDIR'] = 'lib'
        tc.variables['CMAKE_INSTALL_BINDIR'] = 'bin'
        tc.variables['CMAKE_INSTALL_INCLUDEDIR'] = 'include'

        tc.variables['CMAKE_DISABLE_FIND_PACKAGE_OpenGL'] = True
        tc.variables['CMAKE_DISABLE_FIND_PACKAGE_GLUT'] = True

        tc.variables['tiff-install'] = True
        tc.variables['tiff-docs'] = False

        tc.variables["cxx"] = False
        tc.variables["jbig"] = False
        tc.variables["jpeg"] = True
        tc.variables["jpeg12"] = False
        tc.variables["lzma"] = True
        tc.variables["webp"] = True
        tc.variables["zlib"] = True
        tc.variables["zstd"] = True
        tc.generate()


    def build(self):
        cmake = CMake(self)
        cmake.configure()
        cmake.build()

    def package(self):
        cmake = CMake(self)
        cmake.install()
        copy(self, "LICENSE.md", src=self.source_path, dst=self.package_path / "licenses")
        copy(self, "*.pdb", src=self.build_path / "libtiff", dst=self.package_path / "bin",
             keep_path=False, excludes="*vc???.pdb")
        if self.settings.os != "Windows":
            rmdir(self, self.package_path / "bin")
        rmdir(self, self.package_path / "share")
        rmdir(self, self.package_path / "lib" / "cmake")
        rmdir(self, self.package_path / "lib" / "pkgconfig")

    def package_info(self):
        self.cpp_info.set_property("cmake_find_mode", "both")
        self.cpp_info.set_property("cmake_file_name", "TIFF")
        self.cpp_info.set_property("cmake_target_name", "TIFF::TIFF")
        self.cpp_info.set_property("pkg_config_name", f"libtiff-{Version(self.version).major}")
        self.cpp_info.libs = collect_libs(self)

        if self.settings.os == "Linux":
            self.cpp_info.system_libs.append("m")
