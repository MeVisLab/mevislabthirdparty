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
 |      This file defines the SoMaterial node class.
 |
 |   Author(s)          : Paul S. Strauss, Gavin Bell
 |
 ______________  S I L I C O N   G R A P H I C S   I N C .  ____________
 _______________________________________________________________________
 */

#ifndef  _SO_MATERIAL_
#define  _SO_MATERIAL_

#include <Inventor/fields/SoMFColor.h>
#include <Inventor/fields/SoMFFloat.h>
#include <Inventor/nodes/SoSubNode.h>

class SoColorPacker;
class SoVBO;


////////////////////////////////////////////////////////////////////////////////
//! Surface material definition node.
/*!
\class SoMaterial
\ingroup Nodes
This node defines the current surface material properties for all
subsequent shapes. SoMaterial sets several components of the
current material during traversal. 


Multiple values can be specified for
the \b diffuseColor  and \b transparency .
Different shapes interpret
materials with multiple values differently. To bind materials to
shapes, use an SoMaterialBinding node.

\par File Format/Default
\par
\code
Material {
  ambientColor 0.2 0.2 0.2
  diffuseColor 0.8 0.8 0.8
  specularColor 0 0 0
  emissiveColor 0 0 0
  shininess 0.2
  transparency 0
}
\endcode

\par Action Behavior
\par
SoGLRenderAction, SoCallbackAction
<BR> Sets the ambient color, the diffuse color, the specular color, the emissive color, the shininess, and the transparency of the current material. 

\par See Also
\par
SoBaseColor, SoLightModel, SoMaterialBinding, SoPackedColor
*/
////////////////////////////////////////////////////////////////////////////////

class INVENTOR_API SoMaterial : public SoNode {

    SO_NODE_HEADER(SoMaterial);

  public:
    //! \name Fields
    //@{

    //! Ambient color of the surface.
    SoMFColor           ambientColor;   

    //! Diffuse color(s) of the surface.
    SoMFColor           diffuseColor;   

    //! Specular color of the surface.
    SoMFColor           specularColor;  

    //! Emissive color of the surface.
    SoMFColor           emissiveColor;  

    //! Shininess coefficient of the surface. Values can range from 0.0 for
    //! no shininess (a diffuse surface) to 1.0 for maximum shininess (a
    //! highly polished surface).
    SoMFFloat           shininess;      

    //! Transparency value(s) of the surface. Values can range from 0.0 for
    //! opaque surfaces to 1.0 for completely transparent surfaces.  If the
    //! transparency type is SoGLRenderAction::SCREEN_DOOR then only the
    //! first transparency value will be used.  With other transparency types,
    //! multiple transparencies will be used, if the SoMaterial node
    //! contains as many transparencies as diffuse colors.  If there are not
    //! as many transparencies as diffuse colors, only the first transparency
    //! will be used.
    SoMFFloat           transparency;   

    //@}

    //! Creates a material node with default settings.
    SoMaterial();

  SoEXTENDER public:
    virtual void        doAction(SoAction *action);
    virtual void        GLRender(SoGLRenderAction *action);
    virtual void        callback(SoCallbackAction *action);

  SoINTERNAL public:
    static void         initClass();

  protected:
    virtual ~SoMaterial();
    SoColorPacker *colorPacker;

    SoVBO* _vbo;
};

#endif /* _SO_MATERIAL_ */
