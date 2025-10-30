from conan import ConanFile
from conan.tools.files import copy, download
import os

required_conan_version = ">=2.2.2"


class ConanRecipe(ConanFile):
    name = "requirejs"
    version = "2.3.7"
    homepage = "https://requirejs.org"
    description = "RequireJS is a JavaScript file and module loader"
    package_type = "build-scripts"
    license = "MIT"
    settings = None
    exports_sources = ["LICENSE"]

    mlab_hooks = {"test_package.skip": True, "folders.skip": True}

    def source(self):
        download(
            self,
            sha256="c5a2028a4318d3f21fd23f66167f85b10f332a850578224915041d12550e4f2a",
            url=f"https://requirejs.org/docs/release/{self.version}/minified/require.js",
            filename="require-min.js",
        )
        download(
            self,
            sha256="8215b90000b571bd241d28512c83f59855cecc3158db94b79b2d974c9923b5d2",
            url=f"https://requirejs.org/docs/release/{self.version}/comments/require.js",
            filename="require.js",
        )
        download(
            self,
            sha256="fcb236dc90b5983ecb1a0e31e495a5c55d7087081709947a9731f367f91f81c1",
            url=f"https://requirejs.org/docs/release/{self.version}/r.js",
            filename="r.js",
        )

    def package(self):
        copy(self, "*.js", src=self.source_folder, dst=os.path.join(self.package_folder, "web", self.name))
        copy(self, "LICENSE", src=self.source_folder, dst=os.path.join(self.package_folder, "licenses"))

    def package_info(self):
        self.cpp_info.set_property("cpe", "cpe:2.3:a:requirejs:requirejs:*:*:*:*:*:*:*:*")
        self.cpp_info.set_property("purl", f"pkg:github/requirejs/requirejs@{self.version}")
        self.cpp_info.includedirs.clear()
        self.cpp_info.set_property("cmake_find_mode", "none")
