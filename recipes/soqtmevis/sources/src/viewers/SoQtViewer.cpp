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
 * Copyright (C) 1990-93   Silicon Graphics, Inc.
 * Author(s): Alain Dumesny
 * Ported to Qt4 by MeVis (http://www.mevis.de), 2006
 */

#include <cmath>
#include <cstdio>
#include <cstring>

#include <Inventor/SbTypeDefs.h>
#include <Inventor/SbBox.h>
#include <Inventor/SbLinear.h>
#include <Inventor/SbPList.h>
#include <Inventor/SbViewportRegion.h>
#include <Inventor/SoDB.h>
#include <Inventor/SoPath.h>
#include <Inventor/SoPath.h>
#include <Inventor/SoPickedPoint.h>
#include <Inventor/actions/SoGetBoundingBoxAction.h>
#include <Inventor/errors/SoDebugError.h>
#include <Inventor/nodes/SoPackedColor.h>
#include <Inventor/nodes/SoMaterialBinding.h>
#include <Inventor/nodes/SoComplexity.h>
#include <Inventor/nodes/SoDrawStyle.h>
#include <Inventor/nodes/SoGroup.h>
#include <Inventor/nodes/SoLightModel.h>
#include <Inventor/nodes/SoCamera.h>
#include <Inventor/nodes/SoResetTransform.h>
#include <Inventor/nodes/SoRotation.h>
#include <Inventor/nodes/SoSeparator.h>
#include <Inventor/nodes/SoSwitch.h>
#include <Inventor/nodes/SoLocateHighlight.h>
#include <Inventor/sensors/SoFieldSensor.h>
#include <Inventor/fields/SoSFTime.h>
// #include <Inventor/Xt/devices/SoXtInputFocus.h>
// #include <Inventor/Xt/SoXtClipboard.h>
#include <Inventor/Qt/viewers/SoQtViewer.h>
#include <QEvent>
#include <QKeyEvent>
#include <QMouseEvent>
#include <QApplication>

// keep a pointer to global time, since we are going to access it a lot.
SoSFTime *SoQtViewer::viewerRealTime = nullptr;


SoQtViewer::SoQtViewer (SoQtViewer::Type t, QWidget* parent, Qt::WindowFlags f)
: SoQtRenderArea (parent, f, false)
, SoQtCameraController(t)
{
    // init local vars
    viewingFlag = TRUE;
    altSwitchBack = FALSE;
    altSwitchingEnabled = TRUE;
    keyCommandsEnabled = TRUE;
    cursorEnabledFlag = TRUE;
    interactiveFlag = FALSE;
    startCBList = new SoCallbackList;
    finishCBList = new SoCallbackList;
    interactiveCount = 0;
    bufferType = isDoubleBuffer() ? BUFFER_DOUBLE : BUFFER_SINGLE;
    stereoOffset = 3.0;
    sceneSize = 0.0;    // not computed yet.
    viewerSpeed = 1.0;  // default. SoQtFullViewer add UI to increase/decrease

    if (! viewerRealTime) {
        viewerRealTime = (SoSFTime *) SoDB::getGlobalField("realTime");
    }

    //
    // build the small internal graph (nodes used for draw style stuff)
    //
    sceneRoot           = new SoSeparator(4);
    drawStyleSwitch     = new SoSwitch(6);
    drawStyleNode       = new SoDrawStyle;
    lightModelNode      = new SoLightModel;
    colorNode           = new SoPackedColor;
    matBindingNode      = new SoMaterialBinding;
    complexityNode      = new SoComplexity;

    // note: we cannot setSceneGraph on the renderArea in the constructor
    // since it calls virtual functions, and all of our members aren't
    // initialized yet. We'll call it the first time our setSceneGraph
    // is called.
    sceneRoot->ref();
    sceneRoot->renderCaching.setValue(SoSeparator::OFF); // no caching there
    sceneRoot->renderCulling.setValue(SoSeparator::OFF); // no culling there
    sceneRoot->addChild(drawStyleSwitch);
    drawStyleSwitch->addChild(drawStyleNode);
    drawStyleSwitch->addChild(lightModelNode);
    drawStyleSwitch->addChild(colorNode);
    drawStyleSwitch->addChild(matBindingNode);
    drawStyleSwitch->addChild(complexityNode);

    // set the draw style vars and fields that don't change - once we
    // have a context, will will use glGetString() to pick a better default
    // draw style.
    stillDrawStyle = VIEW_AS_IS;
    interactiveDrawStyle = VIEW_SAME_AS_STILL;
    drawStyleSwitch->whichChild = SO_SWITCH_NONE;

    drawStyleNode->setOverride(TRUE); // only use style field
    drawStyleNode->pointSize = 3.0;
    drawStyleNode->lineWidth.setIgnored(TRUE);
    drawStyleNode->linePattern.setIgnored(TRUE);

    lightModelNode->setOverride(TRUE);

    colorNode->setOverride(TRUE);

    matBindingNode->setOverride(TRUE);
    matBindingNode->value = SoMaterialBinding::OVERALL;

    complexityNode->setOverride(TRUE);
    complexityNode->textureQuality = 0; // always turn texture off under switch
    complexityNode->value = 0.15;
    complexityNode->textureQuality.setIgnored(TRUE);

    addStartCallback(SoQtViewer::drawStyleStartCallback);
    addFinishCallback(SoQtViewer::drawStyleFinishCallback);

    SoQtCameraController::setSceneRoot(sceneRoot, 1);
}


SoQtViewer::~SoQtViewer()
{
    // detach everything
    if ( sceneGraph != nullptr ) {
        setSceneGraph(nullptr);
    }
    sceneRoot->unref();

    // delete everything
    delete startCBList;
    delete finishCBList;
}


void
SoQtViewer::resizeGL (int width, int height)
{
    SoQtRenderArea::resizeGL(width, height);
    SoQtCameraController::setSceneSize(SbVec2s(width, height) * getGlxDevicePixelRatio());
}


void
SoQtViewer::setSceneGraph(SoNode *newScene)
{
    // if we haven't already given the render area a scene graph sceneRoot,
    // give it the scene graph now. This is a one shot deal, which
    // cannot be done in the constructor.
    if (SoQtRenderArea::getSceneGraph() == nullptr) {
        SoQtRenderArea::setSceneGraph(sceneRoot);
    }

    SoQtCameraController::setSceneGraph(newScene);

    // recompute the scene size variables...
    recomputeSceneSize();
}

void
SoQtViewer::recomputeSceneSize()
{
    if (! sceneGraph || ! sceneRoot) {
        sceneSize = 0.0;
        return;
    }

    // Use assignment notation to disambiguate from expression (edison)
    SoGetBoundingBoxAction bboxAct = SoGetBoundingBoxAction(SbViewportRegion(getGlxSize()));
    bboxAct.apply(sceneRoot);
    SbBox3f bbox = bboxAct.getBoundingBox();

    if (bbox.isEmpty()) {
        sceneSize = 0.0;
        return;
    }

    float x, y, z;
    bbox.getSize(x, y, z);
    sceneSize = (x > z) ? x : z;
    if (y > sceneSize) {
        sceneSize = y;
    }
    if (sceneSize <= 0.0) {
        sceneSize = 0.0;
    }
}


SoNode *
SoQtViewer::getSceneGraph()
{
    return sceneGraph;
}


void
SoQtViewer::setCamera(SoCamera *newCamera, SbBool createdCamera)
{
    // check for trivual return
    if (camera == newCamera) {
        return;
    }
    if (camera) {
        if (viewingFlag) {
            setViewing(FALSE);
            viewingFlag = TRUE;  // can later be turned on
        }
    }
    SoQtCameraController::setCamera(newCamera, createdCamera);
    if (camera) {
        if (viewingFlag) {
            viewingFlag = FALSE;  // enables the routine to be called
            setViewing(TRUE);
        }
    }
}


void
SoQtViewer::setAltSwitchingEnabled (SbBool on)
{
    altSwitchingEnabled = on;
}


void
SoQtViewer::setKeyCommandsEnabled (SbBool on)
{
    keyCommandsEnabled = on;
}


void
SoQtViewer::setViewing(SbBool flag)
{
    if (flag == viewingFlag) {
        return;
    }

    viewingFlag = flag;

    // if we are goind into viewing mode, then de-highlight any
    // currently highlighted nodes (since the object will never receive
    // any motion events).
    if (viewingFlag) {
        SoGLRenderAction *glAct = getGLRenderAction();
        if (glAct) {
            SoLocateHighlight::turnOffCurrentHighlight(glAct);
        }
    }
}


void
SoQtViewer::setCursorEnabled(SbBool flag)
{
    cursorEnabledFlag = flag;
}


void
SoQtViewer::setAutoClipping(SbBool flag)
{
    if (isAutoClipping() == flag) { return; }

    SoQtCameraController::setAutoClipping(flag);

    // cause a redraw to correctly place the near and far plane now that
    // auto clipping is on.
    if (isAutoClipping()) {
        scheduleRedraw();
    }
}


void
SoQtViewer::setStereoViewing(SbBool flag)
{
    if (flag != isStereoViewing()) {
        setStereoBuffer(flag);
    }
}


SbBool
SoQtViewer::isStereoViewing()
{
    // done in SoXtGLWidget
    return isStereoBuffer();
}


void
SoQtViewer::setDrawStyle(SoQtViewer::DrawType type, SoQtViewer::DrawStyle style)
{
    if (type == STILL) {
        if (stillDrawStyle == style) {
            return;
        }
        if (style == VIEW_SAME_AS_STILL) {
#ifdef DEBUG
            SoDebugError::post("SoQtViewer::setDrawStyle",
                "illegal VIEW_SAME_AS_STILL draw style passed for STILL !");
#endif
            return;
        }
        stillDrawStyle = style;

        if (! interactiveFlag || interactiveDrawStyle == VIEW_SAME_AS_STILL
            || (interactiveDrawStyle == VIEW_NO_TEXTURE && style != VIEW_AS_IS))
        {
            setCurrentDrawStyle(style);
        } else if (interactiveFlag && interactiveDrawStyle == VIEW_NO_TEXTURE &&
            style == VIEW_AS_IS)
        {
            setCurrentDrawStyle(interactiveDrawStyle);
        }
    } else {
        // else it type == INTERACTIVE

        if (interactiveDrawStyle == style) {
            return;
        }
        interactiveDrawStyle = style;

        if (interactiveFlag) {
            if (style == VIEW_SAME_AS_STILL ||
               (style == VIEW_NO_TEXTURE && stillDrawStyle != VIEW_AS_IS))
            {
                setCurrentDrawStyle(stillDrawStyle);
            } else {
                setCurrentDrawStyle(style);
            }
        }
    }
}


void
SoQtViewer::setCurrentDrawStyle(SoQtViewer::DrawStyle style)
{
    if (style != VIEW_AS_IS) {
        drawStyleSwitch->whichChild = SO_SWITCH_ALL;
    }
    switch(style) {
        case VIEW_AS_IS:
            drawStyleSwitch->whichChild = SO_SWITCH_NONE;
            break;

        case VIEW_HIDDEN_LINE:
            // texture is always off under the switch node.
            // List only stuff common to both rendering passes
            // (the rest is done when rendering)
            drawStyleNode->style.setIgnored(FALSE);
            drawStyleNode->pointSize.setIgnored(TRUE);
            lightModelNode->model = SoLightModel::BASE_COLOR;
            lightModelNode->model.setIgnored(FALSE);
            complexityNode->type.setIgnored(TRUE);
            complexityNode->value.setIgnored(TRUE);
            complexityNode->textureQuality.setIgnored(FALSE);
            break;

        case VIEW_NO_TEXTURE:
        case VIEW_LOW_COMPLEXITY:
            // texture is always off under the switch node
            drawStyleNode->style.setIgnored(TRUE);
            drawStyleNode->pointSize.setIgnored(TRUE);
            lightModelNode->model.setIgnored(TRUE);
            colorNode->orderedRGBA.setIgnored(TRUE);
            matBindingNode->value.setIgnored(TRUE);
            complexityNode->type.setIgnored(TRUE);
            complexityNode->value.setIgnored(style != VIEW_LOW_COMPLEXITY);
            complexityNode->textureQuality.setIgnored(style == VIEW_LOW_COMPLEXITY);
            break;

        case VIEW_LINE:
        case VIEW_LOW_RES_LINE:
        case VIEW_POINT:
        case VIEW_LOW_RES_POINT:
        case VIEW_WIREFRAME_OVERLAY:
            // texture is always off under the switch node
            drawStyleNode->style = (style == VIEW_LINE || style == VIEW_LOW_RES_LINE) ?
                SoDrawStyle::LINES : SoDrawStyle::POINTS;
            drawStyleNode->style.setIgnored(FALSE);
            drawStyleNode->pointSize.setIgnored(style != VIEW_POINT && style != VIEW_LOW_RES_POINT);
            lightModelNode->model = SoLightModel::BASE_COLOR;
            lightModelNode->model.setIgnored(FALSE);
            colorNode->orderedRGBA.setIgnored(TRUE);
            matBindingNode->value.setIgnored(TRUE);

            // Force a lower complexity for the low res draw styles
            // ??? this only works if the object didn't have
            // ??? something lower in the first place...
            if (style == VIEW_LOW_RES_LINE || style == VIEW_LOW_RES_POINT) {
                complexityNode->type = SoComplexity::OBJECT_SPACE;
                complexityNode->type.setIgnored(FALSE);
                complexityNode->value.setIgnored(FALSE);
            } else {
                complexityNode->type.setIgnored(TRUE);
                complexityNode->value.setIgnored(TRUE);
            }
            complexityNode->textureQuality.setIgnored(FALSE);
            break;

        case VIEW_BBOX:
            // texture is always off under the switch node
            drawStyleNode->style = SoDrawStyle::LINES;
            drawStyleNode->style.setIgnored(FALSE);
            drawStyleNode->pointSize.setIgnored(TRUE);
            lightModelNode->model = SoLightModel::BASE_COLOR;
            lightModelNode->model.setIgnored(FALSE);
            colorNode->orderedRGBA.setIgnored(TRUE);
            matBindingNode->value.setIgnored(TRUE);
            complexityNode->type = SoComplexity::BOUNDING_BOX;
            complexityNode->type.setIgnored(FALSE);
            complexityNode->value.setIgnored(TRUE);
            complexityNode->textureQuality.setIgnored(FALSE);
            break;

        case VIEW_SAME_AS_STILL:
#ifdef DEBUG
            SoDebugError::post("SoQtViewer::setCurrentDrawStyle", "VIEW_SAME_AS_STILL was passed !");
#endif
            break;
    }
}


SoQtViewer::DrawStyle
SoQtViewer::getDrawStyle(SoQtViewer::DrawType type)
{
    return (type == STILL ? stillDrawStyle : interactiveDrawStyle);
}


void
SoQtViewer::setDoubleBuffer(SbBool flag)

{
    setBufferingType(flag ? SoQtViewer::BUFFER_DOUBLE : SoQtViewer::BUFFER_SINGLE);
}


void
SoQtViewer::setBufferingType(SoQtViewer::BufferType type)
{
    if (bufferType == type) {
        return;
    }

    // remove interactive callback
    if (bufferType == BUFFER_INTERACTIVE) {
        removeStartCallback(SoQtViewer::bufferStartCallback);
        removeFinishCallback(SoQtViewer::bufferFinishCallback);
    }

    bufferType = type;

    switch(bufferType) {
        case BUFFER_SINGLE:
            SoQtRenderArea::setDoubleBuffer(FALSE);
            break;
        case BUFFER_DOUBLE:
            SoQtRenderArea::setDoubleBuffer(TRUE);
            break;
        case BUFFER_INTERACTIVE:
            SoQtRenderArea::setDoubleBuffer(FALSE);
            addStartCallback(SoQtViewer::bufferStartCallback);
            addFinishCallback(SoQtViewer::bufferFinishCallback);
            break;
    }
}


void
SoQtViewer::setSeekMode(SbBool flag)
{
    if (isViewing()) {
        SoQtCameraController::setSeekMode(flag);
    }

}


void
SoQtViewer::actualRedraw()
{
    if (isAutoClipping() && ! isStereoViewing()) {
        adjustCameraClippingPlanes();
    }

    // update the headlight if necessary
    updateHeadlight();

    // make sure that we have a valid sceneSize value - but don't compute
    // a new sceneSize value for every redraw since the walking speed should
    // really be constant.
    if (sceneSize == 0.0) {
        recomputeSceneSize();
    }

    // Check to see if we are in stereo mode, if so draw the scene
    // twice with the camera offseted between the two views, else
    // do a simple redraw.

    if ( isStereoViewing() && camera != nullptr) {

        // Check the camera type, since stereo is different:
        //
        // Ortho camera: stereo is accomplished by simply rorating
        // the camera (around the point of interest) by 6 degree.
        //
        // Perspective camera: we translate the camera and rotate
        // them to look at the same point of interest (idealy we also would
        // make sure the plane of convergence is exactly the same for
        // both perspective views, unfortunatly we cannot do this with
        // the current symetric view volumes).
        //

        // save the camera original values to restore the camera after
        // both views are rendered. This means we will use this in between
        // left and right view for things like picking.
        SbVec3f     camOrigPos = camera->position.getValue();
        SbRotation  camOrigRot = camera->orientation.getValue();

        // get the camera focal point
        SbMatrix mx;
        mx = camOrigRot;
        SbVec3f forward( -mx[2][0], -mx[2][1], -mx[2][2]);
        float radius = camera->focalDistance.getValue();
        SbVec3f center = camOrigPos + radius * forward;


        //
        // change the camera for the LEFT eye view, and render
        //
        glDrawBuffer( isDoubleBuffer() ? GL_BACK_LEFT : GL_FRONT_LEFT);
        // rotate the camera by - stereoOffset/2 degrees
        camera->orientation =
            SbRotation(SbVec3f(0, 1, 0), - stereoOffset * M_PI / 360.0) * camOrigRot;

        // reposition camera to look at pt of interest
        mx = camera->orientation.getValue();
        forward.setValue( -mx[2][0], -mx[2][1], -mx[2][2]);
        camera->position = center - radius * forward;

        if (isAutoClipping()) {
            adjustCameraClippingPlanes();
        }
        doRendering();

        //
        // change the camera for the RIGHT eye view, and render
        //
        glDrawBuffer( isDoubleBuffer() ? GL_BACK_RIGHT : GL_FRONT_RIGHT);
        // rotate the camera by + stereoOffset/2 degrees
        camera->orientation =
            SbRotation(SbVec3f(0, 1, 0), stereoOffset * M_PI / 360.0) * camOrigRot;

        // reposition camera to look at pt of interest
        mx = camera->orientation.getValue();
        forward.setValue( -mx[2][0], -mx[2][1], -mx[2][2]);
        camera->position = center - radius * forward;

        if (isAutoClipping()) {
            adjustCameraClippingPlanes();
        }
        doRendering();

        // reset the camera original values now that we are done rendering
        // the stereo views (leave aspect ratio to do correct picking).
        camera->enableNotify(FALSE); // don't cause a redraw
        camera->position = camOrigPos;
        camera->orientation = camOrigRot;
        camera->enableNotify(TRUE);

        // restore to draw to both buffer (viewer feedback)
        glDrawBuffer( isDoubleBuffer() ? GL_BACK : GL_FRONT);
    } else {
        // not stereo viewing, so do the regular rendering....
        doRendering();
    }
}


void
SoQtViewer::doRendering()
{
    setZbufferState();

    // check if we need two pass rendering for hidden line rendering
    SbBool drawHiddenLine =
        (stillDrawStyle == VIEW_HIDDEN_LINE && (! interactiveFlag ||
                                interactiveDrawStyle == VIEW_NO_TEXTURE ||
                                interactiveDrawStyle == VIEW_LOW_COMPLEXITY ||
                                interactiveDrawStyle == VIEW_SAME_AS_STILL))
        || (interactiveFlag && interactiveDrawStyle == VIEW_HIDDEN_LINE);

    if (camera != nullptr && drawHiddenLine) {

        // ??? what do we do about highlights ??

        // the smaller the near clipping plane is relative to the far
        // plane, the smaller the zbuffer offset needs to be (because
        // the granularity will be pretty big). The closer the clipping
        // planes are relative to each other, the bigger the zbuffer offset
        // needs to be (because the zbuffer granularity will be small).
        // The scale factor was found empirically to work best with the
        // current settings of near/far.
        float zOffset = camera->nearDistance.getValue() /
            (40 * camera->farDistance.getValue());

        // render the first pass as solid, using the background color
        // for the object base color.
        drawStyleNode->style = SoDrawStyle::FILLED;
        colorNode->orderedRGBA = getBackgroundColor().getPackedValue();
        colorNode->orderedRGBA.setIgnored(FALSE);
        matBindingNode->value.setIgnored(FALSE);

        // ??? this should match the SoQtRenderArea::actualRedraw()
        // ??? method exactly (apart for not clearing the z-buffer)
        glDepthRange(zOffset, 1); // enable wireframe to be draw on top
        getSceneManager()->render(isClearBeforeRender(), TRUE);

        // render the second pass as wireframe
        // (the first pass rendered the objects solid with base color
        // set to the background color to set the zbuffer values)
        drawStyleNode->style = SoDrawStyle::LINES;
        colorNode->orderedRGBA.setIgnored(TRUE);
        matBindingNode->value.setIgnored(TRUE);

        // ??? this should match the SoQtRenderArea::actualRedraw()
        // ??? method exactly (apart for not clearing the color and z-buffer)
        glDepthRange(0,1-zOffset); // enable wireframe to be draw on top
        getSceneManager()->render(FALSE, FALSE);

        glDepthRange(0, 1); // restore the range
    } else {
        // ??? this should match the SoQtRenderArea::actualRedraw()
        // ??? method exactly (apart for not clearing the z-buffer)
        getSceneManager()->render(isClearBeforeRender(), ! isZbufferOff());
    }
}


SbBool
SoQtViewer::isZbufferOff()
{
    DrawStyle style = (interactiveFlag ? interactiveDrawStyle : stillDrawStyle);
    if (interactiveFlag && interactiveDrawStyle == VIEW_SAME_AS_STILL) {
        style = stillDrawStyle;
    }

    // for these draw styles, turn the zbuffer off
    return (style == VIEW_LOW_RES_LINE || style == VIEW_LOW_RES_POINT
        || style == VIEW_BBOX);
}


void
SoQtViewer::setZbufferState()
{
    if (isZbufferOff()) {
        glDisable(GL_DEPTH_TEST);
    } else {
        glEnable(GL_DEPTH_TEST);
    }
}


void
SoQtViewer::processEvent (QEvent* anyEvent)
{
    bool isMouseEvent = false;
    // check for special key which turns viewing on/off
    if (anyEvent->type() == QEvent::KeyPress) {
        QKeyEvent *ke = (QKeyEvent *)anyEvent;
        if (keyCommandsEnabled && (ke->key() == Qt::Key_Escape)) {
            setViewing( !isViewing() );  // toggle the viewing mode...
            ke->accept();
        } else if (altSwitchingEnabled && !altSwitchBack && (ke->key() == Qt::Key_Alt)) {
            // Alt-key goes from PICK to VIEW if
            // 1] we are not in VIEW mode already
            // 2] no mouse buttons are pressed
            altSwitchBack = TRUE;   // later return back
            setViewing(!isViewing());
        }
    } else if (anyEvent->type() == QEvent::KeyRelease) {
        QKeyEvent *ke = (QKeyEvent *)anyEvent;
        if (altSwitchBack && (ke->key() == Qt::Key_Alt)) {
            // if Alt-key, then return to PICK (if we had switched)
            setViewing(!isViewing());
            altSwitchBack = FALSE;  // clear the flag
        }
    } else if (anyEvent->type() == QEvent::Enter) {
        // because the application might use Alt-key for motif menu
        // accelerators we might not receive a key-up event, so make sure
        // to reset any Alt mode (temporary viewing) when the mouse re-enters
        // the window.
        Qt::KeyboardModifiers modifiers = QApplication::keyboardModifiers();
        if (altSwitchingEnabled && !altSwitchBack && (modifiers & Qt::AltModifier)) {
            altSwitchBack = TRUE;   // later return back
            setViewing(!isViewing());
        } else if (altSwitchBack && !(modifiers & Qt::AltModifier)) {
            setViewing(!isViewing());
            altSwitchBack = FALSE;  // clear the flag
        }
    } else if (anyEvent->type() == QEvent::MouseButtonPress ||
               anyEvent->type() == QEvent::MouseButtonRelease ||
               anyEvent->type() == QEvent::MouseButtonDblClick ||
               anyEvent->type() == QEvent::MouseMove)
    {
        isMouseEvent = true;
        if (altSwitchBack) {
          // for the rare circumstances where we do not get the KeyRelease for the Alt key
          QInputEvent* ie = static_cast<QInputEvent*>(anyEvent);
          if ((ie->modifiers() & Qt::AltModifier) == 0) {
            setViewing(!isViewing());
            altSwitchBack = FALSE;  // clear the flag
          }
        }
    }

    // send the event to the scene graph and application callback if viewing
    // is (temporarily) off or if it is a non-mouse event we didn't use
    if ( (isCurrentlyPicking() || !isMouseEvent) && !anyEvent->isAccepted()) {
        SoQtRenderArea::processEvent (anyEvent);
    }
    if (camera != nullptr && keyCommandsEnabled &&
        !anyEvent->isAccepted() && anyEvent->type() == QEvent::KeyPress)
    {
        // additional camera control keys
        QKeyEvent *ke = (QKeyEvent *)anyEvent;
        switch ( ke->key() ) {
            case Qt::Key_Home:
                resetToHomePosition();
                ke->accept();
                break;
            case Qt::Key_S:
                setSeekMode( !isSeekMode() );
                // ??? this is kind of a hack, but it is needed
                // ??? until a better solution is found
                if ( isSeekMode() && interactiveCount != 0 ) {
                    interactiveCount = 0;
                    finishCBList->invokeCallbacks(this);
                }
                ke->accept();
                break;
            case Qt::Key_Left:
            case Qt::Key_Up:
            case Qt::Key_Right:
            case Qt::Key_Down:
                arrowKeyPressed (ke->key());
                scheduleRedraw();
                ke->accept();
                break;
        }
    }
}


void
SoQtViewer::interactiveCountInc()
{
    interactiveCount++;

    if (interactiveCount == 1) {
        startCBList->invokeCallbacks(this);
    }
}


void
SoQtViewer::interactiveCountDec()
{
    if (interactiveCount > 0) {
        interactiveCount--;
        if (interactiveCount == 0) {
            finishCBList->invokeCallbacks(this);
        }
    }
}


//
////////////////////////////////////////////////////////////////////////
// static callbacks stubs
////////////////////////////////////////////////////////////////////////
//



void
SoQtViewer::bufferStartCallback(void *, SoQtViewer *v)
{
    v->SoQtRenderArea::setDoubleBuffer(TRUE);
}

void
SoQtViewer::bufferFinishCallback(void *, SoQtViewer *v)
{
    v->SoQtRenderArea::setDoubleBuffer(FALSE);
}

void
SoQtViewer::drawStyleStartCallback(void *, SoQtViewer *v)
{
    v->interactiveFlag = TRUE;  // must happen first

    // if still and move draw styles are the same, return...
    if (v->interactiveDrawStyle == VIEW_SAME_AS_STILL ||
        v->interactiveDrawStyle == v->stillDrawStyle)
    {
        return;
    }

    // if we have "MOVE NO TEXTURE", then we have nothing
    // to do if we have a current draw style (since they all have
    // texturing turned off in the first place).
    if (v->interactiveDrawStyle == VIEW_NO_TEXTURE &&
        v->stillDrawStyle != VIEW_AS_IS)
    {
        return;
    }

    v->setCurrentDrawStyle(v->interactiveDrawStyle);
}

void
SoQtViewer::drawStyleFinishCallback(void *, SoQtViewer *v)
{
    v->interactiveFlag = FALSE;  // must happen first

    // if still and move draw styles are the same, return...
    if (v->interactiveDrawStyle == VIEW_SAME_AS_STILL ||
        v->interactiveDrawStyle == v->stillDrawStyle)
    {
        return;
    }

    // if we have "MOVE NO TEXTURE", then we have nothing
    // to do if we have a current draw style (since they all have
    // texturing turned off in the first place).
    if (v->interactiveDrawStyle == VIEW_NO_TEXTURE &&
        v->stillDrawStyle != VIEW_AS_IS)
    {
        return;
    }

    v->setCurrentDrawStyle(v->stillDrawStyle);
}


//
////////////////////////////////////////////////////////////////////////
// viewer feedback convenience routines
////////////////////////////////////////////////////////////////////////
//



/*
 * Defines
 */

// color used in feedback
#define DARK_COLOR      glColor3ub(90, 90, 90)
#define LIGHT_COLOR     glColor3ub(230, 230, 230)

#define LINE_THIN   3   // line thickness used in feedback
#define LINE_THICK  (LINE_THIN + 2)
#define CROSS       8   // size of cross hair at screen center for Roll
#define RADIUS      15  // radius of center circle (in pix) for Roll
#define ANGLE_LEN   14   // angular size in degrees of Roll anchor


/*
 * Globals
 */

#define ARROW_SIZE  6.0 // size in pix of arrow head

// anchor arrow head description
static float arrow_data[3][3] = {
    { -ARROW_SIZE, 0, 0 },
    { 0, 2*ARROW_SIZE, 0 },
    { ARROW_SIZE, 0, 0 }
};


/*
 * Macros
 */

#define DRAW_ARROW_MACRO    \
    DARK_COLOR; \
    glBegin(GL_POLYGON);    \
    glVertex3fv(arrow_data[0]); \
    glVertex3fv(arrow_data[1]); \
    glVertex3fv(arrow_data[2]); \
    glEnd();    \
    LIGHT_COLOR;        \
    glLineWidth(1); \
    glBegin(GL_LINE_LOOP);      \
    glVertex3fv(arrow_data[0]); \
    glVertex3fv(arrow_data[1]); \
    glVertex3fv(arrow_data[2]); \
    glEnd();


void
SoQtViewer::setFeedbackOrthoProjection(const SbVec2s &size)
{
    // push the gl state to revert it back later....
    glPushAttrib(GL_DEPTH_BUFFER_BIT | GL_LIGHTING_BIT | GL_LINE_BIT);

    // ??? should we worry about restoring this matrix later ?
    glViewport(0, 0, size[0], size[1]);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, size[0], 0, size[1], -1, 1);

    // disable zbuffer and lighting....
    glDisable(GL_DEPTH_TEST);
    glDisable(GL_LIGHTING);
}


void
SoQtViewer::restoreGLStateAfterFeedback()
{
    // restore the gl state that were saved in setFeedbackOrthoProjection()
    glPopAttrib();
}


void
SoQtViewer::drawViewerCrossFeedback(SbVec2s loc)
{
    LIGHT_COLOR;
    glLineWidth(4);
    glBegin(GL_LINES);
    glVertex2s(loc[0]-CROSS, loc[1]);
    glVertex2s(loc[0]+CROSS, loc[1]);
    glVertex2s(loc[0], loc[1]-CROSS);
    glVertex2s(loc[0], loc[1]+CROSS);
    glEnd();

    DARK_COLOR;
    glLineWidth(2);
    glBegin(GL_LINES);
    glVertex2s(loc[0]-CROSS+1, loc[1]);
    glVertex2s(loc[0]+CROSS-1, loc[1]);
    glVertex2s(loc[0], loc[1]-CROSS+1);
    glVertex2s(loc[0], loc[1]+CROSS-1);
    glEnd();
}


void
SoQtViewer::drawViewerRollFeedback(SbVec2s center, SbVec2s loc)
{
    // get angle and distance of mouse from center of rotation
    float ang, dist;
    float vx = loc[0] - center[0];
    float vy = loc[1] - center[1];
    if (vx==0 && vy==0) {
        ang = 0;
        dist = 3; // minimum size (given the circle thickness)
    } else {
        ang = atan2(vy, vx) * 180.0 / M_PI;
        dist = sqrtf(vx*vx + vy*vy);
        if (dist < 3) {
            dist = 3; // minimum size (given the circle thickness)
        }
    }
    float cirAng = -ang + 90; // gluPartialDisk() angle is REALLY backward !!

    static GLUquadricObj *quad = nullptr;
    if (! quad) quad = gluNewQuadric();

    // draw all of the circles (first inner, then outer)
    glTranslatef(center[0], center[1], 0);
    LIGHT_COLOR;
    gluDisk(quad, RADIUS, RADIUS+LINE_THICK, 20, 2);
    gluPartialDisk(quad, dist-2, dist+LINE_THICK-2, 20, 2, cirAng - ANGLE_LEN, 2 * ANGLE_LEN);
    DARK_COLOR;
    gluDisk(quad, RADIUS+1, RADIUS+LINE_THICK-1, 20, 2);
    gluPartialDisk(quad, dist-1, dist+LINE_THICK-3, 20, 2, cirAng - ANGLE_LEN, 2 * ANGLE_LEN);
    glTranslatef(-center[0], -center[1], 0); // undo the translation

    // draw connecting line from center to outer circle
    glLineWidth(LINE_THICK);
    LIGHT_COLOR;
    glBegin(GL_LINES);
    glVertex2s(center[0], center[1]);
    glVertex2s(loc[0], loc[1]);
    glEnd();
    glLineWidth(LINE_THIN);
    DARK_COLOR;
    glBegin(GL_LINES);
    glVertex2s(center[0], center[1]);
    glVertex2s(loc[0], loc[1]);
    glEnd();

    // draw the CCW arrow
    glPushMatrix();
    glTranslatef(center[0], center[1], 0);
    glRotatef(ang+ANGLE_LEN, 0, 0, 1);
    glTranslatef(dist, 0, 0);
    DRAW_ARROW_MACRO
    glPopMatrix();

    // draw the CW arrow
    glPushMatrix();
    glTranslatef(center[0], center[1], 0);
    glRotatef(ang-ANGLE_LEN, 0, 0, 1);
    glTranslatef(dist, 0, 0);
    glScalef(1, -1, 1);
    DRAW_ARROW_MACRO
    glPopMatrix();
}

