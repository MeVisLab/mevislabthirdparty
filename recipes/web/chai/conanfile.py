import os
from conan import ConanFile
from conan.tools.files import copy, get

required_conan_version = ">=2.2.2"


class ConanRecipe(ConanFile):
    name = "chai"
    version = "5.2.0"
    homepage = "https://chaijs.com"
    description = (
        "BDD / TDD assertion framework for node.js and the browser that can be paired with any testing framework"
    )
    package_type = "build-scripts"
    license = "MIT"
    settings = None

    mlab_hooks = {"test_package.skip": True, "folders.skip": True}

    def source(self):
        get(
            self,
            sha256="c5915d1cb96e7fd7fcf47f8adfa835595e5c53206fc9deba41d70c860be00e0a",
            url=f"https://github.com/chaijs/chai/archive/refs/tags/v{self.version}.tar.gz",
            strip_root=True,
        )

    def package(self):
        copy(
            self,
            "*",
            src=os.path.join(self.source_folder, "lib", "chai"),
            dst=os.path.join(self.package_folder, "web", self.name),
        )
        copy(self, "LICENSE", src=self.source_folder, dst=os.path.join(self.package_folder, "licenses"))

    def package_info(self):
        # self.cpp_info.set_property("cpe", "")  # No CPE (yet)?
        self.cpp_info.set_property("purl", f"pkg:github/chaijs/chai@v{self.version}")
        self.cpp_info.includedirs.clear()
        self.cpp_info.set_property("cmake_find_mode", "none")
