#include <PythonQt.h>
#include <PythonQtConversion.h>
#include "inventor_nodekits0.h"



template<class T> void SoNodeSetInstanceWrapperOnShell(void* object, PythonQtInstanceWrapper* wrapper) { 
  (reinterpret_cast<T*>(object))->_wrapper = wrapper;
  if (wrapper) {
    SbName name = Py_TYPE(wrapper)->tp_name;
    SoType t = SoType::fromName(name);
    if (t.isBad()) {
      t = SoType::createType(T::getClassTypeId(),name,NULL,T::getClassTypeId().getData());
    }
    ((T*)object)->_type = t;
  }
}
  
void PythonQt_init_InventorNodekits(PyObject* module) {
PythonQt::priv()->registerCPPClass("SoBaseKit", "SoNode", "InventorNodekits", PythonQtCreateObject<PythonQtWrapper_SoBaseKit>, SoNodeSetInstanceWrapperOnShell<PythonQtShell_SoBaseKit>, module, 0);
PythonQt::priv()->registerCPPClass("SoInteractionKit", "SoBaseKit", "InventorNodekits", PythonQtCreateObject<PythonQtWrapper_SoInteractionKit>, SoNodeSetInstanceWrapperOnShell<PythonQtShell_SoInteractionKit>, module, 0);
PythonQt::priv()->registerCPPClass("SoNodeKit", "", "InventorNodekits", PythonQtCreateObject<PythonQtWrapper_SoNodeKit>, PythonQtSetInstanceWrapperOnShell<PythonQtShell_SoNodeKit>, module, 0);


}
