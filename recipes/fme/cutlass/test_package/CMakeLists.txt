cmake_minimum_required(VERSION 3.31)
project(test_package LANGUAGES CXX CUDA)

if(MSVC)
    string(APPEND CMAKE_C_FLAGS   " /Zc:preprocessor")
    string(APPEND CMAKE_CXX_FLAGS " /Zc:preprocessor")
    string(APPEND CMAKE_CUDA_FLAGS " -Xcompiler=/Zc:preprocessor")
endif()


find_package(CUDAToolkit REQUIRED)
find_package(NvidiaCutlass REQUIRED)

add_executable(${PROJECT_NAME} test_package.cpp)
target_link_libraries(${PROJECT_NAME} PRIVATE CUDA::cudart nvidia::cutlass::cutlass)
