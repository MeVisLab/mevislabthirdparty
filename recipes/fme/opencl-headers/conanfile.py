from conan import ConanFile
from conan.tools.files import copy, get

required_conan_version = ">=2.2.2"


class ConanRecipe(ConanFile):
    name = "opencl-headers"
    version = "2023.12.14"
    homepage = "https://github.com/KhronosGroup/OpenCL-Headers"
    description = "C language headers for the OpenCL API"
    license = "Apache-2.0"
    package_type = "header-library"
    settings = "os", "arch", "compiler", "build_type"

    def configure(self):
        self.settings.rm_safe("compiler.libcxx")
        self.settings.rm_safe("compiler.cppstd")

    def source(self):
        get(self,
            sha256="407d5e109a70ec1b6cd3380ce357c21e3d3651a91caae6d0d8e1719c69a1791d",
            url=f"https://github.com/KhronosGroup/OpenCL-Headers/archive/refs/tags/v{self.version}.tar.gz",
            strip_root=True
            )

    def package(self):
        copy(self, "*", src=self.source_path / "CL", dst=self.package_path / "include" / "CL")
        copy(self, "LICENSE", src=self.source_path, dst=self.package_path / "licenses")

    def package_info(self):
        self.cpp_info.set_property("cmake_file_name", "OpenCL")
        self.cpp_info.set_property("cmake_target_name", "OpenCL::OpenCL")
        self.cpp_info.set_property("cmake_config_version_compat", "AnyNewerVersion")
        self.cpp_info.set_property("mevislab_prosdk_exclude", True)
