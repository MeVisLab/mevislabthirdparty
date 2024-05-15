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
 * Copyright (C) 1990-93   Silicon Graphics, Inc.
 * Author(s): David Mott, Nick Thompson, Paul Isaacs, Alain Dumesny
 * Ported to Qt4 by MeVis (http://www.mevis.de), 2006
 */


#include <Inventor/errors/SoDebugError.h>
#include <Inventor/SoDB.h>
#include <Inventor/SoInteraction.h>
#include <Inventor/nodekits/SoNodeKit.h>
#include <Inventor/sensors/SoSensorManager.h>
#include <Inventor/Qt/SoQt.h>
#include <Inventor/Qt/devices/SoQtDevice.h>
#include <QTimer>
#include <QScreen>
#include <QApplication>
#include <QProcessEnvironment>
#include "SoQtContextShareManager.h"
#include "SoQtHeadlight.h"

#define SOQT_ZERO_TIMER_THRESHOLD 100

// static members
bool                SoQt::_initialized = false;
SoQtEventHandler *  SoQt::_eventHandler = nullptr;


void
SoQt::init (const char* /*appName*/, const char* /*className*/)
{
    // see if we are already initialized!
    if (_initialized) {
        return;
    }
    _initialized = true;

    // init Inventor
    SoDB::init();
    SoNodeKit::init();
    SoInteraction::init();
    SoQtContextShareManager::init();
  
    // register class with run-time type system
    SoQtDevice::initClass();
    SoQtHeadlight::initClass();

    // bind Inventor with Qt
    _eventHandler = new SoQtEventHandler();
}

bool SoQt::loopDetected()
{
  return _eventHandler ? _eventHandler->loopDetected() : false;
}

//----------------------------------------------------------------------
//
//  SoQtEventHandler - this class ties in sensors to Qt events
//
//----------------------------------------------------------------------

SoQtEventHandler::SoQtEventHandler()
{
    qtTimer     = new QTimer (this);
    qtWorkProc  = new QTimer (this);
    qtTimer->setSingleShot (true);
    qtWorkProc->setSingleShot (true);
    connect (qtTimer, SIGNAL (timeout()), SLOT (qtTimerCallback()));
    connect (qtWorkProc, SIGNAL (timeout()), SLOT (qtWorkProcCallback()));

    SoDB::getSensorManager()->setChangedCallback
        (SoQtEventHandler::sensorManagerChangedCallback,
         this);
    
    _zeroTimerCount = 0;
    _isTriggeredByTimer = false;

    // Call this once because things might already be in the timer queue.
    // If we don't call this and no new things happen, then the callbacks
    // will never be set up.
    setUpCallbacks();
}

bool SoQtEventHandler::loopDetected() const
{
  return _zeroTimerCount >= SOQT_ZERO_TIMER_THRESHOLD;
}

void
SoQtEventHandler::setUpCallbacks()
{
    SbTime      nextEvent;
    bool isZeroTimer = false;

    // If we have a timer at some point, schedule that
    if (SoDB::getSensorManager()->isTimerSensorPending (nextEvent)) {
        // Only change the timer if its deadline is different from the
        // current one.
        if (!qtTimer->isActive() || nextEvent != currentDeadline) {
            currentDeadline = nextEvent;
            long msec = (nextEvent - SbTime::getTimeOfDay()).getMsecValue();
            if (msec < 0) { msec = 0; }
            qtTimer->start (msec);
        }
    } else if (qtTimer->isActive()) {           // get rid of existing timer
        qtTimer->stop();
    }

    // If we have an idle task, schedule a workproc for it
    if (SoDB::getSensorManager()->isDelaySensorPending()) {
        // only schedule it if one is not already active
        if (!qtWorkProc->isActive()) {
            int msec = loopDetected()?1:0;
            qtWorkProc->start (msec);
        }
        isZeroTimer = true;
    }
    else if (qtWorkProc->isActive()) {          // remove obsolete workproc
        qtWorkProc->stop();
    }

    if (_isTriggeredByTimer && isZeroTimer) {
      if (!loopDetected()) {
        _zeroTimerCount++;
        if (loopDetected()){
          emit indicateLoop(true);
        }
      }
    } else {
      if (loopDetected()) {
        emit indicateLoop(false);
      }
      _zeroTimerCount = 0;
    }
}

void
SoQtEventHandler::qtTimerCallback()
{
    // process the timer queue
    _isTriggeredByTimer = true;
    SoDB::getSensorManager()->processTimerQueue();
    setUpCallbacks();
    _isTriggeredByTimer = false;
}

void
SoQtEventHandler::qtWorkProcCallback()
{
    // process the idle queue
    _isTriggeredByTimer = true;
    SoDB::getSensorManager()->processDelayQueue(TRUE);
    setUpCallbacks();
    _isTriggeredByTimer = false;
}

// Callback for changes to the sensor manager
void
SoQtEventHandler::sensorManagerChangedCallback (void *data)
{
    SoQtEventHandler *eh = (SoQtEventHandler *) data;

    // update the Qt timeout and workproc if necessary
    eh->setUpCallbacks();
}
