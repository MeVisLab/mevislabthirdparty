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
 |      An idle sensor is triggered when there is idle time - when no
 |      events are waiting to be processed.  Idle are almost exactly like
 |      OneShot sensors, except that OneShot sensors can timeout (see
 |      SoDB::setDelaySensorTimeout()).
 |
 |   Author(s)          : Paul Strauss
 |
 ______________  S I L I C O N   G R A P H I C S   I N C .  ____________
 _______________________________________________________________________
 */

#ifndef  _SO_IDLE_SENSOR_
#define  _SO_IDLE_SENSOR_

#include <Inventor/sensors/SoDelayQueueSensor.h>

////////////////////////////////////////////////////////////////////////////////
//! Sensor for one-time only callbacks when the application is idle.
/*!
\class SoIdleSensor
\ingroup Sensors
An idle sensor is almost exactly like an SoOneShotSensor, except
that it is only triggered when there are no timer queue sensors
waiting to be triggered and there are no events waiting to be
processed; that is, idle sensors will not be triggered if the delay
queue is processed because the delay queue timeout expires.  If the
delay queue timeout is disabled (see
SoDB::setDelaySensorTimeout().),
idle and one-shot sensors are exactly the same.


Note that idle sensors do not reschedule themselves.  Inventor 1 idle
sensors were always scheduled; call schedule() in the callback
function to duplicate that behavior.


See the SoOneShotSensor manual page for more information.

\par See Also
\par
SoOneShotSensor, SoDelayQueueSensor
*/
////////////////////////////////////////////////////////////////////////////////

class INVENTOR_API SoIdleSensor : public SoDelayQueueSensor {

  public:

    //! Creation methods.  The second method takes the callback function and
    //! data to be called when the sensor is triggered.
    SoIdleSensor();
    //! Creation methods.  The second method takes the callback function and
    //! data to be called when the sensor is triggered.
    SoIdleSensor(SoSensorCB *func, void *data);

    //! Destroys the sensor, freeing up any memory associated with it after
    //! unscheduling it.
    virtual ~SoIdleSensor();

  private:
    //! Let sensor manager know this class should only be processed
    //! when there is really idle time.
    virtual bool        isIdleOnly() const;
};

#endif  /* _SO_IDLE_SENSOR_ */
