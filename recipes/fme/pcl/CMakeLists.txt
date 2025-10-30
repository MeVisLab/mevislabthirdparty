cmake_minimum_required(VERSION 3.27)
project(conan-wrapper)

find_package(FLANN REQUIRED)
find_package(Boost COMPONENTS system serialization filesystem date_time iostreams asio REQUIRED)
find_package(Qhull REQUIRED)

set(QHULL_FOUND TRUE)
set(HAVE_QHULL TRUE)
add_library(QHULL::QHULL ALIAS Qhull::Qhull)

add_subdirectory(src)
