from conan import ConanFile
from conan.tools.files import copy, get

required_conan_version = ">=2.2.2"


class ConanRecipe(ConanFile):
    name = "bootstrap"
    version = "3.1.1"
    homepage = "https://getbootstrap.com"
    description = "CSS framework directed at responsive, mobile-first front-end web development"
    package_type = "build-scripts"
    license = "MIT"
    settings = None

    mlab_hooks = {
        'test_package.skip': True,
        'folders.skip': True
    }

    def source(self):
        get(self,
            sha256="449b9c63c0e9bc32f396ef11eef91281f013877427db1e1b59f96ae48d36e971",
            url=f"https://github.com/twbs/bootstrap/archive/v{self.version}.zip",
            strip_root=True
            )

    def package(self):
        copy(self, "*", src=self.source_path / "dist", dst=self.package_path / f"web/{self.name}")
        copy(self, "LICENSE", src=self.source_path, dst=self.package_path / "licenses")

    def package_info(self):
        self.cpp_info.set_property("cpe", "cpe:2.3:a:getbootstrap:bootstrap:*:*:*:*:*:*:*:*")
        self.cpp_info.set_property("base_purl", "github/twbs/bootstrap")
        self.cpp_info.includedirs.clear()
        self.cpp_info.set_property("cmake_find_mode", "none")
