from conan import ConanFile
from conan.tools.files import copy, get
import os

required_conan_version = ">=2.2.2"


class ConanRecipe(ConanFile):
    name = "mocha"
    version = "11.0.0"
    homepage = "https://mochajs.org"
    description = "Simple, flexible, fun javascript test framework for node.js & the browser"
    package_type = "build-scripts"
    license = "MIT"
    settings = None

    mlab_hooks = {"test_package.skip": True, "folders.skip": True}

    def source(self):
        get(
            self,
            sha256="a9a79416a5e8ab14d379df2b75abdfa3ee7db0b926dccf18481277f21af4154f",
            url=f"https://github.com/mochajs/mocha/archive/refs/tags/v{self.version}.tar.gz",
            strip_root=True,
        )

    def package(self):
        copy(self, "*", src=os.path.join(self.source_folder, "lib"), dst=os.path.join(self.package_folder, "web", self.name))
        copy(self, "LICENSE", src=self.source_folder, dst=os.path.join(self.package_folder, "licenses"))

    def package_info(self):
        self.cpp_info.set_property("cpe", "cpe:2.3:a:mochajs:mocha:*:*:*:*:*:*:*:*")
        self.cpp_info.set_property("purl", f"pkg:github/mochajs/mocha@v{self.version}")
        self.cpp_info.includedirs.clear()
        self.cpp_info.set_property("cmake_find_mode", "none")
