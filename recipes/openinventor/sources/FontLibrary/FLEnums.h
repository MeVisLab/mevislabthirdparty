/* *****************************************************************************************
    Copyright 2021 MeVis Medical Solutions AG
    Distributed under the Boost Software License, Version 1.0.
    (See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
***************************************************************************************** */

#ifndef FLENUMS_H
#define FLENUMS_H

namespace FL
{
  enum class FontSource
  {
    FontName,
    FileName,
    XFontName
  };

  enum class FontType
  {
    All,
    Bitmap,
    Outline
  };

  enum class FontHint
  {
    AABitMapFonts = 1,
    CharSpacing = 2,
    FontType = 3,
    MaxAASize = 4,
    MinOutlineSize = 5,
    RoundAdvance = 6,
    ScaleThresh = 7,
    Tolerance  = 8,
    LastEnum = Tolerance
  };

  enum class FontDirection
  {
    LeftToRight,
    RightToLeft,
    BottomToTop,
    TopToBottom
  };
}

#endif