/* *****************************************************************************************
    Copyright 2021 MeVis Medical Solutions AG
    Distributed under the Boost Software License, Version 1.0.
    (See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
***************************************************************************************** */

#include "FLContext.h"

#include "FLEnums.h"

#include <algorithm>

namespace
{
  FL::Context *s_currentContext = nullptr;
}

FL::Context::Context(std::string fontPath)
  : _fontPath(std::move(fontPath))
{

  _hintValue[static_cast<std::size_t>(FontHint::AABitMapFonts)] = 0.0f;
  _hintValue[static_cast<std::size_t>(FontHint::CharSpacing)] = 1.0f;
  _hintValue[static_cast<std::size_t>(FontHint::FontType)] = FontType::Outline;
  _hintValue[static_cast<std::size_t>(FontHint::MaxAASize)] = 2.0f;
  _hintValue[static_cast<std::size_t>(FontHint::MinOutlineSize)] = 12.0f;
  _hintValue[static_cast<std::size_t>(FontHint::RoundAdvance)] = 1.0f;
  _hintValue[static_cast<std::size_t>(FontHint::ScaleThresh)] = 1.0f;
  _hintValue[static_cast<std::size_t>(FontHint::Tolerance)] = 0.1f;
}


FL::FontNumber FL::Context::createFont(const std::string &fontName, GLfloat mat[2][2],
                                       GLint charNameCount, GLubyte **charNameVector)
{
  FontNumber fontNumber{BadFontNumber};

  auto ctx = currentContext();

  if (!ctx)
  {
    return fontNumber;
  }

  auto findIt = std::max_element(ctx->_fontTable.begin(), ctx->_fontTable.end(),
                                 [](const auto &x, const auto &y)
                                 { return x.fontNumber() < y.fontNumber(); });

  fontNumber = findIt != ctx->_fontTable.end() ? (findIt->fontNumber() + 1) : 1;
  FreeTypeFont font{fontName, mat, charNameCount, charNameVector, fontNumber};

  if (!font.valid())
  {
    return fontNumber;
  }

  ctx->_fontTable.emplace_back(std::move(font));

  return fontNumber;
}


void FL::Context::removeFont(FontNumber number)
{
  auto ctx = currentContext();
  if (ctx)
  {
    auto oldIt = std::find_if(ctx->_fontTable.begin(), ctx->_fontTable.end(),
      [number](const auto& item) { return item.fontNumber() == number; });
    ctx->_fontTable.erase(oldIt);
  }
}


FL::FreeTypeFont *FL::Context::fontInfo(FontNumber number)
{
  FreeTypeFont *result{};
  const auto ctx = currentContext();
  if (ctx)
  {
    if (auto findIt =
      std::find_if(ctx->_fontTable.begin(), ctx->_fontTable.end(),
        [number](const auto& font) { return font.fontNumber() == number; });
      findIt != ctx->_fontTable.cend())
    {
      result = &(*findIt);
    }
  }
  return result;
}


std::vector<FL::FreeTypeFont *> FL::Context::fontInfos(const std::vector<FontNumber> &numbers)
{
  std::vector<FreeTypeFont *> result;
  for (const auto &number : numbers)
  {
    result.push_back(fontInfo(number));
  }
  return result;
}


const FL::Outline *FL::Context::outline(const std::vector<FontNumber> &numbers, GLuint c)
{
  const Outline *result{};

  auto fonts = fontInfos(numbers);

  for (auto font : fonts)
  {
    if (auto outline = font->characterOutline(c); outline && !FL::empty(*outline))
    {
      result = outline;
      return result;
    }
  }

  return result;
}


const FL::Outline *FL::Context::outline(const std::vector<FreeTypeFont *> &fonts, GLuint c)
{
  for (auto font : fonts)
  {
    auto result = font->characterOutline(c);
    if (result && result->_outlineCount > 0)
    {
      return result;
    }
  }

  return nullptr;
}


const FL::Outline *FL::Context::uniOutline(const std::vector<FontNumber> &numbers, GLuint c)
{
  const Outline *result{};

  auto fonts = fontInfos(numbers);

  for (auto font : fonts)
  {
    if (auto outline = font->uniOutline(c); outline && !FL::empty(*outline))
    {
      result = outline;
      return result;
    }
  }

  return result;
}


const FL::Bitmap *FL::Context::uniBitmap(const std::vector<FontNumber> &numbers, GLuint c)
{

  const Bitmap *result{};

  auto fonts = fontInfos(numbers);

  for (auto font : fonts)
  {
    if (auto bitmap = font->uniBitmap(c); bitmap && bitmap->_bitmap.get())
    {
      result = bitmap;
      return result;
    }
  }

  return result;
}


FL::FontNumber FL::Context::currentFont() const
{
  return _currentFont;
}


void FL::Context::setCurrentFont(FontNumber number)
{
  _currentFont = number;
}


bool FL::setCurrentContext(Context *context)
{
  if (!context)
  {
    return false;
  }

  s_currentContext = context;
  return true;
}


FL::Context *FL::currentContext()
{
  return s_currentContext;
}


FL::FontNumber FL::currentFont()
{
  if (auto ctx = currentContext(); ctx)
  {
    return ctx->currentFont();
  }

  return BadFontNumber;
}


void FL::setCurrentFont(FontNumber number)
{
  if (auto ctx = currentContext(); ctx)
  {
    return ctx->setCurrentFont(number);
  }
}
