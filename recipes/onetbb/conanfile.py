import re

from conan import ConanFile
from conan.tools.cmake import CMake, CMakeToolchain, cmake_layout
from conan.tools.files import rmdir, copy, load, get

required_conan_version = ">=2.2.2"


class ConanRecipe(ConanFile):
    name = "onetbb"
    version = "2021.12.0"
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
            sha256="c7bb7aa69c254d91b8f0041a71c5bcc3936acb64408a1719aec0b2b7639dd84f",
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
        copy(self, "LICENSE.txt", src=self.source_path, dst=self.package_path / "licenses")
        copy(self, "*.pdb", src=self.build_path, dst=self.package_path / "bin", keep_path=False, excludes=["src/*", "CMakeFiles/*"])
        rmdir(self, self.package_path / "share")
        rmdir(self, self.package_path / "lib" / "cmake")
        rmdir(self, self.package_path / "lib" / "pkgconfig")
        rmdir(self, self.package_path / "share")

    def package_info(self):
        suffix = "_debug" if self.settings.build_type == "Debug" else ""
        self.cpp_info.set_property("cmake_file_name", "TBB")
        self.cpp_info.set_property("cmake_config_version_compat", "AnyNewerVersion")
        tbb = self.cpp_info.components["libtbb"]
        tbb.set_property("cmake_target_name", "TBB::tbb")
        tbb.libs = [f"tbb{suffix}"]
        if self.settings.os == "Windows":
            version_info = load(self, self.package_path / "include" / "oneapi" / "tbb" / "version.h")
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
