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
 |      Thie file defines the SbSpherePlaneProjector class. This
 |      projector projects the mouse position onto a sphere with
 |      a plane cutting through it.
 |
 |      When the mouse position projects on to the plane, the
 |      rotations will be as if the plane is being dragged,
 |      causing the sphere to rotate beneath it.
 |
 |   Author(s)          : Howard Look, Paul Isaacs
 |
 ______________  S I L I C O N   G R A P H I C S   I N C .  ____________
 _______________________________________________________________________
 */

#ifndef _SB_SPHERE_PLANE_PROJECTOR_
#define _SB_SPHERE_PLANE_PROJECTOR_

#include <Inventor/system/SbSystem.h>
#include <Inventor/projectors/SbSphereSectionProjector.h>

////////////////////////////////////////////////////////////////////////////////
//! Sphere-plane projector.
/*!
\class SbSpherePlaneProjector
\ingroup Projectors
SbSpherePlaneProjector 
projects a window space point (usually based on the mouse location)
onto a surface defined by a sphere and plane cutting through the sphere.
Two projected points can produce a rotation
about the sphere's center.
When the mouse position projects onto the plane, the
rotations will be as if the plane is being dragged,
causing the sphere to roll beneath it.


Incremental changes (delta rotation) can be computed during
interactive sessions. Sphere projectors are typically used to write
interactive 3D manipulators and viewers.

\par See Also
\par
SbCylinderProjector, SbCylinderPlaneProjector, SbCylinderSectionProjector, SbCylinderSheetProjector, SbLineProjector, SbPlaneProjector, SbSphereSheetProjector
*/
////////////////////////////////////////////////////////////////////////////////

class INVENTOR_API SbSpherePlaneProjector : public SbSphereSectionProjector
{
  public:
    //! Default constructor.
    //! The default view volume is undefined.
    //! The default working space is identity (world space).
    //! The default sphere to use has a radius of 1.0 and is centered at (0,0,0).
    //! The default edge tolerance is .9.
    //! The default eye orientation is TRUE.
    SbSpherePlaneProjector(float edgeTol = 0.9, bool orientToEye = TRUE);

    //! Constructor taking the sphere.
    SbSpherePlaneProjector( const  SbSphere &sph,
                            float  edgeTol = 0.9,
                            bool orientToEye = TRUE);

    //! Destructor.
    ~SbSpherePlaneProjector() {}
    
    //! Returns an instance that is a copy of this instance. The caller
    //! is responsible for deleting the copy when done.
    virtual SbProjector *    copy() const;

    //! Apply the projector using the given point, returning the
    //! point in three dimensions that it projects to.
    //! The point should be normalized from 0-1, with (0,0) at the lower-left.
    virtual SbVec3f     project(const SbVec2f &point);

    //! Computes a rotation based on two points on this projector.
    virtual SbRotation  getRotation(const SbVec3f &point1,
                                    const SbVec3f &point2);
                            
  protected:
    SbRotation          getRotation(const SbVec3f &point1, bool tol1, 
                                    const SbVec3f &point2, bool tol2);
};

#endif /* _SB_SPHERE_PLANE_PROJECTOR_ */
