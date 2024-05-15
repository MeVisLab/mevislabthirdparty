cmake_minimum_required(VERSION 3.27)
project(LZF VERSION ${CONAN_LZF_VERSION} LANGUAGES CXX)

add_library(LZF)
set_target_properties(LZF PROPERTIES VERSION "${PROJECT_VERSION}" SOVERSION "${PROJECT_VERSION_MAJOR}")

target_sources(LZF PRIVATE
    config.h
    crc32.h
    lzf_c.cpp
    lzf_d.cpp
    lzf.h
    lzfP.h
)

install(TARGETS LZF LIBRARY DESTINATION lib ARCHIVE DESTINATION lib)
install(FILES "lzf.h" DESTINATION include)
