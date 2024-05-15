from conan import ConanFile
from conan.tools.cmake import CMake, CMakeDeps, CMakeToolchain, cmake_layout
from conan.tools.env import VirtualRunEnv
from conan.tools.files import collect_libs, copy, get, patch

required_conan_version = ">=2.2.2"


class ConanRecipe(ConanFile):
    name = "singleapplication"
    # The latest version (3.4.0) has the license slightly changed and no needed new features.
    # In case we want to use a newer version, we also have to handle the new license.
    version = "3.3.4"
    homepage = "https://github.com/itay-grudev/SingleApplication"
    description = "Replacement of QtSingleApplication for Qt 5 and Qt 6"
    license = "MIT"
    package_type = "static-library"
    settings = "os", "arch", "compiler", "build_type"
    exports_sources = "patches/*.patch"

    def source(self):
        get(self,
            sha256="492ec764ac81e808ec8688e8a374a02eaa3fc4c69528adbc84188d9ab1214d3f",
            url=f"https://github.com/itay-grudev/SingleApplication/archive/refs/tags/v{self.version}.zip",
            strip_root=True)
        patch(self, patch_file="patches/001-QCoreApplication.patch")

    def layout(self):
        cmake_layout(self, src_folder="src")

    def requirements(self):
        self.requires("qtbase/[>=6.5]")

    def generate(self):
        env = VirtualRunEnv(self)
        env.generate(scope="build")
        deps = CMakeDeps(self)
        deps.generate()
        tc = CMakeToolchain(self)
        tc.variables["CMAKE_DEBUG_POSTFIX"] = "_d"
        tc.variables["BUILD_SHARED_LIBS"] = False
        tc.variables["CMAKE_POSITION_INDEPENDENT_CODE"] = True
        tc.variables["QT_DEFAULT_MAJOR_VERSION"] = 6
        tc.variables["QAPPLICATION_CLASS"] = "QApplication"
        tc.generate()

    def build(self):
        cmake = CMake(self)
        cmake.configure()
        cmake.build()

    def package(self):
        copy(self, "LICENSE", src=self.source_path, dst=self.package_path / "licenses")
        copy(self, "*.lib", src=self.build_path, dst=self.package_path / "lib", keep_path=False)
        copy(self, "*.a", src=self.build_path, dst=self.package_path / "lib", keep_path=False)
        copy(self, "*.pdb", src=self.build_path, dst=self.package_path / "bin", keep_path=False)
        copy(self, "SingleApplication", src=self.source_path, dst=self.package_path / "include", keep_path=False)
        copy(self, "singleapplication.h", src=self.source_path, dst=self.package_path / "include", keep_path=False)

    def package_info(self):
        self.cpp_info.set_property("cmake_file_name", "SingleApplication")
        self.cpp_info.set_property("cmake_target_name", "SingleApplication::SingleApplication")
        self.cpp_info.libs = collect_libs(self)
