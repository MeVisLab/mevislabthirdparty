message(STATUS "openjp2 is an alias for OpenJPEG")

include(CMakeFindDependencyMacro)
find_dependency(OpenJPEG)

set(openjp2_FOUND ${OpenJPEG_FOUND})
set(openjp2_VERSION_STRING ${OpenJPEG_VERSION_STRING})
set(openjp2_INCLUDE_DIRS ${OpenJPEG_INCLUDE_DIRS})
set(openjp2_INCLUDE_DIR ${OpenJPEG_INCLUDE_DIR})
set(openjp2_LIBRARIES ${OpenJPEG_LIBRARIES})
set(openjp2_DEFINITIONS ${OpenJPEG_DEFINITIONS})
