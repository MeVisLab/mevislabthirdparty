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
 |      SbVec3f
 |      SbVec2f
 |      SbVec2s
 |      SbVec3s         //!< Extension to SGI OIV 2.1
 |      SbVec4f
 |      SbRotation
 |      SbMatrix
 |      SbViewVolume
 |
 |      SbLine
 |      SbPlane
 |      SbSphere
 |
 |   Author(s)          : Paul S. Strauss, Nick Thompson, 
 |                        David Mott, Alain Dumesny
 |
 ______________  S I L I C O N   G R A P H I C S   I N C .  ____________
 _______________________________________________________________________
 */

#ifndef _SB_LINEAR_
#define _SB_LINEAR_

#include <Inventor/system/SbSystem.h>
#include <math.h>
#include <Inventor/SbBasic.h>

//! -----------------------------------
//!
//! Types/classes defined in this file:
//! 
//! -----------------------------------

typedef float SbMat[4][4];


class SbVec3f;
class SbVec2f;
class SbVec2s;
class SbVec4f;
class SbRotation;
class SbMatrix;

class SbLine;
class SbPlane;
class SbCylinder;
class SbSphere;

//! definition so we can use this in SbViewVolume
class SbBox3f;




////////////////////////////////////////////////////////////////////////////////
//! 3D vector class.
/*!
\class SbVec3f
\ingroup Basics
3D vector class used to store 3D vectors and points. This class is used
throughout Inventor for arguments and return values.
{}

\par See Also
\par
SbVec2f, SbVec4f, SbVec2s, SbRotation
*/
////////////////////////////////////////////////////////////////////////////////

class INVENTOR_API SbVec3f {
  public:

    //! Default constructor.
    SbVec3f() { vec[0] = 0.f; vec[1] = 0.f; vec[2] = 0.f; }

    //! Constructor given vector components.
    SbVec3f(const float v[3])
         { vec[0] = v[0]; vec[1] = v[1]; vec[2] = v[2]; }

    //! Constructor given vector components.
    SbVec3f(float x, float y, float z)
         { vec[0] = x; vec[1] = y; vec[2] = z; }

    //! Constructor given 3 planes.
    SbVec3f(SbPlane &p0, SbPlane &p1, SbPlane &p2);

    //! Returns right-handed cross product of vector and another vector.
    SbVec3f     cross(const SbVec3f &v) const;

    //! Returns dot (inner) product of vector and another vector.
    float       dot(const SbVec3f &v) const;

    //! Returns vector components.
    const float *getValue() const                       { return vec; }

    //! Returns vector components.
    void        getValue(float &x, float &y, float &z) const;

    //! Returns geometric length of vector.
    float       length() const;

    //! Changes vector to be unit length, returning the length before normalization.
    float       normalize();

    //! Negates each component of vector in place.
    void        negate();

    //! Sets the vector components.
    SbVec3f &   setValue(const float v[3])
         { vec[0] = v[0]; vec[1] = v[1]; vec[2] = v[2]; return *this; }

    //! Sets the vector components.
    SbVec3f &   setValue(float x, float y, float z)
         { vec[0] = x; vec[1] = y; vec[2] = z; return *this; }

    //! Sets value of vector to be convex combination of 3 other
    //! vectors, using barycentic coordinates
    SbVec3f &   setValue(const SbVec3f &barycentic,
                const SbVec3f &v0, const SbVec3f &v1, const SbVec3f &v2);

    //! Accesses indexed component of vector
    float &       operator [](int i)            { return (vec[i]); }
    const float & operator [](int i) const      { return (vec[i]); }

    //! Component-wise scalar multiplication and division operators.
    SbVec3f &   operator *=(float d);

    //! Component-wise scalar multiplication and division operators.
    SbVec3f &   operator /=(float d)
        { return *this *= (1.0f / d); }

    //! Component-wise vector addition and subtraction operators.
    SbVec3f &   operator +=(SbVec3f v);
    //! Component-wise vector addition and subtraction operators.
    SbVec3f &   operator -=(SbVec3f v);

    //! Nondestructive unary negation - returns a new vector
    SbVec3f     operator -() const;

    //! Component-wise binary scalar multiplication and division operators
    friend INVENTOR_API SbVec3f operator *(const SbVec3f &v, float d);
    friend INVENTOR_API SbVec3f operator *(float d, const SbVec3f &v);
    friend INVENTOR_API SbVec3f operator /(const SbVec3f &v, float d);

    //! Component-wise binary vector addition and subtraction operators
    friend INVENTOR_API SbVec3f operator +(const SbVec3f &v1, const SbVec3f &v2);

    friend INVENTOR_API SbVec3f operator -(const SbVec3f &v1, const SbVec3f &v2);

    //! Equality comparison operator
    friend INVENTOR_API bool               operator ==(const SbVec3f &v1, const SbVec3f &v2);
    friend INVENTOR_API bool               operator !=(const SbVec3f &v1, const SbVec3f &v2);

    //! Equality comparison within given tolerance em the square of the
    //! length of the maximum distance between the two vectors.
    bool                equals(const SbVec3f v, float tolerance) const;

    //! Returns principal axis that is closest (based on maximum dot
    //! product) to this vector.
    SbVec3f             getClosestAxis() const;

  protected:
    float       vec[3];         //!< Storage for vector components
};

INVENTOR_API SbVec3f        operator *(const SbVec3f &v, float d);
inline INVENTOR_API SbVec3f operator *(float d, const SbVec3f &v)
{ return v * d; }
inline INVENTOR_API SbVec3f operator /(const SbVec3f &v, float d)
{ return v * (1.0f / d); }

INVENTOR_API SbVec3f    operator +(const SbVec3f &v1, const SbVec3f &v2);
INVENTOR_API SbVec3f    operator -(const SbVec3f &v1, const SbVec3f &v2);
INVENTOR_API bool          operator ==(const SbVec3f &v1, const SbVec3f &v2);
inline INVENTOR_API bool operator !=(const SbVec3f &v1, const SbVec3f &v2)
{ return !(v1 == v2); }




////////////////////////////////////////////////////////////////////////////////
//! 2D vector class.
/*!
\class SbVec2f
\ingroup Basics
2D vector class used to store 2D vectors and points. This class is used
throughout Inventor for arguments and return values.
{}

\par See Also
\par
SbVec3f, SbVec4f, SbVec2s, SbRotation
*/
////////////////////////////////////////////////////////////////////////////////

class INVENTOR_API SbVec2f {
  public:

    //! Default constructor.
    SbVec2f() { vec[0] = 0.f; vec[1] = 0.f; }

    //! Constructor given vector components.
    SbVec2f(const float v[2])                           { setValue(v); }

    //! Constructor given vector components.
    SbVec2f(float x, float y)                           { setValue(x, y); }

    //! Returns dot (inner) product of vector and another vector.
    float       dot(const SbVec2f &v) const;

    //! Returns vector components.
    const float *getValue() const                       { return vec; }

    //! Returns vector components.
    void        getValue(float &x, float &y) const;

    //! Returns geometric length of vector.
    float       length() const;

    //! Negates each component of vector in place.
    void        negate();

    //! Changes vector to be unit length.
    float       normalize();

    //! Sets the vector components.
    SbVec2f &   setValue(const float v[2]);

    //! Sets the vector components.
    SbVec2f &   setValue(float x, float y);

    //! Accesses indexed component of vector
    float &       operator [](int i)            { return (vec[i]); }
    const float & operator [](int i) const      { return (vec[i]); }

    //! Component-wise scalar multiplication and division operators.
    SbVec2f &   operator *=(float d);

    //! Component-wise scalar multiplication and division operators.
    SbVec2f &   operator /=(float d)
        { return *this *= (1.0f / d); }

    //! Component-wise vector addition and subtraction operators.
    SbVec2f &   operator +=(const SbVec2f &u);
    //! Component-wise vector addition and subtraction operators.
    SbVec2f &   operator -=(const SbVec2f &u);

    //! Nondestructive unary negation - returns a new vector
    SbVec2f     operator -() const;

    //! Component-wise binary scalar multiplication and division operators
    friend INVENTOR_API SbVec2f operator *(const SbVec2f &v, float d);
    friend INVENTOR_API SbVec2f operator *(float d, const SbVec2f &v);
    friend INVENTOR_API SbVec2f operator /(const SbVec2f &v, float d);

    //! Component-wise binary vector addition and subtraction operators
    friend INVENTOR_API SbVec2f operator +(const SbVec2f &v1, const SbVec2f &v2);

    friend INVENTOR_API SbVec2f operator -(const SbVec2f &v1, const SbVec2f &v2);

    //! Equality comparison operator
    friend INVENTOR_API bool               operator ==(const SbVec2f &v1, const SbVec2f &v2);
    friend INVENTOR_API bool               operator !=(const SbVec2f &v1, const SbVec2f &v2);

    //! Equality comparison within given tolerance em the square of the
    //! length of the maximum distance between the two vectors.
    bool                equals(const SbVec2f v, float tolerance) const;

  protected:
    float       vec[2];         //!< Storage for vector components
};

INVENTOR_API        SbVec2f operator *(const SbVec2f &v, float d);
inline INVENTOR_API SbVec2f operator *(float d, const SbVec2f &v)
{ return v * d; }
inline INVENTOR_API SbVec2f operator /(const SbVec2f &v, float d)
{ return v * (1.0f / d); }

INVENTOR_API SbVec2f operator +(const SbVec2f &v1, const SbVec2f &v2);

INVENTOR_API SbVec2f operator -(const SbVec2f &v1, const SbVec2f &v2);

INVENTOR_API bool               operator ==(const SbVec2f &v1, const SbVec2f &v2);
inline INVENTOR_API bool        operator !=(const SbVec2f &v1, const SbVec2f &v2)
{ return !(v1 == v2); }



////////////////////////////////////////////////////////////////////////////////
//! 2D vector class.
/*!
\class SbVec2s
\ingroup Basics
2D vector class used to store 2D integer vectors and points. This class is used
throughout Inventor for arguments and return values.
{}

\par See Also
\par
SbVec3f, SbVec4f, SbVec2f
*/
////////////////////////////////////////////////////////////////////////////////

class INVENTOR_API SbVec2s {
  public:

    //! Default constructor.
    SbVec2s() { vec[0] = 0; vec[1] = 0; }

    //! Constructor given 2 components.
    SbVec2s(const short v[2])                           { setValue(v); }

    //! Constructor given 2 components.
    SbVec2s(short x, short y)                           { setValue(x, y); }

    //! Returns dot (inner) product of vector and another vector.
    int32_t     dot(const SbVec2s &v) const;

    //! Returns vector components.
    const short *getValue() const                       { return vec; }

    //! Returns vector components.
    void        getValue(short &x, short &y) const;

    //! Negates each component of vector in place.
    void        negate();

    //! Sets vector components.
    SbVec2s &   setValue(const short v[2]);

    //! Sets vector components.
    SbVec2s &   setValue(short x, short y);

    //! Accesses indexed component of vector
    short &       operator [](int i)            { return (vec[i]); }
    const short & operator [](int i) const      { return (vec[i]); }

    //! Component-wise scalar multiplication and division operators.
    SbVec2s &   operator *=(int d);
    //! Component-wise scalar multiplication and division operators.
    SbVec2s &   operator *=(double d);

    //! Component-wise scalar multiplication and division operators.
    SbVec2s &   operator /=(int d);
    //! Component-wise scalar multiplication and division operators.
    SbVec2s &   operator /=(double d)
        { return *this *= (1.0 / d); }

    //! Component-wise vector addition and subtraction operators.
    SbVec2s &   operator +=(const SbVec2s &u);
    //! Component-wise vector addition and subtraction operators.
    SbVec2s &   operator -=(const SbVec2s &u);

    //! Nondestructive unary negation - returns a new vector
    SbVec2s     operator -() const;

    //! Component-wise binary scalar multiplication and division operators
    friend INVENTOR_API SbVec2s operator *(const SbVec2s &v, int d);
    friend INVENTOR_API SbVec2s operator *(const SbVec2s &v, double d);
    friend INVENTOR_API SbVec2s operator *(int d, const SbVec2s &v);
    friend INVENTOR_API SbVec2s operator *(double d, const SbVec2s &v);
    friend INVENTOR_API SbVec2s operator /(const SbVec2s &v, int d);
    friend INVENTOR_API SbVec2s operator /(const SbVec2s &v, double d);

    //! Component-wise binary vector addition and subtraction operators
    friend INVENTOR_API SbVec2s operator +(const SbVec2s &v1, const SbVec2s &v2);

    friend INVENTOR_API SbVec2s operator -(const SbVec2s &v1, const SbVec2s &v2);

    //! Equality comparison operator
    friend INVENTOR_API bool               operator ==(const SbVec2s &v1, const SbVec2s &v2);
    friend INVENTOR_API bool               operator !=(const SbVec2s &v1, const SbVec2s &v2);

  protected:
    short       vec[2];         //!< Storage for vector components
};

INVENTOR_API SbVec2s operator *(const SbVec2s &v, int d);
INVENTOR_API SbVec2s operator *(const SbVec2s &v, double d);
inline INVENTOR_API SbVec2s operator *(int d, const SbVec2s &v)
{ return v * d; }
inline INVENTOR_API SbVec2s operator *(double d, const SbVec2s &v)
{ return v * d; }
INVENTOR_API SbVec2s operator /(const SbVec2s &v, int d);
inline INVENTOR_API SbVec2s operator /(const SbVec2s &v, double d)
{ return v * (1.0 / d); }

INVENTOR_API SbVec2s operator +(const SbVec2s &v1, const SbVec2s &v2);
INVENTOR_API SbVec2s operator -(const SbVec2s &v1, const SbVec2s &v2);

INVENTOR_API bool               operator ==(const SbVec2s &v1, const SbVec2s &v2);
inline INVENTOR_API bool               operator !=(const SbVec2s &v1, const SbVec2s &v2)
{ return !(v1 == v2); }

///////////////////////////////////////////////////////////////////////////////
///
////  \class SbVec3s
///
///  3D vector used to represet points or directions. Each component of
///  the vector is a (short) integer.
///
//////////////////////////////////////////////////////////////////////////////

class INVENTOR_API SbVec3s {
  public:

    //! Default constructor
    SbVec3s() { vec[0] = 0; vec[1] = 0; vec[2] = 0; }

    //! Constructor given an array of 3 components
    SbVec3s(const short v[3])                           { setValue(v); }

    //! Constructor given 3 individual components
    SbVec3s(short x, short y, short z)                  { setValue(x, y, z); }

    //! Returns dot (inner) product of vector and another vector.
    int32_t     dot(const SbVec3s &v) const;

    //! Returns vector components.
    const short *getValue() const                       { return vec; }

    //! Returns vector components.
    void        getValue(short &x, short &y, short &z) const;

    //! Negates each component of vector in place.
    void        negate();

    //! Sets value of vector from array of 3 components
    SbVec3s &   setValue(const short v[3]);

    //! Sets value of vector from 3 individual components
    SbVec3s &   setValue(short x, short y, short z);

    //! Accesses indexed component of vector
    short &       operator [](int i)            { return (vec[i]); }
    const short & operator [](int i) const      { return (vec[i]); }

    //! Component-wise scalar multiplication and division operators
    SbVec3s &   operator *=(int d);
    SbVec3s &   operator *=(double d);

    SbVec3s &   operator /=(int d);
    SbVec3s &   operator /=(double d)
        { return *this *= (1.0 / d); }

    //! Component-wise vector addition and subtraction operators.
    SbVec3s &   operator +=(const SbVec3s &u);
    //! Component-wise vector addition and subtraction operators.
    SbVec3s &   operator -=(const SbVec3s &u);

    //! Nondestructive unary negation - returns a new vector
    SbVec3s     operator -() const;

    //! Component-wise binary scalar multiplication and division operators
    friend INVENTOR_API SbVec3s operator *(const SbVec3s &v, int d);
    friend INVENTOR_API SbVec3s operator *(const SbVec3s &v, double d);
    friend INVENTOR_API SbVec3s operator *(int d, const SbVec3s &v);
    friend INVENTOR_API SbVec3s operator *(double d, const SbVec3s &v);
    friend INVENTOR_API SbVec3s operator /(const SbVec3s &v, int d);
    friend INVENTOR_API SbVec3s operator /(const SbVec3s &v, double d);

    //! Component-wise binary vector addition and subtraction operators
    friend INVENTOR_API SbVec3s operator +(const SbVec3s &v1, const SbVec3s &v2);

    friend INVENTOR_API SbVec3s operator -(const SbVec3s &v1, const SbVec3s &v2);

    //! Equality comparison operator
    friend INVENTOR_API bool               operator ==(const SbVec3s &v1, const SbVec3s &v2);
    friend INVENTOR_API bool               operator !=(const SbVec3s &v1, const SbVec3s &v2);

  protected:
    short       vec[3];         //!< Storage for vector components
};


INVENTOR_API SbVec3s operator *(const SbVec3s &v, int d);
INVENTOR_API SbVec3s operator *(const SbVec3s &v, double d);
inline INVENTOR_API SbVec3s operator *(int d, const SbVec3s &v)
{ return v * d; }
inline INVENTOR_API SbVec3s operator *(double d, const SbVec3s &v)
{ return v * d; }
INVENTOR_API SbVec3s operator /(const SbVec3s &v, int d);
inline INVENTOR_API SbVec3s operator /(const SbVec3s &v, double d)
{ return v * (1.0 / d); }

INVENTOR_API SbVec3s operator +(const SbVec3s &v1, const SbVec3s &v2);
INVENTOR_API SbVec3s operator -(const SbVec3s &v1, const SbVec3s &v2);

INVENTOR_API bool               operator ==(const SbVec3s &v1, const SbVec3s &v2);
inline INVENTOR_API bool        operator !=(const SbVec3s &v1, const SbVec3s &v2)
{ return !(v1 == v2); }


////////////////////////////////////////////////////////////////////////////////
//! 4D vector class.
/*!
\class SbVec4f
\ingroup Basics
4D vector class used to store homogeneous coordinates. This class is used
in Inventor for arguments and return values.
{}

\par See Also
\par
SbVec2f, SbVec3f, SbVec2s, SbRotation
*/
////////////////////////////////////////////////////////////////////////////////

class INVENTOR_API SbVec4f {
  public:

    //! Default constructor.
    SbVec4f() { vec[0] = 0.f; vec[1] = 0.f; vec[2] = 0.f; vec[3] = 0.f; }

    //! Constructor given vector components.
    SbVec4f(const float v[4])                           { setValue(v); }

    //! Constructor given vector components.
    SbVec4f(float x, float y, float z, float w)       { setValue(x, y, z, w); }

    //! Returns dot (inner) product of vector and another vector.
    float       dot(const SbVec4f &v) const;

    //! Returns the real portion of the vector by dividing by the fourth value.
    void        getReal(SbVec3f &v) const;

    //! Returns the real portion of the vector by dividing by the fourth value.
    SbVec3f     getReal() const { SbVec3f tmp; getReal(tmp); return tmp; }

    //! Returns vector components.
    const float *getValue() const                       { return vec; }

    //! Returns vector components.
    void        getValue(float &x, float &y, float &z, float &w) const;

    //! Returns geometric length of vector.
    float       length() const;

    //! Negates each component of vector in place.
    void        negate();

    //! Changes vector to be unit length.
    float       normalize();

    //! Sets the vector components.
    SbVec4f &   setValue(const float v[4]);

    //! Sets the vector components.
    SbVec4f &   setValue(float x, float y, float z, float w);

    //! Accesses indexed component of vector
    float &       operator [](int i)            { return (vec[i]); }
    const float & operator [](int i) const      { return (vec[i]); }

    //! Component-wise scalar multiplication and division operators.
    SbVec4f &   operator *=(float d);

    //! Component-wise scalar multiplication and division operators.
    SbVec4f &   operator /=(float d)
        { return *this *= (1.0f / d); }

    //! Component-wise vector addition and subtraction operators.
    SbVec4f &   operator +=(const SbVec4f &u);
    //! Component-wise vector addition and subtraction operators.
    SbVec4f &   operator -=(const SbVec4f &u);

    //! Nondestructive unary negation - returns a new vector
    SbVec4f     operator -() const;

    //! Component-wise binary scalar multiplication and division operators
    friend INVENTOR_API SbVec4f operator *(const SbVec4f &v, float d);
    friend INVENTOR_API SbVec4f operator *(float d, const SbVec4f &v);
    friend INVENTOR_API SbVec4f operator /(const SbVec4f &v, float d);

    //! Component-wise binary vector addition and subtraction operators
    friend INVENTOR_API SbVec4f operator +(const SbVec4f &v1, const SbVec4f &v2);

    friend INVENTOR_API SbVec4f operator -(const SbVec4f &v1, const SbVec4f &v2);

    //! Equality comparison operator
    friend INVENTOR_API bool               operator ==(const SbVec4f &v1, const SbVec4f &v2);
    friend INVENTOR_API bool               operator !=(const SbVec4f &v1, const SbVec4f &v2);

    //! Equality comparison within given tolerance em the square of the
    //! length of the maximum distance between the two vectors.
    bool                equals(const SbVec4f v, float tolerance) const;

  protected:
    float       vec[4];         //!< Storage for vector components
};

INVENTOR_API SbVec4f operator *(const SbVec4f &v, float d);
inline INVENTOR_API SbVec4f operator *(float d, const SbVec4f &v)
{ return v * d; }
inline INVENTOR_API SbVec4f operator /(const SbVec4f &v, float d)
{ return v * (1.0f / d); }

INVENTOR_API SbVec4f operator +(const SbVec4f &v1, const SbVec4f &v2);

INVENTOR_API SbVec4f operator -(const SbVec4f &v1, const SbVec4f &v2);

INVENTOR_API bool               operator ==(const SbVec4f &v1, const SbVec4f &v2);
inline INVENTOR_API bool        operator !=(const SbVec4f &v1, const SbVec4f &v2)
{ return !(v1 == v2); }



////////////////////////////////////////////////////////////////////////////////
//! Class for representing a rotation.
/*!
\class SbRotation
\ingroup Basics
Object that stores a rotation. There are several ways to specify a
rotation: quaternion (4 floats), 4x4 rotation matrix, or axis and angle.
All angles are in radians and all rotations are right-handed.
{}
\par
NOTES

Rotations are stored internally as quaternions.

\par See Also
\par
SbVec3f, SbMatrix
*/
////////////////////////////////////////////////////////////////////////////////

class INVENTOR_API SbRotation {
  public:

    //! Default constructor, initialized to identity.
    SbRotation()
    { quat[0] = 0.f; quat[1] = 0.f; quat[2] = 0.f; quat[3] = 1.f; }

    //! \see SbRotation(const SbVec3f &rotateFrom, const SbVec3f &rotateTo)
    SbRotation(const float v[4])
        { setValue(v); }

    //! \see SbRotation(const SbVec3f &rotateFrom, const SbVec3f &rotateTo)
    SbRotation(float q0, float q1, float q2, float q3)
        { setValue(q0, q1, q2, q3); }

    //! \see SbRotation(const SbVec3f &rotateFrom, const SbVec3f &rotateTo)
    SbRotation(const SbMatrix &m)
        { setValue(m); }

    //! \see SbRotation(const SbVec3f &rotateFrom, const SbVec3f &rotateTo)
    SbRotation(const SbVec3f &axis, float radians)
        { setValue(axis, radians); }

    //! Constructors for rotation. The axis/radians constructor creates a rotation of
    //! angle radians about the given axis.  The constructors that take four floats 
    //! create a quaternion from those floats (careful, this differs from the four 
    //! numbers in an axis/radian definition). 
    //! Matrix constructor requires a valid rotation matrix.
    //! The rotateFrom/To constructor defines rotation that rotates from one vector 
    //! into another.
    //! The \p rotateFrom and \p rotateTo vectors are normalized by the constructor
    //! before calculating the rotation.
    SbRotation(const SbVec3f &rotateFrom, const SbVec3f &rotateTo)
        { setValue(rotateFrom, rotateTo); }

    //! Returns pointer to array of 4 components defining quaternion
    const float *       getValue() const
        { return (quat); }

    //! Returns 4 individual components of rotation quaternion 
    void                getValue(float &q0, float &q1,
                                 float &q2, float &q3) const;

    //! Returns corresponding 3D rotation axis vector and angle in radians
    void                getValue(SbVec3f &axis, float &radians) const;

    //! Returns corresponding 4x4 rotation matrix
    void                getValue(SbMatrix &matrix) const;

    //! Returns corresponding 4x4 rotation matrix
    SbMatrix getMatrix() const;
    
    //! Returns corresponding 3D rotation axis vector.
    SbVec3f getAxis() const { SbVec3f axis; float radians; getValue(axis, radians); return axis; }
    //! Returns corresponding angle in radians.
    float   getAngle() const { SbVec3f axis; float radians; getValue(axis, radians); return radians; }

    //! Changes a rotation to be its inverse.
    SbRotation &        invert();

    //! Returns the inverse of a rotation.
    SbRotation          inverse() const
        { SbRotation q = *this; return q.invert(); }

    //! Sets value of rotation from array of 4 components of a quaternion.
    SbRotation &        setValue(const float q[4]);

    //! Sets value of rotation from 4 individual components of a quaternion.
    SbRotation &        setValue(float q0, float q1, float q2, float q3);

    //! Sets value of rotation from a rotation matrix.
    SbRotation &        setValue(const SbMatrix &m);

    //! Sets value of vector from 3D rotation axis vector and angle in radians.
    SbRotation &        setValue(const SbVec3f &axis, float radians);

    //! Sets rotation to rotate one direction vector to another
    SbRotation &        setValue(const SbVec3f &rotateFrom,
                                 const SbVec3f &rotateTo);

    //! Multiplies by another rotation; results in product of rotations.
    SbRotation &         operator *=(const SbRotation &q);

    //! Equality comparison operator
    friend INVENTOR_API bool       operator ==(const SbRotation &q1, const SbRotation &q2);
    friend INVENTOR_API bool       operator !=(const SbRotation &q1, const SbRotation &q2);

    //! Equality comparison within given tolerance em the square of the
    //! length of the maximum distance between the two quaternion vectors.
    bool                equals(const SbRotation &r, float tolerance) const;

    //! Multiplication of two rotations; results in product of rotations
    friend INVENTOR_API SbRotation      operator *(const SbRotation &q1, const SbRotation &q2);

    //! Multiplies the given vector by the matrix of this rotation.
    void        multVec(const SbVec3f &src, SbVec3f &dst) const;

    //! Multiplies the given vector by the matrix of this rotation.
    SbVec3f     transformPoint(const SbVec3f &src) const { SbVec3f dst; multVec(src, dst); return dst; }

    //! Keep the axis the same. Multiply the angle of rotation by 
    //! the amount \p scaleFactor.
    void scaleAngle( float scaleFactor );

    //! Spherical linear interpolation: as \p t goes from 0 to 1, returned
    //! value goes from \p rot0 to \p rot1.
    static SbRotation   slerp(const SbRotation &rot0,
                              const SbRotation &rot1, float t);

    //! Returns a null rotation.
    static SbRotation   identity()
        { return SbRotation(0.0, 0.0, 0.0, 1.0); }

  private:
    float       quat[4];        //!< Storage for quaternion components

    //! Returns the norm (square of the 4D length) of a rotation's quaterion
    float       norm() const;

    //! Normalizes a rotation quaternion to unit 4D length
    void        normalize();
};

INVENTOR_API        bool       operator ==(const SbRotation &q1, const SbRotation &q2);
inline INVENTOR_API bool       operator !=(const SbRotation &q1, const SbRotation &q2)
{ return !(q1 == q2); }
INVENTOR_API SbRotation     operator *(const SbRotation &q1, const SbRotation &q2);



////////////////////////////////////////////////////////////////////////////////
//! 4x4 matrix class.
/*!
\class SbMatrix
\ingroup Basics
4x4 matrix class/datatype used by many Inventor node and action classes.
The matrices are stored in row-major order.
{}

\par See Also
\par
SbVec3f, SbRotation
*/
////////////////////////////////////////////////////////////////////////////////

class INVENTOR_API SbMatrix {
  public:

    //! Default constructor, initialized to identity.
    SbMatrix() {
      makeIdentity();
    }

    //! Constructor given all 16 elements in row-major order
    SbMatrix(float a11, float a12, float a13, float a14,
             float a21, float a22, float a23, float a24, 
             float a31, float a32, float a33, float a34, 
             float a41, float a42, float a43, float a44);

    //! Constructors.
    SbMatrix(const SbMat &m);

    //! Sets value from 4x4 array of elements.
    void        setValue(const SbMat &m);

    //! Sets value from a float array of 16 elements.
    void        setValue(const float* data);

    public:

    //! Sets matrix to be identity.
    void        makeIdentity();

    //! Returns an identity matrix.
    static SbMatrix     identity();

    //! Sets matrix to rotate by given rotation.
    void        setRotate(const SbRotation &q);

    //! Sets matrix to scale by given uniform factor.
    void        setScale(float s);

    //! Sets matrix to scale by given vector.
    void        setScale(const SbVec3f &s);

    //! Sets matrix to translate by given vector.
    void        setTranslate(const SbVec3f &t);

    //! Composes the matrix based on a translation, rotation, scale,
    //! orientation for scale, and center.  The "center" is the
    //! center point for scaling and rotation.  The "scaleOrientation"
    //! chooses the primary axes for the scale.
    void        setTransform(
                        const SbVec3f &translation,
                        const SbRotation &rotation,
                        const SbVec3f &scaleFactor,
                        const SbRotation &scaleOrientation,
                        const SbVec3f &center);
    //! Overloaded methods as a kludge because the compiler won't let
    //! us have SbVec3f(0,0,0) as a default value:
    void        setTransform(const SbVec3f &t, const SbRotation &r,
                             const SbVec3f &s)
                { setTransform(t, r, s,
                               SbRotation(0,0,0,1), SbVec3f(0,0,0)); }
    void        setTransform(const SbVec3f &t, const SbRotation &r,
                             const SbVec3f &s, const SbRotation &so)
                { setTransform(t, r, s, so, SbVec3f(0,0,0)); }

    //! Decomposes the matrix into a translation, rotation, scale,
    //! and scale orientation.  Any projection information is discarded.
    //! The decomposition depends upon choice of center point for
    //! rotation and scaling, which is optional as the last parameter.
    //! Note that if the center is 0, decompose() is the same as
    //! factor() where "t" is translation, "u" is rotation, "s" is scaleFactor,
    //! and "r" is ScaleOrientattion.
    void        getTransform(SbVec3f &translation,
                          SbRotation &rotation,
                          SbVec3f &scaleFactor,
                          SbRotation &scaleOrientation,
                          const SbVec3f &center) const;
    void        getTransform(SbVec3f &t, SbRotation &r,
                          SbVec3f &s, SbRotation &so) const
                { getTransform(t, r, s, so, SbVec3f(0,0,0)); }


    //! The following methods return matrix values and other info:

    //! Returns 4x4 array of elements
    void        getValue(SbMat &m) const;
    const SbMat &       getValue() const { return matrix; }

    //! Returns determinant of 3x3 submatrix composed of given row and
    //! column indices (0-3 for each).
    float       det3(int r1, int r2, int r3, int c1, int c2, int c3) const;

    //! Returns determinant of upper-left 3x3 submatrix
    float       det3() const { return det3(0, 1, 2, 0, 1, 2); }

    //! Returns determinant of entire matrix.
    float       det4() const;

    //! Factors a matrix m into 5 pieces: m = r s r^ u t, where r^
    //! means transpose of r, and r and u are rotations, s is a scale,
    //! and t is a translation. Any projection information is returned
    //! in \p proj.
    //! NOTE: the projection matrix is always set to identity.
    bool        factor(SbMatrix &r, SbVec3f &s, SbMatrix &u,
                       SbVec3f &t, SbMatrix &proj) const;

    //! Returns inverse of matrix. Results are undefined for
    //! singular matrices.  Uses LU decomposition.
    SbMatrix    inverse() const;

    //! Perform in-place LU decomposition of matrix.  \p index is index of rows
    //! in matrix. \p d is the parity of row swaps.  Returns FALSE if singular.
    bool        LUDecomposition(int index[4], float &d);

    //! Perform back-substitution on LU-decomposed matrix. Index is
    //! permutation of rows from original matrix.
    void        LUBackSubstitution(int index[4], float b[4]) const;

    //! Returns transpose of matrix.
    SbMatrix    transpose() const;

    //! Multiplies matrix by given matrix on right or left.
    SbMatrix &  multRight(const SbMatrix &m);   // this = this * m
    //! Multiplies matrix by given matrix on right or left.
    SbMatrix &  multLeft(const SbMatrix &m);    // this = m * this

    //! Multiplies given row vector by matrix, giving vector result. Use this method to transform points from object coordinates to world coordinates. (MEVIS)
    SbVec3f     transformPoint(const SbVec3f &src) const { SbVec3f dst; multVecMatrix(src, dst); return dst; }
    //! Multiplies given row vector by matrix, giving vector result. Takes homogenous coordinate and returns homogenous coordinate. (MEVIS)
    SbVec4f     transformPoint(const SbVec4f &src) const { SbVec4f dst; multVecMatrix(src, dst); return dst; }

    //! Multiplies given row vector by matrix, giving vector result.
    //! \p src is assumed to be a direction vector, so translation part of
    //! matrix is ignored. Note: if you wish to transform surface points and normals
    //! by a matrix, call
    //! multVecMatrix()
    //! for the points and call
    //! multDirMatrix()
    //! on the inverse transpose of the matrix for the normals. (MEVIS)
    SbVec3f     transformDirection(const SbVec3f &src) const { SbVec3f dst; multDirMatrix(src, dst); return dst; }

    //! Multiplies the given line's origin by the matrix, and the
    //! line's direction by the rotation portion of the matrix. (MEVIS)
    SbLine     transformLine(const SbLine &src) const;

    //! Multiplies matrix by given column vector, giving vector result. NOTE: Typically you should use multVecMatrix() instead,
    //! since object/world transforms normally use row vectors.
    void        multMatrixVec(const SbVec3f &src, SbVec3f &dst) const;

    //! Multiplies given row vector by matrix, giving vector result. Use this method to transform points from object coordinates to world coordinates. 
    void        multVecMatrix(const SbVec3f &src, SbVec3f &dst) const;
    //! Multiplies given row vector by matrix, giving vector result. Takes homogenous coordinate and returns homogenous coordinate.
    void        multVecMatrix(const SbVec4f &src, SbVec4f &dst) const;
    //! Multiplies given row vector by matrix, giving vector result. Takes SbVec4(src,1.f) coordinate and returns homogenous coordinate.
    void        multVecMatrix(const SbVec3f &src, SbVec4f &dst) const;

    //! Multiplies given row vector by matrix, giving vector result.
    //! \p src is assumed to be a direction vector, so translation part of
    //! matrix is ignored. Note: if you wish to transform surface points and normals
    //! by a matrix, call
    //! multVecMatrix()
    //! for the points and call
    //! multDirMatrix()
    //! on the inverse transpose of the matrix for the normals.
    void        multDirMatrix(const SbVec3f &src, SbVec3f &dst) const;

    //! Multiplies the given line's origin by the matrix, and the
    //! line's direction by the rotation portion of the matrix.
    void        multLineMatrix(const SbLine &src, SbLine &dst) const;
    
    //! Prints a formatted version of the matrix to the given file pointer.
    void        print(FILE *fp) const;

    //! Binary multiplication of matrices.
    operator float *()          { return &matrix[0][0]; }

    //! Cast: returns reference to 4x4 array
    operator SbMat &()          { return matrix; }

    //! Make it look like a usual matrix (so you can do m[3][2])
    float *       operator [](int i)        { return &matrix[i][0]; }
    const float * operator [](int i) const  { return &matrix[i][0]; }

    //! Sets value from 4x4 array of elements.
    SbMatrix &  operator =(const SbMat &m);

    //! Set the matrix from another SbMatrix.
    SbMatrix &  operator =(const SbMatrix &m);

    //! Set the matrix from an SbRotation.
    SbMatrix &  operator =(const SbRotation &q) { setRotate(q); return *this; }

    //! Performs right multiplication with another matrix.
    SbMatrix &  operator *=(const SbMatrix &m)  { return multRight(m); }

    //! Binary multiplication of matrices
    friend INVENTOR_API SbMatrix        operator *(const SbMatrix &m1, const SbMatrix &m2);

    //! Equality comparison operator
    friend INVENTOR_API bool               operator ==(const SbMatrix &m1, const SbMatrix &m2);
    friend INVENTOR_API bool               operator !=(const SbMatrix &m1, const SbMatrix &m2);

    //! Equality comparison within given tolerance, for each component.
    bool                equals(const SbMatrix &m, float tolerance) const;

  private:
    SbMat       matrix;         //!< Storage for 4x4 matrix

    //! Diagonalizes 3x3 matrix
    void        jacobi3(float evalues[3], SbVec3f evectors[3], int &rots) const;

    bool affine_inverse(const SbMatrix &in, SbMatrix &out) const;
};

INVENTOR_API SbMatrix        operator *(const SbMatrix &m1, const SbMatrix &m2);

INVENTOR_API        bool               operator ==(const SbMatrix &m1, const SbMatrix &m2);
inline INVENTOR_API bool               operator !=(const SbMatrix &m1, const SbMatrix &m2)
{ return !(m1 == m2); }


////////////////////////////////////////////////////////////////////////////////
//! 3D viewing volume class.
/*!
\class SbViewVolume
\ingroup Basics
Class used to represent a 3D viewing volume. This class is used
to represent viewing frusta and picking volumes.  For perspective projection,
the view volume is a frustum. For orthographic (parallel) projection, the
view volume is a rectangular prism.

\par See Also
\par
SbVec3f, SbVec2f, SbBox3f, SbMatrix, SbRotation
*/
////////////////////////////////////////////////////////////////////////////////

class INVENTOR_API SbViewVolume {
  public:

    //! Constructor and destructor.
    SbViewVolume();
    //! Constructor and destructor.
    ~SbViewVolume()                            {}

    //! Returns two matrices corresponding to the view volume.  The
    //! first is a viewing matrix, which is guaranteed to be an affine
    //! transformation.  The second is suitable for use as a projection
    //! matrix in OpenGL.
    void                getMatrices(SbMatrix &affine, SbMatrix &proj) const;

    //! Returns the affine viewing matrix.
    SbMatrix            getViewingMatrix() const { SbMatrix affine; SbMatrix proj; getMatrices(affine, proj); return affine; }

    //! Returns the projection matrix.
    SbMatrix            getProjectionMatrix() const { SbMatrix affine; SbMatrix proj; getMatrices(affine, proj); return proj; }

    //! Like the method above, but returns the affine and projection parts
    //! together in one matrix (i.e., affine.multRight( proj ) ).
    SbMatrix            getMatrix() const;

    //! Returns a matrix that transforms the view volume into camera
    //! space: it translates the view volume so the viewpoint is at
    //! the origin, and rotates it so the view direction is along the
    //! negative z axis.
    SbMatrix            getCameraSpaceMatrix() const;

    //! Maps a 2d point (in 0 <= x,y <= 1) to a 3d line.
    void                projectPointToLine(const SbVec2f &pt,
                                        SbLine &line) const;
    void                projectPointToLine(const SbVec2f &pt,
                                       SbVec3f &line0, SbVec3f &line1) const;
    //! Maps a 2d point (in 0 <= x,y <= 1) to a 3d line.
    SbLine              projectPointToLine(const SbVec2f &pt) const;
    
    //! Maps the 3D point in world coordinates to a 2D point in
    //! normalized screen coordinates (0 &lt;= x,y,z &lt;= 1).
    //! The z-screen coordinate represents the homogenized z coordinate
    //! which goes (nonlinearly) from 0 at the near clipping plane to
    //! 1 at the far clipping plane.
    void                projectToScreen(const SbVec3f &src,
                                        SbVec3f &dst) const;

    //! Maps the 3D point in world coordinates to a 2D point in
    //! normalized screen coordinates (0 &lt;= x,y,z &lt;= 1).
    //! The z-screen coordinate represents the homogenized z coordinate
    //! which goes (nonlinearly) from 0 at the near clipping plane to
    //! 1 at the far clipping plane.
    SbVec3f              projectToScreen(const SbVec3f &src) const { SbVec3f dst; projectToScreen(src, dst); return dst; }

    //! Returns a plane parallel to the near (or far) plane of the view
    //! volume at a given distance from the projection point (eye).
    SbPlane             getPlane(float distFromEye) const;

    //! Returns the point along the line of sight at the given distance
    //! from the projection point (eye).
    SbVec3f             getSightPoint(float distFromEye) const;

    //! Returns the projection of a given point in normalized screen
    //! coordinates (see projectToScreen()) onto the plane parallel to the
    //! near plane that is at \p distFromEye units from the eye.
    SbVec3f             getPlanePoint(float distFromEye,
                                      const SbVec2f &normPoint) const;

    //! Returns a rotation that would align a viewed object so that
    //! its positive x-axis (of its object space) is to the right in
    //! the view and its positive y-axis is up. If \p rightAngleOnly is
    //! TRUE, it will come as close as it can to this goal by using
    //! only 90 degree rotations.
    SbRotation          getAlignRotation(bool rightAngleOnly = FALSE) const;

    //! Returns a scale factor that would scale a unit sphere centered
    //! at \p worldCenter so that it would appear to have the given radius
    //! in normalized screen coordinates when projected onto the near plane.
    float               getWorldToScreenScale(const SbVec3f &worldCenter,
                                              float normRadius) const;

    //! Projects the given 3D bounding box onto the near plane and
    //! returns the size (in normalized screen coordinates) of the
    //! rectangular region that encloses it.
    SbVec2f             projectBox(const SbBox3f &box) const;

    //! Given a view volume, this narrows the view to the given sub-rectangle
    //! of the near plane. The coordinates of the rectangle are between
    //! 0 and 1, where (0,0) is the lower-left corner of the near plane
    //! and (1,1) is the upper-right corner.
    SbViewVolume        narrow(float left,  float bottom,
                               float right, float top) const;

    //! Narrow a view volume by the given box.  The box must lie inside
    //! the unit cube, and the view will be shrunk according to the
    //! size of the box.
    SbViewVolume        narrow(const SbBox3f &box) const;

    //! Sets up an orthographic view volume with the given sides.
    //! The parameters are the same as for the OpenGL glOrtho() routine.
    void                ortho(float left,   float right,
                              float bottom, float top,
                              float nearVal,   float farVal);

    //! Sets up a perspective view volume with the given field of view
    //! and aspect ratio. The parameters are the same as for the OpenGL
    //! gluPerspective() routine, except that the field of view angle is
    //! specified in radians.
    void                perspective(float fovy, float aspect,
                                    float nearVal, float farVal);

    //! Rotate the camera view direction.  Note that this accomplishes
    //! the reverse of doing an OpenGL glRotate() command after defining a
    //! camera, which rotates the scene viewed by the camera.
    void                rotateCamera(const SbRotation &q);

    //! Translate the camera viewpoint.  Note that this accomplishes
    //! the reverse of doing an OpenGL glTranslate() command after defining a
    //! camera, which translates the scene viewed by the camera.
    void                translateCamera(const SbVec3f &v);

    //! Returns the positive z axis in eye space.  In this coordinate
    //! system, the z value of the near plane should be GREATER than the
    //! z value of the far plane.
    SbVec3f             zVector() const;

    //! Returns a narrowed view volume which contains as tightly as
    //! possible the given interval on the z axis (in eye space).  The
    //! returned view volume will never be larger than the current volume,
    //! however.  \p near and \p far are given in terms of zVector(): this
    //! means that \p near &gt; \p far must hold.
    SbViewVolume        zNarrow(float nearVal, float farVal) const;

    //! Scales width and height of view volume by given factor.
    void                scale(float factor);

    //! Scales view volume to be the given ratio of its current width,
    //! leaving the resulting view volume centered about the
    //! same point (in the near plane) as the current one.
    void                scaleWidth(float ratio);
    //! Scales view volume to be the given ratio of its current
    //! height, leaving the resulting view volume centered about the
    //! same point (in the near plane) as the current one.
    void                scaleHeight(float ratio);

    //! Return projection information
    enum ProjectionType { 
        ORTHOGRAPHIC, 
        PERSPECTIVE 
    };

    //! Returns projection information.
    ProjectionType      getProjectionType() const  { return type; }

    //! Returns projection information.
    const SbVec3f &     getProjectionPoint() const { return projPoint; }

    //! Returns projection information.
    const SbVec3f &     getProjectionDirection() const   { return projDir; }

    //! Returns distance from projection point to near plane.
    float               getNearDist() const        { return nearDist; }

    //! Returns distance from projection point to far plane.
    float               getFarDist() const        { return nearDist + nearToFar; }

    //! Returns bounds of viewing frustum.
    float               getWidth() const      { return (lrfO-llfO).length(); }
    //! Returns bounds of viewing frustum.
    float               getHeight() const     { return (ulfO-llfO).length(); }
    //! Returns bounds of viewing frustum.
    float               getDepth() const      { return nearToFar; }

  SoINTERNAL public:
    ProjectionType type;

    //! Note that there is redundant info in this data structure and its
    //! elements should not be changed by hand.  
    SbVec3f     projPoint;              //!< must be (0,0,0) for ortho
    SbVec3f     projDir;
    float       nearDist;               //!< distance to near plane
    float       nearToFar;              //!< distance between z clips
    SbVec3f     llf;
    SbVec3f     lrf;
    SbVec3f     ulf;

    //! Transforms the view volume by the given matrix. NOTE: if the
    //! matrix performs a scale and a rotation, angles between the
    //! transformed projection direction and the sides of the view
    //! volume may not be preserved.
    void        transform(const SbMatrix &matrix);

    //! Returns TRUE if view volume contains point
    bool        intersect(const SbVec3f &point) const;

    //! Returns TRUE if line segment between 2 points may intersect
    //! volume. Returns closest point on line to center ray of volume
    //! if intersection is found.
    bool        intersect(const SbVec3f &p0, const SbVec3f &p1,
                          SbVec3f &closestPoint) const;

    //! Returns TRUE if bounding box may intersect volume
    bool        intersect(const SbBox3f &box) const;

    //! Returns TRUE if the bounding box defined by min,max is totally
    //! outside plane p.
    bool        outsideTest(const SbPlane &p,
                        const SbVec3f &min, const SbVec3f &max) const;

  private:
    //! Points on the near clipping plane.  Add in the projPoint to
    //! figure out where they are in world space:
    SbVec3f     llfO;                   //!< x = -w, y = -w, z = -w
    SbVec3f     lrfO;                   //!< x =  w, y = -w, z = -w
    SbVec3f     ulfO;                   //!< x = -w, y =  w, z = -w
};



////////////////////////////////////////////////////////////////////////////////
//! Directed line in 3D.
/*!
\class SbLine
\ingroup Basics
Represents a directed line in 3D. This is a basic Inventor datatype that is
used for representing a 3D line. It is used as input and output by a variety of
Inventor classes.
{}

\par See Also
\par
SbVec3f, SbPlane
*/
////////////////////////////////////////////////////////////////////////////////

class INVENTOR_API SbLine {
  public:
    //! Constructors. To construct a line from a position and direction,
    //! use:  <tt>SbLine(p0, p0 + dir)</tt>.  The line is directed from \p p0 to \p p1.
    SbLine()    {}

    //! Constructors. To construct a line from a position and direction,
    //! use:  <tt>SbLine(p0, p0 + dir)</tt>.  The line is directed from \p p0 to \p p1.
    SbLine(const SbVec3f &p0, const SbVec3f &p1);

    //! Sets line to pass through points \p p0 and \p p1.
    void                setValue(const SbVec3f &p0, const SbVec3f &p1);

    //! Finds the two closest points between this line and \p line2,
    //! and loads them into \p ptOnThis and \p ptOnLine2.
    //! Returns <tt>FALSE</tt> if the lines are parallel (results undefined), and returns
    //! <tt>TRUE</tt> otherwise.
    bool                getClosestPoints(const SbLine  &line2,
                                         SbVec3f &ptOnThis,
                                         SbVec3f &ptOnLine2 ) const;

    //! Returns the closest point on the line to the given point.
    SbVec3f             getClosestPoint(const SbVec3f &point) const;

    //! Returns position of line origin point and direction vector of line.
    const SbVec3f &     getPosition() const     { return pos; }
    //! Returns position of line origin point and direction vector of line.
    const SbVec3f &     getDirection() const    { return dir; }


  SoINTERNAL public:
    //! Intersect the line with a box, point, line, and triangle.
    bool                intersect( const SbBox3f &box,
                                   SbVec3f &enter, SbVec3f &exit ) const;
    bool                intersect( float angle, const SbBox3f &box ) const;
    bool                intersect( float angle, const SbVec3f &point ) const;
    bool                intersect( float angle, const SbVec3f &v0,
                                   const SbVec3f &v1, SbVec3f &pt ) const;
    bool                intersect( const SbVec3f &v0,
                                  const SbVec3f &v1,
                                  const SbVec3f &v2,
                                  SbVec3f &pt, SbVec3f &barycentric,
                                  bool &front ) const;

  private:
    //! Parametric description:
    //!  l(t) = pos + t * dir
    SbVec3f     pos;
    SbVec3f     dir;
};



////////////////////////////////////////////////////////////////////////////////
//! Oriented plane in 3D.
/*!
\class SbPlane
\ingroup Basics
Represents an oriented plane in 3D. This is a lightweight
class/datatype that is used for arguments to some Inventor objects. 
{}

\par See Also
\par
SbVec3f, SbLine
*/
////////////////////////////////////////////////////////////////////////////////

class INVENTOR_API SbPlane {
  public:
    //! Default constructor.
    SbPlane() { distance = 0.f; }

    //! Construct a plane given three points.
    //! \p p0, \p p1, and \p p2 represent three points in the plane.
    SbPlane(const SbVec3f &p0, const SbVec3f &p1, const SbVec3f &p2);

    //! Construct a plane given normal and distance from origin along normal.
    //! Orientation is given by the normal vector n.
    SbPlane(const SbVec3f &n, float d);

    //! Construct a plane given normal and a point to pass through
    //! Orientation is given by the normal vector n.
    SbPlane(const SbVec3f &n, const SbVec3f &p);

    //! Offset a plane by a given distance.
    void                offset(float d);

    //! Intersect line and plane, returning TRUE if there is an intersection,
    //! FALSE if line is parallel to plane.
    bool                intersect(const SbLine &l,
                                  SbVec3f &intersection) const;

    //! Transforms the plane by the given matrix.
    void                transform(const SbMatrix &matrix);

    //! Returns TRUE if the given point is within the half-space
    //! defined by the plane.
    bool                isInHalfSpace(const SbVec3f &point) const;

    //! Returns the distance of the point to the plane.
    float getDistance(const SbVec3f &point) const;

    //! Returns normal vector to plane.
    const SbVec3f &     getNormal() const               { return normalVec; }
    //! Returns distance from origin to plane.
    float               getDistanceFromOrigin() const   { return distance; }

    //! Equality/inequality comparison operators
    friend INVENTOR_API bool               operator ==(const SbPlane &p1, const SbPlane &p2);
    friend INVENTOR_API bool               operator !=(const SbPlane &p1, const SbPlane &p2);

  private:
    //! Plane is all p such that normalVec . p - distance = 0

    //! Normal to the plane
    SbVec3f     normalVec;

    //! Distance from origin to plane: distance * normalVec is on the plane
    float       distance;
};

//! Equality/inequality comparison operators
INVENTOR_API        bool               operator ==(const SbPlane &p1, const SbPlane &p2);
inline INVENTOR_API bool               operator !=(const SbPlane &p1, const SbPlane &p2)
{ return !(p1 == p2); }


////////////////////////////////////////////////////////////////////////////////
//! Class for representing a cylinder.
/*!
\class SbCylinder
\ingroup Basics
This class defines a simple cylinder datatype.  It is used by
the Inventor toolkit for arguments or return values.
{}

\par See Also
\par
SbVec3f, SbLine, SbPlane, SbSphere, SoCylinder
*/
////////////////////////////////////////////////////////////////////////////////

class INVENTOR_API SbCylinder {
  public:

    //! Default Constructor.
    SbCylinder();

    //! Create cylinder from axis and radius.
    SbCylinder(const SbLine &a, float r);

    //! Change the axis and radius.
    void        setValue(const SbLine &a, float r);

    //! Set just the axis or radius.
    void        setAxis(const SbLine &a);
    //! Set just the axis or radius.
    void        setRadius(float r);

    //! Return the axis and radius.
    const SbLine &      getAxis() const                 { return axis; }
    //! Return the axis and radius.
    float               getRadius() const               { return radius; }

    //! Intersect line and cylinder, returning TRUE if there is an intersection
    bool        intersect(const SbLine &l, SbVec3f &intersection) const;
    bool        intersect(const SbLine &l,
                          SbVec3f &enter, SbVec3f &exit) const;

  private:
    SbLine      axis;
    float       radius;

    static bool         unitCylinderIntersect(const SbLine &l,
                                              SbVec3f &in, SbVec3f &out);
};




////////////////////////////////////////////////////////////////////////////////
//! Class for representing a sphere.
/*!
\class SbSphere
\ingroup Basics
Represents a sphere in 3D. This is a lightweight datatype that
is used for arguments or return values in the Inventor toolkit. See
SoSphere for a database sphere (used for rendering, picking, etc.).
{}

\par See Also
\par
SbVec3f, SbLine, SoSphere
*/
////////////////////////////////////////////////////////////////////////////////

class INVENTOR_API SbSphere {
  public:

    //! Constructors.
    SbSphere() { radius = 0.f; }

    //! Construct a sphere given center and radius
    SbSphere(const SbVec3f &c, float r);

    //! Change the center and radius.
    void        setValue(const SbVec3f &c, float r);

    //! Set just the center or radius.
    void        setCenter(const SbVec3f &c);
    //! Set just the center or radius.
    void        setRadius(float r);

    //! Return the center and radius.
    const SbVec3f &     getCenter() const               { return center; }
    //! Return the center and radius.
    float               getRadius() const               { return radius; }

    //! Return a sphere containing a given box.
    void        circumscribe(const SbBox3f &box);

    //! Intersect line and sphere, returning TRUE if there is an intersection
    bool        intersect(const SbLine &l, SbVec3f &intersection) const;
    bool        intersect(const SbLine &l, SbVec3f &enter, SbVec3f &exit) const;

  private:
    SbVec3f     center;
    float       radius;
};

#endif /* _SB_LINEAR_ */
