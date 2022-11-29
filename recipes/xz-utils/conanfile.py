# -*- coding: utf-8 -*-
from conans import ConanFile
from conans import AutoToolsBuildEnvironment
from conans import MSBuild
from conans import tools
import os
import xml.etree.ElementTree as ET


class ConanRecipe(ConanFile):
    python_requires = 'common/1.0.0@mevislab/stable'
    python_requires_extend = 'common.CommonRecipe'

    _autotools = None

    def source(self):
        self.default_source()

        # fix/remove rpath (for macos)
        tools.replace_in_file(os.path.join("sources", "configure"), r"-install_name \$rpath/", "-install_name ")

        if tools.os_info.is_windows:
            liblzmaFile = os.path.join('sources', 'windows', 'vs2019', 'liblzma_dll.vcxproj')
            # Adapt VC project file for debug suffix:
            ns = {'': 'http://schemas.microsoft.com/developer/msbuild/2003'}
            ET.register_namespace('', ns[''])
            tree = ET.parse(liblzmaFile)
            root = tree.getroot()
            # we need to add the debug suffix to the liblzma_dll.vcxproj
            for child in root.findall("PropertyGroup", ns):
                if "Debug" in child.get("Condition", ""):
                    targetNameElem = child.find("TargetName", ns)
                    if targetNameElem is not None and not targetNameElem.text.endswith('d'):
                        targetNameElem.text += 'd'
            tree.write(liblzmaFile, encoding="utf-8", xml_declaration=True)


    def _configure_autotools(self):
        if not self._autotools:
            self._autotools = AutoToolsBuildEnvironment(self)
            config_args=[ "--enable-static=no", "--enable-shared=yes",
                        "--disable-xz", "--disable-xzdec",
                        "--disable-lzmadec", "--disable-lzmainfo",
                        "--disable-lzma-links", "--disable-scripts",
                        "--disable-doc" ]

            if self.settings.build_type == "Debug":
                config_args.append("--enable-debug")

            self._autotools.configure(configure_dir="sources", vars=self._autotools.vars, args=config_args)

        return self._autotools


    def build(self):
        if self.settings.os == 'Windows':
            with tools.chdir(os.path.join('sources', 'windows', 'vs2019')):
                msbuild = MSBuild(self)
                msbuild.build('xz_win.sln', targets=['liblzma_dll:Rebuild'], build_type="Debug" if self.settings.build_type == "Debug" else "Release", platforms={"x86": "Win32", "x86_64": "x64"}, upgrade_project=False)
        else:
            autotools = self._configure_autotools()
            autotools.make(vars=autotools.vars)


    def package(self):
        if self.settings.os == 'Windows':
            self.copy("*.h", dst="include", src=os.path.join('sources', 'src', 'liblzma', 'api'), keep_path=True)
            bindir = os.path.join("sources", "windows", 'vs2017' if self.settings.compiler.version == 15 else 'vs2019')
            self.copy("*.dll", dst="bin", src=bindir, keep_path=False)
            self.copy("*.pdb", dst="bin", src=bindir, keep_path=False, excludes="*/vc*.pdb")
            self.copy("*.lib", dst="lib", src=bindir, keep_path=False)
        else:
            autotools = self._configure_autotools()
            autotools.install(vars=autotools.vars)

        if os.path.exists(os.path.join(self.package_folder, 'lib', 'liblzma.la')):
            os.unlink(os.path.join(self.package_folder, 'lib', 'liblzma.la'))

        if not tools.os_info.is_windows:
            tools.rmdir(os.path.join(self.package_folder, "bin"))

        tools.rmdir(os.path.join(self.package_folder, "share"))
        tools.rmdir(os.path.join(self.package_folder, "lib", "pkgconfig"))

        self.patch_binaries()
        self.default_package()
