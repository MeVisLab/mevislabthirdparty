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
#include <Inventor/SbLineard.h>
#include <Inventor/SbString.h>
#include <Inventor/SoInput.h>
#include <Inventor/SoOutput.h>
#include <Inventor/SoType.h>
#include <Inventor/engines/SoEngine.h>
#include <Inventor/engines/SoFieldConverter.h>
#include <Inventor/fields/SoField.h>
#include <Inventor/fields/SoFieldContainer.h>
#include <Inventor/fields/SoSFVec3s.h>
#include <Inventor/fields/SoSFVec4d.h>
#include <Inventor/fields/SoSFVec4f.h>
#include <stdexcept>



class PythonQtWrapper_SoSFVec3s : public QObject
{ Q_OBJECT
public:
public Q_SLOTS:
SoSFVec3s* new_SoSFVec3s();
void delete_SoSFVec3s(SoSFVec3s* obj) { delete obj; }
   void*  static_SoSFVec3s_createInstance();
   SoType  static_SoSFVec3s_getClassTypeId();
   const SbVec3s*  getValue(SoSFVec3s* theWrappedObject) const;
   bool  __ne__(SoSFVec3s* theWrappedObject, const SoSFVec3s&  f) const;
   const SbVec3s*  operator_assign(SoSFVec3s* theWrappedObject, const SbVec3s&  newValue);
   const SoSFVec3s*  operator_assign(SoSFVec3s* theWrappedObject, const SoSFVec3s&  f);
   bool  __eq__(SoSFVec3s* theWrappedObject, const SoSFVec3s&  f) const;
   void setValue(SoSFVec3s* theWrappedObject, const SbVec3s&  newValue);
   void setValue(SoSFVec3s* theWrappedObject, short  x, short  y, short  z);
};





class PythonQtWrapper_SoSFVec4d : public QObject
{ Q_OBJECT
public:
public Q_SLOTS:
SoSFVec4d* new_SoSFVec4d();
void delete_SoSFVec4d(SoSFVec4d* obj) { delete obj; }
   void*  static_SoSFVec4d_createInstance();
   SoType  static_SoSFVec4d_getClassTypeId();
   const SbVec4d*  getValue(SoSFVec4d* theWrappedObject) const;
   bool  __ne__(SoSFVec4d* theWrappedObject, const SoSFVec4d&  f) const;
   const SbVec4d*  operator_assign(SoSFVec4d* theWrappedObject, const SbVec4d&  newValue);
   const SoSFVec4d*  operator_assign(SoSFVec4d* theWrappedObject, const SoSFVec4d&  f);
   bool  __eq__(SoSFVec4d* theWrappedObject, const SoSFVec4d&  f) const;
   void setValue(SoSFVec4d* theWrappedObject, const SbVec4d&  newValue);
   void setValue(SoSFVec4d* theWrappedObject, double  x, double  y, double  z, double  w);
};





class PythonQtWrapper_SoSFVec4f : public QObject
{ Q_OBJECT
public:
public Q_SLOTS:
SoSFVec4f* new_SoSFVec4f();
void delete_SoSFVec4f(SoSFVec4f* obj) { delete obj; }
   void*  static_SoSFVec4f_createInstance();
   SoType  static_SoSFVec4f_getClassTypeId();
   const SbVec4f*  getValue(SoSFVec4f* theWrappedObject) const;
   bool  __ne__(SoSFVec4f* theWrappedObject, const SoSFVec4f&  f) const;
   const SbVec4f*  operator_assign(SoSFVec4f* theWrappedObject, const SbVec4f&  newValue);
   const SoSFVec4f*  operator_assign(SoSFVec4f* theWrappedObject, const SoSFVec4f&  f);
   bool  __eq__(SoSFVec4f* theWrappedObject, const SoSFVec4f&  f) const;
   void setValue(SoSFVec4f* theWrappedObject, const SbVec4f&  newValue);
   void setValue(SoSFVec4f* theWrappedObject, float  x, float  y, float  z, float  w);
};





class PythonQtWrapper_SoSField : public QObject
{ Q_OBJECT
public:
public Q_SLOTS:
void delete_SoSField(SoSField* obj) { delete obj; }
   void*  static_SoSField_createInstance();
   SoType  static_SoSField_getClassTypeId();
};


