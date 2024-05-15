from conan import ConanFile
from conan.tools.cmake import CMake, CMakeDeps, CMakeToolchain, cmake_layout
from conan.tools.files import collect_libs
from conan.tools.files import get, copy, rmdir, patch
from conan.tools.scm import Version

required_conan_version = ">=2.2.2"


class ConanRecipe(ConanFile):
    name = "libxslt"
    version = "1.1.39"
    homepage = "http://xmlsoft.org"
    description = "libxslt is a software library implementing XSLT processor, based on libxml2"
    license = "MIT"
    package_type = "shared-library"
    settings = "os", "arch", "compiler", "build_type"
    exports_sources = "patches/*.patch"

    def configure(self):
        self.settings.rm_safe("compiler.libcxx")
        self.settings.rm_safe("compiler.cppstd")

    def layout(self):
        cmake_layout(self, src_folder="src")

    def requirements(self):
        self.requires("zlib/[>=1.2.11]")
        self.requires("libxml2/[>=2.9.0]", transitive_headers=True)

    def source(self):
        v = Version(self.version)
        get(self,
            sha256="2a20ad621148339b0759c4d4e96719362dee64c9a096dbba625ba053846349f0",
            url=f"https://download.gnome.org/sources/libxslt/{v.major}.{v.minor}/libxslt-{self.version}.tar.xz",
            strip_root=True
        )
        patch(self, patch_file="patches/001-debug_postfix.patch")


    def generate(self):
        tc = CMakeToolchain(self)
        tc.variables["CMAKE_DEBUG_POSTFIX"] = "_d"
        tc.variables["BUILD_SHARED_LIBS"] = True
        tc.variables["CMAKE_INSTALL_RPATH"] = "$ORIGIN;$ORIGIN/../lib"
        tc.variables["LIBXSLT_WITH_TESTS"] = False
        tc.variables["LIBXSLT_WITH_PYTHON"] = False
        tc.generate()
        tc = CMakeDeps(self)
        tc.generate()

    def build(self):
        cmake = CMake(self)
        cmake.configure()
        cmake.build()

    def package(self):
        cmake = CMake(self)
        cmake.install()
        copy(self, "COPYING", src=self.source_path, dst=self.package_path / "licenses")
        rmdir(self, self.package_path / "lib" / "cmake")
        rmdir(self, self.package_path / "lib" / "pkgconfig")
        rmdir(self, self.package_path / "share")
        if self.settings.os == "Windows":
            copy(self, "libpng*.pdb",
                 src=self.build_path / "bin",
                 dst=self.package_path / "bin")

    def package_info(self):
        self.cpp_info.set_property("cmake_find_mode", "both")
        self.cpp_info.set_property("cmake_file_name", "LibXslt")
        self.cpp_info.set_property("cmake_target_name", "LibXslt::LibXslt")
        self.cpp_info.libs = collect_libs(self)

        if self.settings.os == "Windows":
            self.cpp_info.system_libs.append('ws2_32')
        else:
            self.cpp_info.system_libs.append("m")
