from conan import ConanFile
from conan.tools.cmake import CMake, CMakeToolchain, cmake_layout
from conan.tools.files import get, copy, rmdir, collect_libs

required_conan_version = ">=2.2.2"


class ConanRecipe(ConanFile):
    name = "libdeflate"
    version = "1.24"
    homepage = "https://github.com/ebiggers/libdeflate"
    description = "Heavily optimized DEFLATE/zlib/gzip (de)compression"
    license = "MIT"
    package_type = "shared-library"
    settings = "os", "arch", "compiler", "build_type"

    def configure(self):
        self.settings.rm_safe("compiler.libcxx")
        self.settings.rm_safe("compiler.cppstd")

    def layout(self):
        cmake_layout(self, src_folder="src")

    def source(self):
        get(
            self,
            sha256="a0dda1c4b804742066db07b9510876edd09cc0ca06cdc32c5dfe1b2016a26463",
            url=f"https://github.com/ebiggers/libdeflate/releases/download/v{self.version}/libdeflate-{self.version}.tar.gz",
            strip_root=True,
        )

    def generate(self):
        tc = CMakeToolchain(self)
        tc.variables["BUILD_SHARED_LIBS"] = True
        tc.variables["CMAKE_DEBUG_POSTFIX"] = "_d"
        tc.generate()

    def build(self):
        cmake = CMake(self)
        cmake.configure()
        cmake.build()

    def package(self):
        cmake = CMake(self)
        cmake.install()
        copy(self, "COPYING", src=self.source_path, dst=self.package_path / "licenses")
        copy(self, "*.pdb", src=self.build_path, dst=self.package_path / "bin", keep_path=False)
        rmdir(self, self.package_path / "lib" / "cmake")
        rmdir(self, self.package_path / "lib" / "pkgconfig")

    def package_info(self):
        # self.cpp_info.set_property("cpe", "")  # No CPE (yet)?
        self.cpp_info.set_property("purl", f"pkg:github/ebiggers/libdeflate@v{self.version}")
        self.cpp_info.set_property("cmake_find_mode", "both")
        self.cpp_info.set_property("cmake_file_name", "libdeflate")
        self.cpp_info.set_property("cmake_target_name", "libdeflate::libdeflate_shared")
        self.cpp_info.set_property("cmake_target_aliases", ["libdeflate::libdeflate"])
        self.cpp_info.libs = collect_libs(self)
        if self.settings.os == "Linux":
            self.cpp_info.system_libs.append("pthread")
