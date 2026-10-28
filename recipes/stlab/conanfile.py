from conan import ConanFile
from conan.tools.cmake import CMake, CMakeToolchain, cmake_layout
from conan.tools.files import get, copy, rmdir, patch
import os

required_conan_version = ">=2.32.0"


class ConanRecipe(ConanFile):
    name = "stlab"
    version = "2.3.0"
    homepage = "https://stlab.cc"
    description = "Software Technology Lab (stlab) libraries"
    license = "BSL-1.0"
    package_type = "shared-library"
    exports_sources = "patches/*.patch"
    settings = "os", "arch", "compiler", "build_type"

    def source(self):
        get(
            self,
            url=f"https://github.com/stlab/stlab/archive/v{self.version}.tar.gz",
            sha256="22ec971dff4b4ffdc331bc31d243b50583e17a78abc284021bb22064cba8aa9c",
            strip_root=True,
        )
        patch(self, patch_file="patches/001-add_missing_include.patch")
        patch(self, patch_file="patches/002-decouple-from-cpm.patch")

    def layout(self):
        cmake_layout(self, src_folder="src")

    def generate(self):
        tc = CMakeToolchain(self)
        tc.variables["STLAB_VERSION"] = self.version
        # Must be a shared library: stlab defines the priority_task_system singleton and
        # the pre_exit registry in its own translation units. A static build would give every
        # consuming shared library its own thread pool again, which is stlab issue #519.
        tc.variables["BUILD_SHARED_LIBS"] = True
        tc.variables["BUILD_TESTING"] = "OFF"
        tc.variables["CMAKE_DEBUG_POSTFIX"] = "_d"
        tc.variables["CMAKE_POSITION_INDEPENDENT_CODE"] = True
        tc.variables["CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS"] = True
        tc.variables["CMAKE_INSTALL_BINDIR"] = "bin"
        tc.variables["CMAKE_INSTALL_LIBDIR"] = "lib"
        tc.variables["CMAKE_INSTALL_INCLUDEDIR"] = "include"
        tc.variables["CMAKE_DISABLE_FIND_PACKAGE_Qt5"] = True
        tc.variables["CMAKE_DISABLE_FIND_PACKAGE_Qt6"] = True
        tc.variables["CMAKE_DISABLE_FIND_PACKAGE_libdispatch"] = True
        tc.variables["CMAKE_INSTALL_SYSTEM_RUNTIME_LIBS_SKIP"] = True
        tc.generate()

    def build(self):
        cmake = CMake(self)
        cmake.configure()
        cmake.build()

    def package(self):
        copy(self, "LICENSE", src=self.source_folder, dst=os.path.join(self.package_folder, "licenses"))
        cmake = CMake(self)
        cmake.install()
        rmdir(self, os.path.join(self.package_folder, "share"))

    def package_info(self):
        # self.cpp_info.set_property("cpe", "")  # No CPE (yet)?
        self.cpp_info.set_property("purl", f"pkg:github/stlab/stlab@v{self.version}")
        self.cpp_info.set_property("cmake_find_mode", "both")
        self.cpp_info.set_property("cmake_file_name", "stlab")
        self.cpp_info.set_property("cmake_target_name", "stlab::stlab")
        self.cpp_info.set_property("pkg_config_name", "stlab")
        suffix = "_d" if self.settings.build_type == "Debug" else ""
        self.cpp_info.libs = [f"stlab{suffix}"]

        if self.settings.os == "Linux":
            self.cpp_info.system_libs.extend(["pthread"])
