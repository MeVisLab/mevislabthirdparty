/* *****************************************************************************************
    Copyright 2021 MeVis Medical Solutions AG
    Distributed under the Boost Software License, Version 1.0.
    (See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
***************************************************************************************** */

#ifndef FLFREETYPEOUTLINE_H
#define FLFREETYPEOUTLINE_H

#include "FLBitmap.h"

#include <ft2build.h>
#include <freetype/freetype.h>
#include <vector>


#ifdef WIN32
#include <Windows.h>
#include <gl/GL.h>
#else
# ifdef __APPLE__
# include <OpenGL/gl.h>
# else
# include <GL/gl.h>
# endif
#endif


namespace FL
{

  using Char = GLushort; /* 16 bits wide char */

  class FreeTypeFont;

  /* 2D outline point */

  template <typename T> struct Point2DT
  {
    using type = T;
    T x{};
    T y{};
  };

  using Point2DF = Point2DT<float>;
  using Point2DD = Point2DT<double>;
  using Point2DL = Point2DT<long>;

  struct Outline
  {
    std::size_t _outlineCount{};
    std::vector<GLshort> _vertexCounts;
    std::vector<std::vector<Point2DF>> _vertex;
    GLfloat _xAdvance{};
    GLfloat _yAdvance{};
  };

  bool empty(const Outline& outline);


  class FreeTypeOutline
  {
    friend class FreeTypeFont;

  public:
    const Outline &outline() const;

    bool empty() const;

  private:
    Outline _outline;
    Bitmap _bitmap;

    Char _charCodePoint;
    Point2DF _size;
    GLfloat _advance{};
    std::vector<bool> _polygons;
    std::vector<short> _facesIndexes;
    std::vector<short> _tessIndexes;
    std::vector<Point2DF> _vertices;
    FT_GlyphSlot _glyph{};
  };

} // namespace FL
#endif