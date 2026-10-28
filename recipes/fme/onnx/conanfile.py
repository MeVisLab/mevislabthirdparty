import os

from conan import ConanFile
from conan.tools.cmake import CMake, CMakeDeps, CMakeToolchain, cmake_layout
from conan.tools.files import copy, get, mkdir, patch, rename, rmdir, save
from conan.tools.env import VirtualBuildEnv

required_conan_version = ">=2.32.0"


class ConanRecipe(ConanFile):
    name = "onnx"
    version = "1.22.0"
    homepage = "https://onnx.ai"
    description = "open standard for machine learning interoperability"
    license = "Apache-2.0"
    package_type = "static-library"
    settings = "os", "arch", "compiler", "build_type"
    exports_sources = ["patches/*", "requirements.txt"]
    python_requires = "python_package/[>=1.0.0]"
    python_requires_extend = "python_package.PythonPackageBase"
    mlab_hooks = {"package_type.skip": True}

    @property
    def has_requirements_txt(self):
        return True

    @property
    def package_site_packages_path(self):
        return os.path.join(self.package_folder, self.relative_site_package_folder())

    def layout(self):
        cmake_layout(self, src_folder="src")

    def requirements(self):
        self.requires("protobuf/[>=3.21]", transitive_headers=True, transitive_libs=True, run=True)
        self.requires("python/[>=3.13]")
        self.requires("numpy/[>=1.23.2]")
        self.requires("ml_dtypes/[>=0.5.4]")

    def source(self):
        get(
            self,
            sha256="70bb8b25cf31ea9b1d9f94baacfdc8c4fa27a760f9a10f5d93881bc9eede5fbc",
            url=f"https://github.com/onnx/onnx/archive/v{self.version}.tar.gz",
            strip_root=True,
        )
        patch(self, patch_file="patches/001-fix_proto_generation_dependencies.patch")
        patch(self, patch_file="patches/002-register_schemas_in_python_module.patch")
        patch(self, patch_file="patches/003-disable_stable_abi_for_debug_python.patch")
        patch(self, patch_file="patches/004-no_debug_postfix_for_python_module.patch")

    def generate(self):
        super().generate()

        env = VirtualBuildEnv(self)
        env.generate()

        deps = CMakeDeps(self)
        deps.set_property("python", "cmake_find_mode", "none")
        deps.generate()

        python_executable = self.py_command.replace("\\", "/")
        python_root = self.mlab_build_path.replace("\\", "/")

        tc = CMakeToolchain(self, generator=(None if self.settings.os == "Windows" else "Ninja"))
        tc.variables["Python3_EXECUTABLE"] = python_executable
        tc.variables["Python3_ROOT_DIR"] = python_root
        tc.variables["Python_EXECUTABLE"] = python_executable
        tc.variables["Python_ROOT_DIR"] = python_root
        if self.settings.os == "Windows":
            tc.variables["CMAKE_MODULE_LINKER_FLAGS_INIT"] = f"/LIBPATH:{python_root}/libs"
        tc.variables["CMAKE_CXX_STANDARD"] = 20
        tc.variables["CMAKE_DEBUG_POSTFIX"] = "_d"
        tc.variables["BUILD_SHARED_LIBS"] = False
        tc.variables["CMAKE_POSITION_INDEPENDENT_CODE"] = True
        tc.variables["FETCHCONTENT_FULLY_DISCONNECTED"] = True
        tc.variables["CMAKE_DISABLE_FIND_PACKAGE_utf8_range"] = True
        # tc.variables["CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS"] = True

        tc.variables["ONNX_BUILD_SHARED_LIBS"] = False
        tc.variables["ONNX_USE_PROTOBUF_SHARED_LIBS"] = False
        tc.variables["ONNX_BUILD_PYTHON"] = True
        tc.variables["ONNX_GEN_PB_TYPE_STUBS"] = True
        tc.variables["ONNX_WERROR"] = False
        tc.variables["ONNX_COVERAGE"] = False
        tc.variables["ONNX_BUILD_TESTS"] = False
        tc.variables["ONNX_USE_LITE_PROTO"] = False
        tc.variables["ONNX_ML"] = True
        tc.variables["ONNX_VERIFY_PROTO3"] = True
        tc.variables["ONNX_DISABLE_STATIC_REGISTRATION"] = True
        tc.generate()

    def build(self):
        with self.install_packages(os.path.join(os.path.dirname(self.source_folder), "requirements.txt")):
            cmake = CMake(self)
            cmake.configure()
            cmake.build()

    def package(self):
        copy(self, "LICENSE", src=self.source_folder, dst=os.path.join(self.package_folder, "licenses"))
        cmake = CMake(self)
        cmake.install()
        rmdir(self, os.path.join(self.package_folder, "lib", "cmake"))

        python_package_folder = os.path.join(self.package_site_packages_path, "onnx")
        mkdir(self, self.package_site_packages_path)
        rename(self, os.path.join(self.package_folder, "onnx"), python_package_folder)
        copy(
            self,
            "*",
            src=os.path.join(self.source_folder, "onnx"),
            dst=python_package_folder,
            excludes=("*.cc", "*.h", "*.proto3", "*.md", "CMakeLists.txt", "*__pycache__*", "backend/test/data/*"),
        )
        save(
            self,
            os.path.join(self.package_site_packages_path, f"onnx-{self.version}.dist-info", "METADATA"),
            f"Metadata-Version: 2.1\nName: onnx\nVersion: {self.version}\n",
        )

    def package_info(self):
        dbg = "_d" if self.settings.build_type == "Debug" else ""
        self.cpp_info.set_property("cmake_file_name", "ONNX")
        self.cpp_info.ignored_requires = ["python", "numpy", "ml_dtypes"]
        self.buildenv_info.append_path("PYTHONPATH", self.package_site_packages_path)
        self.runenv_info.append_path("PYTHONPATH", self.package_site_packages_path)

        self.cpp_info.components["libonnx"].set_property("cmake_target_name", "onnx")
        self.cpp_info.components["libonnx"].libs = [f"onnx{dbg}"]
        self.cpp_info.components["libonnx"].defines = [
            "ONNX_NAMESPACE=onnx",
            "ONNX_ML=1",
            "__ONNX_DISABLE_STATIC_REGISTRATION",
            "__STDC_FORMAT_MACROS",
        ]
        self.cpp_info.components["libonnx"].requires = ["onnx_proto"]

        self.cpp_info.components["onnx_proto"].set_property("cmake_target_name", "onnx_proto")
        self.cpp_info.components["onnx_proto"].libs = [f"onnx_proto{dbg}"]
        self.cpp_info.components["onnx_proto"].defines = [
            "ONNX_NAMESPACE=onnx",
            "ONNX_ML=1",
            "__ONNX_DISABLE_STATIC_REGISTRATION",
        ]
        self.cpp_info.components["onnx_proto"].requires = ["protobuf::libprotobuf"]
