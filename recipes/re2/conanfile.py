from conan import ConanFile
from conan.tools.cmake import CMake, CMakeDeps, CMakeToolchain, cmake_layout
from conan.tools.files import copy, get, rmdir, collect_libs
import os

required_conan_version = ">=2.2.2"


class ConanRecipe(ConanFile):
    name = "re2"
    version = "20240702"
    homepage = "https://github.com/google/re2"
    description = "Fast, safe, thread-friendly regular expression library"
    license = "BSD-3-Clause"
    package_type = "shared-library"
    settings = "os", "arch", "compiler", "build_type"

    def requirements(self):
        self.requires("abseil/[>=20230802.1]", transitive_headers=True)

    def layout(self):
        cmake_layout(self, src_folder="src")

    def source(self):
        year, month, day = self.version[0:4], self.version[4:6], self.version[6:]
        get(
            self,
            sha256="eb2df807c781601c14a260a507a5bb4509be1ee626024cb45acbd57cb9d4032b",
            url=f"https://github.com/google/re2/archive/{year}-{month}-{day}.tar.gz",
            strip_root=True,
        )

    def generate(self):
        deps = CMakeDeps(self)
        deps.generate()
        tc = CMakeToolchain(self)
        tc.variables["CMAKE_DEBUG_POSTFIX"] = "_d"
        tc.variables["BUILD_SHARED_LIBS"] = True
        tc.variables["RE2_BUILD_TESTING"] = False
        tc.variables["CMAKE_INSTALL_RPATH"] = "$ORIGIN;$ORIGIN/../lib"
        tc.generate()

    def build(self):
        cmake = CMake(self)
        cmake.configure()
        cmake.build()

    def package(self):
        copy(self, "LICENSE", src=self.source_folder, dst=os.path.join(self.package_folder, "licenses"))
        copy(self, "*.pdb", src=self.build_folder, dst=os.path.join(self.package_folder, "bin"), keep_path=False)
        cmake = CMake(self)
        cmake.install()
        rmdir(self, os.path.join(self.package_folder, "lib", "cmake"))
        rmdir(self, os.path.join(self.package_folder, "lib", "pkgconfig"))

    def package_info(self):
        # self.cpp_info.set_property("cpe", "")  # No CPE (yet)?
        self.cpp_info.set_property("base_purl", "github/google/re2")
        self.cpp_info.set_property("cmake_file_name", "re2")
        self.cpp_info.set_property("cmake_target_name", "re2::re2")
        self.cpp_info.set_property("cmake_config_version_compat", "AnyNewerVersion")
        self.cpp_info.set_property("pkg_config_name", "re2")
        self.cpp_info.libs = collect_libs(self)
        if self.settings.os == "Linux":
            self.cpp_info.system_libs = ["m", "pthread"]
