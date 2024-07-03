from conan import ConanFile
from conan.tools.files import get, copy
from conan.tools.layout import basic_layout

required_conan_version = ">=2.2.2"


class ConanRecipe(ConanFile):
    name = "cdt"
    version = "1.4.1"
    homepage = "https://github.com/artem-ogre/CDT/"
    description = "CDT: Constrained Delaunay Triangulation."
    license = "MPL-2.0"
    package_type = "header-library"
    no_copy_source = True

    def layout(self):
        basic_layout(self, src_folder="src")

    def source(self):
        get(
            self,
            sha256="86df99eb5f02a73eeb8c6ea45765eed0d7f206e8d4d9f6479f77e3c590ae5bb3",
            url=f"https://github.com/artem-ogre/CDT/archive/refs/tags/{self.version}.tar.gz",
            strip_root=True,
        )

    def package(self):
        copy(self, pattern="LICENSE", src=self.source_path, dst=self.package_path / "licenses", keep_path=False)
        copy(self, pattern="*.h", src=self.source_path / "CDT" / "include", dst=self.package_path / "include" / "CDT", keep_path=False)
        copy(self, pattern="*.hpp", src=self.source_path / "CDT" / "include", dst=self.package_path / "include" / "CDT", keep_path=False)
