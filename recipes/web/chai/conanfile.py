from conan import ConanFile
from conan.tools.files import copy, get

required_conan_version = ">=2.2.2"


class ConanRecipe(ConanFile):
    name = "chai"
    version = "5.1.1"
    homepage = "https://chaijs.com"
    description = "BDD / TDD assertion framework for node.js and the browser that can be paired with any testing framework"
    package_type = "build-scripts"
    license = "MIT"
    settings = None

    mlab_hooks = {"test_package.skip": True, "folders.skip": True}

    def source(self):
        get(
            self,
            sha256="7d8a91c2a14d9877647999c65e59adc81f9889c7e6c3869fd564d12637a90277",
            url=f"https://github.com/chaijs/chai/archive/refs/tags/v{self.version}.tar.gz",
            strip_root=True,
        )

    def package(self):
        copy(self, "*", src=self.source_path / "lib" / "chai", dst=self.package_path / f"web/{self.name}")
        copy(self, "LICENSE", src=self.source_path, dst=self.package_path / "licenses")

    def package_info(self):
        # self.cpp_info.set_property("cpe", "")  # No CPE (yet)?
        self.cpp_info.set_property("base_purl", "github/chaijs/chai")
        self.cpp_info.includedirs.clear()
        self.cpp_info.set_property("cmake_find_mode", "none")
