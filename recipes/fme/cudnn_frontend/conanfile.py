from conan import ConanFile
from conan.tools.cmake import CMake, CMakeToolchain, cmake_layout
from conan.tools.files import get, copy, rmdir, save, patch
import shutil
import os

required_conan_version = ">=2.32.0"


class ConanRecipe(ConanFile):
    name = "cudnn_frontend"
    version = "1.30.0"
    homepage = "https://github.com/NVIDIA/cudnn-frontend"
    description = "cuDNN FrontEnd(FE) API is a C++ header-only library for the cuDNN C backend API"
    license = "MIT"
    package_type = "header-library"
    settings = "os", "arch", "compiler", "build_type"
    exports_sources = "patches/*.patch"

    def package_id(self):
        self.info.clear()

    def layout(self):
        cmake_layout(self, src_folder="src")

    def requirements(self):
        self.requires("nlohmann_json/[>=3.11.3]")

    def source(self):
        get(
            self,
            sha256="2e6a28661b91c0f43c2b24809750b480a93975bcf949c9715e540a7ab8575b31",
            url=f"https://github.com/NVIDIA/cudnn-frontend/archive/refs/tags/v{self.version}.tar.gz",
            strip_root=True,
        )
        patch(
            self,
            patch_file="patches/1562.patch",
            patch_type="bugfix",
            patch_description="fix load nvcuda.dll/cudart64_*.dll, see https://github.com/NVIDIA/cudnn-frontend/pull/1562",
        )

    def generate(self):
        tc = CMakeToolchain(self)
        tc.variables["CUDNN_FRONTEND_BUILD_SAMPLES"] = False
        tc.variables["CUDNN_FRONTEND_BUILD_TESTS"] = False
        nvcc = os.environ.get("CUDACXX", shutil.which("nvcc"))
        if nvcc:
            tc.variables["CMAKE_CUDA_COMPILER"] = nvcc.replace("\\", "/")
        tc.generate()

    def build(self):
        cmake = CMake(self)
        cmake.configure()
        cmake.build()

    def package(self):
        cmake = CMake(self)
        cmake.install()
        copy(self, "LICENSE.txt", src=self.source_folder, dst=os.path.join(self.package_folder, "licenses"))
        rmdir(self, os.path.join(self.package_folder, "lib"))
        self._cmake_module_file_write()

    def package_info(self):
        self.cpp_info.set_property("cmake_file_name", "cudnn_frontend")
        self.cpp_info.set_property("cmake_target_name", "cuDNN::FrontEnd")
        self.cpp_info.set_property("cmake_build_modules", [self._cmake_module_file])
        self.cpp_info.system_libs.append("CuDNN::CuDNN")
        self.cpp_info.bindirs = []
        self.cpp_info.libdirs = []

    @property
    def _cmake_module_file(self):
        return os.path.join("lib", "cmake", f"{self.name}-variables.cmake")

    def _cmake_module_file_write(self):
        file = os.path.join(self.package_folder, self._cmake_module_file)
        content = r"""
include(FindPackageHandleStandardArgs)

find_package(CUDAToolkit REQUIRED)

string(REGEX MATCH "^[0-9]+\\.[0-9]+" CUDA_SHORT_VERSION "${CUDAToolkit_VERSION}")

set(_CUDNN_HINT_DIRS
    ${CUDNN_ROOT}
    $ENV{CUDNN_ROOT}
    $ENV{CUDA_PATH}
    ${CUDAToolkit_ROOT}
    ${CUDA_TOOLKIT_ROOT_DIR}
)

if(WIN32)
    list(APPEND _CUDNN_HINT_DIRS "C:/Program Files/NVIDIA/CUDNN" "C:/Program Files/NVIDIA GPU Computing Toolkit/CUDA")
else()
    list(APPEND _CUDNN_HINT_DIRS "/usr" "/usr/local" "/usr/local/cuda" "/opt/cuda" "/usr/lib" "/usr/lib/x86_64-linux-gnu")
endif()


set(_CUDNN_SEARCH_DIRS "")
foreach(_root IN LISTS _CUDNN_HINT_DIRS)
    if(EXISTS "${_root}")
        file(GLOB _dirs "${_root}/v*" "${_root}")
        foreach(_dir IN LISTS _dirs)
            list(APPEND _CUDNN_SEARCH_DIRS "${_dir}")
        endforeach()
    endif()
endforeach()
list(REMOVE_DUPLICATES _CUDNN_SEARCH_DIRS)


foreach(_dir IN LISTS _CUDNN_SEARCH_DIRS)
    find_path(CUDNN_INCLUDE_DIR NAMES cudnn.h
        PATHS "${_dir}"
        PATH_SUFFIXES
            include
            include/${CUDA_SHORT_VERSION}
            include/cudnn
    )

    if(CUDNN_INCLUDE_DIR)
        break()
    endif()
endforeach()

foreach(_dir IN LISTS _CUDNN_SEARCH_DIRS)
    find_library(CUDNN_LIBRARY NAMES cudnn
        PATHS "${_dir}"
        PATH_SUFFIXES
            lib
            lib64
            lib/x64
            lib/x86_64-linux-gnu
            lib/${CUDA_SHORT_VERSION}/x64
    )

    if(CUDNN_LIBRARY)
        break()
    endif()
endforeach()

foreach(_hdr cudnn_version.h cudnn.h)
    if(EXISTS "${CUDNN_INCLUDE_DIR}/${_hdr}")
        file(READ "${CUDNN_INCLUDE_DIR}/${_hdr}" _cudnn_hdr)
        string(APPEND _cudnn_contents "${_cudnn_hdr}")
    endif()
endforeach()

string(REGEX MATCH "CUDNN_MAJOR *([0-9]+)" _m "${_cudnn_contents}")
set(CUDNN_MAJOR_VERSION "${CMAKE_MATCH_1}")
string(REGEX MATCH "CUDNN_MINOR *([0-9]+)" _m "${_cudnn_contents}")
set(CUDNN_MINOR_VERSION "${CMAKE_MATCH_1}")
string(REGEX MATCH "CUDNN_PATCHLEVEL *([0-9]+)" _m "${_cudnn_contents}")
set(CUDNN_PATCH_VERSION "${CMAKE_MATCH_1}")
set(CUDNN_VERSION "${CUDNN_MAJOR_VERSION}.${CUDNN_MINOR_VERSION}.${CUDNN_PATCH_VERSION}")

set(CUDNN_INCLUDE_DIRS ${CUDNN_INCLUDE_DIR})
set(CUDNN_LIBRARIES ${CUDNN_LIBRARY})
mark_as_advanced(CUDNN_LIBRARY CUDNN_INCLUDE_DIR)
find_package_handle_standard_args(CUDNN NAME_MISMATCHED REQUIRED_VARS CUDNN_INCLUDE_DIR CUDNN_LIBRARY VERSION_VAR CUDNN_VERSION)

string(REGEX REPLACE "/include(/.*)?$" "" CUDNN_DLL_DIR "${CUDNN_INCLUDE_DIR}")
find_file(CUDNN_LIBRARY_DLL NAMES cudnn64_${CUDNN_MAJOR_VERSION}.dll
    PATHS "${CUDNN_DLL_DIR}"
    PATH_SUFFIXES
        bin
        bin/${CUDA_SHORT_VERSION}
        bin/${CUDA_SHORT_VERSION}/x64
)

if(CUDNN_FOUND AND NOT TARGET CuDNN::CuDNN)
    if(EXISTS "${CUDNN_LIBRARY_DLL}")
        message(STATUS "    CUDNN_LIBRARY_DLL: ${CUDNN_LIBRARY_DLL}")
        add_library(CuDNN::CuDNN SHARED IMPORTED)
        set_target_properties(CuDNN::CuDNN PROPERTIES IMPORTED_LOCATION "${CUDNN_LIBRARY_DLL}" IMPORTED_IMPLIB "${CUDNN_LIBRARY}" INTERFACE_INCLUDE_DIRECTORIES "${CUDNN_INCLUDE_DIR}" IMPORTED_LINK_INTERFACE_LANGUAGES "C")
    else()
        add_library(CuDNN::CuDNN UNKNOWN IMPORTED)
        set_target_properties(CuDNN::CuDNN PROPERTIES IMPORTED_LOCATION "${CUDNN_LIBRARY}" INTERFACE_INCLUDE_DIRECTORIES "${CUDNN_INCLUDE_DIR}" IMPORTED_LINK_INTERFACE_LANGUAGES "C")
    endif()

    target_link_libraries(CuDNN::CuDNN INTERFACE CUDA::cudart_static)
    add_library(CUDNN::cudnn_all ALIAS CuDNN::CuDNN)
endif()
"""
        save(self, file, content)
