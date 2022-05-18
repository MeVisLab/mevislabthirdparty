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
 |      This file defines the SoTextureCoordinate2 node class.
 |      This node is for normal (non-homogenouse), 2D texture coordinates
 |   Author(s)          : John Rohlf, Thad Beier
 |
 ______________  S I L I C O N   G R A P H I C S   I N C .  ____________
 _______________________________________________________________________
 */

#ifndef  _SO_TEXTURE_COORDINATE_2_
#define  _SO_TEXTURE_COORDINATE_2_

#include <Inventor/nodes/SoSubNode.h>
#include <Inventor/fields/SoMFVec2f.h>
class SoVBO;


////////////////////////////////////////////////////////////////////////////////
//! 2D texture coordinate node.
/*!
\class SoTextureCoordinate2
\ingroup Nodes
This node defines a set of 2D coordinates to be used to map textures
to subsequent vertex-based shapes (those derived from
SoVertexShape). It replaces the current texture coordinates in the
rendering state for the shapes to use.


The current texture coordinate binding (see
SoTextureCoordinateBinding) determines how texture coordinates are
mapped to vertices of shapes. An alternative to using explicit texture
coordinates is to generate them using a function; see
SoTextureCoordinateFunction.


Texture coordinates range from 0 to 1 across the texture. The
horizontal coordinate, called <tt>S</tt>, is specified first, followed by
the vertical coordinate, <tt>T</tt>.

\par File Format/Default
\par
\code
TextureCoordinate2 {
  point [  ]
}
\endcode

\par Action Behavior
\par
SoGLRenderAction, SoCallbackAction
<BR> Sets the current texture coordinates in the state. 

\par See Also
\par
SoTexture2, SoTextureCoordinateBinding, SoTextureCoordinateFunction, SoVertexShape
*/
////////////////////////////////////////////////////////////////////////////////

class INVENTOR_API SoTextureCoordinate2 : public SoNode {

    SO_NODE_HEADER(SoTextureCoordinate2);

  public:
    //! \name Fields
    //@{

    //! Texture coordinate points.
    SoMFVec2f           point;          

    //@}

    //! Creates a texture coordinate node with default settings.
    SoTextureCoordinate2();

  SoEXTENDER public:
    virtual void        doAction(SoAction *action);
    virtual void        callback(SoCallbackAction *action);
    virtual void        GLRender(SoGLRenderAction *action);
    virtual void        pick(SoPickAction *action);

  SoINTERNAL public:
    static void         initClass();

  protected:
    virtual ~SoTextureCoordinate2();

    SoVBO* _vbo;
};

#endif /* _SO_TEXTURE_COORDINATE_2_ */
