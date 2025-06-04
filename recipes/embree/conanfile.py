from conan import ConanFile
from conan.errors import ConanInvalidConfiguration
from conan.tools.cmake import CMake, CMakeToolchain, cmake_layout
from conan.tools.files import collect_libs, copy, get, patch, rmdir, rm

required_conan_version = ">=2.2.2"


class ConanRecipe(ConanFile):
    name = "embree"
    version = "2.17.7"
    homepage = "https://github.com/embree/embree"
    description = "Provides ray tracing kernels and BVH building"
    license = "Apache-2.0"
    settings = "os", "arch", "compiler", "build_type"
    package_type = "shared-library"
    exports_sources = "patches/*.patch"

    def validate(self):
        if "arm" in self.settings.arch:
            raise ConanInvalidConfiguration(f"{self.name} not supported on {self.settings.arch}")

    def layout(self):
        cmake_layout(self, src_folder="src")

    def source(self):
        get(self,
            url=f"https://github.com/embree/embree/archive/v{self.version}.tar.gz",
            sha256="c0694f287fa1fbb382aba3a895702e248d92f7e89c0e5f64aefee965482ec04c",
            strip_root=True)
        patch(self, patch_file="patches/001-ignore_broken_sse_4_1_isa.patch")
        patch(self, patch_file="patches/002-cmake_minimum_required_fix.patch")

    def generate(self):
        tc = CMakeToolchain(self)
        tc.variables["CMAKE_DEBUG_POSTFIX"] = "_d"
        tc.variables["BUILD_SHARED_LIBS"] = True
        tc.variables['EMBREE_ISPC_SUPPORT'] = False
        tc.variables['EMBREE_TUTORIALS'] = False
        tc.variables['EMBREE_TASKING_SYSTEM'] = "INTERNAL"
        tc.generate()

    def build(self):
        cmake = CMake(self)
        cmake.configure()
        cmake.build()

    def package(self):
        copy(self, "LICENSE.txt", src=self.source_path, dst=self.package_path / "licenses")
        copy(self, "*.pdb", src=self.build_path, dst=self.package_path / "bin", keep_path=False, excludes="*vc???.pdb")
        cmake = CMake(self)
        cmake.install()
        rmdir(self, self.package_path / "bin" / "models")                    # Windows
        rmdir(self, self.package_path / "bin" / "embree2" / "models")        # Unix
        rmdir(self, self.package_path / "lib" / "cmake")
        rmdir(self, self.package_path / "share")
        rm(self, pattern="embree-config*.cmake", folder=self.package_folder) # Windows

    def package_info(self):
        # self.cpp_info.set_property("cpe", "")  # No CPE (yet)?
        self.cpp_info.set_property("purl", f"pkg:github/embree/embree@v{self.version}")
        self.cpp_info.set_property("cmake_file_name", "Embree")
        self.cpp_info.set_property("cmake_target_name", "Embree::Embree")
        self.cpp_info.libs = collect_libs(self)
