import re
import os
from conan import ConanFile
from conan.tools.cmake import CMake, CMakeToolchain, cmake_layout
from conan.tools.files import rmdir, copy, load, get

required_conan_version = ">=2.2.2"


class ConanRecipe(ConanFile):
    name = "onetbb"
    version = "2021.13.0"
    license = "Apache-2.0"
    homepage = "https://oneapi-src.github.io/oneTBB/"
    description = (
        "oneAPI Threading Building Blocks (oneTBB) lets you easily write parallel C++"
        " programs that take full advantage of multicore performance, that are portable, composable"
        " and have future-proof scalability."
    )
    package_type = "shared-library"
    settings = "os", "arch", "compiler", "build_type"

    def layout(self):
        cmake_layout(self, src_folder="src")

    def source(self):
        get(
            self,
            sha256="3ad5dd08954b39d113dc5b3f8a8dc6dc1fd5250032b7c491eb07aed5c94133e1",
            url=f"https://github.com/oneapi-src/oneTBB/archive/refs/tags/v{self.version}.tar.gz",
            strip_root=True,
        )

    def generate(self):
        tc = CMakeToolchain(self)
        tc.variables["TBB_TEST"] = False
        tc.variables["TBB_EXAMPLES"] = False
        tc.variables["TBB_STRICT"] = False
        tc.variables["TBB_DISABLE_HWLOC_AUTOMATIC_SEARCH"] = True
        tc.variables["CMAKE_INSTALL_RPATH"] = "$ORIGIN;$ORIGIN/../lib"
        tc.generate()

    def build(self):
        cmake = CMake(self)
        cmake.configure()
        cmake.build()

    def package(self):
        cmake = CMake(self)
        cmake.install()
        copy(self, "LICENSE.txt", src=self.source_folder, dst=os.path.join(self.package_folder, "licenses"))
        copy(
            self,
            "*.pdb",
            src=self.build_folder,
            dst=os.path.join(self.package_folder, "bin"),
            keep_path=False,
            excludes=["src/*", "CMakeFiles/*"],
        )
        rmdir(self, os.path.join(self.package_folder, "share"))
        rmdir(self, os.path.join(self.package_folder, "lib", "cmake"))
        rmdir(self, os.path.join(self.package_folder, "lib", "pkgconfig"))
        rmdir(self, os.path.join(self.package_folder, "share"))

    def package_info(self):
        suffix = "_debug" if self.settings.build_type == "Debug" else ""
        self.cpp_info.set_property("cmake_file_name", "TBB")
        self.cpp_info.set_property("cmake_config_version_compat", "AnyNewerVersion")
        tbb = self.cpp_info.components["libtbb"]
        tbb.set_property("cmake_target_name", "TBB::tbb")
        tbb.libs = [f"tbb{suffix}"]
        if self.settings.os == "Windows":
            version_info = load(self, os.path.join(self.package_folder, "include", "oneapi", "tbb", "version.h"))
            binary_version = re.sub(
                r".*" + re.escape("#define __TBB_BINARY_VERSION ") + r"(\d+).*",
                r"\1",
                version_info,
                flags=re.MULTILINE | re.DOTALL,
            )
            tbb.libs.append(f"tbb{binary_version}{suffix}")
        elif self.settings.os == "Linux":
            tbb.system_libs = ["m", "dl", "rt", "pthread"]

        tbb_malloc = self.cpp_info.components["tbbmalloc"]
        tbb_malloc.libs = [f"tbbmalloc{suffix}"]
        if self.settings.os == "Linux":
            tbb_malloc.system_libs = ["dl", "pthread"]
        tbb_malloc.set_property("cmake_target_name", "TBB::tbbmalloc")

        tbbproxy = self.cpp_info.components["tbbmalloc_proxy"]
        tbbproxy.set_property("cmake_target_name", "TBB::tbbmalloc_proxy")
        tbbproxy.libs = [f"tbbmalloc_proxy{suffix}"]
        tbbproxy.requires = ["tbbmalloc"]
