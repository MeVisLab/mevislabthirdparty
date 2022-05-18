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
 |      SbCylinder
 |
 |   Author(s)          : originally by Howard Look
 |                        adapted for double values by Wolf Spindler
 |
 ______________  S I L I C O N   G R A P H I C S   I N C .  ____________
 _______________________________________________________________________
 */

#include <Inventor/SbLineard.h>

//////////////////////////////////////////////////////////////////////////////
//
// Cylinder class with double values
//
//////////////////////////////////////////////////////////////////////////////

// construct a default cylinder
SbCylinderd::SbCylinderd()
{
    axis.setValue(SbVec3d(0.0, 0.0, 0.0), SbVec3d(0.0, 1.0, 0.0));
    radius = 1.0;
}

// construct a cylinder given an axis and radius
SbCylinderd::SbCylinderd(const SbLined &a, double r)
{
    axis = a;
    radius = r;
}

// Change the axis and radius
void
SbCylinderd::setValue(const SbLined &a, double r)
{
    axis = a;
    radius = r;
}

//////////////////////////////////////////////////////////////////////////////
//
// Change just the axis
//

void
SbCylinderd::setAxis(const SbLined &a)
//
//////////////////////////////////////////////////////////////////////////////
{
    axis = a;
}

//////////////////////////////////////////////////////////////////////////////
//
// Change just the radius
//

void
SbCylinderd::setRadius(double r)
//
//////////////////////////////////////////////////////////////////////////////
{
    radius = r;
}

////////////////////////////////////////////////////////////////////////
//
// Description:
//  Intersect given line with this cylinder, returning the
//  first intersection in result. Returns TRUE if there was an
//  intersection (and result is valid).
//
// Use: public

bool
SbCylinderd::intersect(const SbLined &line, SbVec3d &result) const
//
////////////////////////////////////////////////////////////////////////
{
    SbVec3d whoCares;
    return intersect(line, result, whoCares);
}    

////////////////////////////////////////////////////////////////////////
//
// Description:
//  Intersect given line with this cylinder, returning the
//  results in enter and exit. Returns TRUE if there was an
//  intersection (and results are valid).
//
// Use: public

bool
SbCylinderd::intersect(const SbLined &line, SbVec3d &enter, SbVec3d &exit) const
//
////////////////////////////////////////////////////////////////////////
{
    // The intersection will actually be done on a radius 1 cylinder
    // aligned with the y axis, so we transform the line into that
    // space, then intersect, then transform the results back.

    // rotation to y axis
    SbRotationd rotToYAxis(axis.getDirection(), SbVec3d(0,1,0));
    SbMatrixd   mtxToYAxis;
    mtxToYAxis.setRotate(rotToYAxis);

    // scale to unit space
    double       scaleFactor = 1.0/radius;
    SbMatrixd   toUnitCylSpace;
    toUnitCylSpace.setScale(SbVec3d(scaleFactor, scaleFactor, scaleFactor));
    toUnitCylSpace.multLeft(mtxToYAxis);

    // find the given line un-translated
    SbVec3d origin = line.getPosition();
    origin -= axis.getPosition();
    SbLined noTranslationLine(origin, origin + line.getDirection());

    // find the un-translated line in unit cylinder's space
    SbLined cylLine;
    toUnitCylSpace.multLineMatrix(noTranslationLine, cylLine);

    // find the intersection on the unit cylinder
    SbVec3d cylEnter, cylExit;
    bool intersected = unitCylinderIntersect(cylLine, cylEnter, cylExit);

    if (intersected) {
        // transform back to original space
        SbMatrixd fromUnitCylSpace = toUnitCylSpace.inverse();

        fromUnitCylSpace.multVecMatrix(cylEnter, enter);
        enter += axis.getPosition();

        fromUnitCylSpace.multVecMatrix(cylExit, exit);
        exit += axis.getPosition();
    }    

    return intersected;
}    

////////////////////////////////////////////////////////////////////////
//
// Description:
//  Intersect the line with a unit cylinder. Returns TRUE if
//  there was an intersection, and returns the intersection points
//  in enter and exit.
//
//  The cylinder has radius 1 and is aligned with the
//  y axis, such that x^2 + z^2 - 1 = 0
//
//  Taken from Pat Hanrahan's chapter in Glassner's
//  _Intro to Ray Tracing_, page 91, and some code
//  stolen from Paul Strauss.
//
// Use: private, static

bool
SbCylinderd::unitCylinderIntersect(const SbLined &l,
                                   SbVec3d &enter, SbVec3d &exit)
//
////////////////////////////////////////////////////////////////////////
{
    double              A, B, C, discr, sqroot, t0, t1;
    const SbVec3d       &pos = l.getPosition(), &dir = l.getDirection();
    bool                doesIntersect = TRUE;

    A = dir[0] * dir[0] + dir[2] * dir[2];

    B = 2.0 * (pos[0] * dir[0] + pos[2] * dir[2]);

    C = pos[0] * pos[0] + pos[2] * pos[2] - 1;

    // discriminant = B^2 - 4AC
    discr = B*B - 4.0*A*C;

    // if discriminant is negative, no intersection
    if (discr < 0.0) {
        doesIntersect = FALSE;
    }
    else {
        sqroot = double(sqrt(discr));

        // magic to stabilize the answer
        if (B > 0.0) {
            t0 = -(2.0 * C) / (sqroot + B);
            t1 = -(sqroot + B) / (2.0 * A);
        }
        else {
            t0 = (2.0 * C) / (sqroot - B);
            t1 = (sqroot - B) / (2.0 * A);
        }           

        enter = pos + (dir * t0);
        exit = pos + (dir * t1);
    }

    return doesIntersect;
}
