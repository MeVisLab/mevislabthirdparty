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
 |      This file defines the SoPerspectiveCamera node class.
 |
 |   Author(s)          : Paul S. Strauss
 |
 ______________  S I L I C O N   G R A P H I C S   I N C .  ____________
 _______________________________________________________________________
 */

#ifndef  _SO_PERSPECTIVE_CAMERA_
#define  _SO_PERSPECTIVE_CAMERA_

#include <Inventor/fields/SoSFFloat.h>
#include <Inventor/nodes/SoCamera.h>


////////////////////////////////////////////////////////////////////////////////
//! Perspective camera node.
/*!
\class SoPerspectiveCamera
\ingroup Nodes
A perspective camera defines a perspective projection from a
viewpoint. The viewing volume for a perspective camera is a truncated
right pyramid.


By default, the camera is located at (0,0,1) and looks along the
negative z-axis; the \b position  and \b orientation  fields can be
used to change these values. The \b heightAngle  field defines the
total vertical angle of the viewing volume; this and the
aspectRatio field determine the horizontal angle.

\par File Format/Default
\par
\code
PerspectiveCamera {
  viewportMapping ADJUST_CAMERA
  position 0 0 1
  orientation 0 0 1 0
  aspectRatio 1
  nearDistance 1
  farDistance 10
  focalDistance 5
  heightAngle 0.78539819
}
\endcode

\par Action Behavior
\par
SoGLRenderAction, SoCallbackAction, SoGetBoundingBoxAction, SoHandleEventAction, SoRayPickAction
<BR> Sets the viewport and camera information in the state. 

\par See Also
\par
SbViewVolume, SoOrthographicCamera
*/
////////////////////////////////////////////////////////////////////////////////

class INVENTOR_API SoPerspectiveCamera : public SoCamera {

    SO_NODE_HEADER(SoPerspectiveCamera);

  public:
    //! \name Fields
    //@{

    //! Vertical angle of the viewing volume.
    SoSFFloat           heightAngle;    

    //@}

    //! Creates a perspective camera node with default settings.
    SoPerspectiveCamera();

    //! Scales the height of the camera, in this case, the 'heightAngle' field.
    virtual void        scaleHeight( float scaleFactor );

    //! Fills in a view volume structure, based on the camera. If the
    //! useAspectRatio field is not 0.0 (the default), the camera uses
    //! that ratio instead of the one it has.
    virtual SbViewVolume getViewVolume(float useAspectRatio = 0.0) const;

  SoINTERNAL public:
    static void         initClass();

  protected:
    //! Positions camera to view passed bounding box with given aspect
    //! ratio and current height angle
    virtual void        viewBoundingBox(const SbBox3f &box,
                                        float aspect, float slack);

    virtual ~SoPerspectiveCamera();
};

#endif /* _SO_PERSPECTIVE_CAMERA_ */
