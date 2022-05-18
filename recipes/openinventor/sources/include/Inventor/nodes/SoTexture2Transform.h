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
 |      This file defines the SoTexture2Transform node class.
 |
 |   Author(s)          : Paul S. Strauss, Thaddeus Beier
 |
 ______________  S I L I C O N   G R A P H I C S   I N C .  ____________
 _______________________________________________________________________
 */

#ifndef  _SO_TEXTURE_2_TRANSFORM_
#define  _SO_TEXTURE_2_TRANSFORM_

#include <Inventor/fields/SoSFVec2f.h>
#include <Inventor/fields/SoSFFloat.h>
#include <Inventor/nodes/SoSubNode.h>


////////////////////////////////////////////////////////////////////////////////
//! 2D texture transformation node.
/*!
\class SoTexture2Transform
\ingroup Nodes
This node defines a 2D transformation applied to texture coordinates.
This affects the way textures are applied to the surfaces of
subsequent shapes. The transformation consists of (in order) a
non-uniform scale about an arbitrary center point, a rotation about
that same point, and a translation. (Note: while the transformations
can be thought of as being applied in that order, the GL matrices are
actually premultiplied in the opposite order. Therefore, the
operations are listed in the reverse order throughout this reference page.)
This allows a user to change the size and position of the textures on
objects.

\par File Format/Default
\par
\code
Texture2Transform {
  translation 0 0
  rotation 0
  scaleFactor 1 1
  center 0 0
}
\endcode

\par Action Behavior
\par
SoGLRenderAction, SoCallbackAction
<BR> Concatenates transformation with the current texture transformation. 

\par See Also
\par
SoTexture2, SoTextureCoordinate2, SoTextureCoordinateFunction
*/
////////////////////////////////////////////////////////////////////////////////

class INVENTOR_API SoTexture2Transform : public SoNode {

    SO_NODE_HEADER(SoTexture2Transform);

  public:
    //! \name Fields
    //@{

    //! Translation in S and T.
    SoSFVec2f           translation;    

    //! Counter-clockwise rotation of the coordinate space, in radians. This
    //! results in a clockwise rotation of the texture on the object.
    SoSFFloat           rotation;       

    //! Scaling factors in S and T.
    SoSFVec2f           scaleFactor;    

    //! Center point used for scaling and rotation.
    SoSFVec2f           center;         

    //@}

    //! Creates a texture transformation node with default settings.
    SoTexture2Transform();

  SoEXTENDER public:
    virtual void        doAction(SoAction *action);
    virtual void        callback(SoCallbackAction *action);
    virtual void        GLRender(SoGLRenderAction *action);
    virtual void        getMatrix(SoGetMatrixAction *action);
    virtual void        pick(SoPickAction *action);

  SoINTERNAL public:
    static void         initClass();

  protected:
    virtual ~SoTexture2Transform();
};

#endif /* _SO_TEXTURE_2_TRANSFORM_ */
