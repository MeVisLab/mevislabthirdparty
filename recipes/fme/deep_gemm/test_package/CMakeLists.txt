cmake_minimum_required(VERSION 3.31)
project(test_package LANGUAGES CXX CUDA)

find_package(CUDAToolkit REQUIRED)
find_package(deep_gemm REQUIRED)

add_executable(${PROJECT_NAME} test_package.cu)
target_link_libraries(${PROJECT_NAME} PRIVATE CUDA::cudart deep_gemm::deep_gemm)
