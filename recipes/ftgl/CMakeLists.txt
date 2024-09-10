cmake_minimum_required(VERSION 3.27)
project(FTGL LANGUAGES CXX)

# prefer the legacy libGL library instead of GLVND
set(OpenGL_GL_PREFERENCE LEGACY)

find_package(OpenGL REQUIRED)
find_package(Freetype REQUIRED)

set(HEADERS
    src/include/FTBBox.h
    src/include/FTBitmapGlyph.h
    src/include/FTCharmap.h
    src/include/FTCharToGlyphIndexMap.h
    src/include/FTContour.h
    src/include/FTExtrdGlyph.h
    src/include/FTFace.h
    src/include/FTFont.h
    src/include/FTGL.h
    src/include/FTGLBitmapFont.h
    src/include/FTGLExtrdFont.h
    src/include/FTGLOutlineFont.h
    src/include/FTGLPixmapFont.h
    src/include/FTGLPolygonFont.h
    src/include/FTGLTextureFont.h
    src/include/FTGlyph.h
    src/include/FTGlyphContainer.h
    src/include/FTLibrary.h
    src/include/FTList.h
    src/include/FTOutlineGlyph.h
    src/include/FTPixmapGlyph.h
    src/include/FTPoint.h
    src/include/FTPolyGlyph.h
    src/include/FTSize.h
    src/include/FTTextureGlyph.h
    src/include/FTVector.h
    src/include/FTVectoriser.h
)

add_library(FTGL "")
target_sources(FTGL PRIVATE ${HEADERS})
target_sources(FTGL PRIVATE
    src/src/FTBitmapGlyph.cpp
    src/src/FTCharmap.cpp
    src/src/FTContour.cpp
    src/src/FTExtrdGlyph.cpp
    src/src/FTFace.cpp
    src/src/FTFont.cpp
    src/src/FTGLBitmapFont.cpp
    src/src/FTGLExtrdFont.cpp
    src/src/FTGLOutlineFont.cpp
    src/src/FTGLPixmapFont.cpp
    src/src/FTGLPolygonFont.cpp
    src/src/FTGLTextureFont.cpp
    src/src/FTGlyph.cpp
    src/src/FTGlyphContainer.cpp
    src/src/FTLibrary.cpp
    src/src/FTOutlineGlyph.cpp
    src/src/FTPixmapGlyph.cpp
    src/src/FTPoint.cpp
    src/src/FTPolyGlyph.cpp
    src/src/FTSize.cpp
    src/src/FTTextureGlyph.cpp
    src/src/FTVectoriser.cpp
)

target_compile_definitions(FTGL PRIVATE FTGL_LIBRARY)
target_include_directories(FTGL PRIVATE src/include)
target_link_libraries(FTGL PUBLIC OpenGL::GL OpenGL::GLU)
target_link_libraries(FTGL PUBLIC Freetype::Freetype)

install(TARGETS FTGL)
install(FILES ${HEADERS} DESTINATION include/FTGL)
