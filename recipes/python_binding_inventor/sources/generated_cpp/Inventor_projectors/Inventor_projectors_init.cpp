/*************************************************************************************
**
** Copyright 2022, MeVis Medical Solutions AG
**
** GNU LESSER GENERAL PUBLIC LICENSE Version 2.1, February 1999
**
**************************************************************************************/
#include <PythonQt.h>
#include <PythonQtConversion.h>
#include "Inventor_projectors0.h"



void PythonQt_init_InventorProjectors(PyObject* module) {
PythonQt::priv()->registerCPPClass("SbCylinderPlaneProjector", "SbCylinderSectionProjector", "InventorProjectors", PythonQtCreateObject<PythonQtWrapper_SbCylinderPlaneProjector>, PythonQtSetInstanceWrapperOnShell<PythonQtShell_SbCylinderPlaneProjector>, module, 0);
PythonQt::priv()->registerCPPClass("SbCylinderProjector", "SbProjector", "InventorProjectors", PythonQtCreateObject<PythonQtWrapper_SbCylinderProjector>, PythonQtSetInstanceWrapperOnShell<PythonQtShell_SbCylinderProjector>, module, 0);
PythonQt::priv()->registerCPPClass("SbCylinderSectionProjector", "SbCylinderProjector", "InventorProjectors", PythonQtCreateObject<PythonQtWrapper_SbCylinderSectionProjector>, PythonQtSetInstanceWrapperOnShell<PythonQtShell_SbCylinderSectionProjector>, module, 0);
PythonQt::priv()->registerCPPClass("SbCylinderSheetProjector", "SbCylinderProjector", "InventorProjectors", PythonQtCreateObject<PythonQtWrapper_SbCylinderSheetProjector>, PythonQtSetInstanceWrapperOnShell<PythonQtShell_SbCylinderSheetProjector>, module, 0);
PythonQt::priv()->registerCPPClass("SbLineProjector", "SbProjector", "InventorProjectors", PythonQtCreateObject<PythonQtWrapper_SbLineProjector>, PythonQtSetInstanceWrapperOnShell<PythonQtShell_SbLineProjector>, module, 0);
PythonQt::priv()->registerCPPClass("SbPlaneProjector", "SbProjector", "InventorProjectors", PythonQtCreateObject<PythonQtWrapper_SbPlaneProjector>, PythonQtSetInstanceWrapperOnShell<PythonQtShell_SbPlaneProjector>, module, 0);
PythonQt::priv()->registerCPPClass("SbProjector", "", "InventorProjectors", PythonQtCreateObject<PythonQtWrapper_SbProjector>, PythonQtSetInstanceWrapperOnShell<PythonQtShell_SbProjector>, module, 0);
PythonQt::priv()->registerCPPClass("SbSpherePlaneProjector", "SbSphereSectionProjector", "InventorProjectors", PythonQtCreateObject<PythonQtWrapper_SbSpherePlaneProjector>, PythonQtSetInstanceWrapperOnShell<PythonQtShell_SbSpherePlaneProjector>, module, 0);
PythonQt::priv()->registerCPPClass("SbSphereProjector", "SbProjector", "InventorProjectors", PythonQtCreateObject<PythonQtWrapper_SbSphereProjector>, PythonQtSetInstanceWrapperOnShell<PythonQtShell_SbSphereProjector>, module, 0);
PythonQt::priv()->registerCPPClass("SbSphereSectionProjector", "SbSphereProjector", "InventorProjectors", PythonQtCreateObject<PythonQtWrapper_SbSphereSectionProjector>, PythonQtSetInstanceWrapperOnShell<PythonQtShell_SbSphereSectionProjector>, module, 0);
PythonQt::priv()->registerCPPClass("SbSphereSheetProjector", "SbSphereProjector", "InventorProjectors", PythonQtCreateObject<PythonQtWrapper_SbSphereSheetProjector>, PythonQtSetInstanceWrapperOnShell<PythonQtShell_SbSphereSheetProjector>, module, 0);


}
