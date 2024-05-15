from conan import ConanFile
from conan.tools.env import VirtualBuildEnv
from conan.tools.files import collect_libs, copy, get, rmdir, patch
from conan.tools.layout import basic_layout
from conan.tools.meson import Meson, MesonToolchain
from conan.tools.microsoft import is_msvc

required_conan_version = ">=2.2.2"


class ConanRecipe(ConanFile):
    name = "harfbuzz"
    version = "8.3.0"
    homepage = "http://harfbuzz.org"
    description = "An OpenType text shaping engine"
    license = "MIT"
    package_type = "shared-library"
    settings = "os", "arch", "compiler", "build_type"
    exports_sources = ["patches/*.patch"]

    def layout(self):
        basic_layout(self, src_folder="src")

    def source(self):
        get(self,
            sha256="109501eaeb8bde3eadb25fab4164e993fbace29c3d775bcaa1c1e58e2f15f847",
            url=f"https://github.com/harfbuzz/harfbuzz/releases/download/{self.version}/harfbuzz-{self.version}.tar.xz",
            strip_root=True
            )
        patch(self, patch_file="patches/001-debug_suffix.patch")

    def generate(self):
        VirtualBuildEnv(self).generate()
        tc = MesonToolchain(self)
        tc.project_options.update({
            "glib": "disabled",
            "icu": "disabled",
            "freetype": "disabled",
            "gdi": "enabled",
            "directwrite": "disabled",
            "gobject": "disabled",
            "introspection": "disabled",
            "cairo": "disabled",
            "tests": "disabled",
            "docs": "disabled",
            "benchmark": "disabled",
            "icu_builtin": "false",
            "utilities": "disabled"
        })

        if is_msvc(self):
            tc.cpp_args.append("/bigobj")

        tc.generate()

    def build(self):
        meson = Meson(self)
        meson.configure()
        meson.build()

    def package(self):
        copy(self, "COPYING", self.source_path, self.package_path / "licenses")
        meson = Meson(self)
        meson.install()
        rmdir(self, self.package_path / "lib" / "cmake")
        rmdir(self, self.package_path / "lib" / "pkgconfig")

    def package_info(self):
        self.cpp_info.set_property("cmake_file_name", "harfbuzz")
        self.cpp_info.set_property("cmake_target_name", "harfbuzz::harfbuzz")
        self.cpp_info.set_property("cmake_target_aliases", ["Harfbuzz::Harfbuzz"])
        self.cpp_info.set_property("pkg_config_name", "harfbuzz")
        self.cpp_info.libs = collect_libs(self)
        self.cpp_info.includedirs.append("include/harfbuzz")
        if self.settings.os == "Linux":
            self.cpp_info.system_libs.append("m")
