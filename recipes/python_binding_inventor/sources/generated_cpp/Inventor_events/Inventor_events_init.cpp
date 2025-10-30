#include <PythonQt.h>
#include <PythonQtConversion.h>
#include "inventor_events0.h"



void PythonQt_init_InventorEvents(PyObject* module) {
PythonQt::priv()->registerCPPClass("SoButtonEvent", "SoEvent", "InventorEvents", PythonQtCreateObject<PythonQtWrapper_SoButtonEvent>, PythonQtSetInstanceWrapperOnShell<PythonQtShell_SoButtonEvent>, module, 0);
PythonQt::priv()->registerCPPClass("SoEvent", "", "InventorEvents", PythonQtCreateObject<PythonQtWrapper_SoEvent>, PythonQtSetInstanceWrapperOnShell<PythonQtShell_SoEvent>, module, 0);
PythonQt::priv()->registerCPPClass("SoKeyboardEvent", "SoButtonEvent", "InventorEvents", PythonQtCreateObject<PythonQtWrapper_SoKeyboardEvent>, PythonQtSetInstanceWrapperOnShell<PythonQtShell_SoKeyboardEvent>, module, 0);
PythonQt::priv()->registerCPPClass("SoLocation2Event", "SoEvent", "InventorEvents", PythonQtCreateObject<PythonQtWrapper_SoLocation2Event>, PythonQtSetInstanceWrapperOnShell<PythonQtShell_SoLocation2Event>, module, 0);
PythonQt::priv()->registerCPPClass("SoLocation2RefreshEvent", "SoLocation2Event", "InventorEvents", PythonQtCreateObject<PythonQtWrapper_SoLocation2RefreshEvent>, nullptr, module, 0);
PythonQt::priv()->registerCPPClass("SoMotion3Event", "SoEvent", "InventorEvents", PythonQtCreateObject<PythonQtWrapper_SoMotion3Event>, PythonQtSetInstanceWrapperOnShell<PythonQtShell_SoMotion3Event>, module, 0);
PythonQt::priv()->registerCPPClass("SoMouseButtonEvent", "SoButtonEvent", "InventorEvents", PythonQtCreateObject<PythonQtWrapper_SoMouseButtonEvent>, PythonQtSetInstanceWrapperOnShell<PythonQtShell_SoMouseButtonEvent>, module, 0);
PythonQt::priv()->registerCPPClass("SoMouseWheelEvent", "SoEvent", "InventorEvents", PythonQtCreateObject<PythonQtWrapper_SoMouseWheelEvent>, nullptr, module, 0);
PythonQt::priv()->registerCPPClass("SoSpaceballButtonEvent", "SoButtonEvent", "InventorEvents", PythonQtCreateObject<PythonQtWrapper_SoSpaceballButtonEvent>, PythonQtSetInstanceWrapperOnShell<PythonQtShell_SoSpaceballButtonEvent>, module, 0);


}
