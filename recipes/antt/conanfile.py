from conan import ConanFile
from conan.tools.files import copy

required_conan_version = ">=2.2.2"

class ConanRecipe(ConanFile):
    name = "antt"
    version = "2.08"
    homepage = "https://www.gust.org.pl"
    description = "antt - Antykwa Toruńska: a Type 1 family of a Polish traditional type"
    license = "LPPL-1.3a"
    package_type = "build-scripts"
    exports_sources = "sources/*"
    no_copy_source = True

    mlab_hooks = {
        "test_package.skip": True,
        "folders.exclude": ["MeVis"]
    }

    def package(self):
        copy(self, "LICENSE", src=self.source_path / "sources", dst=self.package_path / "licenses" )
        copy(self,
             pattern="*",
             src=self.source_path / "sources",
             dst=self.package_path / "MeVis" / "ThirdParty" / "Resources" / "Linux",
             keep_path=True
        )

    def package_info(self):
        self.cpp_info.includedirs = []
