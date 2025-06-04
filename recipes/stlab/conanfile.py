from conan import ConanFile
from conan.tools.cmake import CMake, CMakeToolchain, cmake_layout
from conan.tools.files import get, copy, rmdir, patch

required_conan_version = ">=2.2.2"


class ConanRecipe(ConanFile):
    name = "stlab"
    version = "1.7.1"
    homepage = "https://stlab.cc"
    description = "Software Technology Lab (stlab) libraries"
    license = "BSL-1.0"
    package_type = "header-library"
    exports_sources = "patches/*.patch"
    settings = "os", "arch", "compiler", "build_type"

    def package_id(self):
        del self.info.settings.build_type
        del self.info.settings.arch

    def source(self):
        get(self,
            url=f"https://github.com/stlab/libraries/archive/v{self.version}.tar.gz",
            sha256="0160b5f7be7d423100a9a8b205a99285b106dd438f806978028a82b9f01c6b64",
            strip_root=True
        )
        patch(self, patch_file="patches/001-add_missing_include.patch")

    def layout(self):
        cmake_layout(self, src_folder="src")

    def generate(self):
        tc = CMakeToolchain(self)
        tc.variables["CMAKE_CXX_STANDARD"] = "17"
        tc.variables["BUILD_TESTING"] = "OFF"
        tc.variables["CMAKE_DISABLE_FIND_PACKAGE_Qt5"] = True
        tc.variables["CMAKE_DISABLE_FIND_PACKAGE_Qt6"] = True
        tc.variables["CMAKE_DISABLE_FIND_PACKAGE_Boost"] = True
        tc.variables["STLAB_USE_BOOST_CPP17_SHIMS"] = False
        tc.variables["CMAKE_INSTALL_SYSTEM_RUNTIME_LIBS_SKIP"] = True
        tc.generate()

    def build(self):
        cmake = CMake(self)
        cmake.configure()

    def package(self):
        copy(self, "LICENSE", src=self.source_path, dst=self.package_path / "licenses")
        cmake = CMake(self)
        cmake.install()
        rmdir(self, self.package_path / 'share')

    def package_info(self):
        # self.cpp_info.set_property("cpe", "")  # No CPE (yet)?
        self.cpp_info.set_property("purl", f"pkg:github/stlab/libraries@v{self.version}")
        self.cpp_info.set_property("cmake_find_mode", "both")
        self.cpp_info.set_property("cmake_file_name", "stlab")
        self.cpp_info.set_property("cmake_target_name", "stlab::stlab")
        self.cpp_info.set_property("pkg_config_name", "stlab")
        self.cpp_info.bindirs = []
        self.cpp_info.libdirs = []

        if self.settings.os == "Linux":
            self.cpp_info.system_libs.extend(["pthread"])
