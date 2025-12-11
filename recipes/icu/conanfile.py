import os
import shutil
from pathlib import Path

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
    version = "78.1"
    homepage = "https://icu.unicode.org/"
    description = "Unicode support, software internationalization, and software globalization"
    license = "Unicode-3.0"
    package_type = "shared-library"
    settings = "os", "arch", "compiler", "build_type"
    exports_sources = "patches/*.patch"

    mlab_hooks = {
        "debug_suffix.exclude": ["icu*.dll", "icu*.lib", "libicu*.so*", "testplugd.dll"],  # TODO testplug needed?
        "split_debug.exclude": ["lib/libicudata*.so.*"],  # libicudata can't be stripped
    }

    def layout(self):
        basic_layout(self, src_folder="src")

    def source(self):
        get(
            self,
            sha256="6217f58ca39b23127605cfc6c7e0d3475fe4b0d63157011383d716cb41617886",
            url=f"https://github.com/unicode-org/icu/releases/download/release-{self.version}/icu4c-{self.version}-sources.tgz",
            strip_root=True,
        )
        patch(self, patch_file="patches/001-disable_renaming_by_default.patch")

    def generate(self):
        env = VirtualBuildEnv(self)
        env.generate()

        if is_msvc(self):
            tc = MSBuildToolchain(self)
            tc.configuration = "Debug" if self.settings.build_type == "Debug" else "Release"
            # Note: The .props output of MSBuildToolchain is currently ignored
            tc.properties["SkipUWP"] = "true"
            tc.generate()
        else:
            tc = AutotoolsToolchain(self)
            tc.extra_cflags.append("-FS")
            tc.extra_cxxflags.append("-FS")

            if is_apple_os(self):
                tc.extra_defines.append("_DARWIN_C_SOURCE")

            tc.configure_args.extend(
                [
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
                    "--with-library-bits=64",
                ]
            )

            if self.settings.build_type == "Debug":
                tc.configure_args.extend(["--disable-release", "--enable-debug", "--with-library-suffix=d"])

            tc.configure_args.extend(["--disable-static", "--enable-shared"])
            tc.generate()

    def build(self):
        proj_dir = os.path.join(self.source_folder, "source")
        if is_msvc(self):
            msbuild = MeVisMSBuild(self)
            msbuild.build_type = "Debug" if self.settings.build_type == "Debug" else "Release"
            msbuild.properties["SkipUWP"] = "true"
            msbuild.build(os.path.join(proj_dir, "allinone", "allinone.sln"))
        else:
            autotools = Autotools(self)
            autotools.configure(build_script_folder=proj_dir)
            autotools.make()

    def package(self):
        copy(self, "LICENSE", src=self.source_folder, dst=os.path.join(self.package_folder, "licenses"))
        if is_msvc(self):
            # Note: build results are located in the source folder
            copy(
                self,
                pattern="*",
                src=os.path.join(self.source_folder, "include"),
                dst=os.path.join(self.package_folder, "include"),
            )
            copy(
                self,
                pattern="*.lib",
                src=os.path.join(self.source_folder, "lib64"),
                dst=os.path.join(self.package_folder, "lib"),
            )
            copy(
                self,
                pattern="*.pdb",
                src=os.path.join(self.source_folder, "lib64"),
                dst=os.path.join(self.package_folder, "bin"),
            )
            copy(
                self,
                pattern="*.exe",
                src=os.path.join(self.source_folder, "bin64"),
                dst=os.path.join(self.package_folder, "bin"),
            )
            copy(
                self,
                pattern="*.dll",
                src=os.path.join(self.source_folder, "bin64"),
                dst=os.path.join(self.package_folder, "bin"),
            )
        else:
            autotools = Autotools(self)
            autotools.install()

        # Copy some files required for cross-compiling
        copy(
            self,
            "icucross.mk",
            src=os.path.join(self.build_folder, "config"),
            dst=os.path.join(self.package_folder, "config"),
        )
        copy(
            self,
            "icucross.inc",
            src=os.path.join(self.build_folder, "config"),
            dst=os.path.join(self.package_folder, "config"),
        )

        suffix = "d" if self.settings.build_type == "Debug" else ""
        rmdir(self, os.path.join(self.package_folder, "lib", f"icu{suffix}"))
        rmdir(self, os.path.join(self.package_folder, "lib", "man"))
        rmdir(self, os.path.join(self.package_folder, "lib", "pkgconfig"))
        rmdir(self, os.path.join(self.package_folder, "share"))

        if self.settings.os == "Linux":
            # change rpath of binaries
            patchelf = shutil.which("patchelf")
            with chdir(self, os.path.join(self.package_folder, "bin")):
                for binary in [
                    "derb",
                    "genbrk",
                    "gencfu",
                    "gencnval",
                    "gendict",
                    "genrb",
                    "icuinfo",
                    "makeconv",
                    "pkgdata",
                ]:
                    self.run(f"{patchelf} --set-rpath '$ORIGIN/../lib' {binary}")
            for lib in Path(self.package_folder, "lib").glob("*.so"):
                self.run(f"{patchelf} --set-rpath '$ORIGIN/../lib' {lib}")

    def package_info(self):
        self.cpp_info.set_property(
            "cpe", "cpe:2.3:a:icu-project:international_components_for_unicode:*:*:*:*:*:c\\/c\\+\\+:*:*"
        )
        self.cpp_info.set_property("purl", f"pkg:github/unicode-org/icu@release-{self.version.replace('.', '-')}")
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
