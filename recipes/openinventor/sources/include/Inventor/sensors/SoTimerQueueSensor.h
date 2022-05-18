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
 |      Abstract base class for all sensors that are added to the timer
 |      queue. Each sensor in the timer queue contains an SbTime
 |      indicating when the sensor should be triggered. Sensors in the
 |      timer queue are sorted by their trigger times.
 |      Each subclass defines public methods for specifying when and how
 |      to trigger the sensor.
 |
 |   Author(s)          : Nick Thompson, Paul Strauss, Gavin Bell
 |
 ______________  S I L I C O N   G R A P H I C S   I N C .  ____________
 _______________________________________________________________________
 */

#ifndef  _SO_TIMER_QUEUE_SENSOR_
#define  _SO_TIMER_QUEUE_SENSOR_

#include <Inventor/sensors/SoSensor.h>
#include <Inventor/SbTime.h>

////////////////////////////////////////////////////////////////////////////////
//! Abstract base class for sensors dependent on time.
/*!
\class SoTimerQueueSensor
\ingroup Sensors
Timer queue sensors are sensors that trigger themselves at specific
times.  The timer queue is normally processed as part of a programs
main loop when the program is not busy doing something else.  Note
that processing the timer queue is not asynchronous em the program must
re-enter its main loop for timers to be triggered.  When the timer
queue is processed, all timers scheduled to go off at or before the
current time are triggered once, in order from earliest to latest.

\par See Also
\par
SoTimerSensor, SoAlarmSensor, SoIdleSensor, SoOneShotSensor, SoDataSensor
*/
////////////////////////////////////////////////////////////////////////////////

class INVENTOR_API SoTimerQueueSensor : public SoSensor {

  public:
    //! Constructors. The second form takes standard callback function and data
    SoTimerQueueSensor();
    SoTimerQueueSensor(SoSensorCB *func, void *data);

    //! Destructor
    virtual ~SoTimerQueueSensor();

    //! Returns the time at which this sensor is scheduled to be triggered.
    //! If the sensor is not scheduled the results are undefined.
    const SbTime &      getTriggerTime() const          { return trigTime; }

    //! Adds this sensor to the timer queue.  Subclasses provide methods for
    //! setting when the sensor will be triggered.
    virtual void        schedule();
    //! If this sensor is scheduled, removes it from the timer queue so that
    //! it will not be triggered.
    virtual void        unschedule();
    //! Returns TRUE if this sensor has been scheduled and is waiting in the
    //! timer queue to be triggered.
    virtual bool        isScheduled() const;

  protected:
    //! Used by subclasses to set the time at which the sensor is to be
    //! triggered.
    void                setTriggerTime(const SbTime &time);

    //! Triggers the sensor, calling its callback function. This
    //! overrides the method in SoSensor because it has to reset the
    //! schedule flag before triggering.
    virtual void        trigger();

    bool                scheduled;      //!< Whether sensor is scheduled

  private:
    SbTime              trigTime;       //!< Time when sensor is to be triggered

    //! Returns TRUE if this sensor should precede sensor s in the delay
    //! queue: it must have a lower priority number than s.
    virtual bool        isBefore(const SoSensor *s) const;
};

#endif  /* _SO_TIMER_SENSOR_ */
