/* *****************************************************************************************
    Copyright 2021 MeVis Medical Solutions AG
    Distributed under the Boost Software License, Version 1.0.
    (See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
***************************************************************************************** */


#ifndef FLFREETYPEFONT_H
#define FLFREETYPEFONT_H

#include "FLEnums.h"
#include "FLFreetypeOutline.h"

#include <freetype/freetype.h>
#include <optional>
#include <string>
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

  using FontNumber = GLint;


  struct FontProperties
  {
    unsigned long name = 0;
    unsigned long value = 0;
  };


  struct CharProperty
  {
    short _leftBearing;         /* origin to left edge of raster */
    short _rightBearing;        /* origin to right edge of raster */
    short _width;               /* advance to next char's origin */
    short _ascent;              /* baseline to top edge of raster */
    short _descent;             /* baseline to bottom edge of raster */
    unsigned short _attributes; /* per char flags (not predefined) */
  };

  constexpr FontNumber BadFontNumber{0};

  enum class RasterResult
  {
    Ok = 0,
    Uninitialized_Object = 1,
    Overflow = 2,
    Negative_Height = 3,
    Invalid_Outline = 4,
    Invalid_Map = 5,
    AntiAlias_Unsupported = 6,
    Invalid_Pool = 7,
    Unimplemented = 8,
    Bad_Palette_Count = 9
  };

  enum class RenderResult
  {
    Success,
    Failure
  };

  using Char = GLushort; /* 16 bits wide char */

  class FreeTypeFont
  {
  public:
    FreeTypeFont(const std::string &fontName, GLfloat mat[2][2], GLint charNameCount,
                 GLubyte **charNameVector, FontNumber number);

    ~FreeTypeFont();

    FreeTypeFont(FreeTypeFont &&other) noexcept;
    FreeTypeFont &operator=(FreeTypeFont &&other) noexcept;

    FreeTypeFont(const FreeTypeFont &) = delete;
    FreeTypeFont &operator=(const FreeTypeFont &other) = delete;

    const Outline *characterOutline(GLuint c);

    const Outline *uniOutline(GLuint c);

    const Bitmap *uniBitmap(GLuint c);

    std::optional<FreeTypeOutline> createGlyphChar(FL::Char c, FT_GlyphSlot slot);

    FontNumber fontNumber() const;

    bool valid() const;

  private:
    RasterResult generateGlyph(FL::FreeTypeOutline &ch);
    RenderResult finalizeFaceTable(FL::FreeTypeOutline *ch, FT_Raster raster);
    RenderResult convertGlyph(FL::FreeTypeOutline *ch, FT_Raster raster, FT_Outline *outline);

    FreeTypeOutline loadChar(Char c);

    FreeTypeOutline *characterUniFreetypeOutline(GLuint c);
    FreeTypeOutline *uniFreetypeOutline(GLuint c);

    void convertBitmap(int width, int height, int pitch, int pitch2, const unsigned char *source,
                       unsigned char *dest) const;

    FontNumber _fontNumber{};
    FontDirection _direction{FontDirection::LeftToRight};
    unsigned _min_char_or_byte2{32};  /* first character */
    unsigned _max_char_or_byte2{127}; /* last character */
    unsigned _min_byte1{};            /* first row that exists */
    unsigned _max_byte1{};            /* last row that exists */
    bool _all_chars_exist{false};     /* flag if all characters have non-zero size*/
    unsigned _default_char{32};       /* char to print for undefined character */

    std::vector<FontProperties> _properties; /* pointer to array of additional properties*/
    CharProperty _min_bounds{};              /* minimum bounds over all existing char*/
    CharProperty _max_bounds{};              /* maximum bounds over all existing char*/
    CharProperty *_per_char{};               /* first_char to last_char information */
    int _ascent{8};                          /* log. extent above baseline for spacing */
    int _descent{4};                         /* log. descent below baseline for spacing */

    std::string _name;

    Point2DF _bound;                     /* max char size */
    std::vector<FreeTypeOutline> _char8; /* 8 bit char array */
    std::vector<std::pair<Char, FreeTypeOutline>>
        _char16; /* 16 bit chars, pair of codepoint and Outline. They are sorted by Char */

    FT_Face _face{};    /* the font face */
    bool _hint{};       /* is glyph hinting active? */
    bool _grayRender{}; /* is anti-aliasing active? */
    bool _lowPrec{};    /* force low precision */
  };
} // namespace FL

#endif