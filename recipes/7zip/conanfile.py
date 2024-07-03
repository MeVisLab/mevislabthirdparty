from conan import ConanFile
from conan.tools.files import copy, get, replace_in_file
from conan.tools.layout import basic_layout
from conan.tools.microsoft import NMakeToolchain
from conans.errors import ConanInvalidConfiguration

required_conan_version = ">=2.2.2"


class ConanRecipe(ConanFile):
    name = "7zip"
    version = "24.06"
    license = ("LGPL-2.1-or-later", "BSD-3-Clause")
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
            sha256="2aa1660c773525b2ed84d6cd7ff0680c786ec0893b87e4db44654dcb7f5ac8b5",
            url=f"https://sourceforge.net/projects/sevenzip/files/7-Zip/{self.version}/7z{version}-src.tar.xz",
        )

    def generate(self):
        tc = NMakeToolchain(self)
        tc.generate()

    def build(self):
        make_file = self.source_path / "CPP" / "Build.mak"
        make_file.chmod(0o644)
        replace_in_file(self, make_file, "-MT", f"-{self.settings.compiler.runtime}")
        replace_in_file(self, make_file, "-MD", f"-{self.settings.compiler.runtime}")
        self.run(f"nmake /f makefile PLATFORM=x64", cwd=self.source_path / "CPP" / "7zip")

    def package(self):
        copy(self, "License.txt", dst=self.package_path / "licenses", src=self.source_path / "DOC")
        copy(self, "unRarLicense.txt", dst=self.package_path / "licenses", src=self.source_path / "DOC")
        copy(self, "*/7z.exe", dst=self.package_path / "bin", src=self.source_path / "CPP" / "7zip", keep_path=False)
        copy(self, "*/7z.dll", dst=self.package_path / "bin", src=self.source_path / "CPP" / "7zip", keep_path=False)

    def package_info(self):
        self.cpp_info.includedirs.clear()
        self.cpp_info.libdirs.clear()
