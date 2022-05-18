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

/////////////////////////////////////////////////////////////////////////
///
/// Description:
///  This is the include file for the SoSpotLightDragger. 
///  This is a composite dragger which allows independent rotation,
///  translation, and beam spread editting of a spot light.
///
///  It is composed of an SoRotateSphericalDragger (for rotation), 
///  an SoDragPointDragger (for translation), and it creates its own projector
///  handles mouse events for doing it's own dragging of the beam angle.
///
///  The beam is editted by behaving like an SoRotateDiscDragger, but the 
///  plane of the disc is re-defined every time a drag is initiated.
///  The plane always passes through the z axis and the selected point.
///  When the rotation angle is determined, however, the beam is not rotated,
///  but scaled so it looks like an opening or closing umbrella. This is done
///  by scaling evenly in x and y, and a different amount in z, so the distance
///  between the selected point and the origin remains constant.
///
/// NOTE TO DEVELOPERS:
///     For info about the structure of SoSpotLightDragger:
///     [1] compile: /usr/share/src/Inventor/samples/ivNodeKitStructure
///     [2] type:    ivNodeKitStructure SoSpotLightDragger.
///     [3] The program prints a diagram of the scene graph and a table with 
///         information about each part.
///
///
///  The following parts in this dragger are created at construction time.
///  'ResourceName' corresponds to the name of the default geometry for the
///  part. The dragger's constructor gets the scene graph for 'ResourceName'
///  by querying the global dictionary ( SoDB::getByName("ResourceName"); ).  
///
///  Resource Name:                      Part Name:
///
///  spotLightOverallMaterial          - material
///
///  spotLightTranslatorLineTranslator - 
///                                    - translator.xTranslator.translator
///                                    - translator.yTranslator.translator
///                                    - translator.zTranslator.translator
///  spotLightTranslatorLineTranslatorActive  - 
///                                    - translator.xTranslator.translatorActive
///                                    - translator.yTranslator.translatorActive
///                                    - translator.zTranslator.translatorActive
///
///  spotLightTranslatorPlaneTranslator- 
///                                    - translator.yzTranslator.translator
///                                    - translator.xzTranslator.translator
///                                    - translator.xyTranslator.translator
///  spotLightTranslatorPlaneTranslatorActive  - 
///                                    - translator.yzTranslator.translatorActive
///                                    - translator.xzTranslator.translatorActive
///                                    - translator.xyTranslator.translatorActive
///
///  spotLightRotatorRotator           - rotator.rotator      
///  spotLightRotatorRotatorActive     - rotator.rotatorActive
///  spotLightRotatorFeedback          - rotator.feedback      
///  spotLightRotatorFeedbackActive    - rotator.feedbackActive
///
///  spotLightBeam                     - beam
///  spotLightBeamActive               - beamActive
///
///  NOTE: This is a translation node that 
///        moves the beam origin relative
///        to the rest of the dragger.
///  spotLightBeamPlacement            - beamPlacement
///
////////////////////////////////////////////////////////////////////////

 
#ifndef  _SO_SPOT_LIGHT_DRAGGER_
#define  _SO_SPOT_LIGHT_DRAGGER_

#include <Inventor/SbLinear.h>
#include <Inventor/draggers/SoDragger.h>
#include <Inventor/fields/SoSFVec3f.h>
#include <Inventor/fields/SoSFFloat.h>
#include <Inventor/fields/SoSFRotation.h>
#include <Inventor/sensors/SoSensor.h>

class SoFieldSensor;
class SbPlaneProjector;

////////////////////////////////////////////////////////////////////////////////
//! Spotlight shaped dragger that allows you to change position, direction, and width of the beam.
/*!
\class SoSpotLightDragger
\ingroup Draggers
SoSpotLightDragger 
is a composite dragger. It is shaped like a beam of light emanating from a
sun-like ball. An arrow runs along the axis of the
beam and extends past the end of the beam.


When you click and drag the beam, it opens and closes with 
an umbrella-like motion. The angle
between the center and edge of the beam is stored in
the \b angle  field of this dragger; setting the \b angle  field causes the
beam to widen or narrow in response.  The spotlight dragger does not
use a standard dragger class to execute this motion.  More details are
given later in this section.


Dragging the arrow rotates it arount the sun, and the beam moves with it.
The arrow is an SoRotateSphericalDragger that controls the \b rotation 
field. See the reference page for SoDirectionalLightDragger, which 
works the same way, for details.


The sun-shape can be dragged to translate all three pieces together
through 3-space. Its movement controls the \b translation  field and
works exactly as described in the reference pages for
SoDirectionalLightDragger  and SoPointLightDragger (which goes
into more detail).


<em>Remember:</em> This is <em>not</em> a light source! It just looks like one.  
If you want to move a light with this dragger, you can do the following:


[a] Use an SoSpotLightManip, which is subclassed from SoLight. 
It creates an SoSpotLightDragger 
and uses it as the interface to change the \b location , \b direction ,
and \b cutOffAngle  of its  light source 
(see the SoSpotLightManip man page). 
The manip also edits the \b material  part of this dragger to match the
color of light the manip is producing.


[b] Connect the \b angle  field of this dragger to the \b cutOffAngle 
field of an SoSpotLight with a field-to-field connection.


See the SoPointLightDragger and SoDirectionalLightDragger
man pages for other ways to control light parameters with the 
\b rotation  and \b translation  fields.


This class  creates its own projector and 
handles mouse events to do it's own dragging of the beam angle.
When the mouse picks a point on the beam, that point is dragged in a
circle just like in an SoRotateDiscDragger, but the
plane of the disc is re-defined every time a drag is initiated.
Imagine placing the metal tip of a compass at the apex of the cone and the
pencil tip at the picked point.
If you swing an arc through the central axis of the cone, 
you will be drawing the arc
used to drag the beam open and closed.


The beam is opened and closed not by rotating, but by scaling.  
The dragger scales the beam-cone so that the height and 
radius change to move the picked point along the circle.  Then the 
\b angle  field is calculated from the height and radius.


You can change the geometry of parts in any instance of this dragger using
setPart().
The default part geometries are defined as resources for this 
SoSpotLightDragger class.  They are detailed below in the 
<tt>DRAGGER RESOURCE</tt> section.
You can make your program use different default resources for the parts
by copying the file
\b /usr/share/data/draggerDefaults/spotLightDragger.iv 
into your own directory, editing the file, and then
setting the environment variable \b SO_DRAGGER_DIR  to be a path to that directory.

\par File Format/Default
\par
\code
SpotLightDragger {
  renderCaching AUTO
  boundingBoxCaching AUTO
  renderCulling AUTO
  pickCulling AUTO
  isActive FALSE
  rotation 0 0 1 0
  translation 0 0 0
  angle 1
}
\endcode

\par See Also
\par
SoInteractionKit, SoDragger, SoCenterballDragger, SoDirectionalLightDragger, SoDragPointDragger, SoHandleBoxDragger, SoJackDragger, SoPointLightDragger, SoRotateCylindricalDragger, SoRotateDiscDragger, SoRotateSphericalDragger, SoScale1Dragger, SoScale2Dragger, SoScale2UniformDragger, SoScaleUniformDragger, SoTabBoxDragger, SoTabPlaneDragger, SoTrackballDragger, SoTransformBoxDragger, SoTransformerDragger, SoTranslate1Dragger, SoTranslate2Dragger
*/
////////////////////////////////////////////////////////////////////////////////

class INVENTOR_API SoSpotLightDragger : public SoDragger
{
    SO_KIT_HEADER(SoSpotLightDragger);

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
    //! Beneath a separator, the beamPlacement part places the beam's local
    //! space relative to the other parts.
    //! The beamSwitch is flipped when the beam is dragged. 
    SO_KIT_CATALOG_ENTRY_HEADER(beamSep);
    SO_KIT_CATALOG_ENTRY_HEADER(beamPlacement);
    SO_KIT_CATALOG_ENTRY_HEADER(beamScale);
    SO_KIT_CATALOG_ENTRY_HEADER(beamSwitch);
    SO_KIT_CATALOG_ENTRY_HEADER(beam);
    SO_KIT_CATALOG_ENTRY_HEADER(beamActive);

  public:

    //! Constructor.
    SoSpotLightDragger();

    SoSFRotation rotation;
    SoSFVec3f    translation;
    SoSFFloat    angle;

  SoINTERNAL public:
    static void initClass(); //!< Initialize the class. 

  protected:

    SbPlaneProjector    *planeProj;  //!< used during interaciton with beam

    static void startCB( void *, SoDragger * );
    static void motionCB( void *, SoDragger * );
    static void doneCB( void *, SoDragger * );

    void        dragStart();
    void        drag();
    void        dragFinish();

    SoFieldSensor *rotFieldSensor;
    SoFieldSensor *translFieldSensor;
    SoFieldSensor *angleFieldSensor;
    static void   fieldSensorCB( void *, SoSensor * );
    static void   valueChangedCB( void *, SoDragger * );

    //! Returns scaleFactor for beamScale part to display beamAngle.
    void setBeamScaleFromAngle(float beamAngle);

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

    virtual ~SoSpotLightDragger();

  private:
    static const unsigned char geomBuffer[];
};    

#endif  /* _SO_SPOT_LIGHT_DRAGGER_ */
