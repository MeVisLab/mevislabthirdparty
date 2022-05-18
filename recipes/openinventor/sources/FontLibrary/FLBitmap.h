/* *****************************************************************************************
    Copyright 2021 MeVis Medical Solutions AG
    Distributed under the Boost Software License, Version 1.0.
    (See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
***************************************************************************************** */

#ifndef FLBITMAP_H
#define FLBITMAP_H

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

#include <memory>

namespace FL
{
  struct Bitmap
  {
    GLsizei _width{};
    GLsizei _height{};
    GLfloat _xorig{};
    GLfloat _yorig{};
    GLfloat _xmove{};
    GLfloat _ymove{};
    std::unique_ptr<GLubyte[]> _bitmap;
  };
}


#endif