# -*- coding: utf-8 -*-
from conans import ConanFile
from conans import AutoToolsBuildEnvironment
from conans import MSBuild
from conans import tools
import os


class ConanRecipe(ConanFile):
    python_requires = 'common/1.0.0@mevislab/stable'
    python_requires_extend = 'common.CommonRecipe'

    _autotools = None


    def build_requirements(self):
        channel = "@{0}/{1}".format(self.user, self.channel)
        if self.settings.compiler == "Visual Studio":
            self.build_requires("strawberryperl_installer/[>=5.30]" + channel)


    def requirements(self):
        channel = "@mevislab/stable"
        self.requires("openssl/1.1.1s" + channel)


    def imports(self):
        self.copy("*.dylib*", src="lib", dst="lib")
        self.copy("*.so*", src="lib", dst="sources")


    def _build_windows(self):
        # fix openssl
        solution_pm = os.path.join("sources", "src", "tools", "msvc", "Solution.pm")
        for ssl in ["VC\libssl32", "VC\libssl64", "libssl"]:
                tools.replace_in_file(solution_pm, "%s.lib" % ssl, "%s.lib" % self.deps_cpp_info["openssl"].libs[0])
        for crypto in ["VC\libcrypto32", "VC\libcrypto64", "libcrypto"]:
            tools.replace_in_file(solution_pm, "%s.lib" % crypto, "%s.lib" % self.deps_cpp_info["openssl"].libs[1])

        config_default_pl = os.path.join("sources", "src", "tools", "msvc", "config_default.pl")
        tools.replace_in_file(config_default_pl, "openssl   => undef", "openssl   => '%s'" % self.deps_cpp_info["openssl"].rootpath.replace("\\", "/"))

        with tools.chdir(os.path.join("sources", "src", "tools", "msvc")):
            with tools.environment_append({"LC_ALL": "C", "LANG": "C"}):
                self.run("perl mkvcbuild.pl")

        with tools.chdir(os.path.join("sources")):
            msbuild = MSBuild(self)
            msbuild.build('libpq.vcxproj', upgrade_project=False)


    def _configure_autotools(self):
        if not self._autotools:
            self._autotools = AutoToolsBuildEnvironment(self, win_bash=tools.os_info.is_windows)
            args = ['--without-readline']
            args.append('--without-zlib')
            args.append('--with-openssl')
            #args.append('--disable-rpath') # ???
            if self.settings.build_type == 'Debug':
                args.append('--enable-debug')

            if tools.os_info.is_macos:
                self._autotools.link_flags.append(f"-rpath {self.build_folder}/lib")

            with tools.chdir("sources"):
                self._autotools.configure(args=args)

        return self._autotools


    def build(self):
        if self.settings.compiler == "Visual Studio":
            self._build_windows()
        else:
            autotools = self._configure_autotools()

            with tools.chdir(os.path.join("sources", "src", "backend")):
                autotools.make(target="generated-headers")
            with tools.chdir(os.path.join("sources", "src", "common")):
                autotools.make()
            with tools.chdir(os.path.join("sources", "src", "include")):
                autotools.make()
            with tools.chdir(os.path.join("sources", "src", "interfaces", "libpq")):
                autotools.make()
            with tools.chdir(os.path.join("sources", "src", "bin", "pg_config")):
                autotools.make()


    def package(self):
        if self.settings.compiler == "Visual Studio":
            self.copy("*postgres_ext.h", src="sources", dst="include", keep_path=False)
            self.copy("*pg_config.h", src="sources", dst="include", keep_path=False)
            self.copy("*pg_config_ext.h", src="sources", dst="include", keep_path=False)
            self.copy("*libpq-fe.h", src="sources", dst="include", keep_path=False)
            self.copy("*libpq-events.h", src="sources", dst="include", keep_path=False)
            self.copy("*.h", src=os.path.join("sources", "src", "include", "libpq"), dst=os.path.join("include", "libpq"), keep_path=False)
            self.copy("*genbki.h", src="sources", dst=os.path.join("include", "catalog"), keep_path=False)
            self.copy("*pg_type.h", src="sources", dst=os.path.join("include", "catalog"), keep_path=False)
            self.copy("*.lib", src="sources", dst="lib", keep_path=False)
            self.copy("*.dll", src="sources", dst="bin", keep_path=False)
            self.copy("*.pdb", src="sources", dst="bin", keep_path=False, excludes="*vc*.pdb")
        else:
            autotools = self._configure_autotools()
            with tools.chdir(os.path.join("sources", "src", "common")):
                autotools.install()
            with tools.chdir(os.path.join("sources", "src", "include")):
                autotools.install()
            with tools.chdir(os.path.join("sources", "src", "interfaces", "libpq")):
                autotools.install()
            with tools.chdir(os.path.join("sources", "src", "bin", "pg_config")):
                autotools.install()
            tools.rmdir(os.path.join(self.package_folder, "include", "postgresql", "server"))
            self.copy(pattern="*.h", dst=os.path.join("include", "catalog"), src=os.path.join("sources", "src", "include", "catalog"))

        self.copy(pattern="*.h", dst=os.path.join("include", "catalog"), src=os.path.join("sources", "src", "backend", "catalog"))
        tools.rmdir(os.path.join(self.package_folder, "share"))
        tools.rmdir(os.path.join(self.package_folder, "lib", "pkgconfig"))

        self.patch_binaries(executables=['pg_config'])
        self.default_package()


    def package_info(self):
        self.env_info.PostgreSQL_ROOT = self.package_folder
        self.cpp_info.libs = tools.collect_libs(self)
        if self.settings.os == "Linux":
            self.cpp_info.system_libs.append("pthread")
        elif self.settings.os == "Windows":
            self.cpp_info.system_libs.extend(["ws2_32", "secur32", "advapi32", "shell32", "crypt32", "wldap32"])
