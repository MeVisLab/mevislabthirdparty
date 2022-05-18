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
 |   Description:
 |      This file defines the SoLOD node class.
 |
 |   Author(s)          : Gavin Bell
 |
 ______________  S I L I C O N   G R A P H I C S   I N C .  ____________
 _______________________________________________________________________
 */

#ifndef  _SO_LOD_
#define  _SO_LOD_

#include <Inventor/fields/SoMFFloat.h>
#include <Inventor/fields/SoSFVec3f.h>
#include <Inventor/nodes/SoGroup.h>


////////////////////////////////////////////////////////////////////////////////
//! Distance-based level-of-detail  switching group node.
/*!
\class SoLOD
\ingroup Nodes
This group node is used to allow applications to switch between
various representations of objects automatically. The children of this
node typically represent the same object or objects at varying levels
of detail, from highest detail to lowest. 
The distance from the world-space
eye point to the transformed center of the LOD is computed, and one
child is drawn, based on the values in the ranges field.


More precisely, if the distance from the world-space eyepoint to the
transformed center is D and the ranges array contains LAST_RANGE+1
values (numbered 0...LAST_RANGE), then:


\code
    if D < ranges[0]                    : Child 0 is drawn
    else if ranges[i-1] < D < ranges[i] : Child i is drawn
    else if D > ranges[LAST_RANGE]      : Child LAST_RANGE+1 is drawn
\endcode


Thus, N ranges and N+1 children should be specified.  If you specify
too few children, the last child will be used for the extra
ranges.  If you specify too few ranges, the extra children will
never be used.


It is often useful to define the lowest detail child to be an SoInfo
node.  This causes the object to completely disappear if it is far enough
away from the eyepoint.  Defining the highest detail child to be an
SoInfo node can also be useful if you want the object to disappear if
it gets too close to the eyepoint.

\par File Format/Default
\par
\code
LOD {
  center 0 0 0
  range [  ]
}
\endcode

\par Action Behavior
\par
SoGLRenderAction, SoRayPickAction, SoCallbackAction
<BR> Only the child with the appropriate level of detail is traversed. 
\par
others
<BR> All implemented as for SoGroup. 

\par See Also
\par
SoSwitch, SoGroup
*/
////////////////////////////////////////////////////////////////////////////////

class INVENTOR_API SoLOD : public SoGroup {

    SO_NODE_HEADER(SoLOD);

  public:
    //! \name Fields
    //@{

    //! World-space distances to use as switching criteria.
    SoMFFloat           range;  

    //! Object-space center of the model.
    SoSFVec3f           center; 

    //@}

    //! Creates a distance-based level-of-detail node with default settings.
    SoLOD();

    //! Creates a distance-based level-of-detail node with default settings.
    SoLOD(int nChildren);

  SoEXTENDER public:
    //! Implement actions:
    virtual void        doAction(SoAction *action);
    virtual void        callback(SoCallbackAction *action);
    virtual void        GLRender(SoGLRenderAction *action);
    virtual void        rayPick(SoRayPickAction *action);
    virtual void        getBoundingBox(SoGetBoundingBoxAction *action);

    //! These methods make render traversal faster by implementing
    //! different rendering paths corresponding to different action
    //! path codes.
    virtual void        GLRenderBelowPath(SoGLRenderAction *action);
    virtual void        GLRenderInPath(SoGLRenderAction *action);
    virtual void        GLRenderOffPath(SoGLRenderAction *action);

  SoINTERNAL public:
    static void         initClass();

  protected:
    virtual ~SoLOD();

    virtual int         whichToTraverse(SoAction *);
};

#endif /* _SO_LOD_ */
