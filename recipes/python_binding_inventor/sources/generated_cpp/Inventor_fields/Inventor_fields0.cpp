#include "inventor_fields0.h"
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
#include <Inventor/fields/SoSFBitMask.h>
#include <Inventor/fields/SoSFBool.h>
#include <Inventor/fields/SoSFColor.h>
#include <Inventor/fields/SoSFDouble.h>
#include <Inventor/fields/SoSFEngine.h>
#include <Inventor/fields/SoSFEnum.h>
#include <Inventor/fields/SoSFFloat.h>
#include <Inventor/fields/SoSFImage.h>
#include <Inventor/fields/SoSFInt32.h>
#include <Inventor/fields/SoSFMatrix.h>
#include <Inventor/fields/SoSFMatrixd.h>
#include <Inventor/fields/SoSFName.h>
#include <Inventor/fields/SoSFNode.h>
#include <Inventor/fields/SoSFPath.h>
#include <Inventor/fields/SoSFPlane.h>
#include <Inventor/fields/SoSFPlaned.h>
#include <Inventor/fields/SoSFRotation.h>
#include <Inventor/fields/SoSFRotationd.h>
#include <Inventor/fields/SoSFShort.h>
#include <Inventor/fields/SoSFString.h>
#include <Inventor/fields/SoSFTime.h>
#include <Inventor/fields/SoSFTrigger.h>
#include <Inventor/fields/SoSFUInt32.h>
#include <Inventor/fields/SoSFUShort.h>
#include <Inventor/fields/SoSFVec2d.h>
#include <Inventor/fields/SoSFVec2f.h>
#include <Inventor/fields/SoSFVec2s.h>
#include <Inventor/fields/SoSFVec3d.h>
#include <Inventor/fields/SoSFVec3f.h>
#include <Inventor/fields/SoSFVec3s.h>
#include <Inventor/fields/SoSFVec4d.h>
#include <Inventor/fields/SoSFVec4f.h>
#include <Inventor/misc/SoBase.h>
#include <Inventor/nodes/SoNode.h>
#include <Inventor/sensors/SoSensor.h>
#include <PythonQtConversion.h>
#include <PythonQtMethodInfo.h>
#include <PythonQtSignalReceiver.h>
#include <QVariant>

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



void*  PythonQtWrapper_SoMField::static_SoMField_createInstance()
{
  return (SoMField::createInstance());
}

void PythonQtWrapper_SoMField::deleteValues(SoMField* theWrappedObject, int  start, int  num)
{
  ( theWrappedObject->deleteValues(start, num));
}

SoType  PythonQtWrapper_SoMField::static_SoMField_getClassTypeId()
{
  return (SoMField::getClassTypeId());
}

int  PythonQtWrapper_SoMField::getNum(SoMField* theWrappedObject) const
{
  return ( theWrappedObject->getNum());
}

void PythonQtWrapper_SoMField::insertSpace(SoMField* theWrappedObject, int  start, int  num)
{
  ( theWrappedObject->insertSpace(start, num));
}

bool  PythonQtWrapper_SoMField::set1(SoMField* theWrappedObject, int  index, const char*  valueString)
{
  return ( theWrappedObject->set1(index, valueString));
}

void PythonQtWrapper_SoMField::setNum(SoMField* theWrappedObject, int  num)
{
  ( theWrappedObject->setNum(num));
}



SoSFBitMask* PythonQtWrapper_SoSFBitMask::new_SoSFBitMask()
{ 
return new SoSFBitMask(); }

void*  PythonQtWrapper_SoSFBitMask::static_SoSFBitMask_createInstance()
{
  return (SoSFBitMask::createInstance());
}

SoType  PythonQtWrapper_SoSFBitMask::static_SoSFBitMask_getClassTypeId()
{
  return (SoSFBitMask::getClassTypeId());
}

const SoSFBitMask*  PythonQtWrapper_SoSFBitMask::operator_assign(SoSFBitMask* theWrappedObject, const SoSFBitMask&  f)
{
  return &( (*theWrappedObject)= f);
}

int  PythonQtWrapper_SoSFBitMask::operator_assign(SoSFBitMask* theWrappedObject, int  newValue)
{
  return ( (*theWrappedObject)= newValue);
}



SoSFBool* PythonQtWrapper_SoSFBool::new_SoSFBool()
{ 
return new SoSFBool(); }

void*  PythonQtWrapper_SoSFBool::static_SoSFBool_createInstance()
{
  return (SoSFBool::createInstance());
}

SoType  PythonQtWrapper_SoSFBool::static_SoSFBool_getClassTypeId()
{
  return (SoSFBool::getClassTypeId());
}

bool  PythonQtWrapper_SoSFBool::getValue(SoSFBool* theWrappedObject) const
{
  return ( theWrappedObject->getValue());
}

bool  PythonQtWrapper_SoSFBool::__ne__(SoSFBool* theWrappedObject, const SoSFBool&  f) const
{
  return ( (*theWrappedObject)!= f);
}

bool  PythonQtWrapper_SoSFBool::operator_assign(SoSFBool* theWrappedObject, bool  newValue)
{
  return ( (*theWrappedObject)= newValue);
}

const SoSFBool*  PythonQtWrapper_SoSFBool::operator_assign(SoSFBool* theWrappedObject, const SoSFBool&  f)
{
  return &( (*theWrappedObject)= f);
}

bool  PythonQtWrapper_SoSFBool::__eq__(SoSFBool* theWrappedObject, const SoSFBool&  f) const
{
  return ( (*theWrappedObject)== f);
}

void PythonQtWrapper_SoSFBool::setValue(SoSFBool* theWrappedObject, bool  newValue)
{
  ( theWrappedObject->setValue(newValue));
}



SoSFColor* PythonQtWrapper_SoSFColor::new_SoSFColor()
{ 
return new SoSFColor(); }

void*  PythonQtWrapper_SoSFColor::static_SoSFColor_createInstance()
{
  return (SoSFColor::createInstance());
}

SoType  PythonQtWrapper_SoSFColor::static_SoSFColor_getClassTypeId()
{
  return (SoSFColor::getClassTypeId());
}

const SbColor*  PythonQtWrapper_SoSFColor::getValue(SoSFColor* theWrappedObject) const
{
  return &( theWrappedObject->getValue());
}

bool  PythonQtWrapper_SoSFColor::__ne__(SoSFColor* theWrappedObject, const SoSFColor&  f) const
{
  return ( (*theWrappedObject)!= f);
}

const SbColor*  PythonQtWrapper_SoSFColor::operator_assign(SoSFColor* theWrappedObject, const SbColor&  newValue)
{
  return &( (*theWrappedObject)= newValue);
}

const SoSFColor*  PythonQtWrapper_SoSFColor::operator_assign(SoSFColor* theWrappedObject, const SoSFColor&  f)
{
  return &( (*theWrappedObject)= f);
}

bool  PythonQtWrapper_SoSFColor::__eq__(SoSFColor* theWrappedObject, const SoSFColor&  f) const
{
  return ( (*theWrappedObject)== f);
}

void PythonQtWrapper_SoSFColor::setHSVValue(SoSFColor* theWrappedObject, float  h, float  s, float  v)
{
  ( theWrappedObject->setHSVValue(h, s, v));
}

void PythonQtWrapper_SoSFColor::setValue(SoSFColor* theWrappedObject, const SbColor&  newValue)
{
  ( theWrappedObject->setValue(newValue));
}

void PythonQtWrapper_SoSFColor::setValue(SoSFColor* theWrappedObject, const SbVec3f&  vec)
{
  ( theWrappedObject->setValue(vec));
}

void PythonQtWrapper_SoSFColor::setValue(SoSFColor* theWrappedObject, float  r, float  g, float  b)
{
  ( theWrappedObject->setValue(r, g, b));
}



SoSFDouble* PythonQtWrapper_SoSFDouble::new_SoSFDouble()
{ 
return new SoSFDouble(); }

void*  PythonQtWrapper_SoSFDouble::static_SoSFDouble_createInstance()
{
  return (SoSFDouble::createInstance());
}

SoType  PythonQtWrapper_SoSFDouble::static_SoSFDouble_getClassTypeId()
{
  return (SoSFDouble::getClassTypeId());
}

double  PythonQtWrapper_SoSFDouble::getValue(SoSFDouble* theWrappedObject) const
{
  return ( theWrappedObject->getValue());
}

bool  PythonQtWrapper_SoSFDouble::__ne__(SoSFDouble* theWrappedObject, const SoSFDouble&  f) const
{
  return ( (*theWrappedObject)!= f);
}

const SoSFDouble*  PythonQtWrapper_SoSFDouble::operator_assign(SoSFDouble* theWrappedObject, const SoSFDouble&  f)
{
  return &( (*theWrappedObject)= f);
}

double  PythonQtWrapper_SoSFDouble::operator_assign(SoSFDouble* theWrappedObject, double  newValue)
{
  return ( (*theWrappedObject)= newValue);
}

bool  PythonQtWrapper_SoSFDouble::__eq__(SoSFDouble* theWrappedObject, const SoSFDouble&  f) const
{
  return ( (*theWrappedObject)== f);
}

void PythonQtWrapper_SoSFDouble::setValue(SoSFDouble* theWrappedObject, double  newValue)
{
  ( theWrappedObject->setValue(newValue));
}



SoSFEngine* PythonQtWrapper_SoSFEngine::new_SoSFEngine()
{ 
return new SoSFEngine(); }

void*  PythonQtWrapper_SoSFEngine::static_SoSFEngine_createInstance()
{
  return (SoSFEngine::createInstance());
}

SoType  PythonQtWrapper_SoSFEngine::static_SoSFEngine_getClassTypeId()
{
  return (SoSFEngine::getClassTypeId());
}

SoEngine*  PythonQtWrapper_SoSFEngine::getValue(SoSFEngine* theWrappedObject) const
{
  return ( theWrappedObject->getValue());
}

bool  PythonQtWrapper_SoSFEngine::__ne__(SoSFEngine* theWrappedObject, const SoSFEngine&  f) const
{
  return ( (*theWrappedObject)!= f);
}

SoEngine*  PythonQtWrapper_SoSFEngine::operator_assign(SoSFEngine* theWrappedObject, SoEngine*  newValue)
{
  return ( (*theWrappedObject)= newValue);
}

const SoSFEngine*  PythonQtWrapper_SoSFEngine::operator_assign(SoSFEngine* theWrappedObject, const SoSFEngine&  f)
{
  return &( (*theWrappedObject)= f);
}

bool  PythonQtWrapper_SoSFEngine::__eq__(SoSFEngine* theWrappedObject, const SoSFEngine&  f) const
{
  return ( (*theWrappedObject)== f);
}

void PythonQtWrapper_SoSFEngine::setValue(SoSFEngine* theWrappedObject, SoEngine*  newValue)
{
  ( theWrappedObject->setValue(newValue));
}



SoSFEnum* PythonQtWrapper_SoSFEnum::new_SoSFEnum()
{ 
return new SoSFEnum(); }

void*  PythonQtWrapper_SoSFEnum::static_SoSFEnum_createInstance()
{
  return (SoSFEnum::createInstance());
}

SoType  PythonQtWrapper_SoSFEnum::static_SoSFEnum_getClassTypeId()
{
  return (SoSFEnum::getClassTypeId());
}

int  PythonQtWrapper_SoSFEnum::getValue(SoSFEnum* theWrappedObject) const
{
  return ( theWrappedObject->getValue());
}

bool  PythonQtWrapper_SoSFEnum::__ne__(SoSFEnum* theWrappedObject, const SoSFEnum&  f) const
{
  return ( (*theWrappedObject)!= f);
}

const SoSFEnum*  PythonQtWrapper_SoSFEnum::operator_assign(SoSFEnum* theWrappedObject, const SoSFEnum&  f)
{
  return &( (*theWrappedObject)= f);
}

int  PythonQtWrapper_SoSFEnum::operator_assign(SoSFEnum* theWrappedObject, int  newValue)
{
  return ( (*theWrappedObject)= newValue);
}

bool  PythonQtWrapper_SoSFEnum::__eq__(SoSFEnum* theWrappedObject, const SoSFEnum&  f) const
{
  return ( (*theWrappedObject)== f);
}

void PythonQtWrapper_SoSFEnum::setEnums(SoSFEnum* theWrappedObject, int  num, int*  vals, SbName*  names)
{
  ( theWrappedObject->setEnums(num, vals, names));
}

void PythonQtWrapper_SoSFEnum::setValue(SoSFEnum* theWrappedObject, const SbName&  name)
{
  ( theWrappedObject->setValue(name));
}

void PythonQtWrapper_SoSFEnum::setValue(SoSFEnum* theWrappedObject, int  newValue)
{
  ( theWrappedObject->setValue(newValue));
}



SoSFFloat* PythonQtWrapper_SoSFFloat::new_SoSFFloat()
{ 
return new SoSFFloat(); }

void*  PythonQtWrapper_SoSFFloat::static_SoSFFloat_createInstance()
{
  return (SoSFFloat::createInstance());
}

SoType  PythonQtWrapper_SoSFFloat::static_SoSFFloat_getClassTypeId()
{
  return (SoSFFloat::getClassTypeId());
}

float  PythonQtWrapper_SoSFFloat::getValue(SoSFFloat* theWrappedObject) const
{
  return ( theWrappedObject->getValue());
}

bool  PythonQtWrapper_SoSFFloat::__ne__(SoSFFloat* theWrappedObject, const SoSFFloat&  f) const
{
  return ( (*theWrappedObject)!= f);
}

const SoSFFloat*  PythonQtWrapper_SoSFFloat::operator_assign(SoSFFloat* theWrappedObject, const SoSFFloat&  f)
{
  return &( (*theWrappedObject)= f);
}

float  PythonQtWrapper_SoSFFloat::operator_assign(SoSFFloat* theWrappedObject, float  newValue)
{
  return ( (*theWrappedObject)= newValue);
}

bool  PythonQtWrapper_SoSFFloat::__eq__(SoSFFloat* theWrappedObject, const SoSFFloat&  f) const
{
  return ( (*theWrappedObject)== f);
}

void PythonQtWrapper_SoSFFloat::setValue(SoSFFloat* theWrappedObject, float  newValue)
{
  ( theWrappedObject->setValue(newValue));
}



SoSFImage* PythonQtWrapper_SoSFImage::new_SoSFImage()
{ 
return new SoSFImage(); }

void*  PythonQtWrapper_SoSFImage::static_SoSFImage_createInstance()
{
  return (SoSFImage::createInstance());
}

void PythonQtWrapper_SoSFImage::finishEditing(SoSFImage* theWrappedObject)
{
  ( theWrappedObject->finishEditing());
}

SoType  PythonQtWrapper_SoSFImage::static_SoSFImage_getClassTypeId()
{
  return (SoSFImage::getClassTypeId());
}

bool  PythonQtWrapper_SoSFImage::__ne__(SoSFImage* theWrappedObject, const SoSFImage&  f) const
{
  return ( (*theWrappedObject)!= f);
}

const SoSFImage*  PythonQtWrapper_SoSFImage::operator_assign(SoSFImage* theWrappedObject, const SoSFImage&  f)
{
  return &( (*theWrappedObject)= f);
}

bool  PythonQtWrapper_SoSFImage::__eq__(SoSFImage* theWrappedObject, const SoSFImage&  f) const
{
  return ( (*theWrappedObject)== f);
}

void PythonQtWrapper_SoSFImage::setValue(SoSFImage* theWrappedObject, const SbVec2s&  size, int  nc, const unsigned char*  bytes)
{
  ( theWrappedObject->setValue(size, nc, bytes));
}



SoSFInt32* PythonQtWrapper_SoSFInt32::new_SoSFInt32()
{ 
return new SoSFInt32(); }

void*  PythonQtWrapper_SoSFInt32::static_SoSFInt32_createInstance()
{
  return (SoSFInt32::createInstance());
}

SoType  PythonQtWrapper_SoSFInt32::static_SoSFInt32_getClassTypeId()
{
  return (SoSFInt32::getClassTypeId());
}

int  PythonQtWrapper_SoSFInt32::getValue(SoSFInt32* theWrappedObject) const
{
  return ( theWrappedObject->getValue());
}

bool  PythonQtWrapper_SoSFInt32::__ne__(SoSFInt32* theWrappedObject, const SoSFInt32&  f) const
{
  return ( (*theWrappedObject)!= f);
}

const SoSFInt32*  PythonQtWrapper_SoSFInt32::operator_assign(SoSFInt32* theWrappedObject, const SoSFInt32&  f)
{
  return &( (*theWrappedObject)= f);
}

int  PythonQtWrapper_SoSFInt32::operator_assign(SoSFInt32* theWrappedObject, int  newValue)
{
  return ( (*theWrappedObject)= newValue);
}

bool  PythonQtWrapper_SoSFInt32::__eq__(SoSFInt32* theWrappedObject, const SoSFInt32&  f) const
{
  return ( (*theWrappedObject)== f);
}

void PythonQtWrapper_SoSFInt32::setValue(SoSFInt32* theWrappedObject, int  newValue)
{
  ( theWrappedObject->setValue(newValue));
}



SoSFMatrix* PythonQtWrapper_SoSFMatrix::new_SoSFMatrix()
{ 
return new SoSFMatrix(); }

void*  PythonQtWrapper_SoSFMatrix::static_SoSFMatrix_createInstance()
{
  return (SoSFMatrix::createInstance());
}

SoType  PythonQtWrapper_SoSFMatrix::static_SoSFMatrix_getClassTypeId()
{
  return (SoSFMatrix::getClassTypeId());
}

const SbMatrix*  PythonQtWrapper_SoSFMatrix::getValue(SoSFMatrix* theWrappedObject) const
{
  return &( theWrappedObject->getValue());
}

bool  PythonQtWrapper_SoSFMatrix::__ne__(SoSFMatrix* theWrappedObject, const SoSFMatrix&  f) const
{
  return ( (*theWrappedObject)!= f);
}

const SbMatrix*  PythonQtWrapper_SoSFMatrix::operator_assign(SoSFMatrix* theWrappedObject, const SbMatrix&  newValue)
{
  return &( (*theWrappedObject)= newValue);
}

const SoSFMatrix*  PythonQtWrapper_SoSFMatrix::operator_assign(SoSFMatrix* theWrappedObject, const SoSFMatrix&  f)
{
  return &( (*theWrappedObject)= f);
}

bool  PythonQtWrapper_SoSFMatrix::__eq__(SoSFMatrix* theWrappedObject, const SoSFMatrix&  f) const
{
  return ( (*theWrappedObject)== f);
}

void PythonQtWrapper_SoSFMatrix::setValue(SoSFMatrix* theWrappedObject, const SbMatrix&  newValue)
{
  ( theWrappedObject->setValue(newValue));
}

void PythonQtWrapper_SoSFMatrix::setValue(SoSFMatrix* theWrappedObject, float  a11, float  a12, float  a13, float  a14, float  a21, float  a22, float  a23, float  a24, float  a31, float  a32, float  a33, float  a34, float  a41, float  a42, float  a43, float  a44)
{
  ( theWrappedObject->setValue(a11, a12, a13, a14, a21, a22, a23, a24, a31, a32, a33, a34, a41, a42, a43, a44));
}



SoSFMatrixd* PythonQtWrapper_SoSFMatrixd::new_SoSFMatrixd()
{ 
return new SoSFMatrixd(); }

void*  PythonQtWrapper_SoSFMatrixd::static_SoSFMatrixd_createInstance()
{
  return (SoSFMatrixd::createInstance());
}

SoType  PythonQtWrapper_SoSFMatrixd::static_SoSFMatrixd_getClassTypeId()
{
  return (SoSFMatrixd::getClassTypeId());
}

const SbMatrixd*  PythonQtWrapper_SoSFMatrixd::getValue(SoSFMatrixd* theWrappedObject) const
{
  return &( theWrappedObject->getValue());
}

bool  PythonQtWrapper_SoSFMatrixd::__ne__(SoSFMatrixd* theWrappedObject, const SoSFMatrixd&  f) const
{
  return ( (*theWrappedObject)!= f);
}

const SbMatrixd*  PythonQtWrapper_SoSFMatrixd::operator_assign(SoSFMatrixd* theWrappedObject, const SbMatrixd&  newValue)
{
  return &( (*theWrappedObject)= newValue);
}

const SoSFMatrixd*  PythonQtWrapper_SoSFMatrixd::operator_assign(SoSFMatrixd* theWrappedObject, const SoSFMatrixd&  f)
{
  return &( (*theWrappedObject)= f);
}

bool  PythonQtWrapper_SoSFMatrixd::__eq__(SoSFMatrixd* theWrappedObject, const SoSFMatrixd&  f) const
{
  return ( (*theWrappedObject)== f);
}

void PythonQtWrapper_SoSFMatrixd::setValue(SoSFMatrixd* theWrappedObject, const SbMatrixd&  newValue)
{
  ( theWrappedObject->setValue(newValue));
}

void PythonQtWrapper_SoSFMatrixd::setValue(SoSFMatrixd* theWrappedObject, double  a11, double  a12, double  a13, double  a14, double  a21, double  a22, double  a23, double  a24, double  a31, double  a32, double  a33, double  a34, double  a41, double  a42, double  a43, double  a44)
{
  ( theWrappedObject->setValue(a11, a12, a13, a14, a21, a22, a23, a24, a31, a32, a33, a34, a41, a42, a43, a44));
}



SoSFName* PythonQtWrapper_SoSFName::new_SoSFName()
{ 
return new SoSFName(); }

void*  PythonQtWrapper_SoSFName::static_SoSFName_createInstance()
{
  return (SoSFName::createInstance());
}

SoType  PythonQtWrapper_SoSFName::static_SoSFName_getClassTypeId()
{
  return (SoSFName::getClassTypeId());
}

const SbName*  PythonQtWrapper_SoSFName::getValue(SoSFName* theWrappedObject) const
{
  return &( theWrappedObject->getValue());
}

bool  PythonQtWrapper_SoSFName::__ne__(SoSFName* theWrappedObject, const SoSFName&  f) const
{
  return ( (*theWrappedObject)!= f);
}

const SbName*  PythonQtWrapper_SoSFName::operator_assign(SoSFName* theWrappedObject, const SbName&  newValue)
{
  return &( (*theWrappedObject)= newValue);
}

const SoSFName*  PythonQtWrapper_SoSFName::operator_assign(SoSFName* theWrappedObject, const SoSFName&  f)
{
  return &( (*theWrappedObject)= f);
}

bool  PythonQtWrapper_SoSFName::__eq__(SoSFName* theWrappedObject, const SoSFName&  f) const
{
  return ( (*theWrappedObject)== f);
}

void PythonQtWrapper_SoSFName::setValue(SoSFName* theWrappedObject, const SbName&  newValue)
{
  ( theWrappedObject->setValue(newValue));
}

void PythonQtWrapper_SoSFName::setValue(SoSFName* theWrappedObject, const char*  string)
{
  ( theWrappedObject->setValue(string));
}



SoSFNode* PythonQtWrapper_SoSFNode::new_SoSFNode()
{ 
return new SoSFNode(); }

void*  PythonQtWrapper_SoSFNode::static_SoSFNode_createInstance()
{
  return (SoSFNode::createInstance());
}

SoType  PythonQtWrapper_SoSFNode::static_SoSFNode_getClassTypeId()
{
  return (SoSFNode::getClassTypeId());
}

SoNode*  PythonQtWrapper_SoSFNode::getValue(SoSFNode* theWrappedObject) const
{
  return ( theWrappedObject->getValue());
}

bool  PythonQtWrapper_SoSFNode::__ne__(SoSFNode* theWrappedObject, const SoSFNode&  f) const
{
  return ( (*theWrappedObject)!= f);
}

SoNode*  PythonQtWrapper_SoSFNode::operator_assign(SoSFNode* theWrappedObject, SoNode*  newValue)
{
  return ( (*theWrappedObject)= newValue);
}

const SoSFNode*  PythonQtWrapper_SoSFNode::operator_assign(SoSFNode* theWrappedObject, const SoSFNode&  f)
{
  return &( (*theWrappedObject)= f);
}

bool  PythonQtWrapper_SoSFNode::__eq__(SoSFNode* theWrappedObject, const SoSFNode&  f) const
{
  return ( (*theWrappedObject)== f);
}

void PythonQtWrapper_SoSFNode::setValue(SoSFNode* theWrappedObject, SoNode*  newValue)
{
  ( theWrappedObject->setValue(newValue));
}



SoSFPath* PythonQtWrapper_SoSFPath::new_SoSFPath()
{ 
return new SoSFPath(); }

void*  PythonQtWrapper_SoSFPath::static_SoSFPath_createInstance()
{
  return (SoSFPath::createInstance());
}

SoType  PythonQtWrapper_SoSFPath::static_SoSFPath_getClassTypeId()
{
  return (SoSFPath::getClassTypeId());
}

SoPath*  PythonQtWrapper_SoSFPath::getValue(SoSFPath* theWrappedObject) const
{
  return ( theWrappedObject->getValue());
}

bool  PythonQtWrapper_SoSFPath::__ne__(SoSFPath* theWrappedObject, const SoSFPath&  f) const
{
  return ( (*theWrappedObject)!= f);
}

SoPath*  PythonQtWrapper_SoSFPath::operator_assign(SoSFPath* theWrappedObject, SoPath*  newValue)
{
  return ( (*theWrappedObject)= newValue);
}

const SoSFPath*  PythonQtWrapper_SoSFPath::operator_assign(SoSFPath* theWrappedObject, const SoSFPath&  f)
{
  return &( (*theWrappedObject)= f);
}

bool  PythonQtWrapper_SoSFPath::__eq__(SoSFPath* theWrappedObject, const SoSFPath&  f) const
{
  return ( (*theWrappedObject)== f);
}

void PythonQtWrapper_SoSFPath::setValue(SoSFPath* theWrappedObject, SoPath*  newValue)
{
  ( theWrappedObject->setValue(newValue));
}



SoSFPlane* PythonQtWrapper_SoSFPlane::new_SoSFPlane()
{ 
return new SoSFPlane(); }

void*  PythonQtWrapper_SoSFPlane::static_SoSFPlane_createInstance()
{
  return (SoSFPlane::createInstance());
}

SoType  PythonQtWrapper_SoSFPlane::static_SoSFPlane_getClassTypeId()
{
  return (SoSFPlane::getClassTypeId());
}

const SbPlane*  PythonQtWrapper_SoSFPlane::getValue(SoSFPlane* theWrappedObject) const
{
  return &( theWrappedObject->getValue());
}

bool  PythonQtWrapper_SoSFPlane::__ne__(SoSFPlane* theWrappedObject, const SoSFPlane&  f) const
{
  return ( (*theWrappedObject)!= f);
}

const SbPlane*  PythonQtWrapper_SoSFPlane::operator_assign(SoSFPlane* theWrappedObject, const SbPlane&  newValue)
{
  return &( (*theWrappedObject)= newValue);
}

const SoSFPlane*  PythonQtWrapper_SoSFPlane::operator_assign(SoSFPlane* theWrappedObject, const SoSFPlane&  f)
{
  return &( (*theWrappedObject)= f);
}

bool  PythonQtWrapper_SoSFPlane::__eq__(SoSFPlane* theWrappedObject, const SoSFPlane&  f) const
{
  return ( (*theWrappedObject)== f);
}

void PythonQtWrapper_SoSFPlane::setValue(SoSFPlane* theWrappedObject, const SbPlane&  newValue)
{
  ( theWrappedObject->setValue(newValue));
}



SoSFPlaned* PythonQtWrapper_SoSFPlaned::new_SoSFPlaned()
{ 
return new SoSFPlaned(); }

void*  PythonQtWrapper_SoSFPlaned::static_SoSFPlaned_createInstance()
{
  return (SoSFPlaned::createInstance());
}

SoType  PythonQtWrapper_SoSFPlaned::static_SoSFPlaned_getClassTypeId()
{
  return (SoSFPlaned::getClassTypeId());
}

const SbPlaned*  PythonQtWrapper_SoSFPlaned::getValue(SoSFPlaned* theWrappedObject) const
{
  return &( theWrappedObject->getValue());
}

bool  PythonQtWrapper_SoSFPlaned::__ne__(SoSFPlaned* theWrappedObject, const SoSFPlaned&  f) const
{
  return ( (*theWrappedObject)!= f);
}

const SbPlaned*  PythonQtWrapper_SoSFPlaned::operator_assign(SoSFPlaned* theWrappedObject, const SbPlaned&  newValue)
{
  return &( (*theWrappedObject)= newValue);
}

const SoSFPlaned*  PythonQtWrapper_SoSFPlaned::operator_assign(SoSFPlaned* theWrappedObject, const SoSFPlaned&  f)
{
  return &( (*theWrappedObject)= f);
}

bool  PythonQtWrapper_SoSFPlaned::__eq__(SoSFPlaned* theWrappedObject, const SoSFPlaned&  f) const
{
  return ( (*theWrappedObject)== f);
}

void PythonQtWrapper_SoSFPlaned::setValue(SoSFPlaned* theWrappedObject, const SbPlaned&  newValue)
{
  ( theWrappedObject->setValue(newValue));
}



SoSFRotation* PythonQtWrapper_SoSFRotation::new_SoSFRotation()
{ 
return new SoSFRotation(); }

void*  PythonQtWrapper_SoSFRotation::static_SoSFRotation_createInstance()
{
  return (SoSFRotation::createInstance());
}

SoType  PythonQtWrapper_SoSFRotation::static_SoSFRotation_getClassTypeId()
{
  return (SoSFRotation::getClassTypeId());
}

const SbRotation*  PythonQtWrapper_SoSFRotation::getValue(SoSFRotation* theWrappedObject) const
{
  return &( theWrappedObject->getValue());
}

bool  PythonQtWrapper_SoSFRotation::__ne__(SoSFRotation* theWrappedObject, const SoSFRotation&  f) const
{
  return ( (*theWrappedObject)!= f);
}

const SbRotation*  PythonQtWrapper_SoSFRotation::operator_assign(SoSFRotation* theWrappedObject, const SbRotation&  newValue)
{
  return &( (*theWrappedObject)= newValue);
}

const SoSFRotation*  PythonQtWrapper_SoSFRotation::operator_assign(SoSFRotation* theWrappedObject, const SoSFRotation&  f)
{
  return &( (*theWrappedObject)= f);
}

bool  PythonQtWrapper_SoSFRotation::__eq__(SoSFRotation* theWrappedObject, const SoSFRotation&  f) const
{
  return ( (*theWrappedObject)== f);
}

void PythonQtWrapper_SoSFRotation::setValue(SoSFRotation* theWrappedObject, const SbRotation&  newValue)
{
  ( theWrappedObject->setValue(newValue));
}

void PythonQtWrapper_SoSFRotation::setValue(SoSFRotation* theWrappedObject, const SbVec3f&  axis, float  angle)
{
  ( theWrappedObject->setValue(axis, angle));
}

void PythonQtWrapper_SoSFRotation::setValue(SoSFRotation* theWrappedObject, float  q0, float  q1, float  q2, float  q3)
{
  ( theWrappedObject->setValue(q0, q1, q2, q3));
}



SoSFRotationd* PythonQtWrapper_SoSFRotationd::new_SoSFRotationd()
{ 
return new SoSFRotationd(); }

void*  PythonQtWrapper_SoSFRotationd::static_SoSFRotationd_createInstance()
{
  return (SoSFRotationd::createInstance());
}

SoType  PythonQtWrapper_SoSFRotationd::static_SoSFRotationd_getClassTypeId()
{
  return (SoSFRotationd::getClassTypeId());
}

const SbRotationd*  PythonQtWrapper_SoSFRotationd::getValue(SoSFRotationd* theWrappedObject) const
{
  return &( theWrappedObject->getValue());
}

bool  PythonQtWrapper_SoSFRotationd::__ne__(SoSFRotationd* theWrappedObject, const SoSFRotationd&  f) const
{
  return ( (*theWrappedObject)!= f);
}

const SbRotationd*  PythonQtWrapper_SoSFRotationd::operator_assign(SoSFRotationd* theWrappedObject, const SbRotationd&  newValue)
{
  return &( (*theWrappedObject)= newValue);
}

const SoSFRotationd*  PythonQtWrapper_SoSFRotationd::operator_assign(SoSFRotationd* theWrappedObject, const SoSFRotationd&  f)
{
  return &( (*theWrappedObject)= f);
}

bool  PythonQtWrapper_SoSFRotationd::__eq__(SoSFRotationd* theWrappedObject, const SoSFRotationd&  f) const
{
  return ( (*theWrappedObject)== f);
}

void PythonQtWrapper_SoSFRotationd::setValue(SoSFRotationd* theWrappedObject, const SbRotationd&  newValue)
{
  ( theWrappedObject->setValue(newValue));
}

void PythonQtWrapper_SoSFRotationd::setValue(SoSFRotationd* theWrappedObject, const SbVec3d&  axis, double  angle)
{
  ( theWrappedObject->setValue(axis, angle));
}

void PythonQtWrapper_SoSFRotationd::setValue(SoSFRotationd* theWrappedObject, double  q0, double  q1, double  q2, double  q3)
{
  ( theWrappedObject->setValue(q0, q1, q2, q3));
}



SoSFShort* PythonQtWrapper_SoSFShort::new_SoSFShort()
{ 
return new SoSFShort(); }

void*  PythonQtWrapper_SoSFShort::static_SoSFShort_createInstance()
{
  return (SoSFShort::createInstance());
}

SoType  PythonQtWrapper_SoSFShort::static_SoSFShort_getClassTypeId()
{
  return (SoSFShort::getClassTypeId());
}

short  PythonQtWrapper_SoSFShort::getValue(SoSFShort* theWrappedObject) const
{
  return ( theWrappedObject->getValue());
}

bool  PythonQtWrapper_SoSFShort::__ne__(SoSFShort* theWrappedObject, const SoSFShort&  f) const
{
  return ( (*theWrappedObject)!= f);
}

const SoSFShort*  PythonQtWrapper_SoSFShort::operator_assign(SoSFShort* theWrappedObject, const SoSFShort&  f)
{
  return &( (*theWrappedObject)= f);
}

short  PythonQtWrapper_SoSFShort::operator_assign(SoSFShort* theWrappedObject, short  newValue)
{
  return ( (*theWrappedObject)= newValue);
}

bool  PythonQtWrapper_SoSFShort::__eq__(SoSFShort* theWrappedObject, const SoSFShort&  f) const
{
  return ( (*theWrappedObject)== f);
}

void PythonQtWrapper_SoSFShort::setValue(SoSFShort* theWrappedObject, short  newValue)
{
  ( theWrappedObject->setValue(newValue));
}



SoSFString* PythonQtWrapper_SoSFString::new_SoSFString()
{ 
return new SoSFString(); }

void*  PythonQtWrapper_SoSFString::static_SoSFString_createInstance()
{
  return (SoSFString::createInstance());
}

SoType  PythonQtWrapper_SoSFString::static_SoSFString_getClassTypeId()
{
  return (SoSFString::getClassTypeId());
}

const SbString*  PythonQtWrapper_SoSFString::getValue(SoSFString* theWrappedObject) const
{
  return &( theWrappedObject->getValue());
}

bool  PythonQtWrapper_SoSFString::__ne__(SoSFString* theWrappedObject, const SoSFString&  f) const
{
  return ( (*theWrappedObject)!= f);
}

const SbString*  PythonQtWrapper_SoSFString::operator_assign(SoSFString* theWrappedObject, const SbString&  newValue)
{
  return &( (*theWrappedObject)= newValue);
}

const SoSFString*  PythonQtWrapper_SoSFString::operator_assign(SoSFString* theWrappedObject, const SoSFString&  f)
{
  return &( (*theWrappedObject)= f);
}

bool  PythonQtWrapper_SoSFString::__eq__(SoSFString* theWrappedObject, const SoSFString&  f) const
{
  return ( (*theWrappedObject)== f);
}

void PythonQtWrapper_SoSFString::setValue(SoSFString* theWrappedObject, const SbString&  newValue)
{
  ( theWrappedObject->setValue(newValue));
}

void PythonQtWrapper_SoSFString::setValue(SoSFString* theWrappedObject, const char*  string)
{
  ( theWrappedObject->setValue(string));
}



SoSFTime* PythonQtWrapper_SoSFTime::new_SoSFTime()
{ 
return new SoSFTime(); }

void*  PythonQtWrapper_SoSFTime::static_SoSFTime_createInstance()
{
  return (SoSFTime::createInstance());
}

SoType  PythonQtWrapper_SoSFTime::static_SoSFTime_getClassTypeId()
{
  return (SoSFTime::getClassTypeId());
}

const SbTime*  PythonQtWrapper_SoSFTime::getValue(SoSFTime* theWrappedObject) const
{
  return &( theWrappedObject->getValue());
}

bool  PythonQtWrapper_SoSFTime::__ne__(SoSFTime* theWrappedObject, const SoSFTime&  f) const
{
  return ( (*theWrappedObject)!= f);
}

const SbTime*  PythonQtWrapper_SoSFTime::operator_assign(SoSFTime* theWrappedObject, const SbTime&  newValue)
{
  return &( (*theWrappedObject)= newValue);
}

const SoSFTime*  PythonQtWrapper_SoSFTime::operator_assign(SoSFTime* theWrappedObject, const SoSFTime&  f)
{
  return &( (*theWrappedObject)= f);
}

bool  PythonQtWrapper_SoSFTime::__eq__(SoSFTime* theWrappedObject, const SoSFTime&  f) const
{
  return ( (*theWrappedObject)== f);
}

void PythonQtWrapper_SoSFTime::setValue(SoSFTime* theWrappedObject, const SbTime&  newValue)
{
  ( theWrappedObject->setValue(newValue));
}



SoSFTrigger* PythonQtWrapper_SoSFTrigger::new_SoSFTrigger()
{ 
return new SoSFTrigger(); }

void*  PythonQtWrapper_SoSFTrigger::static_SoSFTrigger_createInstance()
{
  return (SoSFTrigger::createInstance());
}

SoType  PythonQtWrapper_SoSFTrigger::static_SoSFTrigger_getClassTypeId()
{
  return (SoSFTrigger::getClassTypeId());
}

void PythonQtWrapper_SoSFTrigger::getValue(SoSFTrigger* theWrappedObject) const
{
  ( theWrappedObject->getValue());
}

bool  PythonQtWrapper_SoSFTrigger::__ne__(SoSFTrigger* theWrappedObject, const SoSFTrigger&  t) const
{
  return ( (*theWrappedObject)!= t);
}

const SoSFTrigger*  PythonQtWrapper_SoSFTrigger::operator_assign(SoSFTrigger* theWrappedObject, const SoSFTrigger&  f)
{
  return &( (*theWrappedObject)= f);
}

bool  PythonQtWrapper_SoSFTrigger::__eq__(SoSFTrigger* theWrappedObject, const SoSFTrigger&  t) const
{
  return ( (*theWrappedObject)== t);
}

void PythonQtWrapper_SoSFTrigger::setValue(SoSFTrigger* theWrappedObject)
{
  ( theWrappedObject->setValue());
}



SoSFUInt32* PythonQtWrapper_SoSFUInt32::new_SoSFUInt32()
{ 
return new SoSFUInt32(); }

void*  PythonQtWrapper_SoSFUInt32::static_SoSFUInt32_createInstance()
{
  return (SoSFUInt32::createInstance());
}

SoType  PythonQtWrapper_SoSFUInt32::static_SoSFUInt32_getClassTypeId()
{
  return (SoSFUInt32::getClassTypeId());
}

unsigned int  PythonQtWrapper_SoSFUInt32::getValue(SoSFUInt32* theWrappedObject) const
{
  return ( theWrappedObject->getValue());
}

bool  PythonQtWrapper_SoSFUInt32::__ne__(SoSFUInt32* theWrappedObject, const SoSFUInt32&  f) const
{
  return ( (*theWrappedObject)!= f);
}

const SoSFUInt32*  PythonQtWrapper_SoSFUInt32::operator_assign(SoSFUInt32* theWrappedObject, const SoSFUInt32&  f)
{
  return &( (*theWrappedObject)= f);
}

unsigned int  PythonQtWrapper_SoSFUInt32::operator_assign(SoSFUInt32* theWrappedObject, unsigned int  newValue)
{
  return ( (*theWrappedObject)= newValue);
}

bool  PythonQtWrapper_SoSFUInt32::__eq__(SoSFUInt32* theWrappedObject, const SoSFUInt32&  f) const
{
  return ( (*theWrappedObject)== f);
}

void PythonQtWrapper_SoSFUInt32::setValue(SoSFUInt32* theWrappedObject, unsigned int  newValue)
{
  ( theWrappedObject->setValue(newValue));
}



SoSFUShort* PythonQtWrapper_SoSFUShort::new_SoSFUShort()
{ 
return new SoSFUShort(); }

void*  PythonQtWrapper_SoSFUShort::static_SoSFUShort_createInstance()
{
  return (SoSFUShort::createInstance());
}

SoType  PythonQtWrapper_SoSFUShort::static_SoSFUShort_getClassTypeId()
{
  return (SoSFUShort::getClassTypeId());
}

unsigned short  PythonQtWrapper_SoSFUShort::getValue(SoSFUShort* theWrappedObject) const
{
  return ( theWrappedObject->getValue());
}

bool  PythonQtWrapper_SoSFUShort::__ne__(SoSFUShort* theWrappedObject, const SoSFUShort&  f) const
{
  return ( (*theWrappedObject)!= f);
}

const SoSFUShort*  PythonQtWrapper_SoSFUShort::operator_assign(SoSFUShort* theWrappedObject, const SoSFUShort&  f)
{
  return &( (*theWrappedObject)= f);
}

unsigned short  PythonQtWrapper_SoSFUShort::operator_assign(SoSFUShort* theWrappedObject, unsigned short  newValue)
{
  return ( (*theWrappedObject)= newValue);
}

bool  PythonQtWrapper_SoSFUShort::__eq__(SoSFUShort* theWrappedObject, const SoSFUShort&  f) const
{
  return ( (*theWrappedObject)== f);
}

void PythonQtWrapper_SoSFUShort::setValue(SoSFUShort* theWrappedObject, unsigned short  newValue)
{
  ( theWrappedObject->setValue(newValue));
}



SoSFVec2d* PythonQtWrapper_SoSFVec2d::new_SoSFVec2d()
{ 
return new SoSFVec2d(); }

void*  PythonQtWrapper_SoSFVec2d::static_SoSFVec2d_createInstance()
{
  return (SoSFVec2d::createInstance());
}

SoType  PythonQtWrapper_SoSFVec2d::static_SoSFVec2d_getClassTypeId()
{
  return (SoSFVec2d::getClassTypeId());
}

const SbVec2d*  PythonQtWrapper_SoSFVec2d::getValue(SoSFVec2d* theWrappedObject) const
{
  return &( theWrappedObject->getValue());
}

bool  PythonQtWrapper_SoSFVec2d::__ne__(SoSFVec2d* theWrappedObject, const SoSFVec2d&  f) const
{
  return ( (*theWrappedObject)!= f);
}

const SbVec2d*  PythonQtWrapper_SoSFVec2d::operator_assign(SoSFVec2d* theWrappedObject, const SbVec2d&  newValue)
{
  return &( (*theWrappedObject)= newValue);
}

const SoSFVec2d*  PythonQtWrapper_SoSFVec2d::operator_assign(SoSFVec2d* theWrappedObject, const SoSFVec2d&  f)
{
  return &( (*theWrappedObject)= f);
}

bool  PythonQtWrapper_SoSFVec2d::__eq__(SoSFVec2d* theWrappedObject, const SoSFVec2d&  f) const
{
  return ( (*theWrappedObject)== f);
}

void PythonQtWrapper_SoSFVec2d::setValue(SoSFVec2d* theWrappedObject, const SbVec2d&  newValue)
{
  ( theWrappedObject->setValue(newValue));
}

void PythonQtWrapper_SoSFVec2d::setValue(SoSFVec2d* theWrappedObject, double  x, double  y)
{
  ( theWrappedObject->setValue(x, y));
}



SoSFVec2f* PythonQtWrapper_SoSFVec2f::new_SoSFVec2f()
{ 
return new SoSFVec2f(); }

void*  PythonQtWrapper_SoSFVec2f::static_SoSFVec2f_createInstance()
{
  return (SoSFVec2f::createInstance());
}

SoType  PythonQtWrapper_SoSFVec2f::static_SoSFVec2f_getClassTypeId()
{
  return (SoSFVec2f::getClassTypeId());
}

const SbVec2f*  PythonQtWrapper_SoSFVec2f::getValue(SoSFVec2f* theWrappedObject) const
{
  return &( theWrappedObject->getValue());
}

bool  PythonQtWrapper_SoSFVec2f::__ne__(SoSFVec2f* theWrappedObject, const SoSFVec2f&  f) const
{
  return ( (*theWrappedObject)!= f);
}

const SbVec2f*  PythonQtWrapper_SoSFVec2f::operator_assign(SoSFVec2f* theWrappedObject, const SbVec2f&  newValue)
{
  return &( (*theWrappedObject)= newValue);
}

const SoSFVec2f*  PythonQtWrapper_SoSFVec2f::operator_assign(SoSFVec2f* theWrappedObject, const SoSFVec2f&  f)
{
  return &( (*theWrappedObject)= f);
}

bool  PythonQtWrapper_SoSFVec2f::__eq__(SoSFVec2f* theWrappedObject, const SoSFVec2f&  f) const
{
  return ( (*theWrappedObject)== f);
}

void PythonQtWrapper_SoSFVec2f::setValue(SoSFVec2f* theWrappedObject, const SbVec2f&  newValue)
{
  ( theWrappedObject->setValue(newValue));
}

void PythonQtWrapper_SoSFVec2f::setValue(SoSFVec2f* theWrappedObject, float  x, float  y)
{
  ( theWrappedObject->setValue(x, y));
}



SoSFVec2s* PythonQtWrapper_SoSFVec2s::new_SoSFVec2s()
{ 
return new SoSFVec2s(); }

void*  PythonQtWrapper_SoSFVec2s::static_SoSFVec2s_createInstance()
{
  return (SoSFVec2s::createInstance());
}

SoType  PythonQtWrapper_SoSFVec2s::static_SoSFVec2s_getClassTypeId()
{
  return (SoSFVec2s::getClassTypeId());
}

const SbVec2s*  PythonQtWrapper_SoSFVec2s::getValue(SoSFVec2s* theWrappedObject) const
{
  return &( theWrappedObject->getValue());
}

bool  PythonQtWrapper_SoSFVec2s::__ne__(SoSFVec2s* theWrappedObject, const SoSFVec2s&  f) const
{
  return ( (*theWrappedObject)!= f);
}

const SbVec2s*  PythonQtWrapper_SoSFVec2s::operator_assign(SoSFVec2s* theWrappedObject, const SbVec2s&  newValue)
{
  return &( (*theWrappedObject)= newValue);
}

const SoSFVec2s*  PythonQtWrapper_SoSFVec2s::operator_assign(SoSFVec2s* theWrappedObject, const SoSFVec2s&  f)
{
  return &( (*theWrappedObject)= f);
}

bool  PythonQtWrapper_SoSFVec2s::__eq__(SoSFVec2s* theWrappedObject, const SoSFVec2s&  f) const
{
  return ( (*theWrappedObject)== f);
}

void PythonQtWrapper_SoSFVec2s::setValue(SoSFVec2s* theWrappedObject, const SbVec2s&  newValue)
{
  ( theWrappedObject->setValue(newValue));
}

void PythonQtWrapper_SoSFVec2s::setValue(SoSFVec2s* theWrappedObject, short  x, short  y)
{
  ( theWrappedObject->setValue(x, y));
}



SoSFVec3d* PythonQtWrapper_SoSFVec3d::new_SoSFVec3d()
{ 
return new SoSFVec3d(); }

void*  PythonQtWrapper_SoSFVec3d::static_SoSFVec3d_createInstance()
{
  return (SoSFVec3d::createInstance());
}

SoType  PythonQtWrapper_SoSFVec3d::static_SoSFVec3d_getClassTypeId()
{
  return (SoSFVec3d::getClassTypeId());
}

const SbVec3d*  PythonQtWrapper_SoSFVec3d::getValue(SoSFVec3d* theWrappedObject) const
{
  return &( theWrappedObject->getValue());
}

bool  PythonQtWrapper_SoSFVec3d::__ne__(SoSFVec3d* theWrappedObject, const SoSFVec3d&  f) const
{
  return ( (*theWrappedObject)!= f);
}

const SbVec3d*  PythonQtWrapper_SoSFVec3d::operator_assign(SoSFVec3d* theWrappedObject, const SbVec3d&  newValue)
{
  return &( (*theWrappedObject)= newValue);
}

const SoSFVec3d*  PythonQtWrapper_SoSFVec3d::operator_assign(SoSFVec3d* theWrappedObject, const SoSFVec3d&  f)
{
  return &( (*theWrappedObject)= f);
}

bool  PythonQtWrapper_SoSFVec3d::__eq__(SoSFVec3d* theWrappedObject, const SoSFVec3d&  f) const
{
  return ( (*theWrappedObject)== f);
}

void PythonQtWrapper_SoSFVec3d::setValue(SoSFVec3d* theWrappedObject, const SbVec3d&  newValue)
{
  ( theWrappedObject->setValue(newValue));
}

void PythonQtWrapper_SoSFVec3d::setValue(SoSFVec3d* theWrappedObject, double  x, double  y, double  z)
{
  ( theWrappedObject->setValue(x, y, z));
}



SoSFVec3f* PythonQtWrapper_SoSFVec3f::new_SoSFVec3f()
{ 
return new SoSFVec3f(); }

void*  PythonQtWrapper_SoSFVec3f::static_SoSFVec3f_createInstance()
{
  return (SoSFVec3f::createInstance());
}

SoType  PythonQtWrapper_SoSFVec3f::static_SoSFVec3f_getClassTypeId()
{
  return (SoSFVec3f::getClassTypeId());
}

const SbVec3f*  PythonQtWrapper_SoSFVec3f::getValue(SoSFVec3f* theWrappedObject) const
{
  return &( theWrappedObject->getValue());
}

bool  PythonQtWrapper_SoSFVec3f::__ne__(SoSFVec3f* theWrappedObject, const SoSFVec3f&  f) const
{
  return ( (*theWrappedObject)!= f);
}

const SbVec3f*  PythonQtWrapper_SoSFVec3f::operator_assign(SoSFVec3f* theWrappedObject, const SbVec3f&  newValue)
{
  return &( (*theWrappedObject)= newValue);
}

const SoSFVec3f*  PythonQtWrapper_SoSFVec3f::operator_assign(SoSFVec3f* theWrappedObject, const SoSFVec3f&  f)
{
  return &( (*theWrappedObject)= f);
}

bool  PythonQtWrapper_SoSFVec3f::__eq__(SoSFVec3f* theWrappedObject, const SoSFVec3f&  f) const
{
  return ( (*theWrappedObject)== f);
}

void PythonQtWrapper_SoSFVec3f::setValue(SoSFVec3f* theWrappedObject, const SbVec3f&  newValue)
{
  ( theWrappedObject->setValue(newValue));
}

void PythonQtWrapper_SoSFVec3f::setValue(SoSFVec3f* theWrappedObject, float  x, float  y, float  z)
{
  ( theWrappedObject->setValue(x, y, z));
}



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


