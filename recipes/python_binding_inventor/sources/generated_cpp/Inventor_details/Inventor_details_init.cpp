/*************************************************************************************
**
** Copyright 2022, MeVis Medical Solutions AG
**
** GNU LESSER GENERAL PUBLIC LICENSE Version 2.1, February 1999
**
**************************************************************************************/
#include <PythonQt.h>
#include <PythonQtConversion.h>
#include "Inventor_details0.h"



void PythonQt_init_InventorDetails(PyObject* module) {
PythonQt::priv()->registerCPPClass("SoConeDetail", "SoDetail", "InventorDetails", PythonQtCreateObject<PythonQtWrapper_SoConeDetail>, PythonQtSetInstanceWrapperOnShell<PythonQtShell_SoConeDetail>, module, 0);
PythonQt::priv()->registerCPPClass("SoCubeDetail", "SoDetail", "InventorDetails", PythonQtCreateObject<PythonQtWrapper_SoCubeDetail>, PythonQtSetInstanceWrapperOnShell<PythonQtShell_SoCubeDetail>, module, 0);
PythonQt::priv()->registerCPPClass("SoCylinderDetail", "SoDetail", "InventorDetails", PythonQtCreateObject<PythonQtWrapper_SoCylinderDetail>, PythonQtSetInstanceWrapperOnShell<PythonQtShell_SoCylinderDetail>, module, 0);
PythonQt::priv()->registerCPPClass("SoDetail", "", "InventorDetails", PythonQtCreateObject<PythonQtWrapper_SoDetail>, nullptr, module, 0);
PythonQt::priv()->registerCPPClass("SoFaceDetail", "SoDetail", "InventorDetails", PythonQtCreateObject<PythonQtWrapper_SoFaceDetail>, PythonQtSetInstanceWrapperOnShell<PythonQtShell_SoFaceDetail>, module, 0);
PythonQt::priv()->registerCPPClass("SoLineDetail", "SoDetail", "InventorDetails", PythonQtCreateObject<PythonQtWrapper_SoLineDetail>, PythonQtSetInstanceWrapperOnShell<PythonQtShell_SoLineDetail>, module, 0);
PythonQt::priv()->registerCPPClass("SoPointDetail", "SoDetail", "InventorDetails", PythonQtCreateObject<PythonQtWrapper_SoPointDetail>, PythonQtSetInstanceWrapperOnShell<PythonQtShell_SoPointDetail>, module, 0);
PythonQt::priv()->registerCPPClass("SoTextDetail", "SoDetail", "InventorDetails", PythonQtCreateObject<PythonQtWrapper_SoTextDetail>, PythonQtSetInstanceWrapperOnShell<PythonQtShell_SoTextDetail>, module, 0);


}
