cmake_minimum_required(VERSION 3.27)
project(FTGL LANGUAGES CXX)

# prefer the legacy libGL library instead of GLVND
set(OpenGL_GL_PREFERENCE LEGACY)

find_package(OpenGL REQUIRED)
find_package(Freetype REQUIRED)

set(HEADERS
    include/FTBBox.h
    include/FTBitmapGlyph.h
    include/FTCharmap.h
    include/FTCharToGlyphIndexMap.h
    include/FTContour.h
    include/FTExtrdGlyph.h
    include/FTFace.h
    include/FTFont.h
    include/FTGL.h
    include/FTGLBitmapFont.h
    include/FTGLExtrdFont.h
    include/FTGLOutlineFont.h
    include/FTGLPixmapFont.h
    include/FTGLPolygonFont.h
    include/FTGLTextureFont.h
    include/FTGlyph.h
    include/FTGlyphContainer.h
    include/FTLibrary.h
    include/FTList.h
    include/FTOutlineGlyph.h
    include/FTPixmapGlyph.h
    include/FTPoint.h
    include/FTPolyGlyph.h
    include/FTSize.h
    include/FTTextureGlyph.h
    include/FTVector.h
    include/FTVectoriser.h
)

add_library(FTGL "")
target_sources(FTGL PRIVATE ${HEADERS})
target_sources(FTGL PRIVATE
    src/FTBitmapGlyph.cpp
    src/FTCharmap.cpp
    src/FTContour.cpp
    src/FTExtrdGlyph.cpp
    src/FTFace.cpp
    src/FTFont.cpp
    src/FTGLBitmapFont.cpp
    src/FTGLExtrdFont.cpp
    src/FTGLOutlineFont.cpp
    src/FTGLPixmapFont.cpp
    src/FTGLPolygonFont.cpp
    src/FTGLTextureFont.cpp
    src/FTGlyph.cpp
    src/FTGlyphContainer.cpp
    src/FTLibrary.cpp
    src/FTOutlineGlyph.cpp
    src/FTPixmapGlyph.cpp
    src/FTPoint.cpp
    src/FTPolyGlyph.cpp
    src/FTSize.cpp
    src/FTTextureGlyph.cpp
    src/FTVectoriser.cpp
)

target_compile_definitions(FTGL PRIVATE FTGL_LIBRARY)
target_include_directories(FTGL PRIVATE include)
target_link_libraries(FTGL PUBLIC OpenGL::GL OpenGL::GLU)
target_link_libraries(FTGL PUBLIC Freetype::Freetype)

install(TARGETS FTGL)
install(FILES ${HEADERS} DESTINATION include/FTGL)
