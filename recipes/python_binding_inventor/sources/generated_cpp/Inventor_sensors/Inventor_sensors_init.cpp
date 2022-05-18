/*************************************************************************************
**
** Copyright 2022, MeVis Medical Solutions AG
**
** GNU LESSER GENERAL PUBLIC LICENSE Version 2.1, February 1999
**
**************************************************************************************/
#include <PythonQt.h>
#include <PythonQtConversion.h>
#include "Inventor_sensors0.h"



void PythonQt_init_InventorSensors(PyObject* module) {
PythonQt::priv()->registerCPPClass("SoAlarmSensor", "SoTimerQueueSensor", "InventorSensors", PythonQtCreateObject<PythonQtWrapper_SoAlarmSensor>, nullptr, module, 0);
PythonQt::priv()->registerCPPClass("SoDataSensor", "SoDelayQueueSensor", "InventorSensors", PythonQtCreateObject<PythonQtWrapper_SoDataSensor>, nullptr, module, 0);
PythonQt::priv()->registerCPPClass("SoDelayQueueSensor", "SoSensor", "InventorSensors", PythonQtCreateObject<PythonQtWrapper_SoDelayQueueSensor>, nullptr, module, 0);
PythonQt::priv()->registerCPPClass("SoFieldSensor", "SoDataSensor", "InventorSensors", PythonQtCreateObject<PythonQtWrapper_SoFieldSensor>, nullptr, module, 0);
PythonQt::priv()->registerCPPClass("SoIdleSensor", "SoDelayQueueSensor", "InventorSensors", PythonQtCreateObject<PythonQtWrapper_SoIdleSensor>, nullptr, module, 0);
PythonQt::priv()->registerCPPClass("SoNodeSensor", "SoDataSensor", "InventorSensors", PythonQtCreateObject<PythonQtWrapper_SoNodeSensor>, nullptr, module, 0);
PythonQt::priv()->registerCPPClass("SoPathSensor", "SoDataSensor", "InventorSensors", PythonQtCreateObject<PythonQtWrapper_SoPathSensor>, nullptr, module, 0);
PythonQt::priv()->registerCPPClass("SoSensor", "", "InventorSensors", PythonQtCreateObject<PythonQtWrapper_SoSensor>, nullptr, module, 0);
PythonQt::priv()->registerCPPClass("SoTimerQueueSensor", "SoSensor", "InventorSensors", PythonQtCreateObject<PythonQtWrapper_SoTimerQueueSensor>, nullptr, module, 0);
PythonQt::priv()->registerCPPClass("SoTimerSensor", "SoTimerQueueSensor", "InventorSensors", PythonQtCreateObject<PythonQtWrapper_SoTimerSensor>, nullptr, module, 0);


}
