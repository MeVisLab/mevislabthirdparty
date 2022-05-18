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
* Copyright 2010 by MeVis Medical Solutions AG
* Author(s): Uwe Siems, Stephan Palmer
*/

#ifndef _SO_QT_STANDARD_EVENT_TRANSLATOR_H_
#define _SO_QT_STANDARD_EVENT_TRANSLATOR_H_

#include <Inventor/Qt/SoQtDLLInit.h>

#include <Inventor/events/SoKeyboardEvent.h>
#include <Inventor/events/SoMouseButtonEvent.h>
#include <Inventor/events/SoLocation2Event.h>
#include <Inventor/events/SoLocation2RefreshEvent.h>
#include <Inventor/events/SoEnterLeaveEvent.h>
#include <Inventor/events/SoMouseWheelEvent.h>

class QEvent;
class QMouseEvent;
class QKeyEvent;
class QInputEvent;
class QWheelEvent;

#include <Qt>


/**
 * This class encapsulates the translation from Qt event to Open Inventor event for a default set of mouse and keyboard
 * events.
 * Intended usage: Classes which want to use the event translation should add a member of this class. Since objects of
 * this class have an internal state which depends on the render area (the area which produces the Qt event) they are
 * used in, every render area needs its own instance of this class.
 * @note The position of Open Inventor key events will default to (-1,-1) until at least one mouse event was processed
 *       by an object of this class.
 */
class SOQT_MEVIS_EXPORT SoQtStandardEventTranslator
{
public:

  SoQtStandardEventTranslator();

  /**
  * Convenience method. Forwards to second translateEvent() implementation. See its documentation for details.
  */
  const SoEvent* translateEvent (QEvent *anyEvent, short viewportWidth, short viewportHeight, double devicePixelRatio = 1.0);


  /**
  * Translate given Qt event.
  * @param anyEvent The event to be translated.
  * @param viewportSize Width and height of the current viewport
  * @return Pointer to Open Inventor event if translation was successful. NULL if event type is not supported.
  * @note Open Inventor and Qt coordinate systems have a different point of origin (lower left vs. upper left). Thus
  *       the current viewport dimensions are required to use this method. Furthermore, the returned pointer points
  *       to a member of this class. It must never be deleted, since ownership remains with this class!
  */
  const SoEvent* translateEvent (QEvent *anyEvent, const SbVec2s& viewportSize, double devicePixelRatio = 1.0);

  /**
  * Return QEvent type that can be used for a custom QMouseEvent that will be translated into
  * a special SoLocation2RefreshEvent
  */
  static int locationRefreshEventType();

private:

  SoMouseButtonEvent* translateButtonEvent (QMouseEvent *be, SoButtonEvent::State whichState, const SbVec2s& viewportSize);

  SoLocation2Event* translateMotionEvent (QMouseEvent *me, const SbVec2s& viewportSize);
  SoLocation2Event* translateLocationRefreshEvent (QMouseEvent *me, const SbVec2s& viewportSize);
  SoEnterLeaveEvent* translateEnterLeaveEvent(QEvent * anyEvent);
  SoMouseWheelEvent* translateWheelEvent(QWheelEvent* wheelEvent, const SbVec2s& viewportSize);

  SoKeyboardEvent* translateKeyEvent (QKeyEvent *ke, SoButtonEvent::State whichState, const SbVec2s& viewportSize);

  void fillInEventState (SoEvent* event, QInputEvent* ie, const SbVec2s& viewportSize);
  /**
   * The following values are used to remember the position of the last evaluated mouse event. This is done since
   * in Open Inventor, all events (even keyboard events) have a location, but Qt events have not.
   * Values default to (-1,-1) until the first mouse event is processed.
   */
  //@{
  int lastMouseX;
  int lastMouseY;
  Qt::MouseButtons lastMouseButtons; //!< Also remember last pressed buttons
  //@}

  /**
   * Reused Open Inventor event objects which are filled with values of the translated Qt event.
   */
  //@{
  SoMouseButtonEvent buttonEvent;
  SoLocation2Event   loc2Event;
  SoKeyboardEvent    keyEvent;
  SoLocation2RefreshEvent loc2RefreshEvent;
  SoEnterLeaveEvent  enterLeaveEvent;
  SoMouseWheelEvent  mouseWheelEvent;
  //@}
};

#endif //_SO_QT_STANDARD_EVENT_TRANSLATOR_H_
