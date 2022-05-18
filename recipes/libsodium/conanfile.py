# -*- coding: utf-8 -*-
from conans import ConanFile
from conans import AutoToolsBuildEnvironment
from conans import MSBuild
from conans import tools
import os


class ConanRecipe(ConanFile):
    python_requires = 'common/1.0.0@mevislab/stable'
    python_requires_extend = 'common.CommonRecipe'

    def build(self):
        if self.settings.compiler == "Visual Studio":
            msbuild = MSBuild(self)
            build_type = "DynDebug" if self.settings.build_type == "Debug" else "DynRelease"
            msvc = {"16": "vs2019"}.get(str(self.settings.compiler.version))
            with tools.chdir(os.path.join("sources", "builds", "msvc", msvc)):
                msbuild.build("libsodium.sln", build_type=build_type, upgrade_project=False, platforms={"x86": "Win32"}, properties={"PostBuildEventUseInBuild": "false"})
        else:
            with tools.chdir("sources"):
                args = ["--disable-static", "--enable-shared", "--with-pic"]
                if self.settings.build_type == "Debug":
                    args.append("--enable-debug")
                env_build = AutoToolsBuildEnvironment(self)
                env_build.configure(args=args)
                env_build.make()
                env_build.install()


    def package(self):
        if self.settings.compiler == "Visual Studio":
            self.copy("*.h", dst="include", src=os.path.join("sources", "src", "libsodium", "include"))
            self.copy("*.lib", dst="lib", src="sources", keep_path=False)
            self.copy("*.dll", dst="bin", src="sources", keep_path=False)
            self.copy("*.pdb", dst="bin", src="sources", keep_path=False, excludes="*vc*.pdb")

        if os.path.exists(os.path.join(self.package_folder, 'lib', 'libsodium.la')):
            os.unlink(os.path.join(self.package_folder, 'lib', 'libsodium.la'))

        tools.rmdir(os.path.join(self.package_folder, "lib", "pkgconfig"))

        self.patch_binaries()
        self.default_package()
