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
 * Copyright (C) 1990,91   Silicon Graphics, Inc.
 *
 _______________________________________________________________________
 ______________  S I L I C O N   G R A P H I C S   I N C .  ____________
 |
 |   $Revision: 1.1.1.1 $
 |
 |   Description:
 |      This file defines the SoBlinker node class.
 |
 |   Author(s)          : Ronen Barzel
 |
 ______________  S I L I C O N   G R A P H I C S   I N C .  ____________
 _______________________________________________________________________
 */

#ifndef  _SO_BLINKER_
#define  _SO_BLINKER_

#include <Inventor/nodes/SoSwitch.h>
#include <Inventor/fields/SoSFFloat.h>
#include <Inventor/fields/SoSFBool.h>


////////////////////////////////////////////////////////////////////////////////
//! Animated cycling switch node.
/*!
\class SoBlinker
\ingroup Nodes
The SoBlinker class is derived from SoSwitch, so it selects
one of its children to traverse. Using engines connected to the
\b realTime  global field, the \b whichChild  field is animated over
time. If the node has only one child, \b whichChild  toggles between
<tt>SO_SWITCH_NONE</tt> and 0, causing the child to be switched on and off
repeatedly. If the node has more than one child, they are cycled
through continuously.

\par File Format/Default
\par
\code
Blinker {
  whichChild -1
  speed 1
  on TRUE
}
\endcode

\par Action Behavior
\par
SoGLRenderAction, SoCallbackAction, SoGetBoundingBoxAction, SoGetMatrixAction, SoHandleEventAction, SoRayPickAction, SoSearchAction
<BR> Same as for SoSwitch. 

*/
////////////////////////////////////////////////////////////////////////////////

class INVENTOR_API SoBlinker : public SoSwitch {

    SO_NODE_HEADER(SoBlinker);

  public:
    //! \name Fields
    //@{

    //! Defines the speed of the blinker, in cycles per second.
    SoSFFloat           speed;  

    //! Allows applications to enable or disable the blinking easily.
    SoSFBool            on;     

    //@}

    //! Creates a blinker node with default settings.
    SoBlinker();

  SoEXTENDER public:
    //! Bounding box computation takes all children into account
    virtual void        getBoundingBox(SoGetBoundingBoxAction *action);

    //! overload write method not to write internal engines
    virtual void        write(SoWriteAction *action);

  SoINTERNAL public:
    static void         initClass();

  protected:
    virtual ~SoBlinker();

    virtual void        notify(SoNotList *);

  private:
    bool                wasOn;  //!< Remembers previous state of "on" field

    //! keep track of internal connection
    class SoEngineOutput        *internalConnection;

    class SoTimeCounter *count;
    void                setupCounter();
    int                 nchildren;

    class SoOneShotSensor       *childrenSensor;
    class SoOneShotSensor       *whichChildSensor;
    class SoFieldSensor         *onSensor;

    static void childrenSensorCB(void *data, class SoSensor *sensor);
    static void whichChildSensorCB(void *data, class SoSensor *sensor);
    static void onSensorCB(void *data, class SoSensor *sensor);
};

#endif /* _SO_BLINKER_ */
