
/* *****************************************************************************************
    Copyright 2021 MeVis Medical Solutions AG
    Distributed under the Boost Software License, Version 1.0.
    (See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
***************************************************************************************** */

#ifndef FLCONTEXT_H
#define FLCONTEXT_H


#include "FLEnums.h"
#include "FLFreetypeFont.h"

#include <variant>

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
  class Context
  {
  public:
    Context(std::string fontPath);

    ~Context() = default;

    template <typename T> static void setHint(FontHint hint, T hintValue);

    static FontNumber createFont(const std::string &fontName, GLfloat mat[2][2],
                                 GLint charNameCount, GLubyte **charNameVector);

    static void removeFont(FontNumber number);

    static FreeTypeFont *fontInfo(FontNumber number);

    static std::vector<FreeTypeFont *> fontInfos(const std::vector<FontNumber> &numbers);

    static const Outline *outline(const std::vector<FontNumber> &numbers, GLuint c);

    static const Outline *outline(const std::vector<FreeTypeFont *> &fonts, const GLubyte *ucs2);

    static const Outline *uniOutline(const std::vector<FontNumber> &numbers, const GLubyte *ucs2);

    static const Bitmap *uniBitmap(const std::vector<FontNumber> &numbers, const GLubyte *ucs2);

    FontNumber currentFont() const;
    void setCurrentFont(FontNumber number);

  private:
    std::string _fontPath;
    std::string _fontNameRestriction;

    FontNumber _currentFont{BadFontNumber};
    std::vector<FreeTypeFont> _fontTable;
    std::variant<GLfloat, FontType> _hintValue[9];
  };

  bool setCurrentContext(Context *context);

  Context *currentContext();

  FontNumber currentFont();

  void setCurrentFont(FontNumber number);

  template <typename T> void Context::setHint(FontHint hint, T hintValue)
  {
    auto ctx = currentContext();
    if (ctx)
    {
      std::get<T>(ctx->_hintValue[static_cast<std::size_t>(hint)]) = hintValue;
    }
  }

} // namespace FL


#endif