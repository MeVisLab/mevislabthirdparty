import glob
import os
import shutil
import textwrap
from io import StringIO

from conan import ConanFile
from conan.errors import ConanException, ConanInvalidConfiguration
from conan.tools.cmake import CMake, CMakeDeps, CMakeToolchain, cmake_layout
from conan.tools.files import copy, get, rename, rm, rmdir, save, patch

required_conan_version = ">=2.32.0"


class ConanRecipe(ConanFile):
    name = "onnxruntime"
    version = "1.30.0"
    homepage = "https://onnxruntime.ai"
    description = "cross-platform, high performance ML inferencing and training accelerator"
    license = "MIT"
    package_type = "shared-library"
    settings = "os", "arch", "compiler", "build_type"
    options = {"cuda_architectures": ["ANY"]}
    default_options = {"cuda_architectures": "61-real;75-real;80-real;86-real;89-real;90-real;90-virtual"}
    exports_sources = ["patches/*", "requirements.txt"]
    python_requires = "python_package/[>=1.0.0]"
    python_requires_extend = "python_package.PythonPackageBase"
    mlab_hooks = {
        "dependencies.system_libs": [
            "libcuda.so.*",
            "libcurand.so.*",
            "libcufft.so.*",
            "libcudnn.so.*",
            "libcublas.so.*",
            "libcudart.so.*",
            "libcublasLt.so.*",
            "libnvrtc.so.*",
        ],
    }

    @property
    def has_requirements_txt(self):
        return True

    @property
    def package_site_packages_path(self):
        return os.path.join(self.package_folder, self.relative_site_package_folder())

    def layout(self):
        cmake_layout(self, src_folder="src")

    def requirements(self):
        self.requires("abseil/[>=20240722.0]")
        self.requires("boost/[>=1.86.0]")
        self.requires("cpuinfo/[>=20251119]")
        self.requires("cudnn_frontend/[>=1.16.1]", visible=False)
        self.requires("cutlass/[>=4.3.0]")
        self.requires("date/[>=3.0.3]")
        self.requires("dlpack/[>=1.1]")
        self.requires("eigen/[>=3.4.0]")
        self.requires("flatbuffers/[>=24.0.0]")
        self.requires("ms-gsl/[>=4.1.0]")
        self.requires("nlohmann_json/[>=3.11.3]")
        self.requires("numpy/[>=2.0.0]")
        self.requires("onnx/[>=1.16.0]")
        self.requires("protobuf/[>=3.21]")
        self.requires("python/[>=3.13]")
        self.requires("re2/[>-20240702]")
        self.requires("safeint/[>=3.0.28]")
        if self.settings.os != "Windows":
            self.requires("deep_gemm/[>=26.07]", visible=False)
            self.requires("nsync/[>=1.29.2]")
        else:
            self.requires("wil/[>=1.0.260126.7]")
            self.requires("directx-headers/[>=1.618.2]")

    def source(self):
        get(
            self,
            sha256="f6681ecbddf53898adf0cc9e8e9e84657485b84d2eca3c8aa353de6d7dd417ef",
            url=f"https://github.com/microsoft/onnxruntime/archive/refs/tags/v{self.version}.tar.gz",
            strip_root=True,
        )
        patch(self, patch_file="patches/001-remove_ciso646.patch")
        patch(self, patch_file="patches/002-msvc_permissive.patch")
        patch(self, patch_file="patches/003-cpuinfo_linkage.patch")
        patch(self, patch_file="patches/004-xnnpack_linkage.patch")
        patch(self, patch_file="patches/005-external_lib_include_dir.patch")
        patch(self, patch_file="patches/006-use_external_cudnn_frontend.patch")
        patch(self, patch_file="patches/007-no_warn_as_error.patch")
        patch(self, patch_file="patches/008-provider_debug_suffix.patch")

        content = textwrap.dedent("""
            # Replacement for onnxruntime_external_deps.cmake

            # since we have the opportunity here, let's turn off the most annoying msvc compiler warnings here
            add_compile_options($<$<AND:$<OR:$<COMPILE_LANGUAGE:C>,$<COMPILE_LANGUAGE:CXX>>,$<C_COMPILER_ID:MSVC>>:/wd4018>)
            add_compile_options($<$<AND:$<OR:$<COMPILE_LANGUAGE:C>,$<COMPILE_LANGUAGE:CXX>>,$<C_COMPILER_ID:MSVC>>:/wd4100>)
            add_compile_options($<$<AND:$<OR:$<COMPILE_LANGUAGE:C>,$<COMPILE_LANGUAGE:CXX>>,$<C_COMPILER_ID:MSVC>>:/wd4127>)
            add_compile_options($<$<AND:$<OR:$<COMPILE_LANGUAGE:C>,$<COMPILE_LANGUAGE:CXX>>,$<C_COMPILER_ID:MSVC>>:/wd4267>)
            add_compile_options($<$<AND:$<OR:$<COMPILE_LANGUAGE:C>,$<COMPILE_LANGUAGE:CXX>>,$<C_COMPILER_ID:MSVC>>:/wd4458>)
            add_compile_options($<$<AND:$<OR:$<COMPILE_LANGUAGE:C>,$<COMPILE_LANGUAGE:CXX>>,$<C_COMPILER_ID:MSVC>>:/wd4702>)
            add_compile_options($<$<AND:$<OR:$<COMPILE_LANGUAGE:C>,$<COMPILE_LANGUAGE:CXX>>,$<C_COMPILER_ID:MSVC>>:/wd5055>)

            # and also the CUDA (nvcc) warning about deprecated architectures
            add_compile_options($<$<COMPILE_LANGUAGE:CUDA>:-Wno-deprecated-gpu-targets>)

            # add /bigobj when compiling C and C++ code with MSVC (needed in v1.23.2, check again later)
            add_compile_options(
                $<$<AND:$<CXX_COMPILER_ID:MSVC>,$<COMPILE_LANGUAGE:CXX>>:/bigobj>
                $<$<AND:$<C_COMPILER_ID:MSVC>,$<COMPILE_LANGUAGE:C>>:/bigobj>
            )

            if(MSVC)
                # Enable preprocessor conformance mode
                # This is the default in C++20 and later, but it appears to be lost when invoked through nvcc
                string(APPEND CMAKE_C_FLAGS   " /Zc:preprocessor")
                string(APPEND CMAKE_CXX_FLAGS " /Zc:preprocessor")
                string(APPEND CMAKE_CUDA_FLAGS " -Xcompiler=/Zc:preprocessor")
            endif()

            find_package(absl REQUIRED CONFIG)
            include_directories(${absl_INCLUDE_DIRS})
            set(ABSEIL_LIBS abseil::abseil)

            find_package(re2 REQUIRED CONFIG)
            find_package(flatbuffers REQUIRED CONFIG)

            find_package(protobuf REQUIRED CONFIG)
            set(ONNX_CUSTOM_PROTOC_EXECUTABLE protoc)
            set(PROTOC_EXECUTABLE protoc)

            find_package(date REQUIRED CONFIG)
            include_directories(${date_INCLUDE_DIRS})
            add_library(date_interface ALIAS date::date)

            find_package(Boost REQUIRED CONFIG)
            find_package(nlohmann_json REQUIRED CONFIG)

            find_package(cpuinfo REQUIRED CONFIG)
            set(CPUINFO_SUPPORTED ${cpuinfo_FOUND})
            add_library(cpuinfo ALIAS cpuinfo::cpuinfo)

            if (NOT WIN32)
                find_package(nsync REQUIRED CONFIG)
                include_directories(${nsync_INCLUDE_DIRS})
                add_library(nsync_cpp INTERFACE)
            endif()

            find_package(Microsoft.GSL REQUIRED CONFIG)
            include_directories(${Microsoft.GSL_INCLUDE_DIRS})

            find_package(safeint REQUIRED CONFIG)
            include_directories(${safeint_INCLUDE_DIRS})
            add_library(safeint_interface ALIAS safeint::safeint)

            find_package(Eigen3 REQUIRED CONFIG)
            set(eigen_INCLUDE_DIRS ${Eigen3_INCLUDE_DIRS})

            find_package(ONNX REQUIRED CONFIG)

            find_package(dlpack REQUIRED CONFIG)

            execute_process(
                COMMAND ${Python_EXECUTABLE} -m pybind11 --cmakedir
                OUTPUT_VARIABLE pybind11_DIR
                OUTPUT_STRIP_TRAILING_WHITESPACE
                COMMAND_ERROR_IS_FATAL ANY
            )
            find_package(pybind11 REQUIRED CONFIG)
            set(pybind11_lib pybind11::module)

            if(WIN32)
                find_package(wil REQUIRED CONFIG)
                include_directories(${wil_INCLUDE_DIRS})

                find_package(DirectX-Headers REQUIRED CONFIG)
                include_directories(${DirectX-Headers_INCLUDE_DIRS})
            endif()

            set(onnxruntime_EXTERNAL_LIBRARIES
                nlohmann_json::nlohmann_json
                onnx
                onnx_proto
                protobuf::libprotobuf
                re2::re2
                Boost::mp11
                safeint_interface
                flatbuffers::flatbuffers
                Microsoft.GSL::GSL
                abseil::abseil
                date::date
                cpuinfo::cpuinfo
                Eigen3::Eigen
            )

            if(WIN32)
                list(APPEND onnxruntime_EXTERNAL_LIBRARIES WIL::WIL)
                list(APPEND onnxruntime_EXTERNAL_LIBRARIES Microsoft::DirectX-Headers)
            endif()

            file(TO_NATIVE_PATH ${CMAKE_BINARY_DIR} ORT_BINARY_DIR)
            file(TO_NATIVE_PATH ${PROJECT_SOURCE_DIR} ORT_SOURCE_DIR)
        """)
        save(self, os.path.join(self.source_folder, "cmake", "external", "onnxruntime_external_deps.cmake"), content)

    def generate(self):
        nvcc = os.environ.get("CUDACXX") or shutil.which("nvcc")
        if nvcc:
            output = StringIO()
            self.run(f'"{nvcc}" --list-gpu-arch', stdout=output, quiet=True)

            supported = output.getvalue().split()
            requested = str(self.options.cuda_architectures).split(";")
            if unsupported := [a for a in requested if f"compute_{a.split('-', 1)[0]}" not in supported]:
                output = StringIO()
                self.run(f'"{nvcc}" --version', stdout=output, quiet=True)
                cuda_version = output.getvalue().strip().splitlines()[-2]
                usable = ";".join(a for a in requested if a not in unsupported)
                msg = f"CUDA architectures {', '.join(unsupported)} are not supported by {nvcc} ({cuda_version}).\n"
                self.output.warning(msg)
                self.output.info(f"Supported architectures: {' '.join(supported)}\n")
                self.output.info(
                    f'Build with a supported list, for example: conan create recipes/fme/onnxruntime -o "onnxruntime/*:cuda_architectures={usable}"'
                )
                raise ConanInvalidConfiguration(msg)

        super().generate()

        deps = CMakeDeps(self)
        deps.set_property("boost::headers", "cmake_target_name", "Boost::mp11")
        deps.set_property("python", "cmake_find_mode", "none")
        deps.generate()

        if not self.dependencies["flatbuffers"].cpp_info.bindirs:
            raise ConanException("flatbuffers package has no bindirs!")
        else:
            flatc = os.path.join(
                self.dependencies["flatbuffers"].cpp_info.bindirs[0],
                ("flatc.exe" if self.settings.os == "Windows" else "flatc"),
            )
            compile_schema = os.path.join(
                self.source_folder, "onnxruntime", "core", "flatbuffers", "schema", "compile_schema.py"
            )
            self.run(f'"{self.py_command}" {compile_schema} -f "{flatc}"')
            compile_schema = os.path.join(
                self.source_folder, "onnxruntime", "lora", "adapter_format", "compile_schema.py"
            )
            self.run(f'"{self.py_command}" {compile_schema} -f "{flatc}"')

        tc = CMakeToolchain(self, generator="Ninja")
        tc.variables["CMAKE_CXX_STANDARD"] = 20
        tc.variables["CMAKE_CUDA_STANDARD"] = 20
        tc.variables["CMAKE_CUDA_ARCHITECTURES"] = str(self.options.cuda_architectures)
        tc.variables["CMAKE_DEBUG_POSTFIX"] = "_d"
        tc.variables["CMAKE_CXX_SCAN_FOR_MODULES"] = False
        tc.variables["CMAKE_POSITION_INDEPENDENT_CODE"] = True
        tc.variables["FETCHCONTENT_FULLY_DISCONNECTED"] = True  # disable downloading dependencies
        tc.variables["CMAKE_DISABLE_FIND_PACKAGE_Git"] = True
        tc.variables["CMAKE_DISABLE_FIND_PACKAGE_patch"] = True
        tc.variables["Python_EXECUTABLE"] = self.py_command.replace("\\", "/")
        tc.variables["Python_ROOT_DIR"] = self.mlab_build_path.replace("\\", "/")
        if self.settings.os == "Windows":
            python_libs = os.path.join(self.mlab_build_path, "libs").replace("\\", "/")
            tc.variables["CMAKE_MODULE_LINKER_FLAGS_INIT"] = f"/LIBPATH:{python_libs}"
        numpy_include_dir = self.dependencies["numpy"].cpp_info.includedirs[0]
        tc.variables["Python_NumPy_INCLUDE_DIR"] = numpy_include_dir.replace("\\", "/")
        tc.variables["BUILD_SHARED_LIBS"] = True
        tc.variables["BUILD_TESTING"] = False
        tc.variables["onnxruntime_QUICK_BUILD"] = True
        tc.variables["onnxruntime_ENABLE_PYTHON"] = True
        tc.variables["onnxruntime_BUILD_SHARED_LIB"] = True
        tc.variables["onnxruntime_BUILD_OPSCHEMA_LIB"] = False
        tc.variables["onnxruntime_BUILD_UNIT_TESTS"] = False
        tc.variables["onnxruntime_USE_VCPKG"] = True
        tc.variables["onnxruntime_USE_AVX"] = True
        tc.variables["onnxruntime_USE_AVX2"] = True
        tc.variables["onnxruntime_USE_AVX512"] = False
        tc.variables["onnxruntime_USE_CUDA"] = True
        tc.variables["onnxruntime_USE_CUDA_NHWC_OPS"] = True
        tc.variables["onnxruntime_NVCC_THREADS"] = 1
        tc.variables["onnxruntime_DISABLE_CONTRIB_OPS"] = False
        tc.variables["onnxruntime_USE_FLASH_ATTENTION"] = False
        tc.variables["onnxruntime_DISABLE_RTTI"] = False
        tc.variables["onnxruntime_DISABLE_EXCEPTIONS"] = False
        tc.variables["onnxruntime_ARMNN_RELU_USE_CPU"] = False
        tc.variables["onnxruntime_ARMNN_BN_USE_CPU"] = False
        tc.variables["onnxruntime_ENABLE_CPU_FP16_OPS"] = False
        tc.variables["onnxruntime_ENABLE_EAGER_MODE"] = False
        tc.variables["onnxruntime_ENABLE_LAZY_TENSOR"] = False
        tc.variables["onnxruntime_ENABLE_CUDA_EP_INTERNAL_TESTS"] = False
        tc.variables["onnxruntime_USE_NEURAL_SPEED"] = False
        tc.variables["onnxruntime_USE_MEMORY_EFFICIENT_ATTENTION"] = True
        tc.preprocessor_definitions["_SILENCE_ALL_CXX23_DEPRECATION_WARNINGS"] = "1"
        if nvcc:
            tc.variables["CMAKE_CUDA_COMPILER"] = nvcc.replace("\\", "/")
        tc.generate()

    def build(self):
        with self.install_packages(os.path.join(os.path.dirname(self.source_folder), "requirements.txt")):
            cmake = CMake(self)
            cmake.configure(
                build_script_folder=os.path.join(self.source_folder, "cmake"),
                cli_args=["--compile-no-warning-as-error"],
            )
            cmake.build()

    def package(self):
        copy(self, "LICENSE", src=self.source_folder, dst=os.path.join(self.package_folder, "licenses"))
        cmake = CMake(self)
        cmake.install()
        rmdir(self, os.path.join(self.package_folder, "lib", "pkgconfig"))
        rmdir(self, os.path.join(self.package_folder, "lib", "cmake"))
        if self.settings.os == "Windows":
            # onnxruntime_providers_cuda.dll somehow ends up in the wrong directory:
            copy(
                self,
                "onnxruntime_providers_*.dll",
                os.path.join(self.package_folder, "lib"),
                os.path.join(self.package_folder, "bin"),
            )
            rm(
                self,
                "onnxruntime_providers_*.dll",
                os.path.join(self.package_folder, "lib"),
            )

        python_package_folder = os.path.join(self.package_site_packages_path, "onnxruntime")
        copy(
            self,
            "*",
            src=os.path.join(self.build_folder, "onnxruntime"),
            dst=python_package_folder,
            excludes="*__pycache__*",
        )
        capi_folder = os.path.join(python_package_folder, "capi")
        if self.settings.build_type == "Debug" and self.settings.os != "Windows":
            for module in glob.glob(os.path.join(capi_folder, "onnxruntime_pybind11_state_d.*")):
                rename(self, module, module.replace("onnxruntime_pybind11_state_d.", "onnxruntime_pybind11_state."))
        if self.settings.os == "Linux":
            patchelf = shutil.which("patchelf")
            if not patchelf:
                raise ConanException("patchelf could not be found")
            for library in glob.glob(os.path.join(capi_folder, "*.so*")):
                if not os.path.islink(library):
                    self.run(f"{patchelf} --set-rpath '$ORIGIN' {library}")
        save(
            self,
            os.path.join(python_package_folder, "capi", "build_and_package_info.py"),
            f"package_name = 'onnxruntime-gpu'\n__version__ = '{self.version}'\n",
        )

    def package_info(self):
        self.cpp_info.set_property("purl", f"pkg:github/microsoft/onnxruntime@v{self.version}")
        self.cpp_info.set_property("cmake_file_name", "onnxruntime")
        self.cpp_info.set_property("cmake_target_name", "onnxruntime::onnxruntime")
        self.cpp_info.set_property("pkg_config_name", "onnxruntime")
        self.buildenv_info.append_path("PYTHONPATH", self.package_site_packages_path)
        self.runenv_info.append_path("PYTHONPATH", self.package_site_packages_path)
        suffix = "_d" if self.settings.build_type == "Debug" else ""
        self.cpp_info.libs = [f"onnxruntime{suffix}"]
        if self.settings.os == "Linux":
            self.cpp_info.system_libs.extend(["m", "pthread"])
        if self.settings.os == "Windows":
            self.cpp_info.system_libs.append("shlwapi")
