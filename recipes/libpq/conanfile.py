import os
from conan import ConanFile
from conan.tools.gnu import PkgConfigDeps
from conan.tools.meson import MesonToolchain
from conan.tools.meson import Meson
from conan.tools.layout import basic_layout
from conan.tools.files import get, rm, rmdir, copy, patch
from conan.tools.microsoft import is_msvc

required_conan_version = ">=2.2.2"


class ConanRecipe(ConanFile):
    name = "libpq"
    version = "17.0"
    homepage = "https://www.postgresql.org/docs/current/static/libpq.html"
    description = "The library used by all the standard PostgreSQL tools."
    license = "PostgreSQL"
    package_type = "shared-library"
    settings = "os", "arch", "compiler", "build_type"
    exports_sources = "patches/*.patch"

    def requirements(self):
        if self.settings.os != "Macos":
            self.requires("openssl/[>=3.0.0]")

    def configure(self):
        self.settings.rm_safe("compiler.libcxx")
        self.settings.rm_safe("compiler.cppstd")

    def layout(self):
        basic_layout(self, src_folder="src")

    def source(self):
        get(
            self,
            sha256="7e276131c0fdd6b62588dbad9b3bb24b8c3498d5009328dba59af16e819109de",
            url=f"https://ftp.postgresql.org/pub/source/v{self.version}/postgresql-{self.version}.tar.bz2",
            strip_root=True,
        )
        patch(self, patch_file="patches/001_debug_suffix.patch")

    def generate(self):
        pc = PkgConfigDeps(self)
        pc.generate()
        tc = MesonToolchain(self)
        tc.project_options["auto_features"] = "disabled"
        tc.project_options["ssl"] = "openssl"
        tc.project_options["rpath"] = "false"
        tc.generate()

    def build(self):
        meson = Meson(self)
        meson.configure()
        meson.build(target="backend")

    def package(self):
        copy(self, "COPYRIGHT", src=self.source_folder, dst=os.path.join(self.package_folder, "licenses"))
        meson = Meson(self)
        meson.install()

        rmdir(self, os.path.join(self.package_folder, "include", "postgresql"))
        rmdir(self, os.path.join(self.package_folder, "lib", "pkgconfig"))
        rmdir(self, os.path.join(self.package_folder, "lib", "postgresql"))
        rmdir(self, os.path.join(self.package_folder, "share"))

        rm(self, "*", os.path.join(self.package_folder, "bin"), excludes=["libpq*.dll", "libpq*.pdb"])
        rm(self, "*", os.path.join(self.package_folder, "lib"), excludes=["libpq*.so", "libpq*.so.*", "libpq*.lib"])

    def package_info(self):
        self.cpp_info.set_property("cpe", "cpe:2.3:a:postgresql:postgresql:*:*:*:*:*:*:*:*")  # there seems to be no cpe that only applies to libpq
        self.cpp_info.set_property("base_purl", "github/postgres/postgres")  # this references the whole postgres db, not just the client libpq
        self.cpp_info.set_property("cmake_find_mode", "both")
        self.cpp_info.set_property("cmake_file_name", "PostgreSQL")
        self.cpp_info.set_property("cmake_target_name", "PostgreSQL::PostgreSQL")
        self.cpp_info.set_property("pkg_config_name", "libpq")

        debug_ext = "_d" if self.settings.build_type == "Debug" else ""
        self.cpp_info.components["pq"].libs = [f"{'lib' if is_msvc(self) else ''}pq{debug_ext}"]

        if self.settings.os != "Macos":
            self.cpp_info.components["pq"].requires.append("openssl::openssl")
        if self.settings.os == "Linux":
            self.cpp_info.components["pq"].system_libs = ["pthread"]
        if self.settings.os == "Windows":
            self.cpp_info.components["pq"].system_libs = ["ws2_32", "secur32", "advapi32", "shell32", "crypt32", "wldap32"]
