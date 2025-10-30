import os
from conan import ConanFile
from conan.errors import ConanInvalidConfiguration
from conan.tools.files import get, rmdir, copy, replace_in_file
from conan.tools.layout import basic_layout
from conan.tools.meson import Meson, MesonToolchain

required_conan_version = ">=2.0.7"


class ConanRecipe(ConanFile):
    name = "mesa"
    display_name = "Mesa"
    version = "25.2.2"
    homepage = "https://mesa3d.org"
    description = "an open source software implementation of OpenGL, Vulkan, and other graphics API specifications"
    license = "MIT"
    settings = "os", "compiler", "arch", "build_type"
    package_type = "shared-library"
    exports_sources = ["patches/*", "LICENSE"]

    mlab_hooks = {
        "test_package.skip": True,
        "dependencies.system_libs": [
            "libdrm.so.2",
            "libsensors.so.5",
            "libunwind.so.8",
            "libwayland-client.so.0",
            "libwayland-server.so.0",
            "libX11-xcb.so.1",
            "libxcb-dri2.so.0",
            "libxcb-dri3.so.0",
            "libxcb-glx.so.0",
            "libxcb-present.so.0",
            "libxcb-randr.so.0",
            "libxcb-shm.so.0",
            "libxcb-sync.so.1",
            "libxcb-xfixes.so.0",
            "libxcb.so.1",
            "libXfixes.so.3",
            "libxshmfence.so.1",
            "libXxf86vm.so.1",
        ],
    }

    def package_id(self):
        self.info.settings.rm_safe("build_type")
        self.info.settings.rm_safe("compiler.runtime_type")

    def configure(self):
        if self.settings.os != "Windows":
            raise ConanInvalidConfiguration(f"{self.name} is only supported on Windows")

    def validate(self):
        if self.settings.os != "Windows":
            raise ConanInvalidConfiguration(f"{self.name} is only supported on Windows")

    def validate_build(self):
        if self.settings.build_type != "Release":
            raise ConanInvalidConfiguration(f"{self.name} is built in release mode only.")

    def requirements(self):
        self.requires("llvm/[>=18.0.0]", visible=False)

    def layout(self):
        basic_layout(self, src_folder="src")

    def source(self):
        get(
            self,
            sha256="43d7abcd4aa8049d8fd75538344a374104765e81e17b4a6314cee2c0160e4412",
            url=f"https://mesa.freedesktop.org/archive/mesa-{self.version}.tar.xz",
            strip_root=True,
        )

    def generate(self):
        tc = MesonToolchain(self)
        tc.project_options.update(
            {
                "gallium-drivers": "softpipe,llvmpipe",
                "llvm": "enabled",  # make sure we get the llvmpipe driver, not softpipe
                "shared-llvm": "disabled",
                "platforms": "windows" if self.settings.os == "Windows" else "x11",
                "video-codecs": "",  # no video codecs needed, no patented codecs wanted
                "vulkan-drivers": "",  # no Vulkan drivers on Windows anyway (just to be able to build on Linux too)
                "cpp_rtti": "false",  # on Linux Mesa complains that LLVM was built without RTTI (LLVM_ENABLE_RTTI=ON was not set)
                "zlib": "disabled",  # disable find zlib (used for shader-cache, but not supported on Windows anyway)
                "zstd": "disabled",  # disable find zstd (used for shader-cache, but not supported on Windows anyway)
                "xmlconfig": "disabled",  # disabled on Windows anyway (just to be able to build on Linux too)
                "expat": "disabled",  # disabled on Windows anyway (just to be able to build on Linux too)
                "shader-cache": "disabled",  # disabled on Windows anyway (just to be able to build on Linux too)
            }
        )
        tc.generate()

        # Need to either set llvm-config binary or cmake_config_path built-in option in the configuration .ini file
        # for meson, otherwise llvm isn't found, but unfortunately MesonToolchain doesn't support this (yet):
        llvm_config = self.dependencies["llvm"].cpp_info.bindirs[0] + (
            "\\llvm-config.exe" if self.settings.os == "Windows" else "/llvm-config"
        )
        replace_in_file(
            self,
            tc.native_filename,
            "[binaries]",
            f"[binaries]\nllvm-config = '{llvm_config}'",
        )

    def build(self):
        meson = Meson(self)
        meson.configure()
        meson.build()

    def package(self):
        meson = Meson(self)
        meson.install()

        rmdir(self, os.path.join(self.package_folder, "share"))
        rmdir(self, os.path.join(self.package_folder, "lib", "pkgconfig"))

        copy(
            self, "LICENSE", src=os.path.dirname(self.source_folder), dst=os.path.join(self.package_folder, "licenses")
        )

        # copy ThirdPartyInformation from llvm, because llvm isn't a direct dependency of MeVisLab
        # TODO: no ThirdPartyInformation created yet
        rootpath = self.dependencies["llvm"].package_folder
        copy(
            self,
            "*",
            src=os.path.join(rootpath, "MeVis", "ThirdParty", "ThirdPartyInformation"),
            dst=os.path.join(self.package_folder, "MeVis", "ThirdParty", "ThirdPartyInformation"),
        )

    def package_info(self):
        self.cpp_info.set_property("cpe", "cpe:2.3:a:mesa3d:mesa:*:*:*:*:*:*:*:*")
        # self.cpp_info.set_property("purl", "")  # Official repository is at https://gitlab.freedesktop.org/mesa/
        self.cpp_info.includedirs = []
