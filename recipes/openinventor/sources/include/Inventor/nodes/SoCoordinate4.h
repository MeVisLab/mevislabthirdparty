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
 |      This file defines the SoCoordinate4 node class.
 |
 |   Author(s)          : Paul S. Strauss
 |
 ______________  S I L I C O N   G R A P H I C S   I N C .  ____________
 _______________________________________________________________________
 */

#ifndef  _SO_COORDINATE4_
#define  _SO_COORDINATE4_

#include <Inventor/fields/SoMFVec4f.h>
#include <Inventor/nodes/SoSubNode.h>
class SoVBO;


////////////////////////////////////////////////////////////////////////////////
//! Rational coordinate point node.
/*!
\class SoCoordinate4
\ingroup Nodes
This node defines a set of 3D coordinates to be used by subsequent
vertex-based shape nodes (those derived from SoVertexShape) or
shape nodes that use them as control points (such as NURBS curves and
surfaces).  Coordinates are specifed as rational 4-vectors; the
corresponding 3D point is computed by dividing the first three
components by the fourth.  This node does not produce a visible result
during rendering; it simply replaces the current coordinates in the
rendering state for subsequent nodes to use.


This node exists primarily for use with NURBS curves and surfaces.
However, it can be used to define coordinates for any vertex-based
shape.

\par File Format/Default
\par
\code
Coordinate4 {
  point 0 0 0 1
}
\endcode

\par Action Behavior
\par
SoGLRenderAction, SoCallbackAction, SoGetBoundingBoxAction, SoRayPickAction
<BR> Sets coordinates in current traversal state. 

\par See Also
\par
SoCoordinate4, SoIndexedNurbsCurve, SoIndexedNurbsSurface, SoNurbsCurve, SoNurbsProfile, SoNurbsSurface, SoVertexShape
*/
////////////////////////////////////////////////////////////////////////////////

class INVENTOR_API SoCoordinate4 : public SoNode {

    SO_NODE_HEADER(SoCoordinate4);

  public:
    //! \name Fields
    //@{

    //! Coordinate point(s).
    SoMFVec4f           point;          

    //@}

    //! Creates a coordinate node with default settings.
    SoCoordinate4();

  SoEXTENDER public:
    virtual void        doAction(SoAction *action);
    virtual void        GLRender(SoGLRenderAction *action);
    virtual void        getBoundingBox(SoGetBoundingBoxAction *action);
    virtual void        callback(SoCallbackAction *action);
    virtual void        pick(SoPickAction *action);

  SoINTERNAL public:
    static void         initClass();

  protected:
    virtual ~SoCoordinate4();

    SoVBO* _vbo;
};

#endif /* _SO_COORDINATE4_ */
