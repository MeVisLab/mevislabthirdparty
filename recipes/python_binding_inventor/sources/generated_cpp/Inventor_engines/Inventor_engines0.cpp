/*************************************************************************************
**
** Copyright 2022, MeVis Medical Solutions AG
**
** GNU LESSER GENERAL PUBLIC LICENSE Version 2.1, February 1999
**
**************************************************************************************/
#include "Inventor_engines0.h"
#include <PythonQtConversion.h>
#include <PythonQtMethodInfo.h>
#include <PythonQtSignalReceiver.h>
#include <QVariant>
#include <Inventor/SbLinear.h>
#include <Inventor/SbString.h>
#include <Inventor/SbViewportRegion.h>
#include <Inventor/SoInput.h>
#include <Inventor/SoOutput.h>
#include <Inventor/SoType.h>
#include <Inventor/engines/SoEngine.h>
#include <Inventor/fields/SoField.h>
#include <Inventor/fields/SoFieldContainer.h>
#include <Inventor/fields/SoFieldData.h>
#include <Inventor/misc/SoBase.h>
#include <Inventor/sensors/SoSensor.h>

SoBoolOperation* PythonQtWrapper_SoBoolOperation::new_SoBoolOperation()
{ 
return new SoBoolOperation(); }

SoType  PythonQtWrapper_SoBoolOperation::static_SoBoolOperation_getClassTypeId()
{
  return (SoBoolOperation::getClassTypeId());
}



SoCalculator* PythonQtWrapper_SoCalculator::new_SoCalculator()
{ 
return new SoCalculator(); }

SoType  PythonQtWrapper_SoCalculator::static_SoCalculator_getClassTypeId()
{
  return (SoCalculator::getClassTypeId());
}



SoComposeMatrix* PythonQtWrapper_SoComposeMatrix::new_SoComposeMatrix()
{ 
return new SoComposeMatrix(); }

SoType  PythonQtWrapper_SoComposeMatrix::static_SoComposeMatrix_getClassTypeId()
{
  return (SoComposeMatrix::getClassTypeId());
}



SoComposeRotation* PythonQtWrapper_SoComposeRotation::new_SoComposeRotation()
{ 
return new SoComposeRotation(); }

SoType  PythonQtWrapper_SoComposeRotation::static_SoComposeRotation_getClassTypeId()
{
  return (SoComposeRotation::getClassTypeId());
}



SoComposeRotationFromTo* PythonQtWrapper_SoComposeRotationFromTo::new_SoComposeRotationFromTo()
{ 
return new SoComposeRotationFromTo(); }

SoType  PythonQtWrapper_SoComposeRotationFromTo::static_SoComposeRotationFromTo_getClassTypeId()
{
  return (SoComposeRotationFromTo::getClassTypeId());
}



SoComposeVec2f* PythonQtWrapper_SoComposeVec2f::new_SoComposeVec2f()
{ 
return new SoComposeVec2f(); }

SoType  PythonQtWrapper_SoComposeVec2f::static_SoComposeVec2f_getClassTypeId()
{
  return (SoComposeVec2f::getClassTypeId());
}



SoComposeVec3f* PythonQtWrapper_SoComposeVec3f::new_SoComposeVec3f()
{ 
return new SoComposeVec3f(); }

SoType  PythonQtWrapper_SoComposeVec3f::static_SoComposeVec3f_getClassTypeId()
{
  return (SoComposeVec3f::getClassTypeId());
}



SoComposeVec4f* PythonQtWrapper_SoComposeVec4f::new_SoComposeVec4f()
{ 
return new SoComposeVec4f(); }

SoType  PythonQtWrapper_SoComposeVec4f::static_SoComposeVec4f_getClassTypeId()
{
  return (SoComposeVec4f::getClassTypeId());
}



SoComputeBoundingBox* PythonQtWrapper_SoComputeBoundingBox::new_SoComputeBoundingBox()
{ 
return new SoComputeBoundingBox(); }

SoType  PythonQtWrapper_SoComputeBoundingBox::static_SoComputeBoundingBox_getClassTypeId()
{
  return (SoComputeBoundingBox::getClassTypeId());
}

const SbViewportRegion*  PythonQtWrapper_SoComputeBoundingBox::getViewportRegion(SoComputeBoundingBox* theWrappedObject) const
{
  return &( theWrappedObject->getViewportRegion());
}

void PythonQtWrapper_SoComputeBoundingBox::setViewportRegion(SoComputeBoundingBox* theWrappedObject, const SbViewportRegion&  vpReg)
{
  ( theWrappedObject->setViewportRegion(vpReg));
}



SoCounter* PythonQtWrapper_SoCounter::new_SoCounter()
{ 
return new SoCounter(); }

SoType  PythonQtWrapper_SoCounter::static_SoCounter_getClassTypeId()
{
  return (SoCounter::getClassTypeId());
}



SoDecomposeMatrix* PythonQtWrapper_SoDecomposeMatrix::new_SoDecomposeMatrix()
{ 
return new SoDecomposeMatrix(); }

SoType  PythonQtWrapper_SoDecomposeMatrix::static_SoDecomposeMatrix_getClassTypeId()
{
  return (SoDecomposeMatrix::getClassTypeId());
}



SoDecomposeRotation* PythonQtWrapper_SoDecomposeRotation::new_SoDecomposeRotation()
{ 
return new SoDecomposeRotation(); }

SoType  PythonQtWrapper_SoDecomposeRotation::static_SoDecomposeRotation_getClassTypeId()
{
  return (SoDecomposeRotation::getClassTypeId());
}



SoDecomposeVec2f* PythonQtWrapper_SoDecomposeVec2f::new_SoDecomposeVec2f()
{ 
return new SoDecomposeVec2f(); }

SoType  PythonQtWrapper_SoDecomposeVec2f::static_SoDecomposeVec2f_getClassTypeId()
{
  return (SoDecomposeVec2f::getClassTypeId());
}



SoDecomposeVec3f* PythonQtWrapper_SoDecomposeVec3f::new_SoDecomposeVec3f()
{ 
return new SoDecomposeVec3f(); }

SoType  PythonQtWrapper_SoDecomposeVec3f::static_SoDecomposeVec3f_getClassTypeId()
{
  return (SoDecomposeVec3f::getClassTypeId());
}



SoDecomposeVec4f* PythonQtWrapper_SoDecomposeVec4f::new_SoDecomposeVec4f()
{ 
return new SoDecomposeVec4f(); }

SoType  PythonQtWrapper_SoDecomposeVec4f::static_SoDecomposeVec4f_getClassTypeId()
{
  return (SoDecomposeVec4f::getClassTypeId());
}



SoElapsedTime* PythonQtWrapper_SoElapsedTime::new_SoElapsedTime()
{ 
return new SoElapsedTime(); }

SoType  PythonQtWrapper_SoElapsedTime::static_SoElapsedTime_getClassTypeId()
{
  return (SoElapsedTime::getClassTypeId());
}



SoEngine*  PythonQtWrapper_SoEngine::copy(SoEngine* theWrappedObject) const
{
  return ( theWrappedObject->copy());
}

void PythonQtWrapper_SoEngine::evaluateWrapper(SoEngine* theWrappedObject)
{
  ( theWrappedObject->evaluateWrapper());
}

SoEngine*  PythonQtWrapper_SoEngine::static_SoEngine_getByName(const SbName&  name)
{
  return (SoEngine::getByName(name));
}

SoType  PythonQtWrapper_SoEngine::static_SoEngine_getClassTypeId()
{
  return (SoEngine::getClassTypeId());
}

SoEngineOutput*  PythonQtWrapper_SoEngine::getOutput(SoEngine* theWrappedObject, const SbName&  outputName) const
{
  return ( theWrappedObject->getOutput(outputName));
}

bool  PythonQtWrapper_SoEngine::isNotifying(SoEngine* theWrappedObject) const
{
  return ( theWrappedObject->isNotifying());
}

bool  PythonQtWrapper_SoEngine::shouldCopy(SoEngine* theWrappedObject) const
{
  return ( theWrappedObject->shouldCopy());
}



SoEngineOutput* PythonQtWrapper_SoEngineOutput::new_SoEngineOutput()
{ 
return new SoEngineOutput(); }

void PythonQtWrapper_SoEngineOutput::addConnection(SoEngineOutput* theWrappedObject, SoField*  arg__1)
{
  ( theWrappedObject->addConnection(arg__1));
}

void PythonQtWrapper_SoEngineOutput::doneWriting(SoEngineOutput* theWrappedObject) const
{
  ( theWrappedObject->doneWriting());
}

void PythonQtWrapper_SoEngineOutput::enable(SoEngineOutput* theWrappedObject, bool  flag)
{
  ( theWrappedObject->enable(flag));
}

SoType  PythonQtWrapper_SoEngineOutput::getConnectionType(SoEngineOutput* theWrappedObject) const
{
  return ( theWrappedObject->getConnectionType());
}

SoEngine*  PythonQtWrapper_SoEngineOutput::getContainer(SoEngineOutput* theWrappedObject) const
{
  return ( theWrappedObject->getContainer());
}

int  PythonQtWrapper_SoEngineOutput::getNumConnections(SoEngineOutput* theWrappedObject) const
{
  return ( theWrappedObject->getNumConnections());
}

bool  PythonQtWrapper_SoEngineOutput::isEnabled(SoEngineOutput* theWrappedObject) const
{
  return ( theWrappedObject->isEnabled());
}

SoField*  PythonQtWrapper_SoEngineOutput::operator_subscript(SoEngineOutput* theWrappedObject, int  i) const
{
  return ( (*theWrappedObject)[i]);
}

void PythonQtWrapper_SoEngineOutput::prepareToWrite(SoEngineOutput* theWrappedObject) const
{
  ( theWrappedObject->prepareToWrite());
}

void PythonQtWrapper_SoEngineOutput::removeConnection(SoEngineOutput* theWrappedObject, SoField*  arg__1)
{
  ( theWrappedObject->removeConnection(arg__1));
}

void PythonQtWrapper_SoEngineOutput::setContainer(SoEngineOutput* theWrappedObject, SoEngine*  eng)
{
  ( theWrappedObject->setContainer(eng));
}



SoType  PythonQtWrapper_SoFieldConverter::static_SoFieldConverter_getClassTypeId()
{
  return (SoFieldConverter::getClassTypeId());
}

SoField*  PythonQtWrapper_SoFieldConverter::getConnectedInput(SoFieldConverter* theWrappedObject)
{
  return ( theWrappedObject->getConnectedInput());
}

SoField*  PythonQtWrapper_SoFieldConverter::getInput(SoFieldConverter* theWrappedObject, SoType  type)
{
  return ( theWrappedObject->getInput(type));
}

SoEngineOutput*  PythonQtWrapper_SoFieldConverter::getOutput(SoFieldConverter* theWrappedObject, SoType  type)
{
  return ( theWrappedObject->getOutput(type));
}



SoGate* PythonQtWrapper_SoGate::new_SoGate(SoType  mfInputType)
{ 
return new SoGate(mfInputType); }

SoType  PythonQtWrapper_SoGate::static_SoGate_getClassTypeId()
{
  return (SoGate::getClassTypeId());
}



SoType  PythonQtWrapper_SoInterpolate::static_SoInterpolate_getClassTypeId()
{
  return (SoInterpolate::getClassTypeId());
}



SoInterpolateFloat* PythonQtWrapper_SoInterpolateFloat::new_SoInterpolateFloat()
{ 
return new SoInterpolateFloat(); }

SoType  PythonQtWrapper_SoInterpolateFloat::static_SoInterpolateFloat_getClassTypeId()
{
  return (SoInterpolateFloat::getClassTypeId());
}



SoInterpolateRotation* PythonQtWrapper_SoInterpolateRotation::new_SoInterpolateRotation()
{ 
return new SoInterpolateRotation(); }

SoType  PythonQtWrapper_SoInterpolateRotation::static_SoInterpolateRotation_getClassTypeId()
{
  return (SoInterpolateRotation::getClassTypeId());
}



SoInterpolateVec2f* PythonQtWrapper_SoInterpolateVec2f::new_SoInterpolateVec2f()
{ 
return new SoInterpolateVec2f(); }

SoType  PythonQtWrapper_SoInterpolateVec2f::static_SoInterpolateVec2f_getClassTypeId()
{
  return (SoInterpolateVec2f::getClassTypeId());
}



SoInterpolateVec3f* PythonQtWrapper_SoInterpolateVec3f::new_SoInterpolateVec3f()
{ 
return new SoInterpolateVec3f(); }

SoType  PythonQtWrapper_SoInterpolateVec3f::static_SoInterpolateVec3f_getClassTypeId()
{
  return (SoInterpolateVec3f::getClassTypeId());
}



SoInterpolateVec4f* PythonQtWrapper_SoInterpolateVec4f::new_SoInterpolateVec4f()
{ 
return new SoInterpolateVec4f(); }

SoType  PythonQtWrapper_SoInterpolateVec4f::static_SoInterpolateVec4f_getClassTypeId()
{
  return (SoInterpolateVec4f::getClassTypeId());
}



SoOnOff* PythonQtWrapper_SoOnOff::new_SoOnOff()
{ 
return new SoOnOff(); }

SoType  PythonQtWrapper_SoOnOff::static_SoOnOff_getClassTypeId()
{
  return (SoOnOff::getClassTypeId());
}



SoOneShot* PythonQtWrapper_SoOneShot::new_SoOneShot()
{ 
return new SoOneShot(); }

SoType  PythonQtWrapper_SoOneShot::static_SoOneShot_getClassTypeId()
{
  return (SoOneShot::getClassTypeId());
}



SoSelectOne* PythonQtWrapper_SoSelectOne::new_SoSelectOne(SoType  mfInputType)
{ 
return new SoSelectOne(mfInputType); }

SoType  PythonQtWrapper_SoSelectOne::static_SoSelectOne_getClassTypeId()
{
  return (SoSelectOne::getClassTypeId());
}



SoTimeCounter* PythonQtWrapper_SoTimeCounter::new_SoTimeCounter()
{ 
return new SoTimeCounter(); }

SoType  PythonQtWrapper_SoTimeCounter::static_SoTimeCounter_getClassTypeId()
{
  return (SoTimeCounter::getClassTypeId());
}


