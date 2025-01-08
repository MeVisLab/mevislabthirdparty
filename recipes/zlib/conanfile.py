import os
import textwrap

from conan import ConanFile
from conan.tools.cmake import CMake, CMakeToolchain, cmake_layout
from conan.tools.files import collect_libs, copy
from conan.tools.files import get, patch, load, save
from conan.tools.scm import Version

required_conan_version = ">=2.2.2"


class ConanRecipe(ConanFile):
    name = "zlib"
    version = "1.3.1"
    homepage = "https://zlib.net"
    license = "Zlib"
    description = "A Massively Spiffy Yet Delicately Unobtrusive Compression Library"
    settings = "os", "arch", "compiler", "build_type"
    package_type = "static-library"
    exports_sources = "patches/*.patch"

    def configure(self):
        self.settings.rm_safe("compiler.libcxx")
        self.settings.rm_safe("compiler.cppstd")

    def layout(self):
        cmake_layout(self, src_folder="src")

    def source(self):
        v = Version(self.version)
        vstr = f"{v.major}.{v.minor}" + ("" if v.patch == 0 else f".{v.patch}")
        get(
            self,
            sha256="9a93b2b7dfdac77ceba5a558a580e74667dd6fede4585b91eefb60f03b72df23",
            url=f"https://github.com/madler/zlib/releases/download/v{vstr}/zlib-{vstr}.tar.gz",
            strip_root=True,
        )
        patch(self, patch_file="patches/001-fix_cmake.patch")
        patch(self, patch_file="patches/002-windows_nano_server.patch")

    def generate(self):
        tc = CMakeToolchain(self)
        tc.variables["CMAKE_DEBUG_POSTFIX"] = "_d"
        tc.variables["BUILD_SHARED_LIBS"] = False
        tc.variables["ZLIB_BUILD_EXAMPLES"] = False
        tc.variables["CMAKE_POSITION_INDEPENDENT_CODE"] = True
        tc.variables["CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS"] = True
        tc.variables["CMAKE_C_VISIBILITY_PRESET"] = "default"
        tc.variables["CMAKE_CXX_VISIBILITY_PRESET"] = "default"
        tc.variables["CMAKE_VISIBILITY_INLINES_HIDDEN"] = False

        tc.variables["SKIP_INSTALL_ALL"] = False
        tc.variables["SKIP_INSTALL_LIBRARIES"] = False
        tc.variables["SKIP_INSTALL_HEADERS"] = False
        tc.variables["SKIP_INSTALL_FILES"] = True

        tc.variables["INSTALL_LIB_DIR"] = "lib"
        tc.variables["INSTALL_INC_DIR"] = "include"

        tc.cache_variables["CMAKE_INSTALL_PREFIX"] = ""

        tc.generate()

    def build(self):
        cmake = CMake(self)
        cmake.configure()
        cmake.build()

    def package(self):
        self._write_license_file()
        copy(self, "*.pdb", src=self.build_path, dst=self.package_path / "bin", keep_path=False)
        cmake = CMake(self)
        cmake.install()
        self._cmake_module_file_write()

    def package_info(self):
        self.cpp_info.set_property("cpe", "cpe:2.3:a:zlib:zlib:*:*:*:*:*:*:*:*")
        self.cpp_info.set_property("base_purl", "github/madler/zlib")
        self.cpp_info.set_property("cmake_find_mode", "both")
        self.cpp_info.set_property("cmake_file_name", "ZLIB")
        self.cpp_info.set_property("cmake_target_name", "ZLIB::ZLIB")
        self.cpp_info.set_property("pkg_config_name", "zlib")
        self.cpp_info.set_property("cmake_build_modules", [self._cmake_module_file])
        self.cpp_info.set_property("cmake_find_package", [self._cmake_module_file])
        self.cpp_info.libs = collect_libs(self)

    def _write_license_file(self):
        license_header = load(self, os.path.join(self.source_folder, "zlib.h"))
        license_contents = license_header[2 : license_header.find("*/", 1)]
        license_file = self.package_path / "licenses" / "LICENSE"
        save(self, license_file, license_contents)

    @property
    def _cmake_module_file(self):
        return os.path.join("lib", "cmake", f"{self.name}-variables.cmake")

    def _cmake_module_file_write(self):
        v = Version(self.version)
        file = self.package_path / self._cmake_module_file
        content = textwrap.dedent(
            f"""\
            set(ZLIB_FOUND TRUE)
            set(ZLIB_LIBRARY ZLIB::ZLIB)
            set(ZLIB_VERSION "{self.version}")
            set(ZLIB_VERSION_STRING "{self.version}")
            set(ZLIB_VERSION_MAJOR {v.major})
            set(ZLIB_VERSION_MINOR {v.minor})
            set(ZLIB_VERSION_PATCH {v.patch})
            set(ZLIB_VERSION_TWEAK 0)
            set(ZLIB_MAJOR_VERSION {v.major})
            set(ZLIB_MINOR_VERSION {v.minor})
            set(ZLIB_PATCH_VERSION {v.patch})
            """
        )
        save(self, file, content)
