/* *****************************************************************************************
    Copyright 2021 MeVis Medical Solutions AG
    Distributed under the Boost Software License, Version 1.0.
    (See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
***************************************************************************************** */

#include "FLFreetypeOutline.h"

bool FL::empty(const Outline &outline)
{
  return outline._outlineCount == 0 && outline._xAdvance == 0.f;
}

const FL::Outline &FL::FreeTypeOutline::outline() const
{
  return _outline;
}

bool FL::FreeTypeOutline::empty() const
{
  return FL::empty(outline()) && _vertices.empty();
}
