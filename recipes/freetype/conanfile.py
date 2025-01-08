"""
Parts of the recipe are taken from the Conan Center Index (https://github.com/conan-io/conan-center-index),
licensed under the MIT License.
"""

import re
import os
from conan import ConanFile
from conan.errors import ConanInvalidConfiguration
from conan.tools.cmake import CMake, CMakeDeps, CMakeToolchain, cmake_layout
from conan.tools.files import collect_libs, get, copy, save, load, rmdir, replace_in_file

required_conan_version = ">=2.2.2"


class ConanRecipe(ConanFile):
    name = "freetype"
    version = "2.13.3"
    homepage = "https://www.freetype.org"
    description = "A high-quality and portable font engine"
    license = "FTL"
    package_type = "shared-library"
    settings = "os", "arch", "compiler", "build_type"

    def configure(self):
        self.settings.rm_safe("compiler.libcxx")
        self.settings.rm_safe("compiler.cppstd")

    def validate(self):
        if self.settings.os == "Linux":
            raise ConanInvalidConfiguration(f"{self.name} is not supported on Linux. Please use the one provided by the system.")

    def layout(self):
        cmake_layout(self, src_folder="src")

    def requirements(self):
        self.requires("zlib/[>=1.2.11]")
        self.requires("bzip2/[>=1.0.8]")
        self.requires("libpng/[>=1.6.36]")
        self.requires("brotli/[>=1.0.9]")

    def source(self):
        get(
            self,
            sha256="5c3a8e78f7b24c20b25b54ee575d6daa40007a5f4eea2845861c3409b3021747",
            url=f"https://download.savannah.gnu.org/releases/freetype/freetype-{self.version}.tar.gz",
            strip_root=True,
        )
        replace_in_file(
            self, os.path.join(self.source_folder, "CMakeLists.txt"), 'if ("${CMAKE_BINARY_DIR}" STREQUAL "${CMAKE_SOURCE_DIR}")', "if (0)"
        )
        replace_in_file(
            self,
            os.path.join(self.source_folder, "CMakeLists.txt"),
            "find_package(BrotliDec REQUIRED)",
            "find_package(Brotli REQUIRED)\n" "set(BROTLIDEC_FOUND 1)\n" 'set(BROTLIDEC_LIBRARIES "brotli::brotli")',
        )

    def generate(self):
        tc = CMakeToolchain(self)
        tc.variables["CMAKE_DEBUG_POSTFIX"] = "_d"
        tc.variables["DISABLE_FORCE_DEBUG_POSTFIX"] = True
        tc.variables["BUILD_SHARED_LIBS"] = True
        tc.variables["CMAKE_INSTALL_RPATH"] = "$ORIGIN;$ORIGIN/../lib"

        tc.variables["PROJECT_VERSION"] = self._extract_libtool_version()

        tc.variables["FT_REQUIRE_ZLIB"] = True
        tc.variables["FT_DISABLE_ZLIB"] = not tc.variables["FT_REQUIRE_ZLIB"]

        tc.variables["FT_REQUIRE_PNG"] = True
        tc.variables["FT_DISABLE_PNG"] = not tc.variables["FT_REQUIRE_PNG"]

        tc.variables["FT_REQUIRE_BZIP2"] = True
        tc.variables["FT_DISABLE_BZIP2"] = not tc.variables["FT_REQUIRE_BZIP2"]

        tc.variables["FT_REQUIRE_BROTLI"] = True
        tc.variables["FT_DISABLE_BROTLI"] = not tc.variables["FT_REQUIRE_BROTLI"]

        # TODO: Harfbuzz can be added as an option as soon as it is available.
        tc.variables["FT_REQUIRE_HARFBUZZ"] = False
        tc.variables["FT_DISABLE_HARFBUZZ"] = not tc.variables["FT_REQUIRE_HARFBUZZ"]

        tc.generate()
        tc = CMakeDeps(self)
        tc.generate()

    def build(self):
        cmake = CMake(self)
        cmake.configure()
        cmake.build()

    def _extract_libtool_version(self):
        conf_raw = load(self, os.path.join(self.source_folder, "builds", "unix", "configure.raw"))
        return next(re.finditer(r"^version_info='([0-9:]+)'", conf_raw, flags=re.M)).group(1).replace(":", ".")

    @property
    def _libtool_version_txt(self):
        return os.path.join(self.package_folder, "config", "freetype-libtool-version.txt")

    def package(self):
        cmake = CMake(self)
        cmake.install()
        libtool_version = self._extract_libtool_version()
        save(self, self._libtool_version_txt, libtool_version)
        copy(self, "FTL.TXT", src=os.path.join(self.source_folder, "docs"), dst=os.path.join(self.package_folder, "licenses"))
        copy(self, "*.pdb", src=self.build_folder, dst=os.path.join(self.package_folder, "bin"), keep_path=False, excludes="*vc???.pdb")
        rmdir(self, os.path.join(self.package_folder, "lib", "cmake"))
        rmdir(self, os.path.join(self.package_folder, "lib", "pkgconfig"))

    def package_info(self):
        self.cpp_info.set_property("cpe", "cpe:2.3:a:freetype:freetype:*:*:*:*:*:*:*:*")
        self.cpp_info.set_property("base_purl", "github/freetype/freetype")
        self.cpp_info.set_property("cmake_find_mode", "both")
        self.cpp_info.set_property("cmake_file_name", "Freetype")
        self.cpp_info.set_property("cmake_target_name", "Freetype::Freetype")
        self.cpp_info.set_property("pkg_config_name", "freetype2")
        libtool_version = load(self, self._libtool_version_txt).strip()
        # In theory this should set the version of the generated pkg-config file:
        self.cpp_info.set_property("component_version", libtool_version)
        self.cpp_info.set_property("system_package_version", libtool_version)
        self.cpp_info.libs = collect_libs(self)
        self.cpp_info.includedirs.append("include/freetype2")

        if self.settings.os == "Linux":
            self.cpp_info.system_libs.append("m")
