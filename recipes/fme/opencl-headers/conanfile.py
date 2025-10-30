from conan import ConanFile
from conan.tools.files import copy, get
from pathlib import Path

required_conan_version = ">=2.2.2"


class ConanRecipe(ConanFile):
    name = "opencl-headers"
    version = "2025.07.22"
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
            sha256="98f0a3ea26b4aec051e533cb1750db2998ab8e82eda97269ed6efe66ec94a240",
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
        self.cpp_info.set_property("mevislab_prosdk_exclude", True)
