from conan import ConanFile
from conan.tools.files import get, copy

required_conan_version = ">=2.2.2"


class ConanRecipe(ConanFile):
    name = "threejs"
    version = "140"
    homepage = "https://threejs.org"
    description = "JavaScript 3D library"
    package_type = "build-scripts"
    license = "MIT"
    settings = None

    mlab_hooks = {
        'test_package.skip': True,
        'folders.skip': True
    }

    def source(self):
        get(self,
            sha256="cd5b3458ff5bd979fd4dc693ecbad2d707522ec7e62aaa5a27a9103f167a6edb",
            url=f"https://github.com/mrdoob/three.js/archive/r{self.version}.zip",
            strip_root=True
            )

    def package(self):
        copy(self, "three.js", src=self.source_path / "build", dst=self.package_path / f"web/{self.name}")
        copy(self, "LICENSE", src=self.source_path, dst=self.package_path / "licenses")

    def package_info(self):
        self.cpp_info.includedirs.clear()
        self.cpp_info.set_property("cmake_find_mode", "none")
