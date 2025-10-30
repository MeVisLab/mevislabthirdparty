#include <PythonQt.h>
#include <PythonQtConversion.h>
#include "inventor_draggers0.h"



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
  
void PythonQt_init_InventorDraggers(PyObject* module) {
PythonQt::priv()->registerCPPClass("SoCenterballDragger", "SoDragger", "InventorDraggers", PythonQtCreateObject<PythonQtWrapper_SoCenterballDragger>, SoNodeSetInstanceWrapperOnShell<PythonQtShell_SoCenterballDragger>, module, 0);
PythonQt::priv()->registerCPPClass("SoDirectionalLightDragger", "SoDragger", "InventorDraggers", PythonQtCreateObject<PythonQtWrapper_SoDirectionalLightDragger>, SoNodeSetInstanceWrapperOnShell<PythonQtShell_SoDirectionalLightDragger>, module, 0);
PythonQt::priv()->registerCPPClass("SoDragPointDragger", "SoDragger", "InventorDraggers", PythonQtCreateObject<PythonQtWrapper_SoDragPointDragger>, SoNodeSetInstanceWrapperOnShell<PythonQtShell_SoDragPointDragger>, module, 0);
PythonQt::priv()->registerCPPClass("SoDragger", "SoInteractionKit", "InventorDraggers", PythonQtCreateObject<PythonQtWrapper_SoDragger>, SoNodeSetInstanceWrapperOnShell<PythonQtShell_SoDragger>, module, 0);
PythonQt::priv()->registerCPPClass("SoHandleBoxDragger", "SoDragger", "InventorDraggers", PythonQtCreateObject<PythonQtWrapper_SoHandleBoxDragger>, SoNodeSetInstanceWrapperOnShell<PythonQtShell_SoHandleBoxDragger>, module, 0);
PythonQt::priv()->registerCPPClass("SoJackDragger", "SoDragger", "InventorDraggers", PythonQtCreateObject<PythonQtWrapper_SoJackDragger>, SoNodeSetInstanceWrapperOnShell<PythonQtShell_SoJackDragger>, module, 0);
PythonQt::priv()->registerCPPClass("SoPointLightDragger", "SoDragger", "InventorDraggers", PythonQtCreateObject<PythonQtWrapper_SoPointLightDragger>, SoNodeSetInstanceWrapperOnShell<PythonQtShell_SoPointLightDragger>, module, 0);
PythonQt::priv()->registerCPPClass("SoRotateCylindricalDragger", "SoDragger", "InventorDraggers", PythonQtCreateObject<PythonQtWrapper_SoRotateCylindricalDragger>, SoNodeSetInstanceWrapperOnShell<PythonQtShell_SoRotateCylindricalDragger>, module, 0);
PythonQt::priv()->registerCPPClass("SoRotateDiscDragger", "SoDragger", "InventorDraggers", PythonQtCreateObject<PythonQtWrapper_SoRotateDiscDragger>, SoNodeSetInstanceWrapperOnShell<PythonQtShell_SoRotateDiscDragger>, module, 0);
PythonQt::priv()->registerCPPClass("SoRotateSphericalDragger", "SoDragger", "InventorDraggers", PythonQtCreateObject<PythonQtWrapper_SoRotateSphericalDragger>, SoNodeSetInstanceWrapperOnShell<PythonQtShell_SoRotateSphericalDragger>, module, 0);
PythonQt::priv()->registerCPPClass("SoScale1Dragger", "SoDragger", "InventorDraggers", PythonQtCreateObject<PythonQtWrapper_SoScale1Dragger>, SoNodeSetInstanceWrapperOnShell<PythonQtShell_SoScale1Dragger>, module, 0);
PythonQt::priv()->registerCPPClass("SoScale2Dragger", "SoDragger", "InventorDraggers", PythonQtCreateObject<PythonQtWrapper_SoScale2Dragger>, SoNodeSetInstanceWrapperOnShell<PythonQtShell_SoScale2Dragger>, module, 0);
PythonQt::priv()->registerCPPClass("SoScale2UniformDragger", "SoDragger", "InventorDraggers", PythonQtCreateObject<PythonQtWrapper_SoScale2UniformDragger>, SoNodeSetInstanceWrapperOnShell<PythonQtShell_SoScale2UniformDragger>, module, 0);
PythonQt::priv()->registerCPPClass("SoScaleUniformDragger", "SoDragger", "InventorDraggers", PythonQtCreateObject<PythonQtWrapper_SoScaleUniformDragger>, SoNodeSetInstanceWrapperOnShell<PythonQtShell_SoScaleUniformDragger>, module, 0);
PythonQt::priv()->registerCPPClass("SoSpotLightDragger", "SoDragger", "InventorDraggers", PythonQtCreateObject<PythonQtWrapper_SoSpotLightDragger>, SoNodeSetInstanceWrapperOnShell<PythonQtShell_SoSpotLightDragger>, module, 0);
PythonQt::priv()->registerCPPClass("SoTabBoxDragger", "SoDragger", "InventorDraggers", PythonQtCreateObject<PythonQtWrapper_SoTabBoxDragger>, SoNodeSetInstanceWrapperOnShell<PythonQtShell_SoTabBoxDragger>, module, 0);
PythonQt::priv()->registerCPPClass("SoTabPlaneDragger", "SoDragger", "InventorDraggers", PythonQtCreateObject<PythonQtWrapper_SoTabPlaneDragger>, SoNodeSetInstanceWrapperOnShell<PythonQtShell_SoTabPlaneDragger>, module, 0);
PythonQt::priv()->registerCPPClass("SoTrackballDragger", "SoDragger", "InventorDraggers", PythonQtCreateObject<PythonQtWrapper_SoTrackballDragger>, SoNodeSetInstanceWrapperOnShell<PythonQtShell_SoTrackballDragger>, module, 0);
PythonQt::priv()->registerCPPClass("SoTransformBoxDragger", "SoDragger", "InventorDraggers", PythonQtCreateObject<PythonQtWrapper_SoTransformBoxDragger>, SoNodeSetInstanceWrapperOnShell<PythonQtShell_SoTransformBoxDragger>, module, 0);
PythonQt::priv()->registerCPPClass("SoTransformerDragger", "SoDragger", "InventorDraggers", PythonQtCreateObject<PythonQtWrapper_SoTransformerDragger>, SoNodeSetInstanceWrapperOnShell<PythonQtShell_SoTransformerDragger>, module, 0);
PythonQt::priv()->registerCPPClass("SoTranslate1Dragger", "SoDragger", "InventorDraggers", PythonQtCreateObject<PythonQtWrapper_SoTranslate1Dragger>, SoNodeSetInstanceWrapperOnShell<PythonQtShell_SoTranslate1Dragger>, module, 0);
PythonQt::priv()->registerCPPClass("SoTranslate2Dragger", "SoDragger", "InventorDraggers", PythonQtCreateObject<PythonQtWrapper_SoTranslate2Dragger>, SoNodeSetInstanceWrapperOnShell<PythonQtShell_SoTranslate2Dragger>, module, 0);


}
