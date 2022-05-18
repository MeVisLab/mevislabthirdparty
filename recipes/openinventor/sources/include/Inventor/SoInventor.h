/*
 *
 *  Copyright (C) 2006 MeVis Research GmbH  All Rights Reserved.
 *
 *  This library is free software; you can redistribute it and/or
 *  modify it under the terms of the GNU Lesser General Public
 *  License as published by the Free Software Foundation; either
 *  version 2.1 of the License, or (at your option) any later version.
 *
 *  This library is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 *  Lesser General Public License for more details.
 *
 *  Further, this software is distributed without any warranty that it is
 *  free of the rightful claim of any third person regarding infringement
 *  or the like.  Any license provided herein, whether implied or
 *  otherwise, applies only to this software file.  Patent licenses, if
 *  any, provided herein do not apply to combinations of this program with
 *  other software, or any other product whatsoever.
 *
 *  You should have received a copy of the GNU Lesser General Public
 *  License along with this library; if not, write to the Free Software
 *  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 *
 *  Contact information: MeVis, Center for Medical Diagnostic Systems and
 *  Visualization GmbH, Universitätsallee 29, D-28359 Bremen, GERMANY, or:
 *
 *  http://www.mevis.de
 *
 */

/*
 * Copyright (C) 2006   MeVis Research GmbH
 *
 _______________________________________________________________________
 _______________  M E V I S   R E S E A R C H   G M B H  _______________
 |
 |   Description:
 |      This header file includes all Open Inventor headers.
 |
 |   Author(s)      : Felix Ritter
 |
 _______________  M E V I S   R E S E A R C H   G M B H  _______________
 _______________________________________________________________________
 */

#ifndef  _SO_INVENTOR_
#define  _SO_INVENTOR_

//! SGI Open Inventor (2.1.x)

#include <Inventor/Sb.h>
#include <Inventor/So.h>

#include <Inventor/SoSceneManager.h>

#include <Inventor/SoInteraction.h>

#include <Inventor/elements/SoAccumulatedElement.h>
#include <Inventor/elements/SoBBoxModelMatrixElement.h>
#include <Inventor/elements/SoCacheElement.h>
#include <Inventor/elements/SoClipPlaneElement.h>
#include <Inventor/elements/SoComplexityElement.h>
#include <Inventor/elements/SoComplexityTypeElement.h>
#include <Inventor/elements/SoCoordinateElement.h>
#include <Inventor/elements/SoCreaseAngleElement.h>
#include <Inventor/elements/SoDrawStyleElement.h>
#include <Inventor/elements/SoElement.h>
#include <Inventor/elements/SoElements.h>
#include <Inventor/elements/SoFloatElement.h>
#include <Inventor/elements/SoFocalDistanceElement.h>
#include <Inventor/elements/SoFontNameElement.h>
#include <Inventor/elements/SoFontSizeElement.h>
#include <Inventor/elements/SoGLCacheContextElement.h>
#include <Inventor/elements/SoGLClipPlaneElement.h>
#include <Inventor/elements/SoGLCoordinateElement.h>
#include <Inventor/elements/SoGLDrawStyleElement.h>
#include <Inventor/elements/SoGLLazyElement.h>
#include <Inventor/elements/SoGLLightIdElement.h>
#include <Inventor/elements/SoGLLinePatternElement.h>
#include <Inventor/elements/SoGLLineWidthElement.h>
#include <Inventor/elements/SoGLModelMatrixElement.h>
#include <Inventor/elements/SoGLNormalElement.h>
#include <Inventor/elements/SoGLPointSizeElement.h>
#include <Inventor/elements/SoGLProjectionMatrixElement.h>
#include <Inventor/elements/SoGLRenderPassElement.h>
#include <Inventor/elements/SoGLShapeHintsElement.h>
#include <Inventor/elements/SoGLStencilBitsElement.h>
#include <Inventor/elements/SoGLTextureCoordinateElement.h>
#include <Inventor/elements/SoGLTextureEnabledElement.h>
#include <Inventor/elements/SoGLTextureImageElement.h>
#include <Inventor/elements/SoGLTextureMatrixElement.h>
#include <Inventor/elements/SoGLUpdateAreaElement.h>
#include <Inventor/elements/SoGLViewingMatrixElement.h>
#include <Inventor/elements/SoGLPolygonOffsetElement.h>
#include <Inventor/elements/SoGLViewportRegionElement.h>
#include <Inventor/elements/SoStencilBitsElement.h>
#include <Inventor/elements/SoInt32Element.h>
#include <Inventor/elements/SoLazyElement.h>
#include <Inventor/elements/SoLightAttenuationElement.h>
#include <Inventor/elements/SoLightModelElement.h>
#include <Inventor/elements/SoLinePatternElement.h>
#include <Inventor/elements/SoLineWidthElement.h>
#include <Inventor/elements/SoLocalBBoxMatrixElement.h>
#include <Inventor/elements/SoMaterialBindingElement.h>
#include <Inventor/elements/SoModelMatrixElement.h>
#include <Inventor/elements/SoNormalBindingElement.h>
#include <Inventor/elements/SoNormalElement.h>
#include <Inventor/elements/SoOverrideElement.h>
#include <Inventor/elements/SoPickRayElement.h>
#include <Inventor/elements/SoPickStyleElement.h>
#include <Inventor/elements/SoPointSizeElement.h>
#include <Inventor/elements/SoPolygonOffsetElement.h>
#include <Inventor/elements/SoProfileCoordinateElement.h>
#include <Inventor/elements/SoProfileElement.h>
#include <Inventor/elements/SoProjectionMatrixElement.h>
#include <Inventor/elements/SoReplacedElement.h>
#include <Inventor/elements/SoShapeHintsElement.h>
#include <Inventor/elements/SoShapeStyleElement.h>
#include <Inventor/elements/SoSubElement.h>
#include <Inventor/elements/SoSwitchElement.h>
#include <Inventor/elements/SoTextureCoordinateBindingElement.h>
#include <Inventor/elements/SoTextureCoordinateElement.h>
#include <Inventor/elements/SoTextureImageElement.h>
#include <Inventor/elements/SoTextureMatrixElement.h>
#include <Inventor/elements/SoTextureQualityElement.h>
#include <Inventor/elements/SoUnitsElement.h>
#include <Inventor/elements/SoViewingMatrixElement.h>
#include <Inventor/elements/SoViewportRegionElement.h>
#include <Inventor/elements/SoViewVolumeElement.h>
#include <Inventor/elements/SoWindowElement.h>

#include <Inventor/manips/SoCenterballManip.h>
#include <Inventor/manips/SoDirectionalLightManip.h>
#include <Inventor/manips/SoHandleBoxManip.h>
#include <Inventor/manips/SoJackManip.h>
#include <Inventor/manips/SoPointLightManip.h>
#include <Inventor/manips/SoSpotLightManip.h>
#include <Inventor/manips/SoTabBoxManip.h>
#include <Inventor/manips/SoTrackballManip.h>
#include <Inventor/manips/SoTransformBoxManip.h>
#include <Inventor/manips/SoTransformerManip.h>
#include <Inventor/manips/SoTransformManip.h>

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
#include <Inventor/nodekits/SoSubKit.h>
#include <Inventor/nodekits/SoWrapperKit.h>

#include <Inventor/SoCatch.h>
#include <Inventor/SoTrace.h>
#include <Inventor/elements/SoGLPolygonOffsetElement.h>
#include <Inventor/elements/SoGLStencilBitsElement.h>
#include <Inventor/elements/SoPolygonOffsetElement.h>
#include <Inventor/elements/SoStencilBitsElement.h>
#include <Inventor/fields/SoSFVec2s.h>
#include <Inventor/fields/SoSFVec3s.h>
#include <Inventor/nodes/SoPolygonOffset.h>

#endif  // _SO_INVENTOR_
