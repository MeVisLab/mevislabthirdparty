import os
from conan import ConanFile
from conan.tools.files import get, copy

required_conan_version = ">=2.2.2"


class ConanRecipe(ConanFile):
    name = "yui2"
    version = "2.9.0"
    homepage = "https://yui.github.io/yui2"
    description = "A fast, small, and feature-rich JavaScript library"
    package_type = "build-scripts"
    license = "BSD-3-Clause"
    exports_sources = ["LICENSE"]
    settings = None

    mlab_hooks = {"test_package.skip": True, "folders.skip": True}

    def source(self):
        get(
            self,
            sha256="6e3d2ae0f77877a2daab7946c93d45e5f2780a587dddf5db0ced5799772b1f6a",
            url=f"https://yui.github.io/yui2/archives/yui_{self.version}.zip",
            strip_root=True,
        )

    def package(self):
        copy(
            self,
            "*",
            src=os.path.join(self.source_folder, "build"),
            dst=os.path.join(self.package_folder, "web", self.name),
        )
        copy(self, "LICENSE", src=self.source_folder, dst=os.path.join(self.package_folder, "licenses"))

    def package_info(self):
        self.cpp_info.set_property("cpe", "cpe:2.3:a:yahoo:yui:*:*:*:*:*:*:*:*")
        self.cpp_info.set_property(
            "purl", f"pkg:github/yui/yui2@{self.version}"
        )  # no version related tags on this project
        self.cpp_info.includedirs.clear()
        self.cpp_info.set_property("cmake_find_mode", "none")
