import os
from conan import ConanFile
from conan.tools.files import get, copy
from conan.tools.layout import basic_layout

required_conan_version = ">=2.32.0"


class ConanRecipe(ConanFile):
    name = "cdt"
    version = "2.0.0"
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
            sha256="81ed0c7a8cbdc059b26948a160c3ce68c7a147976334093fe3175c8fa161a447",
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
