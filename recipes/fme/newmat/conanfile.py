from conan import ConanFile
from conan.tools.cmake import CMake, CMakeToolchain, cmake_layout
from conan.tools.files import get, collect_libs, patch, copy

required_conan_version = ">=2.2.2"


class ConanRecipe(ConanFile):
    name = "newmat"
    version = "11"
    homepage = "https://www.robertnz.net/nm_intro.htm"
    description = "A C++ matrix library"
    license = "Unlicense"
    package_type = "static-library"
    settings = "os", "arch", "compiler", "build_type"
    exports_sources = "LICENSE", "CMakeLists.txt", "patches/*.patch"

    def layout(self):
        cmake_layout(self, src_folder="src")

    def source(self):
        get(
            self,
            url=f"https://www.robertnz.net/ftp/newmat{self.version}.zip",
            sha256="e20470150d07fbef0b09eca6759b830ec2ac616ecf9abf0b0c1118b73fe3e5e5",
        )
        patch(self, patch_file="patches/001-fix_ordered_comparison_between_pointer_and_zero.patch")

    def generate(self):
        tc = CMakeToolchain(self)
        tc.cache_variables["CONAN_NEWMAT_VERSION"] = f"{self.version}"
        tc.variables["CMAKE_DEBUG_POSTFIX"] = "_d"
        tc.variables["BUILD_SHARED_LIBS"] = False
        tc.variables["CMAKE_POSITION_INDEPENDENT_CODE"] = True
        tc.generate()

    def build(self):
        cmake = CMake(self)
        cmake.configure(build_script_folder=self.source_path.parent)
        cmake.build()

    def package(self):
        copy(self, pattern="LICENSE", src=self.source_path.parent, dst=self.package_path / "licenses")
        copy(self, "*.pdb", src=self.build_path, dst=self.package_path / "bin", keep_path=False)
        cmake = CMake(self)
        cmake.install()

    def package_info(self):
        # self.cpp_info.set_property("cpe", "")  # No CPE (yet)?
        # self.cpp_info.set_property("base_purl", "")  # Official repository is at https://www.robertnz.net/ftp
        self.cpp_info.libs = collect_libs(self)
