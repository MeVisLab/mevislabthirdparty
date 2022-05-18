# -*- coding: utf-8 -*-
from conans import ConanFile
from conans import tools
from conans import MSBuild
from conans import AutoToolsBuildEnvironment
import os


class ConanRecipe(ConanFile):
    python_requires = 'common/1.0.0@mevislab/stable'
    python_requires_extend = 'common.CommonRecipe'

    def get_windows_sdk_version(self):
        if tools.os_info.is_windows:
            sdkver = os.getenv('WindowsSDKVersion', '').strip()
            # This environment variable might end with a backslash due to a VS bug.
            sdkver = sdkver[0:-1] if sdkver.endswith('\\') else sdkver

            return None if sdkver == '' else sdkver
        return None


    def source(self):
        if tools.os_info.is_windows:
            fileName = "hunspell-%s.zip" % self.version
            url = "https://github.com/hunspell/hunspell/archive/v%s.zip" % self.version
            sha256 = "7089cc01ffd9122c960e1f8c7930a75be989ca4e9468773cef1b0a655bfb4368"
            self.download_distfile(url=url, sha256=sha256, fileName=fileName)
        else:
            fileName = "hunspell-%s.tar.gz" % self.version
            url = "https://github.com/hunspell/hunspell/files/2573619/%s" % fileName
            sha256 = "57be4e03ae9dd62c3471f667a0d81a14513e314d4d92081292b90435944ff951"
            self.download_distfile(url=url, sha256=sha256, fileName=fileName)

        os.rename("hunspell-%s" % self.version, "sources")

        # change rpath
        if not tools.os_info.is_windows:
            tools.replace_in_file('sources/configure', '-install_name \$rpath/\$soname', '-install_name \$soname')
        else:
            tools.replace_in_file(os.path.join('sources', 'msvc', 'hunspell.vcxproj'), "v140_xp", "v140")
            tools.replace_in_file(os.path.join('sources', 'msvc', 'libhunspell.vcxproj'), "v140_xp", "v140")
            tools.replace_in_file(os.path.join('sources', 'msvc', 'testparser.vcxproj'), "v140_xp", "v140")
            sdkver = self.get_windows_sdk_version()
            if sdkver is not None:
                sdk_str = '<WindowsTargetPlatformVersion>%s</WindowsTargetPlatformVersion></PropertyGroup>' % sdkver
                tools.replace_in_file(os.path.join('sources', 'msvc', 'hunspell.vcxproj'), '</PropertyGroup>', sdk_str)
                tools.replace_in_file(os.path.join('sources', 'msvc', 'libhunspell.vcxproj'), '</PropertyGroup>', sdk_str)
                tools.replace_in_file(os.path.join('sources', 'msvc', 'testparser.vcxproj'), '</PropertyGroup>', sdk_str)


    def build(self):
        if self.settings.os == "Windows":
            self._msvc_build()
        else:
            self._unix_build()


    def _unix_build(self):
        args=['--enable-shared', '--disable-static']
        autotools = AutoToolsBuildEnvironment(self)
        autotools.configure(configure_dir='sources', args=args)
        autotools.make()


    def _msvc_build(self):
        with tools.chdir("sources"):
            msbuild = MSBuild(self)
            build_type = {"Release":"Release_dll", "Debug":"Debug_dll"}[str(self.settings.build_type)]
            msbuild.build("msvc/Hunspell.sln", targets=["libhunspell"], build_type=build_type, upgrade_project=False)


    def package(self):
        for h in ["hunspell.hxx", "hunspell.h", "hunvisapi.h", "w_char.hxx", "atypes.hxx"]:
            self.copy(h, dst=os.path.join("include", "hunspell"), src=os.path.join("sources", "src", "hunspell"))

        self.copy("*libhunspell*.dll", dst="bin", keep_path=False)
        self.copy("*libhunspell*.pdb", dst="bin", keep_path=False)

        self.copy("*libhunspell*.dylib", dst="lib", keep_path=False, symlinks=True)
        self.copy("*libhunspell*.so*", dst="lib", keep_path=False, symlinks=True)
        self.copy("*libhunspell*.lib", dst="lib", keep_path=False)
        self.copy("*libhunspell*.a", dst="lib", keep_path=False)

        self.patch_binaries()
        self.default_package()


    def package_info(self):
        self.default_package_info()
        self.cpp_info.includedirs = ["include", "include/hunspell"]
