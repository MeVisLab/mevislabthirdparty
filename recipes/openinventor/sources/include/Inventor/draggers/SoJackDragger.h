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
 * Copyright (C) 1990,91,92   Silicon Graphics, Inc.
 *
 _______________________________________________________________________
 ______________  S I L I C O N   G R A P H I C S   I N C .  ____________
 |
 |   $Revision: 1.1.1.1 $
 |
 |   Description:
 |      This file defines the jack dragger class, so named because
 |      with the default geometry, it looks like the children's toy.
 |      This dragger allows you to perform rotations,uniform scales
 |      and translations, all in one spiffy gadget.
 |
 |      Translation is done with a dragPointDragger, rotation with a 
 |      rotateSphericalDragger, and scaling with a scaleUniformDragger.
 |
 | NOTE TO DEVELOPERS:
 |     For info about the structure of SoJackDragger:
 |     [1] compile: /usr/share/src/Inventor/samples/ivNodeKitStructure
 |     [2] type:    ivNodeKitStructure SoJackDragger.
 |     [3] The program prints a diagram of the scene graph and a table with 
 |         information about each part.
 |
 |  The following parts in this dragger are created at construction time.
 |  'ResourceName' corresponds to the name of the default geometry for the
 |  part. The dragger's constructor gets the scene graph for 'ResourceName'
 |  by querying the global dictionary ( SoDB::getByName("ResourceName"); ).  
 |
 |  Resource Name:                      Part Name:
 |
 |   jackScalerScaler                 - scaler.scaler
 |   jackScalerScalerActive           - scaler.scalerActive
 |   jackScalerFeedback               - scaler.feedback
 |   jackScalerFeedbackActive         - scaler.feedbackActive
 |
 |   jackRotatorRotator               - rotator.rotator
 |   jackRotatorRotatorActive         - rotator.rotatorActive
 |   jackRotatorFeedback              - rotator.feedback
 |   jackRotatorFeedbackActive        - rotator.feedbackActive
 |
 |   jackTranslatorLineTranslator     - 
 |                                    - translator.xTranslator.translator
 |                                    - translator.yTranslator.translator
 |                                    - translator.zTranslator.translator
 |
 |   jackTranslatorLineTranslatorActive  - 
 |                                    - translator.xTranslator.translatorActive
 |                                    - translator.yTranslator.translatorActive
 |                                    - translator.zTranslator.translatorActive
 |
 |   jackTranslatorPlaneTranslator    - 
 |                                    - translator.yzTranslator.translator
 |                                    - translator.xzTranslator.translator
 |                                    - translator.xyTranslator.translator
 |
 |   jackTranslatorPlaneTranslatorActive  - 
 |                                    - translator.yzTranslator.translatorActive
 |                                    - translator.xzTranslator.translatorActive
 |                                    - translator.xyTranslator.translatorActive
 |
 |   jackTranslatorXFeedback          - translator.xFeedback
 |   jackTranslatorYFeedback          - translator.yFeedback
 |   jackTranslatorZFeedback          - translator.zFeedback
 |
 |   jackTranslatorXYFeedback         - translator.xyFeedback
 |   jackTranslatorXZFeedback         - translator.xzFeedback
 |   jackTranslatorYZFeedback         - translator.yzFeedback
 |
 |   Author(s): Paul Isaacs
 |
 ______________  S I L I C O N   G R A P H I C S   I N C .  ____________
 _______________________________________________________________________
 */

#ifndef  _SO_JACK_DRAGGER_
#define  _SO_JACK_DRAGGER_

#include <Inventor/SbLinear.h>
#include <Inventor/draggers/SoDragger.h>
#include <Inventor/fields/SoSFVec3f.h>
#include <Inventor/fields/SoSFRotation.h>
#include <Inventor/sensors/SoSensor.h>

class SbDict;
class SoFieldSensor;

////////////////////////////////////////////////////////////////////////////////
//! Jack-shaped object you rotate, translate, or scale by dragging with the mouse.
/*!
\class SoJackDragger
\ingroup Draggers
SoJackDragger 
is a composite dragger in the shape of a jack from the children's game
jacks.  Three lines along the x, y, and z axes form the central star
shape, which you can drag with the mouse to rotate the jack.
Dragging any of the small cubes mounted at the end of the axes will scale
the jack uniformly in all 3 dimensions.
At the core of the jack is an SoDragPointDragger for translating the
jack. 


Each of these shapes is a different dragger with the default geometry
changed.  All of them are parts of the
jack dragger, which keeps them moving together.
The star is an SoRotateSphericalDragger, and dragging it updates the
\b rotation  field of the jack dragger.  The small cubes are  an
SoScaleUniformDragger, tied to the  \b scaleFactor  field.
The position of the SoDragPointDragger is given by the \b translation 
field.  As with all draggers, if you change the fields the dragger will
move to match the new settings.


<em>Remember:</em> This is <em>not</em> an SoTransform!. 
If you want to move other objects with this dragger, you can either: 


[a] Use an SoJackManip, which is subclassed from SoTransform. 
It creates one of
these draggers and uses it as the interface to change its fields.
(see the SoJackManip man page).  


[b] Use field-to-field connections to connect the fields of this dragger to
those of any SoTransformation node.


You can change the parts in any instance of this dragger using
setPart().
The default part geometries are defined as resources for this 
SoJackDragger class.  They are detailed in the 
Dragger Resources section of the online reference page for this class.
You can make your program use different default resources for the parts
by copying the file
\b /usr/share/data/draggerDefaults/jackDragger.iv 
into your own directory, editing the file, and then
setting the environment variable \b SO_DRAGGER_DIR  to be a path to that directory.

\par File Format/Default
\par
\code
JackDragger {
  renderCaching AUTO
  boundingBoxCaching AUTO
  renderCulling AUTO
  pickCulling AUTO
  isActive FALSE
  rotation 0 0 1 0
  translation 0 0 0
  scaleFactor 1 1 1
}
\endcode

\par See Also
\par
SoInteractionKit, SoDragger, SoCenterballDragger, SoDirectionalLightDragger, SoDragPointDragger, SoHandleBoxDragger, SoPointLightDragger, SoRotateCylindricalDragger, SoRotateDiscDragger, SoRotateSphericalDragger, SoScale1Dragger, SoScale2Dragger, SoScale2UniformDragger, SoScaleUniformDragger, SoSpotLightDragger, SoTabBoxDragger, SoTabPlaneDragger, SoTrackballDragger, SoTransformBoxDragger, SoTransformerDragger, SoTranslate1Dragger, SoTranslate2Dragger
*/
////////////////////////////////////////////////////////////////////////////////

class INVENTOR_API SoJackDragger : public SoDragger
{
    SO_KIT_HEADER(SoJackDragger);

    //! For making the dragger surround what lies above it.
    SO_KIT_CATALOG_ENTRY_HEADER(surroundScale);
    //! For keeping the dragger even size in all 3 dimensions
    SO_KIT_CATALOG_ENTRY_HEADER(antiSquish);

    SO_KIT_CATALOG_ENTRY_HEADER(scaler);
    SO_KIT_CATALOG_ENTRY_HEADER(rotator);
    SO_KIT_CATALOG_ENTRY_HEADER(translator);

  public:

    //! Constructor.
    SoJackDragger();

    SoSFRotation rotation;
    SoSFVec3f    translation;
    SoSFVec3f    scaleFactor;

  SoINTERNAL public:
    static void initClass();  //!< initialize the class

  protected:

    SoFieldSensor *rotFieldSensor;
    SoFieldSensor *translFieldSensor;
    SoFieldSensor *scaleFieldSensor;
    static void   fieldSensorCB( void *, SoSensor * );
    static void valueChangedCB( void *, SoDragger * );

    static void invalidateSurroundScaleCB(  void *, SoDragger * );

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


    virtual ~SoJackDragger();

  private:
    static const unsigned char geomBuffer[];
};    

#endif  /* _SO_JACK_DRAGGER_ */
