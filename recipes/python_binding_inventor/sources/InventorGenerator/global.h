/*************************************************************************************
**
** Copyright 2014, MeVis Medical Solutions AG
**
** GNU LESSER GENERAL PUBLIC LICENSE Version 2.1, February 1999
**
**************************************************************************************/

#define SoEXTENDER
#define IV_STRICT

#define uint32_t unsigned int
#define int32_t int

#include <Inventor/nodes/SoSubNode.h>
#include <Inventor/nodes/SoCube.h>
#include <Inventor/SbLinear.h>
#include <Inventor/SbLineard.h>
#include <Inventor/SbBox.h>
#include <Inventor/SbBoxd.h>
#include <Inventor/SbColor.h>
#include <Inventor/SbViewportRegion.h>
#include <Inventor/SbTime.h>
#include <Inventor/misc/SoState.h>
#include <Inventor/fields/SoFields.h>
#include <Inventor/nodes/SoNodes.h>
#include <Inventor/events/SoEvents.h>
#include <Inventor/actions/SoActions.h>
#include <Inventor/SbViewportRegion.h>
#include <Inventor/SoPath.h>
#include <Inventor/SoSceneManager.h>
#include <Inventor/SoPickedPoint.h>
#include <Inventor/SoPrimitiveVertex.h>

#include <Inventor/projectors/SbSphereSectionProjector.h>
#include <Inventor/projectors/SbSphereSheetProjector.h>
#include <Inventor/projectors/SbSpherePlaneProjector.h>
#include <Inventor/projectors/SbCylinderSectionProjector.h>
#include <Inventor/projectors/SbCylinderPlaneProjector.h>
#include <Inventor/projectors/SbCylinderSheetProjector.h>
#include <Inventor/projectors/SbPlaneProjector.h>
#include <Inventor/projectors/SbLineProjector.h>

#include <Inventor/actions/SoActions.h>
#include <Inventor/details/SoDetails.h>
#include <Inventor/elements/SoElements.h>
#include <Inventor/engines/SoEngines.h>
#include <Inventor/events/SoEvents.h>
#include <Inventor/fields/SoFields.h>
#include <Inventor/nodes/SoNodes.h>
#include <Inventor/sensors/SoSensors.h>

#include <Inventor/fields/SoSFVec2s.h>
#include <Inventor/fields/SoSFVec3s.h>

#include <Inventor/nodes/SoAntiSquish.h>
#include <Inventor/nodes/SoSurroundScale.h>
#include <Inventor/nodes/SoSelection.h>

#include <Inventor/nodes/SoPolygonOffset.h>

#include <Inventor/events/SoLocation2RefreshEvent.h>
#include <Inventor/events/SoMouseWheelEvent.h>
//TODO: add events from MeVisLab...

#include <Inventor/manips/SoTransformerManip.h>
#include <Inventor/manips/SoTransformManip.h>
#include <Inventor/manips/SoCenterballManip.h>
#include <Inventor/manips/SoDirectionalLightManip.h>
#include <Inventor/manips/SoHandleBoxManip.h>
#include <Inventor/manips/SoJackManip.h>
#include <Inventor/manips/SoPointLightManip.h>
#include <Inventor/manips/SoSpotLightManip.h>
#include <Inventor/manips/SoTabBoxManip.h>
#include <Inventor/manips/SoTrackballManip.h>
#include <Inventor/manips/SoTransformBoxManip.h>

#include <Inventor/nodekits/SoWrapperKit.h>
#include <Inventor/nodekits/SoAppearanceKit.h>
#include <Inventor/nodekits/SoBaseKit.h>
#include <Inventor/nodekits/SoCameraKit.h>
#include <Inventor/nodekits/SoInteractionKit.h>
#include <Inventor/nodekits/SoLightKit.h>
#include <Inventor/nodekits/SoNodeKit.h>
#include <Inventor/nodekits/SoNodekitCatalog.h>
#include <Inventor/nodekits/SoNodeKitListPart.h>
#include <Inventor/nodekits/SoNodekitParts.h>
#include <Inventor/nodekits/SoSceneKit.h>
#include <Inventor/nodekits/SoSeparatorKit.h>
#include <Inventor/nodekits/SoShapeKit.h>

#include <Inventor/draggers/SoTabBoxDragger.h>
#include <Inventor/draggers/SoTabPlaneDragger.h>
#include <Inventor/draggers/SoTrackballDragger.h>
#include <Inventor/draggers/SoTransformBoxDragger.h>
#include <Inventor/draggers/SoTransformerDragger.h>
#include <Inventor/draggers/SoTranslate1Dragger.h>
#include <Inventor/draggers/SoTranslate2Dragger.h>
#include <Inventor/draggers/SoCenterballDragger.h>
#include <Inventor/draggers/SoDirectionalLightDragger.h>
#include <Inventor/draggers/SoDragPointDragger.h>
#include <Inventor/draggers/SoHandleBoxDragger.h>
#include <Inventor/draggers/SoJackDragger.h>
#include <Inventor/draggers/SoPointLightDragger.h>
#include <Inventor/draggers/SoRotateCylindricalDragger.h>
#include <Inventor/draggers/SoRotateDiscDragger.h>
#include <Inventor/draggers/SoRotateSphericalDragger.h>
#include <Inventor/draggers/SoScale1Dragger.h>
#include <Inventor/draggers/SoScale2Dragger.h>
#include <Inventor/draggers/SoScale2UniformDragger.h>
#include <Inventor/draggers/SoScaleUniformDragger.h>
#include <Inventor/draggers/SoSpotLightDragger.h>

