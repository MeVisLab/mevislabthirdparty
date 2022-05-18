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
 |      SoEvent
 |
 |   Author(s): David Mott, Gavin Bell
 |
 ______________  S I L I C O N   G R A P H I C S   I N C .  ____________
 _______________________________________________________________________
 */

#ifndef  _SO_EVENT_
#define  _SO_EVENT_

#include <Inventor/system/SbSystem.h>
#include <Inventor/SbBasic.h>
#include <Inventor/SbViewportRegion.h>
#include <Inventor/SbLinear.h>
#include <Inventor/SbTime.h>
#include <Inventor/SoType.h>

////////////////////////////////////////////////////////////////////////////////
//! Base class for all events.
/*!
\class SoEvent
\ingroup Errors
SoEvent is the base class for events in the Inventor
event model. An event typically represents a user action, such as
a mouse button being pressed or a keyboard key being released.
SoEvent contains general information found in all Inventor
events, including the time the event occurred, the position of the
locater when the event occurred, and the state of the modifier
keys when the event occurred.

\par See Also
\par
SoButtonEvent, SoKeyboardEvent, SoLocation2Event, SoMotion3Event, SoMouseButtonEvent, SoSpaceballButtonEvent, SoHandleEventAction, SoEventCallback, SoSelection, SoInteraction
*/
////////////////////////////////////////////////////////////////////////////////

class INVENTOR_API SoEvent {
  public:

    //! This describes the bit mask values of setButtonMask and getButtonMask
    enum MouseButtonsMask {
      NO_MOUSEBUTTON_MASK = 0,
      LEFT_MOUSEBUTTON_MASK = 1,
      MIDDLE_MOUSEBUTTON_MASK = 2,
      RIGHT_MOUSEBUTTON_MASK = 4,
      ALL_MOUSEBUTTONS_MASK = LEFT_MOUSEBUTTON_MASK + MIDDLE_MOUSEBUTTON_MASK + RIGHT_MOUSEBUTTON_MASK
    };

    //! Constructor and destructor.
    SoEvent();
    //! Constructor and destructor.
    virtual ~SoEvent();

    //! Return the type id for this event instance.
    virtual SoType      getTypeId() const;

    //! Return the type id for the SoEvent class.
    static SoType       getClassTypeId() { return classTypeId; }

    //! This returns TRUE if the event is an instance of
    //! or derived from an event of the passed type.
    bool                isOfType(SoType type) const;

    //! Set the time at which the event occurred.
    void                setTime(SbTime t)               { timestamp = t; }
    //! Get the time at which the event occurred.
    SbTime              getTime() const                 { return timestamp; }

    //! Set the window pixel location of the cursor when the event occurred.
    //! The position is relative to the lower left corner of the window
    //! in which the event occurred.
    void                setPosition(const SbVec2s &p)   { position = p; }

    //! Get position in pixel coodinates.
    const SbVec2s &     getPosition() const             { return position; }

    //! Get position relative to the specified viewport bounds
    const SbVec2s &     getPosition(const SbViewportRegion &vpRgn) const;

    //! Get the normalized location of the cursor when the event occurred,
    //! relative to the specified viewport region. The returned value will
    //! lie between 0.0 and 1.0.
    const SbVec2f & getNormalizedPosition(const SbViewportRegion &vpRgn) const;

    //! Set whether the modifier keys were down when the event occurred.
    void                setShiftDown(bool isDown)     { shiftDown = isDown; }
    //! Set whether the modifier keys were down when the event occurred.
    void                setCtrlDown(bool isDown)      { ctrlDown = isDown; }
    //! Set whether the modifier keys were down when the event occurred.
    void                setAltDown(bool isDown)       { altDown = isDown; }

    //! Get whether the modifier keys were down when the event occurred.
    bool                wasShiftDown() const            { return shiftDown; }
    //! Get whether the modifier keys were down when the event occurred.
    bool                wasCtrlDown() const             { return ctrlDown; }
    //! Get whether the modifier keys were down when the event occurred.
    bool                wasAltDown() const              { return altDown; }
    
    //! Get which mouse buttons are currently pressed (as bit mask)
    void                setMouseButtonMask(int mask)    { mouseButtonMask = mask; }
    //! Set which mouse buttons are currently pressed
    int                 getMouseButtonMask() const      { return mouseButtonMask; }

  SoINTERNAL public:
    //! Initializes base event class
    static void         initClass();

    //! Initialize ALL Inventor event classes
    static void         initClasses();
    
  private:
    //! all of these are set according to when the event occurred
    SbTime              timestamp;  //!< time the event occurred
    bool                shiftDown;  //!< TRUE if shift key was down 
    bool                ctrlDown;   //!< TRUE if ctrl key was down 
    bool                altDown;    //!< TRUE if alt key was down 

    int                 mouseButtonMask; //!< bit mask of currently pressed mouse buttons

    SbVec2s             position;   //!< locator position when event occurred
    SbVec2s             viewportPos;    //!< position relative to viewport
    SbVec2f             normalizedPos;  //!< normalized position

    static SoType       classTypeId; //!< base typeId for all events
};


#endif /* _SO_EVENT_ */
