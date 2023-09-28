# -*- coding: utf-8 -*-
import os

from conans import AutoToolsBuildEnvironment
from conans import ConanFile
from conans import tools


class ConanRecipe(ConanFile):
    python_requires = 'common/1.0.0@mevislab/stable'
    python_requires_extend = 'common.CommonRecipe'

    def build_requirements(self):
        channel = "@{0}/{1}".format(self.user, self.channel)
        packages = None

        if self.settings.compiler == "Visual Studio":
            self.build_requires("strawberryperl_installer/[>=5.30]" + channel)
            self.build_requires("nasm_installer/[>=2.14]" + channel)
        elif self.settings.os == "Linux":
            if tools.os_info.with_apt:
                packages = ['libfindbin-libs-perl']

        if packages:
            installer = tools.SystemPackageTool()
            installer.install(" ".join(packages))

    def requirements(self):
        channel = "@{0}/{1}".format(self.user, self.channel)
        self.requires("zlib/[>=1.2.11]" + channel, private=False)

    def build(self):
        def _get_flags():
            if self.settings.os != "Windows":
                env_build = AutoToolsBuildEnvironment(self)
                extra_flags = ' '.join(env_build.flags)
                extra_flags += ' --prefix="/" --openssldir="/" --libdir="/lib"'

                if self.settings.build_type == "Debug":
                    extra_flags += " -O0"
                    if self.settings.compiler in ["apple-clang", "clang", "gcc"]:
                        extra_flags += " -g3 -fno-omit-frame-pointer -fno-inline-functions"
                    if self.settings.os in ["Linux"]:
                        extra_flags += " no-asm"
            else:
                extra_flags = "--debug" if self.settings.build_type == "Debug" else "--release"

            extra_flags += " shared"
            extra_flags += " threads"
            extra_flags += ' --with-zlib-include="%s"' % self.deps_cpp_info["zlib"].include_paths[0]
            if self.settings.os == "Windows":
                extra_flags += '--with-zlib-lib="%s/%s.lib"' % (
                    self.deps_cpp_info["zlib"].lib_paths[0], self.deps_cpp_info["zlib"].libs[0]
                )
            else:
                extra_flags += '--with-zlib-lib="%s"' % self.deps_cpp_info["zlib"].lib_paths[0]

            return extra_flags

        def _get_target():
            target = ""
            if self.settings.os == "Windows" and self.settings.compiler == "Visual Studio":
                if self.settings.arch == "x86":
                    target = "VC-WIN32"
                elif self.settings.arch == "x86_64":
                    target = "VC-WIN64A-masm"
            elif self.settings.os == "Linux":
                if self.settings.arch == "x86":
                    target = "linux-x86"
                elif self.settings.arch == "x86_64":
                    target = "linux-x86_64"

                if not target:
                    raise Exception("Unsupported arch '%s' for Linux" % self.settings.arch)

                if self.settings.compiler == "clang":
                    target += "-clang"
            elif self.settings.os == "Macos":
                if self.settings.arch == "x86":
                    target = "darwin-i386-cc"
                elif self.settings.arch == "x86_64":
                    target = "darwin64-x86_64-cc"
                elif self.settings.arch == "armv8":
                    target = "darwin64-arm64-cc"
            else:
                raise Exception("Unsupported operating system: %s" % self.settings.os)

            if not target:
                raise Exception("Unsupported arch '%s' for %s" % (self.settings.arch, self.settings.os))

            return target

        if self.settings.os in ["Linux", "Macos"]:
            with tools.chdir("sources"):
                self.run("./Configure %s %s" % (_get_target(), _get_flags()), output=True)
                self.run("make depend", output=True)

            if self.settings.os == "Macos":
                tools.replace_in_file("sources/Makefile", '-install_name $(libdir)/', '-install_name ', strict=self.in_local_cache)

            with tools.chdir("sources"):
                self.run("make", output=True)
                # 'make install' would also create the documentation, which takes quite a long time
                # and we don't want to ship it anyway. Therefore, 'make install_sw' should be enough.
                self.run("make install_sw DESTDIR=%s" % self.package_folder, output=True)
        elif self.settings.compiler == "Visual Studio":
            for e in ("MDd", "MTd", "MD", "MT"):
                tools.replace_in_file(os.path.join("sources", "Configurations", "10-main.conf"), f"/{e} ",
                                      f"/{self.settings.compiler.runtime} ", strict=False)
                tools.replace_in_file(os.path.join("sources", "Configurations", "10-main.conf"), f"/{e}\"",
                                      f"/{self.settings.compiler.runtime}\"", strict=False)

            with tools.vcvars(self.settings, filter_known_paths=False):
                with tools.environment_append({"LC_ALL": "C", "LANG": "C"}):
                    with tools.chdir("sources"):
                        self.run(
                            f"perl Configure {_get_target()} --prefix={self.source_folder}/binaries {_get_flags()}",
                            output=True)
                        self.run("nmake", output=True)
        else:
            raise Exception(f"Unsupported operating system: {self.settings.os}")

    def package(self):
        self.copy(src="sources", pattern="*LICENSE", dst="licenses", keep_path=False)
        if self.settings.os == "Windows" and self.settings.compiler == "Visual Studio":
            self.copy(pattern="*/libcrypto*.lib", dst="lib", keep_path=False, excludes="*_static*.lib")
            self.copy(pattern="*/libssl*.lib", dst="lib", keep_path=False, excludes="*_static*.lib")
            self.copy(pattern="*/libcrypto*.dll", dst="bin", keep_path=False)
            self.copy(pattern="*/libcrypto*.pdb", dst="bin", keep_path=False)
            self.copy(pattern="*/libssl*.dll", dst="bin", keep_path=False)
            self.copy(pattern="*/libssl*.pdb", dst="bin", keep_path=False)
            self.copy(pattern="*/openssl.exe", dst="bin", keep_path=False)
            self.copy(pattern="*.h", dst="include/openssl/", src="sources/include/", keep_path=False)

        if not tools.os_info.is_windows:
            os.remove(os.path.join(self.package_folder, "bin", "c_rehash"))
            os.remove(os.path.join(self.package_folder, "lib", "libssl.a"))
            os.remove(os.path.join(self.package_folder, "lib", "libcrypto.a"))

        tools.rmdir(os.path.join(self.package_folder, "lib", "engines-3.0"))
        tools.rmdir(os.path.join(self.package_folder, "lib", "pkgconfig"))
        tools.rmdir(os.path.join(self.package_folder, "share"))
        tools.rmdir(os.path.join(self.package_folder, "private"))
        tools.rmdir(os.path.join(self.package_folder, "misc"))
        tools.rmdir(os.path.join(self.package_folder, "certs"))

        self.patch_binaries(executables=['openssl'])
        self.default_package()

    def package_info(self):
        if self.settings.compiler == "Visual Studio":
            self.cpp_info.libs = ["libssl", "libcrypto"]
            self.cpp_info.system_libs.extend(["crypt32", "msi", "ws2_32"])
        else:
            self.cpp_info.libs = ["ssl", "crypto"]
            if self.settings.os == "Linux":
                self.cpp_info.system_libs = ["dl", "pthread"]

        self.env_info.path.append(os.path.join(self.package_folder, "bin"))
