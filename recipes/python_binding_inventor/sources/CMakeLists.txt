cmake_minimum_required(VERSION 3.27)
project(PythonBindingInventor LANGUAGES CXX)

find_package(GLEW REQUIRED)
find_package(OpenGL 2.1 REQUIRED)
find_package(Python3 REQUIRED)
find_package(NumPy REQUIRED)
find_package(PythonQt REQUIRED)
find_package(Qt6 COMPONENTS Core REQUIRED)
find_package(Threads REQUIRED)
find_package(OpenInventor REQUIRED)

set(REQUIRED_LIBS Qt6::Core Python3::Python PythonQt::PythonQt OpenInventor::OpenInventor Threads::Threads)

set(SITE_PACKAGE_TARGET_DIR "$ENV{MEVIS_PYTHON_SITE_PACKAGES_FOLDER}")

set(TARGET_RUNTIME_OUTPUT_DIRECTORY "${SITE_PACKAGE_TARGET_DIR}/Inventor")

set(CMAKE_AUTOMOC ON)
add_definitions(-DQT_NO_KEYWORDS)

add_subdirectory(InventorActions)
add_subdirectory(InventorBase)
add_subdirectory(InventorDetails)
add_subdirectory(InventorDraggers)
add_subdirectory(InventorElements)
add_subdirectory(InventorEngines)
add_subdirectory(InventorEvents)
add_subdirectory(InventorFields)
add_subdirectory(InventorManips)
add_subdirectory(InventorNodekits)
add_subdirectory(InventorNodes)
add_subdirectory(InventorProjectors)
add_subdirectory(InventorSensors)
