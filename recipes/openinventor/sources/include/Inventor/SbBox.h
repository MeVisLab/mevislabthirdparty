/*
 *
 *  Copyright (C) 2000 Silicon Graphics, Inc.  All Rights Reserved. 
 *
 *  This library is free software; you can redistribute it and/or
 *  modify it under the terms of the GNU Lesser General Public
 *  License as published by the Free Software Foundation; either
 *  version 2.1 of the License, or (at your option) any later version.
 *
 *  This library is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 *  Lesser General Public License for more details.
 *
 *  Further, this software is distributed without any warranty that it is
 *  free of the rightful claim of any third person regarding infringement
 *  or the like.  Any license provided herein, whether implied or
 *  otherwise, applies only to this software file.  Patent licenses, if
 *  any, provided herein do not apply to combinations of this program with
 *  other software, or any other product whatsoever.
 * 
 *  You should have received a copy of the GNU Lesser General Public
 *  License along with this library; if not, write to the Free Software
 *  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 *
 *  Contact information: Silicon Graphics, Inc., 1600 Amphitheatre Pkwy,
 *  Mountain View, CA  94043, or:
 * 
 *  http://www.sgi.com 
 * 
 *  For further information regarding this notice, see: 
 * 
 *  http://oss.sgi.com/projects/GenInfo/NoticeExplan/
 *
 */


/*
 * Copyright (C) 1990,91   Silicon Graphics, Inc.
 *
 _______________________________________________________________________
 ______________  S I L I C O N   G R A P H I C S   I N C .  ____________
 |
 |   $Revision: 1.1.1.1 $
 |
 |   Description:
 |      This file contains definitions of SbBoxes, 2D/3D boxes. A
 |      box has planes parallel to the major axes and can therefore
 |      be specified by two points on a diagonal.  The points with minimum
 |      and maximum x, y, and z coordinates are used.
 |
 |   Author(s)          : Paul S. Strauss, Nick Thompson, David Mott
 |
 ______________  S I L I C O N   G R A P H I C S   I N C .  ____________
 _______________________________________________________________________
 */

#ifndef _SB_BOX_
#define _SB_BOX_

#include <Inventor/system/SbSystem.h>
#include <Inventor/SbBasic.h>
#include <Inventor/SbLinear.h>

////////////////////////////////////////////////////////////////////////////////
//! 3D box class.
/*!
\class SbBox3f
\ingroup Basics
3D box which has planes parallel to the major axes and is specified by two
points on a diagonal. This class is part of the standard Inventor
datatype classes and is used as input and output to geometry operations (see
SoGetBoundingBoxAction).

\par See Also
\par
SbXfBox3f, SbBox2f, SbBox2s, SbVec3f, SbVec2f, SbVec2s, SbMatrix, SoGetBoundingBoxAction
*/
////////////////////////////////////////////////////////////////////////////////

class INVENTOR_API SbBox3f {
  public:

    //! Empty box constructor.
    SbBox3f()                                           { makeEmpty(); }

    //! Constructor given bounds 
    SbBox3f(float xmin, float ymin, float zmin,
            float xmax, float ymax, float zmax)
        { min.setValue(xmin, ymin, zmin); max.setValue(xmax, ymax, zmax); }

    //! Constructor given minimum and maximum points 
    //! \p min and \p max are the corners of the diagonal that define the box.
    SbBox3f(const SbVec3f &min, const SbVec3f &max)
        { this->min = min; this->max = max; }

    //! Destructor.
    ~SbBox3f()                                          { }

    //! Returns the minimum point of the box. The minimum point is
    //! the corner of the box with the lowest X, Y, and Z values.
    const SbVec3f &     getMin() const { return min; }
    //! Returns the maximum point of the box. The maximum
    //! point is the corner of the box with the highest X, Y, and Z values.
    const SbVec3f &     getMax() const { return max; }
    //! Returns the minimum point of the box. The minimum point is
    //! the corner of the box with the lowest X, Y, and Z values.
    SbVec3f &           getMin()       { return min; }
    //! Returns the maximum point of the box. The maximum
    //! point is the corner of the box with the highest X, Y, and Z values.
    SbVec3f &           getMax()       { return max; }

    //! Returns the center of the box.
    SbVec3f     getCenter() const;

    //! Extends Box3f (if necessary) to contain given 3D point
    void        extendBy(const SbVec3f &pt);

    //! Extends Box3f (if necessary) to contain given Box3f
    void        extendBy(const SbBox3f &bb);

    //! Returns TRUE if intersection of given point and Box3f is not empty
    bool        intersect(const SbVec3f &pt) const;

    //! Returns TRUE if intersection of given Box3f and Box3f is not empty
    bool        intersect(const SbBox3f &bb) const;

    //! Returns TRUE if bounding box is completely outside the
    //! view-volume defined by the model+view+projection matrix given.
    //! "cullBits" keeps track of which view-volume clipping planes the
    //! box is completely inside of; if a 'parent' bounding box of this
    //! bounding box was found to be completely inside the left/right
    //! clipping planes, the low bit of cullBits will be set to zero,
    //! and this routine will not test this box against those planes.
    //! When cullBits is zero, it is a waste of time to call this
    //! function!  Before calling this the first time, set cullBits to
    //! 7 (SoGLRenderAction and SoSeparator will handle this
    //! automatically for render culling).
    bool        outside(const SbMatrix &MVP, int &cullBits) const;

    //! Common get and set functions
    void        setBounds(float xmin, float ymin, float zmin,
                          float xmax, float ymax, float zmax)
        { min.setValue(xmin, ymin, zmin); max.setValue(xmax, ymax, zmax); }

    void        setBounds(const SbVec3f &_min, const SbVec3f &_max)
        { min = _min; max = _max; }

    void        getBounds(float &xmin, float &ymin, float &zmin,
                          float &xmax, float &ymax, float &zmax) const
        { min.getValue(xmin, ymin, zmin); max.getValue(xmax, ymax, zmax); }

    void        getBounds(SbVec3f &_min, SbVec3f &_max) const
        { _min = min; _max = max; }

    //! Returns the closest point on the box to the given point.
    //! (Returns the point on the center of the Z face if passed the center.)
    SbVec3f     getClosestPoint(const SbVec3f &point);

    //! Gets box origin which is the same as the minimum corner of the box.
    void        getOrigin(float &originX,
                          float &originY,
                          float &originZ) const
        { originX = min[0]; originY = min[1]; originZ = min[2]; }

    //! Gets box size.
    void        getSize(float &sizeX, float &sizeY, float &sizeZ) const
        { sizeX = max[0] - min[0];
          sizeY = max[1] - min[1];
          sizeZ = max[2] - min[2]; }

    //! Makes an empty box.
    void        makeEmpty();

    //! Returns <tt>TRUE</tt> if the box is empty, and <tt>FALSE</tt> otherwise.
    bool        isEmpty()  const                { return max[0] < min[0]; }

    //! Returns <tt>TRUE</tt> if all three dimensions of the box have positive size,
    //! and <tt>FALSE</tt> otherwise.
    bool        hasVolume() const
        { return (max[0] > min[0] && max[1] > min[1] && max[2] > min[2] ); }

    //! Finds the span of a box along a specified direction.  The span is
    //! the total distance the box occupies along a given direction.  The total
    //! distance is returned in the form of a minimum and maximum distance from
    //! the origin of each of the corners of the box along the given direction.
    //! The difference between these two values is the span.
    void        getSpan(const SbVec3f &direction,
                        float &dMin, float &dMax) const;

    //! Transforms box by matrix, enlarging box to contain result.
    void        transform(const SbMatrix &m);

    //! Returns the volume of the box.
    float       getVolume() const;

    //! Equality comparisons
    friend INVENTOR_API bool            operator ==(const SbBox3f &b1, const SbBox3f &b2);
    friend INVENTOR_API bool            operator !=(const SbBox3f &b1, const SbBox3f &b2);

  private:
    //! Minimum and maximum points
    SbVec3f     min, max;
};

INVENTOR_API bool            operator ==(const SbBox3f &b1, const SbBox3f &b2);
inline INVENTOR_API bool     operator !=(const SbBox3f &b1, const SbBox3f &b2)
{ return !(b1 == b2); }

////////////////////////////////////////////////////////////////////////////////
//! 3D box with an associated transformation matrix.
/*!
\class SbXfBox3f
\ingroup Basics
A 3D box with an arbitrary transformation applied.  This class is useful when
a box will be transformed frequently; if an SbBox3f is used for this
purpose it will expand each time it is transformed in order to keep itself
axis-aligned.  Transformations can be accumulated on an SbXfBox3f
without expanding the box, and after all transformations have been done, the
box can be expanded to an axis-aligned box if necessary.

\par See Also
\par
SbBox3f, SbBox2f, SbBox2s, SbVec3f, SbVec2f, SbVec2s, SbMatrix, SoGetBoundingBoxAction
*/
////////////////////////////////////////////////////////////////////////////////

class INVENTOR_API SbXfBox3f : public SbBox3f {
  public:

    //! Constructors and destructor.
    SbXfBox3f();

    //! Constructors and destructor.
    SbXfBox3f(const SbVec3f &_min, const SbVec3f &_max);

    //! Constructors and destructor.
    SbXfBox3f(const SbBox3f &box);

    //! Constructors and destructor.
    ~SbXfBox3f()                                                { }

    //! Sets the transformation on the box.
    void                setTransform(const SbMatrix &m);

    //! Gets the transformation on the box, and its inverse.
    const SbMatrix &    getTransform() const        { return xform; }
    //! Gets the transformation on the box, and its inverse.
    const SbMatrix &    getInverse() const          { return xformInv; }

    //! Returns the center of the box.
    SbVec3f             getCenter() const;

    //! Extends the box (if necessary) to contain the given 3D point.  If the
    //! box has had a non-identity transformation applied using the
    //! setTransform() method, the point is assumed to be in the transformed
    //! space.  For example, the following code sequence:
    //! \code
    //! SbXfBox3f bbox; bbox.extendBy(SbVec3f(0,0,0));
    //! SbMatrix trans; trans.setTranslate(SbVec3f(1,1,1));
    //! bbox.setTransform(trans);
    //! bbox.extendBy(SbVec3f(0,0,0));
    //! \endcode
    //! will result in a bounding box extending from (-1,-1,-1) to
    //! (0,0,0) in bbox'es local (untransformed) space.
    void                extendBy(const SbVec3f &pt);

    //! Extends the box (if necessary) to contain the given SbBox3f.  If
    //! the box has had a non-identity transformation applied using the
    //! setTransform() method, the given SbBox3f is assumed to be in the
    //! transformed space.
    void                extendBy(const SbBox3f &bb)
        { extendBy(SbXfBox3f(bb)); }

    //! Extends the box (if necessary) to contain the given SbXfBox3f.
    void                extendBy(const SbXfBox3f &bb);

    //! Returns TRUE if intersection of given point and Box3f is not empty
    bool                intersect(const SbVec3f &pt) const;

    //! Returns TRUE if intersection of given XfBox3f and Box3f is not empty
    bool                intersect(const SbBox3f &bb) const
        { return project().intersect(bb); }

    //! Common get and set functions
    void        setBounds(float xmin, float ymin, float zmin,
                          float xmax, float ymax, float zmax)
        { SbBox3f::setBounds(xmin, ymin, zmin, xmax, ymax, zmax); }

    //! Set and get the bounds of the box.
    void        setBounds(const SbVec3f &_min, const SbVec3f &_max)
        { SbBox3f::setBounds(_min, _max); }

    void        getBounds(float &xmin, float &ymin, float &zmin,
                          float &xmax, float &ymax, float &zmax) const
        { SbBox3f::getBounds(xmin, ymin, zmin, xmax, ymax, zmax); }

    void        getBounds(SbVec3f &_min, SbVec3f &_max) const
        { SbBox3f::getBounds(_min, _max); }

    //! Returns origin (minimum point) of the box.
    void        getOrigin(float &originX,
                          float &originY,
                          float &originZ)
        { SbBox3f::getOrigin(originX, originY, originZ); }

    //! Returns size of the box.
    void        getSize(float &sizeX, float &sizeY, float &sizeZ)
        { SbBox3f::getSize(sizeX, sizeY, sizeZ); }

    //! Gives the volume of the box (0 for an empty box).
    float       getVolume() const;

    //! Sets Box3f to contain nothing
    void                makeEmpty()             { SbBox3f::makeEmpty(); }

    //! Checks if the box is empty (degenerate)
    //! note that this relies on boxes being completely degenerate if
    //! they are degenerate at all.  All member functions preserve this
    //! invariant.
    bool                isEmpty() const { return SbBox3f::isEmpty(); }

    //! Checks if the box has volume; i.e., all three dimensions have
    //! positive size
    bool                hasVolume() const { return SbBox3f::hasVolume(); }

    //! Finds the extent of the box along a particular direction.
    void                getSpan(const SbVec3f &direction,
                                float &dMin, float &dMax) const
        { project().getSpan(direction, dMin, dMax); }

    //! Transforms the box by the given matrix.
    void                transform(const SbMatrix &m);

    //! Projects an SbXfBox3f to an SbBox3f
    SbBox3f             project() const;

    //! Equality comparisons
    friend INVENTOR_API bool            operator ==(const SbXfBox3f &b1, const SbXfBox3f &b2);
    friend INVENTOR_API bool            operator !=(const SbXfBox3f &b1, const SbXfBox3f &b2);

  private:
    //! These are incorrect for SbXfBox3f, so we hide them
    const SbVec3f &     getMin() const                  { return SbBox3f::getMin(); }
    const SbVec3f &     getMax() const                  { return SbBox3f::getMax(); }

    //! The box is transformed by this xform
    SbMatrix            xform;
    SbMatrix            xformInv;
};

INVENTOR_API bool            operator ==(const SbXfBox3f &b1, const SbXfBox3f &b2);
inline INVENTOR_API bool            operator !=(const SbXfBox3f &b1, const SbXfBox3f &b2)
{ return !(b1 == b2); }

////////////////////////////////////////////////////////////////////////////////
//! 2D box class.
/*!
\class SbBox2f
\ingroup Basics
2D box which has planes parallel to the major axes and is specified by
two points (specified as floating point) on a diagonal. This class is part
of the standard Inventor datatype classes and is used as input and output
to geometry operations.

\par See Also
\par
SbBox3f, SbXfBox3f, SbBox2s, SbVec3f, SbVec2f, SbVec2s, SbMatrix
*/
////////////////////////////////////////////////////////////////////////////////

class INVENTOR_API SbBox2f {
  public:

    //! Constructs an empty box.
    SbBox2f()                                   { makeEmpty(); };

    //! Constructor given bounds 
    SbBox2f(float xmin, float ymin, float xmax, float ymax)
        { min.setValue(xmin, ymin); max.setValue(xmax, ymax); }

    //! Constructor given minimum and maximum points 
    SbBox2f(const SbVec2f &_min, const SbVec2f &_max)
        { min = _min; max = _max; }

    //! Destructor.
    ~SbBox2f()                                          { }

    //! Returns the minimum and maximum points of the box.
    const SbVec2f &     getMin() const                  { return min; }
    //! Returns the minimum and maximum points of the box.
    const SbVec2f &     getMax() const                  { return max; }

    //! Returns the center of the box.
    SbVec2f             getCenter() const;

    //! Extends Box2f (if necessary) to contain given 2D point
    void        extendBy(const SbVec2f &pt);

    //! Extends Box2f (if necessary) to contain given Box2f
    void        extendBy(const SbBox2f &r);

    //! Returns TRUE if intersection of given point and Box2f is not empty
    bool        intersect(const SbVec2f &pt) const;

    //! Returns TRUE if intersection of given Box2f and Box2f is not empty
    bool        intersect(const SbBox2f &bb) const;

    //! Sets the corners of the box.
    void        setBounds(float xmin, float ymin, float xmax, float ymax)
        { min.setValue(xmin, ymin); max.setValue(xmax, ymax); }

    void        setBounds(const SbVec2f &_min, const SbVec2f &_max)
        { min = _min; max = _max; }

    void        getBounds(float &xmin, float &ymin,
                          float &xmax, float &ymax) const
        { min.getValue(xmin, ymin); max.getValue(xmax, ymax); }

    void        getBounds(SbVec2f &_min, SbVec2f &_max) const
        { _min = min; _max = max; }

    //! Returns the closest point on the box to the given point.
    //! (Returns the point on the center of the X side if passed the center.)
    SbVec2f     getClosestPoint(const SbVec2f &point);

    //! Gets box origin.
    void        getOrigin(float &originX, float &originY) const
        { originX = min[0]; originY = min[1]; }

    //! Gets box size.
    void        getSize(float &sizeX, float &sizeY) const
        { sizeX = max[0] - min[0]; sizeY = max[1] - min[1]; }

    //! Gets box aspect ratio.
    float       getAspectRatio() const
        { return (max[0] - min[0]) / (max[1] - min[1]); }

    //! Makes an empty box.
    void        makeEmpty();

    //! Returns <tt>TRUE</tt> if the box is empty, and <tt>FALSE</tt> otherwise.
    bool        isEmpty() const         { return max[0] < min[0]; }

    //! Returns <tt>TRUE</tt> if both dimensions of the box have positive size,
    //! and <tt>FALSE</tt> otherwise.
    bool        hasArea() const
        { return (max[0] > min[0] && max[1] > min[1]); }

    //! Equality comparisons
    friend INVENTOR_API bool            operator ==(const SbBox2f &b1, const SbBox2f &b2);
    friend INVENTOR_API bool            operator !=(const SbBox2f &b1, const SbBox2f &b2);

  private:
    //! Minimum and maximum points
    SbVec2f     min, max;
};

INVENTOR_API bool            operator ==(const SbBox2f &b1, const SbBox2f &b2);
inline INVENTOR_API bool     operator !=(const SbBox2f &b1, const SbBox2f &b2)
{ return !(b1 == b2); }

////////////////////////////////////////////////////////////////////////////////
//! 2D box class.
/*!
\class SbBox2s
\ingroup Basics
2D box which has planes parallel to the major axes and is specified by two
points (specified with short integers) on a diagonal. This class is part of
the standard Inventor datatype classes and is used as input and output to
geometry operations.

\par See Also
\par
SbBox3f, SbXfBox3f, SbBox2f, SbVec3f, SbVec2f, SbVec2s, SbMatrix
*/
////////////////////////////////////////////////////////////////////////////////

class INVENTOR_API SbBox2s {
  public:

    //! Constructs an empty box.
    SbBox2s()                                   { makeEmpty(); };

    //! Constructor for a 2D integer box.  \p xmin, \p ymin, \p xmax,
    //! and \p ymax are the bounds of the box.
    SbBox2s(short xmin, short ymin, short xmax, short ymax)
        { min.setValue(xmin, ymin); max.setValue(xmax, ymax); }

    //! Constructor for a 2D integer box. \p min and \p max are the corners
    //! of the diagonal that define the box.
    SbBox2s(const SbVec2s &min, const SbVec2s &max)
        { this->min = min; this->max = max; }

    //! Destructor.
    ~SbBox2s()                                          { }

    //! Returns the minimum and maximum points of the box.
    const SbVec2s &     getMin() const                  { return min; }
    //! Returns the minimum and maximum points of the box.
    const SbVec2s &     getMax() const                  { return max; }

    //! Extends Box2s (if necessary) to contain given 2D point
    void        extendBy(const SbVec2s &pt);

    //! Extends Box2s (if necessary) to contain given Box2s
    void        extendBy(const SbBox2s &r);

    //! Returns TRUE if intersection of given point and Box2s is not empty
    bool        intersect(const SbVec2s &pt) const;

    //! Returns TRUE if intersection of given Box2s and Box2s is not empty
    bool        intersect(const SbBox2s &bb) const;

    //! Sets the corners of the box.
    void        setBounds(short xmin, short ymin, short xmax, short ymax)
        { min.setValue(xmin, ymin); max.setValue(xmax, ymax); }

    //! Sets the corners of the box.
    void        setBounds(const SbVec2s &_min, const SbVec2s &_max)
        { min = _min; max = _max; }

    void        getBounds(short &xmin, short &ymin,
                          short &xmax, short &ymax) const
        { min.getValue(xmin, ymin); max.getValue(xmax, ymax); }

    void        getBounds(SbVec2s &_min, SbVec2s &_max) const
        { _min = min; _max = max; }

    //! Returns origin (minimum point) of box.
    void        getOrigin(short &originX, short &originY) const
        { originX = min[0]; originY = min[1]; }

    //! Returns box size.
    void        getSize(short &sizeX, short &sizeY) const
        { sizeX = max[0] - min[0]; sizeY = max[1] - min[1]; }

    //! Returns aspect ratio (ratio of width to height) of box.
    float       getAspectRatio() const
        { return float(max[0] - min[0]) / float(max[1] - min[1]); }

    //! Makes an empty box.
    void        makeEmpty();

    //! Equality comparisons
    friend INVENTOR_API bool            operator ==(const SbBox2s &b1, const SbBox2s &b2);
    friend INVENTOR_API bool            operator !=(const SbBox2s &b1, const SbBox2s &b2);

  private:
    //! Minimum and maximum points
    SbVec2s     min, max;
};

INVENTOR_API bool            operator ==(const SbBox2s &b1, const SbBox2s &b2);
inline INVENTOR_API bool     operator !=(const SbBox2s &b1, const SbBox2s &b2)
{ return !(b1 == b2); }

#endif /* _SB_BOX_ */
