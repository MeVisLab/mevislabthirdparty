cmake_minimum_required(VERSION 3.14)
project(Inventor VERSION 2.5.1)

# prefer the legacy libGL library instead of GLVND
set(OpenGL_GL_PREFERENCE LEGACY)

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup(TARGETS)

set(_UNUSED ${CMAKE_DEBUG_POSTFIX} ${CMAKE_EXPORT_NO_PACKAGE_REGISTRY} ${CMAKE_INSTALL_BINDIR} ${CMAKE_INSTALL_DATAROOTDIR} ${CMAKE_INSTALL_INCLUDEDIR} ${CMAKE_INSTALL_LIBDIR} ${CMAKE_INSTALL_LIBEXECDIR} ${CMAKE_INSTALL_OLDINCLUDEDIR} ${CMAKE_INSTALL_SBINDIR})

find_package(BISON 2.1 REQUIRED)
find_package(OpenGL 2.1 REQUIRED)

if(UNIX AND NOT APPLE)
    find_package(Freetype REQUIRED)
    add_definitions(-DLINUX)
endif()

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

###############################################################################
# fl
###############################################################################

add_library(FL STATIC "")
add_library(FL::FL ALIAS FL)
target_sources(FL PRIVATE
    FontLibrary/FLBitmap.h
    FontLibrary/FLContext.cpp
    FontLibrary/FLContext.h
    FontLibrary/FLEnums.h
    FontLibrary/FLFreetypeFont.cpp
    FontLibrary/FLFreetypeFont.h
    FontLibrary/FLFreetypeOutline.h
    FontLibrary/FLFreetypeOutline.cpp
    FontLibrary/FLScopeGuard.h
)

target_include_directories(FL SYSTEM PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/FontLibrary>
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/FontLibrary>
  $<INSTALL_INTERFACE:${MEVISLAB_INSTALL_INCLUDEDIR}/FontLibrary>
)

if (WIN32)
    add_definitions(-DNOMINMAX)
endif()

set_target_properties(FL PROPERTIES C_VISIBILITY_PRESET default)
set_target_properties(FL PROPERTIES CXX_VISIBILITY_PRESET default)
set_target_properties(FL PROPERTIES POSITION_INDEPENDENT_CODE ON)

target_compile_definitions(FL PRIVATE $<BUILD_INTERFACE:INVENTOR_EXPORTS>)

if(UNIX AND NOT APPLE)
    target_link_libraries(FL PUBLIC Freetype::Freetype)
else()
    target_link_libraries(FL PUBLIC CONAN_PKG::Freetype)
endif()

if (APPLE)
  find_library(CoreFoundation CoreFoundation)
  find_library(CoreText CoreText)
  target_link_libraries(FL PRIVATE ${CoreFoundation} ${CoreText})
endif()

# Disable all compiler warnings (FIXME)
if(CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  target_compile_options(FL PRIVATE "-Wno-everything")
elseif(CMAKE_CXX_COMPILER_ID MATCHES "GNU")
  target_compile_options(FL PRIVATE "-w")
elseif(CMAKE_CXX_COMPILER_ID MATCHES "MSVC")
  target_compile_options(FL PRIVATE "/w")
endif()


###############################################################################
#  ppp
###############################################################################

add_executable(ppp ${CMAKE_CURRENT_SOURCE_DIR}/tools/ppp/ppp.cpp)
target_include_directories(ppp PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/include")
target_compile_definitions(ppp PRIVATE $<BUILD_INTERFACE:INVENTOR_EXPORTS>)

if(WIN32)
  target_compile_definitions(ppp PRIVATE $<BUILD_INTERFACE:__SGIOIV_BUILD_DLL>)
endif()

# Disable all compiler warnings (FIXME)
if(CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  target_compile_options(ppp PRIVATE "-Wno-everything")
elseif(CMAKE_CXX_COMPILER_ID MATCHES "GNU")
  target_compile_options(ppp PRIVATE "-w")
elseif(CMAKE_CXX_COMPILER_ID MATCHES "MSVC")
  target_compile_options(ppp PRIVATE "/w")
endif()


###############################################################################
# Inventor
###############################################################################

add_library(Inventor "")
add_library(Inventor::Inventor ALIAS Inventor)
add_dependencies(Inventor ppp)

target_sources(Inventor PRIVATE
    include/Inventor/actions/SoAction.h
    include/Inventor/actions/SoActions.h
    include/Inventor/actions/SoBoxHighlightRenderAction.h
    include/Inventor/actions/SoCallbackAction.h
    include/Inventor/actions/SoGetBoundingBoxAction.h
    include/Inventor/actions/SoGetMatrixAction.h
    include/Inventor/actions/SoGLRenderAction.h
    include/Inventor/actions/SoHandleEventAction.h
    include/Inventor/actions/SoLineHighlightRenderAction.h
    include/Inventor/actions/SoPickAction.h
    include/Inventor/actions/SoRayPickAction.h
    include/Inventor/actions/SoSearchAction.h
    include/Inventor/actions/SoSubAction.h
    include/Inventor/actions/SoWriteAction.h
    include/Inventor/bundles/SoBundle.h
    include/Inventor/bundles/SoMaterialBundle.h
    include/Inventor/bundles/SoNormalBundle.h
    include/Inventor/bundles/SoTextureCoordinateBundle.h
    include/Inventor/caches/SoBoundingBoxCache.h
    include/Inventor/caches/SoCache.h
    include/Inventor/caches/SoGLCacheList.h
    include/Inventor/caches/SoGLRenderCache.h
    include/Inventor/caches/SoNormalCache.h
    include/Inventor/details/SoConeDetail.h
    include/Inventor/details/SoCubeDetail.h
    include/Inventor/details/SoCylinderDetail.h
    include/Inventor/details/SoDetail.h
    include/Inventor/details/SoDetails.h
    include/Inventor/details/SoFaceDetail.h
    include/Inventor/details/SoLineDetail.h
    include/Inventor/details/SoNodeKitDetail.h
    include/Inventor/details/SoPointDetail.h
    include/Inventor/details/SoSubDetail.h
    include/Inventor/details/SoTextDetail.h
    include/Inventor/draggers/SoCenterballDragger.h
    include/Inventor/draggers/SoDirectionalLightDragger.h
    include/Inventor/draggers/SoDragger.h
    include/Inventor/draggers/SoDragPointDragger.h
    include/Inventor/draggers/SoHandleBoxDragger.h
    include/Inventor/draggers/SoJackDragger.h
    include/Inventor/draggers/SoPointLightDragger.h
    include/Inventor/draggers/SoRotateCylindricalDragger.h
    include/Inventor/draggers/SoRotateDiscDragger.h
    include/Inventor/draggers/SoRotateSphericalDragger.h
    include/Inventor/draggers/SoScale1Dragger.h
    include/Inventor/draggers/SoScale2Dragger.h
    include/Inventor/draggers/SoScale2UniformDragger.h
    include/Inventor/draggers/SoScaleUniformDragger.h
    include/Inventor/draggers/SoSpotLightDragger.h
    include/Inventor/draggers/SoTabBoxDragger.h
    include/Inventor/draggers/SoTabPlaneDragger.h
    include/Inventor/draggers/SoTrackballDragger.h
    include/Inventor/draggers/SoTransformBoxDragger.h
    include/Inventor/draggers/SoTransformerDragger.h
    include/Inventor/draggers/SoTranslate1Dragger.h
    include/Inventor/draggers/SoTranslate2Dragger.h
    include/Inventor/elements/SoAccumulatedElement.h
    include/Inventor/elements/SoAmbientColorElement.h
    include/Inventor/elements/SoBBoxModelMatrixElement.h
    include/Inventor/elements/SoCacheElement.h
    include/Inventor/elements/SoClipPlaneElement.h
    include/Inventor/elements/SoComplexityElement.h
    include/Inventor/elements/SoComplexityTypeElement.h
    include/Inventor/elements/SoCoordinateElement.h
    include/Inventor/elements/SoCreaseAngleElement.h
    include/Inventor/elements/SoCullVolumeElement.h
    include/Inventor/elements/SoCurrentGLMaterialElement.h
    include/Inventor/elements/SoDiffuseColorElement.h
    include/Inventor/elements/SoDrawStyleElement.h
    include/Inventor/elements/SoElement.h
    include/Inventor/elements/SoElements.h
    include/Inventor/elements/SoEmissiveColorElement.h
    include/Inventor/elements/SoFloatElement.h
    include/Inventor/elements/SoFocalDistanceElement.h
    include/Inventor/elements/SoFontNameElement.h
    include/Inventor/elements/SoFontSizeElement.h
    include/Inventor/elements/SoGLAmbientColorElement.h
    include/Inventor/elements/SoGLCacheContextElement.h
    include/Inventor/elements/SoGLClipPlaneElement.h
    include/Inventor/elements/SoGLCoordinateElement.h
    include/Inventor/elements/SoGLDiffuseColorElement.h
    include/Inventor/elements/SoGLDrawStyleElement.h
    include/Inventor/elements/SoGLEmissiveColorElement.h
    include/Inventor/elements/SoGLLazyElement.h
    include/Inventor/elements/SoGLLightIdElement.h
    include/Inventor/elements/SoGLLightModelElement.h
    include/Inventor/elements/SoGLLinePatternElement.h
    include/Inventor/elements/SoGLLineWidthElement.h
    include/Inventor/elements/SoGLModelMatrixElement.h
    include/Inventor/elements/SoGLNormalElement.h
    include/Inventor/elements/SoGLPointSizeElement.h
    include/Inventor/elements/SoGLPolygonOffsetElement.h
    include/Inventor/elements/SoGLPolygonStippleElement.h
    include/Inventor/elements/SoGLProjectionMatrixElement.h
    include/Inventor/elements/SoGLRenderPassElement.h
    include/Inventor/elements/SoGLShapeHintsElement.h
    include/Inventor/elements/SoGLShininessElement.h
    include/Inventor/elements/SoGLSpecularColorElement.h
    include/Inventor/elements/SoGLStencilBitsElement.h
    include/Inventor/elements/SoGLTextureBlendColorElement.h
    include/Inventor/elements/SoGLTextureCoordinateElement.h
    include/Inventor/elements/SoGLTextureEnabledElement.h
    include/Inventor/elements/SoGLTextureImageElement.h
    include/Inventor/elements/SoGLTextureMatrixElement.h
    include/Inventor/elements/SoGLTextureModelElement.h
    include/Inventor/elements/SoGLTextureQualityElement.h
    include/Inventor/elements/SoGLTextureWrapSElement.h
    include/Inventor/elements/SoGLTextureWrapTElement.h
    include/Inventor/elements/SoGLUpdateAreaElement.h
    include/Inventor/elements/SoGLVBOElement.h
    include/Inventor/elements/SoGLViewingMatrixElement.h
    include/Inventor/elements/SoGLViewportRegionElement.h
    include/Inventor/elements/SoInt32Element.h
    include/Inventor/elements/SoLazyElement.h
    include/Inventor/elements/SoLightAttenuationElement.h
    include/Inventor/elements/SoLightModelElement.h
    include/Inventor/elements/SoLinePatternElement.h
    include/Inventor/elements/SoLineWidthElement.h
    include/Inventor/elements/SoLocalBBoxMatrixElement.h
    include/Inventor/elements/SoLongElement.h
    include/Inventor/elements/SoMaterialBindingElement.h
    include/Inventor/elements/SoModelMatrixElement.h
    include/Inventor/elements/SoNormalBindingElement.h
    include/Inventor/elements/SoNormalElement.h
    include/Inventor/elements/SoOverrideElement.h
    include/Inventor/elements/SoPickRayElement.h
    include/Inventor/elements/SoPickStyleElement.h
    include/Inventor/elements/SoPointSizeElement.h
    include/Inventor/elements/SoPolygonOffsetElement.h
    include/Inventor/elements/SoProfileCoordinateElement.h
    include/Inventor/elements/SoProfileElement.h
    include/Inventor/elements/SoProjectionMatrixElement.h
    include/Inventor/elements/SoReplacedElement.h
    include/Inventor/elements/SoShapeHintsElement.h
    include/Inventor/elements/SoShapeStyleElement.h
    include/Inventor/elements/SoShininessElement.h
    include/Inventor/elements/SoSpecularColorElement.h
    include/Inventor/elements/SoStencilBitsElement.h
    include/Inventor/elements/SoSubElement.h
    include/Inventor/elements/SoSwitchElement.h
    include/Inventor/elements/SoTextureBlendColorElement.h
    include/Inventor/elements/SoTextureCoordinateBindingElement.h
    include/Inventor/elements/SoTextureCoordinateElement.h
    include/Inventor/elements/SoTextureImageElement.h
    include/Inventor/elements/SoTextureMatrixElement.h
    include/Inventor/elements/SoTextureModelElement.h
    include/Inventor/elements/SoTextureQualityElement.h
    include/Inventor/elements/SoTextureWrapSElement.h
    include/Inventor/elements/SoTextureWrapTElement.h
    include/Inventor/elements/SoTransparencyElement.h
    include/Inventor/elements/SoUnitsElement.h
    include/Inventor/elements/SoViewingMatrixElement.h
    include/Inventor/elements/SoViewportRegionElement.h
    include/Inventor/elements/SoViewVolumeElement.h
    include/Inventor/elements/SoWindowElement.h
    include/Inventor/engines/SoBoolOperation.h
    include/Inventor/engines/SoCalculator.h
    include/Inventor/engines/SoCompose.h
    include/Inventor/engines/SoComputeBoundingBox.h
    include/Inventor/engines/SoConcatenate.h
    include/Inventor/engines/SoCounter.h
    include/Inventor/engines/SoElapsedTime.h
    include/Inventor/engines/SoEngine.h
    include/Inventor/engines/SoEngines.h
    include/Inventor/engines/SoFieldConverter.h
    include/Inventor/engines/SoGate.h
    include/Inventor/engines/SoInterpolate.h
    include/Inventor/engines/SoOneShot.h
    include/Inventor/engines/SoOnOff.h
    include/Inventor/engines/SoOutputData.h
    include/Inventor/engines/SoSelectOne.h
    include/Inventor/engines/SoSubEngine.h
    include/Inventor/engines/SoTimeCounter.h
    include/Inventor/engines/SoTransformVec3f.h
    include/Inventor/engines/SoTriggerAny.h
    include/Inventor/errors/SoDebugError.h
    include/Inventor/errors/SoError.h
    include/Inventor/errors/SoErrors.h
    include/Inventor/errors/SoMemoryError.h
    include/Inventor/errors/SoReadError.h
    include/Inventor/events/SoButtonEvent.h
    include/Inventor/events/SoEnterLeaveEvent.h
    include/Inventor/events/SoEvent.h
    include/Inventor/events/SoEvents.h
    include/Inventor/events/SoKeyboardEvent.h
    include/Inventor/events/SoLocation2Event.h
    include/Inventor/events/SoLocation2RefreshEvent.h
    include/Inventor/events/SoMotion3Event.h
    include/Inventor/events/SoMouseButtonEvent.h
    include/Inventor/events/SoMouseWheelEvent.h
    include/Inventor/events/SoSpaceballButtonEvent.h
    include/Inventor/events/SoSubEvent.h
    include/Inventor/fields/SoField.h
    include/Inventor/fields/SoFieldContainer.h
    include/Inventor/fields/SoFieldData.h
    include/Inventor/fields/SoFields.h
    include/Inventor/fields/SoMFBitMask.h
    include/Inventor/fields/SoMFBool.h
    include/Inventor/fields/SoMFColor.h
    include/Inventor/fields/SoMFDouble.h
    include/Inventor/fields/SoMFEngine.h
    include/Inventor/fields/SoMFEnum.h
    include/Inventor/fields/SoMFFloat.h
    include/Inventor/fields/SoMFInt32.h
    include/Inventor/fields/SoMFLong.h
    include/Inventor/fields/SoMFMatrix.h
    include/Inventor/fields/SoMFMatrixd.h
    include/Inventor/fields/SoMFName.h
    include/Inventor/fields/SoMFNode.h
    include/Inventor/fields/SoMFPath.h
    include/Inventor/fields/SoMFPlane.h
    include/Inventor/fields/SoMFPlaned.h
    include/Inventor/fields/SoMFRotation.h
    include/Inventor/fields/SoMFRotationd.h
    include/Inventor/fields/SoMFShort.h
    include/Inventor/fields/SoMFString.h
    include/Inventor/fields/SoMFTime.h
    include/Inventor/fields/SoMFUInt32.h
    include/Inventor/fields/SoMFULong.h
    include/Inventor/fields/SoMFUShort.h
    include/Inventor/fields/SoMFVec2d.h
    include/Inventor/fields/SoMFVec2f.h
    include/Inventor/fields/SoMFVec3d.h
    include/Inventor/fields/SoMFVec3f.h
    include/Inventor/fields/SoMFVec4d.h
    include/Inventor/fields/SoMFVec4f.h
    include/Inventor/fields/SoSFBitMask.h
    include/Inventor/fields/SoSFBool.h
    include/Inventor/fields/SoSFColor.h
    include/Inventor/fields/SoSFDouble.h
    include/Inventor/fields/SoSFEngine.h
    include/Inventor/fields/SoSFEnum.h
    include/Inventor/fields/SoSFFloat.h
    include/Inventor/fields/SoSFImage.h
    include/Inventor/fields/SoSFInt32.h
    include/Inventor/fields/SoSFLong.h
    include/Inventor/fields/SoSFMatrix.h
    include/Inventor/fields/SoSFMatrixd.h
    include/Inventor/fields/SoSFName.h
    include/Inventor/fields/SoSFNode.h
    include/Inventor/fields/SoSFPath.h
    include/Inventor/fields/SoSFPlane.h
    include/Inventor/fields/SoSFPlaned.h
    include/Inventor/fields/SoSFRotation.h
    include/Inventor/fields/SoSFRotationd.h
    include/Inventor/fields/SoSFShort.h
    include/Inventor/fields/SoSFString.h
    include/Inventor/fields/SoSFTime.h
    include/Inventor/fields/SoSFTrigger.h
    include/Inventor/fields/SoSFUInt32.h
    include/Inventor/fields/SoSFULong.h
    include/Inventor/fields/SoSFUShort.h
    include/Inventor/fields/SoSFVec2d.h
    include/Inventor/fields/SoSFVec2f.h
    include/Inventor/fields/SoSFVec2s.h
    include/Inventor/fields/SoSFVec3d.h
    include/Inventor/fields/SoSFVec3f.h
    include/Inventor/fields/SoSFVec3s.h
    include/Inventor/fields/SoSFVec4d.h
    include/Inventor/fields/SoSFVec4f.h
    include/Inventor/fields/SoSubField.h
    include/Inventor/manips/SoCenterballManip.h
    include/Inventor/manips/SoDirectionalLightManip.h
    include/Inventor/manips/SoHandleBoxManip.h
    include/Inventor/manips/SoJackManip.h
    include/Inventor/manips/SoPointLightManip.h
    include/Inventor/manips/SoSpotLightManip.h
    include/Inventor/manips/SoTabBoxManip.h
    include/Inventor/manips/SoTrackballManip.h
    include/Inventor/manips/SoTransformBoxManip.h
    include/Inventor/manips/SoTransformerManip.h
    include/Inventor/manips/SoTransformManip.h
    include/Inventor/misc/SoAuditorList.h
    include/Inventor/misc/SoBase.h
    include/Inventor/misc/SoBasic.h
    include/Inventor/misc/SoByteStream.h
    include/Inventor/misc/SoCallbackList.h
    include/Inventor/misc/SoChildList.h
    include/Inventor/misc/SoCompactPathList.h
    include/Inventor/misc/SoNormalGenerator.h
    include/Inventor/misc/SoNotification.h
    include/Inventor/misc/SoRef.h
    include/Inventor/misc/SoState.h
    include/Inventor/misc/SoTempPath.h
    include/Inventor/misc/SoTranscribe.h
    include/Inventor/misc/SoVBO.h
    include/Inventor/misc/SoVertexArrayIndexer.h
    include/Inventor/misc/upgraders/SoUpgrader.h
    include/Inventor/misc/upgraders/SoV1AppearanceKit.h
    include/Inventor/misc/upgraders/SoV1BaseKit.h
    include/Inventor/misc/upgraders/SoV1CameraKit.h
    include/Inventor/misc/upgraders/SoV1ConeKit.h
    include/Inventor/misc/upgraders/SoV1CubeKit.h
    include/Inventor/misc/upgraders/SoV1CustomNode.h
    include/Inventor/misc/upgraders/SoV1CylinderKit.h
    include/Inventor/misc/upgraders/SoV1DirectionalLightKit.h
    include/Inventor/misc/upgraders/SoV1FaceSetKit.h
    include/Inventor/misc/upgraders/SoV1GroupKit.h
    include/Inventor/misc/upgraders/SoV1IndexedFaceSetKit.h
    include/Inventor/misc/upgraders/SoV1IndexedLineSetKit.h
    include/Inventor/misc/upgraders/SoV1IndexedNurbsCurveKit.h
    include/Inventor/misc/upgraders/SoV1IndexedNurbsSurfaceKit.h
    include/Inventor/misc/upgraders/SoV1IndexedTriangleMeshKit.h
    include/Inventor/misc/upgraders/SoV1LightKit.h
    include/Inventor/misc/upgraders/SoV1LineSetKit.h
    include/Inventor/misc/upgraders/SoV1NodeKit.h
    include/Inventor/misc/upgraders/SoV1NodekitCatalog.h
    include/Inventor/misc/upgraders/SoV1NodekitParts.h
    include/Inventor/misc/upgraders/SoV1NurbsCurveKit.h
    include/Inventor/misc/upgraders/SoV1NurbsSurfaceKit.h
    include/Inventor/misc/upgraders/SoV1OrthographicCameraKit.h
    include/Inventor/misc/upgraders/SoV1PerspectiveCameraKit.h
    include/Inventor/misc/upgraders/SoV1PointLightKit.h
    include/Inventor/misc/upgraders/SoV1PointSetKit.h
    include/Inventor/misc/upgraders/SoV1QuadMeshKit.h
    include/Inventor/misc/upgraders/SoV1SceneKit.h
    include/Inventor/misc/upgraders/SoV1ShapeKit.h
    include/Inventor/misc/upgraders/SoV1SphereKit.h
    include/Inventor/misc/upgraders/SoV1SpotLightKit.h
    include/Inventor/misc/upgraders/SoV1SubKit.h
    include/Inventor/misc/upgraders/SoV1Text2Kit.h
    include/Inventor/misc/upgraders/SoV1Text3Kit.h
    include/Inventor/misc/upgraders/SoV1TriangleStripSetKit.h
    include/Inventor/misc/upgraders/SoV1VertexShapeKit.h
    include/Inventor/misc/upgraders/SoV1WrapperKit.h
    include/Inventor/nodekits/SoAppearanceKit.h
    include/Inventor/nodekits/SoBaseKit.h
    include/Inventor/nodekits/SoCameraKit.h
    include/Inventor/nodekits/SoInteractionKit.h
    include/Inventor/nodekits/SoLightKit.h
    include/Inventor/nodekits/SoNodeKit.h
    include/Inventor/nodekits/SoNodekitCatalog.h
    include/Inventor/nodekits/SoNodeKitListPart.h
    include/Inventor/nodekits/SoNodekitParts.h
    include/Inventor/nodekits/SoSceneKit.h
    include/Inventor/nodekits/SoSeparatorKit.h
    include/Inventor/nodekits/SoShapeKit.h
    include/Inventor/nodekits/SoSubKit.h
    include/Inventor/nodekits/SoWrapperKit.h
    include/Inventor/nodes/SoAnnotation.h
    include/Inventor/nodes/SoAntiSquish.h
    include/Inventor/nodes/SoArray.h
    include/Inventor/nodes/SoAsciiText.h
    include/Inventor/nodes/SoBaseColor.h
    include/Inventor/nodes/SoBlinker.h
    include/Inventor/nodes/SoCallback.h
    include/Inventor/nodes/SoCamera.h
    include/Inventor/nodes/SoClipPlane.h
    include/Inventor/nodes/SoComplexity.h
    include/Inventor/nodes/SoCone.h
    include/Inventor/nodes/SoCoordinate3.h
    include/Inventor/nodes/SoCoordinate4.h
    include/Inventor/nodes/SoCube.h
    include/Inventor/nodes/SoCylinder.h
    include/Inventor/nodes/SoDirectionalLight.h
    include/Inventor/nodes/SoDrawStyle.h
    include/Inventor/nodes/SoEnvironment.h
    include/Inventor/nodes/SoEventCallback.h
    include/Inventor/nodes/SoFaceSet.h
    include/Inventor/nodes/SoFile.h
    include/Inventor/nodes/SoFont.h
    include/Inventor/nodes/SoFontStyle.h
    include/Inventor/nodes/SoGroup.h
    include/Inventor/nodes/SoIndexedFaceSet.h
    include/Inventor/nodes/SoIndexedLineSet.h
    include/Inventor/nodes/SoIndexedNurbsCurve.h
    include/Inventor/nodes/SoIndexedNurbsSurface.h
    include/Inventor/nodes/SoIndexedShape.h
    include/Inventor/nodes/SoIndexedTriangleSet.h
    include/Inventor/nodes/SoIndexedTriangleStripSet.h
    include/Inventor/nodes/SoInfo.h
    include/Inventor/nodes/SoLabel.h
    include/Inventor/nodes/SoLevelOfDetail.h
    include/Inventor/nodes/SoLight.h
    include/Inventor/nodes/SoLightModel.h
    include/Inventor/nodes/SoLinearProfile.h
    include/Inventor/nodes/SoLineSet.h
    include/Inventor/nodes/SoLocateHighlight.h
    include/Inventor/nodes/SoLOD.h
    include/Inventor/nodes/SoMaterial.h
    include/Inventor/nodes/SoMaterialBinding.h
    include/Inventor/nodes/SoMaterialIndex.h
    include/Inventor/nodes/SoMatrixTransform.h
    include/Inventor/nodes/SoMultipleCopy.h
    include/Inventor/nodes/SoNode.h
    include/Inventor/nodes/SoNodes.h
    include/Inventor/nodes/SoNonIndexedShape.h
    include/Inventor/nodes/SoNormal.h
    include/Inventor/nodes/SoNormalBinding.h
    include/Inventor/nodes/SoNurbsCurve.h
    include/Inventor/nodes/SoNurbsProfile.h
    include/Inventor/nodes/SoNurbsSurface.h
    include/Inventor/nodes/SoOrthographicCamera.h
    include/Inventor/nodes/SoPackedColor.h
    include/Inventor/nodes/SoPathSwitch.h
    include/Inventor/nodes/SoPendulum.h
    include/Inventor/nodes/SoPerspectiveCamera.h
    include/Inventor/nodes/SoPickStyle.h
    include/Inventor/nodes/SoPointLight.h
    include/Inventor/nodes/SoPointSet.h
    include/Inventor/nodes/SoPolygonOffset.h
    include/Inventor/nodes/SoProfile.h
    include/Inventor/nodes/SoProfileCoordinate2.h
    include/Inventor/nodes/SoProfileCoordinate3.h
    include/Inventor/nodes/SoQuadMesh.h
    include/Inventor/nodes/SoResetTransform.h
    include/Inventor/nodes/SoRotation.h
    include/Inventor/nodes/SoRotationXYZ.h
    include/Inventor/nodes/SoRotor.h
    include/Inventor/nodes/SoScale.h
    include/Inventor/nodes/SoSelection.h
    include/Inventor/nodes/SoSeparator.h
    include/Inventor/nodes/SoShape.h
    include/Inventor/nodes/SoShapeHints.h
    include/Inventor/nodes/SoShuttle.h
    include/Inventor/nodes/SoSphere.h
    include/Inventor/nodes/SoSpotLight.h
    include/Inventor/nodes/SoSubNode.h
    include/Inventor/nodes/SoSurroundScale.h
    include/Inventor/nodes/SoSwitch.h
    include/Inventor/nodes/SoText2.h
    include/Inventor/nodes/SoText3.h
    include/Inventor/nodes/SoTexture2.h
    include/Inventor/nodes/SoTexture2Transform.h
    include/Inventor/nodes/SoTextureCoordinate2.h
    include/Inventor/nodes/SoTextureCoordinateBinding.h
    include/Inventor/nodes/SoTextureCoordinateDefault.h
    include/Inventor/nodes/SoTextureCoordinateEnvironment.h
    include/Inventor/nodes/SoTextureCoordinateFunction.h
    include/Inventor/nodes/SoTextureCoordinatePlane.h
    include/Inventor/nodes/SoTransform.h
    include/Inventor/nodes/SoTransformation.h
    include/Inventor/nodes/SoTransformSeparator.h
    include/Inventor/nodes/SoTranslation.h
    include/Inventor/nodes/SoTriangleStripSet.h
    include/Inventor/nodes/SoUnits.h
    include/Inventor/nodes/SoVertexProperty.h
    include/Inventor/nodes/SoVertexShape.h
    include/Inventor/nodes/SoWWWAnchor.h
    include/Inventor/nodes/SoWWWInline.h
    include/Inventor/projectors/SbCylinderPlaneProjector.h
    include/Inventor/projectors/SbCylinderProjector.h
    include/Inventor/projectors/SbCylinderSectionProjector.h
    include/Inventor/projectors/SbCylinderSheetProjector.h
    include/Inventor/projectors/SbLineProjector.h
    include/Inventor/projectors/SbPlaneProjector.h
    include/Inventor/projectors/SbProjector.h
    include/Inventor/projectors/SbProjectors.h
    include/Inventor/projectors/SbSpherePlaneProjector.h
    include/Inventor/projectors/SbSphereProjector.h
    include/Inventor/projectors/SbSphereSectionProjector.h
    include/Inventor/projectors/SbSphereSheetProjector.h
    include/Inventor/Sb.h
    include/Inventor/SbBasic.h
    include/Inventor/SbBox.h
    include/Inventor/SbBoxd.h
    include/Inventor/SbColor.h
    include/Inventor/SbDict.h
    include/Inventor/SbLinear.h
    include/Inventor/SbLineard.h
    include/Inventor/SbPList.h
    include/Inventor/SbString.h
    include/Inventor/SbTime.h
    include/Inventor/SbTypeDefs.h
    include/Inventor/SbViewportRegion.h
    include/Inventor/sensors/SoAlarmSensor.h
    include/Inventor/sensors/SoDataSensor.h
    include/Inventor/sensors/SoDelayQueueSensor.h
    include/Inventor/sensors/SoFieldSensor.h
    include/Inventor/sensors/SoIdleSensor.h
    include/Inventor/sensors/SoNodeSensor.h
    include/Inventor/sensors/SoOneShotSensor.h
    include/Inventor/sensors/SoPathSensor.h
    include/Inventor/sensors/SoSensor.h
    include/Inventor/sensors/SoSensorManager.h
    include/Inventor/sensors/SoSensors.h
    include/Inventor/sensors/SoTimerQueueSensor.h
    include/Inventor/sensors/SoTimerSensor.h
    include/Inventor/So.h
    include/Inventor/SoCatch.h
    include/Inventor/SoDB.h
    include/Inventor/SoDebug.h
    include/Inventor/SoInput.h
    include/Inventor/SoInteraction.h
    include/Inventor/SoInventor.h
    include/Inventor/SoLists.h
    include/Inventor/SoMachine.h
    include/Inventor/SoNodeKitPath.h
    include/Inventor/SoOutput.h
    include/Inventor/SoPath.h
    include/Inventor/SoPickedPoint.h
    include/Inventor/SoPrimitiveVertex.h
    include/Inventor/SoProfiling.h
    include/Inventor/SoSceneManager.h
    include/Inventor/SoTrace.h
    include/Inventor/SoType.h
    include/Inventor/system/SbConfig.h
    include/Inventor/system/SbOpenGL.h
    include/Inventor/system/SbOpenGLU.h
    include/Inventor/system/SbSystem.h
    include/SoUnknownEngine.h
    include/SoUnknownNode.h
    source/actions/SoAction.cpp
    source/actions/SoActionInit.cpp
    source/actions/SoBoxHighlightRenderAction.cpp
    source/actions/SoCallbackAction.cpp
    source/actions/SoGetBoundingBoxAction.cpp
    source/actions/SoGetMatrixAction.cpp
    source/actions/SoGLRenderAction.cpp
    source/actions/SoHandleEventAction.cpp
    source/actions/SoLineHighlightRenderAction.cpp
    source/actions/SoPickAction.cpp
    source/actions/SoRayPickAction.cpp
    source/actions/SoSearchAction.cpp
    source/actions/SoWriteAction.cpp
    source/bundles/SoMaterialBundle.cpp
    source/bundles/SoNormalBundle.cpp
    source/bundles/SoTextureCoordinateBundle.cpp
    source/caches/SoBoundingBoxCache.cpp
    source/caches/SoCache.cpp
    source/caches/SoGLCacheList.cpp
    source/caches/SoGLRenderCache.cpp
    source/caches/SoNormalCache.cpp
    source/details/SoConeDetail.cpp
    source/details/SoCubeDetail.cpp
    source/details/SoCylinderDetail.cpp
    source/details/SoDetail.cpp
    source/details/SoDetailInit.cpp
    source/details/SoFaceDetail.cpp
    source/details/SoLineDetail.cpp
    source/details/SoNodeKitDetail.cpp
    source/details/SoPointDetail.cpp
    source/details/SoTextDetail.cpp
    source/draggers/geom/SoCenterballDraggerGeom.h
    source/draggers/geom/SoDirectionalLightDraggerGeom.h
    source/draggers/geom/SoDragPointDraggerGeom.h
    source/draggers/geom/SoHandleBoxDraggerGeom.h
    source/draggers/geom/SoJackDraggerGeom.h
    source/draggers/geom/SoPointLightDraggerGeom.h
    source/draggers/geom/SoRotateCylindricalDraggerGeom.h
    source/draggers/geom/SoRotateDiscDraggerGeom.h
    source/draggers/geom/SoRotateSphericalDraggerGeom.h
    source/draggers/geom/SoScale1DraggerGeom.h
    source/draggers/geom/SoScale2DraggerGeom.h
    source/draggers/geom/SoScale2UniformDraggerGeom.h
    source/draggers/geom/SoScaleUniformDraggerGeom.h
    source/draggers/geom/SoSpotLightDraggerGeom.h
    source/draggers/geom/SoTabBoxDraggerGeom.h
    source/draggers/geom/SoTabPlaneDraggerGeom.h
    source/draggers/geom/SoTrackballDraggerGeom.h
    source/draggers/geom/SoTransformBoxDraggerGeom.h
    source/draggers/geom/SoTransformerDraggerGeom.h
    source/draggers/geom/SoTranslate1DraggerGeom.h
    source/draggers/geom/SoTranslate2DraggerGeom.h
    source/draggers/SoCenterballDragger.cpp
    source/draggers/SoDirectionalLightDragger.cpp
    source/draggers/SoDragger.cpp
    source/draggers/SoDraggerInit.cpp
    source/draggers/SoDragPointDragger.cpp
    source/draggers/SoHandleBoxDragger.cpp
    source/draggers/SoJackDragger.cpp
    source/draggers/SoPointLightDragger.cpp
    source/draggers/SoRotateCylindricalDragger.cpp
    source/draggers/SoRotateDiscDragger.cpp
    source/draggers/SoRotateSphericalDragger.cpp
    source/draggers/SoScale1Dragger.cpp
    source/draggers/SoScale2Dragger.cpp
    source/draggers/SoScale2UniformDragger.cpp
    source/draggers/SoScaleUniformDragger.cpp
    source/draggers/SoSpotLightDragger.cpp
    source/draggers/SoTabBoxDragger.cpp
    source/draggers/SoTabPlaneDragger.cpp
    source/draggers/SoTrackballDragger.cpp
    source/draggers/SoTransformBoxDragger.cpp
    source/draggers/SoTransformerDragger.cpp
    source/draggers/SoTranslate1Dragger.cpp
    source/draggers/SoTranslate2Dragger.cpp
    source/elements/SoAccumulatedElement.cpp
    source/elements/SoAmbientColorElement.cpp
    source/elements/SoBBoxModelMatrixElement.cpp
    source/elements/SoCacheElement.cpp
    source/elements/SoClipPlaneElement.cpp
    source/elements/SoComplexityElement.cpp
    source/elements/SoComplexityTypeElement.cpp
    source/elements/SoCoordinateElement.cpp
    source/elements/SoCreaseAngleElement.cpp
    source/elements/SoDiffuseColorElement.cpp
    source/elements/SoDrawStyleElement.cpp
    source/elements/SoElement.cpp
    source/elements/SoElementInit.cpp
    source/elements/SoEmissiveColorElement.cpp
    source/elements/SoFloatElement.cpp
    source/elements/SoFocalDistanceElement.cpp
    source/elements/SoFontNameElement.cpp
    source/elements/SoFontSizeElement.cpp
    source/elements/SoGLAmbientColorElement.cpp
    source/elements/SoGLCacheContextElement.cpp
    source/elements/SoGLClipPlaneElement.cpp
    source/elements/SoGLCoordinateElement.cpp
    source/elements/SoGLDiffuseColorElement.cpp
    source/elements/SoGLDrawStyleElement.cpp
    source/elements/SoGLEmissiveColorElement.cpp
    source/elements/SoGLLazyElement.cpp
    source/elements/SoGLLightIdElement.cpp
    source/elements/SoGLLinePatternElement.cpp
    source/elements/SoGLLineWidthElement.cpp
    source/elements/SoGLModelMatrixElement.cpp
    source/elements/SoGLNormalElement.cpp
    source/elements/SoGLPointSizeElement.cpp
    source/elements/SoGLPolygonOffsetElement.cpp
    source/elements/SoGLProjectionMatrixElement.cpp
    source/elements/SoGLRenderPassElement.cpp
    source/elements/SoGLShapeHintsElement.cpp
    source/elements/SoGLShininessElement.cpp
    source/elements/SoGLSpecularColorElement.cpp
    source/elements/SoGLStencilBitsElement.cpp
    source/elements/SoGLTextureCoordinateElement.cpp
    source/elements/SoGLTextureEnabledElement.cpp
    source/elements/SoGLTextureImageElement.cpp
    source/elements/SoGLTextureMatrixElement.cpp
    source/elements/SoGLUpdateAreaElement.cpp
    source/elements/SoGLVBOElement.cpp
    source/elements/SoGLViewingMatrixElement.cpp
    source/elements/SoGLViewportRegionElement.cpp
    source/elements/SoInt32Element.cpp
    source/elements/SoLazyElement.cpp
    source/elements/SoLightAttenuationElement.cpp
    source/elements/SoLinePatternElement.cpp
    source/elements/SoLineWidthElement.cpp
    source/elements/SoLocalBBoxMatrixElement.cpp
    source/elements/SoMaterialBindingElement.cpp
    source/elements/SoModelMatrixElement.cpp
    source/elements/SoNormalBindingElement.cpp
    source/elements/SoNormalElement.cpp
    source/elements/SoOverrideElement.cpp
    source/elements/SoPickRayElement.cpp
    source/elements/SoPickStyleElement.cpp
    source/elements/SoPointSizeElement.cpp
    source/elements/SoPolygonOffsetElement.cpp
    source/elements/SoProfileCoordinateElement.cpp
    source/elements/SoProfileElement.cpp
    source/elements/SoProjectionMatrixElement.cpp
    source/elements/SoReplacedElement.cpp
    source/elements/SoShapeHintsElement.cpp
    source/elements/SoShapeStyleElement.cpp
    source/elements/SoShininessElement.cpp
    source/elements/SoSpecularColorElement.cpp
    source/elements/SoStencilBitsElement.cpp
    source/elements/SoSwitchElement.cpp
    source/elements/SoTextureCoordinateBindingElement.cpp
    source/elements/SoTextureCoordinateElement.cpp
    source/elements/SoTextureImageElement.cpp
    source/elements/SoTextureMatrixElement.cpp
    source/elements/SoTextureQualityElement.cpp
    source/elements/SoUnitsElement.cpp
    source/elements/SoViewingMatrixElement.cpp
    source/elements/SoViewportRegionElement.cpp
    source/elements/SoViewVolumeElement.cpp
    source/elements/SoWindowElement.cpp
    source/engines/SoBoolOperation.cpp
    source/engines/SoCalcExpr.cpp
    source/engines/SoCalcExpr.h
    source/engines/SoCalculator.cpp
    source/engines/SoCompose.cpp
    source/engines/SoComputeBoundingBox.cpp
    source/engines/SoConcatenate.cpp
    source/engines/SoCounter.cpp
    source/engines/SoElapsedTime.cpp
    source/engines/SoEngine.cpp
    source/engines/SoEngineInit.cpp
    source/engines/SoEngineUtil.h
    source/engines/SoFieldConverter.cpp
    source/engines/SoFieldConverters.cpp
    source/engines/SoFieldConverters.h
    source/engines/SoGate.cpp
    source/engines/SoInterpolate.cpp
    source/engines/SoOneShot.cpp
    source/engines/SoOnOff.cpp
    source/engines/SoOutputData.cpp
    source/engines/SoSelectOne.cpp
    source/engines/SoTimeCounter.cpp
    source/engines/SoTransformVec3f.cpp
    source/engines/SoTriggerAny.cpp
    source/engines/SoUnknownEngine.cpp
    source/errors/SoDebugError.cpp
    source/errors/SoError.cpp
    source/errors/SoErrorInit.cpp
    source/errors/SoMemoryError.cpp
    source/errors/SoReadError.cpp
    source/events/SoButtonEvent.cpp
    source/events/SoEnterLeaveEvent.cpp
    source/events/SoEvent.cpp
    source/events/SoEventInit.cpp
    source/events/SoKeyboardEvent.cpp
    source/events/SoLocation2Event.cpp
    source/events/SoLocation2RefreshEvent.cpp
    source/events/SoMotion3Event.cpp
    source/events/SoMouseButtonEvent.cpp
    source/events/SoMouseWheelEvent.cpp
    source/events/SoSpaceballButtonEvent.cpp
    source/fields/SoField.cpp
    source/fields/SoFieldContainer.cpp
    source/fields/SoFieldData.cpp
    source/fields/SoFieldInit.cpp
    source/fields/SoGlobalField.cpp
    source/fields/SoGlobalField.h
    source/fields/SoMFBitMask.cpp
    source/fields/SoMFBool.cpp
    source/fields/SoMFColor.cpp
    source/fields/SoMFDouble.cpp
    source/fields/SoMFEngine.cpp
    source/fields/SoMFEnum.cpp
    source/fields/SoMFFloat.cpp
    source/fields/SoMFInt32.cpp
    source/fields/SoMFMatrix.cpp
    source/fields/SoMFMatrixd.cpp
    source/fields/SoMFName.cpp
    source/fields/SoMFNode.cpp
    source/fields/SoMFPath.cpp
    source/fields/SoMFPlane.cpp
    source/fields/SoMFPlaned.cpp
    source/fields/SoMFRotation.cpp
    source/fields/SoMFRotationd.cpp
    source/fields/SoMFShort.cpp
    source/fields/SoMFString.cpp
    source/fields/SoMFTime.cpp
    source/fields/SoMFUInt32.cpp
    source/fields/SoMFUShort.cpp
    source/fields/SoMFVec2d.cpp
    source/fields/SoMFVec2f.cpp
    source/fields/SoMFVec3d.cpp
    source/fields/SoMFVec3f.cpp
    source/fields/SoMFVec4d.cpp
    source/fields/SoMFVec4f.cpp
    source/fields/SoSFBitMask.cpp
    source/fields/SoSFBool.cpp
    source/fields/SoSFColor.cpp
    source/fields/SoSFDouble.cpp
    source/fields/SoSFEngine.cpp
    source/fields/SoSFEnum.cpp
    source/fields/SoSFFloat.cpp
    source/fields/SoSFImage.cpp
    source/fields/SoSFInt32.cpp
    source/fields/SoSFMatrix.cpp
    source/fields/SoSFMatrixd.cpp
    source/fields/SoSFName.cpp
    source/fields/SoSFNode.cpp
    source/fields/SoSFPath.cpp
    source/fields/SoSFPlane.cpp
    source/fields/SoSFPlaned.cpp
    source/fields/SoSFRotation.cpp
    source/fields/SoSFRotationd.cpp
    source/fields/SoSFShort.cpp
    source/fields/SoSFString.cpp
    source/fields/SoSFTime.cpp
    source/fields/SoSFTrigger.cpp
    source/fields/SoSFUInt32.cpp
    source/fields/SoSFUShort.cpp
    source/fields/SoSFVec2d.cpp
    source/fields/SoSFVec2f.cpp
    source/fields/SoSFVec2s.cpp
    source/fields/SoSFVec3d.cpp
    source/fields/SoSFVec3f.cpp
    source/fields/SoSFVec3s.cpp
    source/fields/SoSFVec4d.cpp
    source/fields/SoSFVec4f.cpp
    source/manips/SoCenterballManip.cpp
    source/manips/SoDirectionalLightManip.cpp
    source/manips/SoHandleBoxManip.cpp
    source/manips/SoJackManip.cpp
    source/manips/SoPointLightManip.cpp
    source/manips/SoSpotLightManip.cpp
    source/manips/SoTabBoxManip.cpp
    source/manips/SoTrackballManip.cpp
    source/manips/SoTransformBoxManip.cpp
    source/manips/SoTransformerManip.cpp
    source/manips/SoTransformManip.cpp
    source/misc/SoVBO.cpp
    source/misc/SoVertexArrayIndexer.cpp
    source/nodekits/SoAppearKit.cpp
    source/nodekits/SoBaseKit.cpp
    source/nodekits/SoCameraKit.cpp
    source/nodekits/SoInteractionKit.cpp
    source/nodekits/SoLightKit.cpp
    source/nodekits/SoNkCatalog.cpp
    source/nodekits/SoNkParts.cpp
    source/nodekits/SoNodeKit.cpp
    source/nodekits/SoNodeKitListPart.cpp
    source/nodekits/SoSceneKit.cpp
    source/nodekits/SoSeparatorKit.cpp
    source/nodekits/SoShapeKit.cpp
    source/nodekits/SoWrapperKit.cpp
    source/nodes/nurbs/_defines.h
    source/nodes/nurbs/_undefs.h
    source/nodes/nurbs/clients/gl4base.h
    source/nodes/nurbs/clients/gl4curveval.h
    source/nodes/nurbs/clients/gl4surfeval.h
    source/nodes/nurbs/clients/gl4types.h
    source/nodes/nurbs/clients/isocurveeval.h
    source/nodes/nurbs/clients/nurbsClient.cpp
    source/nodes/nurbs/clients/softcurvemaps.h
    source/nodes/nurbs/clients/softcurveval.h
    source/nodes/nurbs/clients/softcurvmap.h
    source/nodes/nurbs/clients/softrenderer.h
    source/nodes/nurbs/clients/softsurfacemaps.h
    source/nodes/nurbs/clients/softsurfeval.h
    source/nodes/nurbs/clients/softsurfmap.h
    source/nodes/nurbs/clients/typestringtable.h
    source/nodes/nurbs/head/arc.h
    source/nodes/nurbs/head/arcsorter.h
    source/nodes/nurbs/head/arctess.h
    source/nodes/nurbs/head/backend.h
    source/nodes/nurbs/head/basiccrveval.h
    source/nodes/nurbs/head/basicsurfeval.h
    source/nodes/nurbs/head/bezierarc.h
    source/nodes/nurbs/head/bin.h
    source/nodes/nurbs/head/bufpool.h
    source/nodes/nurbs/head/cachingeval.h
    source/nodes/nurbs/head/coveandtiler.h
    source/nodes/nurbs/head/curve.h
    source/nodes/nurbs/head/curvelist.h
    source/nodes/nurbs/head/defines.h
    source/nodes/nurbs/head/displaylist.h
    source/nodes/nurbs/head/displaymode.h
    source/nodes/nurbs/head/flist.h
    source/nodes/nurbs/head/flistsorter.h
    source/nodes/nurbs/head/glimports.h
    source/nodes/nurbs/head/gridline.h
    source/nodes/nurbs/head/gridtrimvertex.h
    source/nodes/nurbs/head/gridvertex.h
    source/nodes/nurbs/head/hull.h
    source/nodes/nurbs/head/jarcloc.h
    source/nodes/nurbs/head/jumpbuffer.h
    source/nodes/nurbs/head/knot.h
    source/nodes/nurbs/head/knotvector.h
    source/nodes/nurbs/head/mapdesc.h
    source/nodes/nurbs/head/maplist.h
    source/nodes/nurbs/head/mesher.h
    source/nodes/nurbs/head/myassert.h
    source/nodes/nurbs/head/myglimports.h
    source/nodes/nurbs/head/mymath.h
    source/nodes/nurbs/head/mysetjmp.h
    source/nodes/nurbs/head/mystdio.h
    source/nodes/nurbs/head/mystdlib.h
    source/nodes/nurbs/head/mystring.h
    source/nodes/nurbs/head/nurbsconsts.h
    source/nodes/nurbs/head/nurbstess.h
    source/nodes/nurbs/head/patch.h
    source/nodes/nurbs/head/patchlist.h
    source/nodes/nurbs/head/pwlarc.h
    source/nodes/nurbs/head/quilt.h
    source/nodes/nurbs/head/reader.h
    source/nodes/nurbs/head/renderhints.h
    source/nodes/nurbs/head/simplemath.h
    source/nodes/nurbs/head/slicer.h
    source/nodes/nurbs/head/sorter.h
    source/nodes/nurbs/head/subdivider.h
    source/nodes/nurbs/head/trimline.h
    source/nodes/nurbs/head/trimregion.h
    source/nodes/nurbs/head/trimvertex.h
    source/nodes/nurbs/head/trimvertpool.h
    source/nodes/nurbs/head/types.h
    source/nodes/nurbs/head/uarray.h
    source/nodes/nurbs/head/varray.h
    source/nodes/nurbs/libnurbs/libNurbs.cpp
    source/nodes/nurbs/SoAddPrefix.h
    source/nodes/nurbs/SoCurveMaps.cpp
    source/nodes/nurbs/SoCurveMaps.h
    source/nodes/nurbs/SoCurveRender.cpp
    source/nodes/nurbs/SoCurveRender.h
    source/nodes/nurbs/SoCurveRenderEval.h
    source/nodes/nurbs/SoCurveRndEvl.cpp
    source/nodes/nurbs/SoGLRender.cpp
    source/nodes/nurbs/SoGLRender.h
    source/nodes/nurbs/SoPickEvals.cpp
    source/nodes/nurbs/SoPickEvals.h
    source/nodes/nurbs/SoPickMaps.cpp
    source/nodes/nurbs/SoPickMaps.h
    source/nodes/nurbs/SoPickRender.cpp
    source/nodes/nurbs/SoPickRender.h
    source/nodes/nurbs/SoPrimEvals.cpp
    source/nodes/nurbs/SoPrimEvals.h
    source/nodes/nurbs/SoPrimMaps.cpp
    source/nodes/nurbs/SoPrimMaps.h
    source/nodes/nurbs/SoPrimRender.cpp
    source/nodes/nurbs/SoPrimRender.h
    source/nodes/readGIF.c
    source/nodes/readGIF.h
    source/nodes/readJPEG.cpp
    source/nodes/readJPEG.h
    source/nodes/SoAnnotation.cpp
    source/nodes/SoAntiSquish.cpp
    source/nodes/SoArray.cpp
    source/nodes/SoAsciiText.cpp
    source/nodes/SoBaseColor.cpp
    source/nodes/SoBlinker.cpp
    source/nodes/SoCallback.cpp
    source/nodes/SoCamera.cpp
    source/nodes/SoClipPlane.cpp
    source/nodes/SoComplexity.cpp
    source/nodes/SoCone.cpp
    source/nodes/SoCoordinate3.cpp
    source/nodes/SoCoordinate4.cpp
    source/nodes/SoCube.cpp
    source/nodes/SoCylinder.cpp
    source/nodes/SoDirectionalLight.cpp
    source/nodes/SoDrawStyle.cpp
    source/nodes/SoEnvironment.cpp
    source/nodes/SoEventCallback.cpp
    source/nodes/SoFaceSet.cpp
    source/nodes/SoFile.cpp
    source/nodes/SoFont.cpp
    source/nodes/SoFontStyle.cpp
    source/nodes/SoGroup.cpp
    source/nodes/SoIndexedFaceSet.cpp
    source/nodes/SoIndexedLineSet.cpp
    source/nodes/SoIndexedNurbsCurve.cpp
    source/nodes/SoIndexedNurbsSurface.cpp
    source/nodes/SoIndexedShape.cpp
    source/nodes/SoIndexedTriangleSet.cpp
    source/nodes/SoIndexedTriangleStripSet.cpp
    source/nodes/SoInfo.cpp
    source/nodes/SoLabel.cpp
    source/nodes/SoLevelOfDetail.cpp
    source/nodes/SoLight.cpp
    source/nodes/SoLightModel.cpp
    source/nodes/SoLinearProfile.cpp
    source/nodes/SoLineSet.cpp
    source/nodes/SoLocateHighlight.cpp
    source/nodes/SoLOD.cpp
    source/nodes/SoMaterial.cpp
    source/nodes/SoMaterialBinding.cpp
    source/nodes/SoMatrixTransform.cpp
    source/nodes/SoMultipleCopy.cpp
    source/nodes/SoNode.cpp
    source/nodes/SoNodeInit.cpp
    source/nodes/SoNonIndexedShape.cpp
    source/nodes/SoNormal.cpp
    source/nodes/SoNormalBinding.cpp
    source/nodes/SoNurbsCurve.cpp
    source/nodes/SoNurbsProfile.cpp
    source/nodes/SoNurbsSurface.cpp
    source/nodes/SoOrthographicCamera.cpp
    source/nodes/SoPackedColor.cpp
    source/nodes/SoPathSwitch.cpp
    source/nodes/SoPendulum.cpp
    source/nodes/SoPerspectiveCamera.cpp
    source/nodes/SoPickStyle.cpp
    source/nodes/SoPointLight.cpp
    source/nodes/SoPointSet.cpp
    source/nodes/SoPolygonOffset.cpp
    source/nodes/SoProfile.cpp
    source/nodes/SoProfileCoordinate2.cpp
    source/nodes/SoProfileCoordinate3.cpp
    source/nodes/SoQuadMesh.cpp
    source/nodes/SoResetTransform.cpp
    source/nodes/SoRotation.cpp
    source/nodes/SoRotationXYZ.cpp
    source/nodes/SoRotor.cpp
    source/nodes/SoScale.cpp
    source/nodes/SoSeparator.cpp
    source/nodes/SoShape.cpp
    source/nodes/SoShapeHints.cpp
    source/nodes/SoShuttle.cpp
    source/nodes/SoSphere.cpp
    source/nodes/SoSpotLight.cpp
    source/nodes/SoSurroundScale.cpp
    source/nodes/SoSwitch.cpp
    source/nodes/SoText2.cpp
    source/nodes/SoText3.cpp
    source/nodes/SoTexture2.cpp
    source/nodes/SoTexture2Transform.cpp
    source/nodes/SoTextureCoordinate2.cpp
    source/nodes/SoTextureCoordinateBinding.cpp
    source/nodes/SoTextureCoordinateDefault.cpp
    source/nodes/SoTextureCoordinateEnvironment.cpp
    source/nodes/SoTextureCoordinateFunction.cpp
    source/nodes/SoTextureCoordinatePlane.cpp
    source/nodes/SoTransform.cpp
    source/nodes/SoTransformation.cpp
    source/nodes/SoTransformSeparator.cpp
    source/nodes/SoTranslation.cpp
    source/nodes/SoTriangleStripSet.cpp
    source/nodes/SoUnits.cpp
    source/nodes/SoUnknownNode.cpp
    source/nodes/SoVertexProperty.cpp
    source/nodes/SoVertexShape.cpp
    source/nodes/SoWWWAnchor.cpp
    source/nodes/SoWWWInline.cpp
    source/projectors/SbCylinderPlaneProjector.cpp
    source/projectors/SbCylinderProjector.cpp
    source/projectors/SbCylinderSectionProjector.cpp
    source/projectors/SbCylinderSheetProjector.cpp
    source/projectors/SbLineProjector.cpp
    source/projectors/SbPlaneProjector.cpp
    source/projectors/SbProjector.cpp
    source/projectors/SbSpherePlaneProjector.cpp
    source/projectors/SbSphereProjector.cpp
    source/projectors/SbSphereSectionProjector.cpp
    source/projectors/SbSphereSheetProjector.cpp
    source/SbBox.cpp
    source/SbBoxd.cpp
    source/SbColor.cpp
    source/SbCylinder.cpp
    source/SbCylinderd.cpp
    source/SbDict.cpp
    source/SbLine.cpp
    source/SbLined.cpp
    source/SbMatrix.cpp
    source/SbMatrixd.cpp
    source/SbName.cpp
    source/SbPlane.cpp
    source/SbPlaned.cpp
    source/SbPList.cpp
    source/SbRotation.cpp
    source/SbRotationd.cpp
    source/SbSphere.cpp
    source/SbSphered.cpp
    source/SbString.cpp
    source/SbTime.cpp
    source/SbVec.cpp
    source/SbVecd.cpp
    source/SbView.cpp
    source/SbViewportRegion.cpp
    source/sensors/SoAlarmSensor.cpp
    source/sensors/SoDataSensor.cpp
    source/sensors/SoDelayQueueSensor.cpp
    source/sensors/SoFieldSensor.cpp
    source/sensors/SoIdleSensor.cpp
    source/sensors/SoNodeSensor.cpp
    source/sensors/SoOneShotSensor.cpp
    source/sensors/SoPathSensor.cpp
    source/sensors/SoSensor.cpp
    source/sensors/SoSensorManager.cpp
    source/sensors/SoTimerQueueSensor.cpp
    source/sensors/SoTimerSensor.cpp
    source/SoAuditorList.cpp
    source/SoBase.cpp
    source/SoByteStream.cpp
    source/SoCatch.cpp
    source/SoCBList.cpp
    source/SoChildList.cpp
    source/SoCompactPathList.cpp
    source/SoDB.cpp
    source/SoDebug.cpp
    source/SoInput.cpp
    source/SoInteraction.cpp
    source/SoLists.cpp
    source/SoMachine.cpp
    source/SoNodeKitPath.cpp
    source/SoNormalGenerator.cpp
    source/SoNotification.cpp
    source/SoOutput.cpp
    source/SoPath.cpp
    source/SoPickedPoint.cpp
    source/SoPrimitiveVertex.cpp
    source/SoProfiling.cpp
    source/SoSceneManager.cpp
    source/SoSelection.cpp
    source/SoState.cpp
    source/SoTempPath.cpp
    source/SoTrace.cpp
    source/SoTranscribe.cpp
    source/SoType.cpp
    source/system/SbOpenGL.cpp
    source/upgraders/SoUpgrader.cpp
    source/upgraders/SoUpgraderInit.cpp
    source/upgraders/SoUpgraders.h
    source/upgraders/SoV1AppearKit.cpp
    source/upgraders/SoV1BaseKit.cpp
    source/upgraders/SoV1CameraKit.cpp
    source/upgraders/SoV1ConeKit.cpp
    source/upgraders/SoV1CubeKit.cpp
    source/upgraders/SoV1CustomNode.cpp
    source/upgraders/SoV1CylinderKit.cpp
    source/upgraders/SoV1DirLtKit.cpp
    source/upgraders/SoV1DrawStyle.cpp
    source/upgraders/SoV1DrawStyle.h
    source/upgraders/SoV1Environment.cpp
    source/upgraders/SoV1Environment.h
    source/upgraders/SoV1FaceSetKit.cpp
    source/upgraders/SoV1GroupKit.cpp
    source/upgraders/SoV1IFaceSetKit.cpp
    source/upgraders/SoV1ILineSetKit.cpp
    source/upgraders/SoV1IndexedTriangleMesh.cpp
    source/upgraders/SoV1IndexedTriangleMesh.h
    source/upgraders/SoV1INrbCurvKit.cpp
    source/upgraders/SoV1INrbSurfKit.cpp
    source/upgraders/SoV1ITMshSetKit.cpp
    source/upgraders/SoV1LayerGroup.cpp
    source/upgraders/SoV1LayerGroup.h
    source/upgraders/SoV1LightKit.cpp
    source/upgraders/SoV1LightModel.cpp
    source/upgraders/SoV1LightModel.h
    source/upgraders/SoV1LineSetKit.cpp
    source/upgraders/SoV1Material.cpp
    source/upgraders/SoV1Material.h
    source/upgraders/SoV1NkCatalog.cpp
    source/upgraders/SoV1NkParts.cpp
    source/upgraders/SoV1NodeKit.cpp
    source/upgraders/SoV1NurbCurvKit.cpp
    source/upgraders/SoV1NurbSurfKit.cpp
    source/upgraders/SoV1OrthoCamKit.cpp
    source/upgraders/SoV1PackedColor.cpp
    source/upgraders/SoV1PackedColor.h
    source/upgraders/SoV1PerspCamKit.cpp
    source/upgraders/SoV1PickStyle.cpp
    source/upgraders/SoV1PickStyle.h
    source/upgraders/SoV1PointLtKit.cpp
    source/upgraders/SoV1PointSetKit.cpp
    source/upgraders/SoV1QuadMeshKit.cpp
    source/upgraders/SoV1SceneKit.cpp
    source/upgraders/SoV1Separator.cpp
    source/upgraders/SoV1Separator.h
    source/upgraders/SoV1ShapeHints.cpp
    source/upgraders/SoV1ShapeHints.h
    source/upgraders/SoV1ShapeKit.cpp
    source/upgraders/SoV1SphereKit.cpp
    source/upgraders/SoV1SpotLtKit.cpp
    source/upgraders/SoV1Text2.cpp
    source/upgraders/SoV1Text2.h
    source/upgraders/SoV1Text2Kit.cpp
    source/upgraders/SoV1Text3.cpp
    source/upgraders/SoV1Text3.h
    source/upgraders/SoV1Text3Kit.cpp
    source/upgraders/SoV1Texture2.cpp
    source/upgraders/SoV1Texture2.h
    source/upgraders/SoV1TextureCoordinateCube.cpp
    source/upgraders/SoV1TextureCoordinateCube.h
    source/upgraders/SoV1TextureCoordinateCylinder.cpp
    source/upgraders/SoV1TextureCoordinateCylinder.h
    source/upgraders/SoV1TextureCoordinateEnvironment.cpp
    source/upgraders/SoV1TextureCoordinateEnvironment.h
    source/upgraders/SoV1TextureCoordinatePlane.cpp
    source/upgraders/SoV1TextureCoordinatePlane.h
    source/upgraders/SoV1TextureCoordinateSphere.cpp
    source/upgraders/SoV1TextureCoordinateSphere.h
    source/upgraders/SoV1TriStripKit.cpp
    source/upgraders/SoV1VtxShapeKit.cpp
    source/upgraders/SoV1WrapperKit.cpp
    source/upgraders/SoV2AsciiText.cpp
    source/upgraders/SoV2AsciiText.h
    source/upgraders/SoV2FontStyle.cpp
    source/upgraders/SoV2FontStyle.h
    source/upgraders/SoV2LOD.cpp
    source/upgraders/SoV2LOD.h
    source/upgraders/SoV2MaterialIndex.cpp
    source/upgraders/SoV2MaterialIndex.h
    source/upgraders/SoV2Text2.cpp
    source/upgraders/SoV2Text2.h
    source/upgraders/SoV2Text3.cpp
    source/upgraders/SoV2Text3.h
    source/upgraders/SoV2VertexProperty.cpp
    source/upgraders/SoV2VertexProperty.h
    source/upgraders/SoV2WWWAnchor.cpp
    source/upgraders/SoV2WWWAnchor.h
    source/upgraders/SoV2WWWInline.cpp
    source/upgraders/SoV2WWWInline.h
)

BISON_TARGET(inventor_parser source/engines/SoCalcParse.y ${CMAKE_CURRENT_BINARY_DIR}/SoCalcParse.cpp)
target_sources(Inventor PRIVATE ${BISON_inventor_parser_OUTPUTS})

# generate files using ppp (ppp target defined below)
file(MAKE_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/source/nodes/")
add_custom_command(
  OUTPUT source/nodes/SoCone_generated.cpp
  COMMAND ppp < SoCone.pp > ${CMAKE_CURRENT_BINARY_DIR}/source/nodes/SoCone_generated.cpp
  WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/source/nodes
)
add_custom_command(
  OUTPUT source/nodes/SoCube_generated.cpp
  COMMAND ppp < SoCube.pp > ${CMAKE_CURRENT_BINARY_DIR}/source/nodes/SoCube_generated.cpp
  WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/source/nodes
)
add_custom_command(
  OUTPUT source/nodes/SoCylinder_generated.cpp
  COMMAND ppp < SoCylinder.pp > ${CMAKE_CURRENT_BINARY_DIR}/source/nodes/SoCylinder_generated.cpp
  WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/source/nodes
)
add_custom_command(
  OUTPUT source/nodes/SoFaceSet_generated.cpp
  COMMAND ppp < SoFaceSet.pp > ${CMAKE_CURRENT_BINARY_DIR}/source/nodes/SoFaceSet_generated.cpp
  WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/source/nodes
)
add_custom_command(
  OUTPUT source/nodes/SoIndexedFaceSet_generated.cpp
  COMMAND ppp < SoIndexedFaceSet.pp > ${CMAKE_CURRENT_BINARY_DIR}/source/nodes/SoIndexedFaceSet_generated.cpp
  WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/source/nodes
)
add_custom_command(
  OUTPUT source/nodes/SoIndexedTriangleSet_generated.cpp
  COMMAND ppp < SoIndexedTriangleSet.pp > ${CMAKE_CURRENT_BINARY_DIR}/source/nodes/SoIndexedTriangleSet_generated.cpp
  WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/source/nodes
)
add_custom_command(
  OUTPUT source/nodes/SoIndexedLineSet_generated.cpp
  COMMAND ppp < SoIndexedLineSet.pp > ${CMAKE_CURRENT_BINARY_DIR}/source/nodes/SoIndexedLineSet_generated.cpp
  WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/source/nodes
)
add_custom_command(
  OUTPUT source/nodes/SoIndexedTriangleStripSet_generated.cpp
  COMMAND ppp < SoIndexedTriangleStripSet.pp > ${CMAKE_CURRENT_BINARY_DIR}/source/nodes/SoIndexedTriangleStripSet_generated.cpp
  WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/source/nodes
)
add_custom_command(
  OUTPUT source/nodes/SoLineSet_generated.cpp
  COMMAND ppp < SoLineSet.pp > ${CMAKE_CURRENT_BINARY_DIR}/source/nodes/SoLineSet_generated.cpp
  WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/source/nodes
)
add_custom_command(
  OUTPUT source/nodes/SoQuadMesh_generated.cpp
  COMMAND ppp < SoQuadMesh.pp > ${CMAKE_CURRENT_BINARY_DIR}/source/nodes/SoQuadMesh_generated.cpp
  WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/source/nodes
)
add_custom_command(
  OUTPUT source/nodes/SoSphere_generated.cpp
  COMMAND ppp < SoSphere.pp > ${CMAKE_CURRENT_BINARY_DIR}/source/nodes/SoSphere_generated.cpp
  WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/source/nodes
)
add_custom_command(
  OUTPUT source/nodes/SoTriangleStripSet_generated.cpp
  COMMAND ppp < SoTriangleStripSet.pp > ${CMAKE_CURRENT_BINARY_DIR}/source/nodes/SoTriangleStripSet_generated.cpp
  WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/source/nodes
)

add_custom_target(inventor_generate_ppp
  DEPENDS
    source/nodes/SoCone_generated.cpp
    source/nodes/SoCube_generated.cpp
    source/nodes/SoCylinder_generated.cpp
    source/nodes/SoFaceSet_generated.cpp
    source/nodes/SoIndexedFaceSet_generated.cpp
    source/nodes/SoIndexedTriangleSet_generated.cpp
    source/nodes/SoIndexedLineSet_generated.cpp
    source/nodes/SoIndexedTriangleStripSet_generated.cpp
    source/nodes/SoLineSet_generated.cpp
    source/nodes/SoQuadMesh_generated.cpp
    source/nodes/SoSphere_generated.cpp
    source/nodes/SoTriangleStripSet_generated.cpp
)

target_include_directories(Inventor SYSTEM PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include/Inventor>                   # remove
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include/Inventor/actions>           # remove
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include/Inventor/bundles>           # remove
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include/Inventor/caches>            # remove
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include/Inventor/details>           # remove
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include/Inventor/draggers>          # remove
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include/Inventor/elements>          # remove
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include/Inventor/engines>           # remove
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include/Inventor/errors>            # remove
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include/Inventor/events>            # remove
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include/Inventor/fields>            # remove
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include/Inventor/manips>            # remove
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include/Inventor/misc>              # remove
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include/Inventor/misc/upgraders>    # remove
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include/Inventor/nodekits>          # remove
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include/Inventor/nodes>             # remove
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include/Inventor/projectors>        # remove
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include/Inventor/sensors>           # remove
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include/Inventor/system>            # remove

  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/source/engines>                     # remove
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/source/nodes>                       # remove
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/source/nodes/nurbs>                 # remove
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/source/nodes/nurbs/head>            # remove
  $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}/source/nodes>                       # remove

  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/libFL/src>

  $<INSTALL_INTERFACE:${MEVISLAB_INSTALL_INCLUDEDIR}/include>
  $<INSTALL_INTERFACE:${MEVISLAB_INSTALL_INCLUDEDIR}/include/Inventor>                   # remove
  $<INSTALL_INTERFACE:${MEVISLAB_INSTALL_INCLUDEDIR}/include/Inventor/actions>           # remove
  $<INSTALL_INTERFACE:${MEVISLAB_INSTALL_INCLUDEDIR}/include/Inventor/bundles>           # remove
  $<INSTALL_INTERFACE:${MEVISLAB_INSTALL_INCLUDEDIR}/include/Inventor/caches>            # remove
  $<INSTALL_INTERFACE:${MEVISLAB_INSTALL_INCLUDEDIR}/include/Inventor/details>           # remove
  $<INSTALL_INTERFACE:${MEVISLAB_INSTALL_INCLUDEDIR}/include/Inventor/draggers>          # remove
  $<INSTALL_INTERFACE:${MEVISLAB_INSTALL_INCLUDEDIR}/include/Inventor/elements>          # remove
  $<INSTALL_INTERFACE:${MEVISLAB_INSTALL_INCLUDEDIR}/include/Inventor/engines>           # remove
  $<INSTALL_INTERFACE:${MEVISLAB_INSTALL_INCLUDEDIR}/include/Inventor/errors>            # remove
  $<INSTALL_INTERFACE:${MEVISLAB_INSTALL_INCLUDEDIR}/include/Inventor/events>            # remove
  $<INSTALL_INTERFACE:${MEVISLAB_INSTALL_INCLUDEDIR}/include/Inventor/fields>            # remove
  $<INSTALL_INTERFACE:${MEVISLAB_INSTALL_INCLUDEDIR}/include/Inventor/manips>            # remove
  $<INSTALL_INTERFACE:${MEVISLAB_INSTALL_INCLUDEDIR}/include/Inventor/misc>              # remove
  $<INSTALL_INTERFACE:${MEVISLAB_INSTALL_INCLUDEDIR}/include/Inventor/misc>/upgraders    # remove
  $<INSTALL_INTERFACE:${MEVISLAB_INSTALL_INCLUDEDIR}/include/Inventor/nodekits>          # remove
  $<INSTALL_INTERFACE:${MEVISLAB_INSTALL_INCLUDEDIR}/include/Inventor/nodes>             # remove
  $<INSTALL_INTERFACE:${MEVISLAB_INSTALL_INCLUDEDIR}/include/Inventor/projectors>        # remove
  $<INSTALL_INTERFACE:${MEVISLAB_INSTALL_INCLUDEDIR}/include/Inventor/sensors>           # remove
  $<INSTALL_INTERFACE:${MEVISLAB_INSTALL_INCLUDEDIR}/include/Inventor/system>            # remove
)

target_compile_definitions(Inventor PRIVATE $<BUILD_INTERFACE:LIBRARYBUILD>)
target_compile_definitions(Inventor PRIVATE $<BUILD_INTERFACE:INVENTOR_EXPORTS>)

if(WIN32)
  target_sources(Inventor PRIVATE source/utf8_filesupport_win32.h source/utf8_filesupport_win32.cpp)
  target_compile_definitions(Inventor PRIVATE $<BUILD_INTERFACE:WIN32>)
  target_compile_definitions(Inventor PRIVATE $<BUILD_INTERFACE:__SGIOIV_BUILD_DLL>)
  target_link_libraries(Inventor PRIVATE wsock32 ws2_32 CONAN_PKG::libiconv)
endif()

set_target_properties(Inventor PROPERTIES C_VISIBILITY_PRESET default)
set_target_properties(Inventor PROPERTIES CXX_VISIBILITY_PRESET default)

target_link_libraries(Inventor PUBLIC OpenGL::GL OpenGL::GLU CONAN_PKG::JPEG CONAN_PKG::GLEW)
target_link_libraries(Inventor PRIVATE FL::FL)

add_dependencies(Inventor inventor_generate_ppp)

if (APPLE)
    find_library(AGL AGL)
    find_library(iconv iconv)
    target_link_libraries(Inventor PRIVATE ${AGL} ${iconv})
endif()


# Disable all compiler warnings (FIXME)
if(CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  target_compile_options(Inventor PRIVATE "-Wno-everything")
elseif(CMAKE_CXX_COMPILER_ID MATCHES "GNU")
  target_compile_options(Inventor PRIVATE "-w")
elseif(CMAKE_CXX_COMPILER_ID MATCHES "MSVC")
  target_compile_options(Inventor PRIVATE "/w")
endif()


install(TARGETS Inventor RUNTIME DESTINATION bin LIBRARY DESTINATION lib ARCHIVE DESTINATION lib)
install(DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/include/" DESTINATION include FILES_MATCHING PATTERN "*.h")
install(DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/doxygen/" DESTINATION doxygen)

if(MSVC)
  install(FILES $<TARGET_PDB_FILE:Inventor> DESTINATION bin OPTIONAL)
endif()
