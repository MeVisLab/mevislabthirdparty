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
 |      Defines the SoGetBoundingBoxAction class
 |
 |   Author(s)          : Paul S. Strauss
 |
 ______________  S I L I C O N   G R A P H I C S   I N C .  ____________
 _______________________________________________________________________
 */

#ifndef  _SO_GET_BOUNDING_BOX_ACTION_
#define  _SO_GET_BOUNDING_BOX_ACTION_

#include <Inventor/system/SbSystem.h>
#include <Inventor/SbBox.h>
#include <Inventor/SbViewportRegion.h>
#include <Inventor/actions/SoSubAction.h>


////////////////////////////////////////////////////////////////////////////////
//! Computes bounding box of a scene.
/*!
\class SoGetBoundingBoxAction
\ingroup Actions
This class is used to compute a 3D bounding box enclosing objects
defined by a scene graph. The box is a rectangular prism. The action
also computes the center point, which is defined differently for
different objects.  (For example, the center of an SoFaceSet is
the average of its vertices' coordinates.) For a group, the center
point is defined as the average of the centers of all shapes in it.


Each bounding box is calculated as a SbXfBox3f, where the
transformation matrix is defined so that the bounding box can be
stored in the object space of the SoShape. When two bounding boxes
are combined by a group node, the combination is performed so as to
produce the smaller untransformed box.  The result of the calculation
by the action can be returned as an SbXfBox3f or as a
world-space-aligned SbBox3f.


To calculate the bounding box of a subgraph bounded by two paths,
specify the left edge of the subgraph with setResetPath(), and
apply the action to the path that defines the right edge of the
subgraph. The accumulated bounding box and transformation will be
reset when the tail of the reset path is traversed.


If the subgraph being traversed does not contain any shapes, the returned
bounding box will be empty (that is,
box.isEmpty()
will return TRUE).

\par See Also
\par
SbBox3f, SbXfBox3f, SoGetMatrixAction
*/
////////////////////////////////////////////////////////////////////////////////

class INVENTOR_API SoGetBoundingBoxAction : public SoAction {

    SO_ACTION_HEADER(SoGetBoundingBoxAction);

  public:

    //! Constructor takes viewport region to use for picking. Even
    //! though the bounding box computation may not involve a window
    //! per se, some nodes need this information to determine their
    //! size and placement.
    SoGetBoundingBoxAction(const SbViewportRegion &viewportRegion);

    //! Destructor
    virtual ~SoGetBoundingBoxAction();

    //! Sets/returns current viewport region to use for action.
    void                setViewportRegion(const SbViewportRegion &newRegion);

    //! Sets/returns current viewport region to use for action.
    const SbViewportRegion &getViewportRegion() const   { return vpRegion; }

    //! Returns computed bounding box in world space.
    SbBox3f             getBoundingBox() const  { return box.project(); }

    //! Returns computed bounding box before transformation into world space.
    SbXfBox3f &         getXfBoundingBox()      { return box; }

    //! Returns computed center point in world space.
    const SbVec3f &     getCenter() const;

    //! Set this flag to TRUE if you want the returned bounding box to be in
    //! the space of whatever camera is in the graph. Camera space is defined
    //! to have the viewpoint at the origin, with the direction of view along
    //! the negative z axis. This space can be used to determine distances of
    //! objects from the camera.
    void                setInCameraSpace(bool flag)   { cameraSpace = flag; }

    //! Returns camera space flag.
    bool                isInCameraSpace() const         { return cameraSpace; }

    //! set a path to do a resetTransform/resetBoundingBox on. The default
    //! is to do the reset right before the given path.
    //! Which things get reset:
    enum ResetType {
        TRANSFORM      = 0x01,      //!< Transformation
        BBOX           = 0x02,      //!< Bounding Box
        ALL            = 0x03       //!< Both Transform and Bounding Box
    };
    //! If a non-NULL path is specified, the action will reset the computed
    //! bounding box to be empty and/or the current transformation to
    //! identity. The \p resetBefore flag indicates whether to perform the
    //! reset before or after the tail node of the path is traversed.
    void                setResetPath(const SoPath *path,
                                     bool resetBefore = TRUE,
                                     ResetType what = ALL);
    //! Returns the current reset path, or NULL.
    const SoPath *      getResetPath() const    { return resetPath; }
    //! Returns TRUE if the current reset path is not NULL.
    bool                isResetPath() const     { return( resetPath != NULL); }
    //! Returns TRUE if the \p resetBefore flag was specified for the reset path.
    bool                isResetBefore() const   { return resetBefore; }
    SoGetBoundingBoxAction::ResetType getWhatReset() const { return resetWhat;}

  SoEXTENDER public:

    //! Call these methods at beginning and end (respectively) of
    //! the getBoundingBox action for each node. (SoNode calls these in
    //! its static method for this action.)
    void                checkResetBefore();
    void                checkResetAfter();

    //! Extends the current bounding box by the given bounding box,
    //! after transforming it by the current value of the
    //! SoLocalBBoxMatrixElement
    void                extendBy(const SbBox3f &box);
    void                extendBy(const SbXfBox3f &box);

    //! Sets the center of the bounding box to the given point, which,
    //! if transformCenter is TRUE, is first transformed by the current
    //! value of the SoLocalBBoxMatrixElement. After this is called,
    //! isCenterSet will return TRUE, unless resetCenter is called.
    //! Shapes should setCenter() to whatever is appropriate (e.g.
    //! left-justified text might set the center to be the start of the
    //! string) with transformCenter set to TRUE.  Groups are
    //! responsible for averaging the centers if more than one shape
    //! sets the center; when setting the center to the average of
    //! transformed centers, pass FALSE for transformCenter.
    void                setCenter(const SbVec3f &center,
                                  bool transformCenter);
    bool                isCenterSet() const;
    void                resetCenter();

  SoINTERNAL public:
    static void         initClass();

  protected:
    //! Initiates action on graph
    virtual void        beginTraversal(SoNode *node);

  private:
    SbXfBox3f           box;            //!< Bounding box
    SbVec3f             center;         //!< Center point
    bool                cameraSpace;    //!< Bounding box in camera space?
    const SoPath        *resetPath;     //!< path to reset transform
    bool                resetBefore;    //!< reset before or after?
    ResetType           resetWhat;      //!< which things get reset?
    SbViewportRegion    vpRegion;       //!< Current viewport region
    bool                centerSet;      //!< setCenter() called?

    //! check to see if the reset parameters are met, if so, do the
    //! reset transform and reset bbox
    void                checkReset(bool resetBefore);
};

#endif /* _SO_GET_BOUNDING_BOX_ACTION_ */
