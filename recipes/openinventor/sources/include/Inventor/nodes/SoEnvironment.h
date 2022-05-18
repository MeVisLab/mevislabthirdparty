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
 |      This file defines the SoEnvironment node class.
 |
 |   Author(s)          : Paul S. Strauss
 |
 ______________  S I L I C O N   G R A P H I C S   I N C .  ____________
 _______________________________________________________________________
 */

#ifndef  _SO_ENVIRONMENT_
#define  _SO_ENVIRONMENT_

#include <Inventor/fields/SoSFColor.h>
#include <Inventor/fields/SoSFEnum.h>
#include <Inventor/fields/SoSFFloat.h>
#include <Inventor/fields/SoSFVec3f.h>
#include <Inventor/nodes/SoSubNode.h>


////////////////////////////////////////////////////////////////////////////////
//! Global environment node.
/*!
\class SoEnvironment
\ingroup Nodes
This node describes global environmental attributes such as ambient
lighting, light attenuation, and fog.


Ambient lighting is the amount of extra light impinging on each
surface point when the lighting model is Phong (see SoLightModel).


Light attenuation affects all subsequent lights in a scene (see
SoLight). It is a quadratic function of distance from a light
source to a surface point.  The three coefficients are specified in
the \b attenuation  field.  Attenuation works only for light sources
with a fixed location, such as point and spot lights.


Fog has one of four types, each of which blends each surface point
with the specified fog color. Each type interprets the \b visibility 
field to be the distance at which fog totally obscures objects. A
\b visibility  value of 0 (the default) causes the SoEnvironment
node to set up fog so that the visibility is the distance to the far
clipping plane of the current camera.


Note that this node has effect only during rendering, and that it
does not inherit field values from other SoEnvironment nodes.

\par File Format/Default
\par
\code
Environment {
  ambientIntensity 0.2
  ambientColor 1 1 1
  attenuation 0 0 1
  fogType NONE
  fogColor 1 1 1
  fogVisibility 0
}
\endcode

\par Action Behavior
\par
SoGLRenderAction
<BR> Sets the current environment parameters to those specified with this node. Successive geometries will be rendered using this environment. 

\par See Also
\par
SoLight, SoLightModel
*/
////////////////////////////////////////////////////////////////////////////////

class INVENTOR_API SoEnvironment : public SoNode {

    SO_NODE_HEADER(SoEnvironment);

  public:
    //! Type of fog:
    enum FogType {
        NONE,                   //!< No fog
        HAZE,                   //!< Linear increase in opacity with distance
        FOG,                    //!< Exponential increase in opacity
        SMOKE                   //!< Exponential squared increase in opacity
    };

    //! \name Fields
    //@{

    //! Intensity and RGB color of ambient lighting (for Phong lighting).
    SoSFFloat           ambientIntensity;

    //! Intensity and RGB color of ambient lighting (for Phong lighting).
    SoSFColor           ambientColor;

    //@}

    SoSFVec3f           attenuation;

    SoSFEnum            fogType;
    SoSFColor           fogColor;
    SoSFFloat           fogVisibility;

    //! Creates an environment node with default settings.
    SoEnvironment();

  SoEXTENDER public:
    virtual void        GLRender(SoGLRenderAction *action);
    virtual void        callback(SoCallbackAction *action);

  SoINTERNAL public:
    static void         initClass();

  protected:
    virtual ~SoEnvironment();

  private:
    //! Computes fog density based on visibility
    static float        computeDensity(float visibility, bool squared);
};

#endif /* _SO_ENVIRONMENT_ */
