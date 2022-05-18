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
 |      This file defines the SoMaterialBinding node class.
 |
 |   Author(s)          : Paul S. Strauss
 |
 ______________  S I L I C O N   G R A P H I C S   I N C .  ____________
 _______________________________________________________________________
 */

#ifndef  _SO_MATERIAL_BINDING_
#define  _SO_MATERIAL_BINDING_

#include <Inventor/elements/SoMaterialBindingElement.h>
#include <Inventor/fields/SoSFEnum.h>
#include <Inventor/nodes/SoSubNode.h>


////////////////////////////////////////////////////////////////////////////////
//! Node that specifies how multiple materials are bound to shapes.
/*!
\class SoMaterialBinding
\ingroup Nodes
This node specifies how the current materials are bound to shapes that
follow in the scene graph. Each shape node may interpret bindings
differently. The current material always has a base value, which is
defined by the first value of all material fields. Since material
fields may have multiple values, the binding determines how these
values are distributed over a shape.


The bindings for faces and vertices are meaningful only for shapes
that are made from faces and vertices. Similarly, the indexed bindings
are only used by the shapes that allow indexing.


The bindings apply only to diffuse colors and transparency.  Other
materials (emissive, specular, ambient, shininess) will have the first
value applied to the
entire shape, regardless of the material binding or the number provided.


If the number of transparencies is less than the number of diffuse
colors, only the first transparency value will be used, regardless of
the material binding.
If the number of diffuse colors in the state is less than the number required
for the given binding, a debug warning will be printed and unpredictable colors
will result.

\par File Format/Default
\par
\code
MaterialBinding {
  value OVERALL
}
\endcode

\par Action Behavior
\par
SoGLRenderAction, SoCallbackAction
<BR> Sets the current material binding type. 

\par See Also
\par
SoMaterial, SoNormalBinding, SoShape, SoTextureCoordinateBinding
*/
////////////////////////////////////////////////////////////////////////////////

class INVENTOR_API SoMaterialBinding : public SoNode {

    SO_NODE_HEADER(SoMaterialBinding);

  public:
    enum Binding {
        //! Whole object has same material
        OVERALL           = SoMaterialBindingElement::OVERALL,
        //! One material for each part of object
        PER_PART          = SoMaterialBindingElement::PER_PART,
        //! One material for each part of object, indexed
        PER_PART_INDEXED  = SoMaterialBindingElement::PER_PART_INDEXED,
        //! One material for each face of object
        PER_FACE          = SoMaterialBindingElement::PER_FACE,
        //! One material for each face, indexed
        PER_FACE_INDEXED  = SoMaterialBindingElement::PER_FACE_INDEXED,
        //! One material for each vertex of object
        PER_VERTEX        = SoMaterialBindingElement::PER_VERTEX,
        //! One material for each vertex, indexed
        PER_VERTEX_INDEXED= SoMaterialBindingElement::PER_VERTEX_INDEXED,

#ifndef IV_STRICT
        //! Obsolete bindings:
        DEFAULT           = OVERALL,
        NONE              = OVERALL
#endif
    };

    //! \name Fields
    //@{

    //! Specifies how to bind materials to shapes.
    SoSFEnum            value;          

    //@}

    //! Creates a material binding node with default settings.
    SoMaterialBinding();

  SoEXTENDER public:
    virtual void        doAction(SoAction *action);
    virtual void        GLRender(SoGLRenderAction *action);
    virtual void        callback(SoCallbackAction *action);
    virtual void        pick(SoPickAction *action);

  SoINTERNAL public:
    static void         initClass();

  protected:
    virtual ~SoMaterialBinding();

    //! Reads stuff into instance. Upgrades old bindings.
    virtual bool        readInstance(SoInput *in, unsigned short flags);
};

#endif /* _SO_MATERIAL_BINDING_ */
