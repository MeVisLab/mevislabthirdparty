import os
from conan import ConanFile
from conan.tools.env import Environment
from conan.tools.files import get, patch, replace_in_file

required_conan_version = ">=2.2.2"


class ConanRecipe(ConanFile):
    name = "matplotlib"
    version = "3.2.2"
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
            "libpng16.so.16",  # FIXME MLAB-2790
        ]
    }

    @property
    def license_path(self):
        return "LICENSE/LICENSE*"

    def python_requirements(self):
        self.requires("kiwisolver/[>=1.4.4]")
        self.requires("libpng/[>=1.6.37]")
        self.requires("numpy/[>=1.16.4]")
        self.requires("zlib/[>=1.2.11]")
        if self.settings.os != "Linux":
            self.requires("freetype/[>=2.10.2]")

    def generate(self):
        super().generate()
        if self.settings.os == "Windows":
            env = Environment()
            for dep_name in ("freetype", "libpng", "numpy"):
                for include_dir in self.dependencies[dep_name].cpp_info.includedirs:
                    env.append_path("INCLUDE", include_dir)
            for dep_name in ("freetype", "libpng", "zlib"):
                for lib_dir in self.dependencies[dep_name].cpp_info.libdirs:
                    env.append_path("LIB", lib_dir)
            envvars = env.vars(self, scope="build")
            envvars.save_script("add_dirs")

    def source(self):
        get(
            self,
            url=f"https://github.com/matplotlib/matplotlib/archive/refs/tags/v{self.version}.tar.gz",
            sha256="dd4ff3e19f507a5a07612fa642e6e66fadbaf303483a43dc3acb04067f7ac522",
            strip_root=True,
        )

        get(
            self,
            url="https://jqueryui.com/resources/download/jquery-ui-1.12.1.zip",
            destination=os.path.join(self.source_folder, "lib", "matplotlib", "backends", "web_backend"),
            sha256="f8233674366ab36b2c34c577ec77a3d70cac75d2e387d8587f3836345c0f624d",
        )

        patch(self, patch_file="patches/001-add_support_for_a_PythonQt_backend.patch")
        patch(self, patch_file="patches/002-notice_running_eventloop.patch")
        # This is mostly an amalgam of
        # https://github.com/matplotlib/matplotlib/commit/1cbf8ffa38c5621303d13240ca26d523529ffb3e
        # and
        # https://github.com/matplotlib/matplotlib/commit/b1b0006253f59bb42df36d28cd3e73ea3343a507
        # (and what else had happened at that place until matplotlib 3.6.3).
        # This avoids a deprecation warning from numpy:
        patch(self, patch_file="patches/003-optimize_colors_to_rgba.patch")
        # Do necessary changes for Qt6 (the bare minimum):
        patch(self, patch_file="patches/004-adapt_to_Qt6.patch")
        patch(self, patch_file="patches/005-fix_invalid_conversion.patch")

        replace_in_file(self, os.path.join(self.source_folder, "setupext.py"), 'ext.extra_link_args.extend(["-mwindows"])', "")
        # Conan currently uses the library version for the pkg-config, but freetype should use the libtool version:
        replace_in_file(self, os.path.join(self.source_folder, "setupext.py"), "atleast_version='9.11.3',", "atleast_version='2.3.0',")

    def build(self):
        d_suffix = "_d" if self.settings.build_type == "Debug" else ""
        replace_in_file(
            self,
            os.path.join(self.source_folder, "setupext.py"),
            "['png', 'z'] if os.name == 'posix' else",
            f"['libpng16{d_suffix}', 'zlib{d_suffix}'] if os.name == 'posix' else",
        )
        replace_in_file(
            self,
            os.path.join(self.source_folder, "setupext.py"),
            "[deplib('libpng16'), deplib('z')] if os.name == 'nt' else",
            f"['libpng16{d_suffix}', 'zlib{d_suffix}'] if os.name == 'nt' else",
        )

        if self.settings.os == "Linux":
            replace_in_file(
                self,
                os.path.join(self.source_folder, "setupext.py"),
                "default_libraries=['freetype', deplib('z')])",
                f"default_libraries=['freetype', 'zlib{d_suffix}', 'libpng16{d_suffix}'])",
            )
        else:
            replace_in_file(
                self,
                os.path.join(self.source_folder, "setupext.py"),
                "default_libraries=['freetype', deplib('z')])",
                f"default_libraries=['freetype{d_suffix}', 'zlib{d_suffix}', 'libpng16{d_suffix}'])",
            )

        super().build()
