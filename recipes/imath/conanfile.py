from conan import ConanFile
from conan.tools.build import check_min_cppstd
from conan.tools.cmake import CMake, CMakeToolchain, cmake_layout
from conan.tools.files import collect_libs, copy, get, rmdir

required_conan_version = ">=2.2.2"


class ConanRecipe(ConanFile):
    name = "imath"
    version = "3.1.12"
    homepage = "https://imath.readthedocs.io"
    description = "Imath is a C++ and python library of 2D and 3D vector, matrix, and math operations for computer graphics"
    license = "BSD-3-Clause"
    package_type = "shared-library"
    settings = "os", "arch", "compiler", "build_type"

    def layout(self):
        cmake_layout(self, src_folder="src")

    def validate(self):
        if self.settings.compiler.get_safe("cppstd"):
            check_min_cppstd(self, 11)

    def source(self):
        get(
            self,
            sha256="8a1bc258f3149b5729c2f4f8ffd337c0e57f09096e4ba9784329f40c4a9035da",
            url=f"https://github.com/AcademySoftwareFoundation/Imath/archive/refs/tags/v{self.version}.tar.gz",
            strip_root=True,
        )

    def generate(self):
        tc = CMakeToolchain(self)
        tc.variables["BUILD_SHARED_LIBS"] = True
        tc.variables["IMATH_INSTALL_PKG_CONFIG"] = False
        tc.variables["IMATH_HALF_USE_LOOKUP_TABLE"] = True
        tc.variables["CMAKE_INSTALL_RPATH"] = "$ORIGIN;$ORIGIN/../lib"
        tc.generate()

    def build(self):
        cmake = CMake(self)
        cmake.configure()
        cmake.build()

    def package(self):
        copy(self, "LICENSE.md", src=self.source_path, dst=self.package_path / "licenses")
        copy(self, "*.pdb", src=self.build_path, dst=self.package_path / "bin", keep_path=False, excludes=["*vc???.pdb", "*Test.pdb"])
        cmake = CMake(self)
        cmake.install()
        rmdir(self, self.package_path / "cmake")
        rmdir(self, self.package_path / "lib" / "pkgconfig")
        rmdir(self, self.package_path / "lib" / "cmake")

    def package_info(self):
        # self.cpp_info.set_property("cpe", "")  # No CPE (yet)?
        self.cpp_info.set_property("base_purl", "github/AcademySoftwareFoundation/Imath")
        self.cpp_info.set_property("cmake_file_name", "Imath")
        self.cpp_info.set_property("cmake_target_name", "Imath::Imath")
        self.cpp_info.set_property("pkg_config_name", "Imath")

        imath_config = self.cpp_info.components["imath_config"]
        imath_config.set_property("cmake_target_name", "Imath::ImathConfig")
        imath_config.includedirs.append("include/Imath")

        imath_lib = self.cpp_info.components["imath_lib"]
        imath_lib.set_property("cmake_target_name", "Imath::Imath")
        imath_lib.set_property("pkg_config_name", "Imath")
        imath_lib.libs = collect_libs(self)
        imath_lib.requires = ["imath_config"]
        if self.settings.os == "Windows":
            imath_lib.defines.append("IMATH_DLL")
