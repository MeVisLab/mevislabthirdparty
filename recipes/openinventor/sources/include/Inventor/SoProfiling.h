/*
 *
 *  Copyright (C) 2013 MeVis Medical Solutions AG,  All Rights Reserved.
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
 *  Contact information: MeVis Medical Solutions AG
 *  Universitätsallee 29, D-28359 Bremen, GERMANY, or:
 *
 *  http://www.mevis.de
 *
 */

/*
 * Copyright (C) 2013 MeVis Medical Solutions AG
 *
 *   \file    SoProfiling.h
 *   \author  Florian Link
 *   \date    02/2013
 */

#ifndef  _SO_PROFILING_
#define  _SO_PROFILING_

#include <Inventor/system/SbSystem.h>
#include <Inventor/SbBasic.h>

#define OIV_HAS_PROFILING

class SoAction;
class SoField;
class SoFieldContainer;

//! Static class that offers profiling callbacks for a number of selected
//! Open Inventor features, e.g. field/container notifications.
class INVENTOR_API SoProfiling
{

  //! \name Callbacks
  //@{
  typedef void EnterScopeApplyActionCB(SoAction* action);
  typedef void EnterScopeFieldNotifyCB(SoField* action);
  typedef void EnterScopeFieldContainerNotifyCB(SoFieldContainer* action);
  typedef void EnterScopeProcessDelayQueueCB();
  typedef void EnterScopeProcessTimerQueueCB();

  //! The leave scope callback is used by all EnterScope callbacks.
  //! If an EnterScope callback is not specified, no LeaveScopeCB is emitted
  //! for that callback.
  typedef void LeaveScopeCB();
  //@}

public:
  //! returns if profiling is enabled (callbacks are only called if profiling is enabled)
  static bool isEnabled() { return _enabled; }
  //! enables/disabled the profiling (default is false)
  static void setEnabled(bool flag) { _enabled = flag; }


  //! \name Callback setters
  //@{
  static void setEnterScopeApplyActionCB(EnterScopeApplyActionCB* cb) { _enterScopeApplyActionCB = cb; }
  static void setEnterScopeFieldNotifyCB(EnterScopeFieldNotifyCB* cb) { _enterScopeFieldNotifyCB = cb; }
  static void setEnterScopeFieldContainerNotifyCB(EnterScopeFieldContainerNotifyCB* cb) { _enterScopeFieldContainerNotifyCB = cb; }
  static void setEnterScopeProcessDelayQueueCB(EnterScopeProcessDelayQueueCB* cb) { _enterScopeProcessDelayQueueCB = cb; }
  static void setEnterScopeProcessTimerQueueCB(EnterScopeProcessTimerQueueCB* cb) { _enterScopeProcessTimerQueueCB = cb; }
  static void setLeaveScopeCB(LeaveScopeCB* cb) { _leaveScopeCB = cb; }
  //@}

  //! \name Callback setters
  //@{
  static EnterScopeApplyActionCB* getEnterScopeApplyActionCB() { return _enterScopeApplyActionCB; }
  static EnterScopeFieldNotifyCB* getEnterScopeFieldNotifyCB() { return _enterScopeFieldNotifyCB; }
  static EnterScopeFieldContainerNotifyCB* getEnterScopeFieldContainerNotifyCB() { return _enterScopeFieldContainerNotifyCB; }
  static EnterScopeProcessDelayQueueCB* getEnterScopeProcessDelayQueueCB() { return _enterScopeProcessDelayQueueCB; }
  static EnterScopeProcessTimerQueueCB* getEnterScopeProcessTimerQueueCB() { return _enterScopeProcessTimerQueueCB; }
  static LeaveScopeCB* getLeaveScopeCB() { return _leaveScopeCB; }
  //@}

private:

  static bool _enabled;

  static EnterScopeApplyActionCB* _enterScopeApplyActionCB;
  static EnterScopeFieldNotifyCB* _enterScopeFieldNotifyCB;
  static EnterScopeFieldContainerNotifyCB* _enterScopeFieldContainerNotifyCB;
  static EnterScopeProcessDelayQueueCB* _enterScopeProcessDelayQueueCB;
  static EnterScopeProcessTimerQueueCB* _enterScopeProcessTimerQueueCB;
  static LeaveScopeCB* _leaveScopeCB;
    
};

#endif
