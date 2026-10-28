from conan import ConanFile
from conan.tools.files import copy, get, rmdir, patch
from conan.tools.cmake import CMake, CMakeToolchain, cmake_layout
import os
import shutil

required_conan_version = ">=2.32.0"


class ConanRecipe(ConanFile):
    name = "cutlass"
    version = "4.8.0"
    homepage = "https://github.com/NVIDIA/cutlass"
    description = "CUDA Templates for High-Performance Linear Algebra"
    license = "BSD-3-Clause"
    package_type = "header-library"
    settings = "os", "arch", "compiler", "build_type"
    exports_sources = "patches/*"

    mlab_hooks = {
        "folders.skip": True,
    }

    def layout(self):
        cmake_layout(self, src_folder="src")

    def package_id(self):
        self.info.clear()

    def source(self):
        get(
            self,
            sha256="b7bb2ba0473a5a5d699c62e5feb42caa11cb109ec58ba82ca458af9cd139f39b",
            url=f"https://github.com/NVIDIA/cutlass/archive/refs/tags/v{self.version}.tar.gz",
            strip_root=True,
        )
        patch(self, patch_file="patches/001-find_cudnn.patch")
        patch(self, patch_file="patches/002-msvc_error.patch")

    def generate(self):
        tc = CMakeToolchain(self, generator="Ninja")
        tc.cache_variables["CUTLASS_REVISION"] = f"v{self.version}"
        tc.cache_variables["CUTLASS_ENABLE_HEADERS_ONLY"] = True
        tc.cache_variables["CUTLASS_ENABLE_TOOLS"] = True
        tc.cache_variables["CUTLASS_ENABLE_LIBRARY"] = False
        tc.cache_variables["CUTLASS_ENABLE_PROFILER"] = False
        tc.cache_variables["CUTLASS_ENABLE_PERFORMANCE"] = False
        tc.cache_variables["CUTLASS_ENABLE_TESTS"] = False
        tc.cache_variables["CUTLASS_ENABLE_GTEST_UNIT_TESTS"] = False
        tc.cache_variables["CUTLASS_ENABLE_CUBLAS"] = True
        tc.cache_variables["CUTLASS_ENABLE_CUDNN"] = True
        nvcc = os.environ.get("CUDACXX", shutil.which("nvcc"))
        if nvcc:
            tc.variables["CMAKE_CUDA_COMPILER"] = nvcc.replace("\\", "/")

        tc.generate()

    def build(self):
        cmake = CMake(self)
        cmake.configure()
        cmake.build()

    def package(self):
        copy(self, "LICENSE.txt", self.source_folder, os.path.join(self.package_folder, "licenses"))
        cmake = CMake(self)
        cmake.install()
        rmdir(self, os.path.join(self.package_folder, "lib"))
        rmdir(self, os.path.join(self.package_folder, "test"))
        # onnxruntime needs one of the examples, so we must package them
        copy(self, "examples/**", self.source_folder, self.package_folder)

    def package_info(self):
        # self.cpp_info.set_property("cpe", "")  # No CPE (yet)?
        self.cpp_info.set_property("purl", f"pkg:github/NVIDIA/cutlass@v{self.version}")
        self.cpp_info.set_property("cmake_file_name", "NvidiaCutlass")
        self.cpp_info.set_property("cmake_target_name", "nvidia::cutlass::cutlass")
        self.cpp_info.includedirs.append("examples")
        self.cpp_info.bindirs = []
        self.cpp_info.libdirs = []
