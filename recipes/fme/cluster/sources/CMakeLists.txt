cmake_minimum_required(VERSION 3.27)
project(cluster)

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
