/*************************************************************************************
**
** Copyright 2022, MeVis Medical Solutions AG
**
** GNU LESSER GENERAL PUBLIC LICENSE Version 2.1, February 1999
**
**************************************************************************************/
#include "Inventor_fields2.h"
#include <PythonQtConversion.h>
#include <PythonQtMethodInfo.h>
#include <PythonQtSignalReceiver.h>
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

SoSFVec3s* PythonQtWrapper_SoSFVec3s::new_SoSFVec3s()
{ 
return new SoSFVec3s(); }

void*  PythonQtWrapper_SoSFVec3s::static_SoSFVec3s_createInstance()
{
  return (SoSFVec3s::createInstance());
}

SoType  PythonQtWrapper_SoSFVec3s::static_SoSFVec3s_getClassTypeId()
{
  return (SoSFVec3s::getClassTypeId());
}

const SbVec3s*  PythonQtWrapper_SoSFVec3s::getValue(SoSFVec3s* theWrappedObject) const
{
  return &( theWrappedObject->getValue());
}

bool  PythonQtWrapper_SoSFVec3s::__ne__(SoSFVec3s* theWrappedObject, const SoSFVec3s&  f) const
{
  return ( (*theWrappedObject)!= f);
}

const SbVec3s*  PythonQtWrapper_SoSFVec3s::operator_assign(SoSFVec3s* theWrappedObject, const SbVec3s&  newValue)
{
  return &( (*theWrappedObject)= newValue);
}

const SoSFVec3s*  PythonQtWrapper_SoSFVec3s::operator_assign(SoSFVec3s* theWrappedObject, const SoSFVec3s&  f)
{
  return &( (*theWrappedObject)= f);
}

bool  PythonQtWrapper_SoSFVec3s::__eq__(SoSFVec3s* theWrappedObject, const SoSFVec3s&  f) const
{
  return ( (*theWrappedObject)== f);
}

void PythonQtWrapper_SoSFVec3s::setValue(SoSFVec3s* theWrappedObject, const SbVec3s&  newValue)
{
  ( theWrappedObject->setValue(newValue));
}

void PythonQtWrapper_SoSFVec3s::setValue(SoSFVec3s* theWrappedObject, short  x, short  y, short  z)
{
  ( theWrappedObject->setValue(x, y, z));
}



SoSFVec4d* PythonQtWrapper_SoSFVec4d::new_SoSFVec4d()
{ 
return new SoSFVec4d(); }

void*  PythonQtWrapper_SoSFVec4d::static_SoSFVec4d_createInstance()
{
  return (SoSFVec4d::createInstance());
}

SoType  PythonQtWrapper_SoSFVec4d::static_SoSFVec4d_getClassTypeId()
{
  return (SoSFVec4d::getClassTypeId());
}

const SbVec4d*  PythonQtWrapper_SoSFVec4d::getValue(SoSFVec4d* theWrappedObject) const
{
  return &( theWrappedObject->getValue());
}

bool  PythonQtWrapper_SoSFVec4d::__ne__(SoSFVec4d* theWrappedObject, const SoSFVec4d&  f) const
{
  return ( (*theWrappedObject)!= f);
}

const SbVec4d*  PythonQtWrapper_SoSFVec4d::operator_assign(SoSFVec4d* theWrappedObject, const SbVec4d&  newValue)
{
  return &( (*theWrappedObject)= newValue);
}

const SoSFVec4d*  PythonQtWrapper_SoSFVec4d::operator_assign(SoSFVec4d* theWrappedObject, const SoSFVec4d&  f)
{
  return &( (*theWrappedObject)= f);
}

bool  PythonQtWrapper_SoSFVec4d::__eq__(SoSFVec4d* theWrappedObject, const SoSFVec4d&  f) const
{
  return ( (*theWrappedObject)== f);
}

void PythonQtWrapper_SoSFVec4d::setValue(SoSFVec4d* theWrappedObject, const SbVec4d&  newValue)
{
  ( theWrappedObject->setValue(newValue));
}

void PythonQtWrapper_SoSFVec4d::setValue(SoSFVec4d* theWrappedObject, double  x, double  y, double  z, double  w)
{
  ( theWrappedObject->setValue(x, y, z, w));
}



SoSFVec4f* PythonQtWrapper_SoSFVec4f::new_SoSFVec4f()
{ 
return new SoSFVec4f(); }

void*  PythonQtWrapper_SoSFVec4f::static_SoSFVec4f_createInstance()
{
  return (SoSFVec4f::createInstance());
}

SoType  PythonQtWrapper_SoSFVec4f::static_SoSFVec4f_getClassTypeId()
{
  return (SoSFVec4f::getClassTypeId());
}

const SbVec4f*  PythonQtWrapper_SoSFVec4f::getValue(SoSFVec4f* theWrappedObject) const
{
  return &( theWrappedObject->getValue());
}

bool  PythonQtWrapper_SoSFVec4f::__ne__(SoSFVec4f* theWrappedObject, const SoSFVec4f&  f) const
{
  return ( (*theWrappedObject)!= f);
}

const SbVec4f*  PythonQtWrapper_SoSFVec4f::operator_assign(SoSFVec4f* theWrappedObject, const SbVec4f&  newValue)
{
  return &( (*theWrappedObject)= newValue);
}

const SoSFVec4f*  PythonQtWrapper_SoSFVec4f::operator_assign(SoSFVec4f* theWrappedObject, const SoSFVec4f&  f)
{
  return &( (*theWrappedObject)= f);
}

bool  PythonQtWrapper_SoSFVec4f::__eq__(SoSFVec4f* theWrappedObject, const SoSFVec4f&  f) const
{
  return ( (*theWrappedObject)== f);
}

void PythonQtWrapper_SoSFVec4f::setValue(SoSFVec4f* theWrappedObject, const SbVec4f&  newValue)
{
  ( theWrappedObject->setValue(newValue));
}

void PythonQtWrapper_SoSFVec4f::setValue(SoSFVec4f* theWrappedObject, float  x, float  y, float  z, float  w)
{
  ( theWrappedObject->setValue(x, y, z, w));
}



void*  PythonQtWrapper_SoSField::static_SoSField_createInstance()
{
  return (SoSField::createInstance());
}

SoType  PythonQtWrapper_SoSField::static_SoSField_getClassTypeId()
{
  return (SoSField::getClassTypeId());
}


