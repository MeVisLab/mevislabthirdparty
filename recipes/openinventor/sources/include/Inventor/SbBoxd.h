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
 |   Author(s)          : originally by Paul S. Strauss, Nick Thompson, David Mott
 |                        adapted for double values by Wolf Spindler
 |
 ______________  S I L I C O N   G R A P H I C S   I N C .  ____________
 _______________________________________________________________________
 */

#ifndef _SB_BOXD_
#define _SB_BOXD_

#include <Inventor/system/SbSystem.h>
#include <Inventor/SbBasic.h>
#include <Inventor/SbLineard.h>

////////////////////////////////////////////////////////////////////////////////
//! 3D box class.
/*!
\class SbBox3d
\ingroup Basics
3D box which has planes parallel to the major axes and is specified by two
points on a diagonal. This class is part of the standard Inventor
datatype classes and is used as input and output to geometry operations (see
SoGetBoundingBoxAction).

\par See Also
\par
SbXfBox3f, SbBox2f, SbBox2s, SbVec3f, SbVec2f, SbVec2s, SbMatrix, SoGetBoundingBoxAction, SbBox3f, SbXfBox3d, SbBox2d, SbVec3d, SbVec2d, SbMatrixd
*/
////////////////////////////////////////////////////////////////////////////////

class INVENTOR_API SbBox3d {
  public:

    //! Empty box constructor.
    SbBox3d()                                           { makeEmpty(); }

    //! Constructor given bounds 
    SbBox3d(double xmin, double ymin, double zmin,
            double xmax, double ymax, double zmax)
        { min.setValue(xmin, ymin, zmin); max.setValue(xmax, ymax, zmax); }

    //! Constructor given minimum and maximum points 
    //! \p min and \p max are the corners of the diagonal that define the box.
    SbBox3d(const SbVec3d &min, const SbVec3d &max)
        { this->min = min; this->max = max; }

    //! Destructor.
    ~SbBox3d()                                          { }

    //! Returns the minimum point of the box. The minimum point is
    //! the corner of the box with the lowest X, Y, and Z values.
    const SbVec3d &     getMin() const { return min; }
    //! Returns the maximum point of the box. The maximum
    //! point is the corner of the box with the highest X, Y, and Z values.
    const SbVec3d &     getMax() const { return max; }
    //! Returns the minimum point of the box. The minimum point is
    //! the corner of the box with the lowest X, Y, and Z values.
    SbVec3d &           getMin()       { return min; }
    //! Returns the maximum point of the box. The maximum
    //! point is the corner of the box with the highest X, Y, and Z values.
    SbVec3d &           getMax()       { return max; }

    //! Returns the center of the box.
    SbVec3d     getCenter() const;

    //! Extends Box3d (if necessary) to contain given 3D point
    void        extendBy(const SbVec3d &pt);

    //! Extends Box3d (if necessary) to contain given Box3d
    void        extendBy(const SbBox3d &bb);

    //! Returns TRUE if intersection of given point and Box3d is not empty
    bool        intersect(const SbVec3d &pt) const;

    //! Returns TRUE if intersection of given Box3d and Box3d is not empty
    bool        intersect(const SbBox3d &bb) const;

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
    bool        outside(const SbMatrixd &MVP, int &cullBits) const;

    //! Common get and set functions
    void        setBounds(double xmin, double ymin, double zmin,
                          double xmax, double ymax, double zmax)
        { min.setValue(xmin, ymin, zmin); max.setValue(xmax, ymax, zmax); }

    void        setBounds(const SbVec3d &_min, const SbVec3d &_max)
        { min = _min; max = _max; }

    void        getBounds(double &xmin, double &ymin, double &zmin,
                          double &xmax, double &ymax, double &zmax) const
        { min.getValue(xmin, ymin, zmin); max.getValue(xmax, ymax, zmax); }

    void        getBounds(SbVec3d &_min, SbVec3d &_max) const
        { _min = min; _max = max; }

    //! Returns the closest point on the box to the given point.
    //! (Returns the point on the center of the Z face if passed the center.)
    SbVec3d     getClosestPoint(const SbVec3d &point);

    //! Gets box origin which is the same as the minimum corner of the box.
    void        getOrigin(double &originX,
                          double &originY,
                          double &originZ) const
        { originX = min[0]; originY = min[1]; originZ = min[2]; }

    //! Gets box size.
    void        getSize(double &sizeX, double &sizeY, double &sizeZ) const
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
    void        getSpan(const SbVec3d &direction,
                        double &dMin, double &dMax) const;

    //! Transforms box by matrix, enlarging box to contain result.
    void        transform(const SbMatrixd &m);

    //! Returns the volume of the box.
    double       getVolume() const;

    //! Equality comparisons
    friend INVENTOR_API bool            operator ==(const SbBox3d &b1, const SbBox3d &b2);
    friend INVENTOR_API bool            operator !=(const SbBox3d &b1, const SbBox3d &b2);

  private:
    //! Minimum and maximum points
    SbVec3d     min, max;
};

INVENTOR_API bool            operator ==(const SbBox3d &b1, const SbBox3d &b2);
inline INVENTOR_API bool     operator !=(const SbBox3d &b1, const SbBox3d &b2)
{ return !(b1 == b2); }

////////////////////////////////////////////////////////////////////////////////
//! 3D box with an associated transformation matrix.
/*!
\class SbXfBox3d
\ingroup Basics
A 3D box with an arbitrary transformation applied.  This class is useful when
a box will be transformed frequently; if an SbBox3d is used for this
purpose it will expand each time it is transformed in order to keep itself
axis-aligned.  Transformations can be accumulated on an SbXfBox3d
without expanding the box, and after all transformations have been done, the
box can be expanded to an axis-aligned box if necessary.

\par See Also
\par
SbBox3f, SbBox2f, SbBox2s, SbVec3f, SbVec2f, SbVec2s, SbMatrix, SoGetBoundingBoxAction, SbBox3d, SbBox2d, SbVec3d, SbVec2d, SbMatrixd
*/
////////////////////////////////////////////////////////////////////////////////

class INVENTOR_API SbXfBox3d : public SbBox3d {
  public:

    //! Constructors and destructor.
    SbXfBox3d();

    //! Constructors and destructor.
    SbXfBox3d(const SbVec3d &_min, const SbVec3d &_max);

    //! Constructors and destructor.
    SbXfBox3d(const SbBox3d &box);

    //! Constructors and destructor.
    ~SbXfBox3d()                                                { }

    //! Sets the transformation on the box.
    void                setTransform(const SbMatrixd &m);

    //! Gets the transformation on the box, and its inverse.
    const SbMatrixd &    getTransform() const        { return xform; }
    //! Gets the transformation on the box, and its inverse.
    const SbMatrixd &    getInverse() const          { return xformInv; }

    //! Returns the center of the box.
    SbVec3d             getCenter() const;

    //! Extends the box (if necessary) to contain the given 3D point.  If the
    //! box has had a non-identity transformation applied using the
    //! setTransform() method, the point is assumed to be in the transformed
    //! space.  For example, the following code sequence:
    //! \code
    //! SbXfBox3d bbox; bbox.extendBy(SbVec3d(0,0,0));
    //! SbMatrixd trans; trans.setTranslate(SbVec3d(1,1,1));
    //! bbox.setTransform(trans);
    //! bbox.extendBy(SbVec3d(0,0,0));
    //! \endcode
    //! will result in a bounding box extending from (-1,-1,-1) to
    //! (0,0,0) in bbox'es local (untransformed) space.
    void                extendBy(const SbVec3d &pt);

    //! Extends the box (if necessary) to contain the given SbBox3d.  If
    //! the box has had a non-identity transformation applied using the
    //! setTransform() method, the given SbBox3d is assumed to be in the
    //! transformed space.
    void                extendBy(const SbBox3d &bb)
        { extendBy(SbXfBox3d(bb)); }

    //! Extends the box (if necessary) to contain the given SbXfBox3d.
    void                extendBy(const SbXfBox3d &bb);

    //! Returns TRUE if intersection of given point and Box3d is not empty
    bool                intersect(const SbVec3d &pt) const;

    //! Returns TRUE if intersection of given XfBox3d and Box3d is not empty
    bool                intersect(const SbBox3d &bb) const
        { return project().intersect(bb); }

    //! Common get and set functions
    void        setBounds(double xmin, double ymin, double zmin,
                          double xmax, double ymax, double zmax)
        { SbBox3d::setBounds(xmin, ymin, zmin, xmax, ymax, zmax); }

    //! Set and get the bounds of the box.
    void        setBounds(const SbVec3d &_min, const SbVec3d &_max)
        { SbBox3d::setBounds(_min, _max); }

    void        getBounds(double &xmin, double &ymin, double &zmin,
                          double &xmax, double &ymax, double &zmax) const
        { SbBox3d::getBounds(xmin, ymin, zmin, xmax, ymax, zmax); }

    void        getBounds(SbVec3d &_min, SbVec3d &_max) const
        { SbBox3d::getBounds(_min, _max); }

    //! Returns origin (minimum point) of the box.
    void        getOrigin(double &originX,
                          double &originY,
                          double &originZ)
        { SbBox3d::getOrigin(originX, originY, originZ); }

    //! Returns size of the box.
    void        getSize(double &sizeX, double &sizeY, double &sizeZ)
        { SbBox3d::getSize(sizeX, sizeY, sizeZ); }

    //! Gives the volume of the box (0 for an empty box).
    double       getVolume() const;

    //! Sets Box3d to contain nothing
    void                makeEmpty()             { SbBox3d::makeEmpty(); }

    //! Checks if the box is empty (degenerate)
    //! note that this relies on boxes being completely degenerate if
    //! they are degenerate at all.  All member functions preserve this
    //! invariant.
    bool                isEmpty() const { return SbBox3d::isEmpty(); }

    //! Checks if the box has volume; i.e., all three dimensions have
    //! positive size
    bool                hasVolume() const { return SbBox3d::hasVolume(); }

    //! Finds the extent of the box along a particular direction.
    void                getSpan(const SbVec3d &direction,
                                double &dMin, double &dMax) const
        { project().getSpan(direction, dMin, dMax); }

    //! Transforms the box by the given matrix.
    void                transform(const SbMatrixd &m);

    //! Projects an SbXfBox3d to an SbBox3d
    SbBox3d             project() const;

    //! Equality comparisons
    friend INVENTOR_API bool            operator ==(const SbXfBox3d &b1, const SbXfBox3d &b2);
    friend INVENTOR_API bool            operator !=(const SbXfBox3d &b1, const SbXfBox3d &b2);

  private:
    //! These are incorrect for SbXfBox3d, so we hide them
    const SbVec3d &     getMin() const                  { return SbBox3d::getMin(); }
    const SbVec3d &     getMax() const                  { return SbBox3d::getMax(); }

    //! The box is transformed by this xform
    SbMatrixd           xform;
    SbMatrixd           xformInv;
};

INVENTOR_API bool            operator ==(const SbXfBox3d &b1, const SbXfBox3d &b2);
inline INVENTOR_API bool     operator !=(const SbXfBox3d &b1, const SbXfBox3d &b2)
{ return !(b1 == b2); }

////////////////////////////////////////////////////////////////////////////////
//! 2D box class.
/*!
\class SbBox2d
\ingroup Basics
2D box which has planes parallel to the major axes and is specified by
two points (specified as floating point doubles) on a diagonal. This class is part
of the standard Inventor datatype classes and is used as input and output
to geometry operations.

\par See Also
\par
SbBox3f, SbXfBox3f, SbBox2s, SbVec3f, SbVec2f, SbVec2s, SbMatrix, SbBox2f, SbBox3d, SbXfBox3d, SbVec3d, SbVec2d, SbMatrixd
*/
////////////////////////////////////////////////////////////////////////////////

class INVENTOR_API SbBox2d {
  public:

    //! Constructs an empty box.
    SbBox2d()                                   { makeEmpty(); };

    //! Constructor given bounds 
    SbBox2d(double xmin, double ymin, double xmax, double ymax)
        { min.setValue(xmin, ymin); max.setValue(xmax, ymax); }

    //! Constructor given minimum and maximum points 
    SbBox2d(const SbVec2d &_min, const SbVec2d &_max)
        { min = _min; max = _max; }

    //! Destructor.
    ~SbBox2d()                                          { }

    //! Returns the minimum and maximum points of the box.
    const SbVec2d &     getMin() const                  { return min; }
    //! Returns the minimum and maximum points of the box.
    const SbVec2d &     getMax() const                  { return max; }

    //! Returns the center of the box.
    SbVec2d             getCenter() const;

    //! Extends Box2d (if necessary) to contain given 2D point
    void        extendBy(const SbVec2d &pt);

    //! Extends Box2d (if necessary) to contain given Box2d
    void        extendBy(const SbBox2d &r);

    //! Returns TRUE if intersection of given point and Box2d is not empty
    bool        intersect(const SbVec2d &pt) const;

    //! Returns TRUE if intersection of given Box2d and Box2d is not empty
    bool        intersect(const SbBox2d &bb) const;

    //! Sets the corners of the box.
    void        setBounds(double xmin, double ymin, double xmax, double ymax)
        { min.setValue(xmin, ymin); max.setValue(xmax, ymax); }

    void        setBounds(const SbVec2d &_min, const SbVec2d &_max)
        { min = _min; max = _max; }

    void        getBounds(double &xmin, double &ymin,
                          double &xmax, double &ymax) const
        { min.getValue(xmin, ymin); max.getValue(xmax, ymax); }

    void        getBounds(SbVec2d &_min, SbVec2d &_max) const
        { _min = min; _max = max; }

    //! Returns the closest point on the box to the given point.
    //! (Returns the point on the center of the X side if passed the center.)
    SbVec2d     getClosestPoint(const SbVec2d &point);

    //! Gets box origin.
    void        getOrigin(double &originX, double &originY) const
        { originX = min[0]; originY = min[1]; }

    //! Gets box size.
    void        getSize(double &sizeX, double &sizeY) const
        { sizeX = max[0] - min[0]; sizeY = max[1] - min[1]; }

    //! Gets box aspect ratio.
    double       getAspectRatio() const
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
    friend INVENTOR_API bool            operator ==(const SbBox2d &b1, const SbBox2d &b2);
    friend INVENTOR_API bool            operator !=(const SbBox2d &b1, const SbBox2d &b2);

  private:
    //! Minimum and maximum points
    SbVec2d     min, max;
};

INVENTOR_API bool            operator ==(const SbBox2d &b1, const SbBox2d &b2);
inline INVENTOR_API bool     operator !=(const SbBox2d &b1, const SbBox2d &b2)
{ return !(b1 == b2); }


#endif /* _SB_BOXD_ */
