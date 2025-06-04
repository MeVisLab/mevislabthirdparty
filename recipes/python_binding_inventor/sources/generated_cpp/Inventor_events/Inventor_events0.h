/*************************************************************************************
**
** Copyright 2022, MeVis Medical Solutions AG
**
** GNU LESSER GENERAL PUBLIC LICENSE Version 2.1, February 1999
**
**************************************************************************************/
#include <PythonQt.h>
#include <QObject>
#include <QVariant>
#include <Inventor/SbLinear.h>
#include <Inventor/SbTime.h>
#include <Inventor/SbViewportRegion.h>
#include <Inventor/SoType.h>
#include <Inventor/events/SoButtonEvent.h>
#include <Inventor/events/SoEvent.h>
#include <Inventor/events/SoKeyboardEvent.h>
#include <Inventor/events/SoLocation2Event.h>
#include <Inventor/events/SoLocation2RefreshEvent.h>
#include <Inventor/events/SoMotion3Event.h>
#include <Inventor/events/SoMouseButtonEvent.h>
#include <Inventor/events/SoMouseWheelEvent.h>
#include <Inventor/events/SoSpaceballButtonEvent.h>
#include <stdexcept>



class PythonQtShell_SoButtonEvent : public SoButtonEvent
{
public:
    PythonQtShell_SoButtonEvent():SoButtonEvent(),_wrapper(nullptr) {};

   ~PythonQtShell_SoButtonEvent() override;


  PythonQtInstanceWrapper* _wrapper;
};

class PythonQtWrapper_SoButtonEvent : public QObject
{ Q_OBJECT
public:
Q_ENUMS(State )
enum State{
  UP = SoButtonEvent::UP,   DOWN = SoButtonEvent::DOWN,   UNKNOWN = SoButtonEvent::UNKNOWN};
public Q_SLOTS:
SoButtonEvent* new_SoButtonEvent();
void delete_SoButtonEvent(SoButtonEvent* obj) { delete obj; }
   SoType  static_SoButtonEvent_getClassTypeId();
   SoButtonEvent::State  getState(SoButtonEvent* theWrappedObject) const;
   void setState(SoButtonEvent* theWrappedObject, SoButtonEvent::State  s);
};





class PythonQtShell_SoEvent : public SoEvent
{
public:
    PythonQtShell_SoEvent():SoEvent(),_wrapper(nullptr) {};

   ~PythonQtShell_SoEvent() override;


  PythonQtInstanceWrapper* _wrapper;
};

class PythonQtWrapper_SoEvent : public QObject
{ Q_OBJECT
public:
public Q_SLOTS:
SoEvent* new_SoEvent();
void delete_SoEvent(SoEvent* obj) { delete obj; }
   SoType  static_SoEvent_getClassTypeId();
   int  getMouseButtonMask(SoEvent* theWrappedObject) const;
   const SbVec2f*  getNormalizedPosition(SoEvent* theWrappedObject, const SbViewportRegion&  vpRgn) const;
   const SbVec2s*  getPosition(SoEvent* theWrappedObject) const;
   const SbVec2s*  getPosition(SoEvent* theWrappedObject, const SbViewportRegion&  vpRgn) const;
   SbTime  getTime(SoEvent* theWrappedObject) const;
   bool  isOfType(SoEvent* theWrappedObject, SoType  type) const;
   void setAltDown(SoEvent* theWrappedObject, bool  isDown);
   void setCtrlDown(SoEvent* theWrappedObject, bool  isDown);
   void setMouseButtonMask(SoEvent* theWrappedObject, int  mask);
   void setPosition(SoEvent* theWrappedObject, const SbVec2s&  p);
   void setShiftDown(SoEvent* theWrappedObject, bool  isDown);
   void setTime(SoEvent* theWrappedObject, SbTime  t);
   bool  wasAltDown(SoEvent* theWrappedObject) const;
   bool  wasCtrlDown(SoEvent* theWrappedObject) const;
   bool  wasShiftDown(SoEvent* theWrappedObject) const;
};





class PythonQtShell_SoKeyboardEvent : public SoKeyboardEvent
{
public:
    PythonQtShell_SoKeyboardEvent():SoKeyboardEvent(),_wrapper(nullptr) {};

   ~PythonQtShell_SoKeyboardEvent() override;


  PythonQtInstanceWrapper* _wrapper;
};

class PythonQtWrapper_SoKeyboardEvent : public QObject
{ Q_OBJECT
public:
Q_ENUMS(Key )
enum Key{
  ANY = SoKeyboardEvent::ANY,   LEFT_SHIFT = SoKeyboardEvent::LEFT_SHIFT,   RIGHT_SHIFT = SoKeyboardEvent::RIGHT_SHIFT,   LEFT_CONTROL = SoKeyboardEvent::LEFT_CONTROL,   RIGHT_CONTROL = SoKeyboardEvent::RIGHT_CONTROL,   LEFT_ALT = SoKeyboardEvent::LEFT_ALT,   RIGHT_ALT = SoKeyboardEvent::RIGHT_ALT,   NUMBER_0 = SoKeyboardEvent::NUMBER_0,   NUMBER_1 = SoKeyboardEvent::NUMBER_1,   NUMBER_2 = SoKeyboardEvent::NUMBER_2,   NUMBER_3 = SoKeyboardEvent::NUMBER_3,   NUMBER_4 = SoKeyboardEvent::NUMBER_4,   NUMBER_5 = SoKeyboardEvent::NUMBER_5,   NUMBER_6 = SoKeyboardEvent::NUMBER_6,   NUMBER_7 = SoKeyboardEvent::NUMBER_7,   NUMBER_8 = SoKeyboardEvent::NUMBER_8,   NUMBER_9 = SoKeyboardEvent::NUMBER_9,   A = SoKeyboardEvent::A,   B = SoKeyboardEvent::B,   C = SoKeyboardEvent::C,   D = SoKeyboardEvent::D,   E = SoKeyboardEvent::E,   F = SoKeyboardEvent::F,   G = SoKeyboardEvent::G,   H = SoKeyboardEvent::H,   I = SoKeyboardEvent::I,   J = SoKeyboardEvent::J,   K = SoKeyboardEvent::K,   L = SoKeyboardEvent::L,   M = SoKeyboardEvent::M,   N = SoKeyboardEvent::N,   O = SoKeyboardEvent::O,   P = SoKeyboardEvent::P,   Q = SoKeyboardEvent::Q,   R = SoKeyboardEvent::R,   S = SoKeyboardEvent::S,   T = SoKeyboardEvent::T,   U = SoKeyboardEvent::U,   V = SoKeyboardEvent::V,   W = SoKeyboardEvent::W,   X = SoKeyboardEvent::X,   Y = SoKeyboardEvent::Y,   Z = SoKeyboardEvent::Z,   HOME = SoKeyboardEvent::HOME,   LEFT_ARROW = SoKeyboardEvent::LEFT_ARROW,   UP_ARROW = SoKeyboardEvent::UP_ARROW,   RIGHT_ARROW = SoKeyboardEvent::RIGHT_ARROW,   DOWN_ARROW = SoKeyboardEvent::DOWN_ARROW,   PAGE_UP = SoKeyboardEvent::PAGE_UP,   PAGE_DOWN = SoKeyboardEvent::PAGE_DOWN,   PRIOR = SoKeyboardEvent::PRIOR,   NEXT = SoKeyboardEvent::NEXT,   END = SoKeyboardEvent::END,   PAD_ENTER = SoKeyboardEvent::PAD_ENTER,   PAD_F1 = SoKeyboardEvent::PAD_F1,   PAD_F2 = SoKeyboardEvent::PAD_F2,   PAD_F3 = SoKeyboardEvent::PAD_F3,   PAD_F4 = SoKeyboardEvent::PAD_F4,   PAD_0 = SoKeyboardEvent::PAD_0,   PAD_1 = SoKeyboardEvent::PAD_1,   PAD_2 = SoKeyboardEvent::PAD_2,   PAD_3 = SoKeyboardEvent::PAD_3,   PAD_4 = SoKeyboardEvent::PAD_4,   PAD_5 = SoKeyboardEvent::PAD_5,   PAD_6 = SoKeyboardEvent::PAD_6,   PAD_7 = SoKeyboardEvent::PAD_7,   PAD_8 = SoKeyboardEvent::PAD_8,   PAD_9 = SoKeyboardEvent::PAD_9,   PAD_ADD = SoKeyboardEvent::PAD_ADD,   PAD_SUBTRACT = SoKeyboardEvent::PAD_SUBTRACT,   PAD_MULTIPLY = SoKeyboardEvent::PAD_MULTIPLY,   PAD_DIVIDE = SoKeyboardEvent::PAD_DIVIDE,   PAD_SPACE = SoKeyboardEvent::PAD_SPACE,   PAD_TAB = SoKeyboardEvent::PAD_TAB,   PAD_INSERT = SoKeyboardEvent::PAD_INSERT,   PAD_DELETE = SoKeyboardEvent::PAD_DELETE,   PAD_PERIOD = SoKeyboardEvent::PAD_PERIOD,   F1 = SoKeyboardEvent::F1,   F2 = SoKeyboardEvent::F2,   F3 = SoKeyboardEvent::F3,   F4 = SoKeyboardEvent::F4,   F5 = SoKeyboardEvent::F5,   F6 = SoKeyboardEvent::F6,   F7 = SoKeyboardEvent::F7,   F8 = SoKeyboardEvent::F8,   F9 = SoKeyboardEvent::F9,   F10 = SoKeyboardEvent::F10,   F11 = SoKeyboardEvent::F11,   F12 = SoKeyboardEvent::F12,   BACKSPACE = SoKeyboardEvent::BACKSPACE,   TAB = SoKeyboardEvent::TAB,   RETURN = SoKeyboardEvent::RETURN,   ENTER = SoKeyboardEvent::ENTER,   PAUSE = SoKeyboardEvent::PAUSE,   SCROLL_LOCK = SoKeyboardEvent::SCROLL_LOCK,   ESCAPE = SoKeyboardEvent::ESCAPE,   KEY_DELETE = SoKeyboardEvent::KEY_DELETE,   PRINT = SoKeyboardEvent::PRINT,   INSERT = SoKeyboardEvent::INSERT,   NUM_LOCK = SoKeyboardEvent::NUM_LOCK,   CAPS_LOCK = SoKeyboardEvent::CAPS_LOCK,   SHIFT_LOCK = SoKeyboardEvent::SHIFT_LOCK,   SPACE = SoKeyboardEvent::SPACE,   EXCLAM = SoKeyboardEvent::EXCLAM,   QUOTEDBL = SoKeyboardEvent::QUOTEDBL,   NUMBERSIGN = SoKeyboardEvent::NUMBERSIGN,   DOLLAR = SoKeyboardEvent::DOLLAR,   PERCENT = SoKeyboardEvent::PERCENT,   AMPERSAND = SoKeyboardEvent::AMPERSAND,   APOSTROPHE = SoKeyboardEvent::APOSTROPHE,   PARENLEFT = SoKeyboardEvent::PARENLEFT,   PARENRIGHT = SoKeyboardEvent::PARENRIGHT,   ASTERISK = SoKeyboardEvent::ASTERISK,   PLUS = SoKeyboardEvent::PLUS,   COMMA = SoKeyboardEvent::COMMA,   MINUS = SoKeyboardEvent::MINUS,   PERIOD = SoKeyboardEvent::PERIOD,   SLASH = SoKeyboardEvent::SLASH,   COLON = SoKeyboardEvent::COLON,   SEMICOLON = SoKeyboardEvent::SEMICOLON,   LESS = SoKeyboardEvent::LESS,   EQUAL = SoKeyboardEvent::EQUAL,   GREATER = SoKeyboardEvent::GREATER,   QUESTION = SoKeyboardEvent::QUESTION,   AT = SoKeyboardEvent::AT,   BRACKETLEFT = SoKeyboardEvent::BRACKETLEFT,   BACKSLASH = SoKeyboardEvent::BACKSLASH,   BRACKETRIGHT = SoKeyboardEvent::BRACKETRIGHT,   ASCIICIRCUM = SoKeyboardEvent::ASCIICIRCUM,   UNDERSCORE = SoKeyboardEvent::UNDERSCORE,   GRAVE = SoKeyboardEvent::GRAVE,   BRACELEFT = SoKeyboardEvent::BRACELEFT,   BAR = SoKeyboardEvent::BAR,   BRACERIGHT = SoKeyboardEvent::BRACERIGHT,   ASCIITILDE = SoKeyboardEvent::ASCIITILDE};
public Q_SLOTS:
SoKeyboardEvent* new_SoKeyboardEvent();
void delete_SoKeyboardEvent(SoKeyboardEvent* obj) { delete obj; }
   SoType  static_SoKeyboardEvent_getClassTypeId();
   SoKeyboardEvent::Key  getKey(SoKeyboardEvent* theWrappedObject) const;
   char  getPrintableCharacter(SoKeyboardEvent* theWrappedObject) const;
   bool  isAutoRepeat(SoKeyboardEvent* theWrappedObject) const;
   bool  static_SoKeyboardEvent_isKeyPressEvent(const SoEvent*  e, SoKeyboardEvent::Key  whichKey);
   bool  static_SoKeyboardEvent_isKeyReleaseEvent(const SoEvent*  e, SoKeyboardEvent::Key  whichKey);
   void setIsAutoRepeat(SoKeyboardEvent* theWrappedObject, bool  b);
   void setKey(SoKeyboardEvent* theWrappedObject, SoKeyboardEvent::Key  whichKey);
};





class PythonQtShell_SoLocation2Event : public SoLocation2Event
{
public:
    PythonQtShell_SoLocation2Event():SoLocation2Event(),_wrapper(nullptr) {};

   ~PythonQtShell_SoLocation2Event() override;


  PythonQtInstanceWrapper* _wrapper;
};

class PythonQtWrapper_SoLocation2Event : public QObject
{ Q_OBJECT
public:
public Q_SLOTS:
SoLocation2Event* new_SoLocation2Event();
void delete_SoLocation2Event(SoLocation2Event* obj) { delete obj; }
   SoType  static_SoLocation2Event_getClassTypeId();
};





class PythonQtWrapper_SoLocation2RefreshEvent : public QObject
{ Q_OBJECT
public:
public Q_SLOTS:
SoLocation2RefreshEvent* new_SoLocation2RefreshEvent();
void delete_SoLocation2RefreshEvent(SoLocation2RefreshEvent* obj) { delete obj; }
   SoType  static_SoLocation2RefreshEvent_getClassTypeId();
};





class PythonQtShell_SoMotion3Event : public SoMotion3Event
{
public:
    PythonQtShell_SoMotion3Event():SoMotion3Event(),_wrapper(nullptr) {};

   ~PythonQtShell_SoMotion3Event() override;


  PythonQtInstanceWrapper* _wrapper;
};

class PythonQtWrapper_SoMotion3Event : public QObject
{ Q_OBJECT
public:
public Q_SLOTS:
SoMotion3Event* new_SoMotion3Event();
void delete_SoMotion3Event(SoMotion3Event* obj) { delete obj; }
   SoType  static_SoMotion3Event_getClassTypeId();
   const SbRotation*  getRotation(SoMotion3Event* theWrappedObject) const;
   const SbVec3f*  getTranslation(SoMotion3Event* theWrappedObject) const;
   void setRotation(SoMotion3Event* theWrappedObject, const SbRotation&  r);
   void setTranslation(SoMotion3Event* theWrappedObject, const SbVec3f&  t);
};





class PythonQtShell_SoMouseButtonEvent : public SoMouseButtonEvent
{
public:
    PythonQtShell_SoMouseButtonEvent():SoMouseButtonEvent(),_wrapper(nullptr) {};

   ~PythonQtShell_SoMouseButtonEvent() override;


  PythonQtInstanceWrapper* _wrapper;
};

class PythonQtWrapper_SoMouseButtonEvent : public QObject
{ Q_OBJECT
public:
Q_ENUMS(Button )
enum Button{
  ANY = SoMouseButtonEvent::ANY,   BUTTON1 = SoMouseButtonEvent::BUTTON1,   BUTTON2 = SoMouseButtonEvent::BUTTON2,   BUTTON3 = SoMouseButtonEvent::BUTTON3,   LEFT_BUTTON = SoMouseButtonEvent::LEFT_BUTTON,   MIDDLE_BUTTON = SoMouseButtonEvent::MIDDLE_BUTTON,   RIGHT_BUTTON = SoMouseButtonEvent::RIGHT_BUTTON};
public Q_SLOTS:
SoMouseButtonEvent* new_SoMouseButtonEvent();
void delete_SoMouseButtonEvent(SoMouseButtonEvent* obj) { delete obj; }
   SoMouseButtonEvent::Button  getButton(SoMouseButtonEvent* theWrappedObject) const;
   SoType  static_SoMouseButtonEvent_getClassTypeId();
   bool  static_SoMouseButtonEvent_isButtonPressEvent(const SoEvent*  e, SoMouseButtonEvent::Button  whichButton);
   bool  static_SoMouseButtonEvent_isButtonReleaseEvent(const SoEvent*  e, SoMouseButtonEvent::Button  whichButton);
   bool  isDoubleClick(SoMouseButtonEvent* theWrappedObject) const;
   void setButton(SoMouseButtonEvent* theWrappedObject, SoMouseButtonEvent::Button  b);
   void setIsDoubleClick(SoMouseButtonEvent* theWrappedObject, bool  b);
};





class PythonQtWrapper_SoMouseWheelEvent : public QObject
{ Q_OBJECT
public:
Q_ENUMS(Orientation )
enum Orientation{
  HORIZONTAL = SoMouseWheelEvent::HORIZONTAL,   VERTICAL = SoMouseWheelEvent::VERTICAL};
public Q_SLOTS:
SoMouseWheelEvent* new_SoMouseWheelEvent();
void delete_SoMouseWheelEvent(SoMouseWheelEvent* obj) { delete obj; }
   SoType  static_SoMouseWheelEvent_getClassTypeId();
   SoMouseWheelEvent::Orientation  getWheelOrientation(SoMouseWheelEvent* theWrappedObject) const;
   short  getWheelRotation(SoMouseWheelEvent* theWrappedObject) const;
   void setWheelOrientation(SoMouseWheelEvent* theWrappedObject, SoMouseWheelEvent::Orientation  orient);
   void setWheelRotation(SoMouseWheelEvent* theWrappedObject, short  rot);
};





class PythonQtShell_SoSpaceballButtonEvent : public SoSpaceballButtonEvent
{
public:
    PythonQtShell_SoSpaceballButtonEvent():SoSpaceballButtonEvent(),_wrapper(nullptr) {};

   ~PythonQtShell_SoSpaceballButtonEvent() override;


  PythonQtInstanceWrapper* _wrapper;
};

class PythonQtWrapper_SoSpaceballButtonEvent : public QObject
{ Q_OBJECT
public:
Q_ENUMS(Button )
enum Button{
  ANY = SoSpaceballButtonEvent::ANY,   BUTTON1 = SoSpaceballButtonEvent::BUTTON1,   BUTTON2 = SoSpaceballButtonEvent::BUTTON2,   BUTTON3 = SoSpaceballButtonEvent::BUTTON3,   BUTTON4 = SoSpaceballButtonEvent::BUTTON4,   BUTTON5 = SoSpaceballButtonEvent::BUTTON5,   BUTTON6 = SoSpaceballButtonEvent::BUTTON6,   BUTTON7 = SoSpaceballButtonEvent::BUTTON7,   BUTTON8 = SoSpaceballButtonEvent::BUTTON8,   PICK = SoSpaceballButtonEvent::PICK};
public Q_SLOTS:
SoSpaceballButtonEvent* new_SoSpaceballButtonEvent();
void delete_SoSpaceballButtonEvent(SoSpaceballButtonEvent* obj) { delete obj; }
   SoSpaceballButtonEvent::Button  getButton(SoSpaceballButtonEvent* theWrappedObject) const;
   SoType  static_SoSpaceballButtonEvent_getClassTypeId();
   bool  static_SoSpaceballButtonEvent_isButtonPressEvent(const SoEvent*  e, SoSpaceballButtonEvent::Button  whichButton);
   bool  static_SoSpaceballButtonEvent_isButtonReleaseEvent(const SoEvent*  e, SoSpaceballButtonEvent::Button  whichButton);
   void setButton(SoSpaceballButtonEvent* theWrappedObject, SoSpaceballButtonEvent::Button  b);
};


