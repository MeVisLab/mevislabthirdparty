import os
import shutil

from conan import ConanFile
from conan.tools.apple import is_apple_os
from conan.tools.env import VirtualBuildEnv
from conan.tools.files import copy, chdir, get, patch, rmdir
from conan.tools.gnu import Autotools, AutotoolsToolchain
from conan.tools.layout import basic_layout
from conan.tools.microsoft import is_msvc, MSBuild, MSBuildToolchain

required_conan_version = ">=2.2.2"


class MeVisMSBuild(MSBuild):
    # We need a helper class, so that we can set extra properties.
    # This might become obsolete when the issue is fixed, that the
    # output of MSBuildToolchain is ignored without patching:
    # https://github.com/conan-io/conan/pull/12817

    def __init__(self, conanfile):
        super().__init__(conanfile)
        self.properties = {}

    def command(self, sln, targets=None):
        cmd = super().command(sln, targets)
        for k, v in self.properties.items():
            cmd += f' /p:{k}="{v}"'
        return cmd


class ConanRecipe(ConanFile):
    name = "icu"
    version = "74.1"
    homepage = "https://icu.unicode.org/"
    description = "Unicode support, software internationalization, and software globalization"
    license = "Unicode-3.0"
    package_type = "shared-library"
    settings = "os", "arch", "compiler", "build_type"
    exports_sources = "patches/*.patch"

    mlab_hooks = {
        "debug_suffix.exclude": ['icu*.dll', 'icu*.lib', 'libicu*.so*', 'testplugd.dll'],  # TODO testplug needed?
        "split_debug.exclude": ["lib/libicudata*.so.*"]                                    # libicudata can't be stripped
    }

    def layout(self):
        basic_layout(self, src_folder="src")

    def source(self):
        get(self,
            sha256="86ce8e60681972e60e4dcb2490c697463fcec60dd400a5f9bffba26d0b52b8d0",
            url=f"https://github.com/unicode-org/icu/releases/download/release-{self.version.replace('.', '-')}/icu4c-{self.version.replace('.', '_')}-src.tgz",
            strip_root=True)
        patch(self, patch_file="patches/001-disable_renaming_by_default.patch")

    def generate(self):
        env = VirtualBuildEnv(self)
        env.generate()

        if is_msvc(self):
            tc = MSBuildToolchain(self)
            tc.configuration = "Debug" if self.settings.build_type == "Debug" else "Release"
            # Note: The .props output of MSBuildToolchain is currently ignored
            tc.properties['SkipUWP'] = "true"
            tc.generate()
        else:
            tc = AutotoolsToolchain(self)
            tc.extra_cflags.append("-FS")
            tc.extra_cxxflags.append("-FS")

            if is_apple_os(self):
                tc.extra_defines.append("_DARWIN_C_SOURCE")

            tc.configure_args.extend([
                "--with-data-packaging=library",
                "--with-library-bits=64",
                # "--enable-dyload",
                # "--enable-icuio",
                "--disable-samples",
                "--disable-tests",
                "--disable-renaming",
                "--disable-layout",
                "--disable-layoutex",
                "--disable-extras",
                "--with-library-bits=64"
            ])

            if self.settings.build_type == "Debug":
                tc.configure_args.extend(["--disable-release", "--enable-debug", "--with-library-suffix=d"])

            tc.configure_args.extend(["--disable-static", "--enable-shared"])
            tc.generate()

    def build(self):
        if is_msvc(self):
            proj_dir = self.source_path / 'source' / 'allinone'
            msbuild = MeVisMSBuild(self)
            msbuild.build_type = "Debug" if self.settings.build_type == "Debug" else "Release"
            msbuild.properties['SkipUWP'] = 'true'
            msbuild.build(proj_dir / "allinone.sln")
        else:
            autotools = Autotools(self)
            autotools.configure(build_script_folder=os.path.join(self.source_folder, "source"))
            autotools.make()

    def package(self):
        copy(self, "LICENSE", src=self.source_path, dst=self.package_path / "licenses")
        if is_msvc(self):
            # Note: build results are located in the source folder
            copy(self, pattern="*",
                 src=self.source_path / "include",
                 dst=self.package_path / "include")
            copy(self, pattern="*.lib",
                 src=self.source_path / "lib64",
                 dst=self.package_path / "lib")
            copy(self, pattern="*.pdb",
                 src=self.source_path / "lib64",
                 dst=self.package_path / "bin")
            copy(self, pattern="*.exe",
                 src=self.source_path / "bin64",
                 dst=self.package_path / "bin")
            copy(self, pattern="*.dll",
                 src=self.source_path / "bin64",
                 dst=self.package_path / "bin")
        else:
            autotools = Autotools(self)
            autotools.install()

        # Copy some files required for cross-compiling
        config_dir = self.package_path / "config"
        copy(self, "icucross.mk", src=self.build_path / "config", dst=config_dir)
        copy(self, "icucross.inc", src=self.build_path / "config", dst=config_dir)

        suffix = "d" if self.settings.build_type == "Debug" else ""
        rmdir(self, self.package_path / "lib" / f"icu{suffix}")
        rmdir(self, self.package_path / "lib" / "man")
        rmdir(self, self.package_path / "lib" / "pkgconfig")
        rmdir(self, self.package_path / "share")

        if self.settings.os == "Linux":
            # change rpath of binaries
            patchelf = shutil.which("patchelf")
            with chdir(self, self.package_path / "bin"):
                for binary in ['derb', 'genbrk', 'gencfu', 'gencnval', 'gendict', 'genrb', 'icuinfo', 'makeconv', 'pkgdata']:
                    self.run(f"{patchelf} --set-rpath '$ORIGIN/../lib' {binary}")
            for lib in (self.package_path / "lib").glob("*.so"):
                self.run(f"{patchelf} --set-rpath '$ORIGIN/../lib' {lib}")

    def package_info(self):
        self.cpp_info.set_property("cmake_find_mode", "both")
        self.cpp_info.set_property("cmake_file_name", "ICU")
        self.cpp_info.set_property("cmake_target_name", "ICU::ICU")

        suffix = "d" if self.settings.build_type == "Debug" else ""

        # icudata
        self.cpp_info.components["icu-data"].set_property("cmake_target_name", "ICU::data")
        icudata_libname = "icudt" if self.settings.os == "Windows" else f"icudata{suffix}"
        self.cpp_info.components["icu-data"].libs = [icudata_libname]

        # Alias of data CMake component
        self.cpp_info.components["icu-data-alias"].set_property("cmake_target_name", "ICU::dt")
        self.cpp_info.components["icu-data-alias"].requires = ["icu-data"]

        # icuuc
        self.cpp_info.components["icu-uc"].set_property("cmake_target_name", "ICU::uc")
        self.cpp_info.components["icu-uc"].set_property("pkg_config_name", "icu-uc")
        self.cpp_info.components["icu-uc"].libs = [f"icuuc{suffix}"]
        self.cpp_info.components["icu-uc"].requires = ["icu-data"]
        if self.settings.os in ["Linux"]:
            self.cpp_info.components["icu-uc"].system_libs = ["m", "pthread", "dl"]
        elif self.settings.os == "Windows":
            self.cpp_info.components["icu-uc"].system_libs = ["advapi32"]

        # icui18n
        self.cpp_info.components["icu-i18n"].set_property("cmake_target_name", "ICU::i18n")
        self.cpp_info.components["icu-i18n"].set_property("pkg_config_name", "icu-i18n")
        icui18n_libname = "icuin" if self.settings.os == "Windows" else "icui18n"
        self.cpp_info.components["icu-i18n"].libs = [f"{icui18n_libname}{suffix}"]
        self.cpp_info.components["icu-i18n"].requires = ["icu-uc"]
        if self.settings.os in ["Linux"]:
            self.cpp_info.components["icu-i18n"].system_libs = ["m"]

        # Alias of i18n CMake component
        self.cpp_info.components["icu-i18n-alias"].set_property("cmake_target_name", "ICU::in")
        self.cpp_info.components["icu-i18n-alias"].requires = ["icu-i18n"]

        # icuio
        self.cpp_info.components["icu-io"].set_property("cmake_target_name", "ICU::io")
        self.cpp_info.components["icu-io"].set_property("pkg_config_name", "icu-io")
        self.cpp_info.components["icu-io"].libs = [f"icuio{suffix}"]
        self.cpp_info.components["icu-io"].requires = ["icu-i18n", "icu-uc"]
