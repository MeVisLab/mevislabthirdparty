
/* *****************************************************************************************
    Copyright 2021 MeVis Medical Solutions AG
    Distributed under the Boost Software License, Version 1.0.
    (See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
***************************************************************************************** */

#include "FLFreetypeFont.h"
#include "FLScopeGuard.h"

#include <ft2build.h>
#include <freetype/freetype.h>
#include <freetype/ftoutln.h>

#ifdef WIN32
#include <io.h>
#include <ShlObj.h>
#include <Windows.h>
#ifndef R_OK
#define R_OK 4
#endif
#else
#include <unistd.h>
#endif
#ifdef __APPLE__
#include <ApplicationServices/ApplicationServices.h>
#endif

#include <algorithm>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <mutex>
#include <limits>
#include <numeric>
#include <string>

#ifdef LINUX
#include <fontconfig/fontconfig.h>
#endif

namespace
{
  constexpr double pi{3.14159265358979323846};

  auto constexpr toRadiant(double deg)
  {
    return deg / 180.0 * pi;
  }

  constexpr double KludgeFactor{80.0};
  constexpr long PixelRowAlignment{ 4 };
  constexpr long RasterPrecisionBits{ 8 };
  constexpr long RasterPrecision{ 1 << RasterPrecisionBits };
  constexpr long RasterPrecisionMask{ static_cast<long>(std::numeric_limits<unsigned long>::max() << RasterPrecisionBits) };

  constexpr long BitmapPrecisionBits{ 6 };
  constexpr long BitmapPrecision{ 1 << BitmapPrecisionBits };
  constexpr long BitmapPrecisionMask{ static_cast<long>(std::numeric_limits<unsigned long>::max() << BitmapPrecisionBits) };


  template <typename T>
  constexpr auto rasterFloor(T val)
  {
    return val & RasterPrecisionMask;
  }
  template <typename T>
  constexpr auto bitmapFloor(T val)
  {
    return val & BitmapPrecisionMask;
  }

  template <typename T>
  constexpr auto rasterCeiling(T val)
  {
    return (val + RasterPrecision - 1) & RasterPrecisionMask;
  }
  template <typename T>
  constexpr auto bitmapCeiling(T val)
  {
    return (val + BitmapPrecision - 1) & BitmapPrecisionMask;
  }

  template <typename T>
  constexpr auto rasterTrunc(T val)
  {
    return val >> RasterPrecisionBits;
  }
  template <typename T>
  constexpr auto bitmapTrunc(T val)
  {
    return val >> BitmapPrecisionBits;
  }

  template <typename T>
  constexpr auto rasterFrac(T val)
  {
    return val & (RasterPrecision - 1);
  }

  template <typename T> constexpr auto multiplyDivide(T a, T b, T c)
  {
    return (a * b) / c;
  }


  double boundingTriangleAngle(long x1, long y1, long x, long y, long x2, long y2)
  {
    FL::Point2DD a{static_cast<double>(x1 - x), static_cast<double>(y1 - y)};
    FL::Point2DD b{static_cast<double>(x2 - x), static_cast<double>(y2 - y)};
    double lengthA = sqrt(a.x * a.x + a.y * a.y);
    double lengthB = sqrt(b.x * b.x + b.y * b.y);
    double len2 = lengthA * lengthB;
    return len2 == 0.0 ? 2.0 * pi : acos((a.x * b.x + a.y * b.y) / len2);
  }

  FT_Library library;

  std::once_flag initDone;

#if defined(WIN32)
  std::string fontPath;
  /*
   * Most Inventor font names don't exist in
   * windows, so we'll default to a common
   * windows font.
   */
  std::string defaultFont;
#elif defined(__APPLE__)
  /*
   * We use Apple Type Services for Fonts References on Mac OS X instead of hard-coded
   * directories if no explicit font path it set via environment variable.
   */
  std::string fontPath;
#elif defined(LINUX)
  std::string fontPath = "/usr/share/fonts";
  FcBool fontconfigInitialized = FcFalse;
#else
  std::string fontPath = "/usr/share/data/fonts";
#endif


  void initFontSystem()
  {
    char *ev;

#ifdef WIN32
    /* obtain Windows font path */
    CHAR szPath[MAX_PATH] = {0};
    SHGetSpecialFolderPathA(nullptr, szPath, CSIDL_FONTS, 0);
    fontPath = szPath;

    /* setup fallback font */
    defaultFont = fontPath + "\\times.ttf";

#elif defined(LINUX)
    fontconfigInitialized = FcInit();
    if (!fontconfigInitialized)
    {
      fprintf(stderr, "ERROR: libFL: failed to initialize fontconfig library\n");
    }
#endif

    // ev = getenv("FL_DEBUG");
    // fl_debug = (ev && *ev != '0');

    ev = getenv("FL_FONT_PATH");
    if (ev && *ev)
      fontPath = ev;


    if (auto error = FT_Init_FreeType(&library); error != 0)
    {
      fprintf(stderr, "%s: initialise FreeType failed\n", __FUNCTION__);
    }
  }


  std::string searchFont(const std::string &fontName)
  {
    std::string result;

    if (!fontPath.empty())
    {
      const char *fontExt[] = {
          "", ".otf", ".pfa", ".pfb", ".ttf",
      };

      for (const auto &ext : fontExt)
      {
#ifdef WIN32
        auto fontPathName = fontPath + "\\" + fontName + ext;
#else
        auto fontPathName = fontPath + "/" + fontName + ext;
#endif
        if (access(fontPathName.c_str(), R_OK) == 0)
        {
          result = fontPathName;
        }
      }
    }

#if defined(__APPLE__)

    if (result.empty())
    {
      CFStringRef name = CFStringCreateWithCString(kCFAllocatorDefault, fontName.c_str(),
                                                   kCFStringEncodingUTF8);
      /* Try to find font by using its postscript name (other font name types are matched in a
       * fallback manner) */
      CTFontRef font = CTFontCreateWithName(name, 0.0, nullptr);
      CFRelease(name);
      if (!font)
      {
        /* Use fallback font */
        font = CTFontCreateWithName(CFSTR("Times-Roman"), 0.0, nullptr);
      }
      if (font)
      {
        CFURLRef url = (CFURLRef)CTFontCopyAttribute(font, kCTFontURLAttribute);
        CFRelease(font);
        if (url)
        {
          UInt8 buffer[PATH_MAX];
          if (CFURLGetFileSystemRepresentation(url, true, buffer, sizeof(buffer)))
          {
            result = reinterpret_cast<const char*>(buffer);
          }
          CFRelease(url);
        }
      }
    }

#elif defined(WIN32)

    if (result.empty() && access(defaultFont.c_str(), R_OK) == 0)
    {
      result = defaultFont;
    }

    // WIN32
#elif defined(LINUX)
    if (result.empty() && fontconfigInitialized)
    {
      FcPattern *pattern = FcNameParse(reinterpret_cast<const FcChar8*>(fontName.c_str()));
      FcPatternAddBool(pattern, FC_SCALABLE, FcTrue);
      FcConfigSubstitute(nullptr, pattern, FcMatchPattern);
      FcDefaultSubstitute(pattern);

      FcResult sortResult;
      FcFontSet *fontSet = FcFontSort(nullptr, pattern, FcFalse, nullptr, &sortResult);
      FcPatternDestroy(pattern);

      if (fontSet->nfont > 0)
      {
        FcChar8 *filename;
        if (FcPatternGetString(fontSet->fonts[0], FC_FILE, 0, &filename) == FcResultMatch)
        {
          result = reinterpret_cast<const char*>(filename);
        }
      }

      FcFontSetDestroy(fontSet);
    }
#endif // LINUX

    //fprintf(stderr, "Font %s loaded\n", result.c_str());
    return result;
  }


} // namespace


FL::FreeTypeFont::FreeTypeFont(const std::string &fontName, GLfloat mat[2][2], GLint charNameCount,
                               GLubyte **charNameVector, FontNumber number)
{
  std::call_once(initDone, initFontSystem);

  const std::string path = searchFont(fontName);
  if (path.empty())
  {
    return;
  }

  FT_Face face;
  FT_Error error = FT_New_Face(library, path.c_str(), 0, &face);

  if (!error)
  {
    int px = (mat[0][0] == 1.0) ? 32 : mat[0][0];
    int py = (mat[1][1] == 1.0) ? 32 : mat[1][1];

    error = FT_Set_Char_Size(face, px << 6, py << 6, mat[0][1], mat[1][0]);

    if (!error)
    {
      _char8.resize(256);

      _fontNumber = number;
      _name = fontName;
      _face = face;
      _hint = true;
      _lowPrec = false;
      _grayRender = true;
      _bound.x = (face->bbox.xMax - face->bbox.xMin) >> 5;
      _bound.y = (face->bbox.yMax - face->bbox.yMin) >> 5;

      _bound.x /= KludgeFactor;
      _bound.y /= KludgeFactor;
      if (_bound.y < 0.6)
      {
        _bound.y = 1.2;
      }
    }
  }
}

FL::FreeTypeFont::~FreeTypeFont()
{
  if (_face)
  {
    FT_Done_Face(_face);
    _face = nullptr;
  }
}

FL::FreeTypeFont::FreeTypeFont(FreeTypeFont &&other) noexcept
{
  *this = std::move(other);
}

FL::FreeTypeFont &FL::FreeTypeFont::operator=(FreeTypeFont &&other) noexcept
{
  _fontNumber = other._fontNumber;
  _direction = other._direction;
  _min_char_or_byte2 = other._min_char_or_byte2;
  _max_char_or_byte2 = other._max_char_or_byte2;
  _min_byte1 = other._min_byte1;
  _max_byte1 = other._max_byte1;
  _all_chars_exist = other._all_chars_exist;
  _default_char = other._default_char;

  _properties = std::move(other._properties);
  _min_bounds = std::move(other._min_bounds);
  _max_bounds = std::move(other._max_bounds);
  _per_char = other._per_char;
  other._per_char = nullptr;
  _ascent = other._ascent;
  _descent = other._descent;

  _name = std::move(other._name);
  _bound = std::move(other._bound);
  _char8 = std::move(other._char8);
  _char16 = std::move(other._char16);
  _face = other._face;
  other._face = nullptr;
  _hint = other._hint;
  _grayRender = other._grayRender;
  _lowPrec = other._lowPrec;

  return *this;
}


std::optional<FL::FreeTypeOutline> FL::FreeTypeFont::createGlyphChar(FL::Char c, FT_GlyphSlot slot)
{
  std::optional<FL::FreeTypeOutline> result{ FL::FreeTypeOutline{} };

  result->_charCodePoint = c;
  result->_size.x = 0.0;
  result->_size.y = 0.0;
  result->_advance = 0.0;
  result->_glyph = slot;

  if (generateGlyph(*result) != FL::RasterResult::Ok)
  {
    result.reset();
  }

  auto &bitmap = result->_bitmap;
  bitmap._width = 0;
  bitmap._height = 0;
  bitmap._xorig = 0.0;
  bitmap._yorig = 0.0;
  bitmap._xmove = 0.0;
  bitmap._ymove = 0.0;
  bitmap._bitmap = nullptr;

  return result;
}

FL::FontNumber FL::FreeTypeFont::fontNumber() const
{
  return _fontNumber;
}

bool FL::FreeTypeFont::valid() const
{
  return _face != nullptr;
}

namespace RasterParams
{
  constexpr int PrecisionBits{8};
  constexpr int Precision{1 << PrecisionBits};
  constexpr int PrecisionMask{ static_cast<int>(0xffffffffUL << PrecisionBits) };
  constexpr int PrecisionHalf{Precision >> 1};
  constexpr int PrecisionStep{PrecisionHalf};
} // namespace RasterParams

namespace
{

  /* The maximum number of stacked Bezier curves.  Setting this constant
   * to more than 32 is a pure waste of space.
   */
  constexpr int MaxNumberBezierCurves{64};

  /* The number fractional bits of *input* coordinates.  We always use the
   * 26.6 format (i.e, 6 bits for the fractional part), but hackers are
   * free to experiment with different values.
   */
  constexpr int InputBIts{6};


  /* The lower and upper thresholds for determining whether to continue
   * splitting line segments and whether to reject a line segment as being
   * too straight.
   */
  constexpr double LowerRadianThresHold{toRadiant(170.0)};
  constexpr double UpperRadianThresHold{toRadiant(175.0)};


  /* States and directions of each line, arc, and face. */
  enum class Direction
  {
    UnknownDirection,
    Ascending,
    Descending,
    Flat
  };

  enum class Flow
  {
    Up = 1,
    Down = -1
  };

  struct Face
  {
    FL::Point2DL *_offset;  /* start of face's data in render pool */
    int _n_points;         /* number of points */
    Flow _flow;            /* Face orientation: Asc/Descending */
    struct Face *_next;    /* next face in same contour, used */
                           /* during drop-out control */
  };


} // namespace

template <typename T>
struct Pool
{
  T* _cursor{};          /* Current cursor in render pool */
  T* _poolBegin{};       /* The render pool base address */
  T* _poolEnd{};         /* The render pool end  */
};

struct FT_RasterRec_
{
  Pool<FL::Point2DL> _pointPool;
  Pool<Face> _facePool;

  FL::Point2DL _last;
  long _minY{}, _maxY{};
  long _minX{}, _maxX{};

  FL::RasterResult _error{};

  FT_Outline *_outline{};

  int _nPoints;   /* number of points in current glyph */

  FL::Point2DL *_arc{}; /* current Bezier arc pointer */

  int _numFaces{}; /* current number of faces */

  Face *_currentFace{};   /* current face */
  Face *_startFace{}; /* head of linked list of faces */
  Face *_firstFace{}; /* contour's first face in case */
                      /* of impact */

  int _scaleShift; /* == 0  for bitmaps */
                   /* == 1  for 5-levels pixmaps */
                   /* == 2  for 17-levels pixmaps */

  int _scaleDelta; /* raster->precision_half for bitmaps */
                   /* 0 for pixmaps */

  FL::Point2DL _arcs[2 * MaxNumberBezierCurves + 1]; /* The Bezier stack */
};


constexpr auto scale(const FT_Raster &raster, int val)
{
  return (val << raster->_scaleShift) - raster->_scaleDelta;
}

constexpr FL::Point2DL scale(const FT_Raster &raster, const FT_Vector &p)
{
  return {scale(raster, p.x), scale(raster, p.y)};
}


/*
 * Finalizes the current Face and computes its height.  If it is
 * not 0, the face's fields are updated and a new face is
 * pushed on top of its coordinates.  Otherwise the current face
 * is kept and the recording of intersections is restarted.
 */
FL::RenderResult endFace(FT_RasterRec_ &raster)
{
  Face *newp{};

  auto n = static_cast<int>(raster._pointPool._cursor - raster._currentFace->_offset);
  /* It does not make sense to append a face with only 2 points, because they
   * cannot build a drawable face */
  if (n > 2) 
  {
    Face* oldp = raster._currentFace;
    oldp->_n_points = static_cast<int>(raster._pointPool._cursor - raster._currentFace->_offset);
    raster._currentFace = newp = raster._facePool._cursor;

    if (raster._facePool._cursor == raster._facePool._poolEnd)
    {
      raster._error = FL::RasterResult::Overflow;
      return FL::RenderResult::Failure;
    }

    raster._facePool._cursor += 1;

    newp->_n_points = 0;
    newp->_offset = raster._pointPool._cursor;
    oldp->_next = newp;

    raster._numFaces++;
  }

  return FL::RenderResult::Success;
}


FL::RenderResult checkContour(FT_RasterRec_ &raster)
{
  /* Sometimes, the first and last face in a contour join on
     an integer scan-line; we must then remove the last intersection
     from the last face to get rid of doublets */
  if ((rasterFrac(raster._last.y) == 0 && raster._last.y >= raster._minY && raster._last.y <= raster._maxY))
  {
    if (raster._firstFace && raster._firstFace->_flow == raster._currentFace->_flow)
    {
      if (raster._pointPool._poolBegin == raster._pointPool._cursor)
      {
        return FL::RenderResult::Failure;
      }
      raster._pointPool._cursor--;
    }
  }

  Face *lastFace = raster._currentFace;
  if (endFace(raster) != FL::RenderResult::Success)
  {
    return FL::RenderResult::Failure;
  }

  /* close the `next face in contour' linked list */
  lastFace->_next = raster._firstFace;

  return FL::RenderResult::Success;
}


/*
 * Creates a new Face in the render pool.
 */
FL::RenderResult newFace(FT_Raster raster, Direction direction)
{
  if (raster->_startFace == nullptr)
  {
    if (raster->_facePool._cursor == raster->_facePool._poolEnd)
    {
      raster->_error = FL::RasterResult::Overflow;
      return FL::RenderResult::Failure;
    }
    raster->_currentFace = raster->_facePool._cursor; /* current face */
    raster->_startFace = raster->_currentFace;        /* first face in pool */
    raster->_facePool._cursor += 1;                   /* record face in buffer */
  }

  /* record face direction */
  switch (direction)
  {
  case Direction::Ascending:
    raster->_currentFace->_flow = Flow::Up;
    break;

  case Direction::Descending:
    raster->_currentFace->_flow = Flow::Down;
    break;

  default:
    raster->_error = FL::RasterResult::Invalid_Map;
    return FL::RenderResult::Failure;
  }

  /* initialize a few fields */
  {
    auto currentFace = raster->_currentFace;

    currentFace->_offset = raster->_pointPool._cursor; /* address of first coordinate */
    currentFace->_next = nullptr;
  }

  /* record the first face in a contour */
  if (raster->_firstFace == nullptr)
    raster->_firstFace = raster->_currentFace;

  return FL::RenderResult::Success;
}

FL::Point2DL *appendPoint(FL::Point2DL *list, const FL::Point2DL &p)
{
  *list = p;
  ++list;
  return list;
}

FL::Point2DL *appendPointCheck(FL::Point2DL *list, const FL::Point2DL &p)
{
  auto result = list;
  if (p.x != (list - 1)->x && p.y != (list - 1)->y)
  {
    result = appendPoint(list, p);
  }
  return result;
}


/* This function injects a new contour in the render pool. */
FL::RenderResult moveTo(FT_Vector *to, FT_Raster raster)
{
  /* if there was already a contour being built, perform some checks */
  if (raster->_startFace)
  {
    if (checkContour(*raster) != FL::RenderResult::Success)
    {
      return FL::RenderResult::Failure;
    }
  }

  if (newFace(raster, Direction::Ascending) != FL::RenderResult::Success)
  {
    return FL::RenderResult::Failure;
  }

  /* set the `current last point' */
  raster->_last.x = scale(raster, to->x);
  raster->_last.y = scale(raster, to->y);

  raster->_firstFace = nullptr;

  raster->_pointPool._cursor = appendPoint(raster->_pointPool._cursor, raster->_last);

  return FL::RenderResult::Success;
}

/*
 * This function injects a new line segment in the render pool and
 * adjusts the faces list accordingly.
 */
FL::RenderResult lineTo(FT_Vector *to, FT_Raster raster)
{
  raster->_last.x = scale(raster, to->x);
  raster->_last.y = scale(raster, to->y);

  raster->_pointPool._cursor = appendPoint(raster->_pointPool._cursor, raster->_last);

  return FL::RenderResult::Success;
}


/*
 * Clears the Bezier stack and pushes a new arc on top of it.
 */
void pushConic(FT_Raster raster, FT_Vector *p2, FT_Vector *p3)
{
  FL::Point2DL *arc;

  raster->_arc = arc = raster->_arcs;
  arc[0] = scale(raster, *p3);
  arc[1] = scale(raster, *p2);

  arc[2] = raster->_last;
}


/*
 * Clears the Bezier stack and pushes a new third-order Bezier arc on
 * top of it.
 */
void pushCubic(FT_Raster raster, FT_Vector *p2, FT_Vector *p3, FT_Vector *p4)
{
  FL::Point2DL *arc{};
  raster->_arc = arc = raster->_arcs;

  arc[0] = scale(raster, *p4);
  arc[1] = scale(raster, *p3);
  arc[2] = scale(raster, *p2);
  arc[3] = raster->_last;
}

/*
 * Subdivides one second-order Bezier arc into two joint sub-arcs in
 * the Bezier stack.
 */
void splitConic(FL::Point2DL *base)
{
  base[4].x = base[2].x;
  long b = base[1].x;
  long a = base[3].x = (base[2].x + b + 1) >> 1;
  b = base[1].x = (base[0].x + b + 1) >> 1;
  base[2].x = (a + b + 1) >> 1;

  base[4].y = base[2].y;
  b = base[1].y;
  a = base[3].y = (base[2].y + b + 1) >> 1;
  b = base[1].y = (base[0].y + b + 1) >> 1;
  base[2].y = (a + b) / 2;
}

/*
 * Subdivides a third-order Bezier arc into two joint sub-arcs in
 * the Bezier stack.
 */
void splitCubic(FL::Point2DL *base)
{
  long a, b;

  base[6].x = base[3].x;
  long c = base[1].x;
  long d = base[2].x;
  base[1].x = a = (base[0].x + c + 1) >> 1;
  base[5].x = b = (base[3].x + d + 1) >> 1;
  c = (c + d + 1) >> 1;
  base[2].x = a = (a + c + 1) >> 1;
  base[4].x = b = (b + c + 1) >> 1;
  base[3].x = (a + b + 1) >> 1;

  base[6].y = base[3].y;
  c = base[1].y;
  d = base[2].y;
  base[1].y = a = (base[0].y + c + 1) >> 1;
  base[5].y = b = (base[3].y + d + 1) >> 1;
  c = (c + d + 1) >> 1;
  base[2].y = a = (a + c + 1) >> 1;
  base[4].y = b = (b + c + 1) >> 1;
  base[3].y = (a + b + 1) >> 1;
}

using TSplitter = void(FL::Point2DL *base);
/* A function type describing the functions used to split bezier arcs */


FL::RenderResult bezierUpSign(FT_Raster raster, int degree, TSplitter splitter, long miny,
                              long maxy, long sign)
{
  long x;

  FL::Point2DL *arc = raster->_arc;
  long y1 = arc[degree].y;
  long y2 = arc[0].y;
  FL::Point2DL *top = raster->_pointPool._cursor;

  FL_SCOPE_EXIT{
    raster->_pointPool._cursor = top;
    raster->_arc -= degree;
  };

  if (y2 < miny || y1 > maxy)
  {
    return FL::RenderResult::Success;
  }

  FL::Point2DL *start_arc = arc;

  /* loop while there is still an arc on the bezier stack */
  while (arc >= start_arc)
  {
    long x1 = arc[degree].x; /* start of top-most arc */
    y1 = arc[degree].y;
    long x2 = arc[0].x; /* final of the top-most arc */
    y2 = arc[0].y;

    long e2 = rasterFloor(y2); /* integer end y */
    if (e2 > maxy)
      e2 = rasterFloor(maxy);

    long e0 = rasterCeiling(y1);
    if (e0 < miny)
      e0 = rasterCeiling(miny);

    long y = (e0 + e2) / 2;

    if (e2 == e0)
    {
      top = appendPoint(top, {x2, sign * y2});

      arc -= degree; /* pop the arc */
    }
    else
    {
      if (x2 < x1)
      {
        if (sign > 0)
          x = (x1 - multiplyDivide(x2 - x1, y - e0, e2 - e0));
        else
          x = (x1 + multiplyDivide(x1 - x2, y - e0, e2 - e0));
      }
      else
      {
        if (sign > 0)
          x = (x2 + multiplyDivide(x2 - x1, y - e0, e2 - e0));
        else
          x = (x2 - multiplyDivide(x1 - x2, y - e0, e2 - e0));
      }

      double angle = boundingTriangleAngle(x1, e0, x, y, x2, e2);

      if (abs(x2 - x) >= 16 && e2 - y >= 16 && angle < LowerRadianThresHold)
      {
        /* if the arc's bounding triangle's angle is too great, split it */
        splitter(arc);
        arc += degree;
      }

      else
      {
        /* otherwise, approximate it as a segment and compute
           its intersection with the current scanline */
        if (((x2 < x && x < x1) || (x1 < x && x < x2)) && angle < UpperRadianThresHold)
          top = appendPoint(top, {x, sign * y});

        arc -= degree; /* pop the arc */
      }
    }
  }

  return FL::RenderResult::Success;
}

FL::RenderResult bezierUp(FT_Raster raster, int degree, TSplitter splitter, long miny, long maxy)
{
  return bezierUpSign(raster, degree, splitter, miny, maxy, 1);
}

/*
 * Computes the scan-line intersections of a descending second-order
 * Bezier arc and stores them in the render pool.  The arc is taken
 * from the top of the stack.
 */
FL::RenderResult bezierDown(FT_Raster raster, int degree, TSplitter splitter, long miny, long maxy)
{
  auto arc = raster->_arc;

  arc[0].y = -arc[0].y;
  arc[1].y = -arc[1].y;
  arc[2].y = -arc[2].y;
  if (degree > 2)
    arc[3].y = -arc[3].y;

  auto result = bezierUpSign(raster, degree, splitter, -maxy, -miny, -1);

  arc[0].y = -arc[0].y;
  return result;
}


FL::RenderResult bezierRightSign(FT_Raster raster, int degree, TSplitter splitter, long minx,
                                 long maxx, long sign)
{
  long y;

  auto arc = raster->_arc;
  long x1 = arc[degree].x;
  long x2 = arc[0].x;
  auto top = raster->_pointPool._cursor;

  FL_SCOPE_EXIT {
    raster->_pointPool._cursor = top;
    raster->_arc -= degree;
  };

  if (x1 < minx || x2 > maxx)
  {
    return FL::RenderResult::Success;
  }

  const auto startArc = arc;

  /* loop while there is still an arc on the bezier stack */
  while (arc >= startArc)
  {
    x1 = arc[degree].x; /* start of right-most arc */
    long y1 = arc[degree].y;
    x2 = arc[0].x; /* final of the right-most arc */
    long y2 = arc[0].y;

    long e2 = rasterFloor(x2); /* integer end x */
    if (e2 > maxx)
      e2 = rasterFloor(maxx);

    long e0 = rasterCeiling(x1);
    if (e0 < minx)
      e0 = rasterCeiling(minx);

    long x = (e0 + e2) / 2;

    if (e2 == e0)
    {
      top = appendPoint(top, {sign * x2, y2});

      arc -= degree; /* pop the arc */
    }
    else
    {
      if (y2 < y1)
      {
        if (sign > 0)
          y = (y1 - multiplyDivide(y2 - y1, x - e0, e2 - e0));
        else
          y = (y1 + multiplyDivide(y1 - y2, x - e0, e2 - e0));
      }
      else
      {
        if (sign > 0)
          y = (y2 + multiplyDivide(y2 - y1, x - e0, e2 - e0));
        else
          y = (y2 - multiplyDivide(y1 - y2, x - e0, e2 - e0));
      }

      double angle = boundingTriangleAngle(e0, y1, x, y, e2, y2);

      if (e2 - x >= 64 && abs(y2 - y) >= 64 && angle < LowerRadianThresHold)
      {
        /* if the arc's bounding triangle's angle is too great, split it */
        splitter(arc);
        arc += degree;
      }

      else
      {
        /* otherwise, approximate it as a segment and compute
           its intersection with the current scanline */
        if (((y2 < y && y < y1) || (y1 < y && y < y2)) && angle < UpperRadianThresHold)
          top = appendPoint(top, {sign * x, y});

        arc -= degree; /* pop the arc */
      }
    }
  }

  return FL::RenderResult::Success;
}


FL::RenderResult bezierRight(FT_Raster raster, int degree, TSplitter splitter, long minx, long maxx)
{
  return bezierRightSign(raster, degree, splitter, minx, maxx, 1);
}

/*
 * Computes the scan-line intersections of a descending second-order
 * Bezier arc and stores them in the render pool.  The arc is taken
 * from the top of the stack.
 */
FL::RenderResult bezierLeft(FT_Raster raster, int degree, TSplitter splitter, long minx, long maxx)
{
  auto arc = raster->_arc;

  arc[0].x = -arc[0].x;
  arc[1].x = -arc[1].x;
  arc[2].x = -arc[2].x;
  if (degree > 2)
    arc[3].x = -arc[3].x;

  auto result = bezierRightSign(raster, degree, splitter, -maxx, -minx, -1);

  arc[0].x = -arc[0].x;
  return result;
}


//
// Injects a new conic Bezier arc and adjusts the face list
// accordingly.
//
FL::RenderResult conicTo(FT_Vector *control, FT_Vector *to, FT_Raster raster)
{
  long y3, ymin, ymax;
  long x3, xmin, xmax;
  Direction state_bez;

  pushConic(raster, control, to);

  do
  {
    long y1 = raster->_arc[2].y;
    long y2 = raster->_arc[1].y;
    y3 = raster->_arc[0].y;
    long x1 = raster->_arc[2].x;
    long x2 = raster->_arc[1].x;
    x3 = raster->_arc[0].x;

    /* first, categorize the Bezier arc */

    if (y1 <= y3)
    {
      ymin = y1;
      ymax = y3;
    }
    else
    {
      ymin = y3;
      ymax = y1;
    }

    if (x1 <= x3)
    {
      xmin = x1;
      xmax = x3;
    }
    else
    {
      xmin = x3;
      xmax = x1;
    }

    if ((ymax - ymin) >= (xmax - xmin))
    {
      if (y2 < ymin || y2 > ymax)
      {
        /* this arc has no given direction, split it !! */
        splitConic(raster->_arc);
        raster->_arc += 2;
      }
      else if (y1 == y3)
      {
        /* this arc is flat, ignore it and pop it from the bezier stack */
        raster->_arc -= 2;
      }
      else
      {
        /* the arc is y-monotonous, either ascending or descending
           detect a change of direction */
        state_bez = y1 < y3 ? Direction::Ascending : Direction::Descending;

        /* now call the appropriate routine */
        if (state_bez == Direction::Ascending)
        {
          if (bezierUp(raster, 2, splitConic, raster->_minY, raster->_maxY) ==
              FL::RenderResult::Failure)
            return FL::RenderResult::Failure;
        }
        else if (bezierDown(raster, 2, splitConic, raster->_minY, raster->_maxY) ==
                 FL::RenderResult::Failure)
          return FL::RenderResult::Failure;
      }
    }

    else
    {
      if (x2 < xmin || x2 > xmax)
      {
        /* this arc has no given direction, split it !! */
        splitConic(raster->_arc);
        raster->_arc += 2;
      }
      else if (x1 == x3)
      {
        /* this arc is flat, ignore it and pop it from the bezier stack */
        raster->_arc -= 2;
      }
      else
      {
        /* the arc is y-monotonous, either ascending or descending
           detect a change of direction */
        state_bez = x1 < x3 ? Direction::Ascending : Direction::Descending;

        /* now call the appropriate routine */
        if (state_bez == Direction::Ascending)
        {
          if (bezierRight(raster, 2, splitConic, raster->_minX, raster->_maxX) ==
              FL::RenderResult::Failure)
            return FL::RenderResult::Failure;
        }
        else if (bezierLeft(raster, 2, splitConic, raster->_minX, raster->_maxX) ==
                 FL::RenderResult::Failure)
          return FL::RenderResult::Failure;
      }
    }

  } while (raster->_arc >= raster->_arcs);

  raster->_last.x = x3;
  raster->_last.y = y3;


  raster->_pointPool._cursor = appendPointCheck(raster->_pointPool._cursor, {raster->_last.x, raster->_last.y});

  return FL::RenderResult::Success;
}

/*
 * Injects a new cubic Bezier arc and adjusts the face list
 * accordingly.
 */
FL::RenderResult cubicTo(FT_Vector *control1, FT_Vector *control2, FT_Vector *to, FT_Raster raster)
{
  long y4, x4, ymin1, ymax1, ymin2, ymax2;

  pushCubic(raster, control1, control2, to);

  do
  {
    long y1 = raster->_arc[3].y;
    long y2 = raster->_arc[2].y;
    long y3 = raster->_arc[1].y;
    y4 = raster->_arc[0].y;
    x4 = raster->_arc[0].x;

    /* first, categorize the Bezier arc */

    if (y1 <= y4)
    {
      ymin1 = y1;
      ymax1 = y4;
    }
    else
    {
      ymin1 = y4;
      ymax1 = y1;
    }

    if (y2 <= y3)
    {
      ymin2 = y2;
      ymax2 = y3;
    }
    else
    {
      ymin2 = y3;
      ymax2 = y2;
    }

    if (ymin2 < ymin1 || ymax2 > ymax1)
    {
      // this arc has no given direction, split it!
      splitCubic(raster->_arc);
      raster->_arc += 3;
    }
    else if (y1 == y4)
    {
      // this arc is flat, ignore it and pop it from the bezier stack
      raster->_arc -= 3;
    }
    else
    {
      Direction state_bez = (y1 <= y4) ? Direction::Ascending : Direction::Descending;

      /* compute intersections */
      if (state_bez == Direction::Ascending)
      {
        if (bezierUp(raster, 3, splitCubic, raster->_minY, raster->_maxY) ==
            FL::RenderResult::Failure)
          return FL::RenderResult::Failure;
      }
      else if (bezierDown(raster, 3, splitCubic, raster->_minY, raster->_maxY) ==
               FL::RenderResult::Failure)
        return FL::RenderResult::Failure;
    }

  } while (raster->_arc >= raster->_arcs);

  raster->_last.x = x4;
  raster->_last.y = y4;

  raster->_pointPool._cursor = appendPointCheck(raster->_pointPool._cursor, {raster->_last.x, raster->_last.y});

  return FL::RenderResult::Success;
}


int computeOrientation(int n_points, FL::Point2DL *pt, FT_BBox *bbox)
{
  FL::Point2DD v1, v2;
  FL::Point2DL *p[3];

  // This should not happen, because faces should at least have three points
  if (n_points < 3)
  {
    return 0;
  }

  for (int n = 0; n_points--; pt++)
  {
    if (pt->x == bbox->xMin || pt->x == bbox->xMax || pt->y == bbox->yMin || pt->y == bbox->yMax)
    {
      p[n++] = pt;

      if (n == 3)
        break;
    }
  }

  v1.x = p[1]->x - p[0]->x;
  v1.y = p[1]->y - p[0]->y;
  v2.x = p[2]->x - p[1]->x;
  v2.y = p[2]->y - p[1]->y;
  return (v1.x * v2.y - v1.y * v2.x) > 0.0 ? 1 : -1;
}


/*
 * Adjusts all links in the faces list.  Called when the outline
 * parsing is done.
 */
FL::RenderResult FL::FreeTypeFont::finalizeFaceTable(FL::FreeTypeOutline *ch, FT_Raster raster)
{
  Face *p;
  Point2DF vmin, vmax, v1;
  FT_BBox bbox, lastBBox;
  bool isPolygon{};

  int numFaces = raster->_numFaces;
  Face *start = raster->_startFace;

  /* Compute the size require for indexes array. */
  std::size_t numVertices =
      std::accumulate(raster->_startFace, raster->_startFace + raster->_numFaces, 0,
                      [](auto sum, const auto &face) { return sum + face._n_points; });

  /* Build up indexes and vertices from points, compute the size and
     character advance as well */
  ch->_facesIndexes = std::vector<short>(numVertices + raster->_numFaces + 1, -1);
  auto index = ch->_facesIndexes.begin();
  ch->_polygons.resize(raster->_numFaces);
  auto flag = ch->_polygons.begin();
  ch->_vertices.resize(numVertices);
  auto vertex = ch->_vertices.begin();

  int lastDirection = 0;
  int j = 0;

  vmin.x = vmin.y = 0.0;
  vmax.x = vmax.y = 0.0;
  for (p = start, numFaces = raster->_numFaces; numFaces--; ++p)
  {
    auto p0 = &p->_offset[0];
    bbox.xMin = bbox.xMax = p0->x;
    bbox.yMin = bbox.yMax = p0->y;

    /* Store scaled points and assign indexes to each point */
    for (int i = 0; i < p->_n_points; ++i)
    {
      const auto currentPoint = &p->_offset[i];

      /* Compute the bounding box of the contour */
      if (currentPoint->x < bbox.xMin)
        bbox.xMin = currentPoint->x;
      else if (currentPoint->x > bbox.xMax)
        bbox.xMax = currentPoint->x;

      if (currentPoint->y < bbox.yMin)
        bbox.yMin = currentPoint->y;
      else if (currentPoint->y > bbox.yMax)
        bbox.yMax = currentPoint->y;

      /* Scale the point */
      v1.x = currentPoint->x >> 6;
      v1.y = currentPoint->y >> 6;
      v1.x /= KludgeFactor;
      v1.y /= KludgeFactor;

      /* Compute the overall bounding box of the glyph */
      if (v1.x < vmin.x)
        vmin.x = v1.x;
      else if (v1.x > vmax.x)
        vmax.x = v1.x;

      if (v1.y < vmin.y)
        vmin.y = v1.y;
      else if (v1.y > vmax.y)
        vmax.y = v1.y;

      *vertex++ = v1;
      *index++ = j++;
    }
    *index++ = -1;

    /* Compute the orientation of the contour by looking at its normal */
    int direction = computeOrientation(p->_n_points, p->_offset, &bbox);

    if (lastDirection)
      isPolygon =
          (direction == lastDirection || !(lastBBox.xMin < bbox.xMin && lastBBox.xMax > bbox.xMax &&
                                           lastBBox.yMin < bbox.yMin && lastBBox.yMax > bbox.yMax));
    else
      isPolygon = true;

    *flag++ = isPolygon;

    if (isPolygon)
    {
      lastDirection = direction;
      lastBBox = bbox;
    }
  }
  *index = -1;

  ch->_size.x = vmax.x - vmin.x;
  ch->_size.y = vmax.y - vmin.y;
  ch->_advance = ch->_size.x + 0.1f;

  return FL::RenderResult::Success;
}

/*
 * Converts a glyph into a series of segments and arcs and makes a
 * faces list with them.
 */
FL::RenderResult FL::FreeTypeFont::convertGlyph(FL::FreeTypeOutline *ch, FT_Raster raster,
                                                FT_Outline *outline)
{
  static FT_Outline_Funcs interface_table = {reinterpret_cast<FT_Outline_MoveTo_Func>(moveTo),
                                             reinterpret_cast<FT_Outline_LineTo_Func>(lineTo),
                                             reinterpret_cast<FT_Outline_ConicTo_Func>(conicTo),
                                             reinterpret_cast<FT_Outline_CubicTo_Func>(cubicTo)};

  /* Set up state in the raster object */
  raster->_startFace = nullptr;
  raster->_currentFace = raster->_facePool._cursor;
  raster->_currentFace->_offset = raster->_pointPool._cursor;
  raster->_numFaces = 0;

  if (auto error = FT_Outline_Decompose(outline, &interface_table, raster); error != 0)
    return FL::RenderResult::Failure;

  /* XXX: the error condition is in raster->error */

  /* Check the last contour if needed */
  if (checkContour(*raster) == FL::RenderResult::Failure)
    return FL::RenderResult::Failure;

  /* Finalize faces list */
  return finalizeFaceTable(ch, raster);
}


FL::RasterResult FL::FreeTypeFont::generateGlyph(FL::FreeTypeOutline &ch)
{
  Face facePool[64] = {};
  FL::Point2DL pointPool[1024] = {};
  FT_RasterRec_ rec;
  auto raster = &rec;
  FT_Outline *outline = &ch._glyph->outline;

  raster->_facePool._cursor = raster->_facePool._poolBegin = facePool;
  raster->_facePool._poolEnd = facePool + std::size(facePool);

  raster->_pointPool._cursor = raster->_pointPool._poolBegin = pointPool;
  raster->_pointPool._poolEnd = pointPool + std::size(pointPool);

  /* return immediately if the outline is empty */
  if (outline->n_points == 0 || outline->n_contours <= 0)
    return RasterResult::Ok;

  if (!outline || !outline->contours || !outline->points)
    return RasterResult::Invalid_Outline;

  if (outline->n_points != outline->contours[outline->n_contours - 1] + 1)
    return RasterResult::Invalid_Outline;

  raster->_outline = outline;

  raster->_scaleShift = RasterParams::PrecisionBits - InputBIts;
  raster->_scaleDelta = RasterParams::PrecisionHalf;

  int top = bitmapCeiling(ch._glyph->metrics.horiBearingY);
  int bottom = bitmapFloor(ch._glyph->metrics.horiBearingY - ch._glyph->metrics.height);
  int left = bitmapCeiling(ch._glyph->metrics.horiBearingX);
  int right = bitmapFloor(ch._glyph->metrics.horiBearingX + ch._glyph->metrics.width);
  int y_min = 0;
  int y_max = bitmapTrunc(top - bottom);
  int x_min = 0;
  int x_max = bitmapTrunc(right - left);

  raster->_maxY = ((long)y_max << RasterParams::PrecisionBits) - 1;
  raster->_minY = (long)y_min << RasterParams::PrecisionBits;
  raster->_maxX = ((long)x_max << RasterParams::PrecisionBits) - 1;
  raster->_minX = (long)x_min << RasterParams::PrecisionBits;

  auto error = convertGlyph(&ch, raster, raster->_outline);
  if (error == FL::RenderResult::Failure)
    return FL::RasterResult::Invalid_Outline;

  return FL::RasterResult::Ok;
}


FL::FreeTypeOutline FL::FreeTypeFont::loadChar(Char c)
{
  FreeTypeOutline result{};

  int flags = FT_LOAD_DEFAULT | FT_LOAD_NO_BITMAP;
  if (!_hint)
    flags |= FT_LOAD_NO_HINTING;

  FT_UInt i = FT_Get_Char_Index(_face, c);
  FT_Error error = FT_Load_Glyph(_face, i, flags);

  auto tmp  = createGlyphChar(c, _face->glyph);
  if (!tmp)
  {
    return result;
  }

  result = std::move(*tmp);

  /* Fix character advancement */
  if (result._size.x == 0.0f)
    result._advance = (_face->max_advance_width >> 6) / KludgeFactor;


  /* Fill up FL outline struct */
  auto outline = &result._outline;
  outline->_outlineCount = 0;
  outline->_xAdvance = result._advance;
  outline->_yAdvance = 0.0;

  if (result._vertices.empty())
  {
    outline->_vertex.clear();
    return result;
  }

  /* Count the number of outline contours */
  for (auto index = result._facesIndexes.begin(); *index != -1; index++, outline->_outlineCount++)
    for (index++; *index != -1; index++)
      ;

  /* Create the vertex count and vertex arrays */
  outline->_vertexCounts.resize(outline->_outlineCount);
  auto vertexCount = outline->_vertexCounts.begin();

  outline->_vertex.resize(outline->_outlineCount);
  auto vertex = outline->_vertex.begin();
  std::vector<short>::iterator start;
  for (auto index = result._facesIndexes.begin(); *(start = index) != -1; index++)
  {
    for (index++; *index != -1; index++)
      ;
    *vertexCount = index - start;
    vertex->resize(*vertexCount);
    auto v = vertex->begin();

    auto end = index--;
    while (index >= start)
    {
      int j = *index;
      *v = result._vertices[j];
      if (index > start)
      {
        --index;
      }
      else
      {
        break;
      }
      ++v;
    }
    index = end;

    ++vertexCount;
    ++vertex;
  }

  return result;
}

FL::FreeTypeOutline *FL::FreeTypeFont::characterUniFreetypeOutline(GLuint c)
{
  FreeTypeOutline *result{};
  if (c < 256)
  {
    if (_char8[c].empty())
    {
      _char8[c] = loadChar(c);
    }

    if (!_char8[c].empty())
    {
      result = &_char8[c];
    }
  }

  return result;
}

const FL::Outline *FL::FreeTypeFont::characterOutline(GLuint c)
{
  const FL::Outline *result{};
  if (const auto *freeTypeOutline = characterUniFreetypeOutline(c); freeTypeOutline)
  {
    result = &freeTypeOutline->outline();
  }
  return result;
}


const FL::Outline *FL::FreeTypeFont::uniOutline(GLuint c)
{
  const Outline *result{};
  if (c < 256)
  {
    return characterOutline(c);
  }

  auto codePointSort = [](const auto &x, const auto &y) { return x.first < y.first; };

  auto findIt = _char16.lower_bound(c);

  if (findIt != _char16.end() && findIt->first == c)
  {
    return &findIt->second.outline();
  }

  // Cannot find code point c, load the glyph char
  auto outline = loadChar(c);
  findIt = _char16.insert(findIt, std::make_pair(c, std::move(outline)));
  result = &findIt->second.outline();

  return result;
}


FL::FreeTypeOutline *FL::FreeTypeFont::uniFreetypeOutline(GLuint c)
{
  FreeTypeOutline *result{};
  if (c < 256)
  {
    result = characterUniFreetypeOutline(c);
    return result;
  }

  auto codePointSort = [](const auto &x, const auto &y) { return x.first < y.first; };

  auto findIt = std::lower_bound(_char16.begin(), _char16.end(),
                                 std::make_pair(c, FreeTypeOutline{}), codePointSort);

  if (findIt != _char16.end() && findIt->first == c)
  {
    result = &findIt->second;
    return result;
  }

  // Cannot find code point c, load the glyph char
  auto outline = loadChar(c);
  findIt = _char16.insert(findIt, std::make_pair(c, std::move(outline)));
  result = &findIt->second;

  return result;
}

void FL::FreeTypeFont::convertBitmap(int width, int height, int pitch, int pitch2,
                                     const unsigned char *source, unsigned char *dest) const
{
  for (int j = 0; j < height; j++)
  {
    unsigned char bit = 0x80;
    auto *p = source;
    int c = *p;
    for (int i = 0; i < width; i++)
    {
      if ((c & bit))
        dest[(height - 1 - j) * pitch2 + i / 8] |= (1 << (7 - (i & 7)));

      bit >>= 1;
      if (!bit)
      {
        bit = 0x80;
        p++;
        c = *p;
      }
    }

    source += pitch;
  }
}


const FL::Bitmap *FL::FreeTypeFont::uniBitmap(GLuint c)
{
  auto *outline = uniFreetypeOutline(c);

  const FT_GlyphSlot glyph = outline->_glyph;
  FT_Bitmap bit2;

  FL::Bitmap *bit3 = &outline->_bitmap;
  if (bit3->_bitmap)
    return bit3;

  FT_Pos left = bitmapFloor(glyph->metrics.horiBearingX);
  FT_Pos right = bitmapCeiling(glyph->metrics.horiBearingX + glyph->metrics.width);
  FT_Pos width = bitmapTrunc(right - left);

  FT_Pos top = bitmapCeiling(glyph->metrics.horiBearingY);
  FT_Pos bottom = bitmapFloor(glyph->metrics.horiBearingY - glyph->metrics.height);
  FT_Pos height = bitmapTrunc(top - bottom);

  FT_Pos bearing_x = bitmapTrunc(glyph->metrics.horiBearingX);
  FT_Pos bearing_y = bitmapTrunc(glyph->metrics.horiBearingY);


  if (glyph->format == ft_glyph_format_outline)
  {
    FT_Pos pitch = (width + 7) >> 3;
    FT_Pos size = pitch * height;
    FT_Pos pitch2 = ((width + (PixelRowAlignment << 3) - 1) >> 5) << 2;
    FT_Pos size2 = pitch2 * height;

    bit2.width = width;
    bit2.rows = height;
    bit2.pitch = pitch;
    bit2.pixel_mode = ft_pixel_mode_mono;
    bit2.buffer = new GLubyte[size];

    bit3->_width = bit2.width;
    bit3->_height = bit2.rows;
    bit3->_xorig = -bearing_x;
    bit3->_yorig = height - bearing_y;
    bit3->_xmove = bitmapTrunc(glyph->metrics.horiAdvance);
    bit3->_ymove = 0.0f;
    bit3->_bitmap = std::make_unique<GLubyte[]>(size2);

    FT_Outline_Translate(&glyph->outline, -left, -bottom);
    memset(bit2.buffer, 0, size);
    memset(bit3->_bitmap.get(), 0, size2);

    if (_lowPrec)
    {
      glyph->outline.flags &= ~ft_outline_high_precision;
    }

    FT_Error error = FT_Outline_Get_Bitmap(library, &glyph->outline, &bit2);

    convertBitmap(width, height, pitch, pitch2, bit2.buffer, bit3->_bitmap.get());

    delete[] bit2.buffer;
  }
  else
  {
    bit3->_width = glyph->bitmap.width;
    bit3->_height = glyph->bitmap.rows;
    bit3->_xorig = -bearing_x;
    bit3->_yorig = height - bearing_y;
    bit3->_xmove = bitmapTrunc(glyph->metrics.horiAdvance);
    bit3->_ymove = 0.0f;
    bit3->_bitmap.reset(glyph->bitmap.buffer);
  }

  return bit3;
}
