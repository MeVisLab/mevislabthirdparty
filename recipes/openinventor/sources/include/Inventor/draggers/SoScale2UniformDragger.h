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
 |      This file defines the two dimensional uniform scale dragger class.
 |      This is a simple dragger that allows an object to
 |      be scaled about a given center in a plane (defined by the
 |      center and a rotation. The rotation is a rotation which is to
 |      be applied to the default plane to define a new plane).
 |      The default plane has a normal of (0,0,1), and primary directions
 |      of (1,0,0) and (0,1,0)
 |
 |      The scaling occurs within the plane, but is a uniform scale in 
 |      both directions within that plane.
 |
 | NOTE TO DEVELOPERS:
 |     For info about the structure of SoScale2UniformDragger:
 |     [1] compile: /usr/share/src/Inventor/samples/ivNodeKitStructure
 |     [2] type:    ivNodeKitStructure SoScale2UniformDragger.
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
 |  scale2UniformScaler                    - scaler
 |  scale2UniformScalerActive              - scalerActive
 |  scale2UniformFeedback                  - feedback
 |  scale2UniformFeedbackActive            - feedbackActive
 |
 |   Author(s): Paul Isaacs, Howard Look
 |
 ______________  S I L I C O N   G R A P H I C S   I N C .  ____________
 _______________________________________________________________________
 */

#ifndef  _SO_SCALE_2_UNIFORM_DRAGGER_
#define  _SO_SCALE_2_UNIFORM_DRAGGER_

#include <Inventor/SbLinear.h>
#include <Inventor/draggers/SoDragger.h>
#include <Inventor/fields/SoSFVec3f.h>
#include <Inventor/sensors/SoSensor.h>

class SbDict;
class SbLineProjector;
class SoFieldSensor;

////////////////////////////////////////////////////////////////////////////////
//! Object you can scale uniformly in two dimensions by dragging with the mouse.
/*!
\class SoScale2UniformDragger
\ingroup Draggers
SoScale2UniformDragger 
is a simple dragger that scales uniformly in the x and y dimensions when
dragged within the x-y plane with the mouse.  The local space is
determined by its location in the scene graph.  Transformation nodes
placed before it will affect both the dragger and the plane of motion.


This node has a \b scaleFactor  field which always reflects its size in
local space.  If you set the field, the dragger will change
accordingly.  You can also connect fields of other nodes or engines from
this one to make them follow the dragger's motion.


This dragger contains four parts, <em>scaler</em>, <em>scalerActive</em>,
<em>feedback</em>, and <em>feedbackActive</em>.


Each of these is set by default from
a resource described in the Dragger Resource section of the online 
reference page for this class.  You
can change the parts in any instance of this dragger using
setPart().


You can make your program use different default resources for the parts
by copying the file
\b /usr/share/data/draggerDefaults/scale2UniformDragger.iv 
into your own directory, editing the file, and then
setting the environment variable \b SO_DRAGGER_DIR  to be a path to that directory.

\par File Format/Default
\par
\code
Scale2UniformDragger {
  renderCaching AUTO
  boundingBoxCaching AUTO
  renderCulling AUTO
  pickCulling AUTO
  isActive FALSE
  scaleFactor 1 1 1
}
\endcode

\par See Also
\par
SoInteractionKit, SoDragger, SoCenterballDragger, SoDirectionalLightDragger, SoDragPointDragger, SoHandleBoxDragger, SoJackDragger, SoPointLightDragger, SoRotateCylindricalDragger, SoRotateDiscDragger, SoRotateSphericalDragger, SoScale1Dragger, SoScale2Dragger, SoScaleUniformDragger, SoSpotLightDragger, SoTabBoxDragger, SoTabPlaneDragger, SoTrackballDragger, SoTransformBoxDragger, SoTransformerDragger, SoTranslate1Dragger, SoTranslate2Dragger
*/
////////////////////////////////////////////////////////////////////////////////

class INVENTOR_API SoScale2UniformDragger : public SoDragger
{
    SO_KIT_HEADER(SoScale2UniformDragger);

    SO_KIT_CATALOG_ENTRY_HEADER(scalerSwitch);
    SO_KIT_CATALOG_ENTRY_HEADER(scaler);
    SO_KIT_CATALOG_ENTRY_HEADER(scalerActive);
    SO_KIT_CATALOG_ENTRY_HEADER(feedbackSwitch);
    SO_KIT_CATALOG_ENTRY_HEADER(feedback);
    SO_KIT_CATALOG_ENTRY_HEADER(feedbackActive);

  public:

    //! Constructor.
    SoScale2UniformDragger();

    SoSFVec3f scaleFactor;

  SoINTERNAL public:
    static void initClass();  //!< initialize the class

  protected:

    SbVec3f           closestPtOfZeroScale; //!< used during interaction
    SbLineProjector   *lineProj;     //!< projector for  scaling

    static void startCB( void *, SoDragger * );
    static void motionCB( void *, SoDragger * );
    static void finishCB( void *, SoDragger * );

    SoFieldSensor *fieldSensor;
    static void fieldSensorCB( void *, SoSensor * );
    static void valueChangedCB( void *, SoDragger * );

    void dragStart();
    void drag();
    void dragFinish();

    //! detach/attach any sensors, callbacks, and/or field connections.
    //! Called by:            start/end of SoBaseKit::readInstance
    //! and on new copy by:   start/end of SoBaseKit::copy.
    //! Classes that redefine must call setUpConnections(TRUE,TRUE) 
    //! at end of constructor.
    //! Returns the state of the node when this was called.
    virtual bool setUpConnections( bool onOff, bool doItAlways = FALSE );

    virtual ~SoScale2UniformDragger();

  private:
    static const unsigned char geomBuffer[];
};    

#endif  /* _SO_SCALE_2_UNIFORM_DRAGGER_ */



