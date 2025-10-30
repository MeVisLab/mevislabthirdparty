#include "inventor_events0.h"
#include <Inventor/SbLinear.h>
#include <Inventor/SbTime.h>
#include <Inventor/SbViewportRegion.h>
#include <Inventor/SoType.h>
#include <Inventor/events/SoEvent.h>
#include <PythonQtConversion.h>
#include <PythonQtMethodInfo.h>
#include <PythonQtSignalReceiver.h>
#include <QVariant>

PythonQtShell_SoButtonEvent::~PythonQtShell_SoButtonEvent() {
  PythonQtPrivate* priv = PythonQt::priv();
  if (priv) { priv->shellClassDeleted(this); }
}
SoButtonEvent* PythonQtWrapper_SoButtonEvent::new_SoButtonEvent()
{ 
return new PythonQtShell_SoButtonEvent(); }

SoType  PythonQtWrapper_SoButtonEvent::static_SoButtonEvent_getClassTypeId()
{
  return (SoButtonEvent::getClassTypeId());
}

SoButtonEvent::State  PythonQtWrapper_SoButtonEvent::getState(SoButtonEvent* theWrappedObject) const
{
  return ( theWrappedObject->getState());
}

void PythonQtWrapper_SoButtonEvent::setState(SoButtonEvent* theWrappedObject, SoButtonEvent::State  s)
{
  ( theWrappedObject->setState(s));
}



PythonQtShell_SoEvent::~PythonQtShell_SoEvent() {
  PythonQtPrivate* priv = PythonQt::priv();
  if (priv) { priv->shellClassDeleted(this); }
}
SoEvent* PythonQtWrapper_SoEvent::new_SoEvent()
{ 
return new PythonQtShell_SoEvent(); }

SoType  PythonQtWrapper_SoEvent::static_SoEvent_getClassTypeId()
{
  return (SoEvent::getClassTypeId());
}

int  PythonQtWrapper_SoEvent::getMouseButtonMask(SoEvent* theWrappedObject) const
{
  return ( theWrappedObject->getMouseButtonMask());
}

const SbVec2f*  PythonQtWrapper_SoEvent::getNormalizedPosition(SoEvent* theWrappedObject, const SbViewportRegion&  vpRgn) const
{
  return &( theWrappedObject->getNormalizedPosition(vpRgn));
}

const SbVec2s*  PythonQtWrapper_SoEvent::getPosition(SoEvent* theWrappedObject) const
{
  return &( theWrappedObject->getPosition());
}

const SbVec2s*  PythonQtWrapper_SoEvent::getPosition(SoEvent* theWrappedObject, const SbViewportRegion&  vpRgn) const
{
  return &( theWrappedObject->getPosition(vpRgn));
}

SbTime  PythonQtWrapper_SoEvent::getTime(SoEvent* theWrappedObject) const
{
  return ( theWrappedObject->getTime());
}

bool  PythonQtWrapper_SoEvent::isOfType(SoEvent* theWrappedObject, SoType  type) const
{
  return ( theWrappedObject->isOfType(type));
}

void PythonQtWrapper_SoEvent::setAltDown(SoEvent* theWrappedObject, bool  isDown)
{
  ( theWrappedObject->setAltDown(isDown));
}

void PythonQtWrapper_SoEvent::setCtrlDown(SoEvent* theWrappedObject, bool  isDown)
{
  ( theWrappedObject->setCtrlDown(isDown));
}

void PythonQtWrapper_SoEvent::setMouseButtonMask(SoEvent* theWrappedObject, int  mask)
{
  ( theWrappedObject->setMouseButtonMask(mask));
}

void PythonQtWrapper_SoEvent::setPosition(SoEvent* theWrappedObject, const SbVec2s&  p)
{
  ( theWrappedObject->setPosition(p));
}

void PythonQtWrapper_SoEvent::setShiftDown(SoEvent* theWrappedObject, bool  isDown)
{
  ( theWrappedObject->setShiftDown(isDown));
}

void PythonQtWrapper_SoEvent::setTime(SoEvent* theWrappedObject, SbTime  t)
{
  ( theWrappedObject->setTime(t));
}

bool  PythonQtWrapper_SoEvent::wasAltDown(SoEvent* theWrappedObject) const
{
  return ( theWrappedObject->wasAltDown());
}

bool  PythonQtWrapper_SoEvent::wasCtrlDown(SoEvent* theWrappedObject) const
{
  return ( theWrappedObject->wasCtrlDown());
}

bool  PythonQtWrapper_SoEvent::wasShiftDown(SoEvent* theWrappedObject) const
{
  return ( theWrappedObject->wasShiftDown());
}



PythonQtShell_SoKeyboardEvent::~PythonQtShell_SoKeyboardEvent() {
  PythonQtPrivate* priv = PythonQt::priv();
  if (priv) { priv->shellClassDeleted(this); }
}
SoKeyboardEvent* PythonQtWrapper_SoKeyboardEvent::new_SoKeyboardEvent()
{ 
return new PythonQtShell_SoKeyboardEvent(); }

SoType  PythonQtWrapper_SoKeyboardEvent::static_SoKeyboardEvent_getClassTypeId()
{
  return (SoKeyboardEvent::getClassTypeId());
}

SoKeyboardEvent::Key  PythonQtWrapper_SoKeyboardEvent::getKey(SoKeyboardEvent* theWrappedObject) const
{
  return ( theWrappedObject->getKey());
}

char  PythonQtWrapper_SoKeyboardEvent::getPrintableCharacter(SoKeyboardEvent* theWrappedObject) const
{
  return ( theWrappedObject->getPrintableCharacter());
}

bool  PythonQtWrapper_SoKeyboardEvent::isAutoRepeat(SoKeyboardEvent* theWrappedObject) const
{
  return ( theWrappedObject->isAutoRepeat());
}

bool  PythonQtWrapper_SoKeyboardEvent::static_SoKeyboardEvent_isKeyPressEvent(const SoEvent*  e, SoKeyboardEvent::Key  whichKey)
{
  return (SoKeyboardEvent::isKeyPressEvent(e, whichKey));
}

bool  PythonQtWrapper_SoKeyboardEvent::static_SoKeyboardEvent_isKeyReleaseEvent(const SoEvent*  e, SoKeyboardEvent::Key  whichKey)
{
  return (SoKeyboardEvent::isKeyReleaseEvent(e, whichKey));
}

void PythonQtWrapper_SoKeyboardEvent::setIsAutoRepeat(SoKeyboardEvent* theWrappedObject, bool  b)
{
  ( theWrappedObject->setIsAutoRepeat(b));
}

void PythonQtWrapper_SoKeyboardEvent::setKey(SoKeyboardEvent* theWrappedObject, SoKeyboardEvent::Key  whichKey)
{
  ( theWrappedObject->setKey(whichKey));
}



PythonQtShell_SoLocation2Event::~PythonQtShell_SoLocation2Event() {
  PythonQtPrivate* priv = PythonQt::priv();
  if (priv) { priv->shellClassDeleted(this); }
}
SoLocation2Event* PythonQtWrapper_SoLocation2Event::new_SoLocation2Event()
{ 
return new PythonQtShell_SoLocation2Event(); }

SoType  PythonQtWrapper_SoLocation2Event::static_SoLocation2Event_getClassTypeId()
{
  return (SoLocation2Event::getClassTypeId());
}



SoLocation2RefreshEvent* PythonQtWrapper_SoLocation2RefreshEvent::new_SoLocation2RefreshEvent()
{ 
return new SoLocation2RefreshEvent(); }

SoType  PythonQtWrapper_SoLocation2RefreshEvent::static_SoLocation2RefreshEvent_getClassTypeId()
{
  return (SoLocation2RefreshEvent::getClassTypeId());
}



PythonQtShell_SoMotion3Event::~PythonQtShell_SoMotion3Event() {
  PythonQtPrivate* priv = PythonQt::priv();
  if (priv) { priv->shellClassDeleted(this); }
}
SoMotion3Event* PythonQtWrapper_SoMotion3Event::new_SoMotion3Event()
{ 
return new PythonQtShell_SoMotion3Event(); }

SoType  PythonQtWrapper_SoMotion3Event::static_SoMotion3Event_getClassTypeId()
{
  return (SoMotion3Event::getClassTypeId());
}

const SbRotation*  PythonQtWrapper_SoMotion3Event::getRotation(SoMotion3Event* theWrappedObject) const
{
  return &( theWrappedObject->getRotation());
}

const SbVec3f*  PythonQtWrapper_SoMotion3Event::getTranslation(SoMotion3Event* theWrappedObject) const
{
  return &( theWrappedObject->getTranslation());
}

void PythonQtWrapper_SoMotion3Event::setRotation(SoMotion3Event* theWrappedObject, const SbRotation&  r)
{
  ( theWrappedObject->setRotation(r));
}

void PythonQtWrapper_SoMotion3Event::setTranslation(SoMotion3Event* theWrappedObject, const SbVec3f&  t)
{
  ( theWrappedObject->setTranslation(t));
}



PythonQtShell_SoMouseButtonEvent::~PythonQtShell_SoMouseButtonEvent() {
  PythonQtPrivate* priv = PythonQt::priv();
  if (priv) { priv->shellClassDeleted(this); }
}
SoMouseButtonEvent* PythonQtWrapper_SoMouseButtonEvent::new_SoMouseButtonEvent()
{ 
return new PythonQtShell_SoMouseButtonEvent(); }

SoMouseButtonEvent::Button  PythonQtWrapper_SoMouseButtonEvent::getButton(SoMouseButtonEvent* theWrappedObject) const
{
  return ( theWrappedObject->getButton());
}

SoType  PythonQtWrapper_SoMouseButtonEvent::static_SoMouseButtonEvent_getClassTypeId()
{
  return (SoMouseButtonEvent::getClassTypeId());
}

bool  PythonQtWrapper_SoMouseButtonEvent::static_SoMouseButtonEvent_isButtonPressEvent(const SoEvent*  e, SoMouseButtonEvent::Button  whichButton)
{
  return (SoMouseButtonEvent::isButtonPressEvent(e, whichButton));
}

bool  PythonQtWrapper_SoMouseButtonEvent::static_SoMouseButtonEvent_isButtonReleaseEvent(const SoEvent*  e, SoMouseButtonEvent::Button  whichButton)
{
  return (SoMouseButtonEvent::isButtonReleaseEvent(e, whichButton));
}

bool  PythonQtWrapper_SoMouseButtonEvent::isDoubleClick(SoMouseButtonEvent* theWrappedObject) const
{
  return ( theWrappedObject->isDoubleClick());
}

void PythonQtWrapper_SoMouseButtonEvent::setButton(SoMouseButtonEvent* theWrappedObject, SoMouseButtonEvent::Button  b)
{
  ( theWrappedObject->setButton(b));
}

void PythonQtWrapper_SoMouseButtonEvent::setIsDoubleClick(SoMouseButtonEvent* theWrappedObject, bool  b)
{
  ( theWrappedObject->setIsDoubleClick(b));
}



SoMouseWheelEvent* PythonQtWrapper_SoMouseWheelEvent::new_SoMouseWheelEvent()
{ 
return new SoMouseWheelEvent(); }

SoType  PythonQtWrapper_SoMouseWheelEvent::static_SoMouseWheelEvent_getClassTypeId()
{
  return (SoMouseWheelEvent::getClassTypeId());
}

SoMouseWheelEvent::Orientation  PythonQtWrapper_SoMouseWheelEvent::getWheelOrientation(SoMouseWheelEvent* theWrappedObject) const
{
  return ( theWrappedObject->getWheelOrientation());
}

short  PythonQtWrapper_SoMouseWheelEvent::getWheelRotation(SoMouseWheelEvent* theWrappedObject) const
{
  return ( theWrappedObject->getWheelRotation());
}

void PythonQtWrapper_SoMouseWheelEvent::setWheelOrientation(SoMouseWheelEvent* theWrappedObject, SoMouseWheelEvent::Orientation  orient)
{
  ( theWrappedObject->setWheelOrientation(orient));
}

void PythonQtWrapper_SoMouseWheelEvent::setWheelRotation(SoMouseWheelEvent* theWrappedObject, short  rot)
{
  ( theWrappedObject->setWheelRotation(rot));
}



PythonQtShell_SoSpaceballButtonEvent::~PythonQtShell_SoSpaceballButtonEvent() {
  PythonQtPrivate* priv = PythonQt::priv();
  if (priv) { priv->shellClassDeleted(this); }
}
SoSpaceballButtonEvent* PythonQtWrapper_SoSpaceballButtonEvent::new_SoSpaceballButtonEvent()
{ 
return new PythonQtShell_SoSpaceballButtonEvent(); }

SoSpaceballButtonEvent::Button  PythonQtWrapper_SoSpaceballButtonEvent::getButton(SoSpaceballButtonEvent* theWrappedObject) const
{
  return ( theWrappedObject->getButton());
}

SoType  PythonQtWrapper_SoSpaceballButtonEvent::static_SoSpaceballButtonEvent_getClassTypeId()
{
  return (SoSpaceballButtonEvent::getClassTypeId());
}

bool  PythonQtWrapper_SoSpaceballButtonEvent::static_SoSpaceballButtonEvent_isButtonPressEvent(const SoEvent*  e, SoSpaceballButtonEvent::Button  whichButton)
{
  return (SoSpaceballButtonEvent::isButtonPressEvent(e, whichButton));
}

bool  PythonQtWrapper_SoSpaceballButtonEvent::static_SoSpaceballButtonEvent_isButtonReleaseEvent(const SoEvent*  e, SoSpaceballButtonEvent::Button  whichButton)
{
  return (SoSpaceballButtonEvent::isButtonReleaseEvent(e, whichButton));
}

void PythonQtWrapper_SoSpaceballButtonEvent::setButton(SoSpaceballButtonEvent* theWrappedObject, SoSpaceballButtonEvent::Button  b)
{
  ( theWrappedObject->setButton(b));
}


