#include "inventor_sensors0.h"
#include <Inventor/SbTime.h>
#include <Inventor/SoPath.h>
#include <Inventor/fields/SoField.h>
#include <Inventor/nodes/SoNode.h>
#include <Inventor/sensors/SoSensor.h>
#include <PythonQtConversion.h>
#include <PythonQtMethodInfo.h>
#include <PythonQtSignalReceiver.h>
#include <QVariant>

const SbTime*  PythonQtWrapper_SoAlarmSensor::getTime(SoAlarmSensor* theWrappedObject) const
{
  return &( theWrappedObject->getTime());
}

void PythonQtWrapper_SoAlarmSensor::setTime(SoAlarmSensor* theWrappedObject, const SbTime&  absTime)
{
  ( theWrappedObject->setTime(absTime));
}

void PythonQtWrapper_SoAlarmSensor::setTimeFromNow(SoAlarmSensor* theWrappedObject, const SbTime&  relTime)
{
  ( theWrappedObject->setTimeFromNow(relTime));
}



void PythonQtWrapper_SoDataSensor::dyingReference(SoDataSensor* theWrappedObject)
{
  ( theWrappedObject->dyingReference());
}

SoField*  PythonQtWrapper_SoDataSensor::getTriggerField(SoDataSensor* theWrappedObject) const
{
  return ( theWrappedObject->getTriggerField());
}

SoNode*  PythonQtWrapper_SoDataSensor::getTriggerNode(SoDataSensor* theWrappedObject) const
{
  return ( theWrappedObject->getTriggerNode());
}

SoPath*  PythonQtWrapper_SoDataSensor::getTriggerPath(SoDataSensor* theWrappedObject) const
{
  return ( theWrappedObject->getTriggerPath());
}

bool  PythonQtWrapper_SoDataSensor::getTriggerPathFlag(SoDataSensor* theWrappedObject) const
{
  return ( theWrappedObject->getTriggerPathFlag());
}

void PythonQtWrapper_SoDataSensor::setTriggerPathFlag(SoDataSensor* theWrappedObject, bool  flag)
{
  ( theWrappedObject->setTriggerPathFlag(flag));
}



unsigned int  PythonQtWrapper_SoDelayQueueSensor::getCounter(SoDelayQueueSensor* theWrappedObject) const
{
  return ( theWrappedObject->getCounter());
}

unsigned int  PythonQtWrapper_SoDelayQueueSensor::static_SoDelayQueueSensor_getDefaultPriority()
{
  return (SoDelayQueueSensor::getDefaultPriority());
}

unsigned int  PythonQtWrapper_SoDelayQueueSensor::getPriority(SoDelayQueueSensor* theWrappedObject) const
{
  return ( theWrappedObject->getPriority());
}

bool  PythonQtWrapper_SoDelayQueueSensor::isIdleOnly(SoDelayQueueSensor* theWrappedObject) const
{
  return ( theWrappedObject->isIdleOnly());
}

void PythonQtWrapper_SoDelayQueueSensor::setCounter(SoDelayQueueSensor* theWrappedObject, unsigned int  c)
{
  ( theWrappedObject->setCounter(c));
}

void PythonQtWrapper_SoDelayQueueSensor::setPriority(SoDelayQueueSensor* theWrappedObject, unsigned int  pri)
{
  ( theWrappedObject->setPriority(pri));
}



void PythonQtWrapper_SoFieldSensor::attach(SoFieldSensor* theWrappedObject, SoField*  field)
{
  ( theWrappedObject->attach(field));
}

void PythonQtWrapper_SoFieldSensor::detach(SoFieldSensor* theWrappedObject)
{
  ( theWrappedObject->detach());
}

SoField*  PythonQtWrapper_SoFieldSensor::getAttachedField(SoFieldSensor* theWrappedObject) const
{
  return ( theWrappedObject->getAttachedField());
}





void PythonQtWrapper_SoNodeSensor::attach(SoNodeSensor* theWrappedObject, SoNode*  node)
{
  ( theWrappedObject->attach(node));
}

void PythonQtWrapper_SoNodeSensor::detach(SoNodeSensor* theWrappedObject)
{
  ( theWrappedObject->detach());
}

SoNode*  PythonQtWrapper_SoNodeSensor::getAttachedNode(SoNodeSensor* theWrappedObject) const
{
  return ( theWrappedObject->getAttachedNode());
}



void PythonQtWrapper_SoPathSensor::attach(SoPathSensor* theWrappedObject, SoPath*  path)
{
  ( theWrappedObject->attach(path));
}

void PythonQtWrapper_SoPathSensor::detach(SoPathSensor* theWrappedObject)
{
  ( theWrappedObject->detach());
}

SoPath*  PythonQtWrapper_SoPathSensor::getAttachedPath(SoPathSensor* theWrappedObject) const
{
  return ( theWrappedObject->getAttachedPath());
}



SoSensor*  PythonQtWrapper_SoSensor::getNextInQueue(SoSensor* theWrappedObject) const
{
  return ( theWrappedObject->getNextInQueue());
}

bool  PythonQtWrapper_SoSensor::isBefore(SoSensor* theWrappedObject, const SoSensor*  s) const
{
  return ( theWrappedObject->isBefore(s));
}

bool  PythonQtWrapper_SoSensor::isScheduled(SoSensor* theWrappedObject) const
{
  return ( theWrappedObject->isScheduled());
}

void PythonQtWrapper_SoSensor::schedule(SoSensor* theWrappedObject)
{
  ( theWrappedObject->schedule());
}

void PythonQtWrapper_SoSensor::setNextInQueue(SoSensor* theWrappedObject, SoSensor*  next)
{
  ( theWrappedObject->setNextInQueue(next));
}

void PythonQtWrapper_SoSensor::trigger(SoSensor* theWrappedObject)
{
  ( theWrappedObject->trigger());
}

void PythonQtWrapper_SoSensor::unschedule(SoSensor* theWrappedObject)
{
  ( theWrappedObject->unschedule());
}



const SbTime*  PythonQtWrapper_SoTimerQueueSensor::getTriggerTime(SoTimerQueueSensor* theWrappedObject) const
{
  return &( theWrappedObject->getTriggerTime());
}



const SbTime*  PythonQtWrapper_SoTimerSensor::getBaseTime(SoTimerSensor* theWrappedObject) const
{
  return &( theWrappedObject->getBaseTime());
}

const SbTime*  PythonQtWrapper_SoTimerSensor::getInterval(SoTimerSensor* theWrappedObject) const
{
  return &( theWrappedObject->getInterval());
}

void PythonQtWrapper_SoTimerSensor::reschedule(SoTimerSensor* theWrappedObject, const SbTime&  arg__1)
{
  ( theWrappedObject->reschedule(arg__1));
}

void PythonQtWrapper_SoTimerSensor::setBaseTime(SoTimerSensor* theWrappedObject, const SbTime&  base)
{
  ( theWrappedObject->setBaseTime(base));
}

void PythonQtWrapper_SoTimerSensor::setInterval(SoTimerSensor* theWrappedObject, const SbTime&  intvl)
{
  ( theWrappedObject->setInterval(intvl));
}


