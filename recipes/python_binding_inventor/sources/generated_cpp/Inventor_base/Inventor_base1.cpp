/*************************************************************************************
**
** Copyright 2022, MeVis Medical Solutions AG
**
** GNU LESSER GENERAL PUBLIC LICENSE Version 2.1, February 1999
**
**************************************************************************************/
#include "Inventor_base1.h"
#include <PythonQtConversion.h>
#include <PythonQtMethodInfo.h>
#include <PythonQtSignalReceiver.h>
#include <QVariant>
#include <Inventor/SbBox.h>
#include <Inventor/SbBoxd.h>
#include <Inventor/SbColor.h>
#include <Inventor/SbLinear.h>
#include <Inventor/SbLineard.h>
#include <Inventor/SbString.h>
#include <Inventor/SbTime.h>
#include <Inventor/SbViewportRegion.h>
#include <Inventor/SoInput.h>
#include <Inventor/SoOutput.h>
#include <Inventor/SoPath.h>
#include <Inventor/SoPickedPoint.h>
#include <Inventor/SoPrimitiveVertex.h>
#include <Inventor/SoSceneManager.h>
#include <Inventor/SoType.h>
#include <Inventor/actions/SoAction.h>
#include <Inventor/actions/SoGLRenderAction.h>
#include <Inventor/actions/SoHandleEventAction.h>
#include <Inventor/actions/SoWriteAction.h>
#include <Inventor/details/SoDetail.h>
#include <Inventor/elements/SoElement.h>
#include <Inventor/events/SoEvent.h>
#include <Inventor/fields/SoField.h>
#include <Inventor/misc/SoBase.h>
#include <Inventor/misc/SoState.h>
#include <Inventor/nodes/SoNode.h>
#include <Inventor/nodes/SoSeparator.h>
#include <Inventor/sensors/SoSensor.h>
#include <stdexcept>

SbXfBox3d* PythonQtWrapper_SbXfBox3d::new_SbXfBox3d()
{ 
return new SbXfBox3d(); }

SbXfBox3d* PythonQtWrapper_SbXfBox3d::new_SbXfBox3d(const SbBox3d&  box)
{ 
return new SbXfBox3d(box); }

SbXfBox3d* PythonQtWrapper_SbXfBox3d::new_SbXfBox3d(const SbVec3d&  _min, const SbVec3d&  _max)
{ 
return new SbXfBox3d(_min, _max); }

void PythonQtWrapper_SbXfBox3d::extendBy(SbXfBox3d* theWrappedObject, const SbBox3d&  bb)
{
  ( theWrappedObject->extendBy(bb));
}

void PythonQtWrapper_SbXfBox3d::extendBy(SbXfBox3d* theWrappedObject, const SbVec3d&  pt)
{
  ( theWrappedObject->extendBy(pt));
}

void PythonQtWrapper_SbXfBox3d::extendBy(SbXfBox3d* theWrappedObject, const SbXfBox3d&  bb)
{
  ( theWrappedObject->extendBy(bb));
}

SbVec3d  PythonQtWrapper_SbXfBox3d::getCenter(SbXfBox3d* theWrappedObject) const
{
  return ( theWrappedObject->getCenter());
}

const SbMatrixd*  PythonQtWrapper_SbXfBox3d::getInverse(SbXfBox3d* theWrappedObject) const
{
  return &( theWrappedObject->getInverse());
}

const SbMatrixd*  PythonQtWrapper_SbXfBox3d::getTransform(SbXfBox3d* theWrappedObject) const
{
  return &( theWrappedObject->getTransform());
}

double  PythonQtWrapper_SbXfBox3d::getVolume(SbXfBox3d* theWrappedObject) const
{
  return ( theWrappedObject->getVolume());
}

bool  PythonQtWrapper_SbXfBox3d::hasVolume(SbXfBox3d* theWrappedObject) const
{
  return ( theWrappedObject->hasVolume());
}

bool  PythonQtWrapper_SbXfBox3d::intersect(SbXfBox3d* theWrappedObject, const SbBox3d&  bb) const
{
  return ( theWrappedObject->intersect(bb));
}

bool  PythonQtWrapper_SbXfBox3d::intersect(SbXfBox3d* theWrappedObject, const SbVec3d&  pt) const
{
  return ( theWrappedObject->intersect(pt));
}

bool  PythonQtWrapper_SbXfBox3d::isEmpty(SbXfBox3d* theWrappedObject) const
{
  return ( theWrappedObject->isEmpty());
}

void PythonQtWrapper_SbXfBox3d::makeEmpty(SbXfBox3d* theWrappedObject)
{
  ( theWrappedObject->makeEmpty());
}

bool  PythonQtWrapper_SbXfBox3d::__ne__(SbXfBox3d* theWrappedObject, const SbXfBox3d&  b2)
{
  return ( (*theWrappedObject)!= b2);
}

bool  PythonQtWrapper_SbXfBox3d::__eq__(SbXfBox3d* theWrappedObject, const SbXfBox3d&  b2)
{
  return ( (*theWrappedObject)== b2);
}

SbBox3d  PythonQtWrapper_SbXfBox3d::project(SbXfBox3d* theWrappedObject) const
{
  return ( theWrappedObject->project());
}

void PythonQtWrapper_SbXfBox3d::setBounds(SbXfBox3d* theWrappedObject, const SbVec3d&  _min, const SbVec3d&  _max)
{
  ( theWrappedObject->setBounds(_min, _max));
}

void PythonQtWrapper_SbXfBox3d::setBounds(SbXfBox3d* theWrappedObject, double  xmin, double  ymin, double  zmin, double  xmax, double  ymax, double  zmax)
{
  ( theWrappedObject->setBounds(xmin, ymin, zmin, xmax, ymax, zmax));
}

void PythonQtWrapper_SbXfBox3d::setTransform(SbXfBox3d* theWrappedObject, const SbMatrixd&  m)
{
  ( theWrappedObject->setTransform(m));
}

void PythonQtWrapper_SbXfBox3d::transform(SbXfBox3d* theWrappedObject, const SbMatrixd&  m)
{
  ( theWrappedObject->transform(m));
}



SbXfBox3f* PythonQtWrapper_SbXfBox3f::new_SbXfBox3f()
{ 
return new SbXfBox3f(); }

SbXfBox3f* PythonQtWrapper_SbXfBox3f::new_SbXfBox3f(const SbBox3f&  box)
{ 
return new SbXfBox3f(box); }

SbXfBox3f* PythonQtWrapper_SbXfBox3f::new_SbXfBox3f(const SbVec3f&  _min, const SbVec3f&  _max)
{ 
return new SbXfBox3f(_min, _max); }

void PythonQtWrapper_SbXfBox3f::extendBy(SbXfBox3f* theWrappedObject, const SbBox3f&  bb)
{
  ( theWrappedObject->extendBy(bb));
}

void PythonQtWrapper_SbXfBox3f::extendBy(SbXfBox3f* theWrappedObject, const SbVec3f&  pt)
{
  ( theWrappedObject->extendBy(pt));
}

void PythonQtWrapper_SbXfBox3f::extendBy(SbXfBox3f* theWrappedObject, const SbXfBox3f&  bb)
{
  ( theWrappedObject->extendBy(bb));
}

SbVec3f  PythonQtWrapper_SbXfBox3f::getCenter(SbXfBox3f* theWrappedObject) const
{
  return ( theWrappedObject->getCenter());
}

const SbMatrix*  PythonQtWrapper_SbXfBox3f::getInverse(SbXfBox3f* theWrappedObject) const
{
  return &( theWrappedObject->getInverse());
}

const SbMatrix*  PythonQtWrapper_SbXfBox3f::getTransform(SbXfBox3f* theWrappedObject) const
{
  return &( theWrappedObject->getTransform());
}

float  PythonQtWrapper_SbXfBox3f::getVolume(SbXfBox3f* theWrappedObject) const
{
  return ( theWrappedObject->getVolume());
}

bool  PythonQtWrapper_SbXfBox3f::hasVolume(SbXfBox3f* theWrappedObject) const
{
  return ( theWrappedObject->hasVolume());
}

bool  PythonQtWrapper_SbXfBox3f::intersect(SbXfBox3f* theWrappedObject, const SbBox3f&  bb) const
{
  return ( theWrappedObject->intersect(bb));
}

bool  PythonQtWrapper_SbXfBox3f::intersect(SbXfBox3f* theWrappedObject, const SbVec3f&  pt) const
{
  return ( theWrappedObject->intersect(pt));
}

bool  PythonQtWrapper_SbXfBox3f::isEmpty(SbXfBox3f* theWrappedObject) const
{
  return ( theWrappedObject->isEmpty());
}

void PythonQtWrapper_SbXfBox3f::makeEmpty(SbXfBox3f* theWrappedObject)
{
  ( theWrappedObject->makeEmpty());
}

bool  PythonQtWrapper_SbXfBox3f::__ne__(SbXfBox3f* theWrappedObject, const SbXfBox3f&  b2)
{
  return ( (*theWrappedObject)!= b2);
}

bool  PythonQtWrapper_SbXfBox3f::__eq__(SbXfBox3f* theWrappedObject, const SbXfBox3f&  b2)
{
  return ( (*theWrappedObject)== b2);
}

SbBox3f  PythonQtWrapper_SbXfBox3f::project(SbXfBox3f* theWrappedObject) const
{
  return ( theWrappedObject->project());
}

void PythonQtWrapper_SbXfBox3f::setBounds(SbXfBox3f* theWrappedObject, const SbVec3f&  _min, const SbVec3f&  _max)
{
  ( theWrappedObject->setBounds(_min, _max));
}

void PythonQtWrapper_SbXfBox3f::setBounds(SbXfBox3f* theWrappedObject, float  xmin, float  ymin, float  zmin, float  xmax, float  ymax, float  zmax)
{
  ( theWrappedObject->setBounds(xmin, ymin, zmin, xmax, ymax, zmax));
}

void PythonQtWrapper_SbXfBox3f::setTransform(SbXfBox3f* theWrappedObject, const SbMatrix&  m)
{
  ( theWrappedObject->setTransform(m));
}

void PythonQtWrapper_SbXfBox3f::transform(SbXfBox3f* theWrappedObject, const SbMatrix&  m)
{
  ( theWrappedObject->transform(m));
}



SoType  PythonQtWrapper_SoBase::static_SoBase_getClassTypeId()
{
  return (SoBase::getClassTypeId());
}

SbName  PythonQtWrapper_SoBase::getName(SoBase* theWrappedObject) const
{
  return ( theWrappedObject->getName());
}

int  PythonQtWrapper_SoBase::getRefCount(SoBase* theWrappedObject) const
{
  return ( theWrappedObject->getRefCount());
}

bool  PythonQtWrapper_SoBase::isOfType(SoBase* theWrappedObject, SoType  type) const
{
  return ( theWrappedObject->isOfType(type));
}

void PythonQtWrapper_SoBase::setName(SoBase* theWrappedObject, const SbName&  name)
{
  ( theWrappedObject->setName(name));
}

void PythonQtWrapper_SoBase::startNotify(SoBase* theWrappedObject)
{
  ( theWrappedObject->startNotify());
}

void PythonQtWrapper_SoBase::touch(SoBase* theWrappedObject)
{
  ( theWrappedObject->touch());
}



PythonQtShell_SoDB::~PythonQtShell_SoDB() {
  PythonQtPrivate* priv = PythonQt::priv();
  if (priv) { priv->shellClassDeleted(this); }
}
SoDB* PythonQtWrapper_SoDB::new_SoDB()
{ 
return new PythonQtShell_SoDB(); }

void PythonQtWrapper_SoDB::static_SoDB_addConverter(SoType  fromField, SoType  toField, SoType  converterEngine)
{
  (SoDB::addConverter(fromField, toField, converterEngine));
}

SoField*  PythonQtWrapper_SoDB::static_SoDB_createGlobalField(const SbName&  name, SoType  type)
{
  return (SoDB::createGlobalField(name, type));
}

void PythonQtWrapper_SoDB::static_SoDB_enableRealTimeSensor(bool  enable)
{
  (SoDB::enableRealTimeSensor(enable));
}

void PythonQtWrapper_SoDB::static_SoDB_endNotify()
{
  (SoDB::endNotify());
}

SoType  PythonQtWrapper_SoDB::static_SoDB_getConverter(SoType  fromField, SoType  toField)
{
  return (SoDB::getConverter(fromField, toField));
}

const SbTime*  PythonQtWrapper_SoDB::static_SoDB_getDelaySensorTimeout()
{
  return &(SoDB::getDelaySensorTimeout());
}

SoField*  PythonQtWrapper_SoDB::static_SoDB_getGlobalField(const SbName&  name)
{
  return (SoDB::getGlobalField(name));
}

SbString  PythonQtWrapper_SoDB::static_SoDB_getHeaderString(int  i)
{
  return (SoDB::getHeaderString(i));
}

int  PythonQtWrapper_SoDB::static_SoDB_getNumHeaders()
{
  return (SoDB::getNumHeaders());
}

const SbTime*  PythonQtWrapper_SoDB::static_SoDB_getRealTimeInterval()
{
  return &(SoDB::getRealTimeInterval());
}

const char*  PythonQtWrapper_SoDB::static_SoDB_getVersion()
{
  return (SoDB::getVersion());
}

void PythonQtWrapper_SoDB::static_SoDB_init()
{
  (SoDB::init());
}

bool  PythonQtWrapper_SoDB::static_SoDB_isInitialized()
{
  return (SoDB::isInitialized());
}

bool  PythonQtWrapper_SoDB::static_SoDB_isNotifying()
{
  return (SoDB::isNotifying());
}

bool  PythonQtWrapper_SoDB::static_SoDB_isValidHeader(const char*  testString)
{
  return (SoDB::isValidHeader(testString));
}

SoSeparator*  PythonQtWrapper_SoDB::static_SoDB_readAll(SoInput*  in)
{
  return (SoDB::readAll(in));
}

void PythonQtWrapper_SoDB::static_SoDB_renameGlobalField(const SbName&  oldName, const SbName&  newName)
{
  (SoDB::renameGlobalField(oldName, newName));
}

void PythonQtWrapper_SoDB::static_SoDB_setDelaySensorTimeout(const SbTime&  t)
{
  (SoDB::setDelaySensorTimeout(t));
}

void PythonQtWrapper_SoDB::static_SoDB_setRealTimeInterval(const SbTime&  deltaT)
{
  (SoDB::setRealTimeInterval(deltaT));
}

void PythonQtWrapper_SoDB::static_SoDB_startNotify()
{
  (SoDB::startNotify());
}



SoInput* PythonQtWrapper_SoInput::new_SoInput()
{ 
return new SoInput(); }

SoInput* PythonQtWrapper_SoInput::new_SoInput(SoInput*  dictIn)
{ 
return new SoInput(dictIn); }

void PythonQtWrapper_SoInput::static_SoInput_addDirectoryFirst(const char*  dirName)
{
  (SoInput::addDirectoryFirst(dirName));
}

void PythonQtWrapper_SoInput::static_SoInput_addDirectoryLast(const char*  dirName)
{
  (SoInput::addDirectoryLast(dirName));
}

void PythonQtWrapper_SoInput::static_SoInput_addEnvDirectoriesFirst(const char*  envVarName)
{
  (SoInput::addEnvDirectoriesFirst(envVarName));
}

void PythonQtWrapper_SoInput::static_SoInput_addEnvDirectoriesLast(const char*  envVarName)
{
  (SoInput::addEnvDirectoriesLast(envVarName));
}

void PythonQtWrapper_SoInput::addReference(SoInput* theWrappedObject, const SbName&  name, SoBase*  base, bool  addToGlobalDict)
{
  ( theWrappedObject->addReference(name, base, addToGlobalDict));
}

void PythonQtWrapper_SoInput::static_SoInput_clearDirectories()
{
  (SoInput::clearDirectories());
}

void PythonQtWrapper_SoInput::closeFile(SoInput* theWrappedObject)
{
  ( theWrappedObject->closeFile());
}

bool  PythonQtWrapper_SoInput::eof(SoInput* theWrappedObject) const
{
  return ( theWrappedObject->eof());
}

SoBase*  PythonQtWrapper_SoInput::findReference(SoInput* theWrappedObject, const SbName&  name) const
{
  return ( theWrappedObject->findReference(name));
}

const char*  PythonQtWrapper_SoInput::getCurFileName(SoInput* theWrappedObject) const
{
  return ( theWrappedObject->getCurFileName());
}

SbString  PythonQtWrapper_SoInput::getHeader(SoInput* theWrappedObject)
{
  return ( theWrappedObject->getHeader());
}

float  PythonQtWrapper_SoInput::getIVVersion(SoInput* theWrappedObject)
{
  return ( theWrappedObject->getIVVersion());
}

void PythonQtWrapper_SoInput::static_SoInput_init()
{
  (SoInput::init());
}

bool  PythonQtWrapper_SoInput::isBinary(SoInput* theWrappedObject)
{
  return ( theWrappedObject->isBinary());
}

bool  PythonQtWrapper_SoInput::isValidFile(SoInput* theWrappedObject)
{
  return ( theWrappedObject->isValidFile());
}

bool  PythonQtWrapper_SoInput::openFile(SoInput* theWrappedObject, const char*  fileName, bool  okIfNotFound)
{
  return ( theWrappedObject->openFile(fileName, okIfNotFound));
}

bool  PythonQtWrapper_SoInput::pushFile(SoInput* theWrappedObject, const char*  fileName)
{
  return ( theWrappedObject->pushFile(fileName));
}

void PythonQtWrapper_SoInput::putBack(SoInput* theWrappedObject, char  c)
{
  ( theWrappedObject->putBack(c));
}

void PythonQtWrapper_SoInput::putBack(SoInput* theWrappedObject, const char*  string)
{
  ( theWrappedObject->putBack(string));
}

bool  PythonQtWrapper_SoInput::readBinaryArray(SoInput* theWrappedObject, double*  d, int  length)
{
  return ( theWrappedObject->readBinaryArray(d, length));
}

bool  PythonQtWrapper_SoInput::readBinaryArray(SoInput* theWrappedObject, float*  f, int  length)
{
  return ( theWrappedObject->readBinaryArray(f, length));
}

bool  PythonQtWrapper_SoInput::readBinaryArray(SoInput* theWrappedObject, int*  l, int  length)
{
  return ( theWrappedObject->readBinaryArray(l, length));
}

bool  PythonQtWrapper_SoInput::readBinaryArray(SoInput* theWrappedObject, unsigned char*  c, int  length)
{
  return ( theWrappedObject->readBinaryArray(c, length));
}

void PythonQtWrapper_SoInput::static_SoInput_removeDirectory(const char*  dirName)
{
  (SoInput::removeDirectory(dirName));
}

void PythonQtWrapper_SoInput::removeReference(SoInput* theWrappedObject, const SbName&  name)
{
  ( theWrappedObject->removeReference(name));
}



SoOutput* PythonQtWrapper_SoOutput::new_SoOutput()
{ 
return new SoOutput(); }

SoOutput* PythonQtWrapper_SoOutput::new_SoOutput(SoOutput*  dictOut)
{ 
return new SoOutput(dictOut); }

void PythonQtWrapper_SoOutput::closeFile(SoOutput* theWrappedObject)
{
  ( theWrappedObject->closeFile());
}

void PythonQtWrapper_SoOutput::decrementIndent(SoOutput* theWrappedObject, int  amount)
{
  ( theWrappedObject->decrementIndent(amount));
}

unsigned int  PythonQtWrapper_SoOutput::getAnnotation(SoOutput* theWrappedObject)
{
  return ( theWrappedObject->getAnnotation());
}

SbString  PythonQtWrapper_SoOutput::static_SoOutput_getDefaultASCIIHeader()
{
  return (SoOutput::getDefaultASCIIHeader());
}

SbString  PythonQtWrapper_SoOutput::static_SoOutput_getDefaultBinaryHeader()
{
  return (SoOutput::getDefaultBinaryHeader());
}

SoOutput::Stage  PythonQtWrapper_SoOutput::getStage(SoOutput* theWrappedObject) const
{
  return ( theWrappedObject->getStage());
}

void PythonQtWrapper_SoOutput::incrementIndent(SoOutput* theWrappedObject, int  amount)
{
  ( theWrappedObject->incrementIndent(amount));
}

void PythonQtWrapper_SoOutput::indent(SoOutput* theWrappedObject)
{
  ( theWrappedObject->indent());
}

bool  PythonQtWrapper_SoOutput::isBinary(SoOutput* theWrappedObject) const
{
  return ( theWrappedObject->isBinary());
}

bool  PythonQtWrapper_SoOutput::isCompact(SoOutput* theWrappedObject) const
{
  return ( theWrappedObject->isCompact());
}

bool  PythonQtWrapper_SoOutput::openFile(SoOutput* theWrappedObject, const char*  fileName)
{
  return ( theWrappedObject->openFile(fileName));
}

void PythonQtWrapper_SoOutput::reset(SoOutput* theWrappedObject)
{
  ( theWrappedObject->reset());
}

void PythonQtWrapper_SoOutput::resetBuffer(SoOutput* theWrappedObject)
{
  ( theWrappedObject->resetBuffer());
}

void PythonQtWrapper_SoOutput::resetHeaderString(SoOutput* theWrappedObject)
{
  ( theWrappedObject->resetHeaderString());
}

void PythonQtWrapper_SoOutput::setAnnotation(SoOutput* theWrappedObject, unsigned int  bits)
{
  ( theWrappedObject->setAnnotation(bits));
}

void PythonQtWrapper_SoOutput::setBinary(SoOutput* theWrappedObject, bool  flag)
{
  ( theWrappedObject->setBinary(flag));
}

void PythonQtWrapper_SoOutput::setCompact(SoOutput* theWrappedObject, bool  flag)
{
  ( theWrappedObject->setCompact(flag));
}

void PythonQtWrapper_SoOutput::setFloatPrecision(SoOutput* theWrappedObject, int  precision)
{
  ( theWrappedObject->setFloatPrecision(precision));
}

void PythonQtWrapper_SoOutput::setHeaderString(SoOutput* theWrappedObject, const SbString&  str)
{
  ( theWrappedObject->setHeaderString(str));
}

void PythonQtWrapper_SoOutput::setStage(SoOutput* theWrappedObject, SoOutput::Stage  stage)
{
  ( theWrappedObject->setStage(stage));
}

void PythonQtWrapper_SoOutput::write(SoOutput* theWrappedObject, char  c)
{
  ( theWrappedObject->write(c));
}

void PythonQtWrapper_SoOutput::write(SoOutput* theWrappedObject, const SbName&  n)
{
  ( theWrappedObject->write(n));
}

void PythonQtWrapper_SoOutput::write(SoOutput* theWrappedObject, const SbString&  s)
{
  ( theWrappedObject->write(s));
}

void PythonQtWrapper_SoOutput::write(SoOutput* theWrappedObject, const char*  s)
{
  ( theWrappedObject->write(s));
}

void PythonQtWrapper_SoOutput::write(SoOutput* theWrappedObject, double  d)
{
  ( theWrappedObject->write(d));
}

void PythonQtWrapper_SoOutput::write(SoOutput* theWrappedObject, float  f)
{
  ( theWrappedObject->write(f));
}

void PythonQtWrapper_SoOutput::write(SoOutput* theWrappedObject, int  i)
{
  ( theWrappedObject->write(i));
}

void PythonQtWrapper_SoOutput::write(SoOutput* theWrappedObject, short  s)
{
  ( theWrappedObject->write(s));
}

void PythonQtWrapper_SoOutput::write(SoOutput* theWrappedObject, unsigned int  i)
{
  ( theWrappedObject->write(i));
}

void PythonQtWrapper_SoOutput::write(SoOutput* theWrappedObject, unsigned short  s)
{
  ( theWrappedObject->write(s));
}

void PythonQtWrapper_SoOutput::writeBinaryArray(SoOutput* theWrappedObject, double*  d, int  length)
{
  ( theWrappedObject->writeBinaryArray(d, length));
}

void PythonQtWrapper_SoOutput::writeBinaryArray(SoOutput* theWrappedObject, float*  f, int  length)
{
  ( theWrappedObject->writeBinaryArray(f, length));
}

void PythonQtWrapper_SoOutput::writeBinaryArray(SoOutput* theWrappedObject, int*  l, int  length)
{
  ( theWrappedObject->writeBinaryArray(l, length));
}

void PythonQtWrapper_SoOutput::writeBinaryArray(SoOutput* theWrappedObject, unsigned char*  c, int  length)
{
  ( theWrappedObject->writeBinaryArray(c, length));
}



PythonQtShell_SoPath::~PythonQtShell_SoPath() {
  PythonQtPrivate* priv = PythonQt::priv();
  if (priv) { priv->shellClassDeleted(this); }
}
SbName  PythonQtShell_SoPath::getName() const
{
if (_wrapper) {
  PYTHONQT_GIL_SCOPE
  if (((PyObject*)_wrapper)->ob_refcnt > 0) {
    static PyObject* name = PyString_FromString("getName");
    PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
    if (obj) {
      static const char* argumentList[] ={"SbName"};
      static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(1, argumentList);
      SbName returnValue{};
      void* args[1] = {nullptr};
      PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
      if (result) {
        args[0] = PythonQtConv::ConvertPythonToQt(methodInfo->parameters().at(0), result, false, nullptr, &returnValue);
        if (args[0]!=&returnValue) {
          if (args[0]==nullptr) {
            PythonQt::priv()->handleVirtualOverloadReturnError("getName", methodInfo, result);
          } else {
            returnValue = *((SbName*)args[0]);
          }
        }
      }
      if (result) { Py_DECREF(result); } 
      Py_DECREF(obj);
      return returnValue;
    } else {
      PyErr_Clear();
    }
  }
}
  return SoPath::getName();
}
void PythonQtShell_SoPath::setName(const SbName&  name0)
{
if (_wrapper) {
  PYTHONQT_GIL_SCOPE
  if (((PyObject*)_wrapper)->ob_refcnt > 0) {
    static PyObject* name = PyString_FromString("setName");
    PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
    if (obj) {
      static const char* argumentList[] ={"" , "const SbName&"};
      static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(2, argumentList);
      void* args[2] = {nullptr, (void*)&name0};
      PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
      if (result) { Py_DECREF(result); } 
      Py_DECREF(obj);
      return;
    } else {
      PyErr_Clear();
    }
  }
}
  SoPath::setName(name0);
}
void PythonQtShell_SoPath::startNotify()
{
if (_wrapper) {
  PYTHONQT_GIL_SCOPE
  if (((PyObject*)_wrapper)->ob_refcnt > 0) {
    static PyObject* name = PyString_FromString("startNotify");
    PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
    if (obj) {
      static const char* argumentList[] ={""};
      static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(1, argumentList);
      void* args[1] = {nullptr};
      PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
      if (result) { Py_DECREF(result); } 
      Py_DECREF(obj);
      return;
    } else {
      PyErr_Clear();
    }
  }
}
  SoPath::startNotify();
}
void PythonQtShell_SoPath::write(SoWriteAction*  writeAction0) const
{
if (_wrapper) {
  PYTHONQT_GIL_SCOPE
  if (((PyObject*)_wrapper)->ob_refcnt > 0) {
    static PyObject* name = PyString_FromString("write");
    PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
    if (obj) {
      static const char* argumentList[] ={"" , "SoWriteAction*"};
      static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(2, argumentList);
      void* args[2] = {nullptr, (void*)&writeAction0};
      PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
      if (result) { Py_DECREF(result); } 
      Py_DECREF(obj);
      return;
    } else {
      PyErr_Clear();
    }
  }
}
  SoPath::write(writeAction0);
}
SoPath* PythonQtWrapper_SoPath::new_SoPath()
{ 
return new PythonQtShell_SoPath(); }

SoPath* PythonQtWrapper_SoPath::new_SoPath(SoNode*  node)
{ 
return new PythonQtShell_SoPath(node); }

SoPath* PythonQtWrapper_SoPath::new_SoPath(int  approxLength)
{ 
return new PythonQtShell_SoPath(approxLength); }

void PythonQtWrapper_SoPath::append(SoPath* theWrappedObject, SoNode*  childNode)
{
  ( theWrappedObject->append(childNode));
}

void PythonQtWrapper_SoPath::append(SoPath* theWrappedObject, const SoPath*  fromPath)
{
  ( theWrappedObject->append(fromPath));
}

void PythonQtWrapper_SoPath::append(SoPath* theWrappedObject, int  childIndex)
{
  ( theWrappedObject->append(childIndex));
}

void PythonQtWrapper_SoPath::auditPath(SoPath* theWrappedObject, bool  flag)
{
  ( ((PythonQtPublicPromoter_SoPath*)theWrappedObject)->promoted_auditPath(flag));
}

bool  PythonQtWrapper_SoPath::containsNode(SoPath* theWrappedObject, const SoNode*  node) const
{
  return ( theWrappedObject->containsNode(node));
}

bool  PythonQtWrapper_SoPath::containsPath(SoPath* theWrappedObject, const SoPath*  path) const
{
  return ( theWrappedObject->containsPath(path));
}

SoPath*  PythonQtWrapper_SoPath::copy(SoPath* theWrappedObject, int  startFromNodeIndex, int  numNodes) const
{
  return ( theWrappedObject->copy(startFromNodeIndex, numNodes));
}

int  PythonQtWrapper_SoPath::findFork(SoPath* theWrappedObject, const SoPath*  path) const
{
  return ( theWrappedObject->findFork(path));
}

SoPath*  PythonQtWrapper_SoPath::static_SoPath_getByName(const SbName&  name)
{
  return (SoPath::getByName(name));
}

SoType  PythonQtWrapper_SoPath::static_SoPath_getClassTypeId()
{
  return (SoPath::getClassTypeId());
}

SoNode*  PythonQtWrapper_SoPath::getHead(SoPath* theWrappedObject) const
{
  return ( theWrappedObject->getHead());
}

int  PythonQtWrapper_SoPath::getIndex(SoPath* theWrappedObject, int  i) const
{
  return ( theWrappedObject->getIndex(i));
}

int  PythonQtWrapper_SoPath::getIndexFromTail(SoPath* theWrappedObject, int  i) const
{
  return ( theWrappedObject->getIndexFromTail(i));
}

int  PythonQtWrapper_SoPath::getLength(SoPath* theWrappedObject) const
{
  return ( theWrappedObject->getLength());
}

SoNode*  PythonQtWrapper_SoPath::getNode(SoPath* theWrappedObject, int  i) const
{
  return ( theWrappedObject->getNode(i));
}

SoNode*  PythonQtWrapper_SoPath::getNodeFromTail(SoPath* theWrappedObject, int  i) const
{
  return ( theWrappedObject->getNodeFromTail(i));
}

SoNode*  PythonQtWrapper_SoPath::getTail(SoPath* theWrappedObject) const
{
  return ( theWrappedObject->getTail());
}

void PythonQtWrapper_SoPath::insertIndex(SoPath* theWrappedObject, SoNode*  parent, int  newIndex)
{
  ( theWrappedObject->insertIndex(parent, newIndex));
}

bool  PythonQtWrapper_SoPath::__eq__(SoPath* theWrappedObject, const SoPath&  p2)
{
  return ( (*theWrappedObject)== p2);
}

void PythonQtWrapper_SoPath::pop(SoPath* theWrappedObject)
{
  ( theWrappedObject->pop());
}

void PythonQtWrapper_SoPath::push(SoPath* theWrappedObject, int  childIndex)
{
  ( theWrappedObject->push(childIndex));
}

void PythonQtWrapper_SoPath::removeIndex(SoPath* theWrappedObject, SoNode*  parent, int  oldIndex)
{
  ( theWrappedObject->removeIndex(parent, oldIndex));
}

void PythonQtWrapper_SoPath::replaceIndex(SoPath* theWrappedObject, SoNode*  parent, int  index, SoNode*  newChild)
{
  ( theWrappedObject->replaceIndex(parent, index, newChild));
}

void PythonQtWrapper_SoPath::setHead(SoPath* theWrappedObject, SoNode*  node)
{
  ( theWrappedObject->setHead(node));
}

void PythonQtWrapper_SoPath::truncate(SoPath* theWrappedObject, int  start)
{
  ( theWrappedObject->truncate(start));
}

void PythonQtWrapper_SoPath::write(SoPath* theWrappedObject, SoWriteAction*  writeAction) const
{
  ( theWrappedObject->write(writeAction));
}



SoPickedPoint* PythonQtWrapper_SoPickedPoint::new_SoPickedPoint(const SoPath*  path, SoState*  state, const SbVec3f&  objSpacePoint)
{ 
return new SoPickedPoint(path, state, objSpacePoint); }

SoPickedPoint* PythonQtWrapper_SoPickedPoint::new_SoPickedPoint(const SoPickedPoint&  pp)
{ 
return new SoPickedPoint(pp); }

SoPickedPoint*  PythonQtWrapper_SoPickedPoint::copy(SoPickedPoint* theWrappedObject) const
{
  return ( theWrappedObject->copy());
}

const SoDetail*  PythonQtWrapper_SoPickedPoint::getDetail(SoPickedPoint* theWrappedObject, const SoNode*  node) const
{
  return ( theWrappedObject->getDetail(node));
}

SbMatrix  PythonQtWrapper_SoPickedPoint::getImageToObject(SoPickedPoint* theWrappedObject, const SoNode*  node) const
{
  return ( theWrappedObject->getImageToObject(node));
}

int  PythonQtWrapper_SoPickedPoint::getMaterialIndex(SoPickedPoint* theWrappedObject) const
{
  return ( theWrappedObject->getMaterialIndex());
}

const SbVec3f*  PythonQtWrapper_SoPickedPoint::getNormal(SoPickedPoint* theWrappedObject) const
{
  return &( theWrappedObject->getNormal());
}

SbVec3f  PythonQtWrapper_SoPickedPoint::getObjectNormal(SoPickedPoint* theWrappedObject, const SoNode*  node) const
{
  return ( theWrappedObject->getObjectNormal(node));
}

SbVec3f  PythonQtWrapper_SoPickedPoint::getObjectPoint(SoPickedPoint* theWrappedObject, const SoNode*  node) const
{
  return ( theWrappedObject->getObjectPoint(node));
}

SbVec4f  PythonQtWrapper_SoPickedPoint::getObjectTextureCoords(SoPickedPoint* theWrappedObject, const SoNode*  node) const
{
  return ( theWrappedObject->getObjectTextureCoords(node));
}

SbMatrix  PythonQtWrapper_SoPickedPoint::getObjectToImage(SoPickedPoint* theWrappedObject, const SoNode*  node) const
{
  return ( theWrappedObject->getObjectToImage(node));
}

SbMatrix  PythonQtWrapper_SoPickedPoint::getObjectToWorld(SoPickedPoint* theWrappedObject, const SoNode*  node) const
{
  return ( theWrappedObject->getObjectToWorld(node));
}

SoPath*  PythonQtWrapper_SoPickedPoint::getPath(SoPickedPoint* theWrappedObject) const
{
  return ( theWrappedObject->getPath());
}

const SbVec3f*  PythonQtWrapper_SoPickedPoint::getPoint(SoPickedPoint* theWrappedObject) const
{
  return &( theWrappedObject->getPoint());
}

const SbVec4f*  PythonQtWrapper_SoPickedPoint::getTextureCoords(SoPickedPoint* theWrappedObject) const
{
  return &( theWrappedObject->getTextureCoords());
}

SbMatrix  PythonQtWrapper_SoPickedPoint::getWorldToObject(SoPickedPoint* theWrappedObject, const SoNode*  node) const
{
  return ( theWrappedObject->getWorldToObject(node));
}

bool  PythonQtWrapper_SoPickedPoint::isOnGeometry(SoPickedPoint* theWrappedObject) const
{
  return ( theWrappedObject->isOnGeometry());
}

void PythonQtWrapper_SoPickedPoint::setDetail(SoPickedPoint* theWrappedObject, SoDetail*  detail, SoNode*  node)
{
  ( theWrappedObject->setDetail(detail, node));
}

void PythonQtWrapper_SoPickedPoint::setMaterialIndex(SoPickedPoint* theWrappedObject, int  index)
{
  ( theWrappedObject->setMaterialIndex(index));
}

void PythonQtWrapper_SoPickedPoint::setObjectNormal(SoPickedPoint* theWrappedObject, const SbVec3f&  normal)
{
  ( theWrappedObject->setObjectNormal(normal));
}

void PythonQtWrapper_SoPickedPoint::setObjectTextureCoords(SoPickedPoint* theWrappedObject, const SbVec4f&  texCoords)
{
  ( theWrappedObject->setObjectTextureCoords(texCoords));
}



SoPrimitiveVertex* PythonQtWrapper_SoPrimitiveVertex::new_SoPrimitiveVertex()
{ 
return new SoPrimitiveVertex(); }

SoPrimitiveVertex* PythonQtWrapper_SoPrimitiveVertex::new_SoPrimitiveVertex(const SoPrimitiveVertex&  pv)
{ 
return new SoPrimitiveVertex(pv); }

const SoDetail*  PythonQtWrapper_SoPrimitiveVertex::getDetail(SoPrimitiveVertex* theWrappedObject) const
{
  return ( theWrappedObject->getDetail());
}

int  PythonQtWrapper_SoPrimitiveVertex::getMaterialIndex(SoPrimitiveVertex* theWrappedObject) const
{
  return ( theWrappedObject->getMaterialIndex());
}

const SbVec3f*  PythonQtWrapper_SoPrimitiveVertex::getNormal(SoPrimitiveVertex* theWrappedObject) const
{
  return &( theWrappedObject->getNormal());
}

const SbVec3f*  PythonQtWrapper_SoPrimitiveVertex::getPoint(SoPrimitiveVertex* theWrappedObject) const
{
  return &( theWrappedObject->getPoint());
}

const SbVec4f*  PythonQtWrapper_SoPrimitiveVertex::getTextureCoords(SoPrimitiveVertex* theWrappedObject) const
{
  return &( theWrappedObject->getTextureCoords());
}

SoPrimitiveVertex*  PythonQtWrapper_SoPrimitiveVertex::operator_assign(SoPrimitiveVertex* theWrappedObject, const SoPrimitiveVertex&  pv)
{
  return &( (*theWrappedObject)= pv);
}

void PythonQtWrapper_SoPrimitiveVertex::setDetail(SoPrimitiveVertex* theWrappedObject, SoDetail*  d)
{
  ( theWrappedObject->setDetail(d));
}

void PythonQtWrapper_SoPrimitiveVertex::setMaterialIndex(SoPrimitiveVertex* theWrappedObject, int  index)
{
  ( theWrappedObject->setMaterialIndex(index));
}

void PythonQtWrapper_SoPrimitiveVertex::setNormal(SoPrimitiveVertex* theWrappedObject, const SbVec3f&  norm)
{
  ( theWrappedObject->setNormal(norm));
}

void PythonQtWrapper_SoPrimitiveVertex::setPoint(SoPrimitiveVertex* theWrappedObject, const SbVec3f&  pt)
{
  ( theWrappedObject->setPoint(pt));
}

void PythonQtWrapper_SoPrimitiveVertex::setTextureCoords(SoPrimitiveVertex* theWrappedObject, const SbVec4f&  t)
{
  ( theWrappedObject->setTextureCoords(t));
}



PythonQtShell_SoSceneManager::~PythonQtShell_SoSceneManager() {
  PythonQtPrivate* priv = PythonQt::priv();
  if (priv) { priv->shellClassDeleted(this); }
}
void PythonQtShell_SoSceneManager::activate()
{
if (_wrapper) {
  PYTHONQT_GIL_SCOPE
  if (((PyObject*)_wrapper)->ob_refcnt > 0) {
    static PyObject* name = PyString_FromString("activate");
    PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
    if (obj) {
      static const char* argumentList[] ={""};
      static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(1, argumentList);
      void* args[1] = {nullptr};
      PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
      if (result) { Py_DECREF(result); } 
      Py_DECREF(obj);
      return;
    } else {
      PyErr_Clear();
    }
  }
}
  SoSceneManager::activate();
}
void PythonQtShell_SoSceneManager::deactivate()
{
if (_wrapper) {
  PYTHONQT_GIL_SCOPE
  if (((PyObject*)_wrapper)->ob_refcnt > 0) {
    static PyObject* name = PyString_FromString("deactivate");
    PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
    if (obj) {
      static const char* argumentList[] ={""};
      static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(1, argumentList);
      void* args[1] = {nullptr};
      PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
      if (result) { Py_DECREF(result); } 
      Py_DECREF(obj);
      return;
    } else {
      PyErr_Clear();
    }
  }
}
  SoSceneManager::deactivate();
}
SoNode*  PythonQtShell_SoSceneManager::getSceneGraph() const
{
if (_wrapper) {
  PYTHONQT_GIL_SCOPE
  if (((PyObject*)_wrapper)->ob_refcnt > 0) {
    static PyObject* name = PyString_FromString("getSceneGraph");
    PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
    if (obj) {
      static const char* argumentList[] ={"SoNode*"};
      static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(1, argumentList);
      SoNode* returnValue{};
      void* args[1] = {nullptr};
      PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
      if (result) {
        args[0] = PythonQtConv::ConvertPythonToQt(methodInfo->parameters().at(0), result, false, nullptr, &returnValue);
        if (args[0]!=&returnValue) {
          if (args[0]==nullptr) {
            PythonQt::priv()->handleVirtualOverloadReturnError("getSceneGraph", methodInfo, result);
          } else {
            returnValue = *((SoNode**)args[0]);
          }
        }
      }
      if (result) { Py_DECREF(result); } 
      Py_DECREF(obj);
      return returnValue;
    } else {
      PyErr_Clear();
    }
  }
}
  return SoSceneManager::getSceneGraph();
}
bool  PythonQtShell_SoSceneManager::processEvent(const SoEvent*  event0)
{
if (_wrapper) {
  PYTHONQT_GIL_SCOPE
  if (((PyObject*)_wrapper)->ob_refcnt > 0) {
    static PyObject* name = PyString_FromString("processEvent");
    PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
    if (obj) {
      static const char* argumentList[] ={"bool" , "const SoEvent*"};
      static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(2, argumentList);
      bool returnValue{};
      void* args[2] = {nullptr, (void*)&event0};
      PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
      if (result) {
        args[0] = PythonQtConv::ConvertPythonToQt(methodInfo->parameters().at(0), result, false, nullptr, &returnValue);
        if (args[0]!=&returnValue) {
          if (args[0]==nullptr) {
            PythonQt::priv()->handleVirtualOverloadReturnError("processEvent", methodInfo, result);
          } else {
            returnValue = *((bool*)args[0]);
          }
        }
      }
      if (result) { Py_DECREF(result); } 
      Py_DECREF(obj);
      return returnValue;
    } else {
      PyErr_Clear();
    }
  }
}
  return SoSceneManager::processEvent(event0);
}
void PythonQtShell_SoSceneManager::render(bool  clearWindow0, bool  clearZbuffer1)
{
if (_wrapper) {
  PYTHONQT_GIL_SCOPE
  if (((PyObject*)_wrapper)->ob_refcnt > 0) {
    static PyObject* name = PyString_FromString("render");
    PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
    if (obj) {
      static const char* argumentList[] ={"" , "bool" , "bool"};
      static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(3, argumentList);
      void* args[3] = {nullptr, (void*)&clearWindow0, (void*)&clearZbuffer1};
      PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
      if (result) { Py_DECREF(result); } 
      Py_DECREF(obj);
      return;
    } else {
      PyErr_Clear();
    }
  }
}
  SoSceneManager::render(clearWindow0, clearZbuffer1);
}
void PythonQtShell_SoSceneManager::setSceneGraph(SoNode*  newScene0)
{
if (_wrapper) {
  PYTHONQT_GIL_SCOPE
  if (((PyObject*)_wrapper)->ob_refcnt > 0) {
    static PyObject* name = PyString_FromString("setSceneGraph");
    PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
    if (obj) {
      static const char* argumentList[] ={"" , "SoNode*"};
      static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(2, argumentList);
      void* args[2] = {nullptr, (void*)&newScene0};
      PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
      if (result) { Py_DECREF(result); } 
      Py_DECREF(obj);
      return;
    } else {
      PyErr_Clear();
    }
  }
}
  SoSceneManager::setSceneGraph(newScene0);
}
SoSceneManager* PythonQtWrapper_SoSceneManager::new_SoSceneManager()
{ 
return new PythonQtShell_SoSceneManager(); }

void PythonQtWrapper_SoSceneManager::activate(SoSceneManager* theWrappedObject)
{
  ( theWrappedObject->activate());
}

void PythonQtWrapper_SoSceneManager::deactivate(SoSceneManager* theWrappedObject)
{
  ( theWrappedObject->deactivate());
}

void PythonQtWrapper_SoSceneManager::static_SoSceneManager_enableRealTimeUpdate(bool  flag)
{
  (SoSceneManager::enableRealTimeUpdate(flag));
}

void PythonQtWrapper_SoSceneManager::getAntialiasing(SoSceneManager* theWrappedObject, bool&  smoothing, int&  numPasses) const
{
  ( theWrappedObject->getAntialiasing(smoothing, numPasses));
}

const SbColor*  PythonQtWrapper_SoSceneManager::getBackgroundColor(SoSceneManager* theWrappedObject) const
{
  return &( theWrappedObject->getBackgroundColor());
}

unsigned int  PythonQtWrapper_SoSceneManager::static_SoSceneManager_getDefaultRedrawPriority()
{
  return (SoSceneManager::getDefaultRedrawPriority());
}

SoGLRenderAction*  PythonQtWrapper_SoSceneManager::getGLRenderAction(SoSceneManager* theWrappedObject) const
{
  return ( theWrappedObject->getGLRenderAction());
}

SoHandleEventAction*  PythonQtWrapper_SoSceneManager::getHandleEventAction(SoSceneManager* theWrappedObject) const
{
  return ( theWrappedObject->getHandleEventAction());
}

const SbVec2s*  PythonQtWrapper_SoSceneManager::getOrigin(SoSceneManager* theWrappedObject) const
{
  return &( theWrappedObject->getOrigin());
}

unsigned int  PythonQtWrapper_SoSceneManager::getRedrawPriority(SoSceneManager* theWrappedObject) const
{
  return ( theWrappedObject->getRedrawPriority());
}

SoNode*  PythonQtWrapper_SoSceneManager::getSceneGraph(SoSceneManager* theWrappedObject) const
{
  return ( theWrappedObject->getSceneGraph());
}

const SbVec2s*  PythonQtWrapper_SoSceneManager::getSize(SoSceneManager* theWrappedObject) const
{
  return &( theWrappedObject->getSize());
}

const SbViewportRegion*  PythonQtWrapper_SoSceneManager::getViewportRegion(SoSceneManager* theWrappedObject) const
{
  return &( theWrappedObject->getViewportRegion());
}

const SbVec2s*  PythonQtWrapper_SoSceneManager::getWindowSize(SoSceneManager* theWrappedObject) const
{
  return &( theWrappedObject->getWindowSize());
}

bool  PythonQtWrapper_SoSceneManager::isActive(SoSceneManager* theWrappedObject) const
{
  return ( ((PythonQtPublicPromoter_SoSceneManager*)theWrappedObject)->promoted_isActive());
}

bool  PythonQtWrapper_SoSceneManager::isAutoRedraw(SoSceneManager* theWrappedObject) const
{
  return ( theWrappedObject->isAutoRedraw());
}

bool  PythonQtWrapper_SoSceneManager::static_SoSceneManager_isRealTimeUpdateEnabled()
{
  return (SoSceneManager::isRealTimeUpdateEnabled());
}

bool  PythonQtWrapper_SoSceneManager::processEvent(SoSceneManager* theWrappedObject, const SoEvent*  event)
{
  return ( theWrappedObject->processEvent(event));
}

void PythonQtWrapper_SoSceneManager::redraw(SoSceneManager* theWrappedObject)
{
  ( ((PythonQtPublicPromoter_SoSceneManager*)theWrappedObject)->promoted_redraw());
}

void PythonQtWrapper_SoSceneManager::reinitialize(SoSceneManager* theWrappedObject)
{
  ( theWrappedObject->reinitialize());
}

void PythonQtWrapper_SoSceneManager::render(SoSceneManager* theWrappedObject, bool  clearWindow, bool  clearZbuffer)
{
  ( theWrappedObject->render(clearWindow, clearZbuffer));
}

void PythonQtWrapper_SoSceneManager::scheduleRedraw(SoSceneManager* theWrappedObject)
{
  ( theWrappedObject->scheduleRedraw());
}

void PythonQtWrapper_SoSceneManager::setAntialiasing(SoSceneManager* theWrappedObject, bool  smoothing, int  numPasses)
{
  ( theWrappedObject->setAntialiasing(smoothing, numPasses));
}

void PythonQtWrapper_SoSceneManager::setBackgroundColor(SoSceneManager* theWrappedObject, const SbColor&  c)
{
  ( theWrappedObject->setBackgroundColor(c));
}

void PythonQtWrapper_SoSceneManager::setGLRenderAction(SoSceneManager* theWrappedObject, SoGLRenderAction*  ra)
{
  ( theWrappedObject->setGLRenderAction(ra));
}

void PythonQtWrapper_SoSceneManager::setHandleEventAction(SoSceneManager* theWrappedObject, SoHandleEventAction*  hea)
{
  ( theWrappedObject->setHandleEventAction(hea));
}

void PythonQtWrapper_SoSceneManager::setOrigin(SoSceneManager* theWrappedObject, const SbVec2s&  newOrigin)
{
  ( theWrappedObject->setOrigin(newOrigin));
}

void PythonQtWrapper_SoSceneManager::setRedrawPriority(SoSceneManager* theWrappedObject, unsigned int  priority)
{
  ( theWrappedObject->setRedrawPriority(priority));
}

void PythonQtWrapper_SoSceneManager::setSceneGraph(SoSceneManager* theWrappedObject, SoNode*  newScene)
{
  ( theWrappedObject->setSceneGraph(newScene));
}

void PythonQtWrapper_SoSceneManager::setSize(SoSceneManager* theWrappedObject, const SbVec2s&  newSize)
{
  ( theWrappedObject->setSize(newSize));
}

void PythonQtWrapper_SoSceneManager::setViewportRegion(SoSceneManager* theWrappedObject, const SbViewportRegion&  newRegion)
{
  ( theWrappedObject->setViewportRegion(newRegion));
}

void PythonQtWrapper_SoSceneManager::setWindowSize(SoSceneManager* theWrappedObject, const SbVec2s&  newSize)
{
  ( theWrappedObject->setWindowSize(newSize));
}



SoAction*  PythonQtWrapper_SoState::getAction(SoState* theWrappedObject) const
{
  return ( theWrappedObject->getAction());
}

const SoElement*  PythonQtWrapper_SoState::getConstElement(SoState* theWrappedObject, int  stackIndex) const
{
  return ( theWrappedObject->getConstElement(stackIndex));
}

int  PythonQtWrapper_SoState::getDepth(SoState* theWrappedObject) const
{
  return ( theWrappedObject->getDepth());
}

SoElement*  PythonQtWrapper_SoState::getElement(SoState* theWrappedObject, int  stackIndex)
{
  return ( theWrappedObject->getElement(stackIndex));
}

SoElement*  PythonQtWrapper_SoState::getElementNoPush(SoState* theWrappedObject, int  stackIndex) const
{
  return ( theWrappedObject->getElementNoPush(stackIndex));
}

bool  PythonQtWrapper_SoState::isCacheOpen(SoState* theWrappedObject) const
{
  return ( theWrappedObject->isCacheOpen());
}

bool  PythonQtWrapper_SoState::isElementEnabled(SoState* theWrappedObject, int  stackIndex) const
{
  return ( theWrappedObject->isElementEnabled(stackIndex));
}

void PythonQtWrapper_SoState::pop(SoState* theWrappedObject)
{
  ( theWrappedObject->pop());
}

void PythonQtWrapper_SoState::push(SoState* theWrappedObject)
{
  ( theWrappedObject->push());
}

void PythonQtWrapper_SoState::setCacheOpen(SoState* theWrappedObject, bool  flag)
{
  ( theWrappedObject->setCacheOpen(flag));
}



PythonQtShell_SoType::~PythonQtShell_SoType() {
  PythonQtPrivate* priv = PythonQt::priv();
  if (priv) { priv->shellClassDeleted(this); }
}
SoType* PythonQtWrapper_SoType::new_SoType()
{ 
return new PythonQtShell_SoType(); }

SoType  PythonQtWrapper_SoType::static_SoType_badType()
{
  return (SoType::badType());
}

bool  PythonQtWrapper_SoType::canCreateInstance(SoType* theWrappedObject) const
{
  return ( theWrappedObject->canCreateInstance());
}

void*  PythonQtWrapper_SoType::createInstance(SoType* theWrappedObject) const
{
  return ( theWrappedObject->createInstance());
}

SoType  PythonQtWrapper_SoType::static_SoType_fromName(SbName  name)
{
  return (SoType::fromName(name));
}

short  PythonQtWrapper_SoType::getData(SoType* theWrappedObject) const
{
  return ( theWrappedObject->getData());
}

short  PythonQtWrapper_SoType::getKey(SoType* theWrappedObject) const
{
  return ( theWrappedObject->getKey());
}

SbName  PythonQtWrapper_SoType::getName(SoType* theWrappedObject) const
{
  return ( theWrappedObject->getName());
}

int  PythonQtWrapper_SoType::static_SoType_getNumTypes()
{
  return (SoType::getNumTypes());
}

SoType  PythonQtWrapper_SoType::getParent(SoType* theWrappedObject) const
{
  return ( theWrappedObject->getParent());
}

void PythonQtWrapper_SoType::static_SoType_init()
{
  (SoType::init());
}

bool  PythonQtWrapper_SoType::isBad(SoType* theWrappedObject) const
{
  return ( theWrappedObject->isBad());
}

bool  PythonQtWrapper_SoType::isDerivedFrom(SoType* theWrappedObject, SoType  t) const
{
  return ( theWrappedObject->isDerivedFrom(t));
}

void PythonQtWrapper_SoType::makeInternal(SoType* theWrappedObject)
{
  ( theWrappedObject->makeInternal());
}

bool  PythonQtWrapper_SoType::__ne__(SoType* theWrappedObject, const SoType  t) const
{
  return ( (*theWrappedObject)!= t);
}

bool  PythonQtWrapper_SoType::__lt__(SoType* theWrappedObject, const SoType  t) const
{
  return ( (*theWrappedObject)< t);
}

bool  PythonQtWrapper_SoType::__eq__(SoType* theWrappedObject, const SoType  t) const
{
  return ( (*theWrappedObject)== t);
}


