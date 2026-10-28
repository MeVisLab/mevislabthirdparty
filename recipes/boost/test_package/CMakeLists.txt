cmake_minimum_required(VERSION 3.31)
project(test_package LANGUAGES CXX)

find_package(
    Boost
    COMPONENTS headers
               iostreams
               filesystem
               thread
               json
               serialization
               program_options
               log
               locale
               random
               chrono
               timer
    REQUIRED)
find_package(Threads REQUIRED)

set(THREADS_PREFER_PTHREAD_FLAG ON)

add_executable(test_package test_package.cpp)
target_link_libraries(
    test_package
    PRIVATE Boost::headers
            Boost::iostreams
            Boost::filesystem
            Boost::thread
            Boost::json
            Boost::serialization
            Boost::program_options
            Boost::log
            Boost::locale
            Boost::random
            Boost::chrono
            Boost::timer
            Threads::Threads)
