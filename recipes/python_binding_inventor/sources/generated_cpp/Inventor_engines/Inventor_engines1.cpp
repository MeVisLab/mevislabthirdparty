/*************************************************************************************
**
** Copyright 2022, MeVis Medical Solutions AG
**
** GNU LESSER GENERAL PUBLIC LICENSE Version 2.1, February 1999
**
**************************************************************************************/
#include "Inventor_engines1.h"
#include <PythonQtConversion.h>
#include <PythonQtMethodInfo.h>
#include <PythonQtSignalReceiver.h>
#include <QVariant>
#include <Inventor/SbString.h>
#include <Inventor/SoInput.h>
#include <Inventor/SoOutput.h>
#include <Inventor/SoType.h>
#include <Inventor/engines/SoEngine.h>
#include <Inventor/fields/SoField.h>
#include <Inventor/fields/SoFieldContainer.h>
#include <Inventor/fields/SoFieldData.h>
#include <Inventor/misc/SoBase.h>
#include <Inventor/sensors/SoSensor.h>

SoTransformVec3f* PythonQtWrapper_SoTransformVec3f::new_SoTransformVec3f()
{ 
return new SoTransformVec3f(); }

SoType  PythonQtWrapper_SoTransformVec3f::static_SoTransformVec3f_getClassTypeId()
{
  return (SoTransformVec3f::getClassTypeId());
}



SoTriggerAny* PythonQtWrapper_SoTriggerAny::new_SoTriggerAny()
{ 
return new SoTriggerAny(); }

SoType  PythonQtWrapper_SoTriggerAny::static_SoTriggerAny_getClassTypeId()
{
  return (SoTriggerAny::getClassTypeId());
}


