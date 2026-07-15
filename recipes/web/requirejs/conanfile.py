from conan import ConanFile
from conan.tools.files import copy, get
from conan.tools.layout import basic_layout
import os

required_conan_version = ">=2.2.2"


class ConanRecipe(ConanFile):
    name = "requirejs"
    version = "2.3.8"
    homepage = "https://requirejs.org"
    description = "RequireJS is a JavaScript file and module loader"
    package_type = "build-scripts"
    license = "MIT"
    settings = None
    exports_sources = ["LICENSE"]

    mlab_hooks = {"test_package.skip": True, "folders.skip": True}

    def layout(self):
        basic_layout(self, src_folder="src")

    def source(self):
        get(
            self,
            sha256="777158e89275e16bd51aec3ef714fbcb5dc45789e7078659933bc814916d7dec",
            url=f"https://registry.npmjs.org/requirejs/-/requirejs-{self.version}.tgz",
            strip_root=True,
        )

    def package(self):
        copy(
            self,
            "r.js",
            src=os.path.join(self.source_folder, "bin"),
            dst=os.path.join(self.package_folder, "web", self.name),
        )
        copy(self, "require.js", src=self.source_folder, dst=os.path.join(self.package_folder, "web", self.name))
        copy(self, "LICENSE", src=self.export_sources_folder, dst=os.path.join(self.package_folder, "licenses"))

    def package_info(self):
        self.cpp_info.set_property("cpe", f"cpe:2.3:a:requirejs:requirejs:{self.version}:*:*:*:*:*:*:*")
        self.cpp_info.set_property("purl", f"pkg:github/requirejs/requirejs@{self.version}")
        self.cpp_info.includedirs.clear()
        self.cpp_info.set_property("cmake_find_mode", "none")
