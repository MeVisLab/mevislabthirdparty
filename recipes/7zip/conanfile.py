from conan import ConanFile
from conan.tools.files import copy, get, replace_in_file
from conan.tools.layout import basic_layout
from conan.tools.microsoft import NMakeToolchain
from conan.errors import ConanInvalidConfiguration
import os

required_conan_version = ">=2.2.2"


class ConanRecipe(ConanFile):
    name = "7zip"
    version = "24.09"
    license = "LGPL-2.1-or-later AND BSD-3-Clause"
    homepage = "https://www.7-zip.org"
    description = "7-Zip is a file archiver with a high compression ratio"
    settings = "os", "arch", "compiler", "build_type"
    package_type = "application"

    def package_id(self):
        self.info.settings.rm_safe("build_type")
        self.info.settings.rm_safe("compiler.runtime_type")

    def configure(self):
        if self.settings.os != "Windows":
            raise ConanInvalidConfiguration(f"{self.name} is only supported on Windows")

    def validate(self):
        if self.settings.os != "Windows":
            raise ConanInvalidConfiguration(f"{self.name} is only supported on Windows")

    def validate_build(self):
        if self.settings.build_type != "Release":
            raise ConanInvalidConfiguration(f"{self.name} is built in release mode only.")

    def layout(self):
        basic_layout(self, src_folder="src")

    def source(self):
        version = "".join(self.version.split("."))
        get(
            self,
            sha256="49c05169f49572c1128453579af1632a952409ced028259381dac30726b6133a",
            url=f"https://sourceforge.net/projects/sevenzip/files/7-Zip/{self.version}/7z{version}-src.tar.xz",
        )

    def generate(self):
        tc = NMakeToolchain(self)
        tc.generate()

    def build(self):
        make_file = os.path.join(self.source_folder, "CPP", "Build.mak")
        os.chmod(make_file, 0o644)
        replace_in_file(self, make_file, "-MT", f"-{self.settings.compiler.runtime}")
        replace_in_file(self, make_file, "-MD", f"-{self.settings.compiler.runtime}")
        self.run(f"nmake /f makefile PLATFORM=x64", cwd=os.path.join(self.source_folder, "CPP", "7zip"))

    def package(self):
        copy(self, "License.txt", dst=os.path.join(self.package_folder, "licenses"), src=os.path.join(self.source_folder, "DOC"))
        copy(self, "unRarLicense.txt", dst=os.path.join(self.package_folder, "licenses"), src=os.path.join(self.source_folder, "DOC"))
        copy(
            self,
            "*/7z.exe",
            dst=os.path.join(self.package_folder, "bin"),
            src=os.path.join(self.source_folder, "CPP", "7zip"),
            keep_path=False,
        )
        copy(
            self,
            "*/7z.dll",
            dst=os.path.join(self.package_folder, "bin"),
            src=os.path.join(self.source_folder, "CPP", "7zip"),
            keep_path=False,
        )

    def package_info(self):
        self.cpp_info.set_property("cpe", "cpe:2.3:a:7-zip:7-zip:*:*:*:*:*:*:*:*")
        self.cpp_info.set_property("purl", f"pkg:github/ip7z/7zip@{self.version}")
        self.cpp_info.includedirs.clear()
        self.cpp_info.libdirs.clear()
