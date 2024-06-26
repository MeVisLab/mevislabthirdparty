/*************************************************************************************
**
** Copyright 2014, MeVis Medical Solutions AG
**
** GNU LESSER GENERAL PUBLIC LICENSE Version 2.1, February 1999
**
**************************************************************************************/

#include "PythonQt.h"
#include "PythonQtConversion.h"
#include "InventorSensors.h"

static PyMethodDef NoMethods[] = {
    {nullptr, nullptr, 0, nullptr}        /* Sentinel */
};

void PythonQt_init_InventorSensors(PyObject*);


static PyModuleDef sensorsModuleDef = {
  PyModuleDef_HEAD_INIT,
  "sensors",
  nullptr,
  -1,
  NoMethods,
  nullptr,
  nullptr,
  nullptr,
  nullptr
};

#define PyInitModFunc(name) PyInit_##name(void)
  #define PyModuleInit(name) PyModule_Create(&sensorsModuleDef)

#ifdef UNIX
PyMODINIT_FUNC
PyInitModFunc(sensors) ML_LIBRARY_EXPORT_ATTRIBUTE ;
#endif

PyMODINIT_FUNC
PyInitModFunc(sensors)
{
  PyObject* nodes = PyImport_ImportModule("Inventor.nodes");
  Py_XDECREF(nodes);

  PyObject* module = PyModuleInit("sensors");
  PythonQt_init_InventorSensors(module);

  PythonQt::self()->addDecorators(new InventorSensorsDecorator());

  return module;
}



SoFieldSensor* InventorSensorsDecorator::new_SoFieldSensor( PyObject* callable )
{
  return new PySoFieldSensor(callable);
}

SoNodeSensor* InventorSensorsDecorator::new_SoNodeSensor( PyObject* callable )
{
  return new PySoNodeSensor(callable);
}

SoPathSensor* InventorSensorsDecorator::new_SoPathSensor( PyObject* callable )
{
  return new PySoPathSensor(callable);
}

SoIdleSensor* InventorSensorsDecorator::new_SoIdleSensor( PyObject* callable )
{
  return new PySoIdleSensor(callable);
}

SoOneShotSensor* InventorSensorsDecorator::new_SoOneShotSensor( PyObject* callable )
{
  return new PySoOneShotSensor(callable);
}

SoAlarmSensor* InventorSensorsDecorator::new_SoAlarmSensor( PyObject* callable )
{
  return new PySoAlarmSensor(callable);
}

SoTimerSensor* InventorSensorsDecorator::new_SoTimerSensor( PyObject* callable )
{
  return new PySoTimerSensor(callable);
}

void InventorSensorsDecorator::PySoSensorCB(void *data, SoSensor *sensor, const QByteArray& type)
{
  PYTHONQT_GIL_SCOPE;
  PyObject* pySensor = PythonQt::priv()->wrapPtr(sensor, type);
  PyObject* callable = (PyObject*)data;
  PyObject* args = PyTuple_New(1);
  // steals reference, so we don't need to decref pySensor:
  PyTuple_SET_ITEM(args, 0, pySensor);
  PyObject* result = PyObject_CallObject(callable, args);
  if (result == nullptr) {
    PythonQt::self()->handleError();
  }
  Py_XDECREF(result);
}

