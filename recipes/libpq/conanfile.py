from conan import ConanFile
from conan.tools.apple import fix_apple_shared_install_name
from conan.tools.env import Environment, VirtualBuildEnv, VirtualRunEnv
from conan.tools.files import chdir, copy, get, replace_in_file, rm, rmdir
from conan.tools.gnu import Autotools, AutotoolsToolchain, AutotoolsDeps
from conan.tools.layout import basic_layout
from conan.tools.microsoft import is_msvc, unix_path, VCVars, MSBuild

required_conan_version = ">=2.2.2"


class ConanRecipe(ConanFile):
    name = "libpq"
    version = "16.4"
    homepage = "https://www.postgresql.org/docs/current/static/libpq.html"
    description = "The library used by all the standard PostgreSQL tools."
    license = "PostgreSQL"
    package_type = "shared-library"
    settings = "os", "arch", "compiler", "build_type"

    def requirements(self):
        if self.settings.os != "Macos":
            self.requires("openssl/[>=3.0.0]")

    def configure(self):
        self.settings.rm_safe("compiler.libcxx")
        self.settings.rm_safe("compiler.cppstd")

    def source(self):
        get(
            self,
            sha256="971766d645aa73e93b9ef4e3be44201b4f45b5477095b049125403f9f3386d6f",
            url=f"https://ftp.postgresql.org/pub/source/v{self.version}/postgresql-{self.version}.tar.bz2",
            strip_root=True,
        )

    def layout(self):
        basic_layout(self, src_folder="src")

    def generate(self):
        env = VirtualBuildEnv(self)
        env.generate()

        if is_msvc(self):
            vcvars = VCVars(self)
            vcvars.generate()
            config = "DEBUG" if self.settings.build_type == "Debug" else "RELEASE"
            env = Environment()
            env.define("CONFIG", config)
            env.vars(self).save_script("conanbuild_msvc")
        else:
            env = VirtualRunEnv(self)
            env.generate(scope="build")

            ad = AutotoolsDeps(self)
            ad.generate()

            if self.settings.build_type == "Debug":
                replace_in_file(self, self.source_path / "src" / "interfaces" / "libpq" / "Makefile", "NAME= pq", "NAME= pq_d")
            tc = AutotoolsToolchain(self)
            tc.configure_args.append("--without-readline")
            tc.configure_args.append("--without-zlib")
            tc.configure_args.append("--without-icu")

            if self.settings.os != "Macos":
                tc.configure_args.append("--with-openssl")
            if self.settings.build_type == "Debug":
                tc.configure_args.append("--enable-debug")
            tc.make_args.append(f"DESTDIR={unix_path(self, self.package_folder)}")
            tc.generate()

    def _build_windows(self):
        # fix openssl
        tools_path = self.source_path / "src" / "tools" / "msvc"
        solution_pm = tools_path / "Solution.pm"
        openssl = self.dependencies["openssl"]
        openssl_components = openssl.cpp_info.components
        for ssl in [r"VC\libssl32", r"VC\libssl64", "libssl"]:
            replace_in_file(self, solution_pm, ssl + ".lib", openssl_components["ssl"].libs[0] + ".lib")
        for crypto in [r"VC\libcrypto32", r"VC\libcrypto64", "libcrypto"]:
            replace_in_file(self, solution_pm, crypto + ".lib", openssl_components["crypto"].libs[0] + ".lib")

        config_default_pl = tools_path / "config_default.pl"
        replace_in_file(self, config_default_pl, "openssl => undef,", "openssl => '%s'," % openssl.package_folder.replace("\\", "/"))

        if self.settings.build_type == "Debug":
            # adapt project and target names
            replace_in_file(self, tools_path / "Project.pm", "name => $name", "name => $name . '_d'")
            # adapt DLL name in generated libpqdll.def
            replace_in_file(self, solution_pm, '"LIBPQ"', '"LIBPQ_D"')

        with chdir(self, self.source_path / "src" / "tools" / "msvc"):
            env = Environment()
            env.append("LC_ALL", "C")
            env.append("LANG", "C")
            with env.vars(self).apply():
                self.run("perl mkvcbuild.pl")

        with chdir(self, self.source_folder):
            msbuild = MSBuild(self)
            debug_ext = "_d" if self.settings.build_type == "Debug" else ""
            msbuild.build(f"libpq{debug_ext}.vcxproj")

    def build(self):
        if is_msvc(self):
            self._build_windows()
        else:
            autotools = Autotools(self)
            with chdir(self, self.source_path):
                autotools.configure()
            with chdir(self, self.source_path / "src" / "backend"):
                autotools.make(target="generated-headers")
            with chdir(self, self.source_path / "src" / "common"):
                autotools.make()
            with chdir(self, self.source_path / "src" / "include"):
                autotools.make()
            with chdir(self, self.source_path / "src" / "interfaces" / "libpq"):
                autotools.make()
            with chdir(self, self.source_path / "src" / "port"):
                autotools.make()
            with chdir(self, self.source_path / "src" / "bin" / "pg_config"):
                autotools.make()
            for lib in (self.source_path / "src" / "interfaces" / "libpq").glob("*.so.*"):
                self.run(f"patchelf --set-rpath '$ORIGIN/../lib' {lib}")

    def package(self):
        copy(self, "COPYRIGHT", src=self.source_path, dst=self.package_path / "licenses")
        if is_msvc(self):
            for pattern in ["*postgres_ext.h", "*pg_config.h", "*pg_config_ext.h", "*libpq-fe.h", "*libpq-events.h"]:
                copy(self, pattern=pattern, src=self.source_path, dst=self.package_path / "include", keep_path=False)
            copy(
                self,
                pattern="*.h",
                src=self.source_path / "src" / "include" / "libpq",
                dst=self.package_path / "include" / "libpq",
                keep_path=False,
            )
            for pattern in ["*genbki.h", "*pg_type.h"]:
                copy(self, pattern=pattern, src=self.source_path, dst=self.package_path / "include" / "catalog", keep_path=False)
            debug_ext = "_d" if self.settings.build_type == "Debug" else ""
            copy(self, pattern=f"*libpq{debug_ext}.dll", src=self.source_path, dst=self.package_path / "bin", keep_path=False)
            copy(self, pattern=f"*libpq{debug_ext}.pdb", src=self.source_path, dst=self.package_path / "bin", keep_path=False)
            copy(self, pattern=f"*libpq{debug_ext}.lib", src=self.source_path, dst=self.package_path / "lib", keep_path=False)
        else:
            autotools = Autotools(self)
            with chdir(self, self.source_path / "src" / "common"):
                autotools.install()
            with chdir(self, self.source_path / "src" / "include"):
                autotools.install()
            with chdir(self, self.source_path / "src" / "interfaces" / "libpq"):
                autotools.install()
            with chdir(self, self.source_path / "src" / "port"):
                autotools.install()
            with chdir(self, self.source_path / "src" / "bin" / "pg_config"):
                autotools.install()
            copy(self, "*.h", src=self.build_path / "src" / "include" / "catalog", dst=self.package_path / "include" / "catalog")
            rmdir(self, self.package_path / "share")
            rmdir(self, self.package_path / "lib" / "pkgconfig")
            rmdir(self, self.package_path / "include" / "postgresql" / "server")
            rm(self, "*.a", self.package_path / "lib")
            fix_apple_shared_install_name(self)
        copy(self, "*.h", src=self.build_path / "src" / "backend" / "catalog", dst=self.package_path / "include" / "catalog")

    def package_info(self):
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
