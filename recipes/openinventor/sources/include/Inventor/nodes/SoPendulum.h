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
 |      This file defines the SoPendulum node class.
 |
 |   Author(s)          : Ronen Barzel
 |
 ______________  S I L I C O N   G R A P H I C S   I N C .  ____________
 _______________________________________________________________________
 */

#ifndef  _SO_PENDULUM_
#define  _SO_PENDULUM_

#include <Inventor/nodes/SoRotation.h>
#include <Inventor/fields/SoSFFloat.h>
#include <Inventor/fields/SoSFBool.h>


////////////////////////////////////////////////////////////////////////////////
//! Animated oscillating rotation node.
/*!
\class SoPendulum
\ingroup Nodes
The SoPendulum class is derived from SoRotation, so it applies
a rotation to the current transformation.  Using engines connected to
the \b realTime  global field, the rotation value is animated over
time between two fixed rotations, achieving the effect of a swinging
pendulum. The period of the swing can be adjusted by changing the
\b speed  field. The current rotation at any time is available in
the \b rotation  field, inherited from SoRotation

\par File Format/Default
\par
\code
Pendulum {
  rotation 0 0 1 0
  rotation0 0 0 1 0
  rotation1 0 0 1 0
  speed 1
  on TRUE
}
\endcode

\par Action Behavior
\par
SoGLRenderAction, SoCallbackAction, SoGetBoundingBoxAction, SoRayPickAction
<BR> Concatenates interpolated rotation value with the current transformation matrix. 
\par
SoGetMatrixAction
<BR> Returns transformation matrix specified by the interpolated rotation. 

\par See Also
\par
SoRotor, SoShuttle
*/
////////////////////////////////////////////////////////////////////////////////

class INVENTOR_API SoPendulum : public SoRotation {

    SO_NODE_HEADER(SoPendulum);

  public:
    //! \name Fields
    //@{

    //! These define the two fixed rotations that are interpolated to create
    //! the pendular motion.
    SoSFRotation        rotation0;

    //! These define the two fixed rotations that are interpolated to create
    //! the pendular motion.
    SoSFRotation        rotation1;

    //! Defines the speed of the pendulum, in cycles per second.
    SoSFFloat           speed;  

    //! Allows applications to enable or disable the motion easily.
    SoSFBool            on;     

    //@}

    //! Creates a pendulum node with default settings.
    SoPendulum();

  SoINTERNAL public:
    static void         initClass();

  protected:
    virtual ~SoPendulum();

  private:
    //! internal engines to compute the rotation
    class SoElapsedTime         *time;
    class SoCalculator          *calc;
    class SoInterpolateRotation *interp;

    //! overload write method not to write internal engines
    virtual void        write(class SoWriteAction *action);

    //! keep track of internal connection
    class SoEngineOutput        *internalConnection;

    //! overload notify method to check for field updates
    virtual void notify(SoNotList *list);

    class SoOneShotSensor       *rotationSensor;
    class SoFieldSensor         *rotation0Sensor;
    class SoFieldSensor         *rotation1Sensor;
    class SoFieldSensor         *onSensor;

    static void rotationSensorCB(void *data, class SoSensor *sensor);
    static void onSensorCB(void *data, class SoSensor *sensor);
};

#endif /* _SO_PENDULUM_ */
