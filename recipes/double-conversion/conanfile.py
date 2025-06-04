from conan import ConanFile
from conan.tools.cmake import CMake, CMakeToolchain, cmake_layout
from conan.tools.files import collect_libs
from conan.tools.files import copy, get, rmdir

required_conan_version = ">=2.2.2"


class ConanRecipe(ConanFile):
    name = "double-conversion"
    version = "3.3.1"
    homepage = "https://github.com/google/double-conversion"
    description = "Efficient binary-decimal and decimal-binary conversion routines for IEEE doubles"
    license = "BSD-3-Clause"
    package_type = "shared-library"
    settings = "os", "arch", "compiler", "build_type"

    def layout(self):
        cmake_layout(self, src_folder="src")

    def source(self):
        get(
            self,
            sha256="fe54901055c71302dcdc5c3ccbe265a6c191978f3761ce1414d0895d6b0ea90e",
            url=f"https://github.com/google/double-conversion/archive/v{self.version}.tar.gz",
            strip_root=True,
        )

    def generate(self):
        tc = CMakeToolchain(self)
        tc.variables["CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS"] = True
        tc.variables["CMAKE_POSITION_INDEPENDENT_CODE"] = True
        tc.variables["BUILD_SHARED_LIBS"] = True
        tc.variables["CMAKE_DEBUG_POSTFIX"] = "_d"
        tc.generate()

    def build(self):
        cmake = CMake(self)
        cmake.configure()
        cmake.build()

    def package(self):
        copy(self, "LICENSE", src=self.source_folder, dst=self.package_path / "licenses")
        copy(self, "*.pdb", src=self.build_path, dst=self.package_path / "bin", keep_path=False, excludes="*vc???.pdb")
        cmake = CMake(self)
        cmake.install()
        rmdir(self, self.package_path / "lib" / "cmake")

    def package_info(self):
        # self.cpp_info.set_property("cpe", "")  # No CPE yet?
        self.cpp_info.set_property("purl", f"pkg:github/google/double-conversion@v{self.version}")
        self.cpp_info.set_property("cmake_file_name", "double-conversion")
        self.cpp_info.set_property("cmake_target_name", "double-conversion::double-conversion")
        self.cpp_info.libs = collect_libs(self)
        self.cpp_info.includedirs.append("include/double-conversion")
