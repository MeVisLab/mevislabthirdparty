cmake_minimum_required(VERSION 3.27)
project(test_package LANGUAGES CXX)

find_package(Boost COMPONENTS headers iostreams filesystem thread REQUIRED)
find_package(Threads REQUIRED)

set(THREADS_PREFER_PTHREAD_FLAG ON)

add_executable(test_package test_package.cpp)
target_link_libraries(test_package PRIVATE Boost::headers Boost::iostreams Boost::filesystem Boost::thread Threads::Threads)
