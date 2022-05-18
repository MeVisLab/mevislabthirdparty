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
 |   $Revision $
 |
 |   Description:
 |      This file defines the SoComplexity node class.
 |
 |   Author(s)          : Paul S. Strauss
 |
 ______________  S I L I C O N   G R A P H I C S   I N C .  ____________
 _______________________________________________________________________
 */

#ifndef  _SO_COMPLEXITY_
#define  _SO_COMPLEXITY_

#include <Inventor/elements/SoComplexityTypeElement.h>
#include <Inventor/fields/SoSFEnum.h>
#include <Inventor/fields/SoSFFloat.h>
#include <Inventor/nodes/SoSubNode.h>


////////////////////////////////////////////////////////////////////////////////
//! Shape complexity node.
/*!
\class SoComplexity
\ingroup Nodes
This node sets the current shape complexity value. This is a heuristic
value which provides a hint at what geometric complexity to render
shape nodes.  Values range from 0 to 1, where 0 means minimum
complexity and 1 means maximum complexity. Each shape node interprets
complexity in its own way.


Shape complexity always affects rendering and primitive generation for
the SoCallbackAction. For some shapes, it also affects picking.


There are three ways to interpret shape complexity, depending on the
\b type  field. <tt>BOUNDING_BOX</tt> complexity ignores the \b value 
field and renders all shapes as bounding boxes, using the current
material, drawing style, etc. The other two types use the \b value 
field to determine the tessellation of shapes into polygons.
<tt>OBJECT_SPACE</tt> complexity uses \b value  directly to determine the
tessellation.  <tt>SCREEN_SPACE</tt> complexity depends on \b value  and the
projected size of the shape on the screen; a \b value  of 0 produces
the minimum tessellation for a shape, and a \b value  of 1 produces a
tessellation that is fine enough that each edge of a polygon is about 1
or two pixels in length. Since the projected size depends on the
camera position, objects may be tessellated differently every frame if
the camera is moving; note that this may have adverse effects on
render caching in SoSeparator nodes.


The SoComplexity node also sets a hint for the quality of textures
applied to shapes, based on the value of the \b textureQuality  field.
The texture quality will take effect at the next Texture2 node;
Texture2 nodes previously traversed will not be affected.

\par File Format/Default
\par
\code
Complexity {
  type OBJECT_SPACE
  value 0.5
  textureQuality 0.5
}
\endcode

\par Action Behavior
\par
SoGLRenderAction, SoCallbackAction, SoGetBoundingBoxAction, SoRayPickAction
<BR> Sets the current complexity in the state. 

\par See Also
\par
SoShape, SoShapeHints, SoTexture2
*/
////////////////////////////////////////////////////////////////////////////////

class INVENTOR_API SoComplexity : public SoNode {

    SO_NODE_HEADER(SoComplexity);

  public:
    enum Type {
        OBJECT_SPACE = SoComplexityTypeElement::OBJECT_SPACE,
        SCREEN_SPACE = SoComplexityTypeElement::SCREEN_SPACE,
        BOUNDING_BOX = SoComplexityTypeElement::BOUNDING_BOX
    };

    //! \name Fields
    //@{

    //! How shape complexity is interpreted.
    SoSFEnum            type;           

    //! Complexity value.
    SoSFFloat           value;          

    //! Hint about texture quality. A value of 0 indicates that the fastest
    //! texturing should be used, while a value of 1 indicates that the best
    //! quality texturing should be used.
    SoSFFloat           textureQuality; 

    //@}

    //! Creates a complexity node with default settings.
    SoComplexity();

  SoEXTENDER public:
    virtual void        doAction(SoAction *action);
    virtual void        callback(SoCallbackAction *action);
    virtual void        getBoundingBox(SoGetBoundingBoxAction *action);
    virtual void        GLRender(SoGLRenderAction *action);
    virtual void        pick(SoPickAction *action);

  SoINTERNAL public:
    static void         initClass();

  protected:
    virtual ~SoComplexity();
};

#endif /* _SO_COMPLEXITY_ */
