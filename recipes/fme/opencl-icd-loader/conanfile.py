from conan import ConanFile
from conan.tools.cmake import CMakeToolchain, CMakeDeps, CMake, cmake_layout
from conan.tools.files import copy, rmdir, collect_libs, get
from pathlib import Path

required_conan_version = ">=2.2.2"


class ConanRecipe(ConanFile):
    name = "opencl-icd-loader"
    version = "2024.05.08"
    homepage = "https://github.com/KhronosGroup/OpenCL-ICD-Loader"
    description = "OpenCL ICD Loader"
    license = "Apache-2.0"
    package_type = "shared-library"
    settings = "os", "arch", "compiler", "build_type"

    def layout(self):
        self.folders.source = "src"

    def configure(self):
        self.settings.rm_safe("compiler.libcxx")
        self.settings.rm_safe("compiler.cppstd")

    def requirements(self):
        self.requires("opencl-headers/[>=2021.06.30]")

    def layout(self):
        cmake_layout(self, src_folder="src")

    def source(self):
        get(
            self,
            sha256="eb2c9fde125ffc58f418d62ad83131ba686cccedcb390cc7e6bb81cc5ef2bd4f",
            url=f"https://github.com/KhronosGroup/OpenCL-ICD-Loader/archive/refs/tags/v{self.version}.tar.gz",
            strip_root=True,
        )

    def generate(self):
        tc = CMakeToolchain(self)
        tc.variables["CMAKE_DEBUG_POSTFIX"] = "_d"
        tc.variables["BUILD_SHARED_LIBS"] = True
        header_info = self.dependencies["opencl-headers"].cpp_info
        tc.variables["OPENCL_ICD_LOADER_HEADERS_DIR"] = ";".join([hi.replace("\\", "/") for hi in header_info.includedirs])
        tc.generate()

        cd = CMakeDeps(self)
        cd.generate()

    def build(self):
        cmake = CMake(self)
        cmake.configure()
        cmake.build()

    def package(self):
        cmake = CMake(self)
        cmake.install()

        rmdir(self, Path(self.package_folder) / "share")
        rmdir(self, Path(self.package_folder) / "lib" / "pkgconfig")
        copy(self, "LICENSE", src=self.source_folder, dst=Path(self.package_folder) / "licenses")
        copy(
            self,
            "*.pdb",
            src=self.build_folder,
            dst=Path(self.package_folder) / "bin",
            keep_path=False,
            excludes=["*/vc???.pdb", "test/*", "*test.pdb"],
        )

    def package_info(self):
        self.cpp_info.set_property("cmake_file_name", "OpenCLICDLoader")
        self.cpp_info.set_property("cmake_target_name", "OpenCLICDLoader::OpenCLICDLoader")
        self.cpp_info.set_property("cmake_config_version_compat", "AnyNewerVersion")
        self.cpp_info.set_property("mevislab_prosdk_exclude", True)
        self.cpp_info.includedirs.clear()
        self.cpp_info.libs = collect_libs(self)
