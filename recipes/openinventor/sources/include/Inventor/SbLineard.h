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
 |   $Revision: 1.3 $
 |
 |   Description:
 |      This file contains definitions of various linear algebra classes,
 |      such as vectors, coordinates, etc..
 |
 |   Classes:
 |      SbVec3d
 |      SbVec2d
 |      SbVec4d
 |      SbRotationd
 |      SbMatrixd
 |
 |      SbLined
 |      SbPlaned
 |      SbSphered
 |
 |   Author(s)          : originally by Paul S. Strauss, Nick Thompson, 
 |                        David Mott, Alain Dumesny
 |                        adapted for double types by Wolf Spindler
 |
 ______________  S I L I C O N   G R A P H I C S   I N C .  ____________
 _______________________________________________________________________
 */

#ifndef _SB_LINEARD_
#define _SB_LINEARD_

#include <Inventor/system/SbSystem.h>
#include <math.h>
#include <Inventor/SbBasic.h>

//! -----------------------------------
//!
//! Types/classes defined in this file:
//! 
//! -----------------------------------

typedef double SbMatd[4][4];

class SbVec3d;
class SbVec2d;
class SbVec4d;
class SbRotationd;
class SbMatrixd;

class SbLined;
class SbPlaned;
class SbCylinderd;
class SbSphered;

//! Forward definition so we can use this in other Sb classes
class SbBox3d;




////////////////////////////////////////////////////////////////////////////////
//! 3D vector class with double values.
/*!
\class SbVec3d
\ingroup Basics
3D vector class used to store 3D vectors and points. This class is used
throughout Inventor for arguments and return values.
{}

\par See Also
\par
SbVec2f, SbVec3f, SbVec4f, SbVec2d, SbVec4d, SbVec2s, SbRotation, SbRotationd
*/
////////////////////////////////////////////////////////////////////////////////

class INVENTOR_API SbVec3d {
  public:

    //! Default constructor.
    SbVec3d() { vec[0] = 0.; vec[1] = 0.; vec[2] = 0.; }

    //! Constructor given vector components.
    SbVec3d(const double v[3])
         { vec[0] = v[0]; vec[1] = v[1]; vec[2] = v[2]; }

    //! Constructor given vector components.
    SbVec3d(double x, double y, double z)
         { vec[0] = x; vec[1] = y; vec[2] = z; }

    //! Constructor given 3 planes.
    SbVec3d(SbPlaned &p0, SbPlaned &p1, SbPlaned &p2);

    //! Returns right-handed cross product of vector and another vector.
    SbVec3d     cross(const SbVec3d &v) const;

    //! Returns dot (inner) product of vector and another vector.
    double      dot(const SbVec3d &v) const;

    //! Returns vector components.
    const double *getValue() const                       { return vec; }

    //! Returns vector components.
    void        getValue(double &x, double &y, double &z) const;

    //! Returns geometric length of vector.
    double      length() const;

    //! Changes vector to be unit length, returning the length before normalization.
    double      normalize();

    //! Negates each component of vector in place.
    void        negate();

    //! Sets the vector components.
    SbVec3d &   setValue(const double v[3])
         { vec[0] = v[0]; vec[1] = v[1]; vec[2] = v[2]; return *this; }

    //! Sets the vector components.
    SbVec3d &   setValue(double x, double y, double z)
         { vec[0] = x; vec[1] = y; vec[2] = z; return *this; }

    //! Sets value of vector to be convex combination of 3 other
    //! vectors, using barycentic coordinates
    SbVec3d &   setValue(const SbVec3d &barycentic,
                const SbVec3d &v0, const SbVec3d &v1, const SbVec3d &v2);

    //! Accesses indexed component of vector
    double &       operator [](int i)            { return (vec[i]); }
    const double & operator [](int i) const      { return (vec[i]); }

    //! Component-wise scalar multiplication and division operators.
    SbVec3d &   operator *=(double d);

    //! Component-wise scalar multiplication and division operators.
    SbVec3d &   operator /=(double d)
        { return *this *= (1.0 / d); }

    //! Component-wise vector addition and subtraction operators.
    SbVec3d &   operator +=(SbVec3d v);
    //! Component-wise vector addition and subtraction operators.
    SbVec3d &   operator -=(SbVec3d v);

    //! Nondestructive unary negation - returns a new vector
    SbVec3d     operator -() const;

    //! Component-wise binary scalar multiplication and division operators
    friend INVENTOR_API SbVec3d operator *(const SbVec3d &v, double d);
    friend INVENTOR_API SbVec3d operator *(double d, const SbVec3d &v);
    friend INVENTOR_API SbVec3d operator /(const SbVec3d &v, double d);

    //! Component-wise binary vector addition and subtraction operators
    friend INVENTOR_API SbVec3d operator +(const SbVec3d &v1, const SbVec3d &v2);

    friend INVENTOR_API SbVec3d operator -(const SbVec3d &v1, const SbVec3d &v2);

    //! Equality comparison operator
    friend INVENTOR_API bool       operator ==(const SbVec3d &v1, const SbVec3d &v2);
    friend INVENTOR_API bool       operator !=(const SbVec3d &v1, const SbVec3d &v2);

    //! Equality comparison within given tolerance em the square of the
    //! length of the maximum distance between the two vectors.
    bool                equals(const SbVec3d v, double tolerance) const;

    //! Returns principal axis that is closest (based on maximum dot
    //! product) to this vector.
    SbVec3d             getClosestAxis() const;

  protected:
    double       vec[3];         //!< Storage for vector components
};

INVENTOR_API SbVec3d operator *(const SbVec3d &v, double d);
inline INVENTOR_API SbVec3d operator *(double d, const SbVec3d &v)
{ return v * d; }
inline INVENTOR_API SbVec3d operator /(const SbVec3d &v, double d)
{ return v * (1.0 / d); }

INVENTOR_API SbVec3d operator +(const SbVec3d &v1, const SbVec3d &v2);
INVENTOR_API SbVec3d operator -(const SbVec3d &v1, const SbVec3d &v2);

INVENTOR_API bool       operator ==(const SbVec3d &v1, const SbVec3d &v2);
inline INVENTOR_API bool       operator !=(const SbVec3d &v1, const SbVec3d &v2)
{ return !(v1 == v2); }



////////////////////////////////////////////////////////////////////////////////
//! 2D vector class with double members.
/*!
\class SbVec2d
\ingroup Basics
2D vector class used to store 2D vectors and points. This class is used
throughout Inventor for arguments and return values.
{}

\par See Also
\par
SbVec3f, SbVec3f, SbVec4f, SbVec3d, SbVec4d, SbVec2s, SbRotation, SbRotationd
*/
////////////////////////////////////////////////////////////////////////////////

class INVENTOR_API SbVec2d {
  public:

    //! Default constructor.
    SbVec2d() { vec[0] = 0.; vec[1] = 0.; }

    //! Constructor given vector components.
    SbVec2d(const double v[2])                          { setValue(v); }

    //! Constructor given vector components.
    SbVec2d(double x, double y)                         { setValue(x, y); }

    //! Returns dot (inner) product of vector and another vector.
    double       dot(const SbVec2d &v) const;

    //! Returns vector components.
    const double *getValue() const                      { return vec; }

    //! Returns vector components.
    void        getValue(double &x, double &y) const;

    //! Returns geometric length of vector.
    double      length() const;

    //! Negates each component of vector in place.
    void        negate();

    //! Changes vector to be unit length.
    double      normalize();

    //! Sets the vector components.
    SbVec2d &   setValue(const double v[2]);

    //! Sets the vector components.
    SbVec2d &   setValue(double x, double y);

    //! Accesses indexed component of vector
    double &       operator [](int i)            { return (vec[i]); }
    const double & operator [](int i) const      { return (vec[i]); }

    //! Component-wise scalar multiplication and division operators.
    SbVec2d &   operator *=(double d);

    //! Component-wise scalar multiplication and division operators.
    SbVec2d &   operator /=(double d)
        { return *this *= (1.0 / d); }

    //! Component-wise vector addition and subtraction operators.
    SbVec2d &   operator +=(const SbVec2d &u);
    //! Component-wise vector addition and subtraction operators.
    SbVec2d &   operator -=(const SbVec2d &u);

    //! Nondestructive unary negation - returns a new vector
    SbVec2d     operator -() const;

    //! Component-wise binary scalar multiplication and division operators
    friend INVENTOR_API SbVec2d operator *(const SbVec2d &v, double d);
    friend INVENTOR_API SbVec2d operator *(double d, const SbVec2d &v);
    friend INVENTOR_API SbVec2d operator /(const SbVec2d &v, double d);

    //! Component-wise binary vector addition and subtraction operators
    friend INVENTOR_API SbVec2d operator +(const SbVec2d &v1, const SbVec2d &v2);

    friend INVENTOR_API SbVec2d operator -(const SbVec2d &v1, const SbVec2d &v2);

    //! Equality comparison operator
    friend INVENTOR_API bool               operator ==(const SbVec2d &v1, const SbVec2d &v2);
    friend INVENTOR_API bool               operator !=(const SbVec2d &v1, const SbVec2d &v2);

    //! Equality comparison within given tolerance em the square of the
    //! length of the maximum distance between the two vectors.
    bool                equals(const SbVec2d v, double tolerance) const;

  protected:
    double       vec[2];         //!< Storage for vector components
};

INVENTOR_API SbVec2d operator *(const SbVec2d &v, double d);
inline INVENTOR_API SbVec2d operator *(double d, const SbVec2d &v)
{ return v * d; }
inline INVENTOR_API SbVec2d operator /(const SbVec2d &v, double d)
{ return v * (1.0 / d); }

INVENTOR_API SbVec2d operator +(const SbVec2d &v1, const SbVec2d &v2);
INVENTOR_API SbVec2d operator -(const SbVec2d &v1, const SbVec2d &v2);

INVENTOR_API bool               operator ==(const SbVec2d &v1, const SbVec2d &v2);
inline INVENTOR_API bool               operator !=(const SbVec2d &v1, const SbVec2d &v2)
{ return !(v1 == v2); }



////////////////////////////////////////////////////////////////////////////////
//! 4D vector class with double values.
/*!
\class SbVec4d
\ingroup Basics
4D vector class used to store homogeneous coordinates. This class is used
in Inventor for arguments and return values.
{}

\par See Also
\par
SbVec2f, SbVec3f, SbVec2d, SbVec3d, SbVec4d, SbVec2s, SbRotation
*/
////////////////////////////////////////////////////////////////////////////////

class INVENTOR_API SbVec4d {
  public:

    //! Default constructor.
    SbVec4d() { vec[0] = 0.; vec[1] = 0.; vec[2] = 0.; vec[3] = 0.; }

    //! Constructor given vector components.
    SbVec4d(const double v[4])                         { setValue(v); }

    //! Constructor given vector components.
    SbVec4d(double x, double y, double z, double w)    { setValue(x, y, z, w); }

    //! Returns dot (inner) product of vector and another vector.
    double      dot(const SbVec4d &v) const;

    //! Returns the real portion of the vector by dividing by the fourth value.
    void        getReal(SbVec3d &v) const;

    //! Returns the real portion of the vector by dividing by the fourth value.
    SbVec3d     getReal() const { SbVec3d tmp; getReal(tmp); return tmp; }

    //! Returns vector components.
    const double *getValue() const                     { return vec; }

    //! Returns vector components.
    void        getValue(double &x, double &y, double &z, double &w) const;

    //! Returns geometric length of vector.
    double      length() const;

    //! Negates each component of vector in place.
    void        negate();

    //! Changes vector to be unit length.
    double      normalize();

    //! Sets the vector components.
    SbVec4d &   setValue(const double v[4]);

    //! Sets the vector components.
    SbVec4d &   setValue(double x, double y, double z, double w);

    //! Accesses indexed component of vector
    double &       operator [](int i)            { return (vec[i]); }
    const double & operator [](int i) const      { return (vec[i]); }

    //! Component-wise scalar multiplication and division operators.
    SbVec4d &   operator *=(double d);

    //! Component-wise scalar multiplication and division operators.
    SbVec4d &   operator /=(double d)
        { return *this *= (1.0 / d); }

    //! Component-wise vector addition and subtraction operators.
    SbVec4d &   operator +=(const SbVec4d &u);
    //! Component-wise vector addition and subtraction operators.
    SbVec4d &   operator -=(const SbVec4d &u);

    //! Nondestructive unary negation - returns a new vector
    SbVec4d     operator -() const;

    //! Component-wise binary scalar multiplication and division operators
    friend INVENTOR_API SbVec4d operator *(const SbVec4d &v, double d);
    friend INVENTOR_API SbVec4d operator *(double d, const SbVec4d &v);
    friend INVENTOR_API SbVec4d operator /(const SbVec4d &v, double d);

    //! Component-wise binary vector addition and subtraction operators
    friend INVENTOR_API SbVec4d operator +(const SbVec4d &v1, const SbVec4d &v2);

    friend INVENTOR_API SbVec4d operator -(const SbVec4d &v1, const SbVec4d &v2);

    //! Equality comparison operator
    friend INVENTOR_API bool               operator ==(const SbVec4d &v1, const SbVec4d &v2);
    friend INVENTOR_API bool               operator !=(const SbVec4d &v1, const SbVec4d &v2);

    //! Equality comparison within given tolerance em the square of the
    //! length of the maximum distance between the two vectors.
    bool                equals(const SbVec4d v, double tolerance) const;

  protected:
    double       vec[4];         //!< Storage for vector components
};

INVENTOR_API SbVec4d operator *(const SbVec4d &v, double d);
inline INVENTOR_API SbVec4d operator *(double d, const SbVec4d &v)
{ return v * d; }
inline INVENTOR_API SbVec4d operator /(const SbVec4d &v, double d)
{ return v * (1.0 / d); }

INVENTOR_API SbVec4d operator +(const SbVec4d &v1, const SbVec4d &v2);
INVENTOR_API SbVec4d operator -(const SbVec4d &v1, const SbVec4d &v2);

INVENTOR_API bool               operator ==(const SbVec4d &v1, const SbVec4d &v2);
inline INVENTOR_API bool               operator !=(const SbVec4d &v1, const SbVec4d &v2)
{ return !(v1 == v2); }



////////////////////////////////////////////////////////////////////////////////
//! Class for representing a rotation with double values.
/*!
\class SbRotationd
\ingroup Basics
Object that stores a rotation. There are several ways to specify a
rotation: quaternion (4 doubles), 4x4 rotation matrix, or axis and angle.
All angles are in radians and all rotations are right-handed.
{}
\par
NOTES

Rotations are stored internally as quaternions.

\par See Also
\par
SbVec3f, SbMatrix, SbVec3d, SbMatrix, SbMatrixd, SbRotation
*/
////////////////////////////////////////////////////////////////////////////////

class INVENTOR_API SbRotationd {
  public:

    //! Default constructor, initialized to identity.
    SbRotationd()
    {
      quat[0] = 0.; quat[1] = 0.; quat[2] = 0.; quat[3] = 1.;
    }

    //! \see SbRotationd(const SbVec3d &rotateFrom, const SbVec3d &rotateTo)
    SbRotationd(const double v[4])
        { setValue(v); }

    //! \see SbRotationd(const SbVec3d &rotateFrom, const SbVec3d &rotateTo)
    SbRotationd(double q0, double q1, double q2, double q3)
        { setValue(q0, q1, q2, q3); }

    //! \see SbRotationd(const SbVec3d &rotateFrom, const SbVec3d &rotateTo)
    SbRotationd(const SbMatrixd &m)
        { setValue(m); }

    //! \see SbRotationd(const SbVec3d &rotateFrom, const SbVec3d &rotateTo)
    SbRotationd(const SbVec3d &axis, double radians)
        { setValue(axis, radians); }

    //! Constructors for rotation. The axis/radians constructor creates a rotation of
    //! angle radians about the given axis.  The constructors that take four doubles 
    //! create a quaternion from those doubles (careful, this differs from the four 
    //! numbers in an axis/radian definition). 
    //! Matrix constructor requires a valid rotation matrix.
    //! The rotateFrom/To constructor defines rotation that rotates from one vector 
    //! into another.
    //! The \p rotateFrom and \p rotateTo vectors are normalized by the constructor
    //! before calculating the rotation.
    SbRotationd(const SbVec3d &rotateFrom, const SbVec3d &rotateTo)
        { setValue(rotateFrom, rotateTo); }

    //! Returns pointer to array of 4 components defining quaternion
    const double *      getValue() const
        { return (quat); }

    //! Returns 4 individual components of rotation quaternion 
    void                getValue(double &q0, double &q1,
                                 double &q2, double &q3) const;

    //! Returns corresponding 3D rotation axis vector and angle in radians
    void                getValue(SbVec3d &axis, double &radians) const;

    //! Returns corresponding 4x4 rotation matrix
    void                getValue(SbMatrixd &matrix) const;

    //! Returns corresponding 4x4 rotation matrix
    SbMatrixd getMatrix() const;
    
    //! Returns corresponding 3D rotation axis vector.
    SbVec3d getAxis() const { SbVec3d axis; double radians; getValue(axis, radians); return axis; }
    //! Returns corresponding angle in radians.
    double   getAngle() const { SbVec3d axis; double radians; getValue(axis, radians); return radians; }

    //! Changes a rotation to be its inverse.
    SbRotationd &       invert();

    //! Returns the inverse of a rotation.
    SbRotationd         inverse() const
        { SbRotationd q = *this; return q.invert(); }

    //! Sets value of rotation from array of 4 components of a quaternion.
    SbRotationd &       setValue(const double q[4]);

    //! Sets value of rotation from 4 individual components of a quaternion.
    SbRotationd &       setValue(double q0, double q1, double q2, double q3);

    //! Sets value of rotation from a rotation matrix.
    SbRotationd &       setValue(const SbMatrixd &m);

    //! Sets value of vector from 3D rotation axis vector and angle in radians.
    SbRotationd &       setValue(const SbVec3d &axis, double radians);

    //! Sets rotation to rotate one direction vector to another
    SbRotationd &       setValue(const SbVec3d &rotateFrom,
                                 const SbVec3d &rotateTo);

    //! Multiplies by another rotation; results in product of rotations.
    SbRotationd &        operator *=(const SbRotationd &q);

    //! Equality comparison operator
    friend INVENTOR_API bool       operator ==(const SbRotationd &q1, const SbRotationd &q2);
    friend INVENTOR_API bool       operator !=(const SbRotationd &q1, const SbRotationd &q2);

    //! Equality comparison within given tolerance em the square of the
    //! length of the maximum distance between the two quaternion vectors.
    bool                equals(const SbRotationd &r, double tolerance) const;

    //! Multiplication of two rotations; results in product of rotations
    friend INVENTOR_API SbRotationd     operator *(const SbRotationd &q1, const SbRotationd &q2);

    //! Multiplies the given vector by the matrix of this rotation.
    void        multVec(const SbVec3d &src, SbVec3d &dst) const;

    //! Multiplies the given vector by the matrix of this rotation.
    SbVec3d     transformPoint(const SbVec3d &src) const { SbVec3d dst; multVec(src, dst); return dst; }

    //! Keep the axis the same. Multiply the angle of rotation by 
    //! the amount \p scaleFactor.
    void scaleAngle( double scaleFactor );

    //! Spherical linear interpolation: as \p t goes from 0 to 1, returned
    //! value goes from \p rot0 to \p rot1.
    static SbRotationd  slerp(const SbRotationd &rot0,
                              const SbRotationd &rot1, double t);

    //! Returns a null rotation.
    static SbRotationd  identity()
        { return SbRotationd(0.0, 0.0, 0.0, 1.0); }

  private:
    double      quat[4];        //!< Storage for quaternion components

    //! Returns the norm (square of the 4D length) of a rotation's quaterion
    double      norm() const;

    //! Normalizes a rotation quaternion to unit 4D length
    void        normalize();
};

INVENTOR_API bool       operator ==(const SbRotationd &q1, const SbRotationd &q2);
inline INVENTOR_API bool       operator !=(const SbRotationd &q1, const SbRotationd &q2)
{ return !(q1 == q2); }

INVENTOR_API SbRotationd     operator *(const SbRotationd &q1, const SbRotationd &q2);




////////////////////////////////////////////////////////////////////////////////
//! 4x4 matrix class with double values.
/*!
\class SbMatrixd
\ingroup Basics
4x4 matrix class/datatype used by many Inventor node and action classes.
The matrices are stored in row-major order.
{}

\par See Also
\par
SbVec3f, SbRotation, SbMatrix, SbVec3d, SbRotationd
*/
////////////////////////////////////////////////////////////////////////////////

class INVENTOR_API SbMatrixd {
  public:

    //! Default constructor, initialized to identity.
    SbMatrixd() {
      makeIdentity();
    }

    //! Constructor given all 16 elements in row-major order
    SbMatrixd(double a11, double a12, double a13, double a14,
              double a21, double a22, double a23, double a24, 
              double a31, double a32, double a33, double a34, 
              double a41, double a42, double a43, double a44);

    //! Constructors.
    SbMatrixd(const SbMatd &m);

    //! Sets value from 4x4 array of elements.
    void        setValue(const SbMatd &m);

    //! Sets value from a double array of 16 elements.
    void        setValue(const double* data);

    public:

    //! Sets matrix to be identity.
    void        makeIdentity();

    //! Returns an identity matrix.
    static SbMatrixd     identity();

    //! Sets matrix to rotate by given rotation.
    void        setRotate(const SbRotationd &q);

    //! Sets matrix to scale by given uniform factor.
    void        setScale(double s);

    //! Sets matrix to scale by given vector.
    void        setScale(const SbVec3d &s);

    //! Sets matrix to translate by given vector.
    void        setTranslate(const SbVec3d &t);

    //! Composes the matrix based on a translation, rotation, scale,
    //! orientation for scale, and center.  The "center" is the
    //! center point for scaling and rotation.  The "scaleOrientation"
    //! chooses the primary axes for the scale.
    void        setTransform(
                        const SbVec3d &translation,
                        const SbRotationd &rotation,
                        const SbVec3d &scaleFactor,
                        const SbRotationd &scaleOrientation,
                        const SbVec3d &center);
    //! Overloaded methods as a kludge because the compiler won't let
    //! us have SbVec3d(0,0,0) as a default value:
    void        setTransform(const SbVec3d &t, const SbRotationd &r,
                             const SbVec3d &s)
                { setTransform(t, r, s,
                               SbRotationd(0,0,0,1), SbVec3d(0,0,0)); }
    void        setTransform(const SbVec3d &t, const SbRotationd &r,
                             const SbVec3d &s, const SbRotationd &so)
                { setTransform(t, r, s, so, SbVec3d(0,0,0)); }

    //! Decomposes the matrix into a translation, rotation, scale,
    //! and scale orientation.  Any projection information is discarded.
    //! The decomposition depends upon choice of center point for
    //! rotation and scaling, which is optional as the last parameter.
    //! Note that if the center is 0, decompose() is the same as
    //! factor() where "t" is translation, "u" is rotation, "s" is scaleFactor,
    //! and "r" is ScaleOrientattion.
    void        getTransform(SbVec3d &translation,
                             SbRotationd &rotation,
                             SbVec3d &scaleFactor,
                             SbRotationd &scaleOrientation,
                             const SbVec3d &center) const;
    void        getTransform(SbVec3d &t, SbRotationd &r,
                             SbVec3d &s, SbRotationd &so) const
                { getTransform(t, r, s, so, SbVec3d(0,0,0)); }


    //! The following methods return matrix values and other info:

    //! Returns 4x4 array of elements
    void        getValue(SbMatd &m) const;
    const SbMatd &       getValue() const { return matrix; }

    //! Returns determinant of 3x3 submatrix composed of given row and
    //! column indices (0-3 for each).
    double       det3(int r1, int r2, int r3, int c1, int c2, int c3) const;

    //! Returns determinant of upper-left 3x3 submatrix
    double       det3() const { return det3(0, 1, 2, 0, 1, 2); }

    //! Returns determinant of entire matrix.
    double       det4() const;

    //! Factors a matrix m into 5 pieces: m = r s r^ u t, where r^
    //! means transpose of r, and r and u are rotations, s is a scale,
    //! and t is a translation. Any projection information is returned
    //! in \p proj.
    //! NOTE: the projection matrix is always set to identity.
    bool        factor(SbMatrixd &r, SbVec3d &s, SbMatrixd &u,
                       SbVec3d &t, SbMatrixd &proj) const;

    //! Returns inverse of matrix. Results are undefined for
    //! singular matrices.  Uses LU decomposition.
    SbMatrixd    inverse() const;

    //! Perform in-place LU decomposition of matrix.  \p index is index of rows
    //! in matrix. \p d is the parity of row swaps.  Returns FALSE if singular.
    bool        LUDecomposition(int index[4], double &d);

    //! Perform back-substitution on LU-decomposed matrix. Index is
    //! permutation of rows from original matrix.
    void        LUBackSubstitution(int index[4], double b[4]) const;

    //! Returns transpose of matrix.
    SbMatrixd    transpose() const;

    //! Multiplies matrix by given matrix on right or left.
    SbMatrixd &  multRight(const SbMatrixd &m);   // this = this * m
    //! Multiplies matrix by given matrix on right or left.
    SbMatrixd &  multLeft(const SbMatrixd &m);    // this = m * this

    //! Multiplies given row vector by matrix, giving vector result. Use this method to transform points from object coordinates to world coordinates. (MEVIS)
    SbVec3d     transformPoint(const SbVec3d &src) const { SbVec3d dst; multVecMatrix(src, dst); return dst; }
    //! Multiplies given row vector by matrix, giving vector result. Takes homogenous coordinate and returns homogenous coordinate. (MEVIS)
    SbVec4d     transformPoint(const SbVec4d &src) const { SbVec4d dst; multVecMatrix(src, dst); return dst; }

    //! Multiplies given row vector by matrix, giving vector result.
    //! \p src is assumed to be a direction vector, so translation part of
    //! matrix is ignored. Note: if you wish to transform surface points and normals
    //! by a matrix, call
    //! multVecMatrix()
    //! for the points and call
    //! multDirMatrix()
    //! on the inverse transpose of the matrix for the normals. (MEVIS)
    SbVec3d     transformDirection(const SbVec3d &src) const { SbVec3d dst; multDirMatrix(src, dst); return dst; }

    //! Multiplies the given line's origin by the matrix, and the
    //! line's direction by the rotation portion of the matrix. (MEVIS)
    SbLined     transformLine(const SbLined &src) const;
    
    //! Multiplies matrix by given column vector, giving vector result. NOTE: Typically you should use multVecMatrix() instead,
    //! since object/world transforms normally use row vectors.
    void        multMatrixVec(const SbVec3d &src, SbVec3d &dst) const;

    //! Multiplies given row vector by matrix, giving vector result. Use this method to transform points from object coordinates to world coordinates. 
    void        multVecMatrix(const SbVec3d &src, SbVec3d &dst) const;
    //! Multiplies given row vector by matrix, giving vector result. Takes homogenous coordinate and returns homogenous coordinate.
    void        multVecMatrix(const SbVec4d &src, SbVec4d &dst) const;
    //! Multiplies given row vector by matrix, giving vector result. Takes SbVec4(src,1.) coordinate and returns homogenous coordinate.
    void        multVecMatrix(const SbVec3d &src, SbVec4d &dst) const;

    //! Multiplies given row vector by matrix, giving vector result.
    //! \p src is assumed to be a direction vector, so translation part of
    //! matrix is ignored. Note: if you wish to transform surface points and normals
    //! by a matrix, call
    //! multVecMatrix()
    //! for the points and call
    //! multDirMatrix()
    //! on the inverse transpose of the matrix for the normals.
    void        multDirMatrix(const SbVec3d &src, SbVec3d &dst) const;

    //! Multiplies the given line's origin by the matrix, and the
    //! line's direction by the rotation portion of the matrix.
    void        multLineMatrix(const SbLined &src, SbLined &dst) const;

    //! Prints a formatted version of the matrix to the given file pointer.
    void        print(FILE *fp) const;

    //! Binary multiplication of matrices.
    operator double *()          { return &matrix[0][0]; }

    //! Cast: returns reference to 4x4 array
    operator SbMatd &()          { return matrix; }

    //! Make it look like a usual matrix (so you can do m[3][2])
    double *       operator [](int i)        { return &matrix[i][0]; }
    const double * operator [](int i) const  { return &matrix[i][0]; }

    //! Sets value from 4x4 array of elements.
    SbMatrixd &  operator =(const SbMatd &m);

    //! Set the matrix from another SbMatrixd.
    SbMatrixd &  operator =(const SbMatrixd &m);

    //! Set the matrix from an SbRotationd.
    SbMatrixd &  operator =(const SbRotationd &q) { setRotate(q); return *this; }

    //! Performs right multiplication with another matrix.
    SbMatrixd &  operator *=(const SbMatrixd &m)  { return multRight(m); }

    //! Binary multiplication of matrices
    friend INVENTOR_API SbMatrixd        operator *(const SbMatrixd &m1, const SbMatrixd &m2);

    //! Equality comparison operator
    friend INVENTOR_API bool               operator ==(const SbMatrixd &m1, const SbMatrixd &m2);
    friend INVENTOR_API bool               operator !=(const SbMatrixd &m1, const SbMatrixd &m2);

    //! Equality comparison within given tolerance, for each component.
    bool                equals(const SbMatrixd &m, double tolerance) const;

  private:
    SbMatd      matrix;         //!< Storage for 4x4 matrix

    //! Diagonalizes 3x3 matrix
    void        jacobi3(double evalues[3], SbVec3d evectors[3], int &rots) const;

    bool affine_inverse(const SbMatrixd &in, SbMatrixd &out) const;
};


INVENTOR_API SbMatrixd  operator *(const SbMatrixd &m1, const SbMatrixd &m2);

INVENTOR_API bool          operator ==(const SbMatrixd &m1, const SbMatrixd &m2);
inline INVENTOR_API bool operator !=(const SbMatrixd &m1, const SbMatrixd &m2)
{ return !(m1 == m2); }


////////////////////////////////////////////////////////////////////////////////
//! Directed line in 3D with double values.
/*!
\class SbLined
\ingroup Basics
Represents a directed line in 3D. This is a basic Inventor datatype that is
used for representing a 3D line. It is used as input and output by a variety of
Inventor classes.
{}

\par See Also
\par
SbVec3f, SbPlane, SbLine, SbVec3d, SbPlaned
*/
////////////////////////////////////////////////////////////////////////////////

class INVENTOR_API SbLined {
  public:
    //! Constructors. To construct a line from a position and direction,
    //! use:  <tt>SbLined(p0, p0 + dir)</tt>.  The line is directed from \p p0 to \p p1.
    SbLined()    {}

    //! Constructors. To construct a line from a position and direction,
    //! use:  <tt>SbLined(p0, p0 + dir)</tt>.  The line is directed from \p p0 to \p p1.
    SbLined(const SbVec3d &p0, const SbVec3d &p1);

    //! Sets line to pass through points \p p0 and \p p1.
    void                setValue(const SbVec3d &p0, const SbVec3d &p1);

    //! Finds the two closest points between this line and \p line2,
    //! and loads them into \p ptOnThis and \p ptOnLine2.
    //! Returns <tt>FALSE</tt> if the lines are parallel (results undefined), and returns
    //! <tt>TRUE</tt> otherwise.
    bool                getClosestPoints(const SbLined  &line2,
                                         SbVec3d &ptOnThis,
                                         SbVec3d &ptOnLine2 ) const;

    //! Returns the closest point on the line to the given point.
    SbVec3d             getClosestPoint(const SbVec3d &point) const;

    //! Returns position of line origin point and direction vector of line.
    const SbVec3d &     getPosition() const     { return pos; }
    //! Returns position of line origin point and direction vector of line.
    const SbVec3d &     getDirection() const    { return dir; }


  SoINTERNAL public:
    //! Intersect the line with a box, point, line, and triangle.
    bool                intersect( const SbBox3d &box,
                                   SbVec3d &enter, SbVec3d &exit ) const;
    bool                intersect( double angle, const SbBox3d &box ) const;
    bool                intersect( double angle, const SbVec3d &point ) const;
    bool                intersect( double angle, const SbVec3d &v0,
                                   const SbVec3d &v1, SbVec3d &pt ) const;
    bool                intersect( const SbVec3d &v0,
                                  const SbVec3d &v1,
                                  const SbVec3d &v2,
                                  SbVec3d &pt, SbVec3d &barycentric,
                                  bool &front ) const;

  private:
    //! Parametric description:
    //!  l(t) = pos + t * dir
    SbVec3d     pos;
    SbVec3d     dir;
};



////////////////////////////////////////////////////////////////////////////////
//! Oriented plane in 3D with double values.
/*!
\class SbPlaned
\ingroup Basics
Represents an oriented plane in 3D. This is a lightweight
class/datatype that is used for arguments to some Inventor objects. 
{}

\par See Also
\par
SbVec3f, SbLine, SbPlane, SbVec3d, SbLined
*/
////////////////////////////////////////////////////////////////////////////////

class INVENTOR_API SbPlaned {
  public:
    //! Default constructor.
    SbPlaned() { distance = 0.; }

    //! Construct a plane given three points.
    //! \p p0, \p p1, and \p p2 represent three points in the plane.
    SbPlaned(const SbVec3d &p0, const SbVec3d &p1, const SbVec3d &p2);

    //! Construct a plane given normal and distance from origin along normal.
    //! Orientation is given by the normal vector n.
    SbPlaned(const SbVec3d &n, double d);

    //! Construct a plane given normal and a point to pass through
    //! Orientation is given by the normal vector n.
    SbPlaned(const SbVec3d &n, const SbVec3d &p);

    //! Offset a plane by a given distance.
    void                offset(double d);

    //! Intersect line and plane, returning TRUE if there is an intersection,
    //! FALSE if line is parallel to plane.
    bool                intersect(const SbLined &l,
                                  SbVec3d &intersection) const;

    //! Transforms the plane by the given matrix.
    void                transform(const SbMatrixd &matrix);

    //! Returns TRUE if the given point is within the half-space
    //! defined by the plane.
    bool                isInHalfSpace(const SbVec3d &point) const;

    //! Returns the distance of the point to the plane.
    double getDistance(const SbVec3d &point) const;

    //! Returns normal vector to plane.
    const SbVec3d &     getNormal() const               { return normalVec; }
    //! Returns distance from origin to plane.
    double              getDistanceFromOrigin() const   { return distance; }

    //! Equality/inequality comparison operators
    friend INVENTOR_API bool               operator ==(const SbPlaned &p1, const SbPlaned &p2);
    friend INVENTOR_API bool               operator !=(const SbPlaned &p1, const SbPlaned &p2);

  private:
    //! Plane is all p such that normalVec . p - distance = 0

    //! Normal to the plane
    SbVec3d     normalVec;

    //! Distance from origin to plane: distance * normalVec is on the plane
    double       distance;
};

INVENTOR_API bool               operator ==(const SbPlaned &p1, const SbPlaned &p2);
inline INVENTOR_API bool        operator !=(const SbPlaned &p1, const SbPlaned &p2)
{ return !(p1 == p2); }

////////////////////////////////////////////////////////////////////////////////
//! Class for representing a cylinder with double values.
/*!
\class SbCylinderd
\ingroup Basics
This class defines a simple cylinder datatype.  It is used by
the Inventor toolkit for arguments or return values.
{}

\par See Also
\par
SbVec3f, SbLine, SbPlane, SbSphere, SoCylinder, SbCylinder, SbVec3d, SbLined, SbPlaned, SbSphered
*/
////////////////////////////////////////////////////////////////////////////////

class INVENTOR_API SbCylinderd {
  public:

    //! Constructors.  One takes an axis and radius.
    SbCylinderd();

    //! Constructors.  One takes an axis and radius.
    SbCylinderd(const SbLined &a, double r);

    //! Change the axis and radius.
    void        setValue(const SbLined &a, double r);

    //! Set just the axis or radius.
    void        setAxis(const SbLined &a);
    //! Set just the axis or radius.
    void        setRadius(double r);

    //! Return the axis and radius.
    const SbLined &     getAxis() const                 { return axis; }
    //! Return the axis and radius.
    double              getRadius() const               { return radius; }

    //! Intersect line and cylinder, returning TRUE if there is an intersection
    bool        intersect(const SbLined &l, SbVec3d &intersection) const;
    bool        intersect(const SbLined &l,
                          SbVec3d &enter, SbVec3d &exit) const;

  private:
    SbLined     axis;
    double      radius;

    static bool         unitCylinderIntersect(const SbLined &l,
                                              SbVec3d &in, SbVec3d &out);
};




////////////////////////////////////////////////////////////////////////////////
//! Class for representing a sphere with double values.
/*!
\class SbSphered
\ingroup Basics
Represents a sphere in 3D. This is a lightweight datatype that
is used for arguments or return values in the Inventor toolkit. See
SoSphere for a database sphere (used for rendering, picking, etc.).
{}

\par See Also
\par
SbVec3f, SbLine, SbSphere, SbVec3d, SbLined, SoSphere
*/
////////////////////////////////////////////////////////////////////////////////

class INVENTOR_API SbSphered {
  public:

    //! Constructors.
    SbSphered() { radius = 0.; }

    //! Construct a sphere given center and radius
    SbSphered(const SbVec3d &c, double r);

    //! Change the center and radius.
    void        setValue(const SbVec3d &c, double r);

    //! Set just the center or radius.
    void        setCenter(const SbVec3d &c);
    //! Set just the center or radius.
    void        setRadius(double r);

    //! Return the center and radius.
    const SbVec3d &     getCenter() const               { return center; }
    //! Return the center and radius.
    double              getRadius() const               { return radius; }

    //! Return a sphere containing a given box.
    void        circumscribe(const SbBox3d &box);

    //! Intersect line and sphere, returning TRUE if there is an intersection
    bool        intersect(const SbLined &l, SbVec3d &intersection) const;
    bool        intersect(const SbLined &l, SbVec3d &enter, SbVec3d &exit) const;

  private:
    SbVec3d     center;
    double      radius;
};

#endif /* _SB_LINEARD_ */
