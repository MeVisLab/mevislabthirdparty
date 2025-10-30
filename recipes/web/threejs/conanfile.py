from conan import ConanFile
from conan.tools.files import get, copy
import os

required_conan_version = ">=2.2.2"


class ConanRecipe(ConanFile):
    name = "threejs"
    version = "176"
    homepage = "https://threejs.org"
    description = "JavaScript 3D library"
    package_type = "build-scripts"
    license = "MIT"
    settings = None

    mlab_hooks = {"test_package.skip": True, "folders.skip": True}

    def source(self):
        get(
            self,
            sha256="c28d0e11c281684f4c72356926e8fe374c99176eafad45cda56551fee25e803a",
            url=f"https://github.com/mrdoob/three.js/archive/r{self.version}.zip",
            strip_root=True,
        )

    def package(self):
        copy(
            self,
            "three.js",
            src=os.path.join(self.source_folder, "build"),
            dst=os.path.join(self.package_folder, "web", self.name),
        )
        copy(self, "LICENSE", src=self.source_folder, dst=os.path.join(self.package_folder, "licenses"))

    def package_info(self):
        self.cpp_info.set_property("cpe", "cpe:2.3:a:three_project:three:*:*:*:*:*:*:*:*")
        self.cpp_info.set_property("purl", f"pkg:github/mrdoob/three.js@r{self.version}")
        self.cpp_info.includedirs.clear()
        self.cpp_info.set_property("cmake_find_mode", "none")
