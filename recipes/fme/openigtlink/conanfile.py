from conan import ConanFile
from conan.tools.cmake import CMakeToolchain, CMake, cmake_layout
from conan.tools.files import rmdir, copy, get, collect_libs, patch

required_conan_version = ">=2.2.2"


class ConanRecipe(ConanFile):
    name = "openigtlink"
    version = "2023.06.13"
    homepage = "https://github.com/openigtlink/OpenIGTLink"
    description = "network communication library for image-guided therapy"
    license = "BSD-3-Clause"
    package_type = "shared-library"
    settings = "os", "arch", "compiler", "build_type"
    exports_sources = ["patches/*"]

    def layout(self):
        cmake_layout(self, src_folder="src")

    def source(self):
        get(
            self,
            sha256="b36507a85d6221afaed8b1ddf4bd8ad2adb489480ad9b758fc5aa2d37db1aadc",
            url=f"https://github.com/openigtlink/OpenIGTLink/archive/c512727425c2b7a594fabb9cd1fbfac512bf376e.zip",
            strip_root=True,
        )
        patch(self, patch_file="patches/001-minimum_cmake_version.patch")

    def generate(self):
        tc = CMakeToolchain(self)
        tc.variables["CMAKE_DEBUG_POSTFIX"] = "_d"
        tc.variables["BUILD_SHARED_LIBS"] = True
        tc.variables["BUILD_TESTING"] = False
        tc.variables["CMAKE_CXX_VISIBILITY_PRESET"] = "default"
        tc.variables["CMAKE_C_VISIBILITY_PRESET"] = "default"
        tc.variables["OpenIGTLink_INSTALL_LIB_DIR"] = "lib"
        tc.generate()

    def build(self):
        cmake = CMake(self)
        cmake.configure()
        cmake.build()

    def package(self):
        cmake = CMake(self)
        cmake.install()

        copy(self, "LICENSE.txt", src=self.source_path, dst=self.package_path / "licenses")
        copy(self, "*.pdb", src=self.build_path, dst=self.package_path / "bin", keep_path=False, excludes="*vc???.pdb")
        rmdir(self, self.package_path / "lib" / "cmake")

    def package_info(self):
        # self.cpp_info.set_property("cpe", "")  # No CPE (yet)?
        self.cpp_info.set_property("base_purl", "github/openigtlink/OpenIGTLink")
        self.cpp_info.set_property("display_name", "OpenIGTLink")
        self.cpp_info.set_property("cmake_config_version_compat", "AnyNewerVersion")
        self.cpp_info.set_property("mevislab_prosdk_exclude", True)
        self.cpp_info.libs = collect_libs(self)
        self.cpp_info.includedirs.append("include/igtl")
