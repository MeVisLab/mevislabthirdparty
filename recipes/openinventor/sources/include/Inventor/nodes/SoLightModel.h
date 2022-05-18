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
 |      This file defines the SoLightModel node class.
 |
 |   Author(s)          : Paul S. Strauss
 |
 ______________  S I L I C O N   G R A P H I C S   I N C .  ____________
 _______________________________________________________________________
 */

#ifndef  _SO_LIGHT_MODEL_
#define  _SO_LIGHT_MODEL_

#include <Inventor/elements/SoLazyElement.h>
#include <Inventor/fields/SoSFEnum.h>
#include <Inventor/nodes/SoSubNode.h>


////////////////////////////////////////////////////////////////////////////////
//! Node that defines the lighting model to use when rendering.
/*!
\class SoLightModel
\ingroup Nodes
This node defines the lighting model to be used when rendering
subsequent shapes. The lighting model is specified in the \b model 
field. When the default model (Phong lighting) is used, light sources
are required in a scene for objects to be easily visible.

\par File Format/Default
\par
\code
LightModel {
  model PHONG
}
\endcode

\par Action Behavior
\par
SoGLRenderAction, SoCallbackAction
<BR> Sets the current lighting model in the state. 

\par See Also
\par
SoBaseColor, SoEnvironment, SoLight, SoMaterial
*/
////////////////////////////////////////////////////////////////////////////////

class INVENTOR_API SoLightModel : public SoNode {

    SO_NODE_HEADER(SoLightModel);

  public:
    //! Lighting model:
    enum Model {
        BASE_COLOR = SoLazyElement::BASE_COLOR, //!< Just use base color
        PHONG      = SoLazyElement::PHONG       //!< Phong lighting
    };

    //! \name Fields
    //@{

    //! Lighting model to use
    SoSFEnum            model;          

    //@}

    //! Creates a light model node with default settings.
    SoLightModel();

  SoEXTENDER public:
    virtual void        doAction(SoAction *action);
    virtual void        GLRender(SoGLRenderAction *action);
    virtual void        callback(SoCallbackAction *action);

  SoINTERNAL public:
    static void         initClass();

  protected:
    virtual ~SoLightModel();
};

#endif /* _SO_LIGHT_MODEL_ */
