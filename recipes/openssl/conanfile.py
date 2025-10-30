"""
Parts of the recipe are taken from the Conan Center Index (https://github.com/conan-io/conan-center-index),
licensed under the MIT License.
"""

import fnmatch
import os
import textwrap

from conan import ConanFile
from conan.errors import ConanInvalidConfiguration
from conan.tools.apple import fix_apple_shared_install_name, is_apple_os
from conan.tools.build import build_jobs
from conan.tools.files import chdir, copy, get, patch, replace_in_file, rmdir, save
from conan.tools.gnu import AutotoolsToolchain
from conan.tools.layout import basic_layout
from conan.tools.microsoft import is_msvc, msvc_runtime_flag, unix_path

required_conan_version = ">=2.2.2"


class OpenSSLConan(ConanFile):
    name = "openssl"
    version = "3.5.4"
    homepage = "https://www.openssl.org"
    license = "Apache-2.0"
    description = "full-strength general purpose cryptography library (including SSL and TLS)"
    settings = "os", "arch", "compiler", "build_type"
    package_type = "shared-library"
    exports_sources = "patches/*.patch"

    mlab_hooks = {"debug_suffix.skip": True}

    @property
    def _settings_build(self):
        return getattr(self, "settings_build", self.settings)

    def configure(self):
        self.settings.rm_safe("compiler.libcxx")
        self.settings.rm_safe("compiler.cppstd")

    def requirements(self):
        self.requires("zlib/[>=1.2.13]")

    def layout(self):
        basic_layout(self, src_folder="src")

    def source(self):
        get(
            self,
            sha256="967311f84955316969bdb1d8d4b983718ef42338639c621ec4c34fddef355e99",
            url=f"https://www.openssl.org/source/openssl-{self.version}.tar.gz",
            destination=self.source_folder,
            strip_root=True,
        )
        patch(self, patch_file="patches/001-masm_multilib_suffix.patch")

    @property
    def _target(self):
        target = f"conan-{self.settings.build_type}-{self.settings.os}-{self.settings.arch}-{self.settings.compiler}-{self.settings.compiler.version}"
        if is_msvc(self):
            target = f"VC-{target}"  # VC- prefix is important as it's checked by Configure
        return target

    @property
    def _ancestor_target(self):
        if self.settings.os == "Windows":
            return "VC-WIN64A-masm"
        elif self.settings.os == "Linux":
            if self.settings.arch == "armv8":
                return "linux-aarch64"
            return "linux-x86_64"
        else:
            raise ConanInvalidConfiguration(f"Unsupported platform ({self.settings.os}).\n")

    def _get_default_openssl_dir(self):
        if self.settings.os == "Linux":
            return "/etc/ssl"
        return os.path.join(self.package_folder, "res")

    @property
    def _configure_args(self):
        openssldir = unix_path(self, self._get_default_openssl_dir())
        args = [
            f'"{self._target}"',
            "shared",
            "threads",
            "no-unit-test",
            "no-tests",
            "PERL=perl",
            "--debug" if self.settings.build_type == "Debug" else "--release",
            '--prefix="/"',
            '--libdir="lib"',
            f'--openssldir="{openssldir}"',
        ]

        zlib_info = self.dependencies["zlib"].cpp_info.aggregated_components()
        include_path = zlib_info.includedirs[0]
        if self.settings.os == "Windows":
            lib_path = f"{zlib_info.libdirs[0]}/{zlib_info.libs[0]}.lib"
        else:
            # Just path, linux will find the right file
            lib_path = zlib_info.libdirs[0]

        args.extend(["zlib", f'--with-zlib-include="{include_path}"', f'--with-zlib-lib="{lib_path}"'])
        return args

    def generate(self):
        tc = AutotoolsToolchain(self)
        env = tc.environment()
        env.define_path("PERL", "perl")
        self._create_targets(tc.cflags, tc.cxxflags, tc.defines, tc.ldflags)
        tc.generate(env)

    def _create_targets(self, cflags, cxxflags, defines, ldflags):
        cflags = " ".join(cflags)
        cxxflags = " ".join(cxxflags)
        defines = " ".join(defines)
        defines = f'defines => add("{defines}"),' if defines else ""
        lflags = " ".join(ldflags)
        targets = "my %targets"
        config = textwrap.dedent(
            f"""\
            {targets} = (
                "{self._target}" => {{
                    inherit_from => [ "{self._ancestor_target}" ],
                    cflags => add("{cflags}"),
                    cxxflags => add("{cxxflags}"),
                    {defines}
                    lflags => add("{lflags}"),
                }},
            );
        """
        )

        self.output.info(f"using target: {self._target} -> {self._ancestor_target}")
        self.output.info(config)

        save(self, os.path.join(self.source_folder, "Configurations", "20-conan.conf"), config)

    @property
    def _make_program(self):
        return "nmake" if is_msvc(self) else "make"

    def _run_make(self, targets=None, parallel=True, install=False):
        command = [self._make_program]
        if install:
            command.append(f"DESTDIR={self.package_folder}")
        if targets:
            command.extend(targets)
        if not is_msvc(self):
            command.append(("-j%s" % build_jobs(self)) if parallel else "-j1")
        self.run(" ".join(command), env="conanbuild")

    def _make(self):
        with chdir(self, self.source_folder):
            args = " ".join(self._configure_args)

            if is_msvc(self):
                self._replace_runtime_in_file("Configurations/10-main.conf")
            if self.settings.build_type == "Debug":
                replace_in_file(self, "Configurations/00-base-templates.conf", '"-lz"', '"-lz_d"')

            self.run(f"perl ./Configure {args}", env="conanbuild")
            if self.settings.os == "Windows":
                # replace backslashes in paths with forward slashes
                replace_in_file(self, "Makefile", "INSTALLTOP_dir=\\", "INSTALLTOP_dir=\\\\")
                mkinstallvars_pl = os.path.join(self.source_folder, "util", "mkinstallvars.pl")
                replace_in_file(
                    self, mkinstallvars_pl, "push @{$values{$k}}, $v;", """$v =~ s|\\\\|/|g; push @{$values{$k}}, $v;"""
                )
                replace_in_file(
                    self, mkinstallvars_pl, "$values{$k} = $v;", """$v->[0] =~ s|\\\\|/|g; $values{$k} = $v;"""
                )
            self._run_make()

    def _replace_runtime_in_file(self, filename):
        runtime = msvc_runtime_flag(self)
        for e in ["MDd", "MTd", "MD", "MT"]:
            replace_in_file(self, filename, f"/{e} ", f"/{runtime} ", strict=False)
            replace_in_file(self, filename, f'/{e}"', f'/{runtime}"', strict=False)

    def _make_install(self):
        with chdir(self, self.source_folder):
            self._run_make(targets=["install_sw"], parallel=False, install=True)

    def build(self):
        self._make()
        self.run(f"perl {self.source_folder}/configdata.pm --dump")

    def package(self):
        copy(self, "*LICENSE*", src=self.source_folder, dst=os.path.join(self.package_folder, "licenses"))

        self._make_install()
        if is_apple_os(self):
            fix_apple_shared_install_name(self)

        for root, _, files in os.walk(self.package_folder):
            for filename in files:
                if fnmatch.fnmatch(filename, "*.pdb") or fnmatch.fnmatch(filename, "*.cmake"):
                    os.unlink(os.path.join(self.package_folder, root, filename))
        # if is_msvc(self):
        #    if self.settings.build_type == "Debug":
        #        with chdir(self, os.path.join(self.package_folder, "lib")):
        #            rename(self, "libssl.lib", "libssld.lib")
        #            rename(self, "libcrypto.lib", "libcryptod.lib")

        libdir = os.path.join(self.package_folder, "lib")
        for file in os.listdir(libdir):
            if file.endswith(".a"):
                os.unlink(os.path.join(libdir, file))

        if self.settings.os == "Linux":
            self.run("patchelf --set-rpath '$ORIGIN/../lib' " + os.path.join(self.package_folder, "lib", "libssl.so.3"))

        if True:  # fips support?
            provdir = os.path.join(self.source_folder, "providers")
            modules_dir = os.path.join(self.package_folder, "lib", "ossl-modules")
            if self.settings.os == "Macos":
                copy(self, "fips.dylib", src=provdir, dst=modules_dir)
            elif self.settings.os == "Windows":
                copy(self, "fips.dll", src=provdir, dst=modules_dir)
            else:
                copy(self, "fips.so", src=provdir, dst=modules_dir)

        rmdir(self, os.path.join(self.package_folder, "lib", "pkgconfig"))

        self._create_cmake_module_variables(os.path.join(self.package_folder, self._module_file_rel_path))

    def _create_cmake_module_variables(self, module_file):
        content = textwrap.dedent(
            """\
            set(OPENSSL_FOUND TRUE)
            if(DEFINED OpenSSL_INCLUDE_DIR)
                set(OPENSSL_INCLUDE_DIR ${OpenSSL_INCLUDE_DIR})
            endif()
            if(DEFINED OpenSSL_Crypto_LIBS)
                set(OPENSSL_CRYPTO_LIBRARY ${OpenSSL_Crypto_LIBS})
                set(OPENSSL_CRYPTO_LIBRARIES ${OpenSSL_Crypto_LIBS}
                                             ${OpenSSL_Crypto_DEPENDENCIES}
                                             ${OpenSSL_Crypto_FRAMEWORKS}
                                             ${OpenSSL_Crypto_SYSTEM_LIBS})
            elseif(DEFINED openssl_OpenSSL_Crypto_LIBS_%(config)s)
                set(OPENSSL_CRYPTO_LIBRARY ${openssl_OpenSSL_Crypto_LIBS_%(config)s})
                set(OPENSSL_CRYPTO_LIBRARIES ${openssl_OpenSSL_Crypto_LIBS_%(config)s}
                                             ${openssl_OpenSSL_Crypto_DEPENDENCIES_%(config)s}
                                             ${openssl_OpenSSL_Crypto_FRAMEWORKS_%(config)s}
                                             ${openssl_OpenSSL_Crypto_SYSTEM_LIBS_%(config)s})
            endif()
            if(DEFINED OpenSSL_SSL_LIBS)
                set(OPENSSL_SSL_LIBRARY ${OpenSSL_SSL_LIBS})
                set(OPENSSL_SSL_LIBRARIES ${OpenSSL_SSL_LIBS}
                                          ${OpenSSL_SSL_DEPENDENCIES}
                                          ${OpenSSL_SSL_FRAMEWORKS}
                                          ${OpenSSL_SSL_SYSTEM_LIBS})
            elseif(DEFINED openssl_OpenSSL_SSL_LIBS_%(config)s)
                set(OPENSSL_SSL_LIBRARY ${openssl_OpenSSL_SSL_LIBS_%(config)s})
                set(OPENSSL_SSL_LIBRARIES ${openssl_OpenSSL_SSL_LIBS_%(config)s}
                                          ${openssl_OpenSSL_SSL_DEPENDENCIES_%(config)s}
                                          ${openssl_OpenSSL_SSL_FRAMEWORKS_%(config)s}
                                          ${openssl_OpenSSL_SSL_SYSTEM_LIBS_%(config)s})
            endif()
            if(DEFINED OpenSSL_LIBRARIES)
                set(OPENSSL_LIBRARIES ${OpenSSL_LIBRARIES})
            endif()
            if(DEFINED OpenSSL_VERSION)
                set(OPENSSL_VERSION ${OpenSSL_VERSION})
            endif()
        """
            % {"config": str(self.settings.build_type).upper()}
        )
        save(self, module_file, content)

    @property
    def _module_subfolder(self):
        return os.path.join("lib", "cmake")

    @property
    def _module_file_rel_path(self):
        return os.path.join(self._module_subfolder, "openssl-variables.cmake")

    def package_info(self):
        self.cpp_info.set_property("cpe", "cpe:2.3:a:openssl:openssl:*:*:*:*:*:*:*:*")
        self.cpp_info.set_property("purl", f"pkg:github/openssl/openssl@openssl-{self.version}")
        self.cpp_info.set_property("cmake_find_mode", "both")
        self.cpp_info.set_property("cmake_file_name", "OpenSSL")
        # backwards compatibility with our old Conan 1 build:
        self.cpp_info.set_property("cmake_module_file_name", "openssl")
        self.cpp_info.set_property("pkg_config_name", "openssl")
        self.cpp_info.set_property("cmake_build_modules", [self._module_file_rel_path])
        self.cpp_info.builddirs.append(self._module_subfolder)

        if is_msvc(self):
            # libsuffix = "d" if self.settings.build_type == "Debug" else ""
            libsuffix = ""
            self.cpp_info.components["ssl"].libs = ["libssl" + libsuffix]
            self.cpp_info.components["crypto"].libs = ["libcrypto" + libsuffix]
        else:
            self.cpp_info.components["ssl"].libs = ["ssl"]
            self.cpp_info.components["crypto"].libs = ["crypto"]

        self.cpp_info.components["ssl"].requires = ["crypto"]
        self.cpp_info.components["crypto"].requires.append("zlib::zlib")

        if self.settings.os == "Windows":
            self.cpp_info.components["crypto"].system_libs.extend(["crypt32", "ws2_32", "advapi32", "user32", "bcrypt"])
        elif self.settings.os == "Linux":
            self.cpp_info.components["crypto"].system_libs.extend(["dl", "rt", "pthread"])
            self.cpp_info.components["ssl"].system_libs.extend(["dl", "pthread"])

        self.cpp_info.components["crypto"].set_property("cmake_target_name", "OpenSSL::Crypto")
        self.cpp_info.components["crypto"].set_property("pkg_config_name", "libcrypto")
        self.cpp_info.components["ssl"].set_property("cmake_target_name", "OpenSSL::SSL")
        self.cpp_info.components["ssl"].set_property("pkg_config_name", "libssl")

        openssl_modules_dir = os.path.join(self.package_folder, "lib", "ossl-modules")
        self.runenv_info.define_path("OPENSSL_MODULES", openssl_modules_dir)
