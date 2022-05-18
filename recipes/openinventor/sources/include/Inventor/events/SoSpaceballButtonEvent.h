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
 |   $Revision: 1.2 $
 |
 |   Classes:
 |      SoSpaceballButtonEvent
 |
 |   Author(s): David Mott, Gavin Bell
 |
 ______________  S I L I C O N   G R A P H I C S   I N C .  ____________
 _______________________________________________________________________
 */

#ifndef  _SO_SPACEBALL_BUTTON_EVENT_
#define  _SO_SPACEBALL_BUTTON_EVENT_

#include <Inventor/system/SbSystem.h>
#include <Inventor/SbBasic.h>
#include <Inventor/events/SoButtonEvent.h>

//! some convenience macros for determining if an event matches
#define SO_SPACEBALL_PRESS_EVENT(EVENT,BUTTON) \
    (SoSpaceballButtonEvent::isButtonPressEvent(EVENT, \
                        SoSpaceballButtonEvent::BUTTON))

#define SO_SPACEBALL_RELEASE_EVENT(EVENT,BUTTON) \
    (SoSpaceballButtonEvent::isButtonReleaseEvent(EVENT, \
                        SoSpaceballButtonEvent::BUTTON))



////////////////////////////////////////////////////////////////////////////////
//! Spaceball button press and release events.
/*!
\class SoSpaceballButtonEvent
\ingroup Errors
SoSpaceballButtonEvent represents spaceball button press and release events
in the Inventor event model.

\par See Also
\par
SoEvent, SoButtonEvent, SoKeyboardEvent, SoLocation2Event, SoMotion3Event, SoMouseButtonEvent, SoHandleEventAction, SoEventCallback, SoSelection, SoInteraction
*/
////////////////////////////////////////////////////////////////////////////////

class INVENTOR_API SoSpaceballButtonEvent : public SoButtonEvent {

    SO_EVENT_HEADER();
    
  public:
    enum Button {
        ANY = 0, 
        BUTTON1 = 1, 
        BUTTON2 = 2, 
        BUTTON3 = 3, 
        BUTTON4 = 4, 
        BUTTON5 = 5, 
        BUTTON6 = 6, 
        BUTTON7 = 7, 
        BUTTON8 = 8, 
        PICK = 9
    };

    //! Constructor.
    SoSpaceballButtonEvent();
    virtual ~SoSpaceballButtonEvent();
    
    //! which button generated the event, e.g. SoSpaceballButtonEvent::BUTTON1
    void                setButton(SoSpaceballButtonEvent::Button b)
        { button = b; }
    SoSpaceballButtonEvent::Button      getButton() const
        { return button; }
    
    //! convenience routines to see if an SoEvent is a press or release
    //! of the passed spaceball button
    static bool         isButtonPressEvent(
                            const SoEvent *e,
                            SoSpaceballButtonEvent::Button whichButton);
                            
    static bool         isButtonReleaseEvent(
                            const SoEvent *e,
                            SoSpaceballButtonEvent::Button whichButton);
    
  SoINTERNAL public:
    static void         initClass();
    
  private:
    Button              button;             //!< which button
};

#endif /* _SO_SPACEBALL_BUTTON_EVENT_ */
