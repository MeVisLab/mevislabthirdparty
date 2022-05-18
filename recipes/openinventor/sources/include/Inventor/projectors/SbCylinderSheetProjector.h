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
 * Copyright (C) 1990,91,92   Silicon Graphics, Inc.
 *
 _______________________________________________________________________
 ______________  S I L I C O N   G R A P H I C S   I N C .  ____________
 |
 |   $Revision: 1.1.1.1 $
 |
 |   Description:
 |      This file contains the definition of the SbCylinderSheetProjector
 |      class. This projector projects the mouse position onto the 
 |      surface of a cylinder with a hyperbolic sheet draped over it.
 |      This allows smooth transitions onto and off of the cylinder.
 |
 |   Author(s)          : Howard Look, Paul Isaacs
 |
 ______________  S I L I C O N   G R A P H I C S   I N C .  ____________
 _______________________________________________________________________
 */

#ifndef _SB_CYLINDER_SHEET_PROJECTOR_
#define _SB_CYLINDER_SHEET_PROJECTOR_

#include <Inventor/projectors/SbCylinderProjector.h>

////////////////////////////////////////////////////////////////////////////////
//! Cylinder-sheet projector.
/*!
\class SbCylinderSheetProjector
\ingroup Projectors
SbCylinderSheetProjector 
projects a window space point (usually based on the mouse location)
onto the surface of a cylinder with a hyperbolic sheet draped over it.
This allows smooth transitions onto and off of the cylinder.
Two projected points can produce a rotation
along the cylinder's axis.
When the mouse position projects on to the sheet, the
rotations will be as if the sheet is being dragged,
causing the cylinder to roll beneath it.


Incremental changes (delta rotation) can be computed during
interactive sessions. Cylinder projectors are typically used to write
interactive 3D manipulators and viewers.

\par See Also
\par
SbCylinderSectionProjector, SbCylinderPlaneProjector, SbLineProjector, SbPlaneProjector, SbSpherePlaneProjector, SbSphereProjector, SbSphereSectionProjector, SbSphereSheetProjector
*/
////////////////////////////////////////////////////////////////////////////////

class INVENTOR_API SbCylinderSheetProjector : public SbCylinderProjector
{
  public:

    //! \see SbCylinderSheetProjector(const  SbCylinder &cyl,bool orientToEye)
    SbCylinderSheetProjector(bool orientToEye = TRUE);

    //! Constructors. The first uses a default cylinder aligned with the Y axis
    //! with radius 1.0; the cylinder is supplied in the second.
    //! The \b orientToEye 
    //! parameter determines whether the sheet is perpendicular to the
    //! eye, or perpendicular to the cylinder's Z axis.  Setting that parameter to TRUE
    //! (the default) specifies that the plane be perpendicular to the
    //! eye, which is most often the desired behavior.
    //! 
    //! 
    //! The default view volume is undefined, and the working space is identity.
    SbCylinderSheetProjector(const  SbCylinder &cyl,
                             bool orientToEye = TRUE);

    //! Destructor.
    ~SbCylinderSheetProjector() {}
    
    //! Returns an instance that is a copy of this instance. The caller
    //! is responsible for deleting the copy when done.
    virtual SbProjector *    copy() const;

    //! Apply the projector using the given point, returning the
    //! point in three dimensions that it projects to.
    //! The point should be normalized from 0-1, with (0,0) at
    //! the lower-left.
    virtual SbVec3f     project(const SbVec2f &point);

    //! Computes a rotation based on two points on this projector.
    virtual SbRotation  getRotation(const SbVec3f &point1,
                                    const SbVec3f &point2);

  protected:
    //! Sets up the tolerance plane.
    virtual void        setupPlane();

    //! The projection point in working space.
    SbVec3f             workingProjPoint;
    
    //! Information about the plane used for intersection testing.
    SbVec3f     planeDir;               //!< normal direction
    SbPlane     tolPlane;               //!< the plane itself
};

#endif /* _SB_CYLINDER_SHEET_PROJECTOR_ */
