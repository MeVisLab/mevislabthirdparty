
from conan import ConanFile
from conan.tools.cmake import CMake, CMakeToolchain, cmake_layout
from conan.tools.files import get, collect_libs, load, save
from conan.tools.scm import Version
from conans.errors import ConanException

required_conan_version = ">=2.2.2"


class ConanRecipe(ConanFile):
    name = "lzma_sdk"
    version = "19.00"
    description = "LZMA SDK"
    homepage = "https://7-zip.de/sdk.html"
    license = "Unlicense"
    package_type = "static-library"
    settings = "os", "arch", "compiler", "build_type"
    exports_sources = "CMakeLists.txt"

    def configure(self):
        self.settings.rm_safe("compiler.libcxx")
        self.settings.rm_safe("compiler.cppstd")

    def layout(self):
        cmake_layout(self, src_folder="src")

    def source(self):
        v = Version(self.version)
        minor = f"{v.minor}".zfill(2)
        get(self,
            url=f"https://github.com/sisong/lzma/archive/refs/tags/v{v.major}.{minor}.tar.gz",
            sha256="787787da5be160fb397b57407717686164b21ae469be51b59ce3a815ad046817",
            strip_root=True
        )

    def generate(self):
        tc = CMakeToolchain(self)
        tc.variables["CMAKE_DEBUG_POSTFIX"] = "_d"
        tc.variables["BUILD_SHARED_LIBS"] = False
        tc.variables["CMAKE_POSITION_INDEPENDENT_CODE"] = True
        tc.cache_variables["CONAN_LZMA_VERISON"] = f"{self.version}"
        tc.generate()

    def build(self):
        cmake = CMake(self)
        cmake.configure(build_script_folder=self.source_path.parent)
        cmake.build()

    def package(self):
        cmake = CMake(self)
        cmake.install()

        # extract license text:
        text = load(self, self.source_path / "DOC" / "lzma-sdk.txt")
        license_pos = text.find("LICENSE")
        if license_pos == -1:
            raise ConanException("License text not found")
        license_end = text.find("\n\n\n", license_pos) # two empty lines mark end of license
        if license_end == -1:
            # try Windows line end:
            license_end = text.find("\r\n\r\n\r\n", license_pos)
        if license_end == -1:
            raise ConanException("End of license text not found")
        save(self, self.package_path / "licenses" / "LICENSE", text[license_pos:license_end+2])


    def package_info(self):
        self.cpp_info.set_property("display_name", "LZMA SDK")
        self.cpp_info.libs = collect_libs(self)
        self.cpp_info.includedirs = ["include", "include/C"]
