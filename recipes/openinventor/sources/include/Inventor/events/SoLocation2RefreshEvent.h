/*
 *
 *  Copyright (C) 2012 MeVis Medical Solutions AG,  All Rights Reserved.
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
 *  http://www.mevis.de/mms
 *
 */

/*
 * Copyright (C) 2012 MeVis Medical Solutions AG
 *
 *   \file    SoLocation2RefreshEvent.h
 *   \author  Uwe Siems
 *   \date    08/2012
 */

#ifndef __SoLocation2RefreshEvent_H
#define __SoLocation2RefreshEvent_H

#include <Inventor/system/SbSystem.h>
#include <Inventor/events/SoSubEvent.h>
#include <Inventor/events/SoLocation2Event.h>

//! Open Inventor SoEvent that refreshes the current pointer location
/*!
This event will be sent immediately before an OpenInventor scene is redrawn.
Interested nodes can use this to update their state to exactly match the scene
state for rendering.

\author Uwe Siems
*/
class INVENTOR_API SoLocation2RefreshEvent : public SoLocation2Event
{
  typedef SoEvent inherited;

  SO_EVENT_HEADER();

public:
  SoLocation2RefreshEvent() {}
  ~SoLocation2RefreshEvent() {}

  static void initClass(void);

};

#endif
