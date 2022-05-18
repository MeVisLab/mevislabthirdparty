/*
 *
 *  Copyright (C) 2000 Silicon Graphics, Inc.  All Rights Reserved. 
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
 *  Contact information: Silicon Graphics, Inc., 1600 Amphitheatre Pkwy,
 *  Mountain View, CA  94043, or:
 * 
 *  http://www.sgi.com 
 * 
 *  For further information regarding this notice, see: 
 * 
 *  http://oss.sgi.com/projects/GenInfo/NoticeExplan/
 *
 */

/*
 * Copyright (C) 1990,91   Silicon Graphics, Inc.
 *
 _______________________________________________________________________
 ______________  S I L I C O N   G R A P H I C S   I N C .  ____________
 |
 |   $Revision: 1.1.1.1 $
 |
 |   Classes:
 |      SoCamera
 |
 |   Author(s)          : Paul S. Strauss
 |
 ______________  S I L I C O N   G R A P H I C S   I N C .  ____________
 _______________________________________________________________________
 */

#include <Inventor/system/SbSystem.h>
#include <Inventor/system/SbOpenGL.h>
#include <Inventor/actions/SoCallbackAction.h>
#include <Inventor/actions/SoGLRenderAction.h>
#include <Inventor/actions/SoGetBoundingBoxAction.h>
#include <Inventor/actions/SoGetMatrixAction.h>
#include <Inventor/actions/SoHandleEventAction.h>
#include <Inventor/actions/SoRayPickAction.h>
#include <Inventor/elements/SoFocalDistanceElement.h>
#include <Inventor/elements/SoGLCacheContextElement.h>
#include <Inventor/elements/SoGLLazyElement.h>
#include <Inventor/elements/SoGLProjectionMatrixElement.h>
#include <Inventor/elements/SoGLRenderPassElement.h>
#include <Inventor/elements/SoGLUpdateAreaElement.h>
#include <Inventor/elements/SoGLViewingMatrixElement.h>
#include <Inventor/elements/SoGLViewportRegionElement.h>
#include <Inventor/elements/SoModelMatrixElement.h>
#include <Inventor/elements/SoViewVolumeElement.h>
#include <Inventor/nodes/SoCamera.h>
#include <stdlib.h>

#ifdef WIN32
#define drand48() (((double)rand())/double(RAND_MAX))
#endif

SO_NODE_ABSTRACT_SOURCE(SoCamera);

////////////////////////////////////////////////////////////////////////
//
// Description:
//    Constructor
//
// Use: protected

SoCamera::SoCamera()
//
////////////////////////////////////////////////////////////////////////
{
    SO_NODE_CONSTRUCTOR(SoCamera);

    SO_NODE_ADD_FIELD(viewportMapping,  (ADJUST_CAMERA));
    SO_NODE_ADD_FIELD(position,         (0.0, 0.0, 1.0));
    SO_NODE_ADD_FIELD(orientation,      (0.0, 0.0, 0.0, 1.0));
    SO_NODE_ADD_FIELD(aspectRatio,      (SO_ASPECT_SQUARE));
    SO_NODE_ADD_FIELD(nearDistance,     (1.0));
    SO_NODE_ADD_FIELD(farDistance,      (10.0));
    SO_NODE_ADD_FIELD(focalDistance,  (SoFocalDistanceElement::getDefault()));

    // Set up static info for enumerated type field
    SO_NODE_DEFINE_ENUM_VALUE(ViewportMapping, CROP_VIEWPORT_FILL_FRAME);
    SO_NODE_DEFINE_ENUM_VALUE(ViewportMapping, CROP_VIEWPORT_LINE_FRAME);
    SO_NODE_DEFINE_ENUM_VALUE(ViewportMapping, CROP_VIEWPORT_NO_FRAME);
    SO_NODE_DEFINE_ENUM_VALUE(ViewportMapping, ADJUST_CAMERA);
    SO_NODE_DEFINE_ENUM_VALUE(ViewportMapping, LEAVE_ALONE);

    // Set up info in enumerated type field
    SO_NODE_SET_SF_ENUM_TYPE(viewportMapping, ViewportMapping);

    isBuiltIn = TRUE;
}

////////////////////////////////////////////////////////////////////////
//
// Description:
//    Destructor (necessary since inline destructor is too complex)
//
// Use: private

SoCamera::~SoCamera()
//
////////////////////////////////////////////////////////////////////////
{
}

////////////////////////////////////////////////////////////////////////
//
// Description:
//    Sets the orientation of the camera so that it points toward the
//    given target point while keeping the "up" direction of the
//    camera parallel to the positive y-axis. If this is not possible,
//    it uses the positive z-axis as "up".
//
// Use: public

void
SoCamera::pointAt(const SbVec3f &targetPoint)
//
////////////////////////////////////////////////////////////////////////
{
    SbVec3f     d(targetPoint - position.getValue());

    SbRotation  yRot(SbVec3f(0,1,0), atan2(-d[0], -d[2]));
    SbRotation  xRot(SbVec3f(1,0,0), atan2(d[1], sqrtf(d[0]*d[0] + d[2]*d[2])));

    orientation.setValue(xRot * yRot);
}

////////////////////////////////////////////////////////////////////////
//
// Description:
//    Sets the camera up to view the scene under the given node. The
//    near and far clipping planes will be positioned 'slack' bounding
//    sphere radii away from the bounding box's center. A value of 1.0
//    will make the clipping planes the tightest around the bounding
//    sphere.
//
// Use: public

void
SoCamera::viewAll(SoNode *root, const SbViewportRegion &vpRegion, float slack)
//
////////////////////////////////////////////////////////////////////////
{
    SoGetBoundingBoxAction      action(vpRegion);

    // Crop the viewport region if necessary
    SbViewportRegion    croppedReg = getViewportBounds(vpRegion);

    // Find the bounding box of the scene, then adjust camera to view it
    action.apply(root);
    viewBoundingBox(action.getBoundingBox(),
                    croppedReg.getViewportAspectRatio(), slack);
}

////////////////////////////////////////////////////////////////////////
//
// Description:
//    Sets the camera up to view the scene defined by the given path.
//    The near and far clipping planes will be positioned 'slack'
//    bounding sphere radii away from the bounding box's center. A
//    value of 1.0 will make the clipping planes the tightest around
//    the bounding sphere.
//
// Use: public

void
SoCamera::viewAll(SoPath *path, const SbViewportRegion &vpRegion, float slack)
//
////////////////////////////////////////////////////////////////////////
{
    SoGetBoundingBoxAction      action(vpRegion);

    // Crop the viewport region if necessary
    SbViewportRegion    croppedReg = getViewportBounds(vpRegion);

    // Find the bounding box of the scene, then adjust camera to view it
    action.apply(path);
    viewBoundingBox(action.getBoundingBox(),
                    croppedReg.getViewportAspectRatio(), slack);
}

////////////////////////////////////////////////////////////////////////
//
// Description:
//    Returns the viewport region this camera would use to render into
//    a given viewport region, accounting for cropping.
//
// Use: public

SbViewportRegion
SoCamera::getViewportBounds(const SbViewportRegion &region) const
//
////////////////////////////////////////////////////////////////////////
{
    float       vpAspect, camAspect;

    // Start with the same region as we are given
    SbViewportRegion    croppedRegion = region;

    switch (viewportMapping.getValue()) {

      case CROP_VIEWPORT_FILL_FRAME:
      case CROP_VIEWPORT_LINE_FRAME:
      case CROP_VIEWPORT_NO_FRAME:

        vpAspect  = region.getViewportAspectRatio();
        camAspect = aspectRatio.getValue();

        // Make a smaller viewport that
        //     [a] fits within the old viewport and
        //     [b] uses the camera's aspect ratio

        if (camAspect > vpAspect)
            croppedRegion.scaleHeight(vpAspect / camAspect);

        else if (camAspect < vpAspect)
            croppedRegion.scaleWidth(camAspect / vpAspect);

        break;

      case ADJUST_CAMERA:
      case LEAVE_ALONE:
        // Neither of these adjusts the viewport size.
        break;
    }

    return croppedRegion;
}

////////////////////////////////////////////////////////////////////////
//
// Description:
//    Performs most actions that SoCamera supports.
//
// Use: extender

void
SoCamera::doAction(SoAction *action)
//
////////////////////////////////////////////////////////////////////////
{
    SbViewVolume        viewVol;
    bool                changeRegion;

    // Get the current viewport region
    const SbViewportRegion &vpReg =
        SoViewportRegionElement::get(action->getState());

    // Compute the view volume
    SoCamera::computeView(vpReg, viewVol, changeRegion);

    // Set the state
    SbVec3f dummyJitter;
    setElements(action, viewVol, changeRegion,
                changeRegion ? getViewportBounds(vpReg) : vpReg,
                FALSE, dummyJitter);
}

////////////////////////////////////////////////////////////////////////
//
// Description:
//    Does the callback action.
//
// Use: extender

void
SoCamera::callback(SoCallbackAction *action)
//
////////////////////////////////////////////////////////////////////////
{
    SoCamera::doAction(action);
}

////////////////////////////////////////////////////////////////////////
//
// Description:
//    Performs GL rendering on a camera node.
//
// Use: extender

void
SoCamera::GLRender(SoGLRenderAction *action)
//
////////////////////////////////////////////////////////////////////////
{
    SbViewportRegion    croppedReg;
    SbViewVolume        viewVol;
    SbMatrix            viewMat, projMat;
    SbVec2f             uaOrigin, uaSize;
    SbVec3f             jitterAmount;
    bool                changeRegion;
    SoState             *state = action->getState();

    // Get the current viewport region
    const SbViewportRegion &vpReg = SoGLViewportRegionElement::get(state);

    // Compute the view volume
    SoCamera::computeView(vpReg, viewVol, changeRegion);

    // Draw frame, if necessary, using current (full) viewport
    if (changeRegion) {
        croppedReg = getViewportBounds(vpReg);
        drawFrame(action, vpReg, croppedReg);
    }

    // Jitter the camera for anti-aliasing if doing multiple passes
    if (action->getNumPasses() > 1)
        jitter(action->getNumPasses(), SoGLRenderPassElement::get(state),
               changeRegion ? croppedReg : vpReg, jitterAmount);

    // Set the state
    setElements(action, viewVol, changeRegion, croppedReg,
                action->getNumPasses() > 1, jitterAmount);

    // Compute and set culling volume if different from view volume
    if (! SoGLUpdateAreaElement::get(state, uaOrigin, uaSize)) {
        SbViewVolume cvv = viewVol.narrow(uaOrigin[0], uaOrigin[1],
                                          uaSize[0],   uaSize[1]);
        SoModelMatrixElement::setCullMatrix(state, this, cvv.getMatrix());
    }
    // Otherwise, just set culling volume to be same as view volume
    else
        SoModelMatrixElement::setCullMatrix(state, this, viewVol.getMatrix());

    // Don't auto-cache above cameras:
    SoGLCacheContextElement::shouldAutoCache(state,
                SoGLCacheContextElement::DONT_AUTO_CACHE);
}

////////////////////////////////////////////////////////////////////////
//
// Description:
//    Returns amount to jitter camera in normalized device coordinates
//    (after projection) for anti-aliasing during multi-pass rendering.
//
// Use: protected, virtual

void
SoCamera::jitter(int numPasses, int curPass,
                 const SbViewportRegion &vpReg, SbVec3f &jitterAmount) const
//
////////////////////////////////////////////////////////////////////////
{
    // Get the current sample point within the pixel
    SbVec2f samplePoint;
    getJitterSample(numPasses, curPass, samplePoint);

    // Compute the jitter amount for the projection matrix. This
    // jitter will be in post-perspective space, which goes from -1 to
    // +1 in x and y. In this space, the size of a pixel is 2/width by
    // 2/height.
    const SbVec2s &vpSize = vpReg.getViewportSizePixels();
    jitterAmount[0] = samplePoint[0] * 2.0 / (float) vpSize[0];
    jitterAmount[1] = samplePoint[1] * 2.0 / (float) vpSize[1];
    jitterAmount[2] = 0.0;
}

////////////////////////////////////////////////////////////////////////
//
// Description:
//    Returns a 2D sample point within a pixel.
//
// Use: private, static

void
SoCamera::getJitterSample(int numPasses, int curPass, SbVec2f &samplePoint)
//
////////////////////////////////////////////////////////////////////////
{
    // These arrays define filter kernels to be used when the total
    // number of passes is small. For N passes, use the smallest
    // kernel that is >= N.
    static const float  kernel2[2][2]   = {{ 0.246490f,  0.249999f },
                                           {-0.246490f, -0.249999f }},
                        kernel3[3][2]   = {{-0.373411f, -0.250550f },
                                           { 0.256263f,  0.368119f },
                                           { 0.117148f, -0.117570f }},
                        kernel4[4][2]   = {{-0.208147f,  0.353730f },
                                           { 0.203849f, -0.353780f },
                                           {-0.292626f, -0.149945f },
                                           { 0.296924f,  0.149994f }},
                        kernel8[8][2]   = {{-0.334818f,  0.435331f },
                                           { 0.286438f, -0.393495f },
                                           { 0.459462f,  0.141540f },
                                           {-0.414498f, -0.192829f },
                                           {-0.183790f,  0.082102f },
                                           {-0.079263f, -0.317383f },
                                           { 0.102254f,  0.299133f },
                                           { 0.164216f, -0.054399f }},
                        kernel15[15][2] = {{ 0.285561f,  0.188437f },
                                           { 0.360176f, -0.065688f },
                                           {-0.111751f,  0.275019f },
                                           {-0.055918f, -0.215197f },
                                           {-0.080231f, -0.470965f },
                                           { 0.138721f,  0.409168f },
                                           { 0.384120f,  0.458500f },
                                           {-0.454968f,  0.134088f },
                                           { 0.179271f, -0.331196f },
                                           {-0.307049f, -0.364927f },
                                           { 0.105354f, -0.010099f },
                                           {-0.154180f,  0.021794f },
                                           {-0.370135f, -0.116425f },
                                           { 0.451636f, -0.300013f },
                                           {-0.370610f,  0.387504f }},
                        kernel24[24][2] = {{ 0.030245f,  0.136384f },
                                           { 0.018865f, -0.348867f },
                                           {-0.350114f, -0.472309f },
                                           { 0.222181f,  0.149524f },
                                           {-0.393670f, -0.266873f },
                                           { 0.404568f,  0.230436f },
                                           { 0.098381f,  0.465337f },
                                           { 0.462671f,  0.442116f },
                                           { 0.400373f, -0.212720f },
                                           {-0.409988f,  0.263345f },
                                           {-0.115878f, -0.001981f },
                                           { 0.348425f, -0.009237f },
                                           {-0.464016f,  0.066467f },
                                           {-0.138674f, -0.468006f },
                                           { 0.144932f, -0.022780f },
                                           {-0.250195f,  0.150161f },
                                           {-0.181400f, -0.264219f },
                                           { 0.196097f, -0.234139f },
                                           {-0.311082f, -0.078815f },
                                           { 0.268379f,  0.366778f },
                                           {-0.040601f,  0.327109f },
                                           {-0.234392f,  0.354659f },
                                           {-0.003102f, -0.154402f },
                                           { 0.297997f, -0.417965f }},
                        kernel66[66][2] = {{ 0.266377f, -0.218171f },
                                           {-0.170919f, -0.429368f },
                                           { 0.047356f, -0.387135f },
                                           {-0.430063f,  0.363413f },
                                           {-0.221638f, -0.313768f },
                                           { 0.124758f, -0.197109f },
                                           {-0.400021f,  0.482195f },
                                           { 0.247882f,  0.152010f },
                                           {-0.286709f, -0.470214f },
                                           {-0.426790f,  0.004977f },
                                           {-0.361249f, -0.104549f },
                                           {-0.040643f,  0.123453f },
                                           {-0.189296f,  0.438963f },
                                           {-0.453521f, -0.299889f },
                                           { 0.408216f, -0.457699f },
                                           { 0.328973f, -0.101914f },
                                           {-0.055540f, -0.477952f },
                                           { 0.194421f,  0.453510f },
                                           { 0.404051f,  0.224974f },
                                           { 0.310136f,  0.419700f },
                                           {-0.021743f,  0.403898f },
                                           {-0.466210f,  0.248839f },
                                           { 0.341369f,  0.081490f },
                                           { 0.124156f, -0.016859f },
                                           {-0.461321f, -0.176661f },
                                           { 0.013210f,  0.234401f },
                                           { 0.174258f, -0.311854f },
                                           { 0.294061f,  0.263364f },
                                           {-0.114836f,  0.328189f },
                                           { 0.041206f, -0.106205f },
                                           { 0.079227f,  0.345021f },
                                           {-0.109319f, -0.242380f },
                                           { 0.425005f, -0.332397f },
                                           { 0.009146f,  0.015098f },
                                           {-0.339084f, -0.355707f },
                                           {-0.224596f, -0.189548f },
                                           { 0.083475f,  0.117028f },
                                           { 0.295962f, -0.334699f },
                                           { 0.452998f,  0.025397f },
                                           { 0.206511f, -0.104668f },
                                           { 0.447544f, -0.096004f },
                                           {-0.108006f, -0.002471f },
                                           {-0.380810f,  0.130036f },
                                           {-0.242440f,  0.186934f },
                                           {-0.200363f,  0.070863f },
                                           {-0.344844f, -0.230814f },
                                           { 0.408660f,  0.345826f },
                                           {-0.233016f,  0.305203f },
                                           { 0.158475f, -0.430762f },
                                           { 0.486972f,  0.139163f },
                                           {-0.301610f,  0.009319f },
                                           { 0.282245f, -0.458671f },
                                           { 0.482046f,  0.443890f },
                                           {-0.121527f,  0.210223f },
                                           {-0.477606f, -0.424878f },
                                           {-0.083941f, -0.121440f },
                                           {-0.345773f,  0.253779f },
                                           { 0.234646f,  0.034549f },
                                           { 0.394102f, -0.210901f },
                                           {-0.312571f,  0.397656f },
                                           { 0.200906f,  0.333293f },
                                           { 0.018703f, -0.261792f },
                                           {-0.209349f, -0.065383f },
                                           { 0.076248f,  0.478538f },
                                           {-0.073036f, -0.355064f },
                                           { 0.145087f,  0.221726f }};

    // Determine which kernel to use and access the correct jitter amount
    if (numPasses == 2)
        samplePoint = kernel2[curPass];
    else if (numPasses == 3)
        samplePoint = kernel3[curPass];
    else if (numPasses == 4)
        samplePoint = kernel4[curPass];
    else if (numPasses <= 8)
        samplePoint = kernel8[curPass];
    else if (numPasses <= 15)
        samplePoint = kernel15[curPass];
    else if (numPasses <= 24)
        samplePoint = kernel24[curPass];
    else if (numPasses <= 66)
        samplePoint = kernel66[curPass];

    // If we don't have enough samples in the largest kernel, we'll
    // allocate an array and fill it with random samples to cover the
    // ones not in the kernel
    else {
        static float *  extraSamples = NULL;
        static int      numExtraSamples = 0;

        // Do the allocation (if necessary) only on the first pass, to
        // avoid unnecessary tests
        if (curPass == 1) {

            int numExtraNeeded = numPasses - 66;

            if (numExtraSamples < numExtraNeeded) {
                if (extraSamples != NULL)
                    delete extraSamples;
                extraSamples = new float [numExtraNeeded * 2];

                // Set 2 coords of sample to random number between -1 and +1.
                for (int i = 0; i < 2 * numExtraNeeded; i++)
                    extraSamples[i] = 2.0 * drand48() - 1.0;
            }
        }

        if (curPass < 66)
            samplePoint = kernel66[curPass];
        else
            samplePoint.setValue(extraSamples[(curPass - 66) * 2 + 0],
                                 extraSamples[(curPass - 66) * 2 + 1]);

    }
}

////////////////////////////////////////////////////////////////////////
//
// Description:
//    Does the getBoundingBox action. If the isCameraSpace() flag is
//    set in the action, this also transforms the model matrix to set
//    up camera space.
//
// Use: extender

void
SoCamera::getBoundingBox(SoGetBoundingBoxAction *action)
//
////////////////////////////////////////////////////////////////////////
{
    // Do the usual stuff first
    SoCamera::doAction(action);
}

////////////////////////////////////////////////////////////////////////
//
// Description:
//    Sets up viewing info for event handling.
//
// Use: extender

void
SoCamera::handleEvent(SoHandleEventAction *action)
//
////////////////////////////////////////////////////////////////////////
{
    // Set only a subset of the elements for this action

    SbViewVolume        viewVol;
    bool                changeRegion;
    SoState             *state = action->getState();

    // Get the current viewport region
    const SbViewportRegion &vpReg = SoViewportRegionElement::get(state);

    // Compute the view volume
    SoCamera::computeView(vpReg, viewVol, changeRegion);

    // Set necessary elements in state
    SoViewVolumeElement::set(state, this, viewVol);
    if (changeRegion)
        SoViewportRegionElement::set(state, getViewportBounds(vpReg));
}

////////////////////////////////////////////////////////////////////////
//
// Description:
//    Sets up viewing info for ray picking.
//
// Use: extender

void
SoCamera::rayPick(SoRayPickAction *action)
//
////////////////////////////////////////////////////////////////////////
{
    SoCamera::doAction(action);

    // Tell the action how to set up world space view
    action->computeWorldSpaceRay();
}

////////////////////////////////////////////////////////////////////////
//
// Description:
//    Computes the view volume the camera represents, based on the
//    given viewport region. Returns TRUE in changeRegion if the
//    viewport region needs to be adjusted based on the current
//    viewport mapping, meaning that it has to be changed in the
//    state.
//
// Use: private

void
SoCamera::computeView(const SbViewportRegion &vpReg,
                      SbViewVolume &viewVol, bool &changeRegion)
//
////////////////////////////////////////////////////////////////////////
{
    float       camAspect, vpAspect;

    changeRegion = FALSE;

    camAspect = aspectRatio.getValue();

    switch (viewportMapping.getValue()) {
      case CROP_VIEWPORT_FILL_FRAME:
      case CROP_VIEWPORT_LINE_FRAME:
      case CROP_VIEWPORT_NO_FRAME:
        changeRegion = TRUE;
        viewVol = getViewVolume(camAspect);
        break;

      case ADJUST_CAMERA:
        vpAspect = vpReg.getViewportAspectRatio();
        viewVol = getViewVolume(vpAspect);
        // Adjust size of view volume if it will fill viewport better
        if (vpAspect < 1.0)
            viewVol.scale(1.0 / vpAspect);
        break;

      case LEAVE_ALONE:
        // Do nothing. The window specified by the camera will be
        // stretched to fit into the current viewport.
        viewVol = getViewVolume(camAspect);
        break;
    }
}

////////////////////////////////////////////////////////////////////////
//
// Description:
//    Sets relevant info in elements in state.
//
// Use: private

void
SoCamera::setElements(SoAction *action, SbViewVolume &viewVol,
                      bool setRegion, const SbViewportRegion &vpReg,
                      bool doJitter, const SbVec3f &jitterAmount)
//
////////////////////////////////////////////////////////////////////////
{
    SoState     *state = action->getState();
    SbMatrix    viewMat, projMat;

    // Compute viewing and projection matrices
    viewVol.getMatrices(viewMat, projMat);

    // Jitter if necessary
    if (doJitter) {
        SbMatrix m;
        m.setTranslate(jitterAmount);
        projMat.multRight(m);
    }

    // Set necessary elements in state
    SoProjectionMatrixElement::set(state, this, projMat);

    // Set the viewport region only if it has changed
    if (setRegion)
        SoViewportRegionElement::set(state, vpReg);

    // If the current model matrix is not identity, the camera has to
    // be transformed by it. This is equivalent to transforming the
    // world by the inverse of the model matrix. So we set the viewing
    // matrix to be the product of the inverse of the model matrix and
    // the viewMat.
    bool modelIsIdent;
    const SbMatrix &modelMat = SoModelMatrixElement::get(state, modelIsIdent);
    if (! modelIsIdent) {
        viewMat.multRight(modelMat.inverse());

        // Also, transform the view volume by the model matrix
        viewVol.transform(modelMat);
    }

    SoViewVolumeElement::set(state, this, viewVol);
    SoViewingMatrixElement::set(state, this, viewMat);
    
    // 2004-05-25 Felix: Set focal distance element
    SoFocalDistanceElement::set(state, this, focalDistance.getValue());
}

////////////////////////////////////////////////////////////////////////
//
// Description:
//    Draws cropping frame for use when rendering.
//
// Use: private

void
SoCamera::drawFrame(SoGLRenderAction *action,
                    const SbViewportRegion &vpReg,
                    const SbViewportRegion &croppedReg)
//
////////////////////////////////////////////////////////////////////////
{
// Frame color as RGB. In color index mode, just use the background
// color, since we have no idea what's in the color map.
#define GREY1           .38, .38, .38
#define GREY1_INDEX     0

    // Get origin and size of viewports in pixels
    const SbVec2s &     vpOrig =      vpReg.getViewportOriginPixels();
    const SbVec2s &     vpSize =      vpReg.getViewportSizePixels();
    const SbVec2s &     cropLL = croppedReg.getViewportOriginPixels();
    const SbVec2s &     cropUR = croppedReg.getViewportSizePixels() + cropLL;

    // Save stuff we're going to change explicitly
    glPushAttrib(GL_ENABLE_BIT | GL_CURRENT_BIT |
                 GL_POLYGON_BIT | GL_LINE_BIT);

    glDisable(GL_LIGHTING);
    glColor3f(GREY1);

    // OK to blow away the old projection matrix, because it will be 
    // changed anyway by the camera's render action right after this...
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0.0, vpSize[0] - 1.0, 0.0, vpSize[1] - 1.0, -1.0, 1.0);

    // Ditto for the viewing matrix
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();

    if (viewportMapping.getValue() == CROP_VIEWPORT_LINE_FRAME)  {
        // Draw a rectangle one pixel bigger than the camera's viewport
        glPolygonMode(GL_FRONT, GL_LINE);
        glLineWidth(1.0);
        glDisable(GL_LINE_STIPPLE);
        glRects(cropLL[0] - 1 - vpOrig[0], cropLL[1] - 1 - vpOrig[1],
                cropUR[0] + 1 - vpOrig[0], cropUR[1] + 1 - vpOrig[1]);
    }
    else if (viewportMapping.getValue() == CROP_VIEWPORT_FILL_FRAME) {
        glPolygonMode(GL_FRONT, GL_FILL);
        glDisable(GL_POLYGON_STIPPLE);

        if (croppedReg.getViewportAspectRatio() >
            vpReg.getViewportAspectRatio()) {

            // Draw filled rectangles for a border
            glRects(0, 0,
                    vpSize[0] - 1, cropLL[1] - vpOrig[1] - 1);
            glRects(0, cropUR[1] - vpOrig[1] + 1 ,
                    vpSize[0] - 1, vpSize[1] - 1);
        }
        else {
            glRects(0, 0,
                    cropLL[0] - vpOrig[0] - 1, vpSize[1] - 1);
            glRects(cropUR[0] - vpOrig[0] + 1, 0,
                    vpSize[0] - 1, vpSize[1] - 1);
        }
    }

    glPopMatrix();
    glPopAttrib();

#undef GREY1
#undef GREY1_INDEX
}
