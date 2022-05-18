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
 |      This file defines the drag point dragger class.
 |
 | NOTE TO DEVELOPERS:
 |     For info about the structure of SoDragPointDragger:
 |     [1] compile: /usr/share/src/Inventor/samples/ivNodeKitStructure
 |     [2] type:    ivNodeKitStructure SoDragPointDragger.
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
 |  dragPointXTranslatorTranslator        - xTranslator.translator
 |  dragPointXTranslatorTranslatorActive  - xTranslator.translatorActive
 |  dragPointYTranslatorTranslator        - yTranslator.translator
 |  dragPointYTranslatorTranslatorActive  - yTranslator.translatorActive
 |  dragPointZTranslatorTranslator        - zTranslator.translator
 |  dragPointZTranslatorTranslatorActive  - zTranslator.translatorActive
 |
 |  dragPointYZTranslatorTranslator       - yzTranslator.translator
 |  dragPointYZTranslatorTranslatorActive - yzTranslator.translatorActive
 |  dragPointXZTranslatorTranslator       - xzTranslator.translator
 |  dragPointXZTranslatorTranslatorActive - xzTranslator.translatorActive
 |  dragPointXYTranslatorTranslator       - xyTranslator.translator
 |  dragPointXYTranslatorTranslatorActive - xyTranslator.translatorActive
 |
 |  dragPointXFeedback                    - xFeedback
 |  dragPointYFeedback                    - yFeedback
 |  dragPointZFeedback                    - zFeedback
 |
 |  dragPointYZFeedback                   - yzFeedback
 |  dragPointXZFeedback                   - xzFeedback
 |  dragPointXYFeedback                   - xyFeedback
 |
 |   Author(s): Paul Isaacs, Howard Look
 |
 ______________  S I L I C O N   G R A P H I C S   I N C .  ____________
 _______________________________________________________________________
 */

#ifndef  _SO_DRAGPOINT_DRAGGER_
#define  _SO_DRAGPOINT_DRAGGER_

#include <Inventor/SbLinear.h>
#include <Inventor/SbBox.h>
#include <Inventor/draggers/SoDragger.h>
#include <Inventor/fields/SoSFVec3f.h>
#include <Inventor/sensors/SoSensor.h>


class SoFieldSensor;


////////////////////////////////////////////////////////////////////////////////
//! Object you can translate in 3D by dragging with the mouse.
/*!
\class SoDragPointDragger
\ingroup Draggers
SoDragPointDragger 
is a compound dragger that translates
in all three dimensions when dragged with the mouse.


It is made up of six smaller draggers, which it displays two at a time.  
Each pair has one <em>plane</em> dragger and one <em>line</em> dragger. The line dragger
is oriented perpendicular to the plane, so 
together the <em>plane/line pair</em> lets you move through all of 3-space.


DragPoint has a total of three such pairs, oriented along the x, y, and z
axes of its local space.  You can cycle through the three pairs by hitting
the <tt>&lt;Control&gt;</tt> key with the cursor over the dragger. (You need not press the
mouse button.)

 
The line draggers are SoTranslate1Draggers and  
the plane draggers are SoTranslate2Draggers. So you can use the
<tt>&lt;Shift&gt;</tt> key to constrain the motion of a plane dragger along one of the
two axes within the plane, as described in the SoTranslate2Draggers man
page.


DragPoint adds extra feedback parts to provide a more intuitive idea of
where you are placed in three-space. There are three <em>feedback planes</em>
and three <em>feedback axes</em>; each corresponds to one of the plane or
line draggers, but spans a much greater distance.  When you drag along a
line, that line's larger feedback axis is displayed, and remains
anchored in space while the dragger slides along it.  This helps
establish the motion of the dragger relative to the rest of the scene.
Similarly, when you drag within a plane, the larger (but transparent)
feedback plane establishes a ground plane for you to move upon. The
location of the dragger within the plane is pinpointed by two
intersecting axes that always cross below the cursor and extend to the
edges of the plane.  When you move dragPoint to the edge of the feedback
plane (or line), the feedback will jump to a new location in that
direction, so that the dragger never leaves the feedback behind.


The primary directions of motion are given by the local space of the dragger.
Transforms earlier in the scene will affect the dragger, its children,  
and the orientation of its directions of motion.


This node has a \b translation  field
which always reflects its position in local space.
Setting the field moves the dragger to that point.
You can also connect fields of other nodes or engines from
this one to make them follow the dragger's motion.


Although the child draggers each have their own resources defining 
default part geometries, the dragPoint dragger overrides these
with a new set of resources.  It also defines resources for the feedback 
parts that it adds.  These are detailed in the Dragger Resources 
section of the online reference page for this class.
You can change the parts in any instance of this dragger using
setPart().


You can make your program use different default resources for the parts
by copying the file
\b /usr/share/data/draggerDefaults/dragPointDragger.iv 
into your own directory, editing the file, and then
setting the environment variable \b SO_DRAGGER_DIR  to be a path to that directory.

\par File Format/Default
\par
\code
DragPointDragger {
  renderCaching AUTO
  boundingBoxCaching AUTO
  renderCulling AUTO
  pickCulling AUTO
  isActive FALSE
  translation 0 0 0
}
\endcode

\par See Also
\par
SoInteractionKit, SoDragger, SoCenterballDragger, SoDragPointDragger, SoHandleBoxDragger, SoJackDragger, SoPointLightDragger, SoRotateCylindricalDragger, SoRotateDiscDragger, SoRotateSphericalDragger, SoScale1Dragger, SoScale2Dragger, SoScale2UniformDragger, SoScaleUniformDragger, SoSpotLightDragger, SoTabBoxDragger, SoTabPlaneDragger, SoTrackballDragger, SoTransformBoxDragger, SoTransformerDragger, SoTranslate1Dragger, SoTranslate2Dragger
*/
////////////////////////////////////////////////////////////////////////////////

class INVENTOR_API SoDragPointDragger : public SoDragger
{
    SO_KIT_HEADER(SoDragPointDragger);

    SO_KIT_CATALOG_ENTRY_HEADER(noRotSep);
    SO_KIT_CATALOG_ENTRY_HEADER(xTranslatorSwitch);
    SO_KIT_CATALOG_ENTRY_HEADER(xTranslator);
    SO_KIT_CATALOG_ENTRY_HEADER(xyTranslatorSwitch);
    SO_KIT_CATALOG_ENTRY_HEADER(xyTranslator);

    SO_KIT_CATALOG_ENTRY_HEADER(rotXSep);
    SO_KIT_CATALOG_ENTRY_HEADER(rotX);
    SO_KIT_CATALOG_ENTRY_HEADER(xzTranslatorSwitch);
    SO_KIT_CATALOG_ENTRY_HEADER(xzTranslator);

    SO_KIT_CATALOG_ENTRY_HEADER(rotYSep);
    SO_KIT_CATALOG_ENTRY_HEADER(rotY);
    SO_KIT_CATALOG_ENTRY_HEADER(zTranslatorSwitch);
    SO_KIT_CATALOG_ENTRY_HEADER(zTranslator);
    SO_KIT_CATALOG_ENTRY_HEADER(yzTranslatorSwitch);
    SO_KIT_CATALOG_ENTRY_HEADER(yzTranslator);

    SO_KIT_CATALOG_ENTRY_HEADER(rotZSep);
    SO_KIT_CATALOG_ENTRY_HEADER(rotZ);
    SO_KIT_CATALOG_ENTRY_HEADER(yTranslatorSwitch);
    SO_KIT_CATALOG_ENTRY_HEADER(yTranslator);

    SO_KIT_CATALOG_ENTRY_HEADER(xFeedbackSwitch);
    SO_KIT_CATALOG_ENTRY_HEADER(xFeedbackSep);
    SO_KIT_CATALOG_ENTRY_HEADER(xFeedbackTranslation);
    SO_KIT_CATALOG_ENTRY_HEADER(xFeedback);

    SO_KIT_CATALOG_ENTRY_HEADER(yFeedbackSwitch);
    SO_KIT_CATALOG_ENTRY_HEADER(yFeedbackSep);
    SO_KIT_CATALOG_ENTRY_HEADER(yFeedbackTranslation);
    SO_KIT_CATALOG_ENTRY_HEADER(yFeedback);

    SO_KIT_CATALOG_ENTRY_HEADER(zFeedbackSwitch);
    SO_KIT_CATALOG_ENTRY_HEADER(zFeedbackSep);
    SO_KIT_CATALOG_ENTRY_HEADER(zFeedbackTranslation);
    SO_KIT_CATALOG_ENTRY_HEADER(zFeedback);

    SO_KIT_CATALOG_ENTRY_HEADER(planeFeedbackSep);
    SO_KIT_CATALOG_ENTRY_HEADER(planeFeedbackTranslation);
    SO_KIT_CATALOG_ENTRY_HEADER(planeFeedbackSwitch);
    SO_KIT_CATALOG_ENTRY_HEADER(yzFeedback);
    SO_KIT_CATALOG_ENTRY_HEADER(xzFeedback);
    SO_KIT_CATALOG_ENTRY_HEADER(xyFeedback);

  public:

    //! Constructor.
    SoDragPointDragger();

    SoSFVec3f translation;

  public:

    //! Set the point at which the feedback axes will jump to a new 
    //! position. For example, if set to .1 (the default), the
    //! feedback axes will jump when the dragger gets within
    //! 10% of the end of the axis.
    void    setJumpLimit(float limit)   { jumpLimit = limit; }
    //! Get the point at which the feedback axes will jump to a new 
    //! position.
    float   getJumpLimit() const        { return jumpLimit; }

    //! The dragPoint dragger contains three pairs of draggers, each containing
    //! a plane dragger and a line dragger (see the Description above).
    //! The dragger starts with the (y-line/xz-plane) pair displayed.
    //! Calling this method will cycle next through the (z-line/xy-plane), then
    //! the (x-line/yz-plane).
    void showNextDraggerSet();

  SoINTERNAL public:
    static void         initClass();    //!< initialize the class

  protected:

    static void startCB( void *, SoDragger * );
    static void motionCB( void *, SoDragger * );
    static void finishCB( void *, SoDragger * );

    SoFieldSensor *fieldSensor;
    static void fieldSensorCB( void *, SoSensor * );
    static void valueChangedCB( void *, SoDragger * );

    static void metaKeyChangeCB( void *, SoDragger *);

    void        dragStart();
    void        drag();
    void        dragFinish();
    
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

    virtual ~SoDragPointDragger();

  private:
    
    SoDragger *currentDragger;
    SbVec3f    startLocalHitPt;

    bool            shftDown;  //!< used to keep track of if meta key is down.

    //! The box defining the area where the feedback appears.
    //! This box stays still in world space whil the dragger is moved.
    //! But when the dragger gets too close to the edge, it jumps over
    //! to define a new box.
    SbBox3f     limitBox;
    
    //! when to jump
    float       jumpLimit;

    //! sets the feedback geometry based on the level of
    //! constraints
    void        setFeedbackGeometry();

    //! checks the limit box and extends it if necessary
    void        checkBoxLimits();

    //! Sets the offsetWorkLimit box and updates the feedback geometry 
    void  updateLimitBoxAndFeedback();

    static const unsigned char geomBuffer[];

    //!  Cached values to make updating feedback more efficient
    SoNode *oldXAxisNode;
    SoNode *oldYAxisNode;
    SoNode *oldZAxisNode;
};

#endif  /* _SO_DRAGPOINT_DRAGGER_ */
