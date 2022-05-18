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
 |      SoMotion3Event - 3d change in value (relative, not absolute)
 |
 |   Author(s): David Mott
 |
 ______________  S I L I C O N   G R A P H I C S   I N C .  ____________
 _______________________________________________________________________
 */

#ifndef  _SO_MOTION3_EVENT_
#define  _SO_MOTION3_EVENT_

#include <Inventor/system/SbSystem.h>
#include <Inventor/SbBasic.h>
#include <Inventor/SbLinear.h>
#include <Inventor/events/SoSubEvent.h>


////////////////////////////////////////////////////////////////////////////////
//! 3D motion events.
/*!
\class SoMotion3Event
\ingroup Errors
SoMotion3Event represents 3D relative motion events in the Inventor
event model.

\par See Also
\par
SoEvent, SoButtonEvent, SoKeyboardEvent, SoLocation2Event, SoMouseButtonEvent, SoSpaceballButtonEvent, SoHandleEventAction, SoEventCallback, SoSelection, SoInteraction
*/
////////////////////////////////////////////////////////////////////////////////

class INVENTOR_API SoMotion3Event : public SoEvent {

    SO_EVENT_HEADER();
    
  public:

    //! Constructor.
    SoMotion3Event();
    virtual ~SoMotion3Event();

    //! Set and get the relative change in translation since the last translation event.
    void                setTranslation(const SbVec3f &t)    { translation = t; }
    //! Set and get the relative change in translation since the last translation event.
    const SbVec3f &     getTranslation() const              { return translation; }

    //! Set and get the relative change in rotation since the last rotation event.
    void                setRotation(const SbRotation &r)    { rotation = r; }
    //! Set and get the relative change in rotation since the last rotation event.
    const SbRotation &  getRotation() const                 { return rotation; }
    
    
  SoINTERNAL public:
    static void     initClass();
    
  private:
    SbVec3f         translation;    //!< translation value
    SbRotation      rotation;       //!< rotation value
};


#endif /* _SO_MOTION3_EVENT_ */
