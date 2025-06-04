from conan import ConanFile
from conan.tools.files import copy, get

required_conan_version = ">=2.2.2"


class ConanRecipe(ConanFile):
    name = "jquery"
    version = "3.7.1"
    homepage = "https://jquery.com"
    description = "A fast, small, and feature-rich JavaScript library"
    package_type = "build-scripts"
    license = "MIT"
    settings = None

    mlab_hooks = {
        'test_package.skip': True,
        'folders.skip': True
    }

    def source(self):
        get(self,
            sha256="f4a061b7fa041a7fa52825d9163db02b5927d2fdce704ca211ddb129ec826e02",
            url=f"https://github.com/jquery/jquery/archive/{self.version}.zip",
            strip_root=True
            )

    def package(self):
        copy(self, "*", src=self.source_path / "dist", dst=self.package_path / f"web/{self.name}")
        copy(self, "LICENSE.txt", src=self.source_path, dst=self.package_path / "licenses")

    def package_info(self):
        self.cpp_info.set_property("cpe", "cpe:2.3:a:jquery:jquery:*:*:*:*:*:*:*:*")
        self.cpp_info.set_property("purl", f"pkg:github/jquery/jquery@{self.version}")
        self.cpp_info.includedirs.clear()
        self.cpp_info.set_property("cmake_find_mode", "none")
