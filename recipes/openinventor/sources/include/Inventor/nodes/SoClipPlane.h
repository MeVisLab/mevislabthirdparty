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
 |      This file defines the SoClipPlane node class.
 |
 |   Author(s)          : Paul S. Strauss
 |
 ______________  S I L I C O N   G R A P H I C S   I N C .  ____________
 _______________________________________________________________________
 */

#ifndef  _SO_CLIP_PLANE_
#define  _SO_CLIP_PLANE_

#include <Inventor/fields/SoSFBool.h>
#include <Inventor/fields/SoSFPlane.h>
#include <Inventor/nodes/SoSubNode.h>


////////////////////////////////////////////////////////////////////////////////
//! Clipping plane node.
/*!
\class SoClipPlane
\ingroup Nodes
This node clips all subsequent shapes in the scene graph to the
half-space defined by the plane field. The half-space is the side
of the plane in the direction of the plane normal. 
For example, if the plane is positioned at the origin 
and the normal is pointing down the positive X axis,
everything in the negative X space will be clipped away.


Any number of
clipping planes may be active simultaneously, although the graphics
library may place a limit on this number during rendering.

\par File Format/Default
\par
\code
ClipPlane {
  plane 1 0 0 0
  on TRUE
}
\endcode

\par Action Behavior
\par
SoGLRenderAction, SoCallbackAction, SoRayPickAction
<BR> Adds the plane to the current list of clipping planes in the state. 

\par See Also
\par
SoCamera, SoShapeHints
*/
////////////////////////////////////////////////////////////////////////////////

class INVENTOR_API SoClipPlane : public SoNode {

    SO_NODE_HEADER(SoClipPlane);

  public:
    //! \name Fields
    //@{

    //! Plane defining half-space.
    SoSFPlane           plane;          

    //! Whether clipping plane is active.
    SoSFBool            on;             

    //@}

    //! Creates a clip plane node with default settings.
    SoClipPlane();

  SoEXTENDER public:
    virtual void        doAction(SoAction *action);
    virtual void        GLRender(SoGLRenderAction *action);
    virtual void        callback(SoCallbackAction *action);
    virtual void        pick(SoPickAction *action);

  SoINTERNAL public:
    static void         initClass();

  protected:
    virtual ~SoClipPlane();
};

#endif /* _SO_CLIP_PLANE_ */
