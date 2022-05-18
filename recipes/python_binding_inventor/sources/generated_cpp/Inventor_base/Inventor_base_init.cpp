/*************************************************************************************
**
** Copyright 2022, MeVis Medical Solutions AG
**
** GNU LESSER GENERAL PUBLIC LICENSE Version 2.1, February 1999
**
**************************************************************************************/
#include <PythonQt.h>
#include <PythonQtConversion.h>
#include "Inventor_base0.h"
#include "Inventor_base1.h"



void PythonQt_init_InventorBase(PyObject* module) {
PythonQt::priv()->registerCPPClass("SbBox2f", "", "InventorBase", PythonQtCreateObject<PythonQtWrapper_SbBox2f>, nullptr, module, PythonQt::Type_NonZero|PythonQt::Type_RichCompare);
PythonQt::priv()->registerCPPClass("SbBox2s", "", "InventorBase", PythonQtCreateObject<PythonQtWrapper_SbBox2s>, nullptr, module, PythonQt::Type_RichCompare);
PythonQt::priv()->registerCPPClass("SbBox3d", "", "InventorBase", PythonQtCreateObject<PythonQtWrapper_SbBox3d>, nullptr, module, PythonQt::Type_NonZero|PythonQt::Type_RichCompare);
PythonQt::priv()->registerCPPClass("SbBox3f", "", "InventorBase", PythonQtCreateObject<PythonQtWrapper_SbBox3f>, nullptr, module, PythonQt::Type_NonZero|PythonQt::Type_RichCompare);
PythonQt::priv()->registerCPPClass("SbColor", "SbVec3f", "InventorBase", PythonQtCreateObject<PythonQtWrapper_SbColor>, nullptr, module, PythonQt::Type_InplaceAdd|PythonQt::Type_InplaceDivide|PythonQt::Type_InplaceMultiply|PythonQt::Type_InplaceSubtract|PythonQt::Type_Subtract);
PythonQt::priv()->registerCPPClass("SbCylinder", "", "InventorBase", PythonQtCreateObject<PythonQtWrapper_SbCylinder>, nullptr, module, 0);
PythonQt::priv()->registerCPPClass("SbCylinderd", "", "InventorBase", PythonQtCreateObject<PythonQtWrapper_SbCylinderd>, nullptr, module, 0);
PythonQt::priv()->registerCPPClass("SbLine", "", "InventorBase", PythonQtCreateObject<PythonQtWrapper_SbLine>, nullptr, module, 0);
PythonQt::priv()->registerCPPClass("SbLined", "", "InventorBase", PythonQtCreateObject<PythonQtWrapper_SbLined>, nullptr, module, 0);
PythonQt::priv()->registerCPPClass("SbMatrix", "", "InventorBase", PythonQtCreateObject<PythonQtWrapper_SbMatrix>, nullptr, module, PythonQt::Type_InplaceMultiply|PythonQt::Type_MappingGetItem|PythonQt::Type_MappingSetItem|PythonQt::Type_Multiply|PythonQt::Type_RichCompare);
PythonQt::priv()->registerCPPClass("SbMatrixd", "", "InventorBase", PythonQtCreateObject<PythonQtWrapper_SbMatrixd>, nullptr, module, PythonQt::Type_InplaceMultiply|PythonQt::Type_MappingGetItem|PythonQt::Type_MappingSetItem|PythonQt::Type_Multiply|PythonQt::Type_RichCompare);
PythonQt::priv()->registerCPPClass("SbName", "", "InventorBase", PythonQtCreateObject<PythonQtWrapper_SbName>, nullptr, module, 0);
PythonQt::priv()->registerCPPClass("SbPlane", "", "InventorBase", PythonQtCreateObject<PythonQtWrapper_SbPlane>, nullptr, module, PythonQt::Type_RichCompare);
PythonQt::priv()->registerCPPClass("SbPlaned", "", "InventorBase", PythonQtCreateObject<PythonQtWrapper_SbPlaned>, nullptr, module, PythonQt::Type_RichCompare);
PythonQt::priv()->registerCPPClass("SbRotation", "", "InventorBase", PythonQtCreateObject<PythonQtWrapper_SbRotation>, nullptr, module, PythonQt::Type_InplaceMultiply|PythonQt::Type_Multiply|PythonQt::Type_RichCompare);
PythonQt::priv()->registerCPPClass("SbRotationd", "", "InventorBase", PythonQtCreateObject<PythonQtWrapper_SbRotationd>, nullptr, module, PythonQt::Type_InplaceMultiply|PythonQt::Type_Multiply|PythonQt::Type_RichCompare);
PythonQt::priv()->registerCPPClass("SbSphere", "", "InventorBase", PythonQtCreateObject<PythonQtWrapper_SbSphere>, nullptr, module, 0);
PythonQt::priv()->registerCPPClass("SbSphered", "", "InventorBase", PythonQtCreateObject<PythonQtWrapper_SbSphered>, nullptr, module, 0);
PythonQt::priv()->registerCPPClass("SbString", "", "InventorBase", PythonQtCreateObject<PythonQtWrapper_SbString>, nullptr, module, PythonQt::Type_InplaceAdd);
PythonQt::priv()->registerCPPClass("SbTime", "", "InventorBase", PythonQtCreateObject<PythonQtWrapper_SbTime>, nullptr, module, PythonQt::Type_Add|PythonQt::Type_Divide|PythonQt::Type_InplaceAdd|PythonQt::Type_InplaceDivide|PythonQt::Type_InplaceMultiply|PythonQt::Type_InplaceSubtract|PythonQt::Type_Mod|PythonQt::Type_Multiply|PythonQt::Type_RichCompare|PythonQt::Type_Subtract);
PythonQt::priv()->registerCPPClass("SbVec2d", "", "InventorBase", PythonQtCreateObject<PythonQtWrapper_SbVec2d>, PythonQtSetInstanceWrapperOnShell<PythonQtShell_SbVec2d>, module, PythonQt::Type_Add|PythonQt::Type_Divide|PythonQt::Type_InplaceAdd|PythonQt::Type_InplaceDivide|PythonQt::Type_InplaceMultiply|PythonQt::Type_InplaceSubtract|PythonQt::Type_Length|PythonQt::Type_MappingGetItem|PythonQt::Type_MappingSetItem|PythonQt::Type_Multiply|PythonQt::Type_RichCompare|PythonQt::Type_Subtract);
PythonQt::priv()->registerCPPClass("SbVec2f", "", "InventorBase", PythonQtCreateObject<PythonQtWrapper_SbVec2f>, PythonQtSetInstanceWrapperOnShell<PythonQtShell_SbVec2f>, module, PythonQt::Type_Add|PythonQt::Type_Divide|PythonQt::Type_InplaceAdd|PythonQt::Type_InplaceDivide|PythonQt::Type_InplaceMultiply|PythonQt::Type_InplaceSubtract|PythonQt::Type_Length|PythonQt::Type_MappingGetItem|PythonQt::Type_MappingSetItem|PythonQt::Type_Multiply|PythonQt::Type_RichCompare|PythonQt::Type_Subtract);
PythonQt::priv()->registerCPPClass("SbVec2s", "", "InventorBase", PythonQtCreateObject<PythonQtWrapper_SbVec2s>, PythonQtSetInstanceWrapperOnShell<PythonQtShell_SbVec2s>, module, PythonQt::Type_Add|PythonQt::Type_Divide|PythonQt::Type_InplaceAdd|PythonQt::Type_InplaceDivide|PythonQt::Type_InplaceMultiply|PythonQt::Type_InplaceSubtract|PythonQt::Type_Length|PythonQt::Type_MappingGetItem|PythonQt::Type_MappingSetItem|PythonQt::Type_Multiply|PythonQt::Type_RichCompare|PythonQt::Type_Subtract);
PythonQt::priv()->registerCPPClass("SbVec3d", "", "InventorBase", PythonQtCreateObject<PythonQtWrapper_SbVec3d>, PythonQtSetInstanceWrapperOnShell<PythonQtShell_SbVec3d>, module, PythonQt::Type_Add|PythonQt::Type_Divide|PythonQt::Type_InplaceAdd|PythonQt::Type_InplaceDivide|PythonQt::Type_InplaceMultiply|PythonQt::Type_InplaceSubtract|PythonQt::Type_Length|PythonQt::Type_MappingGetItem|PythonQt::Type_MappingSetItem|PythonQt::Type_Multiply|PythonQt::Type_RichCompare|PythonQt::Type_Subtract);
PythonQt::priv()->registerCPPClass("SbVec3f", "", "InventorBase", PythonQtCreateObject<PythonQtWrapper_SbVec3f>, PythonQtSetInstanceWrapperOnShell<PythonQtShell_SbVec3f>, module, PythonQt::Type_Add|PythonQt::Type_Divide|PythonQt::Type_InplaceAdd|PythonQt::Type_InplaceDivide|PythonQt::Type_InplaceMultiply|PythonQt::Type_InplaceSubtract|PythonQt::Type_Length|PythonQt::Type_MappingGetItem|PythonQt::Type_MappingSetItem|PythonQt::Type_Multiply|PythonQt::Type_RichCompare|PythonQt::Type_Subtract);
PythonQt::priv()->registerCPPClass("SbVec3s", "", "InventorBase", PythonQtCreateObject<PythonQtWrapper_SbVec3s>, PythonQtSetInstanceWrapperOnShell<PythonQtShell_SbVec3s>, module, PythonQt::Type_Add|PythonQt::Type_Divide|PythonQt::Type_InplaceAdd|PythonQt::Type_InplaceDivide|PythonQt::Type_InplaceMultiply|PythonQt::Type_InplaceSubtract|PythonQt::Type_Length|PythonQt::Type_MappingGetItem|PythonQt::Type_MappingSetItem|PythonQt::Type_Multiply|PythonQt::Type_RichCompare|PythonQt::Type_Subtract);
PythonQt::priv()->registerCPPClass("SbVec4d", "", "InventorBase", PythonQtCreateObject<PythonQtWrapper_SbVec4d>, PythonQtSetInstanceWrapperOnShell<PythonQtShell_SbVec4d>, module, PythonQt::Type_Add|PythonQt::Type_Divide|PythonQt::Type_InplaceAdd|PythonQt::Type_InplaceDivide|PythonQt::Type_InplaceMultiply|PythonQt::Type_InplaceSubtract|PythonQt::Type_Length|PythonQt::Type_MappingGetItem|PythonQt::Type_MappingSetItem|PythonQt::Type_Multiply|PythonQt::Type_RichCompare|PythonQt::Type_Subtract);
PythonQt::priv()->registerCPPClass("SbVec4f", "", "InventorBase", PythonQtCreateObject<PythonQtWrapper_SbVec4f>, PythonQtSetInstanceWrapperOnShell<PythonQtShell_SbVec4f>, module, PythonQt::Type_Add|PythonQt::Type_Divide|PythonQt::Type_InplaceAdd|PythonQt::Type_InplaceDivide|PythonQt::Type_InplaceMultiply|PythonQt::Type_InplaceSubtract|PythonQt::Type_Length|PythonQt::Type_MappingGetItem|PythonQt::Type_MappingSetItem|PythonQt::Type_Multiply|PythonQt::Type_RichCompare|PythonQt::Type_Subtract);
PythonQt::priv()->registerCPPClass("SbViewVolume", "", "InventorBase", PythonQtCreateObject<PythonQtWrapper_SbViewVolume>, PythonQtSetInstanceWrapperOnShell<PythonQtShell_SbViewVolume>, module, 0);
PythonQt::priv()->registerCPPClass("SbViewportRegion", "", "InventorBase", PythonQtCreateObject<PythonQtWrapper_SbViewportRegion>, nullptr, module, 0);
PythonQt::priv()->registerCPPClass("SbXfBox3d", "SbBox3d", "InventorBase", PythonQtCreateObject<PythonQtWrapper_SbXfBox3d>, nullptr, module, PythonQt::Type_NonZero|PythonQt::Type_RichCompare);
PythonQt::priv()->registerCPPClass("SbXfBox3f", "SbBox3f", "InventorBase", PythonQtCreateObject<PythonQtWrapper_SbXfBox3f>, nullptr, module, PythonQt::Type_NonZero|PythonQt::Type_RichCompare);
PythonQt::priv()->registerCPPClass("SoBase", "", "InventorBase", PythonQtCreateObject<PythonQtWrapper_SoBase>, nullptr, module, 0);
PythonQt::priv()->registerCPPClass("SoDB", "", "InventorBase", PythonQtCreateObject<PythonQtWrapper_SoDB>, PythonQtSetInstanceWrapperOnShell<PythonQtShell_SoDB>, module, 0);
PythonQt::priv()->registerCPPClass("SoInput", "", "InventorBase", PythonQtCreateObject<PythonQtWrapper_SoInput>, nullptr, module, 0);
PythonQt::priv()->registerCPPClass("SoOutput", "", "InventorBase", PythonQtCreateObject<PythonQtWrapper_SoOutput>, nullptr, module, 0);
PythonQt::priv()->registerCPPClass("SoPath", "SoBase", "InventorBase", PythonQtCreateObject<PythonQtWrapper_SoPath>, PythonQtSetInstanceWrapperOnShell<PythonQtShell_SoPath>, module, PythonQt::Type_RichCompare);
PythonQt::priv()->registerCPPClass("SoPickedPoint", "", "InventorBase", PythonQtCreateObject<PythonQtWrapper_SoPickedPoint>, nullptr, module, 0);
PythonQt::priv()->registerCPPClass("SoPrimitiveVertex", "", "InventorBase", PythonQtCreateObject<PythonQtWrapper_SoPrimitiveVertex>, nullptr, module, 0);
PythonQt::priv()->registerCPPClass("SoSceneManager", "", "InventorBase", PythonQtCreateObject<PythonQtWrapper_SoSceneManager>, PythonQtSetInstanceWrapperOnShell<PythonQtShell_SoSceneManager>, module, 0);
PythonQt::priv()->registerCPPClass("SoState", "", "InventorBase", PythonQtCreateObject<PythonQtWrapper_SoState>, nullptr, module, 0);
PythonQt::priv()->registerCPPClass("SoType", "", "InventorBase", PythonQtCreateObject<PythonQtWrapper_SoType>, PythonQtSetInstanceWrapperOnShell<PythonQtShell_SoType>, module, PythonQt::Type_RichCompare);


}
