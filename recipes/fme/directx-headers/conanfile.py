from conan import ConanFile
from conan.tools.files import copy, get, rmdir, collect_libs
from conan.tools.cmake import CMake, CMakeDeps, CMakeToolchain, cmake_layout
from conan.errors import ConanInvalidConfiguration
import os

required_conan_version = ">=2.32.0"


class ConanRecipe(ConanFile):
    name = "directx-headers"
    version = "1.619.5"
    homepage = "https://github.com/microsoft/DirectX-Headers"
    description = "Official DirectX headers for using D3D12"
    license = "MIT"
    package_type = "static-library"
    settings = "os", "arch", "compiler", "build_type"

    def configure(self):
        if self.settings.os != "Windows":
            raise ConanInvalidConfiguration(f"{self.name} is only supported on Windows")

    def validate(self):
        if self.settings.os != "Windows":
            raise ConanInvalidConfiguration(f"{self.name} is only supported on Windows")

    def source(self):
        get(
            self,
            sha256="24a0b7d8079a2dbbc90753c0d8bc812040d052acce2302e69a97c5d873b313b8",
            url=f"https://github.com/microsoft/DirectX-Headers/archive/refs/tags/v{self.version}.tar.gz",
            strip_root=True,
        )

    def layout(self):
        cmake_layout(self, src_folder="src")

    def generate(self):
        deps = CMakeDeps(self)
        deps.generate()
        tc = CMakeToolchain(self)
        tc.variables["CMAKE_DEBUG_POSTFIX"] = "_d"
        tc.variables["BUILD_SHARED_LIBS"] = False
        tc.variables["DXHEADERS_INSTALL"] = True
        tc.variables["DXHEADERS_BUILD_TEST"] = False
        tc.variables["DXHEADERS_BUILD_GOOGLE_TEST"] = False
        tc.variables["CMAKE_POSITION_INDEPENDENT_CODE"] = True
        tc.generate()

    def build(self):
        cmake = CMake(self)
        cmake.configure()
        cmake.build()

    def package(self):
        cmake = CMake(self)
        cmake.install()
        copy(self, "LICENSE", src=self.source_folder, dst=os.path.join(self.package_folder, "licenses"))
        rmdir(self, os.path.join(self.package_folder, "share"))
        rmdir(self, os.path.join(self.package_folder, "lib", "pkgconfig"))

    def package_info(self):
        # self.cpp_info.set_property("cpe", "")  # No CPE (yet)?
        self.cpp_info.set_property("purl", f"pkg:github/microsoft/DirectX-Headers@v{self.version}")
        self.cpp_info.libs = collect_libs(self)
        self.cpp_info.set_property("cmake_file_name", "DirectX-Headers")
        self.cpp_info.set_property("cmake_target_name", "Microsoft::DirectX-Headers")
        self.cpp_info.set_property("pkg_config_name", "DirectX-Headers")
        self.cpp_info.system_libs.extend(["dxcore", "d3d12"])
