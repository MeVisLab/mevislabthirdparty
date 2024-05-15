from conan import ConanFile
from conan.tools.files import copy, get

required_conan_version = ">=2.2.2"


class ConanRecipe(ConanFile):
    name = "mocha"
    version = "10.2.0"
    homepage = "https://mochajs.org"
    description = "Simple, flexible, fun javascript test framework for node.js & the browser"
    package_type = "build-scripts"
    license = "MIT"
    settings = None

    mlab_hooks = {
        'test_package.skip': True,
        'folders.skip': True
    }

    def source(self):
        get(self,
            sha256="8ba1848453fb641d7a7c982fe2bde95e89dba46316fd7ee11ce68c20c917fb57",
            url=f"https://github.com/mochajs/mocha/archive/refs/tags/v{self.version}.tar.gz",
            strip_root=True
            )

    def package(self):
        copy(self, "*", src=self.source_path / "lib", dst=self.package_path / f"web/{self.name}")
        copy(self, "LICENSE", src=self.source_path, dst=self.package_path / "licenses")

    def package_info(self):
        self.cpp_info.includedirs.clear()
        self.cpp_info.set_property("cmake_find_mode", "none")
