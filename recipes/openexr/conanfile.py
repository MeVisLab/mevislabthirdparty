from conan import ConanFile
from conan.tools.cmake import CMake, CMakeDeps, CMakeToolchain, cmake_layout
from conan.tools.files import collect_libs, replace_in_file
from conan.tools.files import get, copy, rmdir

required_conan_version = ">=2.2.2"


class ConanRecipe(ConanFile):
    name = "openexr"
    version = "3.2.4"
    homepage = "http://www.openexr.com"
    description = "OpenEXR is a high dynamic-range (HDR) image file format developed by Industrial Light & Magic for use in computer imaging applications"
    license = "BSD-3-Clause"
    package_type = "shared-library"
    settings = "os", "arch", "compiler", "build_type"

    def layout(self):
        cmake_layout(self, src_folder="src")

    def requirements(self):
        self.requires("libdeflate/[>=1.19]")
        self.requires("zlib/[>=1.2.11]")
        self.requires("imath/[>=3.1.3]", transitive_headers=True)

    def source(self):
        get(
            self,
            sha256="81e6518f2c4656fdeaf18a018f135e96a96e7f66dbe1c1f05860dd94772176cc",
            url=f"https://github.com/AcademySoftwareFoundation/openexr/archive/v{self.version}.tar.gz",
            strip_root=True,
        )
        replace_in_file(
            self,
            self.source_path / "cmake" / "OpenEXRSetup.cmake",
            "set(CMAKE_INSTALL_RPATH_USE_LINK_PATH TRUE",
            "set(CMAKE_INSTALL_RPATH_USE_LINK_PATH FALSE",
        )

    def generate(self):
        tc = CMakeToolchain(self)
        tc.variables["BUILD_SHARED_LIBS"] = True
        tc.variables["OPENEXR_INSTALL_PKG_CONFIG"] = False
        tc.variables["OPENEXR_BUILD_EXAMPLES"] = False
        tc.variables["OPENEXR_INSTALL_EXAMPLES"] = False
        tc.variables["OPENEXR_BUILD_PYTHON"] = False
        tc.variables["OPENEXR_TEST_LIBRARIES"] = False
        tc.variables["OPENEXR_TEST_TOOLS"] = False
        tc.variables["OPENEXR_TEST_PYTHON"] = False
        tc.variables["CMAKE_INSTALL_RPATH"] = "$ORIGIN;$ORIGIN/../lib"
        tc.variables["OPENEXR_LIB_SUFFIX"] = ""
        tc.generate()
        tc = CMakeDeps(self)
        tc.generate()

    def build(self):
        cmake = CMake(self)
        cmake.configure()
        cmake.build()

    def package(self):
        cmake = CMake(self)
        cmake.install()
        copy(self, "LICENSE.md", src=self.source_path, dst=self.package_path / "licenses")
        copy(
            self,
            "*.pdb",
            src=self.build_path / "bin",
            dst=self.package_path / "bin",
            keep_path=False,
        )
        rmdir(self, self.package_path / "lib" / "cmake")
        rmdir(self, self.package_path / "lib" / "pkgconfig")
        rmdir(self, self.package_path / "share")

    def package_info(self):
        self.cpp_info.set_property("cmake_find_mode", "both")
        self.cpp_info.set_property("cmake_file_name", "OpenEXR")
        self.cpp_info.set_property("cmake_target_name", "OpenEXR::OpenEXR")
        self.cpp_info.set_property("pkg_config_name", "OpenEXR")
        self.cpp_info.libs = collect_libs(self)

        if self.settings.os == "Linux":
            self.cpp_info.system_libs = ["pthread"]
