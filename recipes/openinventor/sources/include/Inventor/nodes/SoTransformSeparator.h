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
 |      This file defines the SoTransformSeparator node class.
 |
 |   Author(s)          : Paul S. Strauss, Nick Thompson
 |
 ______________  S I L I C O N   G R A P H I C S   I N C .  ____________
 _______________________________________________________________________
 */

#ifndef  _SO_TRANSFORM_SEPARATOR_
#define  _SO_TRANSFORM_SEPARATOR_

#include <Inventor/nodes/SoGroup.h>


////////////////////////////////////////////////////////////////////////////////
//! Group node that saves and restores transformation state.
/*!
\class SoTransformSeparator
\ingroup Nodes
This group node is similar to the SoSeparator node in that it
saves state before traversing its children and restores it afterwards.
However, it saves only the current transformation; all other state is
left as is. This node can be useful for positioning a camera, since
the transformations to the camera will not affect the rest of the
scene, even through the camera will view the scene. Similarly, this
node can be used to isolate transformations to light sources or other
objects.

\par File Format/Default
\par
\code
TransformSeparator {
}
\endcode

\par Action Behavior
\par
SoGLRenderAction, SoCallbackAction, SoGetBoundingBoxAction, SoGetMatrixAction, SoRayPickAction
<BR> Saves the current transformation state, traverses all children, and restores the previous transformation state. 

\par See Also
\par
SoResetTransform, SoTransformation
*/
////////////////////////////////////////////////////////////////////////////////

class INVENTOR_API SoTransformSeparator : public SoGroup {

    SO_NODE_HEADER(SoTransformSeparator);

  public:

    //! Creates a transform separator node with default settings.
    SoTransformSeparator();

    //! Constructor that takes approximate number of children.
    SoTransformSeparator(int nChildren);

  SoEXTENDER public:
    //! Implement actions
    virtual void        doAction(SoAction *action);
    virtual void        callback(SoCallbackAction *action);
    virtual void        GLRender(SoGLRenderAction *action);
    virtual void        pick(SoPickAction *action);
    virtual void        getBoundingBox(SoGetBoundingBoxAction *action);
    virtual void        getMatrix(SoGetMatrixAction *action);

  SoINTERNAL public:
    static void         initClass();

  protected:
    virtual ~SoTransformSeparator();
};

#endif /* _SO_TRANSFORM_SEPARATOR_ */
