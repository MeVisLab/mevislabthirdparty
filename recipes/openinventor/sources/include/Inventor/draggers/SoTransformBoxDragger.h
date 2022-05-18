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
 |      This file defines the transform box dragger class.
 |      This dragger allows you to perform rotations,uniform scales
 |      and translations, all in one tidy box.
 |
 | NOTE TO DEVELOPERS:
 |     For info about the structure of SoTransformBoxDragger:
 |     [1] compile: /usr/share/src/Inventor/samples/ivNodeKitStructure
 |     [2] type:    ivNodeKitStructure SoTransformBoxDragger.
 |     [3] The program prints a diagram of the scene graph and a table with 
 |         information about each part.
 |
 |  The following parts in this dragger are created at construction time.
 |  'ResourceName' corresponds to the name of the default geometry for the
 |  part. The dragger's constructor gets the scene graph for 'ResourceName'
 |  by querying the global dictionary ( SoDB::getByName("ResourceName"); ).  
 |
 |  Resource Name:                           Part Name:
 |
 |  transformBoxScalerScaler               - scaler.scaler          
 |  transformBoxScalerScalerActive         - scaler.scalerActive    
 |  transformBoxScalerFeedback             - scaler.feedback        
 |  transformBoxScalerFeedbackActive       - scaler.feedbackActive  
 |
 |  transformBoxRotatorRotator             - rotator1.rotator          
 |  transformBoxRotatorRotatorActive       - rotator1.rotatorActive    
 |  transformBoxRotatorFeedback            - rotator1.feedback        
 |  transformBoxRotatorFeedbackActive      - rotator1.feedbackActive  
 |  (ditto for rotator2 and rotator3)
 |
 |  transformBoxTranslatorTranslator       - translator1.translator  
 |  transformBoxTranslatorTranslatorActive - translator1.translatorActive
 |  transformBoxTranslatorXAxisFeedback    - translator1.xAxisFeedback
 |  transformBoxTranslatorYAxisFeedback    - translator1.yAxisFeedback
 |  (ditto for translator2 - translator6)
 |
 |   Author(s): Paul Isaacs, Howard Look
 |
 ______________  S I L I C O N   G R A P H I C S   I N C .  ____________
 _______________________________________________________________________
 */

#ifndef  _SO_TRANSFORM_BOX_DRAGGER_
#define  _SO_TRANSFORM_BOX_DRAGGER_

#include <Inventor/SbLinear.h>
#include <Inventor/draggers/SoDragger.h>
#include <Inventor/fields/SoSFVec3f.h>
#include <Inventor/fields/SoSFRotation.h>
#include <Inventor/sensors/SoSensor.h>

class SbDict;
class SoFieldSensor;

////////////////////////////////////////////////////////////////////////////////
//! Box-like object you scale, rotate, and translate by dragging with the mouse.
/*!
\class SoTransformBoxDragger
\ingroup Draggers
SoTransformBoxDragger 
is a composite dragger shaped like a box with small cubes at the corners.
Click and drag any of these cubes to scale the box uniformly.
Drag any edge of the box to rotate the whole dragger about
its center, along an axis parallel to that edge.  Pick any  face of the
box for 2D translation in the plane of that face. 


Although the box looks just about like a wireframe cube, 
it is composed of many different simple draggers arranged in a composite
assembly.  When one part is dragged, the transformBox makes sure they all
move together.
Each of the parts of the box  is a different dragger with the default geometry
changed. 
The faces of the box are SoTranslate2Draggers, the edges are 
SoRotateCylindricalDraggers, and the cubes are an
SoScaleUniformDragger.  Drag them and the dragger will update
its \b translation , \b rotation  and \b scaleFactor  fields
to reflect the changes.
As with all draggers, if you change the fields the dragger will
move to match the new settings.


\p Remember: This is <em>not</em> an SoTransform!. 
If you want to move other objects with this dragger, you can either: 


[a] Use an SoTransformBoxManip, which is subclassed from SoTransform. 
It creates one of
these draggers and uses it as the interface to change its fields.
(see the SoTransformBoxManip man page).  


[b] Use field-to-field connections to connect the fields of this dragger to
those of any SoTransformation node.


You can change the parts in any instance of this dragger using
setPart().
The default part geometries are defined as resources for this 
SoTransformBoxDragger class.  They are detailed in the 
Dragger Resources section of the online reference page for this class.
You can make your program use different default resources for the parts
by copying the file
\b /usr/share/data/draggerDefaults/transformBoxDragger.iv 
into your own directory, editing the file, and then
setting the environment variable \b SO_DRAGGER_DIR  to be a path to that directory.

\par File Format/Default
\par
\code
TransformBoxDragger {
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
SoInteractionKit, SoDragger, SoCenterballDragger, SoDirectionalLightDragger, SoDragPointDragger, SoHandleBoxDragger, SoJackDragger, SoPointLightDragger, SoRotateCylindricalDragger, SoRotateDiscDragger, SoRotateSphericalDragger, SoScale1Dragger, SoScale2Dragger, SoScale2UniformDragger, SoScaleUniformDragger, SoSpotLightDragger, SoTabBoxDragger, SoTabPlaneDragger, SoTrackballDragger, SoTransformerDragger, SoTranslate1Dragger, SoTranslate2Dragger
*/
////////////////////////////////////////////////////////////////////////////////

class INVENTOR_API SoTransformBoxDragger : public SoDragger
{
    SO_KIT_HEADER(SoTransformBoxDragger);

    //! For making the dragger surround what lies above it.
    SO_KIT_CATALOG_ENTRY_HEADER(surroundScale);
    //! For keeping the dragger even size in all 3 dimensions
    SO_KIT_CATALOG_ENTRY_HEADER(antiSquish);

    SO_KIT_CATALOG_ENTRY_HEADER(scaler);
    SO_KIT_CATALOG_ENTRY_HEADER(rotator1Sep);
    SO_KIT_CATALOG_ENTRY_HEADER(rotator1Rot);
    SO_KIT_CATALOG_ENTRY_HEADER(rotator1);
    SO_KIT_CATALOG_ENTRY_HEADER(rotator2Sep);
    SO_KIT_CATALOG_ENTRY_HEADER(rotator2Rot);
    SO_KIT_CATALOG_ENTRY_HEADER(rotator2);
    SO_KIT_CATALOG_ENTRY_HEADER(rotator3Sep);
    SO_KIT_CATALOG_ENTRY_HEADER(rotator3Rot);
    SO_KIT_CATALOG_ENTRY_HEADER(rotator3);
    SO_KIT_CATALOG_ENTRY_HEADER(translator1Sep);
    SO_KIT_CATALOG_ENTRY_HEADER(translator1Rot);
    SO_KIT_CATALOG_ENTRY_HEADER(translator1);
    SO_KIT_CATALOG_ENTRY_HEADER(translator2Sep);
    SO_KIT_CATALOG_ENTRY_HEADER(translator2Rot);
    SO_KIT_CATALOG_ENTRY_HEADER(translator2);
    SO_KIT_CATALOG_ENTRY_HEADER(translator3Sep);
    SO_KIT_CATALOG_ENTRY_HEADER(translator3Rot);
    SO_KIT_CATALOG_ENTRY_HEADER(translator3);
    SO_KIT_CATALOG_ENTRY_HEADER(translator4Sep);
    SO_KIT_CATALOG_ENTRY_HEADER(translator4Rot);
    SO_KIT_CATALOG_ENTRY_HEADER(translator4);
    SO_KIT_CATALOG_ENTRY_HEADER(translator5Sep);
    SO_KIT_CATALOG_ENTRY_HEADER(translator5Rot);
    SO_KIT_CATALOG_ENTRY_HEADER(translator5);
    SO_KIT_CATALOG_ENTRY_HEADER(translator6Sep);
    SO_KIT_CATALOG_ENTRY_HEADER(translator6Rot);
    SO_KIT_CATALOG_ENTRY_HEADER(translator6);

  public:

    //! Constructor.
    SoTransformBoxDragger();

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

    //! detach/attach callbacks to child draggers.
    //! Also set geometry of childDraggers to be our default instead of their
    //! regular default, using our resources.
    //! Called by:            start/end of SoBaseKit::readInstance
    //! and on new copy by:   start/end of SoBaseKit::copy.
    //! Classes that redefine must call setUpConnections(TRUE,TRUE) 
    //! at end of constructor.
    //! Returns the state of the node when this was called.
    virtual bool setUpConnections( bool onOff, bool doItAlways = FALSE );

    virtual void setDefaultOnNonWritingFields();

    virtual ~SoTransformBoxDragger();

  private:
    static const unsigned char geomBuffer[];
};    

#endif  /* _SO_TRANSFORM_BOX_DRAGGER_ */
