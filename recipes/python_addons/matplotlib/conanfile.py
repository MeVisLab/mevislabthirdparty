import glob
import os

from conan import ConanFile
from conan.tools.files import get, patch
from conan.tools.gnu import PkgConfigDeps
from conan.tools.meson import MesonToolchain

required_conan_version = ">=2.2.2"


class ConanRecipe(ConanFile):
    name = "matplotlib"
    version = "3.10.7"
    homepage = "https://matplotlib.org"
    description = "A comprehensive library for creating static, animated, and interactive visualizations in Python"
    license = "Python-2.0"
    python_requires = "python_package/[>=1.0.0]"
    python_requires_extend = "python_package.PythonPackageRecipe"
    exports_sources = "patches/*", "requirements.txt"
    package_type = "application"
    parallel_make = False

    mlab_hooks = {
        "dependencies.system_libs": [
            "libfreetype.so.6",
        ],
    }

    @property
    def license_path(self):
        return "LICENSE/LICENSE*"

    def python_requirements(self):
        self.requires("contourpy/[>=1.3.1]")
        self.requires("kiwisolver/[>=1.4.4]")
        self.requires("libpng/[>=1.6.37]")
        self.requires("numpy/[>=1.16.4]")
        self.requires("pillow/[>=10.2]")
        self.requires("qhull/[>=8.0.2]")
        self.requires("zlib/[>=1.2.11]")
        if self.settings.os != "Linux":
            self.requires("freetype/[>=2.10.2]")

    def generate(self):
        super().generate()
        deps = PkgConfigDeps(self)
        deps.generate()
        tc = MesonToolchain(self)
        tc.generate()

    def source(self):
        get(
            self,
            sha256="0678f04e55c839c543a3803a7a13ab427f488ff396d85ffbad7d427f6fdcbbc3",
            url=f"https://github.com/matplotlib/matplotlib/archive/refs/tags/v{self.version}.tar.gz",
            strip_root=True,
        )
        patch(self, patch_file="patches/001-add_support_for_a_PythonQt_backend.patch")
        patch(self, patch_file="patches/002-notice_running_eventloop.patch")
        patch(self, patch_file="patches/003-define_py_debug.patch")

    def build(self):
        build_type = str(self.settings.build_type).lower()
        self.default_build(
            config_settings=[
                f"setup-args=-Dbuildtype={build_type}",
                f"setup-args=-Dsystem-freetype=true",
                f"setup-args=-Dsystem-qhull=true",
                f"setup-args=-Db_lto=false",
            ]
        )

    def package(self):
        self.default_package()
        if self.settings.os == "Linux":
            site_package_folder = os.path.join(self.package_folder, self.relative_site_package_folder())
            for sofile in glob.glob(f"{site_package_folder}/**/*.so", recursive=True):
                self.run(f"patchelf --remove-rpath {sofile}")

    def package_info(self):
        super().package_info()
        # self.cpp_info.set_property("cpe", "")  # No CPE (yet)?
        self.cpp_info.set_property("purl", f"pkg:github/matplotlib/matplotlib@v{self.version}")
