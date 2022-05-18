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
 |      This file defines the trackball dragger class.
 |
 | NOTE TO DEVELOPERS:
 |     For info about the structure of SoTrackballDragger:
 |     [1] compile: /usr/share/src/Inventor/samples/ivNodeKitStructure
 |     [2] type:    ivNodeKitStructure SoTrackballDragger.
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
 |  trackballRotator                       - rotator     
 |  trackballRotatorActive                 - rotatorActive     
 |  trackballXRotator                      - XRotator    
 |  trackballXRotatorActive                - XRotatorActive    
 |  trackballYRotator,                     - YRotator   
 |  trackballYRotatorActive,               - YRotatorActive   
 |  trackballZRotator                      - ZRotator  
 |  trackballZRotatorActive                - ZRotatorActive  
 |  trackballUserAxis                      - userAxis    
 |  trackballUserAxisActive                - userAxisActive    
 |  trackballUserRotator                   - userRotator 
 |  trackballUserRotatorActive             - userRotatorActive 
 |
 |   Author(s): Paul Isaacs, David Mott
 |
 ______________  S I L I C O N   G R A P H I C S   I N C .  ____________
 _______________________________________________________________________
 */

#ifndef  _SO_TRACKBALL_DRAGGER_
#define  _SO_TRACKBALL_DRAGGER_

#include <Inventor/SbLinear.h>
#include <Inventor/SbTime.h>
#include <Inventor/sensors/SoSensor.h>
#include <Inventor/draggers/SoDragger.h>
#include <Inventor/fields/SoSFVec3f.h>
#include <Inventor/fields/SoSFRotation.h>

class SbDict;
class SoGroup;
class SoRotation;
class SbProjector;
class SbSphereProjector;
class SbCylinderProjector;
class SoFieldSensor;
class SoTimerSensor;


////////////////////////////////////////////////////////////////////////////////
//! Striped ball you can rotate or scale uniformly by dragging with the mouse.
/*!
\class SoTrackballDragger
\ingroup Draggers
SoTrackballDragger 
is a ball wrapped in three circular stripes.  The stripes are oriented
like wheels that spin around the x, y, and z axes.  Drag the stripes
to rotate the trackball around those axes.  You do not have to hit the lines;
pick anywhere within the stripe's outline.  To rotate the trackball
freely in 3 dimensions, click the area 
between the stripes and then drag.  An invisible but
pickable sphere initiates this dragging.  If the mouse is still moving when
you release it,  the trackball will continue to  spin.


Press the <tt>&lt;Control&gt;</tt> key to scale the trackball uniformly instead of 
rotating.


Press the <tt>&lt;Shift&gt;</tt> key and the <em>user axis</em> appears; this is a
draggable axis with an extra stripe around it.   
Moving the mouse along the surface of the sphere drags the
'pole' of the axis.  
Release the <tt>&lt;Shift&gt;</tt> key and the user axis remains; drag the
new stripe for constrained rotation around the user axis.
To make the user axis disappear, press <tt>&lt;Shift&gt;</tt> and drag the pole to
where two of other stripes intersect. This aligns the user axis with 
a primary axis, at which point the user axis disappears.


As you drag the trackball, it updates its
\b rotation  field, or its \b scaleFactor  field if 
the <tt>&lt;Control&gt;</tt> key is down. As with all draggers, if you change the 
fields the dragger moves in response.


\p Remember: This is <em>not</em> an SoTransform!. 
If you want to move other objects with this dragger, you can either: 


[a] Use an SoTrackballManip, which is subclassed from SoTransform. 
The manipulator creates one of
these draggers and uses it as the interface to edit the manipulator's fields.
(see the SoTrackballManip reference page).  


[b] Use field-to-field connections to connect the fields of this dragger to
those of any SoTransformation node.


You can change the parts in any instance of this dragger using
setPart().
The default part geometries are defined as resources for this 
SoTrackballDragger class.  They are detailed in the 
Dragger Resources section of the online reference page for this class.
You can make your program use different default resources for the parts
by copying the file
\b /usr/share/data/draggerDefaults/trackballDragger.iv 
into your own directory, editing the file, and then
setting the environment variable \b SO_DRAGGER_DIR  to be a path to that directory.

\par File Format/Default
\par
\code
TrackballDragger {
  renderCaching AUTO
  boundingBoxCaching AUTO
  renderCulling AUTO
  pickCulling AUTO
  isActive FALSE
  rotation 0 0 1 0
  scaleFactor 1 1 1
}
\endcode
\par
NOTE
  Unlike most multi-function draggers,  SoTrackballDragger is
not a compound dragger made up of other draggers that
perform its smaller tasks.  This is 
not because it was inappropriate, but because
the trackball was written before implementation of the methods that
take care of synchronizing multiple child draggers. The younger 
SoCenterballDragger is similar in form to the trackball, but 
the centerball <em>is</em> a compound dragger. 
\par See Also
\par
SoInteractionKit, SoDragger, SoCenterballDragger, SoDirectionalLightDragger, SoDragPointDragger, SoHandleBoxDragger, SoJackDragger, SoPointLightDragger, SoRotateCylindricalDragger, SoRotateDiscDragger, SoRotateSphericalDragger, SoScale1Dragger, SoScale2Dragger, SoScale2UniformDragger, SoScaleUniformDragger, SoSpotLightDragger, SoTabBoxDragger, SoTabPlaneDragger, SoTransformBoxDragger, SoTransformerDragger, SoTranslate1Dragger, SoTranslate2Dragger
*/
////////////////////////////////////////////////////////////////////////////////

class INVENTOR_API SoTrackballDragger : public SoDragger {

    SO_KIT_HEADER(SoTrackballDragger);

    //! For making the dragger surround what lies above it.
    SO_KIT_CATALOG_ENTRY_HEADER(surroundScale);
    //! For keeping the dragger even size in all 3 dimensions
    SO_KIT_CATALOG_ENTRY_HEADER(antiSquish);

    SO_KIT_CATALOG_ENTRY_HEADER(rotatorSwitch);
    SO_KIT_CATALOG_ENTRY_HEADER(rotator);
    SO_KIT_CATALOG_ENTRY_HEADER(rotatorActive);
    SO_KIT_CATALOG_ENTRY_HEADER(XRotatorSwitch);
    SO_KIT_CATALOG_ENTRY_HEADER(XRotator);
    SO_KIT_CATALOG_ENTRY_HEADER(XRotatorActive);
    SO_KIT_CATALOG_ENTRY_HEADER(YRotatorSwitch);
    SO_KIT_CATALOG_ENTRY_HEADER(YRotator);
    SO_KIT_CATALOG_ENTRY_HEADER(YRotatorActive);
    SO_KIT_CATALOG_ENTRY_HEADER(ZRotatorSwitch);
    SO_KIT_CATALOG_ENTRY_HEADER(ZRotator);
    SO_KIT_CATALOG_ENTRY_HEADER(ZRotatorActive);

    //! The userAxisRotation is not a public part.
    SO_KIT_CATALOG_ENTRY_HEADER(userAxisRotation);

    SO_KIT_CATALOG_ENTRY_HEADER(userAxisSwitch);
    SO_KIT_CATALOG_ENTRY_HEADER(userAxis);
    SO_KIT_CATALOG_ENTRY_HEADER(userAxisActive);
    SO_KIT_CATALOG_ENTRY_HEADER(userRotatorSwitch);
    SO_KIT_CATALOG_ENTRY_HEADER(userRotator);
    SO_KIT_CATALOG_ENTRY_HEADER(userRotatorActive);

  public:

    //! Constructor.
    SoTrackballDragger();

    SoSFRotation rotation;
    SoSFVec3f scaleFactor;

    //! \see setAnimationEnabled
    bool isAnimationEnabled() { return animationEnabled; }
    //! If the mouse is moving while you release it, the
    //! trackball will continue to spin afterwards.  
    //! These two methods will query and set whether this 
    //! feature is turned on or off.  By default, the animation feature is turned on.
    void setAnimationEnabled( bool newVal );

  SoINTERNAL public:
    static void         initClass();    //!< initialize the class

  protected:

    //! Callbacks for drag start, motion, and finish
    static void startCB(void *, SoDragger *);
    static void motionCB(void *, SoDragger *);
    static void finishCB(void *, SoDragger *);
    
    SoFieldSensor *rotFieldSensor;
    SoFieldSensor *scaleFieldSensor;
    static void fieldSensorCB( void *, SoSensor * );
    static void valueChangedCB( void *, SoDragger * );

    //! Callback for pressing and releasing the meta keys
    static void metaKeyChangeCB(void *, SoDragger *);

    //! These really do the work during startCB, motionCB, and finishCB
    void        dragStart();
    void        drag();
    void        dragFinish();

    virtual void setAllPartsActive( bool onOrOff );

    //! detach/attach any sensors, callbacks, and/or field connections.
    //! Called by:            start/end of SoBaseKit::readInstance
    //! and on new copy by:   start/end of SoBaseKit::copy.
    //! Classes that redefine must call setUpConnections(TRUE,TRUE) 
    //! at end of constructor.
    //! Returns the state of the node when this was called.
    virtual bool setUpConnections( bool onOff, bool doItAlways = FALSE );

    virtual void setDefaultOnNonWritingFields();

    virtual ~SoTrackballDragger();

    // Results of refactoring (MMS Bug: 57374): 

    //! Moved variables from private to protected
    SbSphereProjector   *sphereProj;
    SbCylinderProjector *stripeProj;

    bool                ctlDown, shftDown; //!< keep track of meta keys

    enum State
        { INACTIVE, FREE_ROTATE, X_ROTATE, Y_ROTATE, Z_ROTATE,
          SCALE, USER_AXIS_ADJUST, USER_AXIS_ROTATE, SPINNING };
    State               currentState;


    //! Determines the State based on the current pick path.
    //! Called by dragStart(). Might be overridden to map interactions to other modifier masks
    //! or to deactivate them
    virtual void initDragState();

    //! Setup the projector at start of free rotation. Returns the used projector.
    //! Per default this is sphereProj, but might me changed in derived classes!
    virtual SbProjector* initSphereProjector(SbVec3f center, float radius, SbVec3f startWorkSpaceHitPt, SbMatrix workingSpace);

    //! Setup the projector at start of constrained rotation. Returns the used projector.
    //! Per default this is stripProj, but might me changed in derived classes!
    virtual SbProjector* initStripeProjector(SbLine  axis,   float radius, SbVec3f startWorkSpaceHitPt, SbMatrix workingSpace);

    //! Compute newHitPt and derive the delta rotation based on prevHitPt and newHitPt.
    virtual void getSphereDeltaRotation(SbRotation &deltaRot, SbVec3f &newHitPt, SbVec3f prevHitPt, SbMatrix workingSpace);

    //! Compute newHitPt and derive the delta rotation based on prevHitPt and newHitPt.
    virtual void getStripeDeltaRotation(SbRotation &deltaRot, SbVec3f &newHitPt, SbVec3f prevHitPt, SbMatrix workingSpace);

  private:
   
    SbVec3f             constrainedAxis;   //!< For storing the rotation axis
    SbVec3f             userAxisVec;       //!< For storing the user definable
                                           //! 'special' rotation axis.
    
    SbVec3f             startWorldHitPt;   //!< used during interaction
    SbVec3f             prevWorldHitPt;    //!< used during interaction by 
                                           //! spherical projector.
    SbMatrix            prevMotionMatrix;  //!< used during interaction by
                                           //! spherical projector.

    //! Setup the projector at start of free rotation. Returns the used projector.
    void initSphereProjectorInternal(SbVec3f center, float radius, SbVec3f startWorkSpaceHitPt, SbMatrix workingSpace);

    //! Setup the projector at start of constrained rotation. Returns the used projector.
    void initStripeProjectorInternal(SbLine  axis,   float radius, SbVec3f startWorkSpaceHitPt, SbMatrix workingSpace);

    void        setHighlights();

    bool                rotateDrag();
    bool                scaleDrag();
    bool                userStripeDrag();
    
    //! character strings from which the shared geometry is read
    static const unsigned char geomBuffer[];

    //! variables used for doing spinning animation
    bool animationEnabled;
    SbTime          prevTime;
    SbTime          spinTime;
    SbTime          scheduleRate;
    SoTimerSensor   *spinSensor;
    SbRotation      *rotBuffer;
    SbTime          *timeBuffer;
    int             firstIndex, lastIndex;
    SbVec3f         averageAxis;
    float           angleVelocity;
    bool            computeAverage;

    //! routines used for doing spinning animation
    static  void spinSensorCB(void *, SoSensor *);
    void    spinAnimate();
    void    resetSpinStuff();

    //! We record whether ball was spinning at drag start. If so, it will 
    //! call ha->setHandled() in dragFinish().  This way, it won't be 
    //! considered an item selection, which is usually the case when you click 
    //! on an object without moving the mouse.
    bool    wasSpinningAtDragStart;
};

#endif /* _SO_TRACKBALL_DRAGGER_ */
