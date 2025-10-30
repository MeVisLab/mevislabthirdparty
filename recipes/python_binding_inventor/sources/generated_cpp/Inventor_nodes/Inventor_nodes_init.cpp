#include <PythonQt.h>
#include <PythonQtConversion.h>
#include "inventor_nodes0.h"



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
  
void PythonQt_init_InventorNodes(PyObject* module) {
PythonQt::priv()->registerCPPClass("SoAnnotation", "SoSeparator", "InventorNodes", PythonQtCreateObject<PythonQtWrapper_SoAnnotation>, SoNodeSetInstanceWrapperOnShell<PythonQtShell_SoAnnotation>, module, 0);
PythonQt::priv()->registerCPPClass("SoAntiSquish", "SoTransformation", "InventorNodes", PythonQtCreateObject<PythonQtWrapper_SoAntiSquish>, SoNodeSetInstanceWrapperOnShell<PythonQtShell_SoAntiSquish>, module, 0);
PythonQt::priv()->registerCPPClass("SoArray", "SoGroup", "InventorNodes", PythonQtCreateObject<PythonQtWrapper_SoArray>, SoNodeSetInstanceWrapperOnShell<PythonQtShell_SoArray>, module, 0);
PythonQt::priv()->registerCPPClass("SoAsciiText", "SoShape", "InventorNodes", PythonQtCreateObject<PythonQtWrapper_SoAsciiText>, SoNodeSetInstanceWrapperOnShell<PythonQtShell_SoAsciiText>, module, 0);
PythonQt::priv()->registerCPPClass("SoBaseColor", "SoNode", "InventorNodes", PythonQtCreateObject<PythonQtWrapper_SoBaseColor>, SoNodeSetInstanceWrapperOnShell<PythonQtShell_SoBaseColor>, module, 0);
PythonQt::priv()->registerCPPClass("SoBlinker", "SoSwitch", "InventorNodes", PythonQtCreateObject<PythonQtWrapper_SoBlinker>, SoNodeSetInstanceWrapperOnShell<PythonQtShell_SoBlinker>, module, 0);
PythonQt::priv()->registerCPPClass("SoCallback", "SoNode", "InventorNodes", PythonQtCreateObject<PythonQtWrapper_SoCallback>, SoNodeSetInstanceWrapperOnShell<PythonQtShell_SoCallback>, module, 0);
PythonQt::priv()->registerCPPClass("SoCamera", "SoNode", "InventorNodes", PythonQtCreateObject<PythonQtWrapper_SoCamera>, SoNodeSetInstanceWrapperOnShell<PythonQtShell_SoCamera>, module, 0);
PythonQt::priv()->registerCPPClass("SoClipPlane", "SoNode", "InventorNodes", PythonQtCreateObject<PythonQtWrapper_SoClipPlane>, SoNodeSetInstanceWrapperOnShell<PythonQtShell_SoClipPlane>, module, 0);
PythonQt::priv()->registerCPPClass("SoComplexity", "SoNode", "InventorNodes", PythonQtCreateObject<PythonQtWrapper_SoComplexity>, SoNodeSetInstanceWrapperOnShell<PythonQtShell_SoComplexity>, module, 0);
PythonQt::priv()->registerCPPClass("SoCone", "SoShape", "InventorNodes", PythonQtCreateObject<PythonQtWrapper_SoCone>, SoNodeSetInstanceWrapperOnShell<PythonQtShell_SoCone>, module, 0);
PythonQt::priv()->registerCPPClass("SoCoordinate3", "SoNode", "InventorNodes", PythonQtCreateObject<PythonQtWrapper_SoCoordinate3>, SoNodeSetInstanceWrapperOnShell<PythonQtShell_SoCoordinate3>, module, 0);
PythonQt::priv()->registerCPPClass("SoCoordinate4", "SoNode", "InventorNodes", PythonQtCreateObject<PythonQtWrapper_SoCoordinate4>, SoNodeSetInstanceWrapperOnShell<PythonQtShell_SoCoordinate4>, module, 0);
PythonQt::priv()->registerCPPClass("SoCube", "SoShape", "InventorNodes", PythonQtCreateObject<PythonQtWrapper_SoCube>, SoNodeSetInstanceWrapperOnShell<PythonQtShell_SoCube>, module, 0);
PythonQt::priv()->registerCPPClass("SoCylinder", "SoShape", "InventorNodes", PythonQtCreateObject<PythonQtWrapper_SoCylinder>, SoNodeSetInstanceWrapperOnShell<PythonQtShell_SoCylinder>, module, 0);
PythonQt::priv()->registerCPPClass("SoDirectionalLight", "SoLight", "InventorNodes", PythonQtCreateObject<PythonQtWrapper_SoDirectionalLight>, SoNodeSetInstanceWrapperOnShell<PythonQtShell_SoDirectionalLight>, module, 0);
PythonQt::priv()->registerCPPClass("SoDrawStyle", "SoNode", "InventorNodes", PythonQtCreateObject<PythonQtWrapper_SoDrawStyle>, SoNodeSetInstanceWrapperOnShell<PythonQtShell_SoDrawStyle>, module, 0);
PythonQt::priv()->registerCPPClass("SoEnvironment", "SoNode", "InventorNodes", PythonQtCreateObject<PythonQtWrapper_SoEnvironment>, SoNodeSetInstanceWrapperOnShell<PythonQtShell_SoEnvironment>, module, 0);
PythonQt::priv()->registerCPPClass("SoEventCallback", "SoNode", "InventorNodes", PythonQtCreateObject<PythonQtWrapper_SoEventCallback>, SoNodeSetInstanceWrapperOnShell<PythonQtShell_SoEventCallback>, module, 0);
PythonQt::priv()->registerCPPClass("SoFaceSet", "SoNonIndexedShape", "InventorNodes", PythonQtCreateObject<PythonQtWrapper_SoFaceSet>, SoNodeSetInstanceWrapperOnShell<PythonQtShell_SoFaceSet>, module, 0);
PythonQt::priv()->registerCPPClass("SoFile", "SoNode", "InventorNodes", PythonQtCreateObject<PythonQtWrapper_SoFile>, SoNodeSetInstanceWrapperOnShell<PythonQtShell_SoFile>, module, 0);
PythonQt::priv()->registerCPPClass("SoFont", "SoNode", "InventorNodes", PythonQtCreateObject<PythonQtWrapper_SoFont>, SoNodeSetInstanceWrapperOnShell<PythonQtShell_SoFont>, module, 0);
PythonQt::priv()->registerCPPClass("SoFontStyle", "SoFont", "InventorNodes", PythonQtCreateObject<PythonQtWrapper_SoFontStyle>, SoNodeSetInstanceWrapperOnShell<PythonQtShell_SoFontStyle>, module, 0);
PythonQt::priv()->registerCPPClass("SoGroup", "SoNode", "InventorNodes", PythonQtCreateObject<PythonQtWrapper_SoGroup>, SoNodeSetInstanceWrapperOnShell<PythonQtShell_SoGroup>, module, 0);
PythonQt::priv()->registerCPPClass("SoIndexedFaceSet", "SoIndexedShape", "InventorNodes", PythonQtCreateObject<PythonQtWrapper_SoIndexedFaceSet>, SoNodeSetInstanceWrapperOnShell<PythonQtShell_SoIndexedFaceSet>, module, 0);
PythonQt::priv()->registerCPPClass("SoIndexedLineSet", "SoIndexedShape", "InventorNodes", PythonQtCreateObject<PythonQtWrapper_SoIndexedLineSet>, SoNodeSetInstanceWrapperOnShell<PythonQtShell_SoIndexedLineSet>, module, 0);
PythonQt::priv()->registerCPPClass("SoIndexedNurbsCurve", "SoShape", "InventorNodes", PythonQtCreateObject<PythonQtWrapper_SoIndexedNurbsCurve>, SoNodeSetInstanceWrapperOnShell<PythonQtShell_SoIndexedNurbsCurve>, module, 0);
PythonQt::priv()->registerCPPClass("SoIndexedNurbsSurface", "SoShape", "InventorNodes", PythonQtCreateObject<PythonQtWrapper_SoIndexedNurbsSurface>, SoNodeSetInstanceWrapperOnShell<PythonQtShell_SoIndexedNurbsSurface>, module, 0);
PythonQt::priv()->registerCPPClass("SoIndexedShape", "SoVertexShape", "InventorNodes", PythonQtCreateObject<PythonQtWrapper_SoIndexedShape>, SoNodeSetInstanceWrapperOnShell<PythonQtShell_SoIndexedShape>, module, 0);
PythonQt::priv()->registerCPPClass("SoIndexedTriangleSet", "SoIndexedShape", "InventorNodes", PythonQtCreateObject<PythonQtWrapper_SoIndexedTriangleSet>, SoNodeSetInstanceWrapperOnShell<PythonQtShell_SoIndexedTriangleSet>, module, 0);
PythonQt::priv()->registerCPPClass("SoIndexedTriangleStripSet", "SoIndexedShape", "InventorNodes", PythonQtCreateObject<PythonQtWrapper_SoIndexedTriangleStripSet>, SoNodeSetInstanceWrapperOnShell<PythonQtShell_SoIndexedTriangleStripSet>, module, 0);
PythonQt::priv()->registerCPPClass("SoInfo", "SoNode", "InventorNodes", PythonQtCreateObject<PythonQtWrapper_SoInfo>, SoNodeSetInstanceWrapperOnShell<PythonQtShell_SoInfo>, module, 0);
PythonQt::priv()->registerCPPClass("SoLOD", "SoGroup", "InventorNodes", PythonQtCreateObject<PythonQtWrapper_SoLOD>, SoNodeSetInstanceWrapperOnShell<PythonQtShell_SoLOD>, module, 0);
PythonQt::priv()->registerCPPClass("SoLabel", "SoNode", "InventorNodes", PythonQtCreateObject<PythonQtWrapper_SoLabel>, SoNodeSetInstanceWrapperOnShell<PythonQtShell_SoLabel>, module, 0);
PythonQt::priv()->registerCPPClass("SoLevelOfDetail", "SoGroup", "InventorNodes", PythonQtCreateObject<PythonQtWrapper_SoLevelOfDetail>, SoNodeSetInstanceWrapperOnShell<PythonQtShell_SoLevelOfDetail>, module, 0);
PythonQt::priv()->registerCPPClass("SoLight", "SoNode", "InventorNodes", PythonQtCreateObject<PythonQtWrapper_SoLight>, SoNodeSetInstanceWrapperOnShell<PythonQtShell_SoLight>, module, 0);
PythonQt::priv()->registerCPPClass("SoLightModel", "SoNode", "InventorNodes", PythonQtCreateObject<PythonQtWrapper_SoLightModel>, SoNodeSetInstanceWrapperOnShell<PythonQtShell_SoLightModel>, module, 0);
PythonQt::priv()->registerCPPClass("SoLineSet", "SoNonIndexedShape", "InventorNodes", PythonQtCreateObject<PythonQtWrapper_SoLineSet>, SoNodeSetInstanceWrapperOnShell<PythonQtShell_SoLineSet>, module, 0);
PythonQt::priv()->registerCPPClass("SoLinearProfile", "SoProfile", "InventorNodes", PythonQtCreateObject<PythonQtWrapper_SoLinearProfile>, SoNodeSetInstanceWrapperOnShell<PythonQtShell_SoLinearProfile>, module, 0);
PythonQt::priv()->registerCPPClass("SoLocateHighlight", "SoSeparator", "InventorNodes", PythonQtCreateObject<PythonQtWrapper_SoLocateHighlight>, SoNodeSetInstanceWrapperOnShell<PythonQtShell_SoLocateHighlight>, module, 0);
PythonQt::priv()->registerCPPClass("SoMaterial", "SoNode", "InventorNodes", PythonQtCreateObject<PythonQtWrapper_SoMaterial>, SoNodeSetInstanceWrapperOnShell<PythonQtShell_SoMaterial>, module, 0);
PythonQt::priv()->registerCPPClass("SoMaterialBinding", "SoNode", "InventorNodes", PythonQtCreateObject<PythonQtWrapper_SoMaterialBinding>, SoNodeSetInstanceWrapperOnShell<PythonQtShell_SoMaterialBinding>, module, 0);
PythonQt::priv()->registerCPPClass("SoMatrixTransform", "SoTransformation", "InventorNodes", PythonQtCreateObject<PythonQtWrapper_SoMatrixTransform>, SoNodeSetInstanceWrapperOnShell<PythonQtShell_SoMatrixTransform>, module, 0);
PythonQt::priv()->registerCPPClass("SoMultipleCopy", "SoGroup", "InventorNodes", PythonQtCreateObject<PythonQtWrapper_SoMultipleCopy>, SoNodeSetInstanceWrapperOnShell<PythonQtShell_SoMultipleCopy>, module, 0);
PythonQt::priv()->registerCPPClass("SoNode", "SoFieldContainer", "InventorNodes", PythonQtCreateObject<PythonQtWrapper_SoNode>, SoNodeSetInstanceWrapperOnShell<PythonQtShell_SoNode>, module, 0);
PythonQt::priv()->registerCPPClass("SoNonIndexedShape", "SoVertexShape", "InventorNodes", PythonQtCreateObject<PythonQtWrapper_SoNonIndexedShape>, SoNodeSetInstanceWrapperOnShell<PythonQtShell_SoNonIndexedShape>, module, 0);
PythonQt::priv()->registerCPPClass("SoNormal", "SoNode", "InventorNodes", PythonQtCreateObject<PythonQtWrapper_SoNormal>, SoNodeSetInstanceWrapperOnShell<PythonQtShell_SoNormal>, module, 0);
PythonQt::priv()->registerCPPClass("SoNormalBinding", "SoNode", "InventorNodes", PythonQtCreateObject<PythonQtWrapper_SoNormalBinding>, SoNodeSetInstanceWrapperOnShell<PythonQtShell_SoNormalBinding>, module, 0);
PythonQt::priv()->registerCPPClass("SoNurbsCurve", "SoShape", "InventorNodes", PythonQtCreateObject<PythonQtWrapper_SoNurbsCurve>, SoNodeSetInstanceWrapperOnShell<PythonQtShell_SoNurbsCurve>, module, 0);
PythonQt::priv()->registerCPPClass("SoNurbsProfile", "SoProfile", "InventorNodes", PythonQtCreateObject<PythonQtWrapper_SoNurbsProfile>, SoNodeSetInstanceWrapperOnShell<PythonQtShell_SoNurbsProfile>, module, 0);
PythonQt::priv()->registerCPPClass("SoNurbsSurface", "SoShape", "InventorNodes", PythonQtCreateObject<PythonQtWrapper_SoNurbsSurface>, SoNodeSetInstanceWrapperOnShell<PythonQtShell_SoNurbsSurface>, module, 0);
PythonQt::priv()->registerCPPClass("SoOrthographicCamera", "SoCamera", "InventorNodes", PythonQtCreateObject<PythonQtWrapper_SoOrthographicCamera>, SoNodeSetInstanceWrapperOnShell<PythonQtShell_SoOrthographicCamera>, module, 0);
PythonQt::priv()->registerCPPClass("SoPackedColor", "SoNode", "InventorNodes", PythonQtCreateObject<PythonQtWrapper_SoPackedColor>, SoNodeSetInstanceWrapperOnShell<PythonQtShell_SoPackedColor>, module, 0);
PythonQt::priv()->registerCPPClass("SoPathSwitch", "SoGroup", "InventorNodes", PythonQtCreateObject<PythonQtWrapper_SoPathSwitch>, SoNodeSetInstanceWrapperOnShell<PythonQtShell_SoPathSwitch>, module, 0);
PythonQt::priv()->registerCPPClass("SoPendulum", "SoRotation", "InventorNodes", PythonQtCreateObject<PythonQtWrapper_SoPendulum>, SoNodeSetInstanceWrapperOnShell<PythonQtShell_SoPendulum>, module, 0);
PythonQt::priv()->registerCPPClass("SoPerspectiveCamera", "SoCamera", "InventorNodes", PythonQtCreateObject<PythonQtWrapper_SoPerspectiveCamera>, SoNodeSetInstanceWrapperOnShell<PythonQtShell_SoPerspectiveCamera>, module, 0);
PythonQt::priv()->registerCPPClass("SoPickStyle", "SoNode", "InventorNodes", PythonQtCreateObject<PythonQtWrapper_SoPickStyle>, SoNodeSetInstanceWrapperOnShell<PythonQtShell_SoPickStyle>, module, 0);
PythonQt::priv()->registerCPPClass("SoPointLight", "SoLight", "InventorNodes", PythonQtCreateObject<PythonQtWrapper_SoPointLight>, SoNodeSetInstanceWrapperOnShell<PythonQtShell_SoPointLight>, module, 0);
PythonQt::priv()->registerCPPClass("SoPointSet", "SoNonIndexedShape", "InventorNodes", PythonQtCreateObject<PythonQtWrapper_SoPointSet>, SoNodeSetInstanceWrapperOnShell<PythonQtShell_SoPointSet>, module, 0);
PythonQt::priv()->registerCPPClass("SoPolygonOffset", "SoNode", "InventorNodes", PythonQtCreateObject<PythonQtWrapper_SoPolygonOffset>, SoNodeSetInstanceWrapperOnShell<PythonQtShell_SoPolygonOffset>, module, 0);
PythonQt::priv()->registerCPPClass("SoProfile", "SoNode", "InventorNodes", PythonQtCreateObject<PythonQtWrapper_SoProfile>, SoNodeSetInstanceWrapperOnShell<PythonQtShell_SoProfile>, module, 0);
PythonQt::priv()->registerCPPClass("SoProfileCoordinate2", "SoNode", "InventorNodes", PythonQtCreateObject<PythonQtWrapper_SoProfileCoordinate2>, SoNodeSetInstanceWrapperOnShell<PythonQtShell_SoProfileCoordinate2>, module, 0);
PythonQt::priv()->registerCPPClass("SoProfileCoordinate3", "SoNode", "InventorNodes", PythonQtCreateObject<PythonQtWrapper_SoProfileCoordinate3>, SoNodeSetInstanceWrapperOnShell<PythonQtShell_SoProfileCoordinate3>, module, 0);
PythonQt::priv()->registerCPPClass("SoQuadMesh", "SoNonIndexedShape", "InventorNodes", PythonQtCreateObject<PythonQtWrapper_SoQuadMesh>, SoNodeSetInstanceWrapperOnShell<PythonQtShell_SoQuadMesh>, module, 0);
PythonQt::priv()->registerCPPClass("SoResetTransform", "SoTransformation", "InventorNodes", PythonQtCreateObject<PythonQtWrapper_SoResetTransform>, SoNodeSetInstanceWrapperOnShell<PythonQtShell_SoResetTransform>, module, 0);
PythonQt::priv()->registerCPPClass("SoRotation", "SoTransformation", "InventorNodes", PythonQtCreateObject<PythonQtWrapper_SoRotation>, SoNodeSetInstanceWrapperOnShell<PythonQtShell_SoRotation>, module, 0);
PythonQt::priv()->registerCPPClass("SoRotationXYZ", "SoTransformation", "InventorNodes", PythonQtCreateObject<PythonQtWrapper_SoRotationXYZ>, SoNodeSetInstanceWrapperOnShell<PythonQtShell_SoRotationXYZ>, module, 0);
PythonQt::priv()->registerCPPClass("SoRotor", "SoRotation", "InventorNodes", PythonQtCreateObject<PythonQtWrapper_SoRotor>, SoNodeSetInstanceWrapperOnShell<PythonQtShell_SoRotor>, module, 0);
PythonQt::priv()->registerCPPClass("SoScale", "SoTransformation", "InventorNodes", PythonQtCreateObject<PythonQtWrapper_SoScale>, SoNodeSetInstanceWrapperOnShell<PythonQtShell_SoScale>, module, 0);
PythonQt::priv()->registerCPPClass("SoSelection", "SoSeparator", "InventorNodes", PythonQtCreateObject<PythonQtWrapper_SoSelection>, SoNodeSetInstanceWrapperOnShell<PythonQtShell_SoSelection>, module, 0);
PythonQt::priv()->registerCPPClass("SoSeparator", "SoGroup", "InventorNodes", PythonQtCreateObject<PythonQtWrapper_SoSeparator>, SoNodeSetInstanceWrapperOnShell<PythonQtShell_SoSeparator>, module, 0);
PythonQt::priv()->registerCPPClass("SoShape", "SoNode", "InventorNodes", PythonQtCreateObject<PythonQtWrapper_SoShape>, SoNodeSetInstanceWrapperOnShell<PythonQtShell_SoShape>, module, 0);
PythonQt::priv()->registerCPPClass("SoShapeHints", "SoNode", "InventorNodes", PythonQtCreateObject<PythonQtWrapper_SoShapeHints>, SoNodeSetInstanceWrapperOnShell<PythonQtShell_SoShapeHints>, module, 0);
PythonQt::priv()->registerCPPClass("SoShuttle", "SoTranslation", "InventorNodes", PythonQtCreateObject<PythonQtWrapper_SoShuttle>, SoNodeSetInstanceWrapperOnShell<PythonQtShell_SoShuttle>, module, 0);
PythonQt::priv()->registerCPPClass("SoSphere", "SoShape", "InventorNodes", PythonQtCreateObject<PythonQtWrapper_SoSphere>, SoNodeSetInstanceWrapperOnShell<PythonQtShell_SoSphere>, module, 0);
PythonQt::priv()->registerCPPClass("SoSpotLight", "SoLight", "InventorNodes", PythonQtCreateObject<PythonQtWrapper_SoSpotLight>, SoNodeSetInstanceWrapperOnShell<PythonQtShell_SoSpotLight>, module, 0);
PythonQt::priv()->registerCPPClass("SoSurroundScale", "SoTransformation", "InventorNodes", PythonQtCreateObject<PythonQtWrapper_SoSurroundScale>, SoNodeSetInstanceWrapperOnShell<PythonQtShell_SoSurroundScale>, module, 0);
PythonQt::priv()->registerCPPClass("SoSwitch", "SoGroup", "InventorNodes", PythonQtCreateObject<PythonQtWrapper_SoSwitch>, SoNodeSetInstanceWrapperOnShell<PythonQtShell_SoSwitch>, module, 0);
PythonQt::priv()->registerCPPClass("SoText2", "SoShape", "InventorNodes", PythonQtCreateObject<PythonQtWrapper_SoText2>, SoNodeSetInstanceWrapperOnShell<PythonQtShell_SoText2>, module, 0);
PythonQt::priv()->registerCPPClass("SoText3", "SoShape", "InventorNodes", PythonQtCreateObject<PythonQtWrapper_SoText3>, SoNodeSetInstanceWrapperOnShell<PythonQtShell_SoText3>, module, 0);
PythonQt::priv()->registerCPPClass("SoTexture2", "SoNode", "InventorNodes", PythonQtCreateObject<PythonQtWrapper_SoTexture2>, SoNodeSetInstanceWrapperOnShell<PythonQtShell_SoTexture2>, module, 0);
PythonQt::priv()->registerCPPClass("SoTexture2Transform", "SoNode", "InventorNodes", PythonQtCreateObject<PythonQtWrapper_SoTexture2Transform>, SoNodeSetInstanceWrapperOnShell<PythonQtShell_SoTexture2Transform>, module, 0);
PythonQt::priv()->registerCPPClass("SoTextureCoordinate2", "SoNode", "InventorNodes", PythonQtCreateObject<PythonQtWrapper_SoTextureCoordinate2>, SoNodeSetInstanceWrapperOnShell<PythonQtShell_SoTextureCoordinate2>, module, 0);
PythonQt::priv()->registerCPPClass("SoTextureCoordinateBinding", "SoNode", "InventorNodes", PythonQtCreateObject<PythonQtWrapper_SoTextureCoordinateBinding>, SoNodeSetInstanceWrapperOnShell<PythonQtShell_SoTextureCoordinateBinding>, module, 0);
PythonQt::priv()->registerCPPClass("SoTextureCoordinateDefault", "SoTextureCoordinateFunction", "InventorNodes", PythonQtCreateObject<PythonQtWrapper_SoTextureCoordinateDefault>, SoNodeSetInstanceWrapperOnShell<PythonQtShell_SoTextureCoordinateDefault>, module, 0);
PythonQt::priv()->registerCPPClass("SoTextureCoordinateEnvironment", "SoTextureCoordinateFunction", "InventorNodes", PythonQtCreateObject<PythonQtWrapper_SoTextureCoordinateEnvironment>, SoNodeSetInstanceWrapperOnShell<PythonQtShell_SoTextureCoordinateEnvironment>, module, 0);
PythonQt::priv()->registerCPPClass("SoTextureCoordinateFunction", "SoNode", "InventorNodes", PythonQtCreateObject<PythonQtWrapper_SoTextureCoordinateFunction>, SoNodeSetInstanceWrapperOnShell<PythonQtShell_SoTextureCoordinateFunction>, module, 0);
PythonQt::priv()->registerCPPClass("SoTextureCoordinatePlane", "SoTextureCoordinateFunction", "InventorNodes", PythonQtCreateObject<PythonQtWrapper_SoTextureCoordinatePlane>, SoNodeSetInstanceWrapperOnShell<PythonQtShell_SoTextureCoordinatePlane>, module, 0);
PythonQt::priv()->registerCPPClass("SoTransform", "SoTransformation", "InventorNodes", PythonQtCreateObject<PythonQtWrapper_SoTransform>, SoNodeSetInstanceWrapperOnShell<PythonQtShell_SoTransform>, module, 0);
PythonQt::priv()->registerCPPClass("SoTransformSeparator", "SoGroup", "InventorNodes", PythonQtCreateObject<PythonQtWrapper_SoTransformSeparator>, SoNodeSetInstanceWrapperOnShell<PythonQtShell_SoTransformSeparator>, module, 0);
PythonQt::priv()->registerCPPClass("SoTransformation", "SoNode", "InventorNodes", PythonQtCreateObject<PythonQtWrapper_SoTransformation>, SoNodeSetInstanceWrapperOnShell<PythonQtShell_SoTransformation>, module, 0);
PythonQt::priv()->registerCPPClass("SoTranslation", "SoTransformation", "InventorNodes", PythonQtCreateObject<PythonQtWrapper_SoTranslation>, SoNodeSetInstanceWrapperOnShell<PythonQtShell_SoTranslation>, module, 0);
PythonQt::priv()->registerCPPClass("SoTriangleStripSet", "SoNonIndexedShape", "InventorNodes", PythonQtCreateObject<PythonQtWrapper_SoTriangleStripSet>, SoNodeSetInstanceWrapperOnShell<PythonQtShell_SoTriangleStripSet>, module, 0);
PythonQt::priv()->registerCPPClass("SoUnits", "SoTransformation", "InventorNodes", PythonQtCreateObject<PythonQtWrapper_SoUnits>, SoNodeSetInstanceWrapperOnShell<PythonQtShell_SoUnits>, module, 0);
PythonQt::priv()->registerCPPClass("SoVertexProperty", "SoNode", "InventorNodes", PythonQtCreateObject<PythonQtWrapper_SoVertexProperty>, SoNodeSetInstanceWrapperOnShell<PythonQtShell_SoVertexProperty>, module, 0);
PythonQt::priv()->registerCPPClass("SoVertexShape", "SoShape", "InventorNodes", PythonQtCreateObject<PythonQtWrapper_SoVertexShape>, SoNodeSetInstanceWrapperOnShell<PythonQtShell_SoVertexShape>, module, 0);


}
