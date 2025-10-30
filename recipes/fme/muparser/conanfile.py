from conan import ConanFile
from conan.tools.cmake import CMakeToolchain, CMake, cmake_layout
from conan.tools.files import copy, rmdir, collect_libs, get, patch
import os

required_conan_version = ">=2.2.2"


class ConanRecipe(ConanFile):
    name = "muparser"
    version = "2.3.5"
    homepage = "https://github.com/beltoforion/muparser"
    description = "fast math parser library"
    license = "BSD-2-Clause"
    settings = "os", "arch", "compiler", "build_type"
    package_type = "shared-library"
    exports_sources = ["patches/*"]

    def layout(self):
        cmake_layout(self, src_folder="src")

    def generate(self):
        tc = CMakeToolchain(self)
        tc.variables["CMAKE_DEBUG_POSTFIX"] = "_d"
        tc.variables["ENABLE_SAMPLES"] = False
        tc.variables["ENABLE_OPENMP"] = False
        tc.generate()

    def source(self):
        get(
            self,
            sha256="20b43cc68c655665db83711906f01b20c51909368973116dfc8d7b3c4ddb5dd4",
            url=f"https://github.com/beltoforion/muparser/archive/refs/tags/v{self.version}.tar.gz",
            strip_root=True,
        )
        patch(self, patch_file="patches/001-disable_unicode.patch")

    def build(self):
        cmake = CMake(self)
        cmake.configure()
        cmake.build()

    def package(self):
        cmake = CMake(self)
        cmake.install()

        copy(self, "LICENSE", src=self.source_folder, dst=os.path.join(self.package_folder, "licenses"))
        copy(
            self,
            "*/muparserd.pdb",
            src=self.build_folder,
            dst=os.path.join(self.package_folder, "bin"),
            keep_path=False,
        )
        rmdir(self, os.path.join(self.package_folder, "lib", "cmake"))
        rmdir(self, os.path.join(self.package_folder, "lib", "pkgconfig"))

    def package_info(self):
        # self.cpp_info.set_property("cpe", "")  # No CPE yet?
        self.cpp_info.set_property("purl", f"pkg:github/beltoforion/muparser@v{self.version}")
        self.cpp_info.set_property("display_name", "muParser")
        self.cpp_info.set_property("mevislab_prosdk_exclude", True)
        self.cpp_info.libs = collect_libs(self)
