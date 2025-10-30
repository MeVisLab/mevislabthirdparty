from conan import ConanFile
from conan.tools.cmake import CMake, CMakeDeps, CMakeToolchain, cmake_layout
from conan.tools.env import VirtualRunEnv
from conan.tools.files import collect_libs, copy, get, patch
import os

required_conan_version = ">=2.2.2"


class ConanRecipe(ConanFile):
    name = "singleapplication"
    # The latest version (3.4.0) has the license slightly changed and no needed new features.
    # In case we want to use a newer version, we also have to handle the new license.
    version = "3.5.3"
    homepage = "https://github.com/itay-grudev/SingleApplication"
    description = "Replacement of QtSingleApplication for Qt 5 and Qt 6"
    license = "MIT"
    package_type = "static-library"
    settings = "os", "arch", "compiler", "build_type"
    exports_sources = "patches/*.patch"

    def source(self):
        get(
            self,
            sha256="ec8a68a24da974397668370a5a9d1fe281bfcbd7390ed1b14642921634f1881f",
            url=f"https://github.com/itay-grudev/SingleApplication/archive/refs/tags/v{self.version}.zip",
            strip_root=True,
        )
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
        copy(self, "LICENSE", src=self.source_folder, dst=os.path.join(self.package_folder, "licenses"))
        copy(self, "*.lib", src=self.build_folder, dst=os.path.join(self.package_folder, "lib"), keep_path=False)
        copy(self, "*.a", src=self.build_folder, dst=os.path.join(self.package_folder, "lib"), keep_path=False)
        copy(self, "*.pdb", src=self.build_folder, dst=os.path.join(self.package_folder, "bin"), keep_path=False)
        copy(
            self,
            "SingleApplication",
            src=self.source_folder,
            dst=os.path.join(self.package_folder, "include"),
            keep_path=False,
        )
        copy(
            self,
            "singleapplication.h",
            src=self.source_folder,
            dst=os.path.join(self.package_folder, "include"),
            keep_path=False,
        )

    def package_info(self):
        # self.cpp_info.set_property("cpe", "")  # No CPE (yet)?
        self.cpp_info.set_property("purl", f"pkg:github/itay-grudev/SingleApplication@v{self.version}")
        self.cpp_info.set_property("cmake_file_name", "SingleApplication")
        self.cpp_info.set_property("cmake_target_name", "SingleApplication::SingleApplication")
        self.cpp_info.libs = collect_libs(self)
