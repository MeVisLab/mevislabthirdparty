cmake_minimum_required(VERSION 3.18)
project(cluster)

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()

set(_UNUSED
  ${CMAKE_DEBUG_POSTFIX}
  ${CMAKE_EXPORT_NO_PACKAGE_REGISTRY}
  ${CMAKE_INSTALL_BINDIR}
  ${CMAKE_INSTALL_DATAROOTDIR}
  ${CMAKE_INSTALL_INCLUDEDIR}
  ${CMAKE_INSTALL_LIBDIR}
  ${CMAKE_INSTALL_LIBEXECDIR}
  ${CMAKE_INSTALL_OLDINCLUDEDIR}
  ${CMAKE_INSTALL_SBINDIR}
)

add_library(cluster)

target_sources(cluster PUBLIC
    clHierarchicalClustering.cpp
    clHierarchicalClustering.h
    clMetricFunctions.cpp
    clMetricFunctions.h
    clPartitioningClustering.cpp
    clPartitioningClustering.h
    clRandom.cpp
    clRandom.h
    clSOM.cpp
    clSOM.h
    clSVD.cpp
    clSVD.h
)

set_property(TARGET cluster PROPERTY PUBLIC_HEADER
    clHierarchicalClustering.h
    clMetricFunctions.h
    clPartitioningClustering.h
    clRandom.h
    clSOM.h
    clSVD.h
)

install(TARGETS cluster)
