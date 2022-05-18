/*************************************************************************************
**
** Copyright 2022, MeVis Medical Solutions AG
**
** GNU LESSER GENERAL PUBLIC LICENSE Version 2.1, February 1999
**
**************************************************************************************/
#include "Inventor_fields0.h"
#include <PythonQtConversion.h>
#include <PythonQtMethodInfo.h>
#include <PythonQtSignalReceiver.h>
#include <QVariant>
#include <Inventor/SbColor.h>
#include <Inventor/SbLinear.h>
#include <Inventor/SbLineard.h>
#include <Inventor/SbString.h>
#include <Inventor/SbTime.h>
#include <Inventor/SoInput.h>
#include <Inventor/SoOutput.h>
#include <Inventor/SoPath.h>
#include <Inventor/SoType.h>
#include <Inventor/engines/SoEngine.h>
#include <Inventor/engines/SoFieldConverter.h>
#include <Inventor/fields/SoField.h>
#include <Inventor/fields/SoFieldContainer.h>
#include <Inventor/fields/SoMFBitMask.h>
#include <Inventor/fields/SoMFBool.h>
#include <Inventor/fields/SoMFColor.h>
#include <Inventor/fields/SoMFDouble.h>
#include <Inventor/fields/SoMFEngine.h>
#include <Inventor/fields/SoMFEnum.h>
#include <Inventor/fields/SoMFFloat.h>
#include <Inventor/fields/SoMFInt32.h>
#include <Inventor/fields/SoMFMatrix.h>
#include <Inventor/fields/SoMFMatrixd.h>
#include <Inventor/fields/SoMFName.h>
#include <Inventor/fields/SoMFNode.h>
#include <Inventor/fields/SoMFPath.h>
#include <Inventor/fields/SoMFPlane.h>
#include <Inventor/fields/SoMFPlaned.h>
#include <Inventor/fields/SoMFRotation.h>
#include <Inventor/fields/SoMFRotationd.h>
#include <Inventor/fields/SoMFShort.h>
#include <Inventor/fields/SoMFString.h>
#include <Inventor/fields/SoMFTime.h>
#include <Inventor/fields/SoMFUInt32.h>
#include <Inventor/fields/SoMFUShort.h>
#include <Inventor/fields/SoMFVec2d.h>
#include <Inventor/fields/SoMFVec2f.h>
#include <Inventor/fields/SoMFVec3d.h>
#include <Inventor/fields/SoMFVec3f.h>
#include <Inventor/fields/SoMFVec4d.h>
#include <Inventor/fields/SoMFVec4f.h>
#include <Inventor/misc/SoBase.h>
#include <Inventor/nodes/SoNode.h>
#include <Inventor/sensors/SoSensor.h>
#include <stdexcept>

bool  PythonQtWrapper_SoField::connectFrom(SoField* theWrappedObject, SoEngineOutput*  engineOutput)
{
  return ( theWrappedObject->connectFrom(engineOutput));
}

bool  PythonQtWrapper_SoField::connectFrom(SoField* theWrappedObject, SoField*  field)
{
  return ( theWrappedObject->connectFrom(field));
}

void PythonQtWrapper_SoField::connectionStatusChanged(SoField* theWrappedObject, int  numConnections)
{
  ( theWrappedObject->connectionStatusChanged(numConnections));
}

void PythonQtWrapper_SoField::copyConnection(SoField* theWrappedObject, const SoField*  fromField)
{
  ( theWrappedObject->copyConnection(fromField));
}

void PythonQtWrapper_SoField::copyFrom(SoField* theWrappedObject, const SoField&  f)
{
  ( theWrappedObject->copyFrom(f));
}

void PythonQtWrapper_SoField::countWriteRefs(SoField* theWrappedObject, SoOutput*  out) const
{
  ( theWrappedObject->countWriteRefs(out));
}

void PythonQtWrapper_SoField::disconnect(SoField* theWrappedObject)
{
  ( theWrappedObject->disconnect());
}

void PythonQtWrapper_SoField::enableConnection(SoField* theWrappedObject, bool  flag)
{
  ( theWrappedObject->enableConnection(flag));
}

bool  PythonQtWrapper_SoField::enableContainerNotify(SoField* theWrappedObject, bool  flag)
{
  return ( theWrappedObject->enableContainerNotify(flag));
}

bool  PythonQtWrapper_SoField::enableNotify(SoField* theWrappedObject, bool  flag)
{
  return ( theWrappedObject->enableNotify(flag));
}

void PythonQtWrapper_SoField::evaluate(SoField* theWrappedObject) const
{
  ( theWrappedObject->evaluate());
}

void PythonQtWrapper_SoField::fixCopy(SoField* theWrappedObject, bool  copyConnections)
{
  ( theWrappedObject->fixCopy(copyConnections));
}

SoType  PythonQtWrapper_SoField::static_SoField_getClassTypeId()
{
  return (SoField::getClassTypeId());
}

SoFieldContainer*  PythonQtWrapper_SoField::getContainer(SoField* theWrappedObject) const
{
  return ( theWrappedObject->getContainer());
}

bool  PythonQtWrapper_SoField::isConnected(SoField* theWrappedObject) const
{
  return ( theWrappedObject->isConnected());
}

bool  PythonQtWrapper_SoField::isConnectedFromEngine(SoField* theWrappedObject) const
{
  return ( theWrappedObject->isConnectedFromEngine());
}

bool  PythonQtWrapper_SoField::isConnectedFromField(SoField* theWrappedObject) const
{
  return ( theWrappedObject->isConnectedFromField());
}

bool  PythonQtWrapper_SoField::isConnectionEnabled(SoField* theWrappedObject) const
{
  return ( theWrappedObject->isConnectionEnabled());
}

bool  PythonQtWrapper_SoField::isContainerNotifyEnabled(SoField* theWrappedObject) const
{
  return ( theWrappedObject->isContainerNotifyEnabled());
}

bool  PythonQtWrapper_SoField::isDefault(SoField* theWrappedObject) const
{
  return ( theWrappedObject->isDefault());
}

bool  PythonQtWrapper_SoField::isIgnored(SoField* theWrappedObject) const
{
  return ( theWrappedObject->isIgnored());
}

bool  PythonQtWrapper_SoField::isNotifyEnabled(SoField* theWrappedObject) const
{
  return ( theWrappedObject->isNotifyEnabled());
}

bool  PythonQtWrapper_SoField::isOfType(SoField* theWrappedObject, SoType  type) const
{
  return ( theWrappedObject->isOfType(type));
}

bool  PythonQtWrapper_SoField::isReadOnly(SoField* theWrappedObject) const
{
  return ( theWrappedObject->isReadOnly());
}

bool  PythonQtWrapper_SoField::isSame(SoField* theWrappedObject, const SoField&  f) const
{
  return ( theWrappedObject->isSame(f));
}

bool  PythonQtWrapper_SoField::__ne__(SoField* theWrappedObject, const SoField&  f) const
{
  return ( (*theWrappedObject)!= f);
}

bool  PythonQtWrapper_SoField::__eq__(SoField* theWrappedObject, const SoField&  f) const
{
  return ( (*theWrappedObject)== f);
}

bool  PythonQtWrapper_SoField::read(SoField* theWrappedObject, SoInput*  in, const SbName&  name)
{
  return ( theWrappedObject->read(in, name));
}

bool  PythonQtWrapper_SoField::referencesCopy(SoField* theWrappedObject) const
{
  return ( theWrappedObject->referencesCopy());
}

bool  PythonQtWrapper_SoField::set(SoField* theWrappedObject, const char*  valueString)
{
  return ( theWrappedObject->set(valueString));
}

void PythonQtWrapper_SoField::setContainer(SoField* theWrappedObject, SoFieldContainer*  cont)
{
  ( theWrappedObject->setContainer(cont));
}

void PythonQtWrapper_SoField::setDefault(SoField* theWrappedObject, bool  def)
{
  ( theWrappedObject->setDefault(def));
}

void PythonQtWrapper_SoField::setIgnored(SoField* theWrappedObject, bool  ig)
{
  ( theWrappedObject->setIgnored(ig));
}

void PythonQtWrapper_SoField::startNotify(SoField* theWrappedObject)
{
  ( theWrappedObject->startNotify());
}

void PythonQtWrapper_SoField::touch(SoField* theWrappedObject)
{
  ( theWrappedObject->touch());
}

void PythonQtWrapper_SoField::write(SoField* theWrappedObject, SoOutput*  out, const SbName&  name) const
{
  ( theWrappedObject->write(out, name));
}



void PythonQtWrapper_SoFieldContainer::addManagedSensor(SoFieldContainer* theWrappedObject, SoSensor*  sensor)
{
  ( theWrappedObject->addManagedSensor(sensor));
}

bool  PythonQtWrapper_SoFieldContainer::enableNotify(SoFieldContainer* theWrappedObject, bool  flag)
{
  return ( theWrappedObject->enableNotify(flag));
}

bool  PythonQtWrapper_SoFieldContainer::fieldsAreEqual(SoFieldContainer* theWrappedObject, const SoFieldContainer*  fc) const
{
  return ( theWrappedObject->fieldsAreEqual(fc));
}

SoType  PythonQtWrapper_SoFieldContainer::static_SoFieldContainer_getClassTypeId()
{
  return (SoFieldContainer::getClassTypeId());
}

SoField*  PythonQtWrapper_SoFieldContainer::getField(SoFieldContainer* theWrappedObject, const SbName&  fieldName) const
{
  return ( theWrappedObject->getField(fieldName));
}

bool  PythonQtWrapper_SoFieldContainer::getIsBuiltIn(SoFieldContainer* theWrappedObject) const
{
  return ( theWrappedObject->getIsBuiltIn());
}

bool  PythonQtWrapper_SoFieldContainer::hasDefaultValues(SoFieldContainer* theWrappedObject) const
{
  return ( theWrappedObject->hasDefaultValues());
}

bool  PythonQtWrapper_SoFieldContainer::isNotifyEnabled(SoFieldContainer* theWrappedObject) const
{
  return ( theWrappedObject->isNotifyEnabled());
}

bool  PythonQtWrapper_SoFieldContainer::set(SoFieldContainer* theWrappedObject, const char*  fieldDataString)
{
  return ( theWrappedObject->set(fieldDataString));
}

bool  PythonQtWrapper_SoFieldContainer::set(SoFieldContainer* theWrappedObject, const char*  fieldDataString, SoInput*  dictIn)
{
  return ( theWrappedObject->set(fieldDataString, dictIn));
}

void PythonQtWrapper_SoFieldContainer::setToDefaults(SoFieldContainer* theWrappedObject)
{
  ( theWrappedObject->setToDefaults());
}



SoMFBitMask* PythonQtWrapper_SoMFBitMask::new_SoMFBitMask()
{ 
return new SoMFBitMask(); }

void*  PythonQtWrapper_SoMFBitMask::static_SoMFBitMask_createInstance()
{
  return (SoMFBitMask::createInstance());
}

SoType  PythonQtWrapper_SoMFBitMask::static_SoMFBitMask_getClassTypeId()
{
  return (SoMFBitMask::getClassTypeId());
}

const SoMFBitMask*  PythonQtWrapper_SoMFBitMask::operator_assign(SoMFBitMask* theWrappedObject, const SoMFBitMask&  f)
{
  return &( (*theWrappedObject)= f);
}

int  PythonQtWrapper_SoMFBitMask::operator_assign(SoMFBitMask* theWrappedObject, int  newValue)
{
  return ( (*theWrappedObject)= newValue);
}



SoMFBool* PythonQtWrapper_SoMFBool::new_SoMFBool()
{ 
return new SoMFBool(); }

void*  PythonQtWrapper_SoMFBool::static_SoMFBool_createInstance()
{
  return (SoMFBool::createInstance());
}

int  PythonQtWrapper_SoMFBool::find(SoMFBool* theWrappedObject, bool  targetValue, bool  addIfNotFound)
{
  return ( theWrappedObject->find(targetValue, addIfNotFound));
}

void PythonQtWrapper_SoMFBool::finishEditing(SoMFBool* theWrappedObject)
{
  ( theWrappedObject->finishEditing());
}

SoType  PythonQtWrapper_SoMFBool::static_SoMFBool_getClassTypeId()
{
  return (SoMFBool::getClassTypeId());
}

bool  PythonQtWrapper_SoMFBool::__ne__(SoMFBool* theWrappedObject, const SoMFBool&  f) const
{
  return ( (*theWrappedObject)!= f);
}

bool  PythonQtWrapper_SoMFBool::operator_assign(SoMFBool* theWrappedObject, bool  newValue)
{
  return ( (*theWrappedObject)= newValue);
}

const SoMFBool*  PythonQtWrapper_SoMFBool::operator_assign(SoMFBool* theWrappedObject, const SoMFBool&  f)
{
  return &( (*theWrappedObject)= f);
}

bool  PythonQtWrapper_SoMFBool::__eq__(SoMFBool* theWrappedObject, const SoMFBool&  f) const
{
  return ( (*theWrappedObject)== f);
}

bool  PythonQtWrapper_SoMFBool::operator_subscript(SoMFBool* theWrappedObject, int  i) const
{
  return ( (*theWrappedObject)[i]);
}

void PythonQtWrapper_SoMFBool::set1Value(SoMFBool* theWrappedObject, int  index, bool  newValue)
{
  ( theWrappedObject->set1Value(index, newValue));
}

void PythonQtWrapper_SoMFBool::setValue(SoMFBool* theWrappedObject, bool  newValue)
{
  ( theWrappedObject->setValue(newValue));
}

void PythonQtWrapper_SoMFBool::setValues(SoMFBool* theWrappedObject, int  start, int  num, const bool*  newValues)
{
  ( theWrappedObject->setValues(start, num, newValues));
}



SoMFColor* PythonQtWrapper_SoMFColor::new_SoMFColor()
{ 
return new SoMFColor(); }

void*  PythonQtWrapper_SoMFColor::static_SoMFColor_createInstance()
{
  return (SoMFColor::createInstance());
}

int  PythonQtWrapper_SoMFColor::find(SoMFColor* theWrappedObject, const SbColor&  targetValue, bool  addIfNotFound)
{
  return ( theWrappedObject->find(targetValue, addIfNotFound));
}

void PythonQtWrapper_SoMFColor::finishEditing(SoMFColor* theWrappedObject)
{
  ( theWrappedObject->finishEditing());
}

SoType  PythonQtWrapper_SoMFColor::static_SoMFColor_getClassTypeId()
{
  return (SoMFColor::getClassTypeId());
}

bool  PythonQtWrapper_SoMFColor::__ne__(SoMFColor* theWrappedObject, const SoMFColor&  f) const
{
  return ( (*theWrappedObject)!= f);
}

const SbColor*  PythonQtWrapper_SoMFColor::operator_assign(SoMFColor* theWrappedObject, const SbColor&  newValue)
{
  return &( (*theWrappedObject)= newValue);
}

const SoMFColor*  PythonQtWrapper_SoMFColor::operator_assign(SoMFColor* theWrappedObject, const SoMFColor&  f)
{
  return &( (*theWrappedObject)= f);
}

bool  PythonQtWrapper_SoMFColor::__eq__(SoMFColor* theWrappedObject, const SoMFColor&  f) const
{
  return ( (*theWrappedObject)== f);
}

const SbColor*  PythonQtWrapper_SoMFColor::operator_subscript(SoMFColor* theWrappedObject, int  i) const
{
  return &( (*theWrappedObject)[i]);
}

void PythonQtWrapper_SoMFColor::set1HSVValue(SoMFColor* theWrappedObject, int  index, float  h, float  s, float  v)
{
  ( theWrappedObject->set1HSVValue(index, h, s, v));
}

void PythonQtWrapper_SoMFColor::set1Value(SoMFColor* theWrappedObject, int  index, const SbColor&  newValue)
{
  ( theWrappedObject->set1Value(index, newValue));
}

void PythonQtWrapper_SoMFColor::set1Value(SoMFColor* theWrappedObject, int  index, const SbVec3f&  vec)
{
  ( theWrappedObject->set1Value(index, vec));
}

void PythonQtWrapper_SoMFColor::set1Value(SoMFColor* theWrappedObject, int  index, float  r, float  g, float  b)
{
  ( theWrappedObject->set1Value(index, r, g, b));
}

void PythonQtWrapper_SoMFColor::setHSVValue(SoMFColor* theWrappedObject, float  h, float  s, float  v)
{
  ( theWrappedObject->setHSVValue(h, s, v));
}

void PythonQtWrapper_SoMFColor::setValue(SoMFColor* theWrappedObject, const SbColor&  newValue)
{
  ( theWrappedObject->setValue(newValue));
}

void PythonQtWrapper_SoMFColor::setValue(SoMFColor* theWrappedObject, const SbVec3f&  vec)
{
  ( theWrappedObject->setValue(vec));
}

void PythonQtWrapper_SoMFColor::setValue(SoMFColor* theWrappedObject, float  r, float  g, float  b)
{
  ( theWrappedObject->setValue(r, g, b));
}

void PythonQtWrapper_SoMFColor::setValues(SoMFColor* theWrappedObject, int  start, int  num, const SbColor*  newValues)
{
  ( theWrappedObject->setValues(start, num, newValues));
}



SoMFDouble* PythonQtWrapper_SoMFDouble::new_SoMFDouble()
{ 
return new SoMFDouble(); }

void*  PythonQtWrapper_SoMFDouble::static_SoMFDouble_createInstance()
{
  return (SoMFDouble::createInstance());
}

int  PythonQtWrapper_SoMFDouble::find(SoMFDouble* theWrappedObject, double  targetValue, bool  addIfNotFound)
{
  return ( theWrappedObject->find(targetValue, addIfNotFound));
}

void PythonQtWrapper_SoMFDouble::finishEditing(SoMFDouble* theWrappedObject)
{
  ( theWrappedObject->finishEditing());
}

SoType  PythonQtWrapper_SoMFDouble::static_SoMFDouble_getClassTypeId()
{
  return (SoMFDouble::getClassTypeId());
}

bool  PythonQtWrapper_SoMFDouble::__ne__(SoMFDouble* theWrappedObject, const SoMFDouble&  f) const
{
  return ( (*theWrappedObject)!= f);
}

const SoMFDouble*  PythonQtWrapper_SoMFDouble::operator_assign(SoMFDouble* theWrappedObject, const SoMFDouble&  f)
{
  return &( (*theWrappedObject)= f);
}

double  PythonQtWrapper_SoMFDouble::operator_assign(SoMFDouble* theWrappedObject, double  newValue)
{
  return ( (*theWrappedObject)= newValue);
}

bool  PythonQtWrapper_SoMFDouble::__eq__(SoMFDouble* theWrappedObject, const SoMFDouble&  f) const
{
  return ( (*theWrappedObject)== f);
}

double  PythonQtWrapper_SoMFDouble::operator_subscript(SoMFDouble* theWrappedObject, int  i) const
{
  return ( (*theWrappedObject)[i]);
}

void PythonQtWrapper_SoMFDouble::set1Value(SoMFDouble* theWrappedObject, int  index, double  newValue)
{
  ( theWrappedObject->set1Value(index, newValue));
}

void PythonQtWrapper_SoMFDouble::setValue(SoMFDouble* theWrappedObject, double  newValue)
{
  ( theWrappedObject->setValue(newValue));
}

void PythonQtWrapper_SoMFDouble::setValues(SoMFDouble* theWrappedObject, int  start, int  num, const double*  newValues)
{
  ( theWrappedObject->setValues(start, num, newValues));
}



SoMFEngine* PythonQtWrapper_SoMFEngine::new_SoMFEngine()
{ 
return new SoMFEngine(); }

void*  PythonQtWrapper_SoMFEngine::static_SoMFEngine_createInstance()
{
  return (SoMFEngine::createInstance());
}

int  PythonQtWrapper_SoMFEngine::find(SoMFEngine* theWrappedObject, SoEngine*  targetValue, bool  addIfNotFound)
{
  return ( theWrappedObject->find(targetValue, addIfNotFound));
}

void PythonQtWrapper_SoMFEngine::finishEditing(SoMFEngine* theWrappedObject)
{
  ( theWrappedObject->finishEditing());
}

SoType  PythonQtWrapper_SoMFEngine::static_SoMFEngine_getClassTypeId()
{
  return (SoMFEngine::getClassTypeId());
}

bool  PythonQtWrapper_SoMFEngine::__ne__(SoMFEngine* theWrappedObject, const SoMFEngine&  f) const
{
  return ( (*theWrappedObject)!= f);
}

SoEngine*  PythonQtWrapper_SoMFEngine::operator_assign(SoMFEngine* theWrappedObject, SoEngine*  newValue)
{
  return ( (*theWrappedObject)= newValue);
}

const SoMFEngine*  PythonQtWrapper_SoMFEngine::operator_assign(SoMFEngine* theWrappedObject, const SoMFEngine&  f)
{
  return &( (*theWrappedObject)= f);
}

bool  PythonQtWrapper_SoMFEngine::__eq__(SoMFEngine* theWrappedObject, const SoMFEngine&  f) const
{
  return ( (*theWrappedObject)== f);
}

SoEngine*  PythonQtWrapper_SoMFEngine::operator_subscript(SoMFEngine* theWrappedObject, int  i) const
{
  return ( (*theWrappedObject)[i]);
}

void PythonQtWrapper_SoMFEngine::set1Value(SoMFEngine* theWrappedObject, int  index, SoEngine*  newValue)
{
  ( theWrappedObject->set1Value(index, newValue));
}

void PythonQtWrapper_SoMFEngine::setValue(SoMFEngine* theWrappedObject, SoEngine*  newValue)
{
  ( theWrappedObject->setValue(newValue));
}

void PythonQtWrapper_SoMFEngine::setValues(SoMFEngine* theWrappedObject, int  start, int  num, const SoEngine**  newValues)
{
  ( theWrappedObject->setValues(start, num, newValues));
}



SoMFEnum* PythonQtWrapper_SoMFEnum::new_SoMFEnum()
{ 
return new SoMFEnum(); }

void*  PythonQtWrapper_SoMFEnum::static_SoMFEnum_createInstance()
{
  return (SoMFEnum::createInstance());
}

int  PythonQtWrapper_SoMFEnum::find(SoMFEnum* theWrappedObject, int  targetValue, bool  addIfNotFound)
{
  return ( theWrappedObject->find(targetValue, addIfNotFound));
}

void PythonQtWrapper_SoMFEnum::finishEditing(SoMFEnum* theWrappedObject)
{
  ( theWrappedObject->finishEditing());
}

SoType  PythonQtWrapper_SoMFEnum::static_SoMFEnum_getClassTypeId()
{
  return (SoMFEnum::getClassTypeId());
}

bool  PythonQtWrapper_SoMFEnum::__ne__(SoMFEnum* theWrappedObject, const SoMFEnum&  f) const
{
  return ( (*theWrappedObject)!= f);
}

const SoMFEnum*  PythonQtWrapper_SoMFEnum::operator_assign(SoMFEnum* theWrappedObject, const SoMFEnum&  f)
{
  return &( (*theWrappedObject)= f);
}

int  PythonQtWrapper_SoMFEnum::operator_assign(SoMFEnum* theWrappedObject, int  newValue)
{
  return ( (*theWrappedObject)= newValue);
}

bool  PythonQtWrapper_SoMFEnum::__eq__(SoMFEnum* theWrappedObject, const SoMFEnum&  f) const
{
  return ( (*theWrappedObject)== f);
}

int  PythonQtWrapper_SoMFEnum::operator_subscript(SoMFEnum* theWrappedObject, int  i) const
{
  return ( (*theWrappedObject)[i]);
}

void PythonQtWrapper_SoMFEnum::set1Value(SoMFEnum* theWrappedObject, int  index, const SbName&  name)
{
  ( theWrappedObject->set1Value(index, name));
}

void PythonQtWrapper_SoMFEnum::set1Value(SoMFEnum* theWrappedObject, int  index, int  newValue)
{
  ( theWrappedObject->set1Value(index, newValue));
}

void PythonQtWrapper_SoMFEnum::setEnums(SoMFEnum* theWrappedObject, int  num, int*  vals, SbName*  names)
{
  ( theWrappedObject->setEnums(num, vals, names));
}

void PythonQtWrapper_SoMFEnum::setValue(SoMFEnum* theWrappedObject, const SbName&  name)
{
  ( theWrappedObject->setValue(name));
}

void PythonQtWrapper_SoMFEnum::setValue(SoMFEnum* theWrappedObject, int  newValue)
{
  ( theWrappedObject->setValue(newValue));
}

void PythonQtWrapper_SoMFEnum::setValues(SoMFEnum* theWrappedObject, int  start, int  num, const int*  newValues)
{
  ( theWrappedObject->setValues(start, num, newValues));
}



SoMFFloat* PythonQtWrapper_SoMFFloat::new_SoMFFloat()
{ 
return new SoMFFloat(); }

void*  PythonQtWrapper_SoMFFloat::static_SoMFFloat_createInstance()
{
  return (SoMFFloat::createInstance());
}

int  PythonQtWrapper_SoMFFloat::find(SoMFFloat* theWrappedObject, float  targetValue, bool  addIfNotFound)
{
  return ( theWrappedObject->find(targetValue, addIfNotFound));
}

void PythonQtWrapper_SoMFFloat::finishEditing(SoMFFloat* theWrappedObject)
{
  ( theWrappedObject->finishEditing());
}

SoType  PythonQtWrapper_SoMFFloat::static_SoMFFloat_getClassTypeId()
{
  return (SoMFFloat::getClassTypeId());
}

bool  PythonQtWrapper_SoMFFloat::__ne__(SoMFFloat* theWrappedObject, const SoMFFloat&  f) const
{
  return ( (*theWrappedObject)!= f);
}

const SoMFFloat*  PythonQtWrapper_SoMFFloat::operator_assign(SoMFFloat* theWrappedObject, const SoMFFloat&  f)
{
  return &( (*theWrappedObject)= f);
}

float  PythonQtWrapper_SoMFFloat::operator_assign(SoMFFloat* theWrappedObject, float  newValue)
{
  return ( (*theWrappedObject)= newValue);
}

bool  PythonQtWrapper_SoMFFloat::__eq__(SoMFFloat* theWrappedObject, const SoMFFloat&  f) const
{
  return ( (*theWrappedObject)== f);
}

float  PythonQtWrapper_SoMFFloat::operator_subscript(SoMFFloat* theWrappedObject, int  i) const
{
  return ( (*theWrappedObject)[i]);
}

void PythonQtWrapper_SoMFFloat::set1Value(SoMFFloat* theWrappedObject, int  index, float  newValue)
{
  ( theWrappedObject->set1Value(index, newValue));
}

void PythonQtWrapper_SoMFFloat::setValue(SoMFFloat* theWrappedObject, float  newValue)
{
  ( theWrappedObject->setValue(newValue));
}

void PythonQtWrapper_SoMFFloat::setValues(SoMFFloat* theWrappedObject, int  start, int  num, const float*  newValues)
{
  ( theWrappedObject->setValues(start, num, newValues));
}



SoMFInt32* PythonQtWrapper_SoMFInt32::new_SoMFInt32()
{ 
return new SoMFInt32(); }

void*  PythonQtWrapper_SoMFInt32::static_SoMFInt32_createInstance()
{
  return (SoMFInt32::createInstance());
}

int  PythonQtWrapper_SoMFInt32::find(SoMFInt32* theWrappedObject, int  targetValue, bool  addIfNotFound)
{
  return ( theWrappedObject->find(targetValue, addIfNotFound));
}

void PythonQtWrapper_SoMFInt32::finishEditing(SoMFInt32* theWrappedObject)
{
  ( theWrappedObject->finishEditing());
}

SoType  PythonQtWrapper_SoMFInt32::static_SoMFInt32_getClassTypeId()
{
  return (SoMFInt32::getClassTypeId());
}

bool  PythonQtWrapper_SoMFInt32::__ne__(SoMFInt32* theWrappedObject, const SoMFInt32&  f) const
{
  return ( (*theWrappedObject)!= f);
}

const SoMFInt32*  PythonQtWrapper_SoMFInt32::operator_assign(SoMFInt32* theWrappedObject, const SoMFInt32&  f)
{
  return &( (*theWrappedObject)= f);
}

int  PythonQtWrapper_SoMFInt32::operator_assign(SoMFInt32* theWrappedObject, int  newValue)
{
  return ( (*theWrappedObject)= newValue);
}

bool  PythonQtWrapper_SoMFInt32::__eq__(SoMFInt32* theWrappedObject, const SoMFInt32&  f) const
{
  return ( (*theWrappedObject)== f);
}

int  PythonQtWrapper_SoMFInt32::operator_subscript(SoMFInt32* theWrappedObject, int  i) const
{
  return ( (*theWrappedObject)[i]);
}

void PythonQtWrapper_SoMFInt32::set1Value(SoMFInt32* theWrappedObject, int  index, int  newValue)
{
  ( theWrappedObject->set1Value(index, newValue));
}

void PythonQtWrapper_SoMFInt32::setValue(SoMFInt32* theWrappedObject, int  newValue)
{
  ( theWrappedObject->setValue(newValue));
}

void PythonQtWrapper_SoMFInt32::setValues(SoMFInt32* theWrappedObject, int  start, int  num, const int*  newValues)
{
  ( theWrappedObject->setValues(start, num, newValues));
}



SoMFMatrix* PythonQtWrapper_SoMFMatrix::new_SoMFMatrix()
{ 
return new SoMFMatrix(); }

void*  PythonQtWrapper_SoMFMatrix::static_SoMFMatrix_createInstance()
{
  return (SoMFMatrix::createInstance());
}

int  PythonQtWrapper_SoMFMatrix::find(SoMFMatrix* theWrappedObject, const SbMatrix&  targetValue, bool  addIfNotFound)
{
  return ( theWrappedObject->find(targetValue, addIfNotFound));
}

void PythonQtWrapper_SoMFMatrix::finishEditing(SoMFMatrix* theWrappedObject)
{
  ( theWrappedObject->finishEditing());
}

SoType  PythonQtWrapper_SoMFMatrix::static_SoMFMatrix_getClassTypeId()
{
  return (SoMFMatrix::getClassTypeId());
}

bool  PythonQtWrapper_SoMFMatrix::__ne__(SoMFMatrix* theWrappedObject, const SoMFMatrix&  f) const
{
  return ( (*theWrappedObject)!= f);
}

const SbMatrix*  PythonQtWrapper_SoMFMatrix::operator_assign(SoMFMatrix* theWrappedObject, const SbMatrix&  newValue)
{
  return &( (*theWrappedObject)= newValue);
}

const SoMFMatrix*  PythonQtWrapper_SoMFMatrix::operator_assign(SoMFMatrix* theWrappedObject, const SoMFMatrix&  f)
{
  return &( (*theWrappedObject)= f);
}

bool  PythonQtWrapper_SoMFMatrix::__eq__(SoMFMatrix* theWrappedObject, const SoMFMatrix&  f) const
{
  return ( (*theWrappedObject)== f);
}

const SbMatrix*  PythonQtWrapper_SoMFMatrix::operator_subscript(SoMFMatrix* theWrappedObject, int  i) const
{
  return &( (*theWrappedObject)[i]);
}

void PythonQtWrapper_SoMFMatrix::set1Value(SoMFMatrix* theWrappedObject, int  index, const SbMatrix&  newValue)
{
  ( theWrappedObject->set1Value(index, newValue));
}

void PythonQtWrapper_SoMFMatrix::setValue(SoMFMatrix* theWrappedObject, const SbMatrix&  newValue)
{
  ( theWrappedObject->setValue(newValue));
}

void PythonQtWrapper_SoMFMatrix::setValue(SoMFMatrix* theWrappedObject, float  a11, float  a12, float  a13, float  a14, float  a21, float  a22, float  a23, float  a24, float  a31, float  a32, float  a33, float  a34, float  a41, float  a42, float  a43, float  a44)
{
  ( theWrappedObject->setValue(a11, a12, a13, a14, a21, a22, a23, a24, a31, a32, a33, a34, a41, a42, a43, a44));
}

void PythonQtWrapper_SoMFMatrix::setValues(SoMFMatrix* theWrappedObject, int  start, int  num, const SbMatrix*  newValues)
{
  ( theWrappedObject->setValues(start, num, newValues));
}



SoMFMatrixd* PythonQtWrapper_SoMFMatrixd::new_SoMFMatrixd()
{ 
return new SoMFMatrixd(); }

void*  PythonQtWrapper_SoMFMatrixd::static_SoMFMatrixd_createInstance()
{
  return (SoMFMatrixd::createInstance());
}

int  PythonQtWrapper_SoMFMatrixd::find(SoMFMatrixd* theWrappedObject, const SbMatrixd&  targetValue, bool  addIfNotFound)
{
  return ( theWrappedObject->find(targetValue, addIfNotFound));
}

void PythonQtWrapper_SoMFMatrixd::finishEditing(SoMFMatrixd* theWrappedObject)
{
  ( theWrappedObject->finishEditing());
}

SoType  PythonQtWrapper_SoMFMatrixd::static_SoMFMatrixd_getClassTypeId()
{
  return (SoMFMatrixd::getClassTypeId());
}

bool  PythonQtWrapper_SoMFMatrixd::__ne__(SoMFMatrixd* theWrappedObject, const SoMFMatrixd&  f) const
{
  return ( (*theWrappedObject)!= f);
}

const SbMatrixd*  PythonQtWrapper_SoMFMatrixd::operator_assign(SoMFMatrixd* theWrappedObject, const SbMatrixd&  newValue)
{
  return &( (*theWrappedObject)= newValue);
}

const SoMFMatrixd*  PythonQtWrapper_SoMFMatrixd::operator_assign(SoMFMatrixd* theWrappedObject, const SoMFMatrixd&  f)
{
  return &( (*theWrappedObject)= f);
}

bool  PythonQtWrapper_SoMFMatrixd::__eq__(SoMFMatrixd* theWrappedObject, const SoMFMatrixd&  f) const
{
  return ( (*theWrappedObject)== f);
}

const SbMatrixd*  PythonQtWrapper_SoMFMatrixd::operator_subscript(SoMFMatrixd* theWrappedObject, int  i) const
{
  return &( (*theWrappedObject)[i]);
}

void PythonQtWrapper_SoMFMatrixd::set1Value(SoMFMatrixd* theWrappedObject, int  index, const SbMatrixd&  newValue)
{
  ( theWrappedObject->set1Value(index, newValue));
}

void PythonQtWrapper_SoMFMatrixd::setValue(SoMFMatrixd* theWrappedObject, const SbMatrixd&  newValue)
{
  ( theWrappedObject->setValue(newValue));
}

void PythonQtWrapper_SoMFMatrixd::setValue(SoMFMatrixd* theWrappedObject, double  a11, double  a12, double  a13, double  a14, double  a21, double  a22, double  a23, double  a24, double  a31, double  a32, double  a33, double  a34, double  a41, double  a42, double  a43, double  a44)
{
  ( theWrappedObject->setValue(a11, a12, a13, a14, a21, a22, a23, a24, a31, a32, a33, a34, a41, a42, a43, a44));
}

void PythonQtWrapper_SoMFMatrixd::setValues(SoMFMatrixd* theWrappedObject, int  start, int  num, const SbMatrixd*  newValues)
{
  ( theWrappedObject->setValues(start, num, newValues));
}



SoMFName* PythonQtWrapper_SoMFName::new_SoMFName()
{ 
return new SoMFName(); }

void*  PythonQtWrapper_SoMFName::static_SoMFName_createInstance()
{
  return (SoMFName::createInstance());
}

int  PythonQtWrapper_SoMFName::find(SoMFName* theWrappedObject, const SbName&  targetValue, bool  addIfNotFound)
{
  return ( theWrappedObject->find(targetValue, addIfNotFound));
}

void PythonQtWrapper_SoMFName::finishEditing(SoMFName* theWrappedObject)
{
  ( theWrappedObject->finishEditing());
}

SoType  PythonQtWrapper_SoMFName::static_SoMFName_getClassTypeId()
{
  return (SoMFName::getClassTypeId());
}

bool  PythonQtWrapper_SoMFName::__ne__(SoMFName* theWrappedObject, const SoMFName&  f) const
{
  return ( (*theWrappedObject)!= f);
}

const SbName*  PythonQtWrapper_SoMFName::operator_assign(SoMFName* theWrappedObject, const SbName&  newValue)
{
  return &( (*theWrappedObject)= newValue);
}

const SoMFName*  PythonQtWrapper_SoMFName::operator_assign(SoMFName* theWrappedObject, const SoMFName&  f)
{
  return &( (*theWrappedObject)= f);
}

bool  PythonQtWrapper_SoMFName::__eq__(SoMFName* theWrappedObject, const SoMFName&  f) const
{
  return ( (*theWrappedObject)== f);
}

const SbName*  PythonQtWrapper_SoMFName::operator_subscript(SoMFName* theWrappedObject, int  i) const
{
  return &( (*theWrappedObject)[i]);
}

void PythonQtWrapper_SoMFName::set1Value(SoMFName* theWrappedObject, int  index, const SbName&  newValue)
{
  ( theWrappedObject->set1Value(index, newValue));
}

void PythonQtWrapper_SoMFName::setValue(SoMFName* theWrappedObject, const SbName&  newValue)
{
  ( theWrappedObject->setValue(newValue));
}

void PythonQtWrapper_SoMFName::setValue(SoMFName* theWrappedObject, const char*  string)
{
  ( theWrappedObject->setValue(string));
}

void PythonQtWrapper_SoMFName::setValues(SoMFName* theWrappedObject, int  start, int  num, const SbName*  newValues)
{
  ( theWrappedObject->setValues(start, num, newValues));
}

void PythonQtWrapper_SoMFName::setValues(SoMFName* theWrappedObject, int  start, int  num, const char**  strings)
{
  ( theWrappedObject->setValues(start, num, strings));
}



SoMFNode* PythonQtWrapper_SoMFNode::new_SoMFNode()
{ 
return new SoMFNode(); }

void*  PythonQtWrapper_SoMFNode::static_SoMFNode_createInstance()
{
  return (SoMFNode::createInstance());
}

int  PythonQtWrapper_SoMFNode::find(SoMFNode* theWrappedObject, SoNode*  targetValue, bool  addIfNotFound)
{
  return ( theWrappedObject->find(targetValue, addIfNotFound));
}

void PythonQtWrapper_SoMFNode::finishEditing(SoMFNode* theWrappedObject)
{
  ( theWrappedObject->finishEditing());
}

SoType  PythonQtWrapper_SoMFNode::static_SoMFNode_getClassTypeId()
{
  return (SoMFNode::getClassTypeId());
}

bool  PythonQtWrapper_SoMFNode::__ne__(SoMFNode* theWrappedObject, const SoMFNode&  f) const
{
  return ( (*theWrappedObject)!= f);
}

SoNode*  PythonQtWrapper_SoMFNode::operator_assign(SoMFNode* theWrappedObject, SoNode*  newValue)
{
  return ( (*theWrappedObject)= newValue);
}

const SoMFNode*  PythonQtWrapper_SoMFNode::operator_assign(SoMFNode* theWrappedObject, const SoMFNode&  f)
{
  return &( (*theWrappedObject)= f);
}

bool  PythonQtWrapper_SoMFNode::__eq__(SoMFNode* theWrappedObject, const SoMFNode&  f) const
{
  return ( (*theWrappedObject)== f);
}

SoNode*  PythonQtWrapper_SoMFNode::operator_subscript(SoMFNode* theWrappedObject, int  i) const
{
  return ( (*theWrappedObject)[i]);
}

void PythonQtWrapper_SoMFNode::set1Value(SoMFNode* theWrappedObject, int  index, SoNode*  newValue)
{
  ( theWrappedObject->set1Value(index, newValue));
}

void PythonQtWrapper_SoMFNode::setValue(SoMFNode* theWrappedObject, SoNode*  newValue)
{
  ( theWrappedObject->setValue(newValue));
}

void PythonQtWrapper_SoMFNode::setValues(SoMFNode* theWrappedObject, int  start, int  num, const SoNode**  newValues)
{
  ( theWrappedObject->setValues(start, num, newValues));
}



SoMFPath* PythonQtWrapper_SoMFPath::new_SoMFPath()
{ 
return new SoMFPath(); }

void*  PythonQtWrapper_SoMFPath::static_SoMFPath_createInstance()
{
  return (SoMFPath::createInstance());
}

int  PythonQtWrapper_SoMFPath::find(SoMFPath* theWrappedObject, SoPath*  targetValue, bool  addIfNotFound)
{
  return ( theWrappedObject->find(targetValue, addIfNotFound));
}

void PythonQtWrapper_SoMFPath::finishEditing(SoMFPath* theWrappedObject)
{
  ( theWrappedObject->finishEditing());
}

SoType  PythonQtWrapper_SoMFPath::static_SoMFPath_getClassTypeId()
{
  return (SoMFPath::getClassTypeId());
}

bool  PythonQtWrapper_SoMFPath::__ne__(SoMFPath* theWrappedObject, const SoMFPath&  f) const
{
  return ( (*theWrappedObject)!= f);
}

SoPath*  PythonQtWrapper_SoMFPath::operator_assign(SoMFPath* theWrappedObject, SoPath*  newValue)
{
  return ( (*theWrappedObject)= newValue);
}

const SoMFPath*  PythonQtWrapper_SoMFPath::operator_assign(SoMFPath* theWrappedObject, const SoMFPath&  f)
{
  return &( (*theWrappedObject)= f);
}

bool  PythonQtWrapper_SoMFPath::__eq__(SoMFPath* theWrappedObject, const SoMFPath&  f) const
{
  return ( (*theWrappedObject)== f);
}

SoPath*  PythonQtWrapper_SoMFPath::operator_subscript(SoMFPath* theWrappedObject, int  i) const
{
  return ( (*theWrappedObject)[i]);
}

void PythonQtWrapper_SoMFPath::set1Value(SoMFPath* theWrappedObject, int  index, SoPath*  newValue)
{
  ( theWrappedObject->set1Value(index, newValue));
}

void PythonQtWrapper_SoMFPath::setValue(SoMFPath* theWrappedObject, SoPath*  newValue)
{
  ( theWrappedObject->setValue(newValue));
}

void PythonQtWrapper_SoMFPath::setValues(SoMFPath* theWrappedObject, int  start, int  num, const SoPath**  newValues)
{
  ( theWrappedObject->setValues(start, num, newValues));
}



SoMFPlane* PythonQtWrapper_SoMFPlane::new_SoMFPlane()
{ 
return new SoMFPlane(); }

void*  PythonQtWrapper_SoMFPlane::static_SoMFPlane_createInstance()
{
  return (SoMFPlane::createInstance());
}

int  PythonQtWrapper_SoMFPlane::find(SoMFPlane* theWrappedObject, SbPlane  targetValue, bool  addIfNotFound)
{
  return ( theWrappedObject->find(targetValue, addIfNotFound));
}

void PythonQtWrapper_SoMFPlane::finishEditing(SoMFPlane* theWrappedObject)
{
  ( theWrappedObject->finishEditing());
}

SoType  PythonQtWrapper_SoMFPlane::static_SoMFPlane_getClassTypeId()
{
  return (SoMFPlane::getClassTypeId());
}

bool  PythonQtWrapper_SoMFPlane::__ne__(SoMFPlane* theWrappedObject, const SoMFPlane&  f) const
{
  return ( (*theWrappedObject)!= f);
}

SbPlane  PythonQtWrapper_SoMFPlane::operator_assign(SoMFPlane* theWrappedObject, SbPlane  newValue)
{
  return ( (*theWrappedObject)= newValue);
}

const SoMFPlane*  PythonQtWrapper_SoMFPlane::operator_assign(SoMFPlane* theWrappedObject, const SoMFPlane&  f)
{
  return &( (*theWrappedObject)= f);
}

bool  PythonQtWrapper_SoMFPlane::__eq__(SoMFPlane* theWrappedObject, const SoMFPlane&  f) const
{
  return ( (*theWrappedObject)== f);
}

SbPlane  PythonQtWrapper_SoMFPlane::operator_subscript(SoMFPlane* theWrappedObject, int  i) const
{
  return ( (*theWrappedObject)[i]);
}

void PythonQtWrapper_SoMFPlane::set1Value(SoMFPlane* theWrappedObject, int  index, SbPlane  newValue)
{
  ( theWrappedObject->set1Value(index, newValue));
}

void PythonQtWrapper_SoMFPlane::setValue(SoMFPlane* theWrappedObject, SbPlane  newValue)
{
  ( theWrappedObject->setValue(newValue));
}

void PythonQtWrapper_SoMFPlane::setValues(SoMFPlane* theWrappedObject, int  start, int  num, const SbPlane*  newValues)
{
  ( theWrappedObject->setValues(start, num, newValues));
}



SoMFPlaned* PythonQtWrapper_SoMFPlaned::new_SoMFPlaned()
{ 
return new SoMFPlaned(); }

void*  PythonQtWrapper_SoMFPlaned::static_SoMFPlaned_createInstance()
{
  return (SoMFPlaned::createInstance());
}

int  PythonQtWrapper_SoMFPlaned::find(SoMFPlaned* theWrappedObject, SbPlaned  targetValue, bool  addIfNotFound)
{
  return ( theWrappedObject->find(targetValue, addIfNotFound));
}

void PythonQtWrapper_SoMFPlaned::finishEditing(SoMFPlaned* theWrappedObject)
{
  ( theWrappedObject->finishEditing());
}

SoType  PythonQtWrapper_SoMFPlaned::static_SoMFPlaned_getClassTypeId()
{
  return (SoMFPlaned::getClassTypeId());
}

bool  PythonQtWrapper_SoMFPlaned::__ne__(SoMFPlaned* theWrappedObject, const SoMFPlaned&  f) const
{
  return ( (*theWrappedObject)!= f);
}

SbPlaned  PythonQtWrapper_SoMFPlaned::operator_assign(SoMFPlaned* theWrappedObject, SbPlaned  newValue)
{
  return ( (*theWrappedObject)= newValue);
}

const SoMFPlaned*  PythonQtWrapper_SoMFPlaned::operator_assign(SoMFPlaned* theWrappedObject, const SoMFPlaned&  f)
{
  return &( (*theWrappedObject)= f);
}

bool  PythonQtWrapper_SoMFPlaned::__eq__(SoMFPlaned* theWrappedObject, const SoMFPlaned&  f) const
{
  return ( (*theWrappedObject)== f);
}

SbPlaned  PythonQtWrapper_SoMFPlaned::operator_subscript(SoMFPlaned* theWrappedObject, int  i) const
{
  return ( (*theWrappedObject)[i]);
}

void PythonQtWrapper_SoMFPlaned::set1Value(SoMFPlaned* theWrappedObject, int  index, SbPlaned  newValue)
{
  ( theWrappedObject->set1Value(index, newValue));
}

void PythonQtWrapper_SoMFPlaned::setValue(SoMFPlaned* theWrappedObject, SbPlaned  newValue)
{
  ( theWrappedObject->setValue(newValue));
}

void PythonQtWrapper_SoMFPlaned::setValues(SoMFPlaned* theWrappedObject, int  start, int  num, const SbPlaned*  newValues)
{
  ( theWrappedObject->setValues(start, num, newValues));
}



SoMFRotation* PythonQtWrapper_SoMFRotation::new_SoMFRotation()
{ 
return new SoMFRotation(); }

void*  PythonQtWrapper_SoMFRotation::static_SoMFRotation_createInstance()
{
  return (SoMFRotation::createInstance());
}

int  PythonQtWrapper_SoMFRotation::find(SoMFRotation* theWrappedObject, const SbRotation&  targetValue, bool  addIfNotFound)
{
  return ( theWrappedObject->find(targetValue, addIfNotFound));
}

void PythonQtWrapper_SoMFRotation::finishEditing(SoMFRotation* theWrappedObject)
{
  ( theWrappedObject->finishEditing());
}

SoType  PythonQtWrapper_SoMFRotation::static_SoMFRotation_getClassTypeId()
{
  return (SoMFRotation::getClassTypeId());
}

bool  PythonQtWrapper_SoMFRotation::__ne__(SoMFRotation* theWrappedObject, const SoMFRotation&  f) const
{
  return ( (*theWrappedObject)!= f);
}

const SbRotation*  PythonQtWrapper_SoMFRotation::operator_assign(SoMFRotation* theWrappedObject, const SbRotation&  newValue)
{
  return &( (*theWrappedObject)= newValue);
}

const SoMFRotation*  PythonQtWrapper_SoMFRotation::operator_assign(SoMFRotation* theWrappedObject, const SoMFRotation&  f)
{
  return &( (*theWrappedObject)= f);
}

bool  PythonQtWrapper_SoMFRotation::__eq__(SoMFRotation* theWrappedObject, const SoMFRotation&  f) const
{
  return ( (*theWrappedObject)== f);
}

const SbRotation*  PythonQtWrapper_SoMFRotation::operator_subscript(SoMFRotation* theWrappedObject, int  i) const
{
  return &( (*theWrappedObject)[i]);
}

void PythonQtWrapper_SoMFRotation::set1Value(SoMFRotation* theWrappedObject, int  index, const SbRotation&  newValue)
{
  ( theWrappedObject->set1Value(index, newValue));
}

void PythonQtWrapper_SoMFRotation::set1Value(SoMFRotation* theWrappedObject, int  index, const SbVec3f&  axis, float  angle)
{
  ( theWrappedObject->set1Value(index, axis, angle));
}

void PythonQtWrapper_SoMFRotation::set1Value(SoMFRotation* theWrappedObject, int  index, float  q0, float  q1, float  q2, float  q3)
{
  ( theWrappedObject->set1Value(index, q0, q1, q2, q3));
}

void PythonQtWrapper_SoMFRotation::setValue(SoMFRotation* theWrappedObject, const SbRotation&  newValue)
{
  ( theWrappedObject->setValue(newValue));
}

void PythonQtWrapper_SoMFRotation::setValue(SoMFRotation* theWrappedObject, const SbVec3f&  axis, float  angle)
{
  ( theWrappedObject->setValue(axis, angle));
}

void PythonQtWrapper_SoMFRotation::setValue(SoMFRotation* theWrappedObject, float  q0, float  q1, float  q2, float  q3)
{
  ( theWrappedObject->setValue(q0, q1, q2, q3));
}

void PythonQtWrapper_SoMFRotation::setValues(SoMFRotation* theWrappedObject, int  start, int  num, const SbRotation*  newValues)
{
  ( theWrappedObject->setValues(start, num, newValues));
}



SoMFRotationd* PythonQtWrapper_SoMFRotationd::new_SoMFRotationd()
{ 
return new SoMFRotationd(); }

void*  PythonQtWrapper_SoMFRotationd::static_SoMFRotationd_createInstance()
{
  return (SoMFRotationd::createInstance());
}

int  PythonQtWrapper_SoMFRotationd::find(SoMFRotationd* theWrappedObject, const SbRotationd&  targetValue, bool  addIfNotFound)
{
  return ( theWrappedObject->find(targetValue, addIfNotFound));
}

void PythonQtWrapper_SoMFRotationd::finishEditing(SoMFRotationd* theWrappedObject)
{
  ( theWrappedObject->finishEditing());
}

SoType  PythonQtWrapper_SoMFRotationd::static_SoMFRotationd_getClassTypeId()
{
  return (SoMFRotationd::getClassTypeId());
}

bool  PythonQtWrapper_SoMFRotationd::__ne__(SoMFRotationd* theWrappedObject, const SoMFRotationd&  f) const
{
  return ( (*theWrappedObject)!= f);
}

const SbRotationd*  PythonQtWrapper_SoMFRotationd::operator_assign(SoMFRotationd* theWrappedObject, const SbRotationd&  newValue)
{
  return &( (*theWrappedObject)= newValue);
}

const SoMFRotationd*  PythonQtWrapper_SoMFRotationd::operator_assign(SoMFRotationd* theWrappedObject, const SoMFRotationd&  f)
{
  return &( (*theWrappedObject)= f);
}

bool  PythonQtWrapper_SoMFRotationd::__eq__(SoMFRotationd* theWrappedObject, const SoMFRotationd&  f) const
{
  return ( (*theWrappedObject)== f);
}

const SbRotationd*  PythonQtWrapper_SoMFRotationd::operator_subscript(SoMFRotationd* theWrappedObject, int  i) const
{
  return &( (*theWrappedObject)[i]);
}

void PythonQtWrapper_SoMFRotationd::set1Value(SoMFRotationd* theWrappedObject, int  index, const SbRotationd&  newValue)
{
  ( theWrappedObject->set1Value(index, newValue));
}

void PythonQtWrapper_SoMFRotationd::set1Value(SoMFRotationd* theWrappedObject, int  index, const SbVec3d&  axis, double  angle)
{
  ( theWrappedObject->set1Value(index, axis, angle));
}

void PythonQtWrapper_SoMFRotationd::set1Value(SoMFRotationd* theWrappedObject, int  index, double  q0, double  q1, double  q2, double  q3)
{
  ( theWrappedObject->set1Value(index, q0, q1, q2, q3));
}

void PythonQtWrapper_SoMFRotationd::setValue(SoMFRotationd* theWrappedObject, const SbRotationd&  newValue)
{
  ( theWrappedObject->setValue(newValue));
}

void PythonQtWrapper_SoMFRotationd::setValue(SoMFRotationd* theWrappedObject, const SbVec3d&  axis, double  angle)
{
  ( theWrappedObject->setValue(axis, angle));
}

void PythonQtWrapper_SoMFRotationd::setValue(SoMFRotationd* theWrappedObject, double  q0, double  q1, double  q2, double  q3)
{
  ( theWrappedObject->setValue(q0, q1, q2, q3));
}

void PythonQtWrapper_SoMFRotationd::setValues(SoMFRotationd* theWrappedObject, int  start, int  num, const SbRotationd*  newValues)
{
  ( theWrappedObject->setValues(start, num, newValues));
}



SoMFShort* PythonQtWrapper_SoMFShort::new_SoMFShort()
{ 
return new SoMFShort(); }

void*  PythonQtWrapper_SoMFShort::static_SoMFShort_createInstance()
{
  return (SoMFShort::createInstance());
}

int  PythonQtWrapper_SoMFShort::find(SoMFShort* theWrappedObject, short  targetValue, bool  addIfNotFound)
{
  return ( theWrappedObject->find(targetValue, addIfNotFound));
}

void PythonQtWrapper_SoMFShort::finishEditing(SoMFShort* theWrappedObject)
{
  ( theWrappedObject->finishEditing());
}

SoType  PythonQtWrapper_SoMFShort::static_SoMFShort_getClassTypeId()
{
  return (SoMFShort::getClassTypeId());
}

bool  PythonQtWrapper_SoMFShort::__ne__(SoMFShort* theWrappedObject, const SoMFShort&  f) const
{
  return ( (*theWrappedObject)!= f);
}

const SoMFShort*  PythonQtWrapper_SoMFShort::operator_assign(SoMFShort* theWrappedObject, const SoMFShort&  f)
{
  return &( (*theWrappedObject)= f);
}

short  PythonQtWrapper_SoMFShort::operator_assign(SoMFShort* theWrappedObject, short  newValue)
{
  return ( (*theWrappedObject)= newValue);
}

bool  PythonQtWrapper_SoMFShort::__eq__(SoMFShort* theWrappedObject, const SoMFShort&  f) const
{
  return ( (*theWrappedObject)== f);
}

short  PythonQtWrapper_SoMFShort::operator_subscript(SoMFShort* theWrappedObject, int  i) const
{
  return ( (*theWrappedObject)[i]);
}

void PythonQtWrapper_SoMFShort::set1Value(SoMFShort* theWrappedObject, int  index, short  newValue)
{
  ( theWrappedObject->set1Value(index, newValue));
}

void PythonQtWrapper_SoMFShort::setValue(SoMFShort* theWrappedObject, short  newValue)
{
  ( theWrappedObject->setValue(newValue));
}

void PythonQtWrapper_SoMFShort::setValues(SoMFShort* theWrappedObject, int  start, int  num, const short*  newValues)
{
  ( theWrappedObject->setValues(start, num, newValues));
}



SoMFString* PythonQtWrapper_SoMFString::new_SoMFString()
{ 
return new SoMFString(); }

void*  PythonQtWrapper_SoMFString::static_SoMFString_createInstance()
{
  return (SoMFString::createInstance());
}

void PythonQtWrapper_SoMFString::deleteText(SoMFString* theWrappedObject, int  fromLine, int  fromChar, int  toLine, int  toChar)
{
  ( theWrappedObject->deleteText(fromLine, fromChar, toLine, toChar));
}

int  PythonQtWrapper_SoMFString::find(SoMFString* theWrappedObject, const SbString&  targetValue, bool  addIfNotFound)
{
  return ( theWrappedObject->find(targetValue, addIfNotFound));
}

void PythonQtWrapper_SoMFString::finishEditing(SoMFString* theWrappedObject)
{
  ( theWrappedObject->finishEditing());
}

SoType  PythonQtWrapper_SoMFString::static_SoMFString_getClassTypeId()
{
  return (SoMFString::getClassTypeId());
}

bool  PythonQtWrapper_SoMFString::__ne__(SoMFString* theWrappedObject, const SoMFString&  f) const
{
  return ( (*theWrappedObject)!= f);
}

const SbString*  PythonQtWrapper_SoMFString::operator_assign(SoMFString* theWrappedObject, const SbString&  newValue)
{
  return &( (*theWrappedObject)= newValue);
}

const SoMFString*  PythonQtWrapper_SoMFString::operator_assign(SoMFString* theWrappedObject, const SoMFString&  f)
{
  return &( (*theWrappedObject)= f);
}

bool  PythonQtWrapper_SoMFString::__eq__(SoMFString* theWrappedObject, const SoMFString&  f) const
{
  return ( (*theWrappedObject)== f);
}

const SbString*  PythonQtWrapper_SoMFString::operator_subscript(SoMFString* theWrappedObject, int  i) const
{
  return &( (*theWrappedObject)[i]);
}

void PythonQtWrapper_SoMFString::set1Value(SoMFString* theWrappedObject, int  index, const SbString&  newValue)
{
  ( theWrappedObject->set1Value(index, newValue));
}

void PythonQtWrapper_SoMFString::setValue(SoMFString* theWrappedObject, const SbString&  newValue)
{
  ( theWrappedObject->setValue(newValue));
}

void PythonQtWrapper_SoMFString::setValue(SoMFString* theWrappedObject, const char*  string)
{
  ( theWrappedObject->setValue(string));
}

void PythonQtWrapper_SoMFString::setValues(SoMFString* theWrappedObject, int  start, int  num, const SbString*  newValues)
{
  ( theWrappedObject->setValues(start, num, newValues));
}

void PythonQtWrapper_SoMFString::setValues(SoMFString* theWrappedObject, int  start, int  num, const char**  strings)
{
  ( theWrappedObject->setValues(start, num, strings));
}



SoMFTime* PythonQtWrapper_SoMFTime::new_SoMFTime()
{ 
return new SoMFTime(); }

void*  PythonQtWrapper_SoMFTime::static_SoMFTime_createInstance()
{
  return (SoMFTime::createInstance());
}

int  PythonQtWrapper_SoMFTime::find(SoMFTime* theWrappedObject, const SbTime&  targetValue, bool  addIfNotFound)
{
  return ( theWrappedObject->find(targetValue, addIfNotFound));
}

void PythonQtWrapper_SoMFTime::finishEditing(SoMFTime* theWrappedObject)
{
  ( theWrappedObject->finishEditing());
}

SoType  PythonQtWrapper_SoMFTime::static_SoMFTime_getClassTypeId()
{
  return (SoMFTime::getClassTypeId());
}

bool  PythonQtWrapper_SoMFTime::__ne__(SoMFTime* theWrappedObject, const SoMFTime&  f) const
{
  return ( (*theWrappedObject)!= f);
}

const SbTime*  PythonQtWrapper_SoMFTime::operator_assign(SoMFTime* theWrappedObject, const SbTime&  newValue)
{
  return &( (*theWrappedObject)= newValue);
}

const SoMFTime*  PythonQtWrapper_SoMFTime::operator_assign(SoMFTime* theWrappedObject, const SoMFTime&  f)
{
  return &( (*theWrappedObject)= f);
}

bool  PythonQtWrapper_SoMFTime::__eq__(SoMFTime* theWrappedObject, const SoMFTime&  f) const
{
  return ( (*theWrappedObject)== f);
}

const SbTime*  PythonQtWrapper_SoMFTime::operator_subscript(SoMFTime* theWrappedObject, int  i) const
{
  return &( (*theWrappedObject)[i]);
}

void PythonQtWrapper_SoMFTime::set1Value(SoMFTime* theWrappedObject, int  index, const SbTime&  newValue)
{
  ( theWrappedObject->set1Value(index, newValue));
}

void PythonQtWrapper_SoMFTime::setValue(SoMFTime* theWrappedObject, const SbTime&  newValue)
{
  ( theWrappedObject->setValue(newValue));
}

void PythonQtWrapper_SoMFTime::setValues(SoMFTime* theWrappedObject, int  start, int  num, const SbTime*  newValues)
{
  ( theWrappedObject->setValues(start, num, newValues));
}



SoMFUInt32* PythonQtWrapper_SoMFUInt32::new_SoMFUInt32()
{ 
return new SoMFUInt32(); }

void*  PythonQtWrapper_SoMFUInt32::static_SoMFUInt32_createInstance()
{
  return (SoMFUInt32::createInstance());
}

int  PythonQtWrapper_SoMFUInt32::find(SoMFUInt32* theWrappedObject, unsigned int  targetValue, bool  addIfNotFound)
{
  return ( theWrappedObject->find(targetValue, addIfNotFound));
}

void PythonQtWrapper_SoMFUInt32::finishEditing(SoMFUInt32* theWrappedObject)
{
  ( theWrappedObject->finishEditing());
}

SoType  PythonQtWrapper_SoMFUInt32::static_SoMFUInt32_getClassTypeId()
{
  return (SoMFUInt32::getClassTypeId());
}

bool  PythonQtWrapper_SoMFUInt32::__ne__(SoMFUInt32* theWrappedObject, const SoMFUInt32&  f) const
{
  return ( (*theWrappedObject)!= f);
}

const SoMFUInt32*  PythonQtWrapper_SoMFUInt32::operator_assign(SoMFUInt32* theWrappedObject, const SoMFUInt32&  f)
{
  return &( (*theWrappedObject)= f);
}

unsigned int  PythonQtWrapper_SoMFUInt32::operator_assign(SoMFUInt32* theWrappedObject, unsigned int  newValue)
{
  return ( (*theWrappedObject)= newValue);
}

bool  PythonQtWrapper_SoMFUInt32::__eq__(SoMFUInt32* theWrappedObject, const SoMFUInt32&  f) const
{
  return ( (*theWrappedObject)== f);
}

unsigned int  PythonQtWrapper_SoMFUInt32::operator_subscript(SoMFUInt32* theWrappedObject, int  i) const
{
  return ( (*theWrappedObject)[i]);
}

void PythonQtWrapper_SoMFUInt32::set1Value(SoMFUInt32* theWrappedObject, int  index, unsigned int  newValue)
{
  ( theWrappedObject->set1Value(index, newValue));
}

void PythonQtWrapper_SoMFUInt32::setValue(SoMFUInt32* theWrappedObject, unsigned int  newValue)
{
  ( theWrappedObject->setValue(newValue));
}

void PythonQtWrapper_SoMFUInt32::setValues(SoMFUInt32* theWrappedObject, int  start, int  num, const unsigned int*  newValues)
{
  ( theWrappedObject->setValues(start, num, newValues));
}



SoMFUShort* PythonQtWrapper_SoMFUShort::new_SoMFUShort()
{ 
return new SoMFUShort(); }

void*  PythonQtWrapper_SoMFUShort::static_SoMFUShort_createInstance()
{
  return (SoMFUShort::createInstance());
}

int  PythonQtWrapper_SoMFUShort::find(SoMFUShort* theWrappedObject, unsigned short  targetValue, bool  addIfNotFound)
{
  return ( theWrappedObject->find(targetValue, addIfNotFound));
}

void PythonQtWrapper_SoMFUShort::finishEditing(SoMFUShort* theWrappedObject)
{
  ( theWrappedObject->finishEditing());
}

SoType  PythonQtWrapper_SoMFUShort::static_SoMFUShort_getClassTypeId()
{
  return (SoMFUShort::getClassTypeId());
}

bool  PythonQtWrapper_SoMFUShort::__ne__(SoMFUShort* theWrappedObject, const SoMFUShort&  f) const
{
  return ( (*theWrappedObject)!= f);
}

const SoMFUShort*  PythonQtWrapper_SoMFUShort::operator_assign(SoMFUShort* theWrappedObject, const SoMFUShort&  f)
{
  return &( (*theWrappedObject)= f);
}

unsigned short  PythonQtWrapper_SoMFUShort::operator_assign(SoMFUShort* theWrappedObject, unsigned short  newValue)
{
  return ( (*theWrappedObject)= newValue);
}

bool  PythonQtWrapper_SoMFUShort::__eq__(SoMFUShort* theWrappedObject, const SoMFUShort&  f) const
{
  return ( (*theWrappedObject)== f);
}

unsigned short  PythonQtWrapper_SoMFUShort::operator_subscript(SoMFUShort* theWrappedObject, int  i) const
{
  return ( (*theWrappedObject)[i]);
}

void PythonQtWrapper_SoMFUShort::set1Value(SoMFUShort* theWrappedObject, int  index, unsigned short  newValue)
{
  ( theWrappedObject->set1Value(index, newValue));
}

void PythonQtWrapper_SoMFUShort::setValue(SoMFUShort* theWrappedObject, unsigned short  newValue)
{
  ( theWrappedObject->setValue(newValue));
}

void PythonQtWrapper_SoMFUShort::setValues(SoMFUShort* theWrappedObject, int  start, int  num, const unsigned short*  newValues)
{
  ( theWrappedObject->setValues(start, num, newValues));
}



SoMFVec2d* PythonQtWrapper_SoMFVec2d::new_SoMFVec2d()
{ 
return new SoMFVec2d(); }

void*  PythonQtWrapper_SoMFVec2d::static_SoMFVec2d_createInstance()
{
  return (SoMFVec2d::createInstance());
}

int  PythonQtWrapper_SoMFVec2d::find(SoMFVec2d* theWrappedObject, const SbVec2d&  targetValue, bool  addIfNotFound)
{
  return ( theWrappedObject->find(targetValue, addIfNotFound));
}

void PythonQtWrapper_SoMFVec2d::finishEditing(SoMFVec2d* theWrappedObject)
{
  ( theWrappedObject->finishEditing());
}

SoType  PythonQtWrapper_SoMFVec2d::static_SoMFVec2d_getClassTypeId()
{
  return (SoMFVec2d::getClassTypeId());
}

bool  PythonQtWrapper_SoMFVec2d::__ne__(SoMFVec2d* theWrappedObject, const SoMFVec2d&  f) const
{
  return ( (*theWrappedObject)!= f);
}

const SbVec2d*  PythonQtWrapper_SoMFVec2d::operator_assign(SoMFVec2d* theWrappedObject, const SbVec2d&  newValue)
{
  return &( (*theWrappedObject)= newValue);
}

const SoMFVec2d*  PythonQtWrapper_SoMFVec2d::operator_assign(SoMFVec2d* theWrappedObject, const SoMFVec2d&  f)
{
  return &( (*theWrappedObject)= f);
}

bool  PythonQtWrapper_SoMFVec2d::__eq__(SoMFVec2d* theWrappedObject, const SoMFVec2d&  f) const
{
  return ( (*theWrappedObject)== f);
}

const SbVec2d*  PythonQtWrapper_SoMFVec2d::operator_subscript(SoMFVec2d* theWrappedObject, int  i) const
{
  return &( (*theWrappedObject)[i]);
}

void PythonQtWrapper_SoMFVec2d::set1Value(SoMFVec2d* theWrappedObject, int  index, const SbVec2d&  newValue)
{
  ( theWrappedObject->set1Value(index, newValue));
}

void PythonQtWrapper_SoMFVec2d::set1Value(SoMFVec2d* theWrappedObject, int  index, double  x, double  y)
{
  ( theWrappedObject->set1Value(index, x, y));
}

void PythonQtWrapper_SoMFVec2d::setValue(SoMFVec2d* theWrappedObject, const SbVec2d&  newValue)
{
  ( theWrappedObject->setValue(newValue));
}

void PythonQtWrapper_SoMFVec2d::setValue(SoMFVec2d* theWrappedObject, double  x, double  y)
{
  ( theWrappedObject->setValue(x, y));
}

void PythonQtWrapper_SoMFVec2d::setValues(SoMFVec2d* theWrappedObject, int  start, int  num, const SbVec2d*  newValues)
{
  ( theWrappedObject->setValues(start, num, newValues));
}



SoMFVec2f* PythonQtWrapper_SoMFVec2f::new_SoMFVec2f()
{ 
return new SoMFVec2f(); }

void*  PythonQtWrapper_SoMFVec2f::static_SoMFVec2f_createInstance()
{
  return (SoMFVec2f::createInstance());
}

int  PythonQtWrapper_SoMFVec2f::find(SoMFVec2f* theWrappedObject, const SbVec2f&  targetValue, bool  addIfNotFound)
{
  return ( theWrappedObject->find(targetValue, addIfNotFound));
}

void PythonQtWrapper_SoMFVec2f::finishEditing(SoMFVec2f* theWrappedObject)
{
  ( theWrappedObject->finishEditing());
}

SoType  PythonQtWrapper_SoMFVec2f::static_SoMFVec2f_getClassTypeId()
{
  return (SoMFVec2f::getClassTypeId());
}

bool  PythonQtWrapper_SoMFVec2f::__ne__(SoMFVec2f* theWrappedObject, const SoMFVec2f&  f) const
{
  return ( (*theWrappedObject)!= f);
}

const SbVec2f*  PythonQtWrapper_SoMFVec2f::operator_assign(SoMFVec2f* theWrappedObject, const SbVec2f&  newValue)
{
  return &( (*theWrappedObject)= newValue);
}

const SoMFVec2f*  PythonQtWrapper_SoMFVec2f::operator_assign(SoMFVec2f* theWrappedObject, const SoMFVec2f&  f)
{
  return &( (*theWrappedObject)= f);
}

bool  PythonQtWrapper_SoMFVec2f::__eq__(SoMFVec2f* theWrappedObject, const SoMFVec2f&  f) const
{
  return ( (*theWrappedObject)== f);
}

const SbVec2f*  PythonQtWrapper_SoMFVec2f::operator_subscript(SoMFVec2f* theWrappedObject, int  i) const
{
  return &( (*theWrappedObject)[i]);
}

void PythonQtWrapper_SoMFVec2f::set1Value(SoMFVec2f* theWrappedObject, int  index, const SbVec2f&  newValue)
{
  ( theWrappedObject->set1Value(index, newValue));
}

void PythonQtWrapper_SoMFVec2f::set1Value(SoMFVec2f* theWrappedObject, int  index, float  x, float  y)
{
  ( theWrappedObject->set1Value(index, x, y));
}

void PythonQtWrapper_SoMFVec2f::setValue(SoMFVec2f* theWrappedObject, const SbVec2f&  newValue)
{
  ( theWrappedObject->setValue(newValue));
}

void PythonQtWrapper_SoMFVec2f::setValue(SoMFVec2f* theWrappedObject, float  x, float  y)
{
  ( theWrappedObject->setValue(x, y));
}

void PythonQtWrapper_SoMFVec2f::setValues(SoMFVec2f* theWrappedObject, int  start, int  num, const SbVec2f*  newValues)
{
  ( theWrappedObject->setValues(start, num, newValues));
}



SoMFVec3d* PythonQtWrapper_SoMFVec3d::new_SoMFVec3d()
{ 
return new SoMFVec3d(); }

void*  PythonQtWrapper_SoMFVec3d::static_SoMFVec3d_createInstance()
{
  return (SoMFVec3d::createInstance());
}

int  PythonQtWrapper_SoMFVec3d::find(SoMFVec3d* theWrappedObject, const SbVec3d&  targetValue, bool  addIfNotFound)
{
  return ( theWrappedObject->find(targetValue, addIfNotFound));
}

void PythonQtWrapper_SoMFVec3d::finishEditing(SoMFVec3d* theWrappedObject)
{
  ( theWrappedObject->finishEditing());
}

SoType  PythonQtWrapper_SoMFVec3d::static_SoMFVec3d_getClassTypeId()
{
  return (SoMFVec3d::getClassTypeId());
}

bool  PythonQtWrapper_SoMFVec3d::__ne__(SoMFVec3d* theWrappedObject, const SoMFVec3d&  f) const
{
  return ( (*theWrappedObject)!= f);
}

const SbVec3d*  PythonQtWrapper_SoMFVec3d::operator_assign(SoMFVec3d* theWrappedObject, const SbVec3d&  newValue)
{
  return &( (*theWrappedObject)= newValue);
}

const SoMFVec3d*  PythonQtWrapper_SoMFVec3d::operator_assign(SoMFVec3d* theWrappedObject, const SoMFVec3d&  f)
{
  return &( (*theWrappedObject)= f);
}

bool  PythonQtWrapper_SoMFVec3d::__eq__(SoMFVec3d* theWrappedObject, const SoMFVec3d&  f) const
{
  return ( (*theWrappedObject)== f);
}

const SbVec3d*  PythonQtWrapper_SoMFVec3d::operator_subscript(SoMFVec3d* theWrappedObject, int  i) const
{
  return &( (*theWrappedObject)[i]);
}

void PythonQtWrapper_SoMFVec3d::set1Value(SoMFVec3d* theWrappedObject, int  index, const SbVec3d&  newValue)
{
  ( theWrappedObject->set1Value(index, newValue));
}

void PythonQtWrapper_SoMFVec3d::set1Value(SoMFVec3d* theWrappedObject, int  index, double  x, double  y, double  z)
{
  ( theWrappedObject->set1Value(index, x, y, z));
}

void PythonQtWrapper_SoMFVec3d::setValue(SoMFVec3d* theWrappedObject, const SbVec3d&  newValue)
{
  ( theWrappedObject->setValue(newValue));
}

void PythonQtWrapper_SoMFVec3d::setValue(SoMFVec3d* theWrappedObject, double  x, double  y, double  z)
{
  ( theWrappedObject->setValue(x, y, z));
}

void PythonQtWrapper_SoMFVec3d::setValues(SoMFVec3d* theWrappedObject, int  start, int  num, const SbVec3d*  newValues)
{
  ( theWrappedObject->setValues(start, num, newValues));
}



SoMFVec3f* PythonQtWrapper_SoMFVec3f::new_SoMFVec3f()
{ 
return new SoMFVec3f(); }

void*  PythonQtWrapper_SoMFVec3f::static_SoMFVec3f_createInstance()
{
  return (SoMFVec3f::createInstance());
}

int  PythonQtWrapper_SoMFVec3f::find(SoMFVec3f* theWrappedObject, const SbVec3f&  targetValue, bool  addIfNotFound)
{
  return ( theWrappedObject->find(targetValue, addIfNotFound));
}

void PythonQtWrapper_SoMFVec3f::finishEditing(SoMFVec3f* theWrappedObject)
{
  ( theWrappedObject->finishEditing());
}

SoType  PythonQtWrapper_SoMFVec3f::static_SoMFVec3f_getClassTypeId()
{
  return (SoMFVec3f::getClassTypeId());
}

bool  PythonQtWrapper_SoMFVec3f::__ne__(SoMFVec3f* theWrappedObject, const SoMFVec3f&  f) const
{
  return ( (*theWrappedObject)!= f);
}

const SbVec3f*  PythonQtWrapper_SoMFVec3f::operator_assign(SoMFVec3f* theWrappedObject, const SbVec3f&  newValue)
{
  return &( (*theWrappedObject)= newValue);
}

const SoMFVec3f*  PythonQtWrapper_SoMFVec3f::operator_assign(SoMFVec3f* theWrappedObject, const SoMFVec3f&  f)
{
  return &( (*theWrappedObject)= f);
}

bool  PythonQtWrapper_SoMFVec3f::__eq__(SoMFVec3f* theWrappedObject, const SoMFVec3f&  f) const
{
  return ( (*theWrappedObject)== f);
}

const SbVec3f*  PythonQtWrapper_SoMFVec3f::operator_subscript(SoMFVec3f* theWrappedObject, int  i) const
{
  return &( (*theWrappedObject)[i]);
}

void PythonQtWrapper_SoMFVec3f::set1Value(SoMFVec3f* theWrappedObject, int  index, const SbVec3f&  newValue)
{
  ( theWrappedObject->set1Value(index, newValue));
}

void PythonQtWrapper_SoMFVec3f::set1Value(SoMFVec3f* theWrappedObject, int  index, float  x, float  y, float  z)
{
  ( theWrappedObject->set1Value(index, x, y, z));
}

void PythonQtWrapper_SoMFVec3f::setValue(SoMFVec3f* theWrappedObject, const SbVec3f&  newValue)
{
  ( theWrappedObject->setValue(newValue));
}

void PythonQtWrapper_SoMFVec3f::setValue(SoMFVec3f* theWrappedObject, float  x, float  y, float  z)
{
  ( theWrappedObject->setValue(x, y, z));
}

void PythonQtWrapper_SoMFVec3f::setValues(SoMFVec3f* theWrappedObject, int  start, int  num, const SbVec3f*  newValues)
{
  ( theWrappedObject->setValues(start, num, newValues));
}



SoMFVec4d* PythonQtWrapper_SoMFVec4d::new_SoMFVec4d()
{ 
return new SoMFVec4d(); }

void*  PythonQtWrapper_SoMFVec4d::static_SoMFVec4d_createInstance()
{
  return (SoMFVec4d::createInstance());
}

int  PythonQtWrapper_SoMFVec4d::find(SoMFVec4d* theWrappedObject, const SbVec4d&  targetValue, bool  addIfNotFound)
{
  return ( theWrappedObject->find(targetValue, addIfNotFound));
}

void PythonQtWrapper_SoMFVec4d::finishEditing(SoMFVec4d* theWrappedObject)
{
  ( theWrappedObject->finishEditing());
}

SoType  PythonQtWrapper_SoMFVec4d::static_SoMFVec4d_getClassTypeId()
{
  return (SoMFVec4d::getClassTypeId());
}

bool  PythonQtWrapper_SoMFVec4d::__ne__(SoMFVec4d* theWrappedObject, const SoMFVec4d&  f) const
{
  return ( (*theWrappedObject)!= f);
}

const SbVec4d*  PythonQtWrapper_SoMFVec4d::operator_assign(SoMFVec4d* theWrappedObject, const SbVec4d&  newValue)
{
  return &( (*theWrappedObject)= newValue);
}

const SoMFVec4d*  PythonQtWrapper_SoMFVec4d::operator_assign(SoMFVec4d* theWrappedObject, const SoMFVec4d&  f)
{
  return &( (*theWrappedObject)= f);
}

bool  PythonQtWrapper_SoMFVec4d::__eq__(SoMFVec4d* theWrappedObject, const SoMFVec4d&  f) const
{
  return ( (*theWrappedObject)== f);
}

const SbVec4d*  PythonQtWrapper_SoMFVec4d::operator_subscript(SoMFVec4d* theWrappedObject, int  i) const
{
  return &( (*theWrappedObject)[i]);
}

void PythonQtWrapper_SoMFVec4d::set1Value(SoMFVec4d* theWrappedObject, int  index, const SbVec4d&  newValue)
{
  ( theWrappedObject->set1Value(index, newValue));
}

void PythonQtWrapper_SoMFVec4d::set1Value(SoMFVec4d* theWrappedObject, int  index, double  x, double  y, double  z, double  w)
{
  ( theWrappedObject->set1Value(index, x, y, z, w));
}

void PythonQtWrapper_SoMFVec4d::setValue(SoMFVec4d* theWrappedObject, const SbVec4d&  newValue)
{
  ( theWrappedObject->setValue(newValue));
}

void PythonQtWrapper_SoMFVec4d::setValue(SoMFVec4d* theWrappedObject, double  x, double  y, double  z, double  w)
{
  ( theWrappedObject->setValue(x, y, z, w));
}

void PythonQtWrapper_SoMFVec4d::setValues(SoMFVec4d* theWrappedObject, int  start, int  num, const SbVec4d*  newValues)
{
  ( theWrappedObject->setValues(start, num, newValues));
}



SoMFVec4f* PythonQtWrapper_SoMFVec4f::new_SoMFVec4f()
{ 
return new SoMFVec4f(); }

void*  PythonQtWrapper_SoMFVec4f::static_SoMFVec4f_createInstance()
{
  return (SoMFVec4f::createInstance());
}

int  PythonQtWrapper_SoMFVec4f::find(SoMFVec4f* theWrappedObject, const SbVec4f&  targetValue, bool  addIfNotFound)
{
  return ( theWrappedObject->find(targetValue, addIfNotFound));
}

void PythonQtWrapper_SoMFVec4f::finishEditing(SoMFVec4f* theWrappedObject)
{
  ( theWrappedObject->finishEditing());
}

SoType  PythonQtWrapper_SoMFVec4f::static_SoMFVec4f_getClassTypeId()
{
  return (SoMFVec4f::getClassTypeId());
}

bool  PythonQtWrapper_SoMFVec4f::__ne__(SoMFVec4f* theWrappedObject, const SoMFVec4f&  f) const
{
  return ( (*theWrappedObject)!= f);
}

const SbVec4f*  PythonQtWrapper_SoMFVec4f::operator_assign(SoMFVec4f* theWrappedObject, const SbVec4f&  newValue)
{
  return &( (*theWrappedObject)= newValue);
}

const SoMFVec4f*  PythonQtWrapper_SoMFVec4f::operator_assign(SoMFVec4f* theWrappedObject, const SoMFVec4f&  f)
{
  return &( (*theWrappedObject)= f);
}

bool  PythonQtWrapper_SoMFVec4f::__eq__(SoMFVec4f* theWrappedObject, const SoMFVec4f&  f) const
{
  return ( (*theWrappedObject)== f);
}

const SbVec4f*  PythonQtWrapper_SoMFVec4f::operator_subscript(SoMFVec4f* theWrappedObject, int  i) const
{
  return &( (*theWrappedObject)[i]);
}

void PythonQtWrapper_SoMFVec4f::set1Value(SoMFVec4f* theWrappedObject, int  index, const SbVec4f&  newValue)
{
  ( theWrappedObject->set1Value(index, newValue));
}

void PythonQtWrapper_SoMFVec4f::set1Value(SoMFVec4f* theWrappedObject, int  index, float  x, float  y, float  z, float  w)
{
  ( theWrappedObject->set1Value(index, x, y, z, w));
}

void PythonQtWrapper_SoMFVec4f::setValue(SoMFVec4f* theWrappedObject, const SbVec4f&  newValue)
{
  ( theWrappedObject->setValue(newValue));
}

void PythonQtWrapper_SoMFVec4f::setValue(SoMFVec4f* theWrappedObject, float  x, float  y, float  z, float  w)
{
  ( theWrappedObject->setValue(x, y, z, w));
}

void PythonQtWrapper_SoMFVec4f::setValues(SoMFVec4f* theWrappedObject, int  start, int  num, const SbVec4f*  newValues)
{
  ( theWrappedObject->setValues(start, num, newValues));
}


