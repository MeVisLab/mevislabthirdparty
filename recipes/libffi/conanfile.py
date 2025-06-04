from conan import ConanFile
from conan.tools.cmake import CMake, CMakeToolchain, cmake_layout
from conan.tools.files import get, collect_libs, copy

required_conan_version = ">=2.2.2"


class ConanRecipe(ConanFile):
    name = "libffi"
    version = "3.4.8"
    homepage = "https://sourceware.org/libffi/"
    description = "A portable foreign-function interface library"
    license = "MIT"
    package_type = "static-library"
    settings = "os", "arch", "compiler", "build_type"
    exports_sources = "CMakeLists.txt", "files/fficonfig.h.in"

    def configure(self):
        self.settings.rm_safe("compiler.libcxx")
        self.settings.rm_safe("compiler.cppstd")

    def layout(self):
        cmake_layout(self, src_folder="src")

    def source(self):
        get(
            self,
            sha256="bc9842a18898bfacb0ed1252c4febcc7e78fa139fd27fdc7a3e30d9d9356119b",
            url=f"https://github.com/libffi/libffi/releases/download/v{self.version}/libffi-{self.version}.tar.gz",
            strip_root=True,
        )

    def generate(self):
        tc = CMakeToolchain(self)
        tc.variables["BUILD_SHARED_LIBS"] = False
        tc.variables["CMAKE_DEBUG_POSTFIX"] = "_d"
        tc.variables["CMAKE_POSITION_INDEPENDENT_CODE"] = True
        tc.cache_variables["CONAN_LIBFFI_VERSION"] = f"{self.version}"
        tc.cache_variables["CONAN_LIBFFI_ARCH"] = f"{self.settings.arch}"
        tc.generate()

    def build(self):
        cmake = CMake(self)
        cmake.configure(build_script_folder=self.source_path.parent)
        cmake.build()

    def package(self):
        copy(self, "LICENSE", src=self.source_path, dst=self.package_path / "licenses")
        copy(self, "*.pdb", src=self.build_path, dst=self.package_path / "bin", keep_path=False)
        cmake = CMake(self)
        cmake.install()

    def package_info(self):
        self.cpp_info.set_property("cpe", "cpe:2.3:a:libffi_project:libffi:*:*:*:*:*:*:*:")
        self.cpp_info.set_property("purl", f"pkg:github/libffi/libffi@v{self.version}")
        self.cpp_info.defines = ["FFI_BUILDING", "FFI_STATIC_BUILD"]
        self.cpp_info.libs = collect_libs(self)
