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
#include <Inventor/SbTime.h>
#include <Inventor/SoPath.h>
#include <Inventor/fields/SoField.h>
#include <Inventor/nodes/SoNode.h>
#include <Inventor/sensors/SoAlarmSensor.h>
#include <Inventor/sensors/SoDataSensor.h>
#include <Inventor/sensors/SoDelayQueueSensor.h>
#include <Inventor/sensors/SoFieldSensor.h>
#include <Inventor/sensors/SoIdleSensor.h>
#include <Inventor/sensors/SoNodeSensor.h>
#include <Inventor/sensors/SoPathSensor.h>
#include <Inventor/sensors/SoSensor.h>
#include <Inventor/sensors/SoTimerQueueSensor.h>
#include <Inventor/sensors/SoTimerSensor.h>



class PythonQtWrapper_SoAlarmSensor : public QObject
{ Q_OBJECT
public:
public slots:
void delete_SoAlarmSensor(SoAlarmSensor* obj) { delete obj; }
   const SbTime*  getTime(SoAlarmSensor* theWrappedObject) const;
   void setTime(SoAlarmSensor* theWrappedObject, const SbTime&  absTime);
   void setTimeFromNow(SoAlarmSensor* theWrappedObject, const SbTime&  relTime);
};





class PythonQtWrapper_SoDataSensor : public QObject
{ Q_OBJECT
public:
public slots:
void delete_SoDataSensor(SoDataSensor* obj) { delete obj; }
   void dyingReference(SoDataSensor* theWrappedObject);
   SoField*  getTriggerField(SoDataSensor* theWrappedObject) const;
   SoNode*  getTriggerNode(SoDataSensor* theWrappedObject) const;
   SoPath*  getTriggerPath(SoDataSensor* theWrappedObject) const;
   bool  getTriggerPathFlag(SoDataSensor* theWrappedObject) const;
   void setTriggerPathFlag(SoDataSensor* theWrappedObject, bool  flag);
};





class PythonQtWrapper_SoDelayQueueSensor : public QObject
{ Q_OBJECT
public:
public slots:
void delete_SoDelayQueueSensor(SoDelayQueueSensor* obj) { delete obj; }
   unsigned int  getCounter(SoDelayQueueSensor* theWrappedObject) const;
   unsigned int  static_SoDelayQueueSensor_getDefaultPriority();
   unsigned int  getPriority(SoDelayQueueSensor* theWrappedObject) const;
   bool  isIdleOnly(SoDelayQueueSensor* theWrappedObject) const;
   void setCounter(SoDelayQueueSensor* theWrappedObject, unsigned int  c);
   void setPriority(SoDelayQueueSensor* theWrappedObject, unsigned int  pri);
};





class PythonQtWrapper_SoFieldSensor : public QObject
{ Q_OBJECT
public:
public slots:
void delete_SoFieldSensor(SoFieldSensor* obj) { delete obj; }
   void attach(SoFieldSensor* theWrappedObject, SoField*  field);
   SoField*  getAttachedField(SoFieldSensor* theWrappedObject) const;
};





class PythonQtWrapper_SoIdleSensor : public QObject
{ Q_OBJECT
public:
public slots:
void delete_SoIdleSensor(SoIdleSensor* obj) { delete obj; }
};





class PythonQtWrapper_SoNodeSensor : public QObject
{ Q_OBJECT
public:
public slots:
void delete_SoNodeSensor(SoNodeSensor* obj) { delete obj; }
   void attach(SoNodeSensor* theWrappedObject, SoNode*  node);
   SoNode*  getAttachedNode(SoNodeSensor* theWrappedObject) const;
};





class PythonQtWrapper_SoPathSensor : public QObject
{ Q_OBJECT
public:
public slots:
void delete_SoPathSensor(SoPathSensor* obj) { delete obj; }
   void attach(SoPathSensor* theWrappedObject, SoPath*  path);
   SoPath*  getAttachedPath(SoPathSensor* theWrappedObject) const;
};





class PythonQtWrapper_SoSensor : public QObject
{ Q_OBJECT
public:
public slots:
void delete_SoSensor(SoSensor* obj) { delete obj; }
   SoSensor*  getNextInQueue(SoSensor* theWrappedObject) const;
   bool  isBefore(SoSensor* theWrappedObject, const SoSensor*  s) const;
   bool  isScheduled(SoSensor* theWrappedObject) const;
   void schedule(SoSensor* theWrappedObject);
   void setNextInQueue(SoSensor* theWrappedObject, SoSensor*  next);
   void trigger(SoSensor* theWrappedObject);
   void unschedule(SoSensor* theWrappedObject);
};





class PythonQtWrapper_SoTimerQueueSensor : public QObject
{ Q_OBJECT
public:
public slots:
void delete_SoTimerQueueSensor(SoTimerQueueSensor* obj) { delete obj; }
   const SbTime*  getTriggerTime(SoTimerQueueSensor* theWrappedObject) const;
};





class PythonQtWrapper_SoTimerSensor : public QObject
{ Q_OBJECT
public:
public slots:
void delete_SoTimerSensor(SoTimerSensor* obj) { delete obj; }
   const SbTime*  getBaseTime(SoTimerSensor* theWrappedObject) const;
   const SbTime*  getInterval(SoTimerSensor* theWrappedObject) const;
   void reschedule(SoTimerSensor* theWrappedObject, const SbTime&  arg__1);
   void setBaseTime(SoTimerSensor* theWrappedObject, const SbTime&  base);
   void setInterval(SoTimerSensor* theWrappedObject, const SbTime&  intvl);
};


