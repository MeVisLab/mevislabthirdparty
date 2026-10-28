import os

from conan import ConanFile
from conan.tools.env import VirtualBuildEnv
from conan.tools.files import copy, get, patch, rm, rmdir
from conan.tools.gnu import PkgConfigDeps
from conan.tools.layout import basic_layout
from conan.tools.meson import Meson, MesonToolchain

required_conan_version = ">=2.32.0"


class ConanRecipe(ConanFile):
    name = "raqm"
    version = "0.11.0"
    homepage = "https://github.com/HOST-Oman/libraqm"
    description = "A library for complex text layout"
    license = "MIT"
    settings = "os", "arch", "compiler", "build_type"
    package_type = "shared-library"
    exports_sources = "patches/*.patch"

    mlab_hooks = {
        "dependencies.system_libs": [
            "libfreetype.so.6",
        ],
    }

    def configure(self):
        self.settings.rm_safe("compiler.cppstd")
        self.settings.rm_safe("compiler.libcxx")

    def layout(self):
        basic_layout(self, src_folder="src")

    def requirements(self):
        self.requires("harfbuzz/[>=14.0.0]")
        self.requires("sheenbidi/[>=3.0.0]")
        if self.settings.os != "Linux":
            # raqm.h includes <ft2build.h>, so consumers need the FreeType headers as well
            self.requires("freetype/[>=2.13.0]", transitive_headers=True, transitive_libs=True)

    def source(self):
        get(
            self,
            sha256="3d0add115f7d4a9410d3377462ed3c05e86342193ef984183e4380e3787b2d4c",
            url=f"https://github.com/HOST-Oman/libraqm/releases/download/v{self.version}/raqm-{self.version}.tar.xz",
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
                "docs": "false",
                "sheenbidi": "true",
                "tests": "false",
            }
        )
        tc.generate()

    def build(self):
        meson = Meson(self)
        meson.configure()
        meson.build()

    def package(self):
        copy(self, "COPYING", src=self.source_folder, dst=os.path.join(self.package_folder, "licenses"))
        meson = Meson(self)
        meson.install()
        rmdir(self, os.path.join(self.package_folder, "lib", "pkgconfig"))

    def package_info(self):
        # self.cpp_info.set_property("cpe", "")  # No CPE (yet)?
        self.cpp_info.set_property("purl", f"pkg:github/HOST-Oman/libraqm@v{self.version}")
        self.cpp_info.set_property("cmake_file_name", "raqm")
        self.cpp_info.set_property("cmake_target_name", "raqm::raqm")
        self.cpp_info.set_property("pkg_config_name", "raqm")
        suffix = "_d" if self.settings.build_type == "Debug" else ""
        self.cpp_info.libs = [f"raqm{suffix}"]
