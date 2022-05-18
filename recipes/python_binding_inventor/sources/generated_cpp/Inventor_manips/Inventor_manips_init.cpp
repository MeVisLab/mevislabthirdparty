/*************************************************************************************
**
** Copyright 2022, MeVis Medical Solutions AG
**
** GNU LESSER GENERAL PUBLIC LICENSE Version 2.1, February 1999
**
**************************************************************************************/
#include <PythonQt.h>
#include <PythonQtConversion.h>
#include "Inventor_manips0.h"



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
  
void PythonQt_init_InventorManips(PyObject* module) {
PythonQt::priv()->registerCPPClass("SoCenterballManip", "SoTransformManip", "InventorManips", PythonQtCreateObject<PythonQtWrapper_SoCenterballManip>, SoNodeSetInstanceWrapperOnShell<PythonQtShell_SoCenterballManip>, module, 0);
PythonQt::priv()->registerCPPClass("SoDirectionalLightManip", "SoDirectionalLight", "InventorManips", PythonQtCreateObject<PythonQtWrapper_SoDirectionalLightManip>, SoNodeSetInstanceWrapperOnShell<PythonQtShell_SoDirectionalLightManip>, module, 0);
PythonQt::priv()->registerCPPClass("SoHandleBoxManip", "SoTransformManip", "InventorManips", PythonQtCreateObject<PythonQtWrapper_SoHandleBoxManip>, SoNodeSetInstanceWrapperOnShell<PythonQtShell_SoHandleBoxManip>, module, 0);
PythonQt::priv()->registerCPPClass("SoJackManip", "SoTransformManip", "InventorManips", PythonQtCreateObject<PythonQtWrapper_SoJackManip>, SoNodeSetInstanceWrapperOnShell<PythonQtShell_SoJackManip>, module, 0);
PythonQt::priv()->registerCPPClass("SoSpotLightManip", "SoSpotLight", "InventorManips", PythonQtCreateObject<PythonQtWrapper_SoSpotLightManip>, SoNodeSetInstanceWrapperOnShell<PythonQtShell_SoSpotLightManip>, module, 0);
PythonQt::priv()->registerCPPClass("SoTabBoxManip", "SoTransformManip", "InventorManips", PythonQtCreateObject<PythonQtWrapper_SoTabBoxManip>, SoNodeSetInstanceWrapperOnShell<PythonQtShell_SoTabBoxManip>, module, 0);
PythonQt::priv()->registerCPPClass("SoTrackballManip", "SoTransformManip", "InventorManips", PythonQtCreateObject<PythonQtWrapper_SoTrackballManip>, SoNodeSetInstanceWrapperOnShell<PythonQtShell_SoTrackballManip>, module, 0);
PythonQt::priv()->registerCPPClass("SoTransformBoxManip", "SoTransformManip", "InventorManips", PythonQtCreateObject<PythonQtWrapper_SoTransformBoxManip>, SoNodeSetInstanceWrapperOnShell<PythonQtShell_SoTransformBoxManip>, module, 0);
PythonQt::priv()->registerCPPClass("SoTransformManip", "SoTransform", "InventorManips", PythonQtCreateObject<PythonQtWrapper_SoTransformManip>, SoNodeSetInstanceWrapperOnShell<PythonQtShell_SoTransformManip>, module, 0);
PythonQt::priv()->registerCPPClass("SoTransformerManip", "SoTransformManip", "InventorManips", PythonQtCreateObject<PythonQtWrapper_SoTransformerManip>, SoNodeSetInstanceWrapperOnShell<PythonQtShell_SoTransformerManip>, module, 0);


}
