/*
 *
 *  Copyright (C) 2010 MeVis Medical Solutions AG,  All Rights Reserved.
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
 * Copyright (C) 2010 MeVis Medical Solutions AG
 *
 *   \file    SoMouseWheelEvent.h
 *   \author  Florian Link
 *   \date    11/2000
 */

#ifndef __SoMouseWheelEvent_H
#define __SoMouseWheelEvent_H

#include <Inventor/system/SbSystem.h>
#include <Inventor/events/SoSubEvent.h>

//! Open Inventor SoEvent that represents a MouseWheel movement
/*!
This class represents a MouseWheel event. It stores the wheel rotation,
which may be positive or negative, depending on the move of the wheel

\author Florian Link
*/
class INVENTOR_API SoMouseWheelEvent : public SoEvent {
  typedef SoEvent inherited;

  SO_EVENT_HEADER();

public:
  enum Orientation {
    HORIZONTAL,
    VERTICAL
  };
    
  SoMouseWheelEvent() { _wheelRotation = 0; _orientation = VERTICAL; }

  static void initClass(void);

  //! get the wheel rotation value (may be positive or neagtive depending on the move direction)
  short getWheelRotation() const;

  //! set the wheel rotation (should only be called by the event producer, not by the event user
  void  setWheelRotation(short rot);
  
  //! get the wheel's orientation
  Orientation getWheelOrientation() const;
  
  //! set the wheel's orientation
  void  setWheelOrientation(Orientation orient);

private:
  //! the wheel's rotation
  short _wheelRotation;
  //! the wheel's orientation 
  Orientation _orientation;
};

#endif
