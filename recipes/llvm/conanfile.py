from conan import ConanFile
from conan.errors import ConanInvalidConfiguration
from conan.tools.cmake import CMake, CMakeDeps, CMakeToolchain, cmake_layout
from conan.tools.files import copy, rmdir, get, collect_libs
import os

required_conan_version = ">=2.2.2"


class ConanRecipe(ConanFile):
    name = "llvm"
    version = "19.1.7"
    license = "Apache-2.0"
    homepage = "https://llvm.org"
    description = "Low Level Virtual Machine"
    settings = "os", "arch", "compiler", "build_type"
    package_type = "shared-library"
    exports_sources = "CMakeLists.txt"

    mlab_hooks = {"test_package.skip": True}

    def validate_build(self):
        if self.settings.build_type != "Release":
            raise ConanInvalidConfiguration(f"{self.name} is built in release mode only.")

    def package_id(self):
        self.info.settings.rm_safe("build_type")

    def configure(self):
        self.settings.compiler.rm_safe("libcxx")
        self.settings.compiler.rm_safe("cppstd")

    def layout(self):
        cmake_layout(self, src_folder="src")

    def source(self):
        get(
            self,
            sha256="82401fea7b79d0078043f7598b835284d6650a75b93e64b6f761ea7b63097501",
            url=f"https://github.com/llvm/llvm-project/releases/download/llvmorg-{self.version}/llvm-project-{self.version}.src.tar.xz",
            strip_root=True,
        )

    def generate(self):
        deps = CMakeDeps(self)
        deps.generate()
        tc = CMakeToolchain(self, generator="Ninja")
        tc.variables["CMAKE_DEBUG_POSTFIX"] = "_d"
        # see https://llvm.org/docs/CMake.html#options-and-variables
        tc.variables["CMAKE_VS_PLATFORM_TOOLSET_HOST_ARCHITECTURE"] = "x64"
        tc.variables["CMAKE_DISABLE_FIND_PACKAGE_git"] = True
        tc.variables["CMAKE_DISABLE_FIND_PACKAGE_Git"] = True
        tc.variables["CMAKE_DISABLE_FIND_PACKAGE_OCaml"] = True
        tc.variables["LLVM_TARGETS_TO_BUILD"] = "X86"
        tc.variables["LLVM_BUILD_EXAMPLES"] = False
        tc.variables["LLVM_INCLUDE_EXAMPLES"] = False
        tc.variables["LLVM_BUILD_TESTS"] = False
        tc.variables["LLVM_INCLUDE_TESTS"] = False
        tc.variables["LLVM_BUILD_BENCHMARKS"] = False
        tc.variables["LLVM_INCLUDE_BENCHMARKS"] = False
        tc.variables["LLVM_ENABLE_UNWIND_TABLES"] = False
        tc.variables["LLVM_ENABLE_LIBPFM"] = False
        tc.variables["LLVM_ENABLE_Z3_SOLVER"] = False
        tc.variables["LLVM_ENABLE_TERMINFO"] = False
        tc.variables["LLVM_ENABLE_CURL"] = False
        tc.variables["LLVM_ENABLE_HTTPLIB"] = False
        tc.variables["LLVM_ENABLE_LIBEDIT"] = False
        tc.variables["LLVM_ENABLE_DOXYGEN"] = False
        tc.variables["LLVM_ENABLE_FFI"] = False
        tc.variables["LLVM_ENABLE_DIA_SDK"] = False
        tc.variables["LLVM_ENABLE_BINDINGS"] = False
        tc.variables["LLVM_ENABLE_ZSTD"] = False
        tc.variables["LLVM_ENABLE_ZLIB"] = False
        tc.variables["LLVM_ENABLE_LIBXML2"] = False
        tc.generate()

    def build(self):
        cmake = CMake(self)
        cmake.configure(build_script_folder="llvm")
        cmake.build()

    def package(self):
        copy(self, "LICENSE.TXT", src=self.source_folder, dst=os.path.join(self.package_folder, "licenses"), keep_path=False)
        cmake = CMake(self)
        cmake.install()
        rmdir(self, os.path.join(self.package_folder, "share"))
        rmdir(self, os.path.join(self.package_folder, "lib", "cmake"))

    def package_info(self):
        self.cpp_info.set_property("cpe", "cpe:2.3:a:llvm:llvm:*:*:*:*:*:*:*:*")
        self.cpp_info.set_property("purl", f"pkg:github/llvm/llvm-project@llvmorg-{self.version}")
        self.cpp_info.set_property("cmake_find_mode", "both")
        self.cpp_info.set_property("cmake_file_name", "LLVM")
        self.cpp_info.set_property("cmake_target_name", "LLVM::LLVM")
        self.cpp_info.libs = collect_libs(self)
