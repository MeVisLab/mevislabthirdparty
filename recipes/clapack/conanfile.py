from conan import ConanFile
from conan.tools.cmake import CMake, CMakeToolchain, cmake_layout
from conan.tools.files import get, patch
from conan.tools.files import copy

required_conan_version = ">=2.2.2"


class ConanRecipe(ConanFile):
    name = "clapack"
    version = "3.2.1"
    homepage = "http://www.netlib.org/clapack"
    description = "CLAPACK, a C translation of the FORTRAN77 LAPACK linear algebra libraries"
    license = "BSD-3-Clause"
    settings = "os", "arch", "compiler", "build_type"
    package_type = "static-library"
    exports_sources = "patches/*.patch"

    def configure(self):
        self.settings.rm_safe("compiler.libcxx")
        self.settings.rm_safe("compiler.cppstd")

    def layout(self):
        cmake_layout(self, src_folder="src")

    def source(self):
        get(self,
            url=f"http://www.netlib.org/clapack/clapack-{self.version}-CMAKE.tgz",
            sha256="0b3f782bc24845d85f36bafbff0f2f1384dc72df730fda4e7924ec1a70baca5a",
            destination=self.source_folder,
            strip_root=True)
        patch(self, patch_file="patches/001-add_missing_stdio_include.patch")
        patch(self, patch_file="patches/002-disable_testing.patch")
        patch(self, patch_file="patches/003-no_math_defines.patch")

    def generate(self):
        tc = CMakeToolchain(self)
        tc.preprocessor_definitions["BUILD_CLAPACK"] = 1
        tc.variables["CMAKE_DEBUG_POSTFIX"] = "_d"
        tc.variables["BUILD_SHARED_LIBS"] = False
        tc.variables['CMAKE_POSITION_INDEPENDENT_CODE'] = True
        tc.variables["CMAKE_C_VISIBILITY_PRESET"] = "hidden"
        tc.cache_variables["CMAKE_POLICY_DEFAULT_CMP0063"] = "NEW"  # don't ignore CMAKE_C_VISIBILITY_PRESET for static libs
        tc.generate()

    def build(self):
        cmake = CMake(self)
        cmake.configure()
        cmake.build()

    def package(self):
        copy(self, pattern="COPYING", src=self.source_path, dst=self.package_path / "licenses")
        copy(self, pattern="*.h", src=self.source_path / "INCLUDE", dst=self.package_path / "include")
        copy(self, pattern="*.lib", src=self.build_path, dst=self.package_path / "lib", keep_path=False)
        copy(self, pattern="*.dll", src=self.build_path, dst=self.package_path / "bin", keep_path=False)
        copy(self, pattern="*.pdb", src=self.build_path, dst=self.package_path / "bin",
             keep_path=False, excludes="*vc???.pdb")
        copy(self, pattern="*.so*", src=self.build_path, dst=self.package_path / "lib", keep_path=False)
        copy(self, pattern="*.dylib", src=self.build_path, dst=self.package_path / "lib", keep_path=False)
        copy(self, pattern="*.a", src=self.build_path, dst=self.package_path / "lib", keep_path=False)

    def package_info(self):
        self.cpp_info.set_property("cmake_find_mode", "both")
        self.cpp_info.set_property("cmake_file_name", "CLAPACK")
        self.cpp_info.set_property("cmake_target_name", "CLAPACK::CLAPACK")
        self.cpp_info.set_property("pkg_config_name", "clapack")
        self.cpp_info.libs = ['lapack', 'blas']
        self.cpp_info.libs.append('libf2c' if self.settings.os == "Windows" else 'f2c')
        if self.settings.build_type == "Debug":
            self.cpp_info.libs = [x + "_d" for x in self.cpp_info.libs]
        if self.settings.os == "Linux":
            self.cpp_info.system_libs.append("m")
