import os

from conan import ConanFile
from conan.errors import ConanInvalidConfiguration
from conan.tools.files import copy, get, rmdir
from conan.tools.layout import basic_layout

required_conan_version = ">=2.32.0"


class ConanRecipe(ConanFile):
    name = "deep_gemm"
    version = "26.07"
    homepage = "https://github.com/deepseek-ai/DeepGEMM"
    description = "Clean and efficient FP8 GEMM kernels with fine-grained scaling"
    license = "MIT"
    package_type = "header-library"
    settings = "os", "arch", "compiler", "build_type"

    # upstream doesn't create tags or releases — only release commits 🤨
    _commit = "559d79fb6994a58b8a15b4b93bf13ccc16edf247"

    def validate(self):
        if self.settings.os == "Windows":
            raise ConanInvalidConfiguration(f"{self.name} is not supported on Windows")

    def package_id(self):
        self.info.clear()

    def layout(self):
        basic_layout(self, src_folder="src")

    def requirements(self):
        self.requires("cutlass/[>=4.7.0]", transitive_headers=True)

    def source(self):
        get(
            self,
            sha256="8a6c67b6f74d4a3a242c4dad7714d147797b2ecc5d55c52925bbdf6155207d2c",
            url=f"https://github.com/deepseek-ai/DeepGEMM/archive/{self._commit}.tar.gz",
            strip_root=True,
        )
        rmdir(self, os.path.join(self.source_folder, "third-party"))

    def package(self):
        copy(self, "LICENSE", src=self.source_folder, dst=os.path.join(self.package_folder, "licenses"))
        copy(
            self,
            "*.cuh",
            src=os.path.join(self.source_folder, "deep_gemm", "include"),
            dst=os.path.join(self.package_folder, "include"),
        )

    def package_info(self):
        # self.cpp_info.set_property("cpe", "")  # No CPE (yet)?
        self.cpp_info.set_property("purl", f"pkg:github/deepseek-ai/DeepGEMM@{self._commit}")
        self.cpp_info.set_property("cmake_find_mode", "both")
        self.cpp_info.set_property("cmake_file_name", "deep_gemm")
        self.cpp_info.set_property("cmake_target_name", "deep_gemm::deep_gemm")
        self.cpp_info.bindirs = []
        self.cpp_info.libdirs = []
