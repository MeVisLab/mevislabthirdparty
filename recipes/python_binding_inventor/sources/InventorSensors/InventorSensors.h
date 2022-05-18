/*************************************************************************************
**
** Copyright 2014, MeVis Medical Solutions AG
**
** GNU LESSER GENERAL PUBLIC LICENSE Version 2.1, February 1999
**
**************************************************************************************/

#ifndef _INVENTORSENSORS_H
#define _INVENTORSENSORS_H

#include <PythonQt.h>

#include <QObject>
#include <Inventor/sensors/SoSensors.h>

class InventorSensorsDecorator : public QObject
{
  Q_OBJECT

public slots:
  SoFieldSensor* new_SoFieldSensor(PyObject* callable);
  SoNodeSensor* new_SoNodeSensor(PyObject* callable);
  SoPathSensor* new_SoPathSensor(PyObject* callable);
  SoIdleSensor* new_SoIdleSensor(PyObject* callable);
  SoOneShotSensor* new_SoOneShotSensor(PyObject* callable);
  SoAlarmSensor* new_SoAlarmSensor(PyObject* callable);
  SoTimerSensor* new_SoTimerSensor(PyObject* callable);
public:
  static void PySoSensorCB(void *data, SoSensor *sensor, const QByteArray& type);
};

#define PySensor(TYPE) \
class Py##TYPE : public TYPE \
{ \
public: \
  Py##TYPE(PyObject* callable){ \
    _callable = callable; \
    setFunction(sensorCB); \
    setData(callable); \
  } \
  ~Py##TYPE(){ \
    PYTHONQT_GIL_SCOPE; \
    _callable = NULL; \
  } \
  static void sensorCB(void *data, SoSensor *sensor) \
  { \
    static const QByteArray type(#TYPE); \
    InventorSensorsDecorator::PySoSensorCB(data,sensor, type); \
  } \
 \
protected:\
  PythonQtObjectPtr _callable;\
};\

PySensor(SoFieldSensor)
PySensor(SoNodeSensor)
PySensor(SoPathSensor)
PySensor(SoTimerSensor)
PySensor(SoAlarmSensor)
PySensor(SoIdleSensor)
PySensor(SoOneShotSensor)

#endif
