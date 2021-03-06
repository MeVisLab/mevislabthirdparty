/*************************************************************************************
**
** Copyright 2022, MeVis Medical Solutions AG
**
** GNU LESSER GENERAL PUBLIC LICENSE Version 2.1, February 1999
**
**************************************************************************************/
#include <PythonQt.h>
#include <PythonQtConversion.h>
#include "Inventor_elements0.h"
#include "Inventor_elements1.h"
#include "Inventor_elements2.h"



void PythonQt_init_InventorElements(PyObject* module) {
PythonQt::priv()->registerCPPClass("SoAccumulatedElement", "SoElement", "InventorElements", PythonQtCreateObject<PythonQtWrapper_SoAccumulatedElement>, PythonQtSetInstanceWrapperOnShell<PythonQtShell_SoAccumulatedElement>, module, 0);
PythonQt::priv()->registerCPPClass("SoBBoxModelMatrixElement", "SoModelMatrixElement", "InventorElements", PythonQtCreateObject<PythonQtWrapper_SoBBoxModelMatrixElement>, PythonQtSetInstanceWrapperOnShell<PythonQtShell_SoBBoxModelMatrixElement>, module, 0);
PythonQt::priv()->registerCPPClass("SoCacheElement", "SoElement", "InventorElements", PythonQtCreateObject<PythonQtWrapper_SoCacheElement>, PythonQtSetInstanceWrapperOnShell<PythonQtShell_SoCacheElement>, module, 0);
PythonQt::priv()->registerCPPClass("SoClipPlaneElement", "SoAccumulatedElement", "InventorElements", PythonQtCreateObject<PythonQtWrapper_SoClipPlaneElement>, PythonQtSetInstanceWrapperOnShell<PythonQtShell_SoClipPlaneElement>, module, 0);
PythonQt::priv()->registerCPPClass("SoComplexityElement", "SoFloatElement", "InventorElements", PythonQtCreateObject<PythonQtWrapper_SoComplexityElement>, PythonQtSetInstanceWrapperOnShell<PythonQtShell_SoComplexityElement>, module, 0);
PythonQt::priv()->registerCPPClass("SoComplexityTypeElement", "SoInt32Element", "InventorElements", PythonQtCreateObject<PythonQtWrapper_SoComplexityTypeElement>, PythonQtSetInstanceWrapperOnShell<PythonQtShell_SoComplexityTypeElement>, module, 0);
PythonQt::priv()->registerCPPClass("SoCoordinateElement", "SoReplacedElement", "InventorElements", PythonQtCreateObject<PythonQtWrapper_SoCoordinateElement>, PythonQtSetInstanceWrapperOnShell<PythonQtShell_SoCoordinateElement>, module, 0);
PythonQt::priv()->registerCPPClass("SoCreaseAngleElement", "SoFloatElement", "InventorElements", PythonQtCreateObject<PythonQtWrapper_SoCreaseAngleElement>, PythonQtSetInstanceWrapperOnShell<PythonQtShell_SoCreaseAngleElement>, module, 0);
PythonQt::priv()->registerCPPClass("SoDrawStyleElement", "SoInt32Element", "InventorElements", PythonQtCreateObject<PythonQtWrapper_SoDrawStyleElement>, PythonQtSetInstanceWrapperOnShell<PythonQtShell_SoDrawStyleElement>, module, 0);
PythonQt::priv()->registerCPPClass("SoElement", "", "InventorElements", PythonQtCreateObject<PythonQtWrapper_SoElement>, PythonQtSetInstanceWrapperOnShell<PythonQtShell_SoElement>, module, 0);
PythonQt::priv()->registerCPPClass("SoFloatElement", "SoElement", "InventorElements", PythonQtCreateObject<PythonQtWrapper_SoFloatElement>, PythonQtSetInstanceWrapperOnShell<PythonQtShell_SoFloatElement>, module, 0);
PythonQt::priv()->registerCPPClass("SoFocalDistanceElement", "SoFloatElement", "InventorElements", PythonQtCreateObject<PythonQtWrapper_SoFocalDistanceElement>, PythonQtSetInstanceWrapperOnShell<PythonQtShell_SoFocalDistanceElement>, module, 0);
PythonQt::priv()->registerCPPClass("SoFontNameElement", "SoReplacedElement", "InventorElements", PythonQtCreateObject<PythonQtWrapper_SoFontNameElement>, PythonQtSetInstanceWrapperOnShell<PythonQtShell_SoFontNameElement>, module, 0);
PythonQt::priv()->registerCPPClass("SoFontSizeElement", "SoFloatElement", "InventorElements", PythonQtCreateObject<PythonQtWrapper_SoFontSizeElement>, PythonQtSetInstanceWrapperOnShell<PythonQtShell_SoFontSizeElement>, module, 0);
PythonQt::priv()->registerCPPClass("SoGLCacheContextElement", "SoElement", "InventorElements", PythonQtCreateObject<PythonQtWrapper_SoGLCacheContextElement>, PythonQtSetInstanceWrapperOnShell<PythonQtShell_SoGLCacheContextElement>, module, 0);
PythonQt::priv()->registerCPPClass("SoGLClipPlaneElement", "SoClipPlaneElement", "InventorElements", PythonQtCreateObject<PythonQtWrapper_SoGLClipPlaneElement>, PythonQtSetInstanceWrapperOnShell<PythonQtShell_SoGLClipPlaneElement>, module, 0);
PythonQt::priv()->registerCPPClass("SoGLCoordinateElement", "SoCoordinateElement", "InventorElements", PythonQtCreateObject<PythonQtWrapper_SoGLCoordinateElement>, PythonQtSetInstanceWrapperOnShell<PythonQtShell_SoGLCoordinateElement>, module, 0);
PythonQt::priv()->registerCPPClass("SoGLDrawStyleElement", "SoDrawStyleElement", "InventorElements", PythonQtCreateObject<PythonQtWrapper_SoGLDrawStyleElement>, PythonQtSetInstanceWrapperOnShell<PythonQtShell_SoGLDrawStyleElement>, module, 0);
PythonQt::priv()->registerCPPClass("SoGLLazyElement", "SoLazyElement", "InventorElements", PythonQtCreateObject<PythonQtWrapper_SoGLLazyElement>, PythonQtSetInstanceWrapperOnShell<PythonQtShell_SoGLLazyElement>, module, 0);
PythonQt::priv()->registerCPPClass("SoGLLightIdElement", "SoInt32Element", "InventorElements", PythonQtCreateObject<PythonQtWrapper_SoGLLightIdElement>, PythonQtSetInstanceWrapperOnShell<PythonQtShell_SoGLLightIdElement>, module, 0);
PythonQt::priv()->registerCPPClass("SoGLLinePatternElement", "SoLinePatternElement", "InventorElements", PythonQtCreateObject<PythonQtWrapper_SoGLLinePatternElement>, PythonQtSetInstanceWrapperOnShell<PythonQtShell_SoGLLinePatternElement>, module, 0);
PythonQt::priv()->registerCPPClass("SoGLLineWidthElement", "SoLineWidthElement", "InventorElements", PythonQtCreateObject<PythonQtWrapper_SoGLLineWidthElement>, PythonQtSetInstanceWrapperOnShell<PythonQtShell_SoGLLineWidthElement>, module, 0);
PythonQt::priv()->registerCPPClass("SoGLModelMatrixElement", "SoModelMatrixElement", "InventorElements", PythonQtCreateObject<PythonQtWrapper_SoGLModelMatrixElement>, PythonQtSetInstanceWrapperOnShell<PythonQtShell_SoGLModelMatrixElement>, module, 0);
PythonQt::priv()->registerCPPClass("SoGLNormalElement", "SoNormalElement", "InventorElements", PythonQtCreateObject<PythonQtWrapper_SoGLNormalElement>, PythonQtSetInstanceWrapperOnShell<PythonQtShell_SoGLNormalElement>, module, 0);
PythonQt::priv()->registerCPPClass("SoGLPointSizeElement", "SoPointSizeElement", "InventorElements", PythonQtCreateObject<PythonQtWrapper_SoGLPointSizeElement>, PythonQtSetInstanceWrapperOnShell<PythonQtShell_SoGLPointSizeElement>, module, 0);
PythonQt::priv()->registerCPPClass("SoGLProjectionMatrixElement", "SoProjectionMatrixElement", "InventorElements", PythonQtCreateObject<PythonQtWrapper_SoGLProjectionMatrixElement>, PythonQtSetInstanceWrapperOnShell<PythonQtShell_SoGLProjectionMatrixElement>, module, 0);
PythonQt::priv()->registerCPPClass("SoGLRenderPassElement", "SoElement", "InventorElements", PythonQtCreateObject<PythonQtWrapper_SoGLRenderPassElement>, PythonQtSetInstanceWrapperOnShell<PythonQtShell_SoGLRenderPassElement>, module, 0);
PythonQt::priv()->registerCPPClass("SoGLShapeHintsElement", "SoShapeHintsElement", "InventorElements", PythonQtCreateObject<PythonQtWrapper_SoGLShapeHintsElement>, PythonQtSetInstanceWrapperOnShell<PythonQtShell_SoGLShapeHintsElement>, module, 0);
PythonQt::priv()->registerCPPClass("SoGLTextureCoordinateElement", "SoTextureCoordinateElement", "InventorElements", PythonQtCreateObject<PythonQtWrapper_SoGLTextureCoordinateElement>, PythonQtSetInstanceWrapperOnShell<PythonQtShell_SoGLTextureCoordinateElement>, module, 0);
PythonQt::priv()->registerCPPClass("SoGLTextureEnabledElement", "SoInt32Element", "InventorElements", PythonQtCreateObject<PythonQtWrapper_SoGLTextureEnabledElement>, PythonQtSetInstanceWrapperOnShell<PythonQtShell_SoGLTextureEnabledElement>, module, 0);
PythonQt::priv()->registerCPPClass("SoGLTextureImageElement", "SoTextureImageElement", "InventorElements", PythonQtCreateObject<PythonQtWrapper_SoGLTextureImageElement>, PythonQtSetInstanceWrapperOnShell<PythonQtShell_SoGLTextureImageElement>, module, 0);
PythonQt::priv()->registerCPPClass("SoGLTextureMatrixElement", "SoTextureMatrixElement", "InventorElements", PythonQtCreateObject<PythonQtWrapper_SoGLTextureMatrixElement>, PythonQtSetInstanceWrapperOnShell<PythonQtShell_SoGLTextureMatrixElement>, module, 0);
PythonQt::priv()->registerCPPClass("SoGLUpdateAreaElement", "SoElement", "InventorElements", PythonQtCreateObject<PythonQtWrapper_SoGLUpdateAreaElement>, PythonQtSetInstanceWrapperOnShell<PythonQtShell_SoGLUpdateAreaElement>, module, 0);
PythonQt::priv()->registerCPPClass("SoGLViewingMatrixElement", "SoViewingMatrixElement", "InventorElements", PythonQtCreateObject<PythonQtWrapper_SoGLViewingMatrixElement>, PythonQtSetInstanceWrapperOnShell<PythonQtShell_SoGLViewingMatrixElement>, module, 0);
PythonQt::priv()->registerCPPClass("SoGLViewportRegionElement", "SoViewportRegionElement", "InventorElements", PythonQtCreateObject<PythonQtWrapper_SoGLViewportRegionElement>, PythonQtSetInstanceWrapperOnShell<PythonQtShell_SoGLViewportRegionElement>, module, 0);
PythonQt::priv()->registerCPPClass("SoInt32Element", "SoElement", "InventorElements", PythonQtCreateObject<PythonQtWrapper_SoInt32Element>, PythonQtSetInstanceWrapperOnShell<PythonQtShell_SoInt32Element>, module, 0);
PythonQt::priv()->registerCPPClass("SoLazyElement", "SoElement", "InventorElements", PythonQtCreateObject<PythonQtWrapper_SoLazyElement>, PythonQtSetInstanceWrapperOnShell<PythonQtShell_SoLazyElement>, module, 0);
PythonQt::priv()->registerCPPClass("SoLightAttenuationElement", "SoReplacedElement", "InventorElements", PythonQtCreateObject<PythonQtWrapper_SoLightAttenuationElement>, PythonQtSetInstanceWrapperOnShell<PythonQtShell_SoLightAttenuationElement>, module, 0);
PythonQt::priv()->registerCPPClass("SoLinePatternElement", "SoInt32Element", "InventorElements", PythonQtCreateObject<PythonQtWrapper_SoLinePatternElement>, PythonQtSetInstanceWrapperOnShell<PythonQtShell_SoLinePatternElement>, module, 0);
PythonQt::priv()->registerCPPClass("SoLineWidthElement", "SoFloatElement", "InventorElements", PythonQtCreateObject<PythonQtWrapper_SoLineWidthElement>, PythonQtSetInstanceWrapperOnShell<PythonQtShell_SoLineWidthElement>, module, 0);
PythonQt::priv()->registerCPPClass("SoLocalBBoxMatrixElement", "SoElement", "InventorElements", PythonQtCreateObject<PythonQtWrapper_SoLocalBBoxMatrixElement>, PythonQtSetInstanceWrapperOnShell<PythonQtShell_SoLocalBBoxMatrixElement>, module, 0);
PythonQt::priv()->registerCPPClass("SoMaterialBindingElement", "SoInt32Element", "InventorElements", PythonQtCreateObject<PythonQtWrapper_SoMaterialBindingElement>, PythonQtSetInstanceWrapperOnShell<PythonQtShell_SoMaterialBindingElement>, module, 0);
PythonQt::priv()->registerCPPClass("SoModelMatrixElement", "SoAccumulatedElement", "InventorElements", PythonQtCreateObject<PythonQtWrapper_SoModelMatrixElement>, PythonQtSetInstanceWrapperOnShell<PythonQtShell_SoModelMatrixElement>, module, 0);
PythonQt::priv()->registerCPPClass("SoNormalBindingElement", "SoInt32Element", "InventorElements", PythonQtCreateObject<PythonQtWrapper_SoNormalBindingElement>, PythonQtSetInstanceWrapperOnShell<PythonQtShell_SoNormalBindingElement>, module, 0);
PythonQt::priv()->registerCPPClass("SoNormalElement", "SoReplacedElement", "InventorElements", PythonQtCreateObject<PythonQtWrapper_SoNormalElement>, PythonQtSetInstanceWrapperOnShell<PythonQtShell_SoNormalElement>, module, 0);
PythonQt::priv()->registerCPPClass("SoOverrideElement", "SoElement", "InventorElements", PythonQtCreateObject<PythonQtWrapper_SoOverrideElement>, PythonQtSetInstanceWrapperOnShell<PythonQtShell_SoOverrideElement>, module, 0);
PythonQt::priv()->registerCPPClass("SoPickRayElement", "SoElement", "InventorElements", PythonQtCreateObject<PythonQtWrapper_SoPickRayElement>, PythonQtSetInstanceWrapperOnShell<PythonQtShell_SoPickRayElement>, module, 0);
PythonQt::priv()->registerCPPClass("SoPickStyleElement", "SoInt32Element", "InventorElements", PythonQtCreateObject<PythonQtWrapper_SoPickStyleElement>, PythonQtSetInstanceWrapperOnShell<PythonQtShell_SoPickStyleElement>, module, 0);
PythonQt::priv()->registerCPPClass("SoPointSizeElement", "SoFloatElement", "InventorElements", PythonQtCreateObject<PythonQtWrapper_SoPointSizeElement>, PythonQtSetInstanceWrapperOnShell<PythonQtShell_SoPointSizeElement>, module, 0);
PythonQt::priv()->registerCPPClass("SoProfileCoordinateElement", "SoReplacedElement", "InventorElements", PythonQtCreateObject<PythonQtWrapper_SoProfileCoordinateElement>, PythonQtSetInstanceWrapperOnShell<PythonQtShell_SoProfileCoordinateElement>, module, 0);
PythonQt::priv()->registerCPPClass("SoProfileElement", "SoAccumulatedElement", "InventorElements", PythonQtCreateObject<PythonQtWrapper_SoProfileElement>, PythonQtSetInstanceWrapperOnShell<PythonQtShell_SoProfileElement>, module, 0);
PythonQt::priv()->registerCPPClass("SoProjectionMatrixElement", "SoReplacedElement", "InventorElements", PythonQtCreateObject<PythonQtWrapper_SoProjectionMatrixElement>, PythonQtSetInstanceWrapperOnShell<PythonQtShell_SoProjectionMatrixElement>, module, 0);
PythonQt::priv()->registerCPPClass("SoReplacedElement", "SoElement", "InventorElements", PythonQtCreateObject<PythonQtWrapper_SoReplacedElement>, PythonQtSetInstanceWrapperOnShell<PythonQtShell_SoReplacedElement>, module, 0);
PythonQt::priv()->registerCPPClass("SoShapeHintsElement", "SoElement", "InventorElements", PythonQtCreateObject<PythonQtWrapper_SoShapeHintsElement>, PythonQtSetInstanceWrapperOnShell<PythonQtShell_SoShapeHintsElement>, module, 0);
PythonQt::priv()->registerCPPClass("SoShapeStyleElement", "SoElement", "InventorElements", PythonQtCreateObject<PythonQtWrapper_SoShapeStyleElement>, PythonQtSetInstanceWrapperOnShell<PythonQtShell_SoShapeStyleElement>, module, 0);
PythonQt::priv()->registerCPPClass("SoSwitchElement", "SoInt32Element", "InventorElements", PythonQtCreateObject<PythonQtWrapper_SoSwitchElement>, PythonQtSetInstanceWrapperOnShell<PythonQtShell_SoSwitchElement>, module, 0);
PythonQt::priv()->registerCPPClass("SoTextureCoordinateBindingElement", "SoInt32Element", "InventorElements", PythonQtCreateObject<PythonQtWrapper_SoTextureCoordinateBindingElement>, PythonQtSetInstanceWrapperOnShell<PythonQtShell_SoTextureCoordinateBindingElement>, module, 0);
PythonQt::priv()->registerCPPClass("SoTextureCoordinateElement", "SoReplacedElement", "InventorElements", PythonQtCreateObject<PythonQtWrapper_SoTextureCoordinateElement>, PythonQtSetInstanceWrapperOnShell<PythonQtShell_SoTextureCoordinateElement>, module, 0);
PythonQt::priv()->registerCPPClass("SoTextureImageElement", "SoReplacedElement", "InventorElements", PythonQtCreateObject<PythonQtWrapper_SoTextureImageElement>, PythonQtSetInstanceWrapperOnShell<PythonQtShell_SoTextureImageElement>, module, 0);
PythonQt::priv()->registerCPPClass("SoTextureMatrixElement", "SoAccumulatedElement", "InventorElements", PythonQtCreateObject<PythonQtWrapper_SoTextureMatrixElement>, PythonQtSetInstanceWrapperOnShell<PythonQtShell_SoTextureMatrixElement>, module, 0);
PythonQt::priv()->registerCPPClass("SoTextureQualityElement", "SoFloatElement", "InventorElements", PythonQtCreateObject<PythonQtWrapper_SoTextureQualityElement>, PythonQtSetInstanceWrapperOnShell<PythonQtShell_SoTextureQualityElement>, module, 0);
PythonQt::priv()->registerCPPClass("SoUnitsElement", "SoInt32Element", "InventorElements", PythonQtCreateObject<PythonQtWrapper_SoUnitsElement>, PythonQtSetInstanceWrapperOnShell<PythonQtShell_SoUnitsElement>, module, 0);
PythonQt::priv()->registerCPPClass("SoViewVolumeElement", "SoReplacedElement", "InventorElements", PythonQtCreateObject<PythonQtWrapper_SoViewVolumeElement>, PythonQtSetInstanceWrapperOnShell<PythonQtShell_SoViewVolumeElement>, module, 0);
PythonQt::priv()->registerCPPClass("SoViewingMatrixElement", "SoReplacedElement", "InventorElements", PythonQtCreateObject<PythonQtWrapper_SoViewingMatrixElement>, PythonQtSetInstanceWrapperOnShell<PythonQtShell_SoViewingMatrixElement>, module, 0);
PythonQt::priv()->registerCPPClass("SoViewportRegionElement", "SoElement", "InventorElements", PythonQtCreateObject<PythonQtWrapper_SoViewportRegionElement>, PythonQtSetInstanceWrapperOnShell<PythonQtShell_SoViewportRegionElement>, module, 0);


}
