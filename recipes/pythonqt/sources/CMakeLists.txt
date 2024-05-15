cmake_minimum_required(VERSION 3.27)
project(PythonQt LANGUAGES CXX)

find_package(Python3)

find_package(Qt6 COMPONENTS Core Gui Widgets Network REQUIRED)
find_package(Threads REQUIRED)

set(CMAKE_AUTOMOC ON)

add_library(PythonQt "")
add_library(PythonQt::PythonQt ALIAS PythonQt)
set_target_properties(PythonQt PROPERTIES OUTPUT_NAME PythonQt)

add_subdirectory(src)
add_subdirectory(generated_cpp)

target_compile_definitions(PythonQt PRIVATE MEVIS_TARGET=PythonQt)
target_compile_definitions(PythonQt PRIVATE PYTHONQT_EXPORTS)
target_compile_definitions(PythonQt PUBLIC PYTHONQT_SUPPORT_NAME_PROPERTY)
target_compile_definitions(PythonQt PUBLIC PYTHONQT_SUPPORT_ML_TYPES)

target_include_directories(PythonQt
  PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src>
    $<INSTALL_INTERFACE:${MEVISLAB_INSTALL_INCLUDEDIR}>
)

target_link_libraries(PythonQt
  PUBLIC
    Qt6::Core
    Qt6::CorePrivate
    Qt6::Gui
    Qt6::Widgets
    Qt6::Network
    Python3::Python
    Threads::Threads
)

# MVL-11: TODO We have to fix the code generator!
# The code in generated_cpp uses many deprecated Qt function.
# Therefore I just remove QT_DISABLE_DEPRECATED_BEFORE=xxx and enable QT_NO_DEPRECATED_WARNINGS.
get_directory_property(defs DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} COMPILE_DEFINITIONS)
if("${defs}" MATCHES ".*QT_DISABLE_DEPRECATED_BEFORE=0x[0-9]+")
    remove_definitions("-D${CMAKE_MATCH_0}")
endif()
remove_definitions("-DQT_DEPRECATED_WARNINGS")
target_compile_definitions(PythonQt PRIVATE QT_NO_DEPRECATED_WARNINGS) # since Qt 5.13
if(WIN32)
    add_definitions(/bigobj)
endif()

install(TARGETS PythonQt RUNTIME DESTINATION bin LIBRARY DESTINATION lib ARCHIVE DESTINATION lib)

if(WIN32)
    install(FILES $<TARGET_PDB_FILE:PythonQt> DESTINATION bin OPTIONAL)
endif()

install(DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/src/" DESTINATION include FILES_MATCHING PATTERN "*.h")
install(DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/src/gui" DESTINATION include FILES_MATCHING PATTERN "*.h")

#file(RELATIVE_PATH REL ${CMAKE_SOURCE_DIR} ${CMAKE_CURRENT_SOURCE_DIR})
#install(FILES COPYING README DESTINATION ${REL})
