# -*- coding: utf-8 -*-
from conans import ConanFile
from conans import tools
from conans import MSBuild
from conans import AutoToolsBuildEnvironment
import glob
import os


class ConanRecipe(ConanFile):
    python_requires = 'common/1.0.0@mevislab/stable'
    python_requires_extend = 'common.CommonRecipe'


    def source(self):
        fileName = "icu4c-%s-src.tgz" % self.version.replace('.', '_')
        url = "https://github.com/unicode-org/icu/releases/download/release-%s/%s" % (self.version.replace('.', '-'), fileName)
        sha256 = self.conan_data['sha256'][self.version]['src']
        self.download_distfile(url=url, sha256=sha256, fileName=fileName)
        os.rename("icu", "sources")

        fileName = "icu4c-%s-data.zip" % self.version.replace('.', '_')
        url = "https://github.com/unicode-org/icu/releases/download/release-%s/%s" % (self.version.replace('.', '-'), fileName)
        sha256 = self.conan_data['sha256'][self.version]['data']
        self.download_distfile(url=url, sha256=sha256, fileName=fileName, baseFolder="sources/source")

        self.apply_patches()

    def build(self):
        if tools.os_info.is_windows:
            with tools.chdir(os.path.join('sources', 'source', 'allinone')):
                msbuild = MSBuild(self)
                msbuild.build('allinone.sln', upgrade_project=False, build_type="Debug" if self.settings.build_type == "Debug" else "Release", platforms={"x86_64":"x64"}, properties={'SkipUWP':'true'})
        else:
            build_env = AutoToolsBuildEnvironment(self)
            if tools.os_info.is_macos:
                build_env.defines.append("_DARWIN_C_SOURCE")
                if self.settings.get_safe("os.version"):
                    build_env.flags.append(tools.apple_deployment_target_flag(self.settings.os, self.settings.os.version))

            build_dir = os.path.join(self.build_folder, 'sources', 'build')
            os.mkdir(build_dir)

            platform = {
                ("Linux", "gcc"): "Linux/gcc",
                ("Linux", "clang"): "Linux",
                ("Macos", "gcc"): "MacOSX",
                ("Macos", "clang"): "MacOSX",
                ("Macos", "apple-clang"): "MacOSX"
            }.get((str(self.settings.os),  str(self.settings.compiler)))

            args = [platform,
                    f"--prefix={self.package_folder}",
                    "--with-library-bits=64",
                    "--disable-samples",
                    "--disable-tests",
                    "--disable-renaming",
                    "--disable-layout",
                    "--disable-layoutex",
                    "--disable-extras",
                    "--with-data-packaging=library"]

            if self.settings.build_type == "Debug":
                args.extend(["--disable-release", "--enable-debug", "--with-library-suffix=d"])

            args.extend(["--disable-static", "--enable-shared"])

            with tools.environment_append(build_env.vars):
                with tools.chdir(build_dir):
                    # workaround for https://unicode-org.atlassian.net/browse/ICU-20531
                    os.makedirs(os.path.join("data", "out", "tmp"))
                    self.run("../source/runConfigureICU %s" % " ".join(args))
                    self.run("make VERBOSE=1 -j {cpu_count}".format(cpu_count=tools.cpu_count()))
                    self.run("make VERBOSE=1 install")


    def package(self):
        if tools.os_info.is_windows:
            self.copy(pattern="*", dst="include", src="sources/include")
            self.copy(pattern="*.lib", dst="lib/", src="sources/lib64")
            self.copy(pattern="*.exe", dst="bin/", src="sources/bin64")
            self.copy(pattern="*.dll", dst="bin/", src="sources/bin64")
            self.copy(pattern="*.pdb", dst="bin/", src="sources/lib64")
        else:
            tools.rmdir(os.path.join(self.package_folder, "lib", "pkgconfig"))
            tools.rmdir(os.path.join(self.package_folder, "lib", "icud"))
            tools.rmdir(os.path.join(self.package_folder, "lib", "icu"))
            tools.rmdir(os.path.join(self.package_folder, "share"))
            tools.rmdir(os.path.join(self.package_folder, "sbin"))

        # change rpath of binaries
        if tools.os_info.is_linux:
            patchelf = tools.which("patchelf")
            with tools.chdir(os.path.join(self.package_folder, "bin")):
                for binary in ['derb', 'genbrk', 'gencfu', 'gencnval', 'gendict', 'genrb', 'icuinfo', 'makeconv', 'pkgdata']:
                    self.run(f"{patchelf} --set-rpath '$ORIGIN/../lib' {binary}")
            for lib in glob.glob(os.path.join(self.package_folder, "lib", "*.so")):
                self.run(f"{patchelf} --set-rpath '$ORIGIN/../lib' {lib}")

        self.patch_binaries()
        self.default_package(split_debug=False) # split_debug=True would corrupt libicudata.so


    def package_info(self):
        libname = lambda name: name + "d" if self.settings.build_type == 'Debug' else name

        self.cpp_info.names["cmake_find_package"] = "ICU"
        self.cpp_info.names["cmake_find_package_multi"] = "ICU"

        # icudata
        self.cpp_info.components["icu-data"].names["cmake_find_package"] = "data"
        self.cpp_info.components["icu-data"].names["cmake_find_package_multi"] = "data"
        self.cpp_info.components["icu-data"].names["pkg_config"] = "icu-data"
        self.cpp_info.components["icu-data"].libs = ['icudt' if tools.os_info.is_windows else libname('icudata')]

        self.cpp_info.components["icu-data-alias"].names["cmake_find_package"] = "dt"
        self.cpp_info.components["icu-data-alias"].names["cmake_find_package_multi"] = "dt"
        self.cpp_info.components["icu-data-alias"].requires = ["icu-data"]

        # icuuc
        self.cpp_info.components["icu-uc"].names["cmake_find_package"] = "uc"
        self.cpp_info.components["icu-uc"].names["cmake_find_package_multi"] = "uc"
        self.cpp_info.components["icu-uc"].names["pkg_config"] = "icu-uc"
        self.cpp_info.components["icu-uc"].libs = [libname("icuuc")]
        self.cpp_info.components["icu-uc"].requires = ["icu-data"]

        if tools.os_info.is_linux:
            self.cpp_info.components["icu-uc"].system_libs = ["m", "pthread", "dl"]
        elif tools.os_info.is_windows:
            self.cpp_info.components["icu-uc"].system_libs = ["advapi32"]

        # icui18n
        self.cpp_info.components["icu-i18n"].names["cmake_find_package"] = "i18n"
        self.cpp_info.components["icu-i18n"].names["cmake_find_package_multi"] = "i18n"
        self.cpp_info.components["icu-i18n"].names["pkg_config"] = "icu-i18n"
        self.cpp_info.components["icu-i18n"].libs = [libname("icuin" if tools.os_info.is_windows else "icui18n")]
        self.cpp_info.components["icu-i18n"].requires = ["icu-uc"]
        if tools.os_info.is_linux:
            self.cpp_info.components["icu-i18n"].system_libs = ["m"]

        self.cpp_info.components["icu-i18n-alias"].names["cmake_find_package"] = "in"
        self.cpp_info.components["icu-i18n-alias"].names["cmake_find_package_multi"] = "in"
        self.cpp_info.components["icu-i18n-alias"].requires = ["icu-i18n"]

        # icuio
        self.cpp_info.components["icu-io"].names["cmake_find_package"] = "io"
        self.cpp_info.components["icu-io"].names["cmake_find_package_multi"] = "io"
        self.cpp_info.components["icu-io"].names["pkg_config"] = "icu-io"
        self.cpp_info.components["icu-io"].libs = [libname("icuio")]
        self.cpp_info.components["icu-io"].requires = ["icu-i18n", "icu-uc"]

        # icutu
        self.cpp_info.components["icu-tu"].names["cmake_find_package"] = "tu"
        self.cpp_info.components["icu-tu"].names["cmake_find_package_multi"] = "tu"
        self.cpp_info.components["icu-tu"].names["pkg_config"] = "icu-tu"
        self.cpp_info.components["icu-tu"].libs = [libname("icutu")]
        self.cpp_info.components["icu-tu"].requires = ["icu-i18n", "icu-uc"]
        if tools.os_info.is_linux:
            self.cpp_info.components["icu-tu"].system_libs = ["pthread"]

        # icutest
        self.cpp_info.components["icu-test"].names["cmake_find_package"] = "test"
        self.cpp_info.components["icu-test"].names["cmake_find_package_multi"] = "test"
        self.cpp_info.components["icu-tu"].names["pkg_config"] = "icu-test"
        self.cpp_info.components["icu-test"].libs = [libname("icutest")]
        self.cpp_info.components["icu-test"].requires = ["icu-tu", "icu-uc"]

        # extend PATH
        bin_path = os.path.join(self.package_folder, "bin")
        self.output.info("Appending PATH environment variable: {}".format(bin_path))
        self.env_info.PATH.append(bin_path)
