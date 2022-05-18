/*************************************************************************************
**
** Copyright 2022, MeVis Medical Solutions AG
**
** GNU LESSER GENERAL PUBLIC LICENSE Version 2.1, February 1999
**
**************************************************************************************/
#include <PythonQt.h>
#include <PythonQtConversion.h>
#include "Inventor_engines0.h"
#include "Inventor_engines1.h"



void PythonQt_init_InventorEngines(PyObject* module) {
PythonQt::priv()->registerCPPClass("SoBoolOperation", "SoEngine", "InventorEngines", PythonQtCreateObject<PythonQtWrapper_SoBoolOperation>, nullptr, module, 0);
PythonQt::priv()->registerCPPClass("SoCalculator", "SoEngine", "InventorEngines", PythonQtCreateObject<PythonQtWrapper_SoCalculator>, nullptr, module, 0);
PythonQt::priv()->registerCPPClass("SoComposeMatrix", "SoEngine", "InventorEngines", PythonQtCreateObject<PythonQtWrapper_SoComposeMatrix>, nullptr, module, 0);
PythonQt::priv()->registerCPPClass("SoComposeRotation", "SoEngine", "InventorEngines", PythonQtCreateObject<PythonQtWrapper_SoComposeRotation>, nullptr, module, 0);
PythonQt::priv()->registerCPPClass("SoComposeRotationFromTo", "SoEngine", "InventorEngines", PythonQtCreateObject<PythonQtWrapper_SoComposeRotationFromTo>, nullptr, module, 0);
PythonQt::priv()->registerCPPClass("SoComposeVec2f", "SoEngine", "InventorEngines", PythonQtCreateObject<PythonQtWrapper_SoComposeVec2f>, nullptr, module, 0);
PythonQt::priv()->registerCPPClass("SoComposeVec3f", "SoEngine", "InventorEngines", PythonQtCreateObject<PythonQtWrapper_SoComposeVec3f>, nullptr, module, 0);
PythonQt::priv()->registerCPPClass("SoComposeVec4f", "SoEngine", "InventorEngines", PythonQtCreateObject<PythonQtWrapper_SoComposeVec4f>, nullptr, module, 0);
PythonQt::priv()->registerCPPClass("SoComputeBoundingBox", "SoEngine", "InventorEngines", PythonQtCreateObject<PythonQtWrapper_SoComputeBoundingBox>, nullptr, module, 0);
PythonQt::priv()->registerCPPClass("SoCounter", "SoEngine", "InventorEngines", PythonQtCreateObject<PythonQtWrapper_SoCounter>, nullptr, module, 0);
PythonQt::priv()->registerCPPClass("SoDecomposeMatrix", "SoEngine", "InventorEngines", PythonQtCreateObject<PythonQtWrapper_SoDecomposeMatrix>, nullptr, module, 0);
PythonQt::priv()->registerCPPClass("SoDecomposeRotation", "SoEngine", "InventorEngines", PythonQtCreateObject<PythonQtWrapper_SoDecomposeRotation>, nullptr, module, 0);
PythonQt::priv()->registerCPPClass("SoDecomposeVec2f", "SoEngine", "InventorEngines", PythonQtCreateObject<PythonQtWrapper_SoDecomposeVec2f>, nullptr, module, 0);
PythonQt::priv()->registerCPPClass("SoDecomposeVec3f", "SoEngine", "InventorEngines", PythonQtCreateObject<PythonQtWrapper_SoDecomposeVec3f>, nullptr, module, 0);
PythonQt::priv()->registerCPPClass("SoDecomposeVec4f", "SoEngine", "InventorEngines", PythonQtCreateObject<PythonQtWrapper_SoDecomposeVec4f>, nullptr, module, 0);
PythonQt::priv()->registerCPPClass("SoElapsedTime", "SoEngine", "InventorEngines", PythonQtCreateObject<PythonQtWrapper_SoElapsedTime>, nullptr, module, 0);
PythonQt::priv()->registerCPPClass("SoEngine", "SoFieldContainer", "InventorEngines", PythonQtCreateObject<PythonQtWrapper_SoEngine>, nullptr, module, 0);
PythonQt::priv()->registerCPPClass("SoEngineOutput", "", "InventorEngines", PythonQtCreateObject<PythonQtWrapper_SoEngineOutput>, nullptr, module, 0);
PythonQt::priv()->registerCPPClass("SoFieldConverter", "SoEngine", "InventorEngines", PythonQtCreateObject<PythonQtWrapper_SoFieldConverter>, nullptr, module, 0);
PythonQt::priv()->registerCPPClass("SoGate", "SoEngine", "InventorEngines", PythonQtCreateObject<PythonQtWrapper_SoGate>, nullptr, module, 0);
PythonQt::priv()->registerCPPClass("SoInterpolate", "SoEngine", "InventorEngines", PythonQtCreateObject<PythonQtWrapper_SoInterpolate>, nullptr, module, 0);
PythonQt::priv()->registerCPPClass("SoInterpolateFloat", "SoInterpolate", "InventorEngines", PythonQtCreateObject<PythonQtWrapper_SoInterpolateFloat>, nullptr, module, 0);
PythonQt::priv()->registerCPPClass("SoInterpolateRotation", "SoInterpolate", "InventorEngines", PythonQtCreateObject<PythonQtWrapper_SoInterpolateRotation>, nullptr, module, 0);
PythonQt::priv()->registerCPPClass("SoInterpolateVec2f", "SoInterpolate", "InventorEngines", PythonQtCreateObject<PythonQtWrapper_SoInterpolateVec2f>, nullptr, module, 0);
PythonQt::priv()->registerCPPClass("SoInterpolateVec3f", "SoInterpolate", "InventorEngines", PythonQtCreateObject<PythonQtWrapper_SoInterpolateVec3f>, nullptr, module, 0);
PythonQt::priv()->registerCPPClass("SoInterpolateVec4f", "SoInterpolate", "InventorEngines", PythonQtCreateObject<PythonQtWrapper_SoInterpolateVec4f>, nullptr, module, 0);
PythonQt::priv()->registerCPPClass("SoOnOff", "SoEngine", "InventorEngines", PythonQtCreateObject<PythonQtWrapper_SoOnOff>, nullptr, module, 0);
PythonQt::priv()->registerCPPClass("SoOneShot", "SoEngine", "InventorEngines", PythonQtCreateObject<PythonQtWrapper_SoOneShot>, nullptr, module, 0);
PythonQt::priv()->registerCPPClass("SoSelectOne", "SoEngine", "InventorEngines", PythonQtCreateObject<PythonQtWrapper_SoSelectOne>, nullptr, module, 0);
PythonQt::priv()->registerCPPClass("SoTimeCounter", "SoEngine", "InventorEngines", PythonQtCreateObject<PythonQtWrapper_SoTimeCounter>, nullptr, module, 0);
PythonQt::priv()->registerCPPClass("SoTransformVec3f", "SoEngine", "InventorEngines", PythonQtCreateObject<PythonQtWrapper_SoTransformVec3f>, nullptr, module, 0);
PythonQt::priv()->registerCPPClass("SoTriggerAny", "SoEngine", "InventorEngines", PythonQtCreateObject<PythonQtWrapper_SoTriggerAny>, nullptr, module, 0);


}
