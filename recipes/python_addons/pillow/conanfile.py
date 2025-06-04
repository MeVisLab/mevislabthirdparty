from conan import ConanFile
from conan.tools.env import Environment
from conan.tools.files import get, patch, replace_in_file

required_conan_version = ">=2.0.0"


class ConanRecipe(ConanFile):
    name = "pillow"
    version = "11.2.1"
    homepage = "https://python-pillow.org/"
    description = "Python Imaging Library (Fork)"
    license = "HPND"
    python_requires = "python_package/[>=1.0.0]"
    python_requires_extend = "python_package.PythonPackageRecipe"
    exports_sources = "requirements.txt", "patches/*"
    package_type = "application"
    parallel_make = False

    mlab_hooks = {
        "dependencies.system_libs": [
            "libfreetype.so.6",
            "libxcb.so.1",
        ],
    }

    @property
    def license_path(self):
        return "LICENSE"

    def configure(self):
        self.settings.rm_safe("compiler.libcxx")
        self.settings.rm_safe("compiler.cppstd")

    def python_requirements(self):
        self.requires("harfbuzz/[>=7.3.0]")
        self.requires("libjpeg-turbo/[>=2.1.5]")
        self.requires("libpng/[>=1.6.37]")
        self.requires("tiff/[>=4.1.0]")
        self.requires("zlib/[>=1.2.11]")
        if self.settings.os == "Windows":
            self.requires("freetype/[>=2.13.0]")

    def generate(self):
        super().generate()
        env = Environment()
        dep_names = ["libpng", "zlib", "libjpeg-turbo", "tiff"]
        if self.settings.os == "Windows":
            dep_names.append("freetype")

        for dep_name in dep_names:
            for include_dir in self.dependencies[dep_name].cpp_info.includedirs:
                env.prepend_path("INCLUDE", include_dir)
            for lib_dir in self.dependencies[dep_name].cpp_info.libdirs:
                env.prepend_path("LIB", lib_dir)
        env_vars = env.vars(self, scope="build")
        env_vars.save_script("add_dirs")

    def source(self):
        get(
            self,
            sha256="67dd6d40e282fd3b50189bd7f68a6e9b8e59b297d3684cb35ab107e7aec8379e",
            url=f"https://github.com/python-pillow/Pillow/archive/refs/tags/{self.version}.tar.gz",
            strip_root=True,
        )
        patch(
            self,
            patch_file="patches/001-find_debug_libraries.patch",
            patch_description="Check for debug libraries if in debug mode",
        )
        patch(
            self,
            patch_file="patches/002-debug_extension.patch",
            patch_description="Under Linux/debug also check for libraries with _d",
        )

    def build(self):
        env = Environment()
        env.define("PKG_CONFIG", "invalid-command")  # FIXME hack to not use pkg-config on linux
        is_win = self.settings.os == "Windows"
        if self.settings.build_type == "Debug":
            if is_win:
                # disable flaky multithreaded debug build under Windows
                env.append("MAX_CONCURRENCY", "1")
            else:
                # workaround for Python not build in debug mode under Linux
                replace_in_file(self, self.source_path / "setup.py", 'hasattr(sys, "gettotalrefcount")', "True")
        with env.vars(self).apply():
            config_settings = [
                "zlib=enable",
                "jpeg=disable",
                "tiff=enable",
                "freetype=enable",
                "raqm=disable",
                "lcms=disable",
                "webp=disable",
                "webpmux=disable",
                "jpeg2000=disable",
                "imagequant=disable",
                f"xcb={'disable' if is_win else 'enable'}",
            ]
            self.default_build(config_settings=config_settings)

    def package_info(self):
        super().package_info()
        self.cpp_info.set_property("cpe", "cpe:2.3:a:python:pillow:*:*:*:*:*:*:*:*")
        self.cpp_info.set_property("purl", f"pkg:github/python-pillow/Pillow@{self.version}")
