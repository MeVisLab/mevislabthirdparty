/*************************************************************************************
**
** Copyright 2022, MeVis Medical Solutions AG
**
** GNU LESSER GENERAL PUBLIC LICENSE Version 2.1, February 1999
**
**************************************************************************************/
#include <PythonQt.h>
#include <PythonQtConversion.h>
#include "Inventor_actions0.h"



void PythonQt_init_InventorActions(PyObject* module) {
PythonQt::priv()->registerCPPClass("SoAction", "", "InventorActions", PythonQtCreateObject<PythonQtWrapper_SoAction>, nullptr, module, 0);
PythonQt::priv()->registerCPPClass("SoCallbackAction", "SoAction", "InventorActions", PythonQtCreateObject<PythonQtWrapper_SoCallbackAction>, PythonQtSetInstanceWrapperOnShell<PythonQtShell_SoCallbackAction>, module, 0);
PythonQt::priv()->registerCPPClass("SoGLRenderAction", "SoAction", "InventorActions", PythonQtCreateObject<PythonQtWrapper_SoGLRenderAction>, PythonQtSetInstanceWrapperOnShell<PythonQtShell_SoGLRenderAction>, module, 0);
PythonQt::priv()->registerCPPClass("SoGetBoundingBoxAction", "SoAction", "InventorActions", PythonQtCreateObject<PythonQtWrapper_SoGetBoundingBoxAction>, PythonQtSetInstanceWrapperOnShell<PythonQtShell_SoGetBoundingBoxAction>, module, 0);
PythonQt::priv()->registerCPPClass("SoGetMatrixAction", "SoAction", "InventorActions", PythonQtCreateObject<PythonQtWrapper_SoGetMatrixAction>, PythonQtSetInstanceWrapperOnShell<PythonQtShell_SoGetMatrixAction>, module, 0);
PythonQt::priv()->registerCPPClass("SoHandleEventAction", "SoAction", "InventorActions", PythonQtCreateObject<PythonQtWrapper_SoHandleEventAction>, PythonQtSetInstanceWrapperOnShell<PythonQtShell_SoHandleEventAction>, module, 0);
PythonQt::priv()->registerCPPClass("SoPickAction", "SoAction", "InventorActions", PythonQtCreateObject<PythonQtWrapper_SoPickAction>, PythonQtSetInstanceWrapperOnShell<PythonQtShell_SoPickAction>, module, 0);
PythonQt::priv()->registerCPPClass("SoRayPickAction", "SoPickAction", "InventorActions", PythonQtCreateObject<PythonQtWrapper_SoRayPickAction>, PythonQtSetInstanceWrapperOnShell<PythonQtShell_SoRayPickAction>, module, 0);
PythonQt::priv()->registerCPPClass("SoSearchAction", "SoAction", "InventorActions", PythonQtCreateObject<PythonQtWrapper_SoSearchAction>, PythonQtSetInstanceWrapperOnShell<PythonQtShell_SoSearchAction>, module, 0);
PythonQt::priv()->registerCPPClass("SoWriteAction", "SoAction", "InventorActions", PythonQtCreateObject<PythonQtWrapper_SoWriteAction>, PythonQtSetInstanceWrapperOnShell<PythonQtShell_SoWriteAction>, module, 0);


}
