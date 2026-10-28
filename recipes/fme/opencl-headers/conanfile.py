from conan import ConanFile
from conan.tools.files import copy, get
from pathlib import Path

required_conan_version = ">=2.32.0"


class ConanRecipe(ConanFile):
    name = "opencl-headers"
    version = "2026.05.29"
    homepage = "https://github.com/KhronosGroup/OpenCL-Headers"
    description = "C language headers for the OpenCL API"
    license = "Apache-2.0"
    package_type = "header-library"
    settings = "os", "arch", "compiler", "build_type"

    def layout(self):
        self.folders.source = "src"

    def configure(self):
        self.settings.rm_safe("compiler.libcxx")
        self.settings.rm_safe("compiler.cppstd")

    def source(self):
        get(
            self,
            sha256="d9e6c48357de5002da11ce45de600e0c3ffe6ab4f628a3b9fe2b38603161658a",
            url=f"https://github.com/KhronosGroup/OpenCL-Headers/archive/refs/tags/v{self.version}.tar.gz",
            strip_root=True,
        )

    def package(self):
        copy(self, "*", src=Path(self.source_folder) / "CL", dst=Path(self.package_folder) / "include" / "CL")
        copy(self, "LICENSE", src=self.source_folder, dst=Path(self.package_folder) / "licenses")

    def package_info(self):
        # self.cpp_info.set_property("cpe", "")  # No CPE (yet)?
        self.cpp_info.set_property("purl", f"pkg:github/KhronosGroup/OpenCL-Headers@v{self.version}")
        self.cpp_info.set_property("cmake_file_name", "OpenCL")
        self.cpp_info.set_property("cmake_target_name", "OpenCL::OpenCL")
        self.cpp_info.set_property("cmake_config_version_compat", "AnyNewerVersion")
