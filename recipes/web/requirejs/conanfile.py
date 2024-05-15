from conan import ConanFile
from conan.tools.files import copy, download

required_conan_version = ">=2.2.2"


class ConanRecipe(ConanFile):
    name = "requirejs"
    version = "2.3.6"
    homepage = "https://requirejs.org"
    description = "RequireJS is a JavaScript file and module loader"
    package_type = "build-scripts"
    license = "MIT"
    settings = None
    exports_sources = ["LICENSE"]

    mlab_hooks = {
        'test_package.skip': True,
        'folders.skip': True
    }

    def source(self):
        download(self,
                 sha256="4948c3fe4b57cd92118ec7b89deb99ff0eb2586a02c5f454df21c1ecfc144c81",
                 url=f"https://requirejs.org/docs/release/{self.version}/minified/require.js",
                 filename="require-min.js"
                 )
        download(self,
                 sha256="9485f0917f97fcf4f63a5ea365200ffd57f123f451382a2f9a1ad2e2fd51ac9b",
                 url=f"https://requirejs.org/docs/release/{self.version}/comments/require.js",
                 filename="require.js"
                 )
        download(self,
                 sha256="65951f36480c17a1efe101ab673382fc435e239f51f9f7f686ea9f974c065528",
                 url=f"https://requirejs.org/docs/release/{self.version}/r.js",
                 filename="r.js"
                 )

    def package(self):
        copy(self, "*.js", src=self.source_path, dst=self.package_path / f"web/{self.name}")
        copy(self, "LICENSE", src=self.source_path, dst=self.package_path / "licenses")

    def package_info(self):
        self.cpp_info.includedirs.clear()
        self.cpp_info.set_property("cmake_find_mode", "none")
