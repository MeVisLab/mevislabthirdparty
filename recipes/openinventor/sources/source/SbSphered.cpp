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
 |      SbSphered
 |
 |   Author(s)          : originally by Nick Thompson, David Mott
 |                        adapted for double values by Wolf Spindler
 |
 ______________  S I L I C O N   G R A P H I C S   I N C .  ____________
 _______________________________________________________________________
 */

#include <Inventor/SbLineard.h>
#include <Inventor/SbBoxd.h>

//////////////////////////////////////////////////////////////////////////////
//
// Sphere class with double values
//
//////////////////////////////////////////////////////////////////////////////

// construct a sphere given a center and radius
SbSphered::SbSphered(const SbVec3d &c, double r)
{
    center = c;
    radius = r;
}

// Change the center and radius
void
SbSphered::setValue(const SbVec3d &c, double r)
{
    center = c;
    radius = r;
}

//////////////////////////////////////////////////////////////////////////////
//
// Change just the center
//

void
SbSphered::setCenter(const SbVec3d &c)
//
//////////////////////////////////////////////////////////////////////////////
{
    center = c;
}

//////////////////////////////////////////////////////////////////////////////
//
// Change just the radius
//

void
SbSphered::setRadius(double r)
//
//////////////////////////////////////////////////////////////////////////////
{
    radius = r;
}

//////////////////////////////////////////////////////////////////////////////
//
// Return a sphere containing a given box
//

void
SbSphered::circumscribe(const SbBox3d &box)
//
//////////////////////////////////////////////////////////////////////////////
{
    center = 0.5 * (box.getMin() + box.getMax());
    radius = (box.getMax() - center).length();
}

//////////////////////////////////////////////////////////////////////////////
//
// Sphere line intersection - this sets the parameter intersection,
// and returns TRUE if the line and sphere really do intersect.
//
// line-sphere intersection algorithm lifted from Eric Haines chapter in 
// Glassner's "Introduction to Ray Tracing", pp. 35-7
//
bool
SbSphered::intersect(const SbLined &l, SbVec3d &intersection) const
//
//////////////////////////////////////////////////////////////////////////////
{
    double  B,C;        // At^2 + Bt + C = 0, but A is 1 since we normalize Rd
    double  discr;      // discriminant (B^2 - 4AC)
    SbVec3d v;
    double  t,sqroot;
    bool    doesIntersect = TRUE;

    // setup B,C
    v = l.getPosition() - center;
    B = 2.0 * (l.getDirection().dot(v));
    C = v.dot(v) - (radius * radius);

    // compute discriminant
    // if negative, there is no intersection
    discr = B*B - 4.0*C;
    if (discr < 0.0) {
        // line and sphere do not intersect
        doesIntersect = FALSE;
    }
    else {
        // compute t0: (-B - sqrt(B^2 - 4AC)) / 2A  (A = 1)
        sqroot = sqrt(discr);
        t = (-B - sqroot) * 0.5;
        if (t < 0.0) {
            // no intersection, try t1: (-B + sqrt(B^2 - 4AC)) / 2A  (A = 1)
            t = (-B + sqroot) * 0.5;
        }

        if (t < 0.0) {
            // line and sphere do not intersect
            doesIntersect = FALSE;
        }
        else {
            // intersection! point is (point + (dir * t))
            intersection = l.getPosition() + (l.getDirection() * t);
        }
    }

    return doesIntersect;
}

//////////////////////////////////////////////////////////////////////////////
//
// Sphere line intersection - this sets the parameter intersection,
// and returns TRUE if the line and sphere really do intersect.
//
// line-sphere intersection algorithm lifted from Eric Haines chapter in 
// Glassner's "Introduction to Ray Tracing", pp. 35-7
//
bool
SbSphered::intersect(const SbLined &l, SbVec3d &enter, SbVec3d &exit) const
//
//////////////////////////////////////////////////////////////////////////////
{
    double  B,C;        // At^2 + Bt + C = 0, but A is 1 since we normalize Rd
    double  discr;      // discriminant (B^2 - 4AC)
    SbVec3d v;
    double  sqroot;
    bool    doesIntersect = TRUE;

    // setup B,C
    v = l.getPosition() - center;
    B = 2.0 * (l.getDirection().dot(v));
    C = v.dot(v) - (radius * radius);

    // compute discriminant
    // if negative, there is no intersection
    discr = B*B - 4.0*C;

    if (discr < 0.0) {
        // line and sphere do not intersect
        doesIntersect = FALSE;
    }
    else {
        sqroot = sqrt(discr);
            
        double t0 = (-B - sqroot) * 0.5;
        enter = l.getPosition() + (l.getDirection() * t0);
        
        double t1 = (-B + sqroot) * 0.5;
        exit = l.getPosition() + (l.getDirection() * t1);
    }

    return doesIntersect;
}
