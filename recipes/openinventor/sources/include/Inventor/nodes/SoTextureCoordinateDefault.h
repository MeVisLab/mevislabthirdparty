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
 |      TextureCoordinateDefault causes there to be no texture
 |      coordinates (either explicit from a Texture2 node or implicit
 |      from a texture coordinate function node) in the state, forcing
 |      shapes to use their own, default coordinates.
 |
 |   Author(s)          : Thad Beier, Gavin Bell
 |
 ______________  S I L I C O N   G R A P H I C S   I N C .  ____________
 _______________________________________________________________________
 */

#ifndef  _SO_TEXTURE_COORDINATE_DEFAULT_
#define  _SO_TEXTURE_COORDINATE_DEFAULT_

#include <Inventor/nodes/SoTextureCoordinateFunction.h>


////////////////////////////////////////////////////////////////////////////////
//! Node that removes texture coordinates from state.
/*!
\class SoTextureCoordinateDefault
\ingroup Nodes
This node changes the current traversal state to indicate that there
are no currently defined texture coordinates or texture coordinate
function. This forces subsequent shapes to use their own default
texture coordinates. The net result is that this node turns off any
previous texture coordinate specification.

\par File Format/Default
\par
\code
TextureCoordinateDefault {
}
\endcode

\par Action Behavior
\par
SoGLRenderAction, SoCallbackAction, SoRayPickAction
<BR> Removes any texture coordinates or function. 

\par See Also
\par
SoTexture2, SoTexture2Transform, SoTextureCoordinateEnvironment, SoTextureCoordinatePlane
*/
////////////////////////////////////////////////////////////////////////////////

class INVENTOR_API SoTextureCoordinateDefault : public SoTextureCoordinateFunction {

    SO_NODE_HEADER(SoTextureCoordinateDefault);

  public:

    //! Creates a node with default settings.
    SoTextureCoordinateDefault();

  SoEXTENDER public:
    //! These action methods all just call doAction.
    void                GLRender(SoGLRenderAction *action);
    void                pick(SoPickAction *action);
    void                callback(SoCallbackAction *action);
    
    //! Updates the state for any action.
    void                doAction(SoAction *action);

  SoINTERNAL public:
    static void         initClass();

  protected:
    virtual ~SoTextureCoordinateDefault();
};

#endif /* _SO_TEXTURE_COORDINATE_DEFAULT_ */
