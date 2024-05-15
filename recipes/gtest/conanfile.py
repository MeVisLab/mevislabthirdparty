from conan import ConanFile
from conan.tools.cmake import CMake, CMakeToolchain, cmake_layout
from conan.tools.files import collect_libs, copy, get, rmdir
from conan.tools.microsoft import is_msvc

required_conan_version = ">=2.2.2"


class ConanRecipe(ConanFile):
    name = "gtest"
    display_name = "GTest"
    version = "1.14.0"
    homepage = "https://github.com/google/googletest"
    description = "Google Testing and Mocking Framework"
    license = "BSD-3-Clause"
    package_type = "shared-library"
    settings = "os", "arch", "compiler", "build_type"

    def layout(self):
        cmake_layout(self, src_folder="src")

    def source(self):
        get(self,
            url=f"https://github.com/google/googletest/archive/refs/tags/v{self.version}.tar.gz",
            sha256="8ad598c73ad796e0d8280b082cebd82a630d73e73cd3c70057938a6501bba5d7",
            destination=self.source_folder,
            strip_root=True)

    def generate(self):
        tc = CMakeToolchain(self)
        if is_msvc(self) and "MD" in str(self.settings.compiler.runtime):
            tc.variables["gtest_force_shared_crt"] = "ON"
        tc.variables["CMAKE_DEBUG_POSTFIX"] = '_d'
        tc.variables["BUILD_SHARED_LIBS"] = True
        tc.variables["CMAKE_POSITION_INDEPENDENT_CODE"] = True
        tc.generate()

    def build(self):
        cmake = CMake(self)
        cmake.configure()
        cmake.build()

    def package(self):
        copy(self, "LICENSE", src=self.source_path, dst=self.package_path / "licenses")
        copy(self, "*.pdb", src=self.build_path, dst=self.package_path / "bin", keep_path=False)
        cmake = CMake(self)
        cmake.install()
        rmdir(self, self.package_path / "lib" / "pkgconfig")
        rmdir(self, self.package_path / "lib" / "cmake")
        for pdb in (self.package_path / "lib").glob("*.pdb"):
            pdb.unlink()

    def package_info(self):
        self.cpp_info.set_property("cmake_find_mode", "config")
        self.cpp_info.set_property("cmake_file_name", "GTest")
        self.cpp_info.set_property("cmake_target_name", "GTest::GTest")
        self.cpp_info.set_property("pkg_config_name", "gtest")
        self.cpp_info.libs = collect_libs(self)

        for lib in collect_libs(self):
            if lib.endswith(f".{self.version}"):
                continue

            comp = lib[:-2] if self.settings.build_type == "Debug" else lib
            if not comp.endswith("_main"):
                comp += "_lib"
            self.cpp_info.components[comp].libs = [lib]
            self.cpp_info.components[comp].set_property("cmake_target_name", f"GTest::{comp}")
