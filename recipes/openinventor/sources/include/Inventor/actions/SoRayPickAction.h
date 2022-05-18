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
 |      Defines the SoRayPickAction class
 |
 |   Author(s)          : Paul S. Strauss, Nick Thompson
 |
 ______________  S I L I C O N   G R A P H I C S   I N C .  ____________
 _______________________________________________________________________
 */

#ifndef  _SO_RAY_PICK_ACTION_
#define  _SO_RAY_PICK_ACTION_

#include <Inventor/system/SbSystem.h>
#include <Inventor/SoLists.h>
#include <Inventor/actions/SoPickAction.h>


////////////////////////////////////////////////////////////////////////////////
//! Intersects objects with a ray cast into scene.
/*!
\class SoRayPickAction
\ingroup Actions
This class performs picking by casting a ray into a scene and
performing intersection tests with each object. The ray is extended to
be a cone or cylinder, depending on the camera type, for intersection
with points and lines. Each intersection is returned as an
SoPickedPoint instance.


The picking ray can be specified as either a ray from the camera
location through a particular viewport pixel, or as a world-space ray.
In the former case, a valid camera must be encountered during
traversal of the graph to determine the location of the ray in world
space.


Callers can cause the action to compute all intersections along the
ray (sorted closest to farthest) by setting the \b pickAll  flag to 
TRUE. By default, the action computes only the closest intersection.
In either case, the
intersections are returned in an SoPickedPointList. Each
intersection can be examined by accessing the appropriate
SoPickedPoint in the list. The SoPickedPoint class provides
methods to get the intersection point, normal, and other info.

\par See Also
\par
SoPickedPoint, SoPickedPointList
*/
////////////////////////////////////////////////////////////////////////////////

class INVENTOR_API SoRayPickAction : public SoPickAction {

    SO_ACTION_HEADER(SoRayPickAction);

  public:

    //! Constructor takes viewport region to use for picking. Even though
    //! the picking operation may not involve a window per se, some nodes need
    //! this information to determine their size and placement.
    SoRayPickAction(const SbViewportRegion &viewportRegion);

    //! Destructor
    virtual ~SoRayPickAction();

    ///////////////////////////////////////////////////////////////////
    ///
    ///  Setting up the action before it is applied:
    ///

    //! Sets the viewport-space point through which the ray passes, starting
    //! at the camera's viewpoint. Viewport coordinates range from (0,0) at
    //! the lower left to (width-1,height-1) at the upper right.
    void                setPoint(const SbVec2s &viewportPoint);

    //! Sets the viewport point in normalized coordinates, which range
    //! from (0,0) at the lower left to (1,1) at the upper right.
    void                setNormalizedPoint(const SbVec2f &normPoint);

    //! Set the radius (in pixels) around the point. This is used when testing
    //! the ray against lines and points. By default, the radius is 5 pixels.
    //! For perspective cameras, the ray is extended to be a cone when testing
    //! against lines and points. For orthographic cameras, the ray is
    //! extended to be a cylinder. The radius has no effect for shapes of
    //! other types.
    void                setRadius(float radiusInPixels);

    //! Sets a world-space ray along which to pick. The ray is defined as a
    //! world space starting point and direction vector. The direction vector
    //! will be normalized automatically. The last two arguments are the
    //! parametric distances between which intersections along the ray must
    //! occur. The distances are measured as if the direction vector is unit
    //! length; e.g., if \p nearDistance is 2.0, the intersection must occur
    //! past (\p start + 2*(length of the direction vector)) units along the 
    //! ray. These distances can be used to achieve near and far plane clipping. 
    //! A negative distance (such as the default values) means disable clipping 
    //! to that plane.
    void                setRay(const SbVec3f &start, const SbVec3f &direction,
                               float nearDistance = -1.0,
                               float farDistance = -1.0);

    //! Sets/returns whether the action will return all objects intersected or
    //! just the closest one.
    void                setPickAll(bool flag)         { pickAll = flag; }
    //! Sets/returns whether the action will return all objects intersected or
    //! just the closest one.
    bool                isPickAll() const               { return pickAll;     }

    ///////////////////////////////////////////////////////////////////
    ///
    ///  Examining results after the action is applied:
    ///

    //! Returns list of picked points.
    const SoPickedPointList &getPickedPointList() const  { return ptList; }

    //! Returns the indexed picked point from the list.
    SoPickedPoint *     getPickedPoint(int index = 0) const;

  SoEXTENDER public:

    //! If a ray was not defined with setRay(), this causes the world
    //! space pick ray to be computed from the screen space point and
    //! radius, using the current view specification from the state.
    //! This is typically done when a camera is encountered during
    //! traversal.
    void                computeWorldSpaceRay();

    //! This returns TRUE if the action has had a world space ray set
    //! or computed
    bool                hasWorldSpaceRay() const;

    //! This is called by shapes to set up object space picking. It
    //! uses the current state matrices to determine how to map between
    //! world and object spaces. It should be called before calling any
    //! of the intersection methods.
    //! The second form takes a matrix to concatenate with the current
    //! objToWorld matrix. It can be used, for example, if a shape has
    //! sizing or positioning info built into it.
    void                setObjectSpace();
    void                setObjectSpace(const SbMatrix &matrix);

    //! These intersect the current object-space ray with a variety of
    //! primitives: triangle, line, point, bounding-box. Intersection
    //! with a triangle uses only the ray, while intersection with a
    //! line or point uses the cone or cylinder around the ray. The
    //! intersection with a bounding-box uses the cone/cylinder also,
    //! since the contents of the box may be lines or points. NOTE: you
    //! must call setObjectSpace() before calling any of these.

    //! Triangle: returns intersection point, barycentric coordinates,
    //! and whether the front side (defined by right-hand-rule) was hit.
    bool                intersect(const SbVec3f &v0,
                                  const SbVec3f &v1,
                                  const SbVec3f &v2,
                                  SbVec3f &intersection, SbVec3f &barycentric,
                                  bool &front) const;

    //! Line:
    bool                intersect(const SbVec3f &v0, const SbVec3f &v1,
                                  SbVec3f &intersection) const;

    //! Point:
    bool                intersect(const SbVec3f &point) const;

    //! Bounding box: just return whether the ray intersects it. If
    //! useFullViewVolume is TRUE, it intersects the picking view
    //! volume with the box. Otherwise, it uses just the picking ray,
    //! which is faster.
    bool                intersect(const SbBox3f &box,
                                  bool useFullViewVolume = TRUE);

    //! Returns an SbViewVolume that represents the object-space ray to
    //! pick along. The projection point of the view volume is the
    //! starting point of the ray. The projection direction is the
    //! direction of the ray. The distance to the near plane is the
    //! same as the distance to the near plane for the ray. The
    //! distance to the far plane is the sum of the near distance and
    //! the depth of the view volume.
    const SbViewVolume &getViewVolume() const   { return objVol; }

    //! Returns SbLine that can be used for other intersection tests.
    //! The line's position is the starting point and the direction is
    //! the direction of the ray. Given an intersection with this ray,
    //! you can call isBetweenPlanes() to see if the intersection is
    //! between the near and far clipping planes.
    const SbLine &      getLine() const         { return objLine; }

    //! Returns TRUE if the given object-space intersection point is
    //! between the near and far planes of the object-space view
    //! volume, as well as any clipping planes that have been defined.
    //! This test can be used to determine whether the point of
    //! intersection of the ray with an object is valid with respect to
    //! the clipping planes.
    bool                isBetweenPlanes(const SbVec3f &intersection) const;

    //! Adds an SoPickedPoint instance representing the given object
    //! space point to the current list and returns a pointer to it. If
    //! pickAll is TRUE, this inserts the instance in correct sorted
    //! order. If it is FALSE, it replaces the one instance in the list
    //! only if the new one is closer; if the new one is farther away,
    //! no instance is created and NULL is returned, meaning that no
    //! more work has to be done to set up the SoPickedPoint.
    SoPickedPoint *     addIntersection(const SbVec3f &objectSpacePoint);

  protected:
    //! Initiates action on graph
    virtual void        beginTraversal(SoNode *node);

  SoINTERNAL public:
    static void         initClass();

  private:
    bool                lineWasSet;     //!< TRUE if a world-space line was set
    bool                rayWasComputed; //!< TRUE if ray computed by camera
    bool                pickAll;        //!< Pick all objects or just closest
    SbVec2s             VPPoint;        //!< Point in viewport coordinates
    SbVec2f             normVPPoint;    //!< Point in normalized vp coordinates
    bool                normPointSet;   //!< TRUE if setNormalizedPoint called
    float               VPRadius;       //!< Radius in viewport space pixels
    SbMatrix            objToWorld;     //!< Object-to-world space matrix
    SbMatrix            worldToObj;     //!< World-to-object space matrix
    SoPickedPointList   ptList;         //!< List of intersections

    //! The ray is defined as an SbViewVolume as in the
    //! SoPickRayElement, and is usually stored in an instance of the
    //! element. This stores the ray if it is set using setRay().
    SbViewVolume        worldVol;

    //! Users can specify negative near and far distances to indicate
    //! that picks should not be clipped to those planes. These flags
    //! store that info, since the distances in the view volume can't
    //! be negative.
    bool                clipToNear, clipToFar;

    //! These store the object-space ray info as a view volume and a
    //! line. See the comments on getViewVolume() and getLine().
    SbLine              objLine;        //!< Line representing ray
    SbViewVolume        objVol;         //!< View volume representing ray

    //! If the caller passes a matrix to setObjectSpace(), the inverse
    //! of it is stored here so the object-space angle can be computed
    //! correctly later. The extraMatrixSet flag is set to TRUE in this
    //! case.
    bool                extraMatrixSet;
    SbMatrix            extraMatrix;

    //! Computes matrices to go between object and world space
    void                computeMatrices();

    //! Computes object-space view volume and line
    void                computeObjVolAndLine();

    //! Returns TRUE if the first intersection point is closer to the
    //! starting point of the ray than the second.
    bool                isCloser(const SoPickedPoint *pp0,
                                 const SoPickedPoint *pp1);

    //! Computes distance of point along ray: start * t * direction.
    //! The point has to be on the ray for this to work
    static float        rayDistance(const SbVec3f &start,
                                    const SbVec3f &direction,
                                    const SbVec3f &point);
};

#endif /* _SO_RAY_PICK_ACTION_ */
