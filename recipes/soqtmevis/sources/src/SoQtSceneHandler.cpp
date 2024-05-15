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
 * Copyright (C) 1990-93   Silicon Graphics, Inc.
 * Author(s): David Mott, Alain Dumesny
 * Ported to Qt4 by MeVis (http://www.mevis.de), 2006
 */

#include <Inventor/Qt/SoQt.h>
#include <Inventor/Qt/SoQtSceneHandler.h>
#include <Inventor/Qt/devices/SoQtDevice.h>
#include <QEvent>
#include <QMouseEvent>
#include <QDate>
#include <QTime>
#include <QRegularExpression>
#include <QDebug>

#include <Inventor/Qt/devices/SoQtDevice.h>
#include <Inventor/SbLinear.h>
#include <Inventor/SoDB.h>
#include <Inventor/SoInteraction.h>
#include <Inventor/actions/SoHandleEventAction.h>
#include <Inventor/elements/SoGLLazyElement.h>
#include <Inventor/elements/SoWindowElement.h>
#include <Inventor/errors/SoDebugError.h>
#include <Inventor/misc/SoState.h>
#include <Inventor/nodes/SoLocateHighlight.h>
#include <Inventor/nodes/SoNode.h>
#include <Inventor/nodes/SoSelection.h>
#include <cstdio>
#include <cstdlib>

// These are defined on Linux in X11 headers. They make it impossible
// to use QEvent::KeyPress and QEvent::KeyEvent
#ifdef KeyPress
  #undef KeyPress
#endif
#ifdef KeyRelease
  #undef KeyRelease
#endif

// safeguard against missed leave events: remember which handler was the last one
// to have mouse events; only this one will generate mouse move events on repaint
SoQtSceneHandler* SoQtSceneHandler::lastPositionEventHandler = nullptr;

SoQtSceneHandler::SoQtSceneHandler ()
{
    SoQt::init("Dummy");

    devicePixelRatio = 1.0;

    firstEvent = TRUE;
    storedButtonState = Qt::NoButton;
    storedModifierState = Qt::NoModifier;
    lastEventPositionValid = false;
    lockEventHandling = false;

    clearFirst = TRUE;
    autoRedraw = TRUE;
    selection = nullptr;

    sceneMgr = new SoSceneManager();
    sceneMgr->setRenderCallback (renderCB, this);
    sceneContainer = new SoGroup();
    sceneContainer->ref();
    mainScene = nullptr;
    preCallbackCount = 0;
}

SoQtSceneHandler::~SoQtSceneHandler()
{
    // Remove our callback from old selection node
    if (selection != nullptr) {
        selection->removeChangeCallback (SoQtSceneHandler::selectionChangeCB, this);

        // Unref the old selection node
        selection->unref();
    }

    sceneContainer->unref(); sceneContainer = nullptr;
    delete sceneMgr;
}

void
SoQtSceneHandler::setSceneGraph(SoNode *newScene)
{
    // Deactivate while we change the scene so that our sensors
    // get unhooked before the data changes beneath us.
    sceneMgr->deactivate();

    if (mainScene) {
        sceneContainer->removeChild (mainScene);
        mainScene = nullptr;
    }
    if (newScene) {
        // insert scene node after the pre-scene callback nodes, but before the post-scene ones
        sceneContainer->insertChild (newScene, preCallbackCount);
    }
    mainScene = newScene;

    sceneMgr->setSceneGraph(sceneContainer); // treat as totally new scene

    // we activate only if we are visible.
    // after all, if we're not on screen, the visibility change
    // callback will invoke activate() once we are on screen.
    if (isSceneVisible() && autoRedraw) {
        sceneMgr->activate();
        sceneMgr->scheduleRedraw();
    }
}

SoNode *
SoQtSceneHandler::getSceneGraph()
{
    return mainScene;
}

SoCallback*
SoQtSceneHandler::addSceneCallback (SoCallbackCB* func, void* userData, bool afterScene)
{
    SoCallback* cb = new SoCallback();
    cb->setCallback (func, userData);
    if (afterScene) {
        sceneContainer->addChild (cb);
    } else {
        sceneContainer->insertChild (cb, 0);
        preCallbackCount++;
    }
    return cb;
}

bool
SoQtSceneHandler::removeSceneCallback (SoCallback* callbackNode)
{
    if (callbackNode && (callbackNode != mainScene)) { // check against removing the main scene
        int index = sceneContainer->findChild (callbackNode);
        bool ok = (index >= 0);
        sceneContainer->removeChild (callbackNode);
        if (ok && index < preCallbackCount) { preCallbackCount--; } // we removed a pre-scene callback node
        return ok;
    } else {
        return false;
    }
}

void
SoQtSceneHandler::setTransparencyType(SoGLRenderAction::TransparencyType type)
{
    sceneMgr->getGLRenderAction()->setTransparencyType(type);
    sceneMgr->scheduleRedraw();
}

void
SoQtSceneHandler::processSceneEvent(QEvent *anyEvent)
{
    bool isKeyEvent = false;
    bool isMouseEvent = false;
    bool isKnownInputEvent = false;
    // check for special key which turns viewing on/off
    if (anyEvent->type() == QEvent::KeyPress ||
        anyEvent->type() == QEvent::KeyRelease)
    {
        isKeyEvent = true;
    } else if (anyEvent->type() == QEvent::MouseButtonPress ||
               anyEvent->type() == QEvent::MouseButtonRelease ||
               anyEvent->type() == QEvent::MouseButtonDblClick ||
               anyEvent->type() == QEvent::MouseMove)
    {
        isMouseEvent = true;
    }
    if (isKeyEvent || isMouseEvent ||
        anyEvent->type() == QEvent::Wheel ||
        anyEvent->type() == QEvent::Enter ||
        anyEvent->type() == QEvent::Leave)
    {
        isKnownInputEvent = true;
    }

    if (lockEventHandling) {
      if (isKnownInputEvent) {
        qWarning("SoQtSceneHandler: Recursive event handling; event was ignored.");
      }
      return;
    }
    lockEventHandling = true;

    if (isMouseEvent && (anyEvent->type() != QEvent::MouseMove)) {
      QMouseEvent* me = ((QMouseEvent*)anyEvent);
      if ((me->pos() != lastEventPosition) ||
          !lastEventPositionValid || (lastPositionEventHandler == nullptr))
      {
        // synthesize event MouseMove to get to press/release position;
        // many OpenInventor nodes only act on the last mouse move before the release,
        // but especially in remote rendering scenarios these positions are not the same
        QMouseEvent synthEvent(QEvent::MouseMove,
                               me->pos(), me->globalPos(), Qt::NoButton, storedButtonState,
                               storedModifierState);
        translateAndSendEvent(&synthEvent);

      }
    }
    // restore modifier state because some key events may not have reached us:
    if (isKeyEvent || isMouseEvent) {
        synthesizeCurrentModifierState (((QInputEvent*)anyEvent)->modifiers());
    }
    // restore button state because some mouse events may not have reached us:
    if (isMouseEvent) {
        synthesizeCurrentButtonState ((QMouseEvent*)anyEvent);
    }
    // pass event to inventor scene:
    translateAndSendEvent(anyEvent);
    // store last button state for comparison (shouldn't really be necessary):
    if (isKeyEvent || isMouseEvent) {
        storedModifierState = ((QInputEvent*)anyEvent)->modifiers();
        if (isKeyEvent) {
            // with modifier key events the modifier mask changes _after_ the event:
            QKeyEvent* ke = ((QKeyEvent*)anyEvent);
            if (ke->key() == Qt::Key_Shift) {
                storedModifierState ^= Qt::ShiftModifier;
            }
            if (ke->key() == Qt::Key_Control) {
                storedModifierState ^= Qt::ControlModifier;
            }
            if (ke->key() == Qt::Key_Alt) {
                storedModifierState ^= Qt::AltModifier;
            }
        }
    }

    lockEventHandling = false;

    if (isMouseEvent) {
        storedButtonState = ((QMouseEvent*)anyEvent)->buttons();
        lastEventPosition = ((QMouseEvent*)anyEvent)->pos();
        lastEventPositionValid = true;
        lastPositionEventHandler = this;
    } else if (anyEvent->type() == QEvent::Leave) {
        lastEventPositionValid = false;
    }
    // always accept mouse and wheel events, so that they are not propagated to parent widgets
    if (isMouseEvent || (anyEvent->type() == QEvent::Wheel)) {
      anyEvent->accept();
    }
}


void SoQtSceneHandler::resendLastMousePosition()
{
    if (lastEventPositionValid && (lastPositionEventHandler == this)) {
      QMouseEvent me(static_cast<QEvent::Type>(SoQtStandardEventTranslator::locationRefreshEventType()),
        lastEventPosition, Qt::NoButton, storedButtonState, storedModifierState);
      processSceneEvent(&me);
    }
}


void
SoQtSceneHandler::synthesizeCurrentButtonState (QMouseEvent* me)
{
    // synthesize input state _before_ this event
    Qt::MouseButtons buttonState = (me->type() == QEvent::MouseMove) ? me->buttons() : (me->buttons() ^ me->button());
    if (buttonState != storedButtonState) {
        // first generate button release events for every button that is different:
        synthesizeButtonState (buttonState, Qt::LeftButton,  me, false);
        synthesizeButtonState (buttonState, Qt::MiddleButton,   me, false);
        synthesizeButtonState (buttonState, Qt::RightButton, me, false);
        // then generate button press events for every button that is different:
        synthesizeButtonState (buttonState, Qt::LeftButton,  me, true);
        synthesizeButtonState (buttonState, Qt::MiddleButton,   me, true);
        synthesizeButtonState (buttonState, Qt::RightButton, me, true);
    }
}


void
SoQtSceneHandler::synthesizeButtonState (Qt::MouseButtons newButtons,
                                         Qt::MouseButton button,
                                         QMouseEvent* me, bool press)
{
    // generate a button press or release event if the button state of the selected button
    // is different and the new state correlates with the "press" flag:
    if ((((storedButtonState ^ newButtons) & button) != 0) &&
        (((newButtons & button) != 0) == press))
    {
        storedButtonState ^= button;
        // the event is generated at the same position as the final event:
        QMouseEvent synthEvent (press ? QEvent::MouseButtonPress : QEvent::MouseButtonRelease,
                                me->pos(), me->globalPos(), button, storedButtonState,
                                me->modifiers());
        translateAndSendEvent(&synthEvent);
    }
}


void
SoQtSceneHandler::synthesizeCurrentModifierState (Qt::KeyboardModifiers modifiers)
{
    if (modifiers != storedModifierState) {
        // first generate key release events for every modifier that is different:
        synthesizeModifierState (modifiers, Qt::ShiftModifier,   Qt::Key_Shift,   false);
        synthesizeModifierState (modifiers, Qt::ControlModifier, Qt::Key_Control, false);
        synthesizeModifierState (modifiers, Qt::AltModifier,     Qt::Key_Alt,     false);
        // then generate key press events for every modifier that is different:
        synthesizeModifierState (modifiers, Qt::ShiftModifier,   Qt::Key_Shift,   true);
        synthesizeModifierState (modifiers, Qt::ControlModifier, Qt::Key_Control, true);
        synthesizeModifierState (modifiers, Qt::AltModifier,     Qt::Key_Alt,     true);
    }
}


void
SoQtSceneHandler::synthesizeModifierState (Qt::KeyboardModifiers newModifiers,
                                           Qt::KeyboardModifier modifier,
                                           Qt::Key keyCode, bool press)
{
    // generate a button press or release event if the button state of the selected button
    // is different and the new state correlates with the "press" flag:
    if ((((storedModifierState ^ newModifiers) & modifier) != 0) &&
        (((newModifiers & modifier) != 0) == press))
    {
        QKeyEvent synthEvent (press ? QEvent::KeyPress : QEvent::KeyRelease, keyCode,
                              storedModifierState);
        storedModifierState ^= modifier;
        translateAndSendEvent(&synthEvent);
    }
}


void
SoQtSceneHandler::translateAndSendEvent(QEvent *anyevent)
{
    // send event to the scene
    const SoEvent *soevent = translateEvent (anyevent);

    // if no translation possible, return...
    if (! soevent) { return; }

    // now send the event to
    // the regular scene graph.
    SbBool handled = sceneMgr->processEvent (soevent);
    // now check to make sure that we updated the handle event action
    // with the current window the very first time. This is needed
    // because the SoState does not exists until the action is
    // applied, and we only update those during enter/leave notify.
    if (firstEvent) {
      SoState *state = sceneMgr->getHandleEventAction()->getState();
      if (state) {
        setWindowElement(state);
        firstEvent = FALSE;
      }
    }

    // consume event if it was handled
    anyevent->setAccepted(handled);
}

void SoQtSceneHandler::registerDevice (SoQtDevice *d)
{
    int index = deviceList.indexOf (d);
    if (index < 0) {
        // only append if not yet contained in list
        deviceList.append (d);
    }

    // tell the device the window size
    d->setWindowSize(currentSize);
    d->setDevicePixelRatio(devicePixelRatio);

    // Tell the device to register event interest for our widget
    QWidget *w = getDeviceWidget();
    if (w != nullptr) {
        d->enable(w, /*(SoQtEventHandler) SoQtGLWidget::eventHandler*/ nullptr, (void *) this);
    }
}

void SoQtSceneHandler::unregisterDevice (SoQtDevice *d)
{
    int index = deviceList.indexOf (d);
    if (index < 0) {
        return;
    }

    deviceList.removeAt (deviceList.indexOf (d));

    // Tell the device to unregister event interest for our widget
    QWidget *w = getDeviceWidget();
    if (w != nullptr) {
        d->disable(w, /*(SoQtEventHandler) SoQtGLWidget::eventHandler*/ nullptr, (void *) this);
    }
}

void SoQtSceneHandler::detachAllDevices()
{
  QWidget *w = getDeviceWidget();
  if (!w)
    return;

  for (int i=0; i < deviceList.count(); i++) {
    deviceList[i]->disable(w, /*(SoQtEventHandler) SoQtGLWidget::eventHandler*/ nullptr, (void *) this);
  }
}

void SoQtSceneHandler::reattachAllDevices()
{
  QWidget *w = getDeviceWidget();
  if (!w)
    return;

  for (int i=0; i < deviceList.count(); i++) {
    deviceList[i]->enable(w, /*(SoQtEventHandler) SoQtGLWidget::eventHandler*/ nullptr, (void *) this);
  }
}

void SoQtSceneHandler::registerNamedDevices(const SbString &d)
{
  SoTypeList registeredDeviceTypes;
  foreach (SoQtDevice* dev, deviceList) {
    registeredDeviceTypes.append(dev->getTypeId());
  }

  QStringList devices = QString(QLatin1String(d.getString())).split(QRegularExpression("\\s+"), Qt::SkipEmptyParts);
  foreach (QString dev, devices) {
    SoType devType = SoType::fromName(dev.toLatin1().constData());
    if (devType == SoType::badType()) {
      SoDebugError::post("SoQtSceneHandler::setInputDevicesList", "Type '%s' is unknown to the runtime type system", dev.toLatin1().constData());

      SoTypeList knownDevices;
      if (SoType::getAllDerivedFrom(SoQtDevice::getClassTypeId(), knownDevices) > 0) {
        for (int i = 0; i < knownDevices.getLength(); ++i) {
          if (knownDevices[i].canCreateInstance()) {
            SoDebugError::postInfo("SoQtSceneHandler::setInputDevicesList", "A known device type name is '%s'", knownDevices[i].getName().getString());
          }
        }
      }
    }
    else {
      if (! devType.isDerivedFrom(SoQtDevice::getClassTypeId())) {
        SoDebugError::post("SoQtSceneHandler::setInputDevicesList", "Type '%s' is no descendant of SoQtDevice", dev.toLatin1().constData());
      }
      else {
        if (registeredDeviceTypes.find(devType) >= 0) {
          SoDebugError::post("SoQtSceneHandler::setInputDevicesList", "A device of type '%s' is already registered", dev.toLatin1().constData());
        }
        else {
          if (! devType.canCreateInstance()) {
            SoDebugError::post("SoQtSceneHandler::setInputDevicesList", "Type '%s' cannot create an instance", dev.toLatin1().constData());
          }
          else {
            SoQtDevice *qd = (SoQtDevice *)devType.createInstance();
            if (! qd) {
              SoDebugError::post("SoQtSceneHandler::setInputDevicesList", "Could not create an instance of type '%s'", dev.toLatin1().constData());
            }
            else {
              registerDevice(qd);
            }
          }
        }
      }
    }
  }
}

void
SoQtSceneHandler::initializeScene(int shareID)
{
    sceneMgr->reinitialize();

    SoGLRenderAction *ra = sceneMgr->getGLRenderAction();
    ra->setCacheContext(shareID);
}

void
SoQtSceneHandler::resizeScene(int width, int height, double devicePixelRatio, bool sizeIncorporatesRatio)
{
  this->devicePixelRatio = devicePixelRatio;

  currentSize = SbVec2s(width, height) * (sizeIncorporatesRatio ? 1.0 : devicePixelRatio);

  sceneMgr->setWindowSize(currentSize);

  for (int i=0; i < deviceList.count(); i++) {
    deviceList[i]->setWindowSize(currentSize);
    deviceList[i]->setDevicePixelRatio(devicePixelRatio);
  }
}

void
SoQtSceneHandler::activate()
{
    // if autoRedraw is off, then don't attach the scene sensor
    if (! autoRedraw) {
        return;
    }

    // Activate the scene manager
    sceneMgr->activate();
}

void
SoQtSceneHandler::deactivate()
{
    // detach sensors
    sceneMgr->deactivate();
}

void
SoQtSceneHandler::setAutoRedraw(SbBool flag)
{
    if (flag == autoRedraw) {
        return;
    }

    autoRedraw = flag;

    if (autoRedraw) {
        if (isSceneVisible()) {
            activate();
        }
    } else {
        deactivate();
    }
}

void SoQtSceneHandler::paintScene()
{
  // Reset the lazy element state to make sure that
  // Inventor resends all GL state and does not
  // expect the GL state to be like it was on the last
  // paintScene() call. This is important when rendering
  // to FBOs on a shared GL context.
  // It has the performance overhead of resending more GL
  // state, but that is insignificant on todays hardware/drivers.
  SoState* state = sceneMgr->getGLRenderAction()->getState();
  if (state) {
    SoGLLazyElement* glLazyElement = SoGLLazyElement::getInstance(state);
    if (glLazyElement) {
      glLazyElement->reset(state, SoGLLazyElement::ALL_MASK);
    }
  }

  resendLastMousePosition();
  actualRedraw();
}

void
SoQtSceneHandler::actualRedraw()
{
    sceneMgr->render (clearFirst);
}

bool
SoQtSceneHandler::setAntialiasing (SbBool smoothing, int numPasses)
{
    SoGLRenderAction *ra = getGLRenderAction();

    if (smoothing != ra->isSmoothing() || numPasses != ra->getNumPasses()) {

        // this must probably set first (don't know when the redraw happens
        // from the format change:
        sceneMgr->setAntialiasing(smoothing, numPasses);
        return true;
    } else {
        return false;
    }
}

void
SoQtSceneHandler::scheduleRedraw()
{
    if (isAutoRedraw()) {
        sceneMgr->scheduleRedraw();
    } else {
        updateScene();
    }
}


void
SoQtSceneHandler::redrawOnSelectionChange (SoSelection *s)
{
    if (s != selection) {

        // Remove our callback from old selection node
        if (selection != nullptr) {
            selection->removeChangeCallback (SoQtSceneHandler::selectionChangeCB, this);
            // Unref the old selection node
            selection->unref();
        }
        selection = s;
        // Add our callback to this selection node. (We've already ref'd this new sel node)
        if (selection != nullptr) {
            selection->addChangeCallback (SoQtSceneHandler::selectionChangeCB, this);
            // Ref the new selection node
            selection->ref();
        }
    }
}

void
SoQtSceneHandler::selectionChangeCB(void *p, SoSelection *)
{
    ((SoQtSceneHandler *)p)->scheduleRedraw();
}


void
SoQtSceneHandler::renderCB(void *p, SoSceneManager *)
{
    ((SoQtSceneHandler *)p)->updateScene();
}


const SoEvent *
SoQtSceneHandler::translateEvent(QEvent *anyEvent)
{
    // send event to the scene
    const SoEvent *soevent = nullptr;

    // process list of special devices
    for (int i = 0; (soevent == nullptr) && (i < deviceList.count()); i++) {
        SoQtDevice *device = deviceList[i];
        soevent = device->translateEvent (anyEvent);
    }

    // if no device found, try standard translations for mouse and keyboard
    if (! soevent) {
        soevent = translateStdEvent (anyEvent);
    } else {
        // Set event time stamp in any case, otherwise we might risk
        // inconsistent time stamps between internally and externally
        // translated events. Since QEvent has no time stamps, we must do
        // something like this in any case...
        // [Casting to non-const is ugly, but changing the signature of
        // SoQtDevice::translateEvent is somewhat too much hassle. Setting
        // the time on the event should be possible in any case.]
        ((SoEvent*)soevent)->setTime (SbTime::getTimeOfDay());
    }

    return soevent;
}

const SoEvent *
SoQtSceneHandler::translateStdEvent(QEvent *xe)
{
  return standardEventTranslator.translateEvent(xe, currentSize, devicePixelRatio);
}
