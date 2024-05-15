from conan import ConanFile
from conan.tools.files import copy, get

required_conan_version = ">=2.2.2"

class ConanRecipe(ConanFile):
    name = "chai"
    version = "4.3.10"
    homepage = "https://chaijs.com"
    description = "BDD / TDD assertion framework for node.js and the browser that can be paired with any testing framework"
    package_type = "build-scripts"
    license = "MIT"
    settings = None

    mlab_hooks = {
        'test_package.skip': True,
        'folders.skip': True
    }

    def source(self):
        get(self,
            sha256="f5f29bd2ba20ecd1fb47a51808403a5fe5162bb1be9ade9796061d4228c3eb24",
            url=f"https://github.com/chaijs/chai/archive/refs/tags/v{self.version}.tar.gz",
            strip_root=True
            )

    def package(self):
        copy(self, "*", src=self.source_path / "lib" / "chai", dst=self.package_path / f"web/{self.name}")
        copy(self, "LICENSE", src=self.source_path, dst=self.package_path / "licenses")

    def package_info(self):
        self.cpp_info.includedirs.clear()
        self.cpp_info.set_property("cmake_find_mode", "none")
