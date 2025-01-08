from conan import ConanFile
from conan.tools.cmake import CMake, CMakeDeps, CMakeToolchain, cmake_layout
from conan.tools.env import VirtualRunEnv
from conan.tools.files import collect_libs, copy, get, patch

required_conan_version = ">=2.2.2"


class ConanRecipe(ConanFile):
    name = "qtservice"
    version = "2022.10.24"
    homepage = "https://code.qt.io/cgit/qt-solutions/qt-solutions.git/tree/qtservice"
    description = "Qt library for developing Windows services and Unix daemons"
    license = "BSD-3-Clause"
    package_type = "shared-library"
    settings = "os", "arch", "compiler", "build_type"
    exports_sources = "patches/*.patch", "CMakeLists.txt"

    def layout(self):
        cmake_layout(self, src_folder="src")

    def requirements(self):
        self.requires("qtbase/[>=6.5]")

    def source(self):
        get(self, sha256="195f1fcabe80e711199517f20b916d603ea260b1a2d7abcc8ce980af67f3cc96",
            url="https://github.com/qtproject/qt-solutions/archive/777e95ba69952f11eaec0adfb0cb987fabcdecb3.zip",
            strip_root=True)
        patch(self, patch_file="patches/001-adapt_to_qt6.patch")

    def generate(self):
        env = VirtualRunEnv(self)
        env.generate(scope="build")

        deps = CMakeDeps(self)
        deps.generate()
        tc = CMakeToolchain(self)
        tc.variables["CMAKE_DEBUG_POSTFIX"] = "_d"
        tc.variables["BUILD_SHARED_LIBS"] = True
        tc.variables["CMAKE_INSTALL_RPATH"] = "$ORIGIN;$ORIGIN/../lib"
        tc.variables["CMAKE_POSITION_INDEPENDENT_CODE"] = True
        tc.generate()

    def build(self):
        cmake = CMake(self)
        cmake.configure(build_script_folder=self.source_path.parent)
        cmake.build()

    def package(self):
        copy(self, "BSD-3-Clause.txt", src=self.source_path / "LICENSES", dst=self.package_path / "licenses")
        cmake = CMake(self)
        cmake.install()

    def package_info(self):
        # self.cpp_info.set_property("cpe", "")  # No CPE (yet)?
        self.cpp_info.set_property("base_purl", "github/qtproject/qt-solutions")
        self.cpp_info.set_property("cmake_file_name", "QtService")
        self.cpp_info.set_property("cmake_target_name", "QtService::QtService")
        self.cpp_info.set_property("cmake_config_version_compat", "AnyNewerVersion")
        self.cpp_info.set_property("pkg_config_name", "QtService")
        self.cpp_info.includedirs = ["include", "include/QtService"]
        self.cpp_info.libs = collect_libs(self)
