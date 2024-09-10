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

#include <Inventor/Qt/SoQtStandardEventTranslator.h>
#include <QMouseEvent>
#include <QKeyEvent>
#include <QApplication>

SoQtStandardEventTranslator::SoQtStandardEventTranslator()
:lastMouseX(-1)
,lastMouseY(-1)
,lastMouseButtons(Qt::NoButton)
{

}

int SoQtStandardEventTranslator::locationRefreshEventType()
{
  static int typeNum = -1;
  if (typeNum == -1) {
    typeNum = QEvent::registerEventType();
  }
  return typeNum;
}

const SoEvent* SoQtStandardEventTranslator::translateEvent(QEvent *anyEvent, short viewportWidth, short viewportHeight, double devicePixelRatio)
{
  return translateEvent(anyEvent,SbVec2s(viewportWidth,viewportHeight),devicePixelRatio);
}

const SoEvent *
SoQtStandardEventTranslator::translateEvent(QEvent *anyEvent, const SbVec2s& viewportSize, double devicePixelRatio)
{
  SoEvent *event = nullptr;

  QMouseEvent *mouseEvent = nullptr;
  QWheelEvent *wheelEvent = nullptr;

  // adapt mouse pointer coordinates for hi-res screens:
  if (anyEvent->type() == QEvent::MouseButtonPress ||
      anyEvent->type() == QEvent::MouseButtonRelease ||
      anyEvent->type() == QEvent::MouseButtonDblClick ||
      anyEvent->type() == QEvent::MouseMove ||
      anyEvent->type() == locationRefreshEventType()) {
    QMouseEvent *me = static_cast<QMouseEvent *>(anyEvent);
    mouseEvent = new QMouseEvent(anyEvent->type(), me->pos() * devicePixelRatio, me->button(), me->buttons(), me->modifiers(), me->pointingDevice());
  }
  else if (anyEvent->type() == QEvent::Wheel) {
    QWheelEvent* we = static_cast<QWheelEvent *>(anyEvent);
    wheelEvent = new QWheelEvent(we->position() * devicePixelRatio, we->globalPosition(), we->pixelDelta() * devicePixelRatio,
      we->angleDelta(), we->buttons(), we->modifiers(),
      we->phase(), we->inverted(), we->source(), we->pointingDevice());
  }

  if (anyEvent->type() == locationRefreshEventType()) {
    event = translateLocationRefreshEvent(mouseEvent, viewportSize);
  } else {
    // switch on event type
    switch (anyEvent->type()) {
      case QEvent::MouseButtonPress:
      case QEvent::MouseButtonDblClick:
        event = translateButtonEvent(mouseEvent, SoButtonEvent::DOWN, viewportSize);
        break;
      case QEvent::MouseButtonRelease:
        event = translateButtonEvent(mouseEvent, SoButtonEvent::UP, viewportSize);
        break;
      case QEvent::MouseMove:
        event = translateMotionEvent(mouseEvent, viewportSize);
        break;
      case QEvent::KeyPress:
        event = translateKeyEvent((QKeyEvent *) anyEvent, SoButtonEvent::DOWN, viewportSize);
        break;
      case QEvent::KeyRelease:
        event = translateKeyEvent((QKeyEvent *) anyEvent, SoButtonEvent::UP, viewportSize);
        break;
      case QEvent::Wheel:
        event = translateWheelEvent(wheelEvent, viewportSize);
        break;
      case QEvent::Enter:
      case QEvent::Leave:
        event = translateEnterLeaveEvent(anyEvent);
      default:
        break;
    }
  }

  delete mouseEvent;
  delete wheelEvent;

  return event;
}


void SoQtStandardEventTranslator::fillInEventState (SoEvent* event, QInputEvent* ie, const SbVec2s& viewportSize)
{
  // mirror y-position:
  event->setPosition (SbVec2s (lastMouseX, viewportSize[1] - lastMouseY));
  event->setTime (SbTime::getTimeOfDay());
  event->setShiftDown (ie->modifiers() & Qt::ShiftModifier);
  event->setCtrlDown (ie->modifiers() & Qt::ControlModifier);
  event->setAltDown (ie->modifiers() & Qt::AltModifier);

  int buttonMask = 0;
  if (lastMouseButtons & Qt::LeftButton) {
    buttonMask |= SoEvent::LEFT_MOUSEBUTTON_MASK;
  }
  if (lastMouseButtons & Qt::MiddleButton) {
    buttonMask |= SoEvent::MIDDLE_MOUSEBUTTON_MASK;
  }
  if (lastMouseButtons & Qt::RightButton) {
    buttonMask |= SoEvent::RIGHT_MOUSEBUTTON_MASK;
  }
  event->setMouseButtonMask(buttonMask);
}


SoMouseWheelEvent* SoQtStandardEventTranslator::translateWheelEvent(QWheelEvent* wevent, const SbVec2s& viewportSize)
{
  static bool environmentRead = false;
  static bool roundUpWheelDelta = false;
  if (!environmentRead) {
    environmentRead = true;
    roundUpWheelDelta = qEnvironmentVariableIsSet("MLAB_SOQT_ROUNDUP_WHEEL_DELTA");
  }
  lastMouseX = wevent->position().toPoint().x();
  lastMouseY = wevent->position().toPoint().y();
  // Qt 5.12.3 has a bug that returns a wrong buttons state in wheel events on Windows if the
  // user previously clicked on the window title bar - as a workaround we ignore this and simply
  // rely on the state provided by previous QMouseEvents:
  // lastMouseButtons = wevent->buttons();

  int delta{};
  SoMouseWheelEvent::Orientation orientation{};
  QPoint angleDelta = wevent->angleDelta();
  if (angleDelta.y()) {
    delta = angleDelta.y();
    orientation = SoMouseWheelEvent::VERTICAL;
  }
  else {
    delta = angleDelta.x();
    orientation = SoMouseWheelEvent::HORIZONTAL;
  }
  if (roundUpWheelDelta && qAbs(delta) < 120) {
    // apply fix for TouchStrip of WACOM monitor;
    // NOTE: this would collide with the Apple Magic/Mighty Mouse handling
    delta = (delta < 0) ? -120 : 120;
  }
  mouseWheelEvent.setWheelRotation(delta);
  mouseWheelEvent.setWheelOrientation(orientation);

  fillInEventState(&mouseWheelEvent, wevent, viewportSize);

  wevent->accept();

  return &mouseWheelEvent;
}

SoEnterLeaveEvent* SoQtStandardEventTranslator::translateEnterLeaveEvent(QEvent* event)
{
  // enter/leave events are not QInputEvents, so we have to get the
  // keyboard modifiers elsewhere:
  Qt::KeyboardModifiers modifiers = QApplication::keyboardModifiers();
  enterLeaveEvent.setEventType((event->type() == QEvent::Enter)
    ? SoEnterLeaveEvent::SO_ENTER_EVENT
    : SoEnterLeaveEvent::SO_LEAVE_EVENT);

  // Modifiers
  enterLeaveEvent.setShiftDown((modifiers & Qt::ShiftModifier) != 0);
  enterLeaveEvent.setCtrlDown((modifiers & Qt::ControlModifier) != 0);
  enterLeaveEvent.setAltDown((modifiers & Qt::AltModifier) != 0);

  // Position is not used, set it anyways...
  enterLeaveEvent.setPosition(SbVec2s(0, 0));

  enterLeaveEvent.setTime(SbTime::getTimeOfDay());
  return &enterLeaveEvent;
}

SoMouseButtonEvent *
SoQtStandardEventTranslator::translateButtonEvent (QMouseEvent *be, SoButtonEvent::State whichState, const SbVec2s& viewportSize)
{
  SoMouseButtonEvent::Button whichButton;
  switch (be->button()) {
    case Qt::LeftButton:
      whichButton = SoMouseButtonEvent::LEFT_BUTTON;
      break;
    case Qt::MiddleButton:
      whichButton = SoMouseButtonEvent::MIDDLE_BUTTON;
      break;
    case Qt::RightButton:
      whichButton = SoMouseButtonEvent::RIGHT_BUTTON;
      break;
    default:
      whichButton = SoMouseButtonEvent::ANY;
  }
  lastMouseX = be->pos().x();
  lastMouseY = be->pos().y();
  lastMouseButtons = be->buttons();
  fillInEventState (&buttonEvent, be, viewportSize);

  buttonEvent.setState (whichState);
  buttonEvent.setButton (whichButton);
  buttonEvent.setIsDoubleClick(be->type() == QEvent::MouseButtonDblClick);

  return &buttonEvent;
}


SoLocation2Event *
SoQtStandardEventTranslator::translateMotionEvent (QMouseEvent *me, const SbVec2s& viewportSize)
{
  lastMouseX = me->pos().x();
  lastMouseY = me->pos().y();
  lastMouseButtons = me->buttons();
  fillInEventState (&loc2Event, me, viewportSize);

  //    qDebug("mouse move %d %d", loc2Event->getPosition()[0],loc2Event->getPosition()[1]);
  return &loc2Event;
}

SoLocation2Event *
SoQtStandardEventTranslator::translateLocationRefreshEvent (QMouseEvent *me, const SbVec2s& viewportSize)
{
  fillInEventState (&loc2RefreshEvent, me, viewportSize);

  //    qDebug("location refresh %d %d", loc2Event->getPosition()[0],loc2Event->getPosition()[1]);
  return &loc2RefreshEvent;
}

SoKeyboardEvent::Key lookupKey (int qtKeyCode, bool keyPad)
{
  // NOTE: SoKeyboardConstants.h has provided an exact mapping
  // from X11/keysymdef.h for keyboard symbols. So this file was
  // referenced for missing key codes.
  // some key codes have been skipped out of lazyness...
  if (keyPad) {
    // keypad keys are marked with a modifier flag under Qt
    switch (qtKeyCode) {
            case Qt::Key_Comma:   // better safe than sorry
            case Qt::Key_Period:  return SoKeyboardEvent::PAD_PERIOD;
            case Qt::Key_0:       return SoKeyboardEvent::PAD_0;
            case Qt::Key_1:       return SoKeyboardEvent::PAD_1;
            case Qt::Key_2:       return SoKeyboardEvent::PAD_2;
            case Qt::Key_3:       return SoKeyboardEvent::PAD_3;
            case Qt::Key_4:       return SoKeyboardEvent::PAD_4;
            case Qt::Key_5:       return SoKeyboardEvent::PAD_5;
            case Qt::Key_6:       return SoKeyboardEvent::PAD_6;
            case Qt::Key_7:       return SoKeyboardEvent::PAD_7;
            case Qt::Key_8:       return SoKeyboardEvent::PAD_8;
            case Qt::Key_9:       return SoKeyboardEvent::PAD_9;
            case Qt::Key_Plus:    return SoKeyboardEvent::PAD_ADD;
            case Qt::Key_Minus:   return SoKeyboardEvent::PAD_SUBTRACT;
            case Qt::Key_Asterisk: return SoKeyboardEvent::PAD_MULTIPLY;
            case Qt::Key_Slash:   return SoKeyboardEvent::PAD_DIVIDE;
            case Qt::Key_Enter:   return SoKeyboardEvent::PAD_ENTER;
              // Qt (Version 4.2.2) doesn't get the numpad modifier right for MacOSX:
#if !defined(__APPLE__)
              // Keypad-Keys without numlock, but we return the number codes anyway:
            case Qt::Key_Delete:  return SoKeyboardEvent::PAD_PERIOD;
            case Qt::Key_Insert:  return SoKeyboardEvent::PAD_0;
            case Qt::Key_End:     return SoKeyboardEvent::PAD_1;
            case Qt::Key_Down:    return SoKeyboardEvent::PAD_2;
            case Qt::Key_PageDown: return SoKeyboardEvent::PAD_3;
            case Qt::Key_Left:    return SoKeyboardEvent::PAD_4;
            case Qt::Key_Clear:   return SoKeyboardEvent::PAD_5;
            case Qt::Key_Right:   return SoKeyboardEvent::PAD_6;
            case Qt::Key_Home:    return SoKeyboardEvent::PAD_7;
            case Qt::Key_Up:      return SoKeyboardEvent::PAD_8;
            case Qt::Key_PageUp:  return SoKeyboardEvent::PAD_9;
              // These ones you normally don't get with a PC keyboard:
            case Qt::Key_F1:      return SoKeyboardEvent::PAD_F1;
            case Qt::Key_F2:      return SoKeyboardEvent::PAD_F2;
            case Qt::Key_F3:      return SoKeyboardEvent::PAD_F3;
            case Qt::Key_F4:      return SoKeyboardEvent::PAD_F4;
            case Qt::Key_Space:   return SoKeyboardEvent::PAD_SPACE;
            case Qt::Key_Tab:     return SoKeyboardEvent::PAD_TAB;
#endif
    }
  }
  switch (qtKeyCode) {
        case Qt::Key_Escape:      return SoKeyboardEvent::ESCAPE;
        case Qt::Key_Tab:         return SoKeyboardEvent::TAB;
          // case Qt::Key_Backtab:     return SoKeyboardEvent::ANY;
        case Qt::Key_Backspace:   return SoKeyboardEvent::BACKSPACE;
        case Qt::Key_Return:      return SoKeyboardEvent::RETURN;
        case Qt::Key_Enter:       return SoKeyboardEvent::ENTER;
        case Qt::Key_Insert:      return SoKeyboardEvent::INSERT;
        case Qt::Key_Delete:      return (SoKeyboardEvent::Key) 0xFFFF; // taken from X11/keysymdef.h
        case Qt::Key_Pause:       return SoKeyboardEvent::PAUSE;
        case Qt::Key_Print:       return SoKeyboardEvent::PRINT;
        case Qt::Key_SysReq:      return (SoKeyboardEvent::Key) 0xFF15; // taken from X11/keysymdef.h
          // case Qt::Key_Clear:       return SoKeyboardEvent::ANY;
        case Qt::Key_Home:        return SoKeyboardEvent::HOME;
        case Qt::Key_End:         return SoKeyboardEvent::END;
        case Qt::Key_Left:        return SoKeyboardEvent::LEFT_ARROW;
        case Qt::Key_Up:          return SoKeyboardEvent::UP_ARROW;
        case Qt::Key_Right:       return SoKeyboardEvent::RIGHT_ARROW;
        case Qt::Key_Down:        return SoKeyboardEvent::DOWN_ARROW;
        case Qt::Key_PageUp:      return SoKeyboardEvent::PAGE_UP;
        case Qt::Key_PageDown:    return SoKeyboardEvent::PAGE_DOWN;
        case Qt::Key_Shift:       return SoKeyboardEvent::LEFT_SHIFT;
        case Qt::Key_Control:     return SoKeyboardEvent::LEFT_CONTROL;
        case Qt::Key_Meta:        return (SoKeyboardEvent::Key) 0xFFE7; // taken from X11/keysymdef.h
        case Qt::Key_Alt:         return SoKeyboardEvent::LEFT_ALT;
        case Qt::Key_AltGr:       return SoKeyboardEvent::RIGHT_ALT;
        case Qt::Key_CapsLock:    return SoKeyboardEvent::CAPS_LOCK;
        case Qt::Key_NumLock:     return SoKeyboardEvent::NUM_LOCK;
        case Qt::Key_ScrollLock:  return SoKeyboardEvent::SCROLL_LOCK;
        case Qt::Key_Super_L:     return (SoKeyboardEvent::Key) 0xFFEB; // taken from X11/keysymdef.h
        case Qt::Key_Super_R:     return (SoKeyboardEvent::Key) 0xFFEC; // taken from X11/keysymdef.h
        case Qt::Key_Menu:        return (SoKeyboardEvent::Key) 0xFF67; // taken from X11/keysymdef.h
        case Qt::Key_Hyper_L:     return (SoKeyboardEvent::Key) 0xFFED; // taken from X11/keysymdef.h
        case Qt::Key_Hyper_R:     return (SoKeyboardEvent::Key) 0xFFEE; // taken from X11/keysymdef.h
        case Qt::Key_Help:        return (SoKeyboardEvent::Key) 0xFF6A; // taken from X11/keysymdef.h
          // case Qt::Key_Direction_L: return SoKeyboardEvent::ANY;
          // case Qt::Key_Direction_R: return SoKeyboardEvent::ANY;
        case Qt::Key_A:           return SoKeyboardEvent::A;
        case Qt::Key_B:           return SoKeyboardEvent::B;
        case Qt::Key_C:           return SoKeyboardEvent::C;
        case Qt::Key_D:           return SoKeyboardEvent::D;
        case Qt::Key_E:           return SoKeyboardEvent::E;
        case Qt::Key_F:           return SoKeyboardEvent::F;
        case Qt::Key_G:           return SoKeyboardEvent::G;
        case Qt::Key_H:           return SoKeyboardEvent::H;
        case Qt::Key_I:           return SoKeyboardEvent::I;
        case Qt::Key_J:           return SoKeyboardEvent::J;
        case Qt::Key_K:           return SoKeyboardEvent::K;
        case Qt::Key_L:           return SoKeyboardEvent::L;
        case Qt::Key_M:           return SoKeyboardEvent::M;
        case Qt::Key_N:           return SoKeyboardEvent::N;
        case Qt::Key_O:           return SoKeyboardEvent::O;
        case Qt::Key_P:           return SoKeyboardEvent::P;
        case Qt::Key_Q:           return SoKeyboardEvent::Q;
        case Qt::Key_R:           return SoKeyboardEvent::R;
        case Qt::Key_S:           return SoKeyboardEvent::S;
        case Qt::Key_T:           return SoKeyboardEvent::T;
        case Qt::Key_U:           return SoKeyboardEvent::U;
        case Qt::Key_V:           return SoKeyboardEvent::V;
        case Qt::Key_W:           return SoKeyboardEvent::W;
        case Qt::Key_X:           return SoKeyboardEvent::X;
        case Qt::Key_Y:           return SoKeyboardEvent::Y;
        case Qt::Key_Z:           return SoKeyboardEvent::Z;
        case Qt::Key_Multi_key:         return (SoKeyboardEvent::Key) 0xFF20; // taken from X11/keysymdef.h
        case Qt::Key_Codeinput:         return (SoKeyboardEvent::Key) 0xFF37; // taken from X11/keysymdef.h
        case Qt::Key_SingleCandidate:   return (SoKeyboardEvent::Key) 0xFF3C; // taken from X11/keysymdef.h
        case Qt::Key_MultipleCandidate: return (SoKeyboardEvent::Key) 0xFF3D; // taken from X11/keysymdef.h
        case Qt::Key_PreviousCandidate: return (SoKeyboardEvent::Key) 0xFF3E; // taken from X11/keysymdef.h
        case Qt::Key_Mode_switch:       return (SoKeyboardEvent::Key) 0xFF7E; // taken from X11/keysymdef.h
        default:
          if (qtKeyCode >= Qt::Key_F1 && qtKeyCode <= Qt::Key_F35) {
            // handle function keys economically
            return (SoKeyboardEvent::Key) (qtKeyCode - Qt::Key_F1 + SoKeyboardEvent::F1);
          } else if (((qtKeyCode >= 0x20) && (qtKeyCode <= 0x7f)) ||
                     ((qtKeyCode >= 0xa0) && (qtKeyCode <= 0xff)))
          {
            // ascii+latin1 key codes are the same, except for the
            // letters A-Z (upper vs. lower case) which are handled above
            return (SoKeyboardEvent::Key) qtKeyCode;
          } else {
            return SoKeyboardEvent::ANY;
          }
  }
}

SoKeyboardEvent *
SoQtStandardEventTranslator::translateKeyEvent (QKeyEvent *ke, SoButtonEvent::State whichState, const SbVec2s& viewportSize)
{
  SoKeyboardEvent::Key whichKey = lookupKey (ke->key(), ke->modifiers() & Qt::KeypadModifier);
  fillInEventState (&keyEvent, ke, viewportSize);
  // Qt returns the modifiers _before_ the event, but we need them after the event:
  if (ke->key() == Qt::Key_Alt) {
    keyEvent.setAltDown (whichState == SoButtonEvent::DOWN);
  }
  if (ke->key() == Qt::Key_Control) {
    keyEvent.setCtrlDown (whichState == SoButtonEvent::DOWN);
  }
  if (ke->key() == Qt::Key_Shift) {
    keyEvent.setShiftDown (whichState == SoButtonEvent::DOWN);
  }
  keyEvent.setState (whichState);
  keyEvent.setKey (whichKey);
  keyEvent.setIsAutoRepeat(ke->isAutoRepeat());
  return &keyEvent;
}
