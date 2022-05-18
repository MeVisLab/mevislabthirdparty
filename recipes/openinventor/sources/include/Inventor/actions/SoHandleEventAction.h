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
 |      Defines the SoHandleEventAction class
 |
 |   Author(s)          : Paul S. Strauss
 |
 ______________  S I L I C O N   G R A P H I C S   I N C .  ____________
 _______________________________________________________________________
 */

#ifndef  _SO_HANDLE_EVENT_ACTION_
#define  _SO_HANDLE_EVENT_ACTION_

#include <Inventor/system/SbSystem.h>
#include <Inventor/SbViewportRegion.h>
#include <Inventor/actions/SoSubAction.h>
#include <Inventor/actions/SoRayPickAction.h>

class SoEvent;


////////////////////////////////////////////////////////////////////////////////
//! Allows nodes in a graph to receive input events.
/*!
\class SoHandleEventAction
\ingroup Actions
This class is used to allow nodes in a scene graph to handle input events.
It is usually invoked from a
component derived from SoQtRenderArea when the component receives a window
system event.


Manipulator, dragger and selection nodes respond to and process
events. Most other group nodes just pass the event to their children,
while most other nodes simply ignore the action entirely. Once a node
has indicated to the action that it has handled the event, traversal
stops.


A node that handles an event can also grab future events. Once it has
done so, all events will be sent directly to that node, with no
traversal taking place, until the node releases the grab.

\par See Also
\par
SoEvent, SoPickedPoint, SoRayPickAction
*/
////////////////////////////////////////////////////////////////////////////////

class INVENTOR_API SoHandleEventAction : public SoAction {

    SO_ACTION_HEADER(SoHandleEventAction);

  public:

    //! Constructor takes viewport region to use; this is needed to perform
    //! a pick operation when requested.
    SoHandleEventAction(const SbViewportRegion &viewportRegion);

    //! Destructor
    virtual ~SoHandleEventAction();

    //! Sets/returns current viewport region to use for action.
    void                setViewportRegion(const SbViewportRegion &newRegion);

    //! Sets/returns current viewport region to use for action.
    const SbViewportRegion &getViewportRegion() const   { return vpRegion; }

    //! Sets/returns the event being handled.
    void                setEvent(const SoEvent *ev)     { event = ev; }
    //! Sets/returns the event being handled.
    const SoEvent *     getEvent() const                { return event; }

    //! Sets/returns whether any node has yet handled the event.
    void                setHandled()            { setTerminated(TRUE); }
    //! Sets/returns whether any node has yet handled the event.
    bool                isHandled() const       { return hasTerminated(); }

    //! Initiates grabbing of future events. All events will be sent to the
    //! given node until the grab is released.
    void                setGrabber(SoNode *node);
    //! Releases the grab.
    void                releaseGrabber()            { setGrabber(NULL); }
    //! Returns the node that is currently grabbing events, or NULL if there is none.
    SoNode *            getGrabber() const          { return eventGrabber; }

    //! Sets/returns the root node used for initiating a pick action for those
    //! nodes that want to know what is under the cursor.
    void                setPickRoot(SoNode *node);
    //! Sets/returns the root node used for initiating a pick action for those
    //! nodes that want to know what is under the cursor.
    SoNode *            getPickRoot() const             { return pickRoot; }

    //! Set the radius (in pixels) around the viewport-space point
    //! through which the ray passes when doing ray picking. Ray picking
    //! is performed when 
    //! getPickedPoint()
    //! is called. The pick radius set here is used when
    //! testing the ray against lines and points.
    void                setPickRadius(float radiusInPixels) 
                            { pickAct->setRadius(radiusInPixels); }

    //! Returns the frontmost object hit (as an SoPickedPoint) by
    //! performing a pick based on the mouse location specified in the event
    //! for which the action is being applied. The first time this is called
    //! for a particular event, a SoRayPickAction is applied to find this
    //! object; subsequent calls for the same event return the same
    //! information. The storage for the picked point remains valid as long as
    //! the action is not re-applied or deleted.
    const SoPickedPoint *getPickedPoint();

    //! Returns a list of objects intersected by a picking operation, sorted
    //! from nearest to farthest.
    const SoPickedPointList &getPickedPointList();

  SoINTERNAL public:
    static void         initClass();

  protected:
    //! Initiates action on graph
    virtual void        beginTraversal(SoNode *node);

  private:
    const SoEvent       *event;         //!< Event being handled
    SoNode              *pickRoot;      //!< Root node for initiating picking
    SoPickedPoint       *pickedPoint;   //!< PickedPoint from last pick
    bool                pickValid;      //!< Whether last pick is still valid
    bool                usedPickAll;    //!< TRUE if last pick used pickAll=TRUE
    SoRayPickAction     *pickAct;       //!< Pick action
    SoNode              *eventGrabber;  //!< Event grabber - gets all events
    SbViewportRegion    vpRegion;       //!< Current viewport region
};

#endif /* _SO_HANDLE_EVENT_ACTION_ */
