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
 |      This is the include file for the SoDirectionalLightDragger.
 |
 |   This is a composite dragger which allows independent rotation,
 |   and translation for dragging a directional light.
 |   When applied to a directional light, the translation will only serve
 |   to move the dragger. This translation will have no effect on
 |   the directional light being dragged.
 |
 |  It is composed of an SoRotateSphericalDragger (for rotation), 
 |  and an SoDragPointDragger (for translation).
 |
 | NOTE TO DEVELOPERS:
 |     For info about the structure of SoDirectionalLightDragger:
 |     [1] compile: /usr/share/src/Inventor/samples/ivNodeKitStructure
 |     [2] type:    ivNodeKitStructure SoDirectionalLightDragger.
 |     [3] The program prints a diagram of the scene graph and a table with 
 |         information about each part.
 |
 |  The following parts in this dragger are created at construction time.
 |  'ResourceName' corresponds to the name of the default geometry for the
 |  part. The dragger's constructor gets the scene graph for 'ResourceName'
 |  by querying the global dictionary ( SoDB::getByName("ResourceName"); ).  
 |
 |  Resource Name:                             Part Name:
 |
 |  directionalLightOverallMaterial          - material
 |
 |  directionalLightTranslatorLineTranslator - 
 |                                    - translator.xTranslator.translator
 |                                    - translator.yTranslator.translator
 |                                    - translator.zTranslator.translator
 |  directionalLightTranslatorLineTranslatorActive  - 
 |                                    - translator.xTranslator.translatorActive
 |                                    - translator.yTranslator.translatorActive
 |                                    - translator.zTranslator.translatorActive
 |
 |  directionalLightTranslatorPlaneTranslator        - 
 |                                    - translator.yzTranslator.translator
 |                                    - translator.xzTranslator.translator
 |                                    - translator.xyTranslator.translator
 |  directionalLightTranslatorPlaneTranslatorActive  - 
 |                                    - translator.yzTranslator.translatorActive
 |                                    - translator.xzTranslator.translatorActive
 |                                    - translator.xyTranslator.translatorActive
 |
 |  directionalLightRotatorRotator        - rotator.rotator
 |  directionalLightRotatorRotatorActive  - rotator.rotatorActive
 |  directionalLightRotatorFeedback       - rotator.feedback
 |  directionalLightRotatorFeedbackActive - rotator.feedbackActive
 |
 |   Author(s): Paul Isaacs, David Mott
 |
 ______________  S I L I C O N   G R A P H I C S   I N C .  ____________
 _______________________________________________________________________
 */

#ifndef  _SO_DIRECTIONAL_LIGHT_DRAGGER_
#define  _SO_DIRECTIONAL_LIGHT_DRAGGER_

#include <Inventor/SbLinear.h>
#include <Inventor/draggers/SoDragger.h>
#include <Inventor/fields/SoSFVec3f.h>
#include <Inventor/fields/SoSFRotation.h>
#include <Inventor/sensors/SoSensor.h>

class SoFieldSensor;


////////////////////////////////////////////////////////////////////////////////
//! Directional icon you rotate and translate by dragging with the mouse.
/*!
\class SoDirectionalLightDragger
\ingroup Draggers
SoDirectionalLightDragger 
is a composite dragger.  It looks like a sun with a large arrow coming
out of it.  
The arrow can be rotated about the sun by dragging with the mouse; its
orientation is given by the \b rotation  field.
You can also drag the sun (and the arrow with it) through 3-space. The
location is stored in the \b translation  field.


The dragger uses an SoRotateSphericalDragger for changing the 
rotation. Instead of using the default spherical geometry, this dragger
uses an arrow shape.


The sun is an SoDragPointDragger. Dragging it edits the \b translation 
field; conversely, if you change the \b translation  field the sun 
will move to that new location, bringing the arrow with it.  The sun 
looks and behaves just like 
the sun in an SoPointLightDragger,
as does the \b material  part. See the SoPointLightDragger man page
for details.


<em>Remember:</em> This is <em>not</em> a light source! It just looks like one.  
If you want to move a light with this dragger, you can either: 


[a] Use an SoDirectionalLightManip, which is subclassed from SoLight. 
It creates an SoDirectionalLightDragger 
and uses it as the interface to change the \b direction  of its  
light source (see the SoDirectionalLightManip man page). 
The manipulator also edits the \b material  part of this dragger to match the
color of light the manipulator is producing.
However, the directional light manipulator will ignore the \b translation  
field, because a directional light has no location or translation field.
So in this case the translation dragger merely allows you to 
move the physical arrow to wherever you'd like it to be.


[b] Put an SoTransform under an SoTransformSeparator.
Add the SoDirectionalLight as the next child. Use 
a field-to-field connection between the \b rotation  fields of this
dragger and the transform node to synchronize the light with this dragger.


[c] Use engines to connect the \b rotation  field of this dragger to the 
\b direction  field of an SoDirectionalLight.  Use the \b rotation  as 
input to an SoComposeMatrix engine. Then, use an 
SoTransformVec3f engine to apply that matrix to (0,0,-1), the default
light direction.


You can change the parts in any instance of this dragger using
setPart().
The default part geometries are defined as resources for this 
SoDirectionalLightDragger class.  They are detailed in the 
Dragger Resources section of the online reference page for this class.
You can make your program use different default resources for the parts
by copying the file
\b /usr/share/data/draggerDefaults/directionalLightDragger.iv 
into your own directory, editing the file, and then
setting the environment variable \b SO_DRAGGER_DIR  to be a path to that directory.

\par File Format/Default
\par
\code
DirectionalLightDragger {
  renderCaching AUTO
  boundingBoxCaching AUTO
  renderCulling AUTO
  pickCulling AUTO
  isActive FALSE
  translation 0 0 0
  rotation 0 0 1 0
}
\endcode

\par See Also
\par
SoInteractionKit, SoDragger, SoCenterballDragger, SoDragPointDragger, SoHandleBoxDragger, SoJackDragger, SoPointLightDragger, SoRotateCylindricalDragger, SoRotateDiscDragger, SoRotateSphericalDragger, SoScale1Dragger, SoScale2Dragger, SoScale2UniformDragger, SoScaleUniformDragger, SoSpotLightDragger, SoTabBoxDragger, SoTabPlaneDragger, SoTrackballDragger, SoTransformBoxDragger, SoTransformerDragger, SoTranslate1Dragger, SoTranslate2Dragger
*/
////////////////////////////////////////////////////////////////////////////////

class INVENTOR_API SoDirectionalLightDragger : public SoDragger {

    SO_KIT_HEADER(SoDirectionalLightDragger);

    //! This gives the dragger an overall material.  It is edited by lightManips
    //! to make its dragger match the color of the light.  Any materials within 
    //! other parts will override this one. 
    SO_KIT_CATALOG_ENTRY_HEADER(material);

    //! The translator is kept under a separator along with a
    //! rotation that is maintained as the inverse to the rotation of the
    //! light. This means that using the rotator does not rotate the
    //! coordinate system that we translate the base of the dragger in.
    SO_KIT_CATALOG_ENTRY_HEADER(translatorSep);
    SO_KIT_CATALOG_ENTRY_HEADER(translatorRotInv);
    SO_KIT_CATALOG_ENTRY_HEADER(translator);
    SO_KIT_CATALOG_ENTRY_HEADER(rotator);

  public:
    //! Constructor.
    SoDirectionalLightDragger();

    SoSFRotation rotation;
    SoSFVec3f    translation;

  SoINTERNAL public:
    static void         initClass();    //!< initialize the class

  protected:

    SoFieldSensor *translFieldSensor;
    SoFieldSensor *rotFieldSensor;
    static void   fieldSensorCB( void *, SoSensor * );
    static void valueChangedCB( void *, SoDragger * );

    //! detach/attach any sensors, callbacks, and/or field connections.
    //! Also set geometry of childDraggers to be our default instead of their
    //! regular default, using our resources.
    //! Called by:            start/end of SoBaseKit::readInstance
    //! and on new copy by:   start/end of SoBaseKit::copy.
    //! Classes that redefine must call setUpConnections(TRUE,TRUE) 
    //! at end of constructor.
    //! Returns the state of the node when this was called.
    virtual bool setUpConnections( bool onOff, bool doItAlways = FALSE );

    virtual void setDefaultOnNonWritingFields();

    ~SoDirectionalLightDragger();

  private:
    static const unsigned char geomBuffer[];
};

#endif /* _SO_DIRECTIONAL_LIGHT_DRAGGER_ */
