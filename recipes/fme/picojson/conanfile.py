from conan import ConanFile
from conan.tools.files import copy, get

required_conan_version = ">=2.2.2"


class ConanRecipe(ConanFile):
    name = "picojson"
    version = "1.3.0"
    homepage = "https://github.com/kazuho/picojson"
    description = "A header-file-only, JSON parser serializer in C++"
    license = "BSD-2-Clause"
    package_type = "header-library"
    settings = "os", "arch", "compiler", "build_type"

    def configure(self):
        self.settings.rm_safe("compiler.libcxx")
        self.settings.rm_safe("compiler.cppstd")

    def source(self):
        get(self,
            sha256="056805ca2691798f5545935a14bb477f2e1d827c9fb862e6e449dbea22801c7d",
            url=f"https://github.com/kazuho/picojson/archive/refs/tags/v{self.version}.tar.gz",
            strip_root=True
            )

    def package(self):
        copy(self, "LICENSE", src=self.source_path, dst=self.package_path / "licenses")
        copy(self, "picojson.h", src=self.source_path, dst=self.package_path / "include")

    def package_info(self):
        # self.cpp_info.set_property("cpe", "")  # No CPE (yet)?
        self.cpp_info.set_property("purl", f"pkg:github/kazuho/picojson@v{self.version}")
        self.cpp_info.set_property("display_name", "PicoJSON")
        self.cpp_info.set_property("mevislab_prosdk_exclude", True)
        self.cpp_info.bindirs = []
        self.cpp_info.libdirs = []
        self.cpp_info.resdirs = []
