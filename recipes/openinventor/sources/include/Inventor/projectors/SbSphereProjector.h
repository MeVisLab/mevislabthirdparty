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
 |      This file contains the definition of the SbSphereProjector
 |      class. This is an abstract base class for projectors
 |      that somehow use a sphere in their projection.
 |        
 |   Author(s)          : Howard Look
 |
 ______________  S I L I C O N   G R A P H I C S   I N C .  ____________
 _______________________________________________________________________
 */

#ifndef _SB_SPHERE_PROJECTOR_
#define _SB_SPHERE_PROJECTOR_

#include <Inventor/projectors/SbProjector.h>

////////////////////////////////////////////////////////////////////////////////
//! Sphere projector.
/*!
\class SbSphereProjector
\ingroup Projectors
SbSphereProjector 
is an abstract base class for projectors that use a sphere in
their projection.
Sphere projectors are typically used to write
interactive 3D manipulators and viewers.

\par See Also
\par
SbCylinderProjector, SbCylinderPlaneProjector, SbCylinderSectionProjector, SbCylinderSheetProjector, SbLineProjector, SbPlaneProjector, SbSpherePlaneProjector, SbSphereSectionProjector, SbSphereSheetProjector
*/
////////////////////////////////////////////////////////////////////////////////

class INVENTOR_API SbSphereProjector : public SbProjector
{
  public:
    //! Apply the projector using the given point, returning the
    //! point in three dimensions that it projects to.
    //! The point should be normalized from 0-1, with (0,0) at the lower-left.
    virtual SbVec3f     project(const SbVec2f &point) = 0;

    //! Apply the projector using the given point, returning the
    //! point in three dimensions that it projects to.
    //! This also returns in \b rot  a rotation on the surface of the sphere
    //! from the last projected point to this one.
    //! The passed \b point  should be normalized (i.e. lie in the range [0.0,1.0]),
    //! with (0,0) at the lower-left.
    SbVec3f             projectAndGetRotation(const SbVec2f &point,
                                              SbRotation &rot);

    //! Get a rotation given two points on this sphere projector.
    //! The rotation will be on the surface of the sphere.
    virtual SbRotation  getRotation(const SbVec3f &point1,
                                    const SbVec3f &point2) = 0;

    //! Set and get the sphere on which to project points.
    //! The default sphere has radius 1.0.
    void                setSphere(const SbSphere &sph);

    //! Set and get the sphere on which to project points.
    //! The default sphere has radius 1.0.
    const SbSphere &    getSphere() const                 { return sphere; }

    //! Set and get whether the projector should always be oriented towards the eye.
    //! Set to FALSE if the tolerance should be evaluated in working space.
    void                setOrientToEye(bool orientToEye);
    //! Set and get whether the projector should always be oriented towards the eye.
    //! Set to FALSE if the tolerance should be evaluated in working space.
    bool                isOrientToEye() const           { return orientToEye; }

    //! Set whether the projector should intersect the half of the
    //! sphere that faces the eye.
    //! Set to FALSE if the projector should intersect with the rear half.
    void                setFront(bool inFront);
    //! Get whether the projector should intersect the half of the
    //! sphere that faces the eye.
    bool                isFront()       const   { return intersectFront; }
    //! Get whether the projector should intersect the half of the
    //! sphere that faces the eye.
    bool                isPointInFront( const SbVec3f &point ) const;

    //! Set the transform space to work in.
    virtual void            setWorkingSpace(const SbMatrix &space);

    //! Destructor
    ~SbSphereProjector(){};
    
  protected:
    //! Constructors
    //! The default sphere to use has a radius of 1.0 and is centered at (0,0,0).
    SbSphereProjector(bool orientToEye);
    SbSphereProjector(const SbSphere &s, bool orientToEye);

    //! Are intersections done on the front half (if not, they're done on
    //! the back half) of the sphere?
    bool        intersectFront;

    SbSphere    sphere;                 //!< The sphere being used.
    bool        orientToEye;            //!< TRUE if always oriented to eye.
    bool        needSetup;              //!< Set TRUE whenever sphere, work space
                                        //! or orientation changes.

    //! cached last point on this projector
    SbVec3f     lastPoint;
};

#endif /* _SB_SPHERE_PROJECTOR_ */
