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
 |   $Revision: 1.2 $
 |
 |   Description:
 |      This file defines the SoPackedColor node class.
 |
 |   Author(s)          : Paul S. Strauss
 |
 ______________  S I L I C O N   G R A P H I C S   I N C .  ____________
 _______________________________________________________________________
 */

#ifndef  _SO_PACKED_COLOR_
#define  _SO_PACKED_COLOR_

#include <Inventor/fields/SoMFUInt32.h>
#include <Inventor/nodes/SoSubNode.h>
class SoVBO;


////////////////////////////////////////////////////////////////////////////////
//! Node that defines base colors using packed representation.
/*!
\class SoPackedColor
\ingroup Nodes
SoPackedColor is similar to SoBaseColor in that it sets the
diffuse color component of the current material. However, it also
changes the transparency component. The color and transparency
information is packed into unsigned 32-bit integers: <tt>0xrrggbbaa</tt>,
where <tt>aa</tt> represents the alpha (<tt>0x00</tt> = fully transparent,
<tt>0xff</tt> = opaque), and <tt>rr</tt>, <tt>gg</tt>, and <tt>bb</tt> represent the
red, blue, and green components of the color, respectively.
Note that the order (r,g,b,a) of these components is reversed from
the ordering in releases of Inventor prior to 2.1.


If the
transparency type is SoGLRenderAction::SCREEN_DOOR, only the
first transparency value will be used.  With other transparency types,
multiple transparencies will be used.  


SoPackedColor uses less memory than SoBaseColor or
SoMaterial  to store multiple color and transparency values. It
can be used in cases where space is critical.

\par File Format/Default
\par
\code
PackedColor {
  orderedRGBA 0xccccccff
}
\endcode

\par Action Behavior
\par
SoGLRenderAction, SoCallbackAction
<BR> Sets the current base (diffuse) color(s) in the state. 

\par See Also
\par
SoBaseColor, SoMaterial
*/
////////////////////////////////////////////////////////////////////////////////

class INVENTOR_API SoPackedColor : public SoNode {

    SO_NODE_HEADER(SoPackedColor);

  public:
    //! \name Fields
    //@{

    //! Defines the packed colors.
    SoMFUInt32          orderedRGBA;    

    //@}

    //! Creates a packed color node with default settings.
    SoPackedColor();

  SoEXTENDER public:
    virtual void        doAction(SoAction *action);
    virtual void        GLRender(SoGLRenderAction *action);
    virtual void        callback(SoCallbackAction *action);
    bool                isTransparent()
        {return transparent;}

  SoINTERNAL public:
    static void         initClass();

  protected:
    virtual ~SoPackedColor();
    
  private:
    //! check for transparency when field changes.
    virtual void        notify(SoNotList *list);
    //! store whether transparent or not
    bool transparent;
    
    SoVBO* _vbo;
};

#endif /* _SO_PACKED_COLOR_ */
