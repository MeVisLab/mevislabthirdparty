cmake_minimum_required(VERSION 3.14)
project(conan-wrapper)

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()

set(_UNUSED ${CMAKE_DEBUG_POSTFIX} ${CMAKE_INSTALL_BINDIR} ${CMAKE_EXPORT_NO_PACKAGE_REGISTRY} ${CMAKE_INSTALL_DATAROOTDIR} ${CMAKE_INSTALL_INCLUDEDIR} ${CMAKE_INSTALL_LIBEXECDIR} ${CMAKE_INSTALL_OLDINCLUDEDIR} ${CMAKE_INSTALL_SBINDIR})

# prefer the legacy libGL library instead of GLVND
set(OpenGL_GL_PREFERENCE LEGACY)

find_package(OpenGL REQUIRED)

if(UNIX AND NOT APPLE)
    find_package(Freetype REQUIRED)
endif()

add_library(FTGL "")

set(HEADERS
    sources/include/FTBBox.h
    sources/include/FTBitmapGlyph.h
    sources/include/FTCharmap.h
    sources/include/FTCharToGlyphIndexMap.h
    sources/include/FTContour.h
    sources/include/FTExtrdGlyph.h
    sources/include/FTFace.h
    sources/include/FTFont.h
    sources/include/FTGL.h
    sources/include/FTGLBitmapFont.h
    sources/include/FTGLExtrdFont.h
    sources/include/FTGLOutlineFont.h
    sources/include/FTGLPixmapFont.h
    sources/include/FTGLPolygonFont.h
    sources/include/FTGLTextureFont.h
    sources/include/FTGlyph.h
    sources/include/FTGlyphContainer.h
    sources/include/FTLibrary.h
    sources/include/FTList.h
    sources/include/FTOutlineGlyph.h
    sources/include/FTPixmapGlyph.h
    sources/include/FTPoint.h
    sources/include/FTPolyGlyph.h
    sources/include/FTSize.h
    sources/include/FTTextureGlyph.h
    sources/include/FTVector.h
    sources/include/FTVectoriser.h
)

target_sources(FTGL PRIVATE ${HEADERS})
target_sources(FTGL PRIVATE
    sources/src/FTBitmapGlyph.cpp
    sources/src/FTCharmap.cpp
    sources/src/FTContour.cpp
    sources/src/FTExtrdGlyph.cpp
    sources/src/FTFace.cpp
    sources/src/FTFont.cpp
    sources/src/FTGLBitmapFont.cpp
    sources/src/FTGLExtrdFont.cpp
    sources/src/FTGLOutlineFont.cpp
    sources/src/FTGLPixmapFont.cpp
    sources/src/FTGLPolygonFont.cpp
    sources/src/FTGLTextureFont.cpp
    sources/src/FTGlyph.cpp
    sources/src/FTGlyphContainer.cpp
    sources/src/FTLibrary.cpp
    sources/src/FTOutlineGlyph.cpp
    sources/src/FTPixmapGlyph.cpp
    sources/src/FTPoint.cpp
    sources/src/FTPolyGlyph.cpp
    sources/src/FTSize.cpp
    sources/src/FTTextureGlyph.cpp
    sources/src/FTVectoriser.cpp
)
target_compile_definitions(FTGL PRIVATE FTGL_LIBRARY)
target_include_directories(FTGL PRIVATE ${CMAKE_SOURCE_DIR}/sources/include)
target_link_libraries(FTGL PUBLIC OpenGL::GL OpenGL::GLU ${CONAN_LIBS})

if(UNIX AND NOT APPLE)
    target_link_libraries(FTGL PRIVATE Freetype::Freetype)
endif()

install(TARGETS FTGL)
install(FILES ${HEADERS} DESTINATION include/FTGL)
