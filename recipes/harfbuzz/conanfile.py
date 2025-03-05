from conan import ConanFile
from conan.tools.env import VirtualBuildEnv
from conan.tools.files import collect_libs, copy, get, rmdir, patch
from conan.tools.layout import basic_layout
from conan.tools.meson import Meson, MesonToolchain
from conan.tools.microsoft import is_msvc
import os

required_conan_version = ">=2.2.2"


class ConanRecipe(ConanFile):
    name = "harfbuzz"
    version = "10.2.0"
    homepage = "http://harfbuzz.org"
    description = "An OpenType text shaping engine"
    license = "MIT"
    package_type = "shared-library"
    settings = "os", "arch", "compiler", "build_type"
    exports_sources = ["patches/*.patch"]

    mlab_hooks = {
        "dependencies.system_libs": [
            "libfreetype.so.6",  # freetype
        ]
    }

    def layout(self):
        basic_layout(self, src_folder="src")

    def source(self):
        get(
            self,
            sha256="620e3468faec2ea8685d32c46a58469b850ef63040b3565cde05959825b48227",
            url=f"https://github.com/harfbuzz/harfbuzz/releases/download/{self.version}/harfbuzz-{self.version}.tar.xz",
            strip_root=True,
        )
        patch(self, patch_file="patches/001-debug_suffix.patch")

    def generate(self):
        VirtualBuildEnv(self).generate()
        tc = MesonToolchain(self)
        tc.project_options.update(
            {
                "glib": "disabled",
                "icu": "disabled",
                "gdi": "enabled",
                "directwrite": "disabled",
                "gobject": "disabled",
                "introspection": "disabled",
                "cairo": "disabled",
                "tests": "disabled",
                "docs": "disabled",
                "benchmark": "disabled",
                "icu_builtin": "false",
                "utilities": "disabled",
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
        rmdir(self, os.path.join(self.package_folder, "lib", "cmake"))
        rmdir(self, os.path.join(self.package_folder, "lib", "pkgconfig"))

    def package_info(self):
        self.cpp_info.set_property("cpe", "cpe:2.3:a:harfbuzz_project:harfbuzz:*:*:*:*:*:*:*:*")
        self.cpp_info.set_property("base_purl", "github/harfbuzz/harfbuzz")
        self.cpp_info.set_property("cmake_file_name", "harfbuzz")
        self.cpp_info.set_property("cmake_target_name", "harfbuzz::harfbuzz")
        self.cpp_info.set_property("cmake_target_aliases", ["Harfbuzz::Harfbuzz"])
        self.cpp_info.set_property("pkg_config_name", "harfbuzz")
        self.cpp_info.libs = collect_libs(self)
        self.cpp_info.includedirs.append("include/harfbuzz")
        if self.settings.os == "Linux":
            self.cpp_info.system_libs.append("m")
