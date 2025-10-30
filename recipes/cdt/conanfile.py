import os
from conan import ConanFile
from conan.tools.files import get, copy
from conan.tools.layout import basic_layout

required_conan_version = ">=2.2.2"


class ConanRecipe(ConanFile):
    name = "cdt"
    version = "1.4.4"
    homepage = "https://github.com/artem-ogre/CDT"
    description = "CDT: Constrained Delaunay Triangulation"
    license = "MPL-2.0"
    package_type = "header-library"
    no_copy_source = True

    def layout(self):
        basic_layout(self, src_folder="src")

    def source(self):
        get(
            self,
            sha256="97e57bdd1cf8219dcc81634236a502390a20dda3599dd3414a74343b7f03427f",
            url=f"https://github.com/artem-ogre/CDT/archive/refs/tags/{self.version}.tar.gz",
            strip_root=True,
        )

    def package(self):
        copy(
            self,
            pattern="LICENSE",
            src=self.source_folder,
            dst=os.path.join(self.package_folder, "licenses"),
            keep_path=False,
        )
        copy(
            self,
            pattern="*.h",
            src=os.path.join(self.source_folder, "CDT", "include"),
            dst=os.path.join(self.package_folder, "include", "CDT"),
            keep_path=False,
        )
        copy(
            self,
            pattern="*.hpp",
            src=os.path.join(self.source_folder, "CDT", "include"),
            dst=os.path.join(self.package_folder, "include", "CDT"),
            keep_path=False,
        )

    def package_info(self):
        # self.cpp_info.set_property("cpe", "")  # No CPE yet?
        self.cpp_info.set_property("purl", f"pkg:github/artem-ogre/CDT@{self.version}")
