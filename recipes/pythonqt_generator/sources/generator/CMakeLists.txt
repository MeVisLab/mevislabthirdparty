cmake_minimum_required(VERSION 3.27)

project(PythonQtGenerator)

include(CTestUseLaunchers OPTIONAL)

find_package(Qt6 COMPONENTS Core Xml Core5Compat REQUIRED)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

#-----------------------------------------------------------------------------
# Sources

set(sources
  parser/ast.cpp
  parser/binder.cpp
  parser/class_compiler.cpp
  parser/codemodel.cpp
  parser/codemodel_finder.cpp
  parser/compiler_utils.cpp
  parser/control.cpp
  parser/declarator_compiler.cpp
  parser/default_visitor.cpp
  parser/dumptree.cpp
  parser/lexer.cpp
  parser/list.cpp
  parser/name_compiler.cpp
  parser/parser.cpp
  parser/smallobject.cpp
  parser/tokens.cpp
  parser/type_compiler.cpp
  parser/visitor.cpp

  abstractmetabuilder.cpp
  abstractmetalang.cpp
  asttoxml.cpp
  customtypes.cpp
  fileout.cpp
  generator.cpp
  generatorset.cpp
  generatorsetqtscript.cpp
  main.cpp
  metajava.cpp
  metaqtscriptbuilder.cpp
  metaqtscript.cpp
  prigenerator.cpp
  reporthandler.cpp
  setupgenerator.cpp
  shellgenerator.cpp
  shellheadergenerator.cpp
  shellimplgenerator.cpp
  typeparser.cpp
  typesystem.cpp
)

#-----------------------------------------------------------------------------
# Headers that should run through moc

set(moc_sources
  fileout.h
  generator.h
  generatorset.h
  generatorsetqtscript.h
  prigenerator.h
  setupgenerator.h
  shellgenerator.h
  shellheadergenerator.h
  shellimplgenerator.h
)

#-----------------------------------------------------------------------------
# UI files

set(ui_sources )

#-----------------------------------------------------------------------------
# Resources

set(qrc_sources
  generator.qrc
)

#-----------------------------------------------------------------------------
# Copy file expected by the generator and specify install rules

file(GLOB files_to_copy RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} "build_*.txt" "typesystem_*.xml")
list(APPEND files_to_copy qtscript_masterinclude.h parser/rpp/pp-qt-configuration)
foreach(file ${files_to_copy})
  configure_file(
    ${file}
    ${CMAKE_CURRENT_BINARY_DIR}/${file}
    COPYONLY
    )
  get_filename_component(destination_dir ${file} PATH)
  install(FILES ${file} DESTINATION bin/${destination_dir})
endforeach()

include_directories(
  ${CMAKE_CURRENT_SOURCE_DIR}
  ${CMAKE_CURRENT_SOURCE_DIR}/parser
  ${CMAKE_CURRENT_SOURCE_DIR}/parser/rpp
)

add_definitions(-DRXX_ALLOCATOR_INIT_0)

qt_add_executable(${PROJECT_NAME}
  ${sources}
  ${gen_moc_sources}
  ${gen_ui_sources}
  ${qrc_sources}
)

target_link_libraries(${PROJECT_NAME}
  PUBLIC
    Qt6::Core
    Qt6::Xml
    Qt6::CorePrivate
    Qt6::Core5Compat
)

#-----------------------------------------------------------------------------
# Install library (on windows, put the dll in 'bin' and the archive in 'lib')

install(TARGETS ${PROJECT_NAME}
        RUNTIME DESTINATION bin
        LIBRARY DESTINATION lib
        ARCHIVE DESTINATION lib)
