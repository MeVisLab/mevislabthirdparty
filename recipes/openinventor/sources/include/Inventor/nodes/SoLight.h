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
 |      This file defines the SoLight node class.
 |
 |   Author(s)          : Paul S. Strauss
 |
 ______________  S I L I C O N   G R A P H I C S   I N C .  ____________
 _______________________________________________________________________
 */

#ifndef  _SO_LIGHT_
#define  _SO_LIGHT_

#include <Inventor/nodes/SoSubNode.h>
#include <Inventor/fields/SoSFBool.h>
#include <Inventor/fields/SoSFColor.h>
#include <Inventor/fields/SoSFFloat.h>


////////////////////////////////////////////////////////////////////////////////
//! Abstract base class for all light source nodes.
/*!
\class SoLight
\ingroup Nodes
SoLight is the abstract base class for all light nodes. A light
node defines an illumination source that may affect subsequent shapes
in the scene graph, depending on the current lighting style.
Light sources are affected by the current transformation. A light node
under a separator does not affect any objects outside that separator.


You can also use a node kit to create a light; see the reference page for
SoLightKit.

\par Action Behavior
\par
SoGLRenderAction
<BR> Activates this light (if so specified) during traversal. All shape nodes that come after this light in the scene graph are illuminated by this light. 

\par See Also
\par
SoDirectionalLight, SoEnvironment, SoLightKit, SoLightModel, SoMaterial, SoPointLight, SoSpotLight
*/
////////////////////////////////////////////////////////////////////////////////

class INVENTOR_API SoLight : public SoNode {

    SO_NODE_ABSTRACT_HEADER(SoLight);

  public:
    //! \name Fields
    //@{

    //! Determines whether the source is active or inactive. When inactive, the
    //! source does not illuminate at all.
    SoSFBool            on;             

    //! Illumination intensity of light source. Valid values range from 0.0
    //! (no illumination) to 1.0 (maximum illumination).
    SoSFFloat           intensity;      

    //! Light source illumination color.
    SoSFColor           color;          

    //@}

  SoINTERNAL public:
    static void         initClass();

  protected:
    SoLight();                          //!< Makes this abstract

    virtual ~SoLight();
};

#endif /* _SO_LIGHT_ */
