# -*- coding: utf-8 -*-
from conans import ConanFile
from conans import tools
from conans import Meson
from conans.errors import ConanInvalidConfiguration
import os

class ConanRecipe(ConanFile):
    python_requires = 'common/1.0.0@mevislab/stable'
    python_requires_extend = 'common.CommonRecipe'
    settings = "os", "compiler"

    _meson = None


    def package_id(self):
        self.info.header_only()


    def validate(self):
        if self.settings.os != "Windows":
            raise ConanInvalidConfiguration(f"{self.name} is only supported on Windows")


    def build_requirements(self):
        channel = "@{0}/{1}".format(self.user, self.channel)
        if tools.os_info.is_windows:
            self.build_requires("meson_installer/[>=0.54.1]" + channel)
            self.build_requires("winflexbison_installer/[>=2.5.22]" + channel)


    def requirements(self):
        channel = "@{0}/{1}".format(self.user, self.channel)
        self.requires("llvm/[>=10.0.0]" + channel, private=True)


    def _configure_meson(self):
        if not self._meson:
            # hack to get the right compiler runtime:
            if self.settings.compiler == "Visual Studio":
                self.settings.compiler.runtime = "MT"

            with tools.environment_append({"ZLIB_ROOT": self.deps_cpp_info['zlib'].rootpath}):
                self._meson = Meson(self, build_type="Release")
                self._meson.configure(
                    # This version creates separate AVX and AVX2 dlls (besides OpenGL32.dll):
                    # defs={ "gallium-drivers": "swr,swrast" },
                    # This version only creates the OpenGL32.dll (with only AVX support):
                    defs={
                        "gallium-drivers": "swr,swrast",
                        "shared-swr": "false",
                        "swr-arches": "avx"
                    },
                    source_folder="sources",
                    build_folder="build")
        return self._meson


    def build(self):
        meson = self._configure_meson()
        meson.build()


    def package(self):
        meson = self._configure_meson()
        meson.install()

        tools.rmdir(os.path.join(self.package_folder, 'share'))

        # copy ThirdPartyInformation from llvm, because llvm isn't a direct dependency of MeVisLab
        rootpath = self.deps_cpp_info["llvm"].rootpath
        self.copy("*", src=os.path.join(rootpath, "MeVis", "ThirdParty", "ThirdPartyInformation"), dst=os.path.join("MeVis", "ThirdParty", "ThirdPartyInformation"))

        self.default_package()
