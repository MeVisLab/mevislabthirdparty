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
 |      This file defines the SoLevelOfDetail node class.
 |
 |   Author(s)          : Paul S. Strauss, Nick Thompson
 |
 ______________  S I L I C O N   G R A P H I C S   I N C .  ____________
 _______________________________________________________________________
 */

#ifndef  _SO_LEVEL_OF_DETAIL_
#define  _SO_LEVEL_OF_DETAIL_

#include <Inventor/fields/SoMFFloat.h>
#include <Inventor/nodes/SoGroup.h>


////////////////////////////////////////////////////////////////////////////////
//! Level-of-detail switching group node.
/*!
\class SoLevelOfDetail
\ingroup Nodes
The children of this
node typically represent the same object or objects at varying levels
of detail, from highest detail to lowest. The size of the objects when
projected into the viewport is used to determine which version to use
(i.e., which child to traverse).


The size is computed as the area of the screen rectangle enclosing the
projection of the 3D bounding box that encloses all of the children.
When rendering, this size is compared to the values in the
\b screenArea  field. If the size is greater than the first value,
child 0 is traversed. If it is smaller than the first, but greater
than the second, child 1 is traversed, and so on. If there are fewer
children than are required by this rule, the last child is traversed.
The \b screenArea  field contains just 0 by default, so the first
child is always traversed.


The size calculation takes the current complexity into account. If the
complexity is 0 or is of type <tt>BOUNDING_BOX</tt>, the last child is
always traversed. If the complexity is less than .5, the computed size
is scaled down appropriately to use (possibly) a less detailed
representation. If the complexity is greater than .5, the size is
scaled up. At complexity 1, the first child is always used.


Note that the SoLOD node is similar to SoLevelOfDetail, except
the switching between levels in the SoLOD node is based on 
distance from the camera, which is faster than using screen area.

\par File Format/Default
\par
\code
LevelOfDetail {
  screenArea 0
}
\endcode

\par Action Behavior
\par
SoGLRenderAction, SoRayPickAction, SoCallbackAction
<BR> Only the child with the appropriate level of detail is traversed. 
\par
SoGetBoundingBoxAction
<BR> The box that encloses all children is computed. (This is the box that is needed to compute the projected size.) 
\par
others
<BR> All implemented as for SoGroup. 

\par See Also
\par
SoLOD, SoComplexity, SoSwitch, SoGroup
*/
////////////////////////////////////////////////////////////////////////////////

class INVENTOR_API SoLevelOfDetail : public SoGroup {

    SO_NODE_HEADER(SoLevelOfDetail);

  public:
    //! \name Fields
    //@{

    //! Areas to use for comparison
    SoMFFloat           screenArea;     

    //@}

    //! Creates a level-of-detail node with default settings.
    SoLevelOfDetail();

    //! Creates a level-of-detail node with default settings.
    SoLevelOfDetail(int nChildren);

  SoEXTENDER public:
    //! Implement actions:
    virtual void        doAction(SoAction *action);
    virtual void        callback(SoCallbackAction *action);
    virtual void        GLRender(SoGLRenderAction *action);
    virtual void        rayPick(SoRayPickAction *action);

  SoINTERNAL public:
    static void         initClass();

  protected:
    virtual ~SoLevelOfDetail();

  private:
    //! This action is used to compute the screen-space bbox
    static SoGetBoundingBoxAction       *bboxAction;
};

#endif /* _SO_LEVEL_OF_DETAIL_ */
