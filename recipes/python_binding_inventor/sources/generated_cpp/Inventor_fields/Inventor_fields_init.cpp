#include <PythonQt.h>
#include <PythonQtConversion.h>
#include "inventor_fields0.h"



void PythonQt_init_InventorFields(PyObject* module) {
PythonQt::priv()->registerCPPClass("SoField", "", "InventorFields", PythonQtCreateObject<PythonQtWrapper_SoField>, nullptr, module, PythonQt::Type_RichCompare);
PythonQt::priv()->registerCPPClass("SoFieldContainer", "SoBase", "InventorFields", PythonQtCreateObject<PythonQtWrapper_SoFieldContainer>, nullptr, module, 0);
PythonQt::priv()->registerCPPClass("SoMFBitMask", "SoMFEnum", "InventorFields", PythonQtCreateObject<PythonQtWrapper_SoMFBitMask>, nullptr, module, PythonQt::Type_RichCompare);
PythonQt::priv()->registerCPPClass("SoMFBool", "SoMField", "InventorFields", PythonQtCreateObject<PythonQtWrapper_SoMFBool>, nullptr, module, PythonQt::Type_RichCompare);
PythonQt::priv()->registerCPPClass("SoMFColor", "SoMField", "InventorFields", PythonQtCreateObject<PythonQtWrapper_SoMFColor>, nullptr, module, PythonQt::Type_RichCompare);
PythonQt::priv()->registerCPPClass("SoMFDouble", "SoMField", "InventorFields", PythonQtCreateObject<PythonQtWrapper_SoMFDouble>, nullptr, module, PythonQt::Type_RichCompare);
PythonQt::priv()->registerCPPClass("SoMFEngine", "SoMField", "InventorFields", PythonQtCreateObject<PythonQtWrapper_SoMFEngine>, nullptr, module, PythonQt::Type_RichCompare);
PythonQt::priv()->registerCPPClass("SoMFEnum", "SoMField", "InventorFields", PythonQtCreateObject<PythonQtWrapper_SoMFEnum>, nullptr, module, PythonQt::Type_RichCompare);
PythonQt::priv()->registerCPPClass("SoMFFloat", "SoMField", "InventorFields", PythonQtCreateObject<PythonQtWrapper_SoMFFloat>, nullptr, module, PythonQt::Type_RichCompare);
PythonQt::priv()->registerCPPClass("SoMFInt32", "SoMField", "InventorFields", PythonQtCreateObject<PythonQtWrapper_SoMFInt32>, nullptr, module, PythonQt::Type_RichCompare);
PythonQt::priv()->registerCPPClass("SoMFMatrix", "SoMField", "InventorFields", PythonQtCreateObject<PythonQtWrapper_SoMFMatrix>, nullptr, module, PythonQt::Type_RichCompare);
PythonQt::priv()->registerCPPClass("SoMFMatrixd", "SoMField", "InventorFields", PythonQtCreateObject<PythonQtWrapper_SoMFMatrixd>, nullptr, module, PythonQt::Type_RichCompare);
PythonQt::priv()->registerCPPClass("SoMFName", "SoMField", "InventorFields", PythonQtCreateObject<PythonQtWrapper_SoMFName>, nullptr, module, PythonQt::Type_RichCompare);
PythonQt::priv()->registerCPPClass("SoMFNode", "SoMField", "InventorFields", PythonQtCreateObject<PythonQtWrapper_SoMFNode>, nullptr, module, PythonQt::Type_RichCompare);
PythonQt::priv()->registerCPPClass("SoMFPath", "SoMField", "InventorFields", PythonQtCreateObject<PythonQtWrapper_SoMFPath>, nullptr, module, PythonQt::Type_RichCompare);
PythonQt::priv()->registerCPPClass("SoMFPlane", "SoMField", "InventorFields", PythonQtCreateObject<PythonQtWrapper_SoMFPlane>, nullptr, module, PythonQt::Type_RichCompare);
PythonQt::priv()->registerCPPClass("SoMFPlaned", "SoMField", "InventorFields", PythonQtCreateObject<PythonQtWrapper_SoMFPlaned>, nullptr, module, PythonQt::Type_RichCompare);
PythonQt::priv()->registerCPPClass("SoMFRotation", "SoMField", "InventorFields", PythonQtCreateObject<PythonQtWrapper_SoMFRotation>, nullptr, module, PythonQt::Type_RichCompare);
PythonQt::priv()->registerCPPClass("SoMFRotationd", "SoMField", "InventorFields", PythonQtCreateObject<PythonQtWrapper_SoMFRotationd>, nullptr, module, PythonQt::Type_RichCompare);
PythonQt::priv()->registerCPPClass("SoMFShort", "SoMField", "InventorFields", PythonQtCreateObject<PythonQtWrapper_SoMFShort>, nullptr, module, PythonQt::Type_RichCompare);
PythonQt::priv()->registerCPPClass("SoMFString", "SoMField", "InventorFields", PythonQtCreateObject<PythonQtWrapper_SoMFString>, nullptr, module, PythonQt::Type_RichCompare);
PythonQt::priv()->registerCPPClass("SoMFTime", "SoMField", "InventorFields", PythonQtCreateObject<PythonQtWrapper_SoMFTime>, nullptr, module, PythonQt::Type_RichCompare);
PythonQt::priv()->registerCPPClass("SoMFUInt32", "SoMField", "InventorFields", PythonQtCreateObject<PythonQtWrapper_SoMFUInt32>, nullptr, module, PythonQt::Type_RichCompare);
PythonQt::priv()->registerCPPClass("SoMFUShort", "SoMField", "InventorFields", PythonQtCreateObject<PythonQtWrapper_SoMFUShort>, nullptr, module, PythonQt::Type_RichCompare);
PythonQt::priv()->registerCPPClass("SoMFVec2d", "SoMField", "InventorFields", PythonQtCreateObject<PythonQtWrapper_SoMFVec2d>, nullptr, module, PythonQt::Type_RichCompare);
PythonQt::priv()->registerCPPClass("SoMFVec2f", "SoMField", "InventorFields", PythonQtCreateObject<PythonQtWrapper_SoMFVec2f>, nullptr, module, PythonQt::Type_RichCompare);
PythonQt::priv()->registerCPPClass("SoMFVec3d", "SoMField", "InventorFields", PythonQtCreateObject<PythonQtWrapper_SoMFVec3d>, nullptr, module, PythonQt::Type_RichCompare);
PythonQt::priv()->registerCPPClass("SoMFVec3f", "SoMField", "InventorFields", PythonQtCreateObject<PythonQtWrapper_SoMFVec3f>, nullptr, module, PythonQt::Type_RichCompare);
PythonQt::priv()->registerCPPClass("SoMFVec4d", "SoMField", "InventorFields", PythonQtCreateObject<PythonQtWrapper_SoMFVec4d>, nullptr, module, PythonQt::Type_RichCompare);
PythonQt::priv()->registerCPPClass("SoMFVec4f", "SoMField", "InventorFields", PythonQtCreateObject<PythonQtWrapper_SoMFVec4f>, nullptr, module, PythonQt::Type_RichCompare);
PythonQt::priv()->registerCPPClass("SoMField", "SoField", "InventorFields", PythonQtCreateObject<PythonQtWrapper_SoMField>, nullptr, module, PythonQt::Type_RichCompare);
PythonQt::priv()->registerCPPClass("SoSFBitMask", "SoSFEnum", "InventorFields", PythonQtCreateObject<PythonQtWrapper_SoSFBitMask>, nullptr, module, PythonQt::Type_RichCompare);
PythonQt::priv()->registerCPPClass("SoSFBool", "SoSField", "InventorFields", PythonQtCreateObject<PythonQtWrapper_SoSFBool>, nullptr, module, PythonQt::Type_RichCompare);
PythonQt::priv()->registerCPPClass("SoSFColor", "SoSField", "InventorFields", PythonQtCreateObject<PythonQtWrapper_SoSFColor>, nullptr, module, PythonQt::Type_RichCompare);
PythonQt::priv()->registerCPPClass("SoSFDouble", "SoSField", "InventorFields", PythonQtCreateObject<PythonQtWrapper_SoSFDouble>, nullptr, module, PythonQt::Type_RichCompare);
PythonQt::priv()->registerCPPClass("SoSFEngine", "SoSField", "InventorFields", PythonQtCreateObject<PythonQtWrapper_SoSFEngine>, nullptr, module, PythonQt::Type_RichCompare);
PythonQt::priv()->registerCPPClass("SoSFEnum", "SoSField", "InventorFields", PythonQtCreateObject<PythonQtWrapper_SoSFEnum>, nullptr, module, PythonQt::Type_RichCompare);
PythonQt::priv()->registerCPPClass("SoSFFloat", "SoSField", "InventorFields", PythonQtCreateObject<PythonQtWrapper_SoSFFloat>, nullptr, module, PythonQt::Type_RichCompare);
PythonQt::priv()->registerCPPClass("SoSFImage", "SoSField", "InventorFields", PythonQtCreateObject<PythonQtWrapper_SoSFImage>, nullptr, module, PythonQt::Type_RichCompare);
PythonQt::priv()->registerCPPClass("SoSFInt32", "SoSField", "InventorFields", PythonQtCreateObject<PythonQtWrapper_SoSFInt32>, nullptr, module, PythonQt::Type_RichCompare);
PythonQt::priv()->registerCPPClass("SoSFMatrix", "SoSField", "InventorFields", PythonQtCreateObject<PythonQtWrapper_SoSFMatrix>, nullptr, module, PythonQt::Type_RichCompare);
PythonQt::priv()->registerCPPClass("SoSFMatrixd", "SoSField", "InventorFields", PythonQtCreateObject<PythonQtWrapper_SoSFMatrixd>, nullptr, module, PythonQt::Type_RichCompare);
PythonQt::priv()->registerCPPClass("SoSFName", "SoSField", "InventorFields", PythonQtCreateObject<PythonQtWrapper_SoSFName>, nullptr, module, PythonQt::Type_RichCompare);
PythonQt::priv()->registerCPPClass("SoSFNode", "SoSField", "InventorFields", PythonQtCreateObject<PythonQtWrapper_SoSFNode>, nullptr, module, PythonQt::Type_RichCompare);
PythonQt::priv()->registerCPPClass("SoSFPath", "SoSField", "InventorFields", PythonQtCreateObject<PythonQtWrapper_SoSFPath>, nullptr, module, PythonQt::Type_RichCompare);
PythonQt::priv()->registerCPPClass("SoSFPlane", "SoSField", "InventorFields", PythonQtCreateObject<PythonQtWrapper_SoSFPlane>, nullptr, module, PythonQt::Type_RichCompare);
PythonQt::priv()->registerCPPClass("SoSFPlaned", "SoSField", "InventorFields", PythonQtCreateObject<PythonQtWrapper_SoSFPlaned>, nullptr, module, PythonQt::Type_RichCompare);
PythonQt::priv()->registerCPPClass("SoSFRotation", "SoSField", "InventorFields", PythonQtCreateObject<PythonQtWrapper_SoSFRotation>, nullptr, module, PythonQt::Type_RichCompare);
PythonQt::priv()->registerCPPClass("SoSFRotationd", "SoSField", "InventorFields", PythonQtCreateObject<PythonQtWrapper_SoSFRotationd>, nullptr, module, PythonQt::Type_RichCompare);
PythonQt::priv()->registerCPPClass("SoSFShort", "SoSField", "InventorFields", PythonQtCreateObject<PythonQtWrapper_SoSFShort>, nullptr, module, PythonQt::Type_RichCompare);
PythonQt::priv()->registerCPPClass("SoSFString", "SoSField", "InventorFields", PythonQtCreateObject<PythonQtWrapper_SoSFString>, nullptr, module, PythonQt::Type_RichCompare);
PythonQt::priv()->registerCPPClass("SoSFTime", "SoSField", "InventorFields", PythonQtCreateObject<PythonQtWrapper_SoSFTime>, nullptr, module, PythonQt::Type_RichCompare);
PythonQt::priv()->registerCPPClass("SoSFTrigger", "SoSField", "InventorFields", PythonQtCreateObject<PythonQtWrapper_SoSFTrigger>, nullptr, module, PythonQt::Type_RichCompare);
PythonQt::priv()->registerCPPClass("SoSFUInt32", "SoSField", "InventorFields", PythonQtCreateObject<PythonQtWrapper_SoSFUInt32>, nullptr, module, PythonQt::Type_RichCompare);
PythonQt::priv()->registerCPPClass("SoSFUShort", "SoSField", "InventorFields", PythonQtCreateObject<PythonQtWrapper_SoSFUShort>, nullptr, module, PythonQt::Type_RichCompare);
PythonQt::priv()->registerCPPClass("SoSFVec2d", "SoSField", "InventorFields", PythonQtCreateObject<PythonQtWrapper_SoSFVec2d>, nullptr, module, PythonQt::Type_RichCompare);
PythonQt::priv()->registerCPPClass("SoSFVec2f", "SoSField", "InventorFields", PythonQtCreateObject<PythonQtWrapper_SoSFVec2f>, nullptr, module, PythonQt::Type_RichCompare);
PythonQt::priv()->registerCPPClass("SoSFVec2s", "SoSField", "InventorFields", PythonQtCreateObject<PythonQtWrapper_SoSFVec2s>, nullptr, module, PythonQt::Type_RichCompare);
PythonQt::priv()->registerCPPClass("SoSFVec3d", "SoSField", "InventorFields", PythonQtCreateObject<PythonQtWrapper_SoSFVec3d>, nullptr, module, PythonQt::Type_RichCompare);
PythonQt::priv()->registerCPPClass("SoSFVec3f", "SoSField", "InventorFields", PythonQtCreateObject<PythonQtWrapper_SoSFVec3f>, nullptr, module, PythonQt::Type_RichCompare);
PythonQt::priv()->registerCPPClass("SoSFVec3s", "SoSField", "InventorFields", PythonQtCreateObject<PythonQtWrapper_SoSFVec3s>, nullptr, module, PythonQt::Type_RichCompare);
PythonQt::priv()->registerCPPClass("SoSFVec4d", "SoSField", "InventorFields", PythonQtCreateObject<PythonQtWrapper_SoSFVec4d>, nullptr, module, PythonQt::Type_RichCompare);
PythonQt::priv()->registerCPPClass("SoSFVec4f", "SoSField", "InventorFields", PythonQtCreateObject<PythonQtWrapper_SoSFVec4f>, nullptr, module, PythonQt::Type_RichCompare);
PythonQt::priv()->registerCPPClass("SoSField", "SoField", "InventorFields", PythonQtCreateObject<PythonQtWrapper_SoSField>, nullptr, module, PythonQt::Type_RichCompare);


}
