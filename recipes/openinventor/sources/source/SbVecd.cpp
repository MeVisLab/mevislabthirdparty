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
 |   Classes:
 |      SbVec3d
 |      SbVec2d
 |      SbVec4d
 |
 |   Author(s)          : originally by Paul S. Strauss, Nick Thompson, Alain Dumesny
 |                        adapted for double values by Wolf Spindler
 |
 ______________  S I L I C O N   G R A P H I C S   I N C .  ____________
 _______________________________________________________________________
 */

#include <Inventor/SbLineard.h>



//////////////////////////////////////////////////////////////////////////////
//
// Vec3d class
//
//////////////////////////////////////////////////////////////////////////////

// amount squared to figure if two doubles are equal
// (used for Vec2d and Vec3d right now)
#define DELTA_DBL 1e-12
//
// constructor that creates vector from intersection of three planes
//

#define DET3(m) ((                      \
    m[0][0] * m[1][1] * m[2][2] \
  + m[0][1] * m[1][2] * m[2][0] \
  + m[0][2] * m[1][0] * m[2][1] \
  - m[2][0] * m[1][1] * m[0][2] \
  - m[2][1] * m[1][2] * m[0][0] \
  - m[2][2] * m[1][0] * m[0][1]))

SbVec3d::SbVec3d(SbPlaned &p0, SbPlaned &p1, SbPlaned &p2)
{
    double       v[3], del, mx[3][3], mi[3][3];

    // create 3x3 matrix of normal coefficients
    mx[0][0] = p0.getNormal()[0];
    mx[0][1] = p0.getNormal()[1];
    mx[0][2] = p0.getNormal()[2];
    mx[1][0] = p1.getNormal()[0];
    mx[1][1] = p1.getNormal()[1];
    mx[1][2] = p1.getNormal()[2];
    mx[2][0] = p2.getNormal()[0];
    mx[2][1] = p2.getNormal()[1];
    mx[2][2] = p2.getNormal()[2];

    // find determinant of matrix to use for divisor
    del = DET3(mx);

//    printf("mx = %10.5f %10.5f %10.5f\n", mx[0][0], mx[0][1], mx[0][2]);
//    printf("     %10.5f %10.5f %10.5f\n", mx[1][0], mx[1][1], mx[1][2]);
//    printf("     %10.5f %10.5f %10.5f\n", mx[2][0], mx[2][1], mx[2][2]);
    if(del > -DELTA_DBL && del < DELTA_DBL) {   // if singular, just set to the origin
        vec[0] = 0;
        vec[1] = 0;
        vec[2] = 0;
    }
    else {
        v[0] = p0.getDistanceFromOrigin();
        v[1] = p1.getDistanceFromOrigin();
        v[2] = p2.getDistanceFromOrigin();

//      printf("v = %10.5f\n    %10.5f\n    %10.5f\n", v[0], v[1], v[2]);

        mi[0][0] = v[0]; mi[0][1] = mx[0][1]; mi[0][2] = mx[0][2];
        mi[1][0] = v[1]; mi[1][1] = mx[1][1]; mi[1][2] = mx[1][2];
        mi[2][0] = v[2]; mi[2][1] = mx[2][1]; mi[2][2] = mx[2][2];

//      printf("mi = %10.5f %10.5f %10.5f\n", mi[0][0], mi[0][1], mi[0][2]);
//      printf("     %10.5f %10.5f %10.5f\n", mi[1][0], mi[1][1], mi[1][2]);
//      printf("     %10.5f %10.5f %10.5f\n", mi[2][0], mi[2][1], mi[2][2]);

        vec[0] = DET3(mi) / del;
        mi[0][0] = mx[0][0]; mi[0][1] = v[0]; mi[0][2] = mx[0][2];
        mi[1][0] = mx[1][0]; mi[1][1] = v[1]; mi[1][2] = mx[1][2];
        mi[2][0] = mx[2][0]; mi[2][1] = v[2]; mi[2][2] = mx[2][2];

//      printf("mi = %10.5f %10.5f %10.5f\n", mi[0][0], mi[0][1], mi[0][2]);
//      printf("     %10.5f %10.5f %10.5f\n", mi[1][0], mi[1][1], mi[1][2]);
//      printf("     %10.5f %10.5f %10.5f\n", mi[2][0], mi[2][1], mi[2][2]);

        vec[1] = DET3(mi) / del;
        mi[0][0] = mx[0][0]; mi[0][1] = mx[0][1]; mi[0][2] = v[0];
        mi[1][0] = mx[1][0]; mi[1][1] = mx[1][1]; mi[1][2] = v[1];
        mi[2][0] = mx[2][0]; mi[2][1] = mx[2][1]; mi[2][2] = v[2];

//      printf("mi = %10.5f %10.5f %10.5f\n", mi[0][0], mi[0][1], mi[0][2]);
//      printf("     %10.5f %10.5f %10.5f\n", mi[1][0], mi[1][1], mi[1][2]);
//      printf("     %10.5f %10.5f %10.5f\n", mi[2][0], mi[2][1], mi[2][2]);

        vec[2] = DET3(mi) / del;
    }

//    printf("%10.5f %10.5f %10.5f\n", vec[0], vec[1], vec[2]);
}

//
// Returns right-handed cross product of vector and another vector
//

SbVec3d
SbVec3d::cross(const SbVec3d &v) const
{
    return SbVec3d(vec[1] * v.vec[2] - vec[2] * v.vec[1],
                   vec[2] * v.vec[0] - vec[0] * v.vec[2],
                   vec[0] * v.vec[1] - vec[1] * v.vec[0]);
}

//
// Returns dot (inner) product of vector and another vector
//

double
SbVec3d::dot(const SbVec3d &v) const
{
    return (vec[0] * v.vec[0] +
            vec[1] * v.vec[1] +
            vec[2] * v.vec[2]);
}

//
// Returns 3 individual components
//

void
SbVec3d::getValue(double &x, double &y, double &z) const
{
    x = vec[0];
    y = vec[1];
    z = vec[2];
}

//
// Returns geometric length of vector
//

double
SbVec3d::length() const
{
    return sqrt(vec[0] * vec[0] + vec[1] * vec[1] + vec[2] * vec[2]);
}

//
// Negates each component of vector in place
//

void
SbVec3d::negate()
{
    vec[0] = -vec[0];
    vec[1] = -vec[1];
    vec[2] = -vec[2];
}

//
// Changes vector to be unit length
//

double
SbVec3d::normalize()
{
    double len = length();

    if (len != 0.0)
        (*this) *= (1.0 / len);

    else setValue(0.0, 0.0, 0.0);

    return len;
}

SbVec3d &
SbVec3d::setValue(const SbVec3d &barycentric,
                  const SbVec3d &v0, const SbVec3d &v1, const SbVec3d &v2)
{
    *this = v0 * barycentric[0] + v1 * barycentric[1] + v2 * barycentric[2];
    return (*this);
}
    

//
// Component-wise scalar multiplication operator
//

SbVec3d &
SbVec3d::operator *=(double d)
{
    vec[0] *= d;
    vec[1] *= d;
    vec[2] *= d;

    return *this;
}

//
// Component-wise vector addition operator
//

SbVec3d &
SbVec3d::operator +=(SbVec3d v)
{
    vec[0] += v.vec[0];
    vec[1] += v.vec[1];
    vec[2] += v.vec[2];

    return *this;
}

//
// Component-wise vector subtraction operator
//

SbVec3d &
SbVec3d::operator -=(SbVec3d v)
{
    vec[0] -= v.vec[0];
    vec[1] -= v.vec[1];
    vec[2] -= v.vec[2];

    return *this;
}

//
// Nondestructive unary negation - returns a new vector
//

SbVec3d
SbVec3d::operator -() const
{
    return SbVec3d(-vec[0], -vec[1], -vec[2]);
}

//
// Component-wise binary scalar multiplication operator
//

SbVec3d
operator *(const SbVec3d &v, double d)
{
    return SbVec3d(v.vec[0] * d,
                   v.vec[1] * d,
                   v.vec[2] * d);
}

//
// Component-wise binary vector addition operator
//

SbVec3d
operator +(const SbVec3d &v1, const SbVec3d &v2)
{
    return SbVec3d(v1.vec[0] + v2.vec[0],
                   v1.vec[1] + v2.vec[1],
                   v1.vec[2] + v2.vec[2]);
}

//
// Component-wise binary vector subtraction operator
//

SbVec3d
operator -(const SbVec3d &v1, const SbVec3d &v2)
{
    return SbVec3d(v1.vec[0] - v2.vec[0],
                   v1.vec[1] - v2.vec[1],
                   v1.vec[2] - v2.vec[2]);
}

//
// Equality comparison operator. Components must match exactly.
//

bool
operator ==(const SbVec3d &v1, const SbVec3d &v2)
{
    return (v1.vec[0] == v2.vec[0] &&
            v1.vec[1] == v2.vec[1] &&
            v1.vec[2] == v2.vec[2]);
}

//
// Equality comparison operator within a tolerance.
//

bool
SbVec3d::equals(const SbVec3d v, double tolerance) const
{
    SbVec3d     diff = *this - v;

    return diff.dot(diff) <= tolerance;
}

//
// Returns principal axis that is closest (based on maximum dot
// product) to this vector.
//

SbVec3d
SbVec3d::getClosestAxis() const
{
    SbVec3d     axis(0.0, 0.0, 0.0), bestAxis;
    double      d, max = -21.234;

#define TEST_AXIS()                                                           \
    if ((d = dot(axis)) > max) {                                              \
        max = d;                                                              \
        bestAxis = axis;                                                      \
    }

    axis[0] = 1.0;      // +x axis
    TEST_AXIS();

    axis[0] = -1.0;     // -x axis
    TEST_AXIS();
    axis[0] = 0.0;

    axis[1] = 1.0;      // +y axis
    TEST_AXIS();

    axis[1] = -1.0;     // -y axis
    TEST_AXIS();
    axis[1] = 0.0;

    axis[2] = 1.0;      // +z axis
    TEST_AXIS();

    axis[2] = -1.0;     // -z axis
    TEST_AXIS();

#undef TEST_AXIS

    return bestAxis;
}

//////////////////////////////////////////////////////////////////////////////
//
// Vec2d class
//
//////////////////////////////////////////////////////////////////////////////

//
// Returns dot (inner) product of vector and another vector
//

double
SbVec2d::dot(const SbVec2d &v) const
{
    return vec[0] * v.vec[0] + vec[1] * v.vec[1];
}

//
// Returns 2 individual components
//

void
SbVec2d::getValue(double &x, double &y) const
{
    x = vec[0];
    y = vec[1];
}

//
// Returns geometric length of vector
//

double
SbVec2d::length() const
{
    return sqrt(vec[0] * vec[0] + vec[1] * vec[1]);
}

//
// Negates each component of vector in place
//

void
SbVec2d::negate()
{
    vec[0] = -vec[0];
    vec[1] = -vec[1];
}

//
// Changes vector to be unit length
//

double
SbVec2d::normalize()
{
    double len = length();

    if (len != 0.0)
        (*this) *= (1.0 / len);

    else setValue(0.0, 0.0);

    return len;
}

//
// Sets value of vector from array of 2 components
//

SbVec2d &
SbVec2d::setValue(const double v[2])     
{
    vec[0] = v[0];
    vec[1] = v[1];

    return (*this);
}

//
// Sets value of vector from 2 individual components
//

SbVec2d &
SbVec2d::setValue(double x, double y)     
{
    vec[0] = x;
    vec[1] = y;

    return (*this);
}

//
// Component-wise scalar multiplication operator
//

SbVec2d &
SbVec2d::operator *=(double d)
{
    vec[0] *= d;
    vec[1] *= d;

    return *this;
}

//
// Component-wise vector addition operator
//

SbVec2d &
SbVec2d::operator +=(const SbVec2d &u)
{
    vec[0] += u.vec[0];
    vec[1] += u.vec[1];

    return *this;
}

//
// Component-wise vector subtraction operator
//

SbVec2d &
SbVec2d::operator -=(const SbVec2d &u)
{
    vec[0] -= u.vec[0];
    vec[1] -= u.vec[1];

    return *this;
}

//
// Nondestructive unary negation - returns a new vector
//

SbVec2d
SbVec2d::operator -() const
{
    return SbVec2d(-vec[0], -vec[1]);
}


//
// Component-wise binary scalar multiplication operator
//

SbVec2d
operator *(const SbVec2d &v, double d)
{
    return SbVec2d(v.vec[0] * d, v.vec[1] * d);
}

//
// Component-wise binary vector addition operator
//

SbVec2d
operator +(const SbVec2d &v1, const SbVec2d &v2)
{
    return SbVec2d(v1.vec[0] + v2.vec[0],
                   v1.vec[1] + v2.vec[1]);
}

//
// Component-wise binary vector subtraction operator
//

SbVec2d
operator -(const SbVec2d &v1, const SbVec2d &v2)
{
    return SbVec2d(v1.vec[0] - v2.vec[0],
                   v1.vec[1] - v2.vec[1]);
}

//
// Equality comparison operator. Components must match exactly.
//

bool
operator ==(const SbVec2d &v1, const SbVec2d &v2)
{
    return (v1.vec[0] == v2.vec[0] &&
            v1.vec[1] == v2.vec[1]);
}

//
// Equality comparison operator within a tolerance.
//

bool
SbVec2d::equals(const SbVec2d v, double tolerance) const
{
    SbVec2d     diff = *this - v;

    return diff.dot(diff) <= tolerance;
}

//////////////////////////////////////////////////////////////////////////////
//
// Vec4d class
//
//////////////////////////////////////////////////////////////////////////////

//
// Returns dot (inner) product of vector and another vector
//

double
SbVec4d::dot(const SbVec4d &v) const
{
    return vec[0] * v.vec[0] + vec[1] * v.vec[1] + 
           vec[2] * v.vec[2] + vec[3] * v.vec[3] ;
}

//
// Returns 4 individual components
//

void
SbVec4d::getValue(double &x, double &y, double &z, double &w) const
{
    x = vec[0];
    y = vec[1];
    z = vec[2];
    w = vec[3];
}


//
// Returns geometric length of vector
//

double
SbVec4d::length() const
{
    return sqrt(vec[0] * vec[0] + vec[1] * vec[1]
              + vec[2] * vec[2] + vec[3] * vec[3]);
}

//
// Negates each component of vector in place
//

void
SbVec4d::negate()
{
    vec[0] = -vec[0];
    vec[1] = -vec[1];
    vec[2] = -vec[2];
    vec[3] = -vec[3];
}

//
// Changes vector to be unit length
//

double
SbVec4d::normalize()
{
    double len = length();

    if (len != 0.0)
        (*this) *= (1.0 / len);

    else setValue(0.0, 0.0, 0.0, 0.0);

    return len;
}

//
// Sets value of vector from array of 4 components
//

SbVec4d &
SbVec4d::setValue(const double v[4])     
{
    vec[0] = v[0];
    vec[1] = v[1];
    vec[2] = v[2];
    vec[3] = v[3];

    return (*this);
}

//
// Sets value of vector from 4 individual components
//

SbVec4d &
SbVec4d::setValue(double x, double y, double z, double w)   
{
    vec[0] = x;
    vec[1] = y;
    vec[2] = z;
    vec[3] = w;

    return (*this);
}

//
// Returns the real portion of the vector by dividing the first three
// values by the fourth.
//

void
SbVec4d::getReal(SbVec3d &v ) const
{
    v[0] = vec[0]/vec[3];
    v[1] = vec[1]/vec[3];
    v[2] = vec[2]/vec[3];
}

//
// Component-wise scalar multiplication operator
//

SbVec4d &
SbVec4d::operator *=(double d)
{
    vec[0] *= d;
    vec[1] *= d;
    vec[2] *= d;
    vec[3] *= d;

    return *this;
}

//
// Component-wise vector addition operator
//

SbVec4d &
SbVec4d::operator +=(const SbVec4d &u)
{
    vec[0] += u.vec[0];
    vec[1] += u.vec[1];
    vec[2] += u.vec[2];
    vec[3] += u.vec[3];

    return *this;
}

//
// Component-wise vector subtraction operator
//

SbVec4d &
SbVec4d::operator -=(const SbVec4d &u)
{
    vec[0] -= u.vec[0];
    vec[1] -= u.vec[1];
    vec[2] -= u.vec[2];
    vec[3] -= u.vec[3];

    return *this;
}

//
// Nondestructive unary negation - returns a new vector
//

SbVec4d
SbVec4d::operator -() const
{
    return SbVec4d(-vec[0], -vec[1], -vec[2], -vec[3]);
}


//
// Component-wise binary scalar multiplication operator
//

SbVec4d
operator *(const SbVec4d &v, double d)
{
    return SbVec4d(v.vec[0] * d, v.vec[1] * d, v.vec[2] * d, v.vec[3] * d);
}

//
// Component-wise binary vector addition operator
//

SbVec4d
operator +(const SbVec4d &v1, const SbVec4d &v2)
{
    return SbVec4d(v1.vec[0] + v2.vec[0],
                   v1.vec[1] + v2.vec[1],
                   v1.vec[2] + v2.vec[2],
                   v1.vec[3] + v2.vec[3]);
}

//
// Component-wise binary vector subtraction operator
//

SbVec4d
operator -(const SbVec4d &v1, const SbVec4d &v2)
{
    return SbVec4d(v1.vec[0] - v2.vec[0],
                   v1.vec[1] - v2.vec[1],
                   v1.vec[2] - v2.vec[2],
                   v1.vec[3] - v2.vec[3]);
}

//
// Equality comparison operator. Components must match exactly.
//

bool
operator ==(const SbVec4d &v1, const SbVec4d &v2)
{
    return (v1.vec[0] == v2.vec[0] &&
            v1.vec[1] == v2.vec[1] &&
            v1.vec[2] == v2.vec[2] &&
            v1.vec[3] == v2.vec[3]);
}

//
// Equality comparison operator within a tolerance.
//

bool
SbVec4d::equals(const SbVec4d v, double tolerance) const
{
    SbVec4d     diff = *this - v;

    return diff.dot(diff) <= tolerance;
}
