from conan import ConanFile
from conan.tools.env import VirtualBuildEnv
from conan.tools.files import collect_libs, copy, get, rm, rmdir, patch
from conan.tools.gnu import PkgConfigDeps
from conan.tools.layout import basic_layout
from conan.tools.meson import Meson, MesonToolchain
from conan.tools.microsoft import is_msvc
import os

required_conan_version = ">=2.32.0"


class ConanRecipe(ConanFile):
    name = "harfbuzz"
    version = "14.6.0"
    homepage = "http://harfbuzz.org"
    description = "An OpenType text shaping engine"
    license = "MIT"
    package_type = "shared-library"
    settings = "os", "arch", "compiler", "build_type"
    exports_sources = ["patches/*.patch"]

    mlab_hooks = {
        "dependencies.system_libs": ["libfreetype.so.6"],
    }

    def requirements(self):
        if self.settings.os != "Linux":
            self.requires("freetype/[>=2.13.0]")

    def layout(self):
        basic_layout(self, src_folder="src")

    def source(self):
        get(
            self,
            sha256="d07a007327277708a2a73ae437887cdbaf282937f6d03ca5467723e9099af586",
            url=f"https://github.com/harfbuzz/harfbuzz/releases/download/{self.version}/harfbuzz-{self.version}.tar.xz",
            strip_root=True,
        )
        patch(self, patch_file="patches/001-debug_suffix.patch")
        rm(self, "*.wrap", os.path.join(self.source_folder, "subprojects"))

    def generate(self):
        VirtualBuildEnv(self).generate()
        PkgConfigDeps(self).generate()
        tc = MesonToolchain(self)
        tc.project_options.update(
            {
                "benchmark": "disabled",
                "cairo": "disabled",
                "directwrite": "disabled",
                "docs": "disabled",
                "freetype": "enabled",
                "gdi": "enabled",
                "glib": "disabled",
                "gobject": "disabled",
                "gpu": "disabled",
                "icu_builtin": "false",
                "icu": "disabled",
                "introspection": "disabled",
                "png": "disabled",
                "raster": "disabled",
                "tests": "disabled",
                "utilities": "disabled",
                "vector": "disabled",
                "zlib": "disabled",
            }
        )

        if is_msvc(self):
            tc.cpp_args.append("/bigobj")

        tc.generate()

    def build(self):
        meson = Meson(self)
        meson.configure()
        meson.build()

    def package(self):
        copy(self, "COPYING", self.source_folder, os.path.join(self.package_folder, "licenses"))
        meson = Meson(self)
        meson.install()
        rmdir(self, os.path.join(self.package_folder, "share"))
        rmdir(self, os.path.join(self.package_folder, "lib", "cmake"))
        rmdir(self, os.path.join(self.package_folder, "lib", "pkgconfig"))

    def package_info(self):
        self.cpp_info.set_property("cpe", f"cpe:2.3:a:harfbuzz_project:harfbuzz:{self.version}:*:*:*:*:*:*:*")
        self.cpp_info.set_property("purl", f"pkg:github/harfbuzz/harfbuzz@{self.version}")
        self.cpp_info.set_property("cmake_file_name", "harfbuzz")
        self.cpp_info.set_property("cmake_target_name", "harfbuzz::harfbuzz")
        self.cpp_info.set_property("cmake_target_aliases", ["Harfbuzz::Harfbuzz"])
        self.cpp_info.set_property("pkg_config_name", "harfbuzz")
        self.cpp_info.libs = collect_libs(self)
        self.cpp_info.includedirs.append("include/harfbuzz")
        if self.settings.os == "Linux":
            self.cpp_info.system_libs.append("m")
