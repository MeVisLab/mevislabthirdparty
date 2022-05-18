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
 |   Classes:
 |      SoButtonEvent
 |
 |   Author(s): David Mott, Gavin Bell
 |
 ______________  S I L I C O N   G R A P H I C S   I N C .  ____________
 _______________________________________________________________________
 */

#ifndef  _SO_BUTTON_EVENT_
#define  _SO_BUTTON_EVENT_

#include <Inventor/system/SbSystem.h>
#include <Inventor/SbBasic.h>
#include <Inventor/events/SoSubEvent.h>


////////////////////////////////////////////////////////////////////////////////
//! Base class for all button events.
/*!
\class SoButtonEvent
\ingroup Errors
SoButtonEvent represents generic button press
and release events in the Inventor event model. It is the base class
for device-specific button events, namely 
SoKeyboardEvent, SoMouseButtonEvent, and
SoSpaceballButtonEvent.
This class stores the down/up state of the button
when the event occurred.

\par See Also
\par
SoEvent, SoKeyboardEvent, SoLocation2Event, SoMotion3Event, SoMouseButtonEvent, SoSpaceballButtonEvent, SoHandleEventAction, SoEventCallback, SoSelection, SoInteraction
*/
////////////////////////////////////////////////////////////////////////////////

class INVENTOR_API SoButtonEvent : public SoEvent {

    SO_EVENT_HEADER();
    
  public:

    //! Constructor.
    SoButtonEvent();
    virtual ~SoButtonEvent();
    
    enum State {
        UP, 
        DOWN, 
        UNKNOWN
    };
    
    //! get state of the button
    void                 setState(SoButtonEvent::State s)   { state = s; }
    SoButtonEvent::State getState() const           { return state; }
    
  SoINTERNAL public:
    static void         initClass();
  
  private:
    State           state;       //!< up, down, or unknown
};


#endif /* _SO_BUTTON_EVENT_ */
