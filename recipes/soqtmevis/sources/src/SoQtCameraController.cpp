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
#include <Inventor/SbViewportRegion.h>
#include <Inventor/SoDB.h>
#include <Inventor/SoPath.h>
#include <Inventor/SoPickedPoint.h>
#include <Inventor/actions/SoGetBoundingBoxAction.h>
#include <Inventor/actions/SoRayPickAction.h>
#include <Inventor/actions/SoSearchAction.h>
#include <Inventor/errors/SoDebugError.h>
#include <Inventor/nodes/SoDirectionalLight.h>
#include <Inventor/nodes/SoSeparator.h>
#include <Inventor/nodes/SoOrthographicCamera.h>
#include <Inventor/nodes/SoPerspectiveCamera.h>
#include <Inventor/nodes/SoResetTransform.h>
#include <Inventor/nodes/SoRotation.h>
#include <Inventor/nodes/SoSeparator.h>
#include <Inventor/nodes/SoSwitch.h>
#include <Inventor/sensors/SoFieldSensor.h>
#include <Inventor/sensors/SoNodeSensor.h>
#include <Inventor/projectors/SbSphereSheetProjector.h>
#include <Inventor/fields/SoSFTime.h>
#include <Inventor/Qt/SoQtCameraController.h>
#include <Qt>

#include "SoQtHeadlight.h"

// size of the rotation buffer, which is used to animate the spinning ball.
#define ROT_BUFF_SIZE 3

// keep a pointer to global time, since we are going to access it a lot.
SoSFTime *SoQtCameraController::realTime = nullptr;

SbName SoQtCameraController::headlightName("SoQtCameraController_headlight");

SoSFTime *SoQtCameraController::getRealTime()
{
    if (! realTime) {
        realTime = (SoSFTime *) SoDB::getGlobalField("realTime");
    }
    return realTime;
}

SoQtCameraController::SoQtCameraController(Type t)
: sceneSize(0,0)
{
    // init local vars
    type = t;
    sceneGraph = nullptr;
    sceneRoot = nullptr;
    cameraIndex = 0;
    camera = nullptr;
    cameraType = SoPerspectiveCamera::getClassTypeId();
    createdCamera = FALSE;

    // init auto clipping stuff
    autoClipFlag = TRUE;
    minimumNearPlane = 0.001;
    autoClipBboxAction = new SoGetBoundingBoxAction(SbVec2s(1,1));  // ??? no valid size yet

    // init seek animation variables
    seekDistance = 50.0;
    seekDistAsPercentage = TRUE;
    seekModeFlag = FALSE;
    detailSeekFlag = TRUE;
    seekAnimTime = 2.0;
    seekAnimationSensor = new SoFieldSensor(SoQtCameraController::seekAnimationSensorCB, this);

    // headlightNode - we either insert a new headlight node or use the already existing node
    // (in case another view uses the same scene/camera) and the last viewer has to remove
    // the headlight again, therefore the SoQtHeadlight has a reference count.
    headlightNode   = nullptr;
    headlightFlag   = TRUE;
    isPrimaryHeadlightOwner = FALSE;
    headlightParent = nullptr;
    headlightParentSensor = new SoNodeSensor();
    headlightParentSensor->setDeleteCallback(SoQtCameraController::headlightParentDeletedCB, this);
    prototypeHeadlightNode = new SoQtHeadlight();
    prototypeHeadlightNode->ref();

    rotBuffer = new SbRotation[ROT_BUFF_SIZE];

    // init the projector class
    SbViewVolume vv;
    vv.ortho(-1, 1, -1, 1, -10, 10);
    sphereSheet = new SbSphereSheetProjector;
    sphereSheet->setViewVolume( vv );
    sphereSheet->setSphere( SbSphere( SbVec3f(0, 0, 0), .7) );

    zoomSensitivity = 1.0f;

    boundingBoxSeparator = new SoSeparator();
    boundingBoxSeparator->ref();
}


SoQtCameraController::~SoQtCameraController()
{
    // delete everything
    delete sphereSheet;
    delete [] rotBuffer;
    delete seekAnimationSensor;
    delete headlightParentSensor;
    delete autoClipBboxAction;
    prototypeHeadlightNode->unref();
    boundingBoxSeparator->unref();
}


void
SoQtCameraController::setSceneRoot(SoGroup* root, int camIndex)
{
    sceneRoot = root;
    cameraIndex = camIndex;
}

void
SoQtCameraController::setSceneGraph(SoNode *newScene)
{
    // detach everything that depends on the old sceneGraph
    if ( sceneGraph != nullptr ) {
        setCamera(nullptr, FALSE);
        sceneRoot->removeChild(sceneGraph);
        boundingBoxSeparator->removeAllChildren();
    }

    sceneGraph = newScene;

    // now assign the new sceneGraph, find or create the new camera
    // and attach things back.
    if ( sceneGraph != nullptr ) {
        sceneRoot->addChild(sceneGraph);
        // we need a SoSeparator to optimize bounding box calculation
        boundingBoxSeparator->addChild(sceneGraph);

        // search for first camera in the scene
        SoSearchAction sa;
        sa.setType(SoCamera::getClassTypeId());
        sa.setSearchingAll(FALSE); // don't look under off switches
        sa.apply(sceneGraph);

        SoCamera *newCamera = nullptr;
        if (sa.getPath()) {
            newCamera = (SoCamera *)((SoFullPath *)sa.getPath())->getTail();
        }

        // if no camera found create one of the right kind...
        if ( newCamera == nullptr ) {

            newCamera = (SoCamera*) cameraType.createInstance();
            if (newCamera == nullptr) {
#ifdef DEBUG
                SoDebugError::post("SoQtCameraController::setSceneGraph",
                    "unknown camera type!");
#endif
                // ??? what should we do here ?
                cameraType = SoPerspectiveCamera::getClassTypeId();
                newCamera = new SoPerspectiveCamera;
            }

            if (type == SoQtCameraController::BROWSER) {
                // add camera after drawstyle stuff
                sceneRoot->insertChild(newCamera, cameraIndex);
            } else {
                // check to make sure scene starts with at least a group node
                if ( sceneGraph->isOfType(SoGroup::getClassTypeId()) ) {
                    ((SoGroup *)sceneGraph)->insertChild(newCamera, 0);
                } else {
                    // make scene start with a group node
                    SoGroup *group = new SoGroup;
                    group->addChild(newCamera);
                    group->addChild(sceneGraph);
                    sceneRoot->addChild(group);
                    sceneRoot->removeChild(sceneGraph);
                    sceneGraph = group;
                }
            }

            newCamera->viewAll(sceneGraph, SbViewportRegion(sceneSize));
            setCamera(newCamera, TRUE);
        } else {
            setCamera(newCamera, FALSE);
        }
    }
}

SoNode *
SoQtCameraController::getSceneGraph()
{
    return sceneGraph;
}


void
SoQtCameraController::setCamera(SoCamera *newCamera, SbBool cameraCreated)
{
    // check for trivual return
    if (camera == newCamera) {
        return;
    }

    //
    // detach everything that depended on the old camera
    //
    if ( camera != nullptr ) {

        if (headlightParent != nullptr) {
            setHeadlightInternal(FALSE);
        }

        // remove the camera if we created one outside of the
        // scene graph.
        if (this->createdCamera && type == SoQtCameraController::BROWSER) {
            if (sceneRoot->findChild(camera) >= 0) {
                sceneRoot->removeChild(camera);
            }
            this->createdCamera = FALSE;
        }

        camera->unref();
    }

    camera = newCamera;

    //
    // attach everything that depends on the new camera
    //
    if ( camera != nullptr) {
        camera->ref();
        this->createdCamera = cameraCreated;

        if (headlightFlag) {
            setHeadlightInternal(TRUE);
        }

        saveHomePosition();
    }
}


void
SoQtCameraController::setCameraType(SoType type)
{
    if (type.isDerivedFrom(SoPerspectiveCamera::getClassTypeId()) ||
        type.isDerivedFrom(SoOrthographicCamera::getClassTypeId()))
    {
        cameraType = type;
#ifdef DEBUG
    } else {
        SoDebugError::post("SoQtCameraController::setCameraType",
                        "unknown camera type!");
#endif
    }
}


void
SoQtCameraController::viewAll()
{
    if ( camera != nullptr ) {
        camera->viewAll(sceneGraph,SbViewportRegion(sceneSize));
    }
}


void
SoQtCameraController::viewAll(const SbRotation &dir)
{
    if ( camera != nullptr ) {
        camera->orientation = dir;
        camera->viewAll(sceneGraph,SbViewportRegion(sceneSize));
    }
}


bool
SoQtCameraController::isPerspective() const
{
  return (camera != nullptr) && camera->isOfType(SoPerspectiveCamera::getClassTypeId());
}

bool
SoQtCameraController::isOrthographic() const
{
  return (camera != nullptr) && camera->isOfType(SoOrthographicCamera::getClassTypeId());
}



void
SoQtCameraController::setAutoClipping(SbBool flag)
{
    autoClipFlag = flag;
}


void
SoQtCameraController::setHeadlight(SbBool on)
{
    if (on != headlightFlag) {
        setHeadlightInternal(on);
        headlightFlag = on;
    }
}


void
SoQtCameraController::setHeadlightInternal(bool insertFlag)
{
    if (headlightParent) {
        if (headlightNode) {
            // remove previous headlight
            if (isPrimaryHeadlightOwner) {
                // in case headlight attributes have been changed in the meantime:
                prototypeHeadlightNode->copyFieldValues(headlightNode, true);
            }
            headlightNode->decreaseStakeHolderCount();
            if (headlightNode->stakeHolderCount() == 0) {
                if (headlightParent->findChild(headlightNode) >= 0) {
                    headlightParent->removeChild(headlightNode);
                }
            }
            headlightNode = nullptr;
            isPrimaryHeadlightOwner = false;
        }
        headlightParentSensor->detach();
        headlightParent = nullptr;
    }

    //
    // find the camera parent to insert the headlight
    //
    if (insertFlag && (camera != nullptr)) {
        SoSearchAction sa;
        sa.setNode(camera);
        sa.apply(sceneRoot);
        SoFullPath *fullPath = (SoFullPath *) sa.getPath();
        if (!fullPath) {
    #if DEBUG
            SoDebugError::post("SoQtCameraController::setHeadlight",
                               "ERROR: cannot find camera in graph");
    #endif
            // headlight was not inserted:
            headlightParent = nullptr;
            return;
        }
        headlightParent = (SoGroup *) fullPath->getNodeFromTail(1);

        //
        // inserts the headlight group node
        //
        int camIndex;

        // check to make sure that the camera parent is not a switch node
        // (VRML camera viewpoints are kept under a switch node). Otherwise
        // we will insert the headlight right after the switch node.
        if (headlightParent->isOfType(SoSwitch::getClassTypeId())) {
            SoNode *switchNode = headlightParent;
            headlightParent = (SoGroup *) fullPath->getNodeFromTail(2);
            camIndex = headlightParent->findChild(switchNode);
        } else {
            camIndex = headlightParent->findChild(camera);
        }

        // so we get notified if the headlightParent goes away:
        headlightParentSensor->attach(headlightParent);

        if (camIndex >= 0) {
            SoNode* possibleHeadlight =
                (headlightParent->getNumChildren() > camIndex + 1) ? headlightParent->getChild(camIndex + 1) : nullptr;
            if ((possibleHeadlight != nullptr) && (possibleHeadlight->getName() == headlightName) &&
                (possibleHeadlight->isOfType(SoQtHeadlight::getClassTypeId())))
            {
                headlightNode = (SoQtHeadlight*)possibleHeadlight;
            }
            else {
                // only insert if there wasn't a headlight yet
                headlightNode = new SoQtHeadlight();
                // copy changed headlight attributes from prototype to actual headlight:
                headlightNode->copyFieldValues(prototypeHeadlightNode, true);
                headlightNode->setName(headlightName);
                headlightParent->insertChild(headlightNode, camIndex + 1);
                isPrimaryHeadlightOwner = true;
            }
            headlightNode->increaseStakeHolderCount();
        }
    }
}

void
SoQtCameraController::headlightParentDeletedCB(void *p, SoSensor *)
{
    // headlightParent has been deleted
    SoQtCameraController* thisp = (SoQtCameraController*)p;
    thisp->headlightParent = nullptr;
    if (thisp->isPrimaryHeadlightOwner && thisp->headlightNode) {
        // copy headlight attributes that may have been changed in the meantime
        // (it is ok to use the headlight because the callback is called
        // _before_ the node is about to be deleted)
        thisp->prototypeHeadlightNode->copyFieldValues(thisp->headlightNode, true);
    }
    thisp->headlightNode = nullptr;
    thisp->isPrimaryHeadlightOwner = false;
}

void
SoQtCameraController::setSeekMode(SbBool flag)
{
    // check if seek is being turned off while seek animation is happening
    if ( !flag && seekAnimationSensor->getAttachedField() ) {
        seekAnimationSensor->detach();
        seekAnimationSensor->unschedule();
        animationFinished();
    }

    seekModeFlag = flag;
}


SoDirectionalLight*
SoQtCameraController::getHeadlight() {
    // only the primary (first) headlight owner may change the actual headlight,
    // secondary owners will only provide their own prototype headlight
    // (whose attributes will be used if they get to create their own headlight)
    return isPrimaryHeadlightOwner ? headlightNode : prototypeHeadlightNode;
}


void
SoQtCameraController::updateHeadlight()
{
    // unnecessary
}

void
SoQtCameraController::saveHomePosition()
{
    if (camera == nullptr) {
        return;
    }

    origPosition = camera->position.getValue();
    origOrientation = camera->orientation.getValue();
    origNearDistance = camera->nearDistance.getValue();
    origFarDistance = camera->farDistance.getValue();
    origFocalDistance = camera->focalDistance.getValue();

    // save camera height (changed by zooming)
    if (camera->isOfType(SoPerspectiveCamera::getClassTypeId())) {
        origHeight = ((SoPerspectiveCamera *)camera)->heightAngle.getValue();
    } else if (camera->isOfType(SoOrthographicCamera::getClassTypeId())) {
        origHeight = ((SoOrthographicCamera *)camera)->height.getValue();
    }
}


void
SoQtCameraController::resetToHomePosition()
{
    if (camera == nullptr) {
        return;
    }

    camera->position = origPosition;
    camera->orientation = origOrientation;
    camera->nearDistance = origNearDistance;
    camera->farDistance = origFarDistance;
    camera->focalDistance = origFocalDistance;

    // restore camera height (changed by zooming)
    if (camera->isOfType(SoPerspectiveCamera::getClassTypeId())) {
        ((SoPerspectiveCamera *)camera)->heightAngle.setValue(origHeight);
    } else if (camera->isOfType(SoOrthographicCamera::getClassTypeId())) {
        ((SoOrthographicCamera *)camera)->height.setValue(origHeight);
    }
}

SbBool
SoQtCameraController::seekToPoint(const SbVec2s &mouseLocation)
{
    if (camera == nullptr) {
        setSeekMode(FALSE);
        return FALSE;
    }

    // do the picking
    // Use assignment notation to disambiguate from expression (edison)
    SoRayPickAction pick = SoRayPickAction(SbViewportRegion(sceneSize));
    pick.setPoint(mouseLocation);
    pick.setRadius(1.0);
    pick.setPickAll(FALSE); // pick only the closest object
    pick.apply(sceneRoot);

    // makes sure something got picked
    SoPickedPoint *pp = pick.getPickedPoint();
    if ( pp == nullptr ) {
        setSeekMode(FALSE);
        return FALSE;
    }

    // Get picked point and normal if detailtSeek
    if (detailSeekFlag) {

        seekPoint = pp->getPoint();
        seekNormal = pp->getNormal();

        // check to make sure normal points torward the camera, else
        // flip the normal around
        if ( seekNormal.dot(camera->position.getValue() - seekPoint) < 0 ) {
            seekNormal.negate();
        }
    }
    // else get object bounding box as the seek point and the camera
    // orientation as the normal.
    else {
        // get center of object's bounding box
        // Use assignment notation to disambiguate from expression (edison)
        SoGetBoundingBoxAction bba = SoGetBoundingBoxAction(SbViewportRegion(sceneSize));
        bba.apply(pp->getPath());
        SbBox3f bbox = bba.getBoundingBox();
        seekPoint = bbox.getCenter();

        // keep the camera oriented the same way
        SbMatrix mx;
        mx = camera->orientation.getValue();
        seekNormal.setValue(mx[2][0], mx[2][1], mx[2][2]);
    }

    // now check if animation sensor needs to be scheduled
    computeSeekVariables = TRUE;
    if (seekAnimTime == 0) {
        // jump to new location, no animation needed
        interpolateSeekAnimation(1.0);
    } else {
        // schedule sensor and call viewer start callbacks
        if ( ! seekAnimationSensor->getAttachedField() ) {
            seekAnimationSensor->attach(getRealTime());
            seekAnimationSensor->schedule();
            animationStarted();
        }

        seekStartTime = getRealTime()->getValue();
    }

    return TRUE;    // successfull
}


void
SoQtCameraController::computeSeekFinalOrientation()
{
    SbMatrix mx;
    SbVec3f viewVector;

    // find the camera final orientation
    if ( isDetailSeek() ) {

        // get the camera new orientation
        mx = camera->orientation.getValue();
        viewVector.setValue(-mx[2][0], -mx[2][1], -mx[2][2]);
        SbRotation changeOrient;
        changeOrient.setValue(viewVector, seekPoint - camera->position.getValue());
        newCamOrientation = camera->orientation.getValue() * changeOrient;
    } else {
        newCamOrientation = camera->orientation.getValue();
    }
}


void
SoQtCameraController::interpolateSeekAnimation(float t)
{
    if (camera == nullptr) {
        return;
    }

    // check if camera new and old position/orientation have already
    // been computed.
    if (computeSeekVariables) {
        SbMatrix mx;
        SbVec3f viewVector;

        // save camera starting point
        oldCamPosition = camera->position.getValue();
        oldCamOrientation = camera->orientation.getValue();

        // compute the distance the camera will be from the seek point
        // and update the camera focalDistance.
        float dist;
        if ( seekDistAsPercentage ) {
            SbVec3f seekVec(seekPoint - camera->position.getValue());
            dist = seekVec.length() * (seekDistance / 100.0);
        } else {
            dist = seekDistance;
        }
        camera->focalDistance = dist;

        // let subclasses have a chance to redefine what the
        // camera final orientation should be.
        computeSeekFinalOrientation();

        // find the camera final position based on orientation and distance
        mx = newCamOrientation;
        viewVector.setValue(-mx[2][0], -mx[2][1], -mx[2][2]);
        newCamPosition = seekPoint - dist * viewVector;

        computeSeekVariables = FALSE;
    }

    // Now position the camera according to the animation time

    // use and ease-in ease-out approach
    float cos_t = 0.5 - 0.5 * cosf(t * M_PI);

    // get camera new rotation
    camera->orientation = SbRotation::slerp(oldCamOrientation, newCamOrientation, cos_t);

    // get camera new position
    camera->position = oldCamPosition + (newCamPosition - oldCamPosition) * cos_t;
}


void
SoQtCameraController::adjustCameraClippingPlanes()
{
    if (camera == nullptr) {
        return;
    }

    // get the scene bounding box
    autoClipBboxAction->setViewportRegion(SbViewportRegion(sceneSize));
    autoClipBboxAction->apply(boundingBoxSeparator);

    SbXfBox3f xfbbox = autoClipBboxAction->getXfBoundingBox();
    if (!xfbbox.isEmpty()) {
        // get camera transformation and apply to xfbbox
        // to align the bounding box to camera space.
        // This will enable us to simply use the z values of the
        // transformed bbox for near and far plane values.
        SbMatrix mx;
        mx.setTranslate(- camera->position.getValue());
        xfbbox.transform(mx);
        mx = camera->orientation.getValue().inverse();
        xfbbox.transform(mx);

        // get screen align bbox and figure the near and far plane values
        SbBox3f bbox = xfbbox.project();
        // take negative value and opposite to what one might think
        // because the camera points down the -Z axis
        float farDist = - bbox.getMin()[2];
        float nearDist = - bbox.getMax()[2];

        // check for minimum near plane value (Value will be negative
        // when the camera is inside the bounding box).
        // Note: there needs to be a minimum near value for perspective
        // camera because of zbuffer resolution problem (plus the values
        // has to be positive). There is no such restriction for
        // an Orthographic camera (you can see behind you).
        if (! camera->isOfType(SoOrthographicCamera::getClassTypeId()))
        {
          // scene is behind the camera so don't change the planes
          if (farDist < 0) {
            return;
          }

          if (nearDist < (minimumNearPlane * farDist)) {
            nearDist = minimumNearPlane * farDist;
          }
        }

        // give the near and far distances a little bit of slack in case
        // the object lies against the bounding box, otherwise the object
        // will be poping in and out of view.
        // (example: a cube is the same as it's bbox)
        nearDist *= 0.999;
        farDist *= 1.001;

        // finally assign camera plane values
        if (camera->nearDistance.getValue() != nearDist)
            camera->nearDistance = nearDist;
        if (camera->farDistance.getValue() != farDist)
            camera->farDistance = farDist;
    }
}

void
SoQtCameraController::changeCameraValues(SoCamera *newCamera)
{
    if (camera == nullptr) {
        return;
    }

    // only paste cameras of the same type
    if (camera->getTypeId() != newCamera->getTypeId()) {
        return;
    }

    // give our camera the values of the new camera
    camera->position        = newCamera->position;
    camera->orientation     = newCamera->orientation;
    camera->nearDistance    = newCamera->nearDistance;
    camera->farDistance     = newCamera->farDistance;
    camera->focalDistance   = newCamera->focalDistance;

    // get the height or heightAngle
    if (camera->isOfType(SoPerspectiveCamera::getClassTypeId())) {
        ((SoPerspectiveCamera *)camera)->heightAngle =
                ((SoPerspectiveCamera *)newCamera)->heightAngle;
    } else {
        ((SoOrthographicCamera *)camera)->height =
                ((SoOrthographicCamera *)newCamera)->height;
    }
}

void
SoQtCameraController::toggleCameraType()
{
    if (camera == nullptr) {
        return;
    }

    // create the camera of the opposite kind and compute the wanted height
    // or heightAngle of the new camera.
    SoCamera *newCam;
    if (camera->isOfType(SoPerspectiveCamera::getClassTypeId())) {
        float angle = ((SoPerspectiveCamera *)camera)->heightAngle.getValue();
        float height = camera->focalDistance.getValue() * tanf(angle/2);
        newCam = new SoOrthographicCamera;
        ((SoOrthographicCamera *)newCam)->height = 2 * height;
    } else if (camera->isOfType(SoOrthographicCamera::getClassTypeId())) {
        float height = ((SoOrthographicCamera *)camera)->height.getValue() / 2;
        float angle = atanf(height / camera->focalDistance.getValue());
        newCam = new SoPerspectiveCamera;
        ((SoPerspectiveCamera *)newCam)->heightAngle = 2 * angle;
    } else {
#ifdef DEBUG
        SoDebugError::post("SoQtCameraController::toggleCameraType", "unknown camera type!");
#endif
        return;
    }

    newCam->ref();

    // copy common stuff from the old to the new camera
    newCam->viewportMapping = camera->viewportMapping.getValue();
    newCam->position = camera->position.getValue();
    newCam->orientation = camera->orientation.getValue();
    newCam->aspectRatio = camera->aspectRatio.getValue();
    newCam->focalDistance = camera->focalDistance.getValue();

    // search for the old camera and replace it by the new camera
    SoSearchAction sa;
    sa.setNode(camera);
    sa.apply(sceneRoot);
    SoFullPath *fullCamPath = (SoFullPath *) sa.getPath();
    if (fullCamPath) {
        SoGroup *parent = (SoGroup *)fullCamPath->getNode(fullCamPath->getLength() - 2);
        parent->insertChild(newCam, parent->findChild(camera));
        SoCamera *oldCam = camera;
        setCamera(newCam, TRUE);

        // remove the old camera if it is still there (setCamera() might
        // have removed it) and set the created flag to true (for next time)
        if (parent->findChild(oldCam) >= 0) {
            parent->removeChild(oldCam);
        }
#ifdef DEBUG
    } else {
        SoDebugError::post("SoQtCameraController::toggleCameraType", "camera not found!");
#endif
    }
    newCam->unref();
}


void
SoQtCameraController::arrowKeyPressed (int key)
{
    if (camera == nullptr) {
        return;
    }

    // get the camera near plane height value
    float dist = 0.0;
    if (camera->isOfType(SoPerspectiveCamera::getClassTypeId())) {
        float angle = ((SoPerspectiveCamera *)camera)->heightAngle.getValue();
        float length = camera->nearDistance.getValue();
        dist = length * tanf(angle);
    } else if (camera->isOfType(SoOrthographicCamera::getClassTypeId())) {
        dist = ((SoOrthographicCamera *)camera)->height.getValue();
    }
    dist /= 2.0;

    // get camera right/left/up/down direction
    SbMatrix mx;
    mx = camera->orientation.getValue();
    SbVec3f dir;
    switch(key) {
        case Qt::Key_Up:
            dir.setValue(mx[1][0], mx[1][1], mx[1][2]);
            break;
        case Qt::Key_Down:
            dir.setValue(-mx[1][0], -mx[1][1], -mx[1][2]);
            break;
        case Qt::Key_Right:
            dir.setValue(mx[0][0], mx[0][1], mx[0][2]);
            dist *= camera->aspectRatio.getValue();
            break;
        case Qt::Key_Left:
            dir.setValue(-mx[0][0], -mx[0][1], -mx[0][2]);
            dist *= camera->aspectRatio.getValue();
            break;
    }

    // finally reposition the camera
    camera->position = camera->position.getValue() + dist * dir;
}

//
////////////////////////////////////////////////////////////////////////
// static callbacks stubs
////////////////////////////////////////////////////////////////////////
//


void
SoQtCameraController::seekAnimationSensorCB(void *p, SoSensor *)
{
    SoQtCameraController *v = (SoQtCameraController *)p;

    // get the time difference
    SbTime time = getRealTime()->getValue();
    float sec = float((time - v->seekStartTime).getValue());
    if (sec == 0.0) {
        sec = 1.0/72.0; // at least one frame (needed for first call)
    }
    float t = (sec / v->seekAnimTime);

    // check to make sure the values are correctly clipped
    if (t > 1.0) {
        t = 1.0;
    } else if ((1.0 - t) < 0.0001) {
        t = 1.0; // this will be the last one...
    }

    // call subclasses to interpolate the animation
    v->interpolateSeekAnimation(t);

    // stops seek if this was the last interval
    if (t == 1.0) {
        v->setSeekMode(FALSE);
    }
}

void
SoQtCameraController::startDrag(const SbVec2s &pos)
{
    startPos = pos;

    SbVec2f relLocator =
        SbVec2f(startPos[0]/float(sceneSize[0]), startPos[1]/float(sceneSize[1]));

    // set the sphere sheet starting point
    sphereSheet->project(relLocator);

    // reset the animation queue
    firstIndex = 0;
    lastIndex = -1;

    if (camera == nullptr) { return; }

    // Figure out the focal plane
    SbMatrix mx;
    mx = camera->orientation.getValue();
    SbVec3f forward(-mx[2][0], -mx[2][1], -mx[2][2]);
    SbVec3f fp = camera->position.getValue() +
        forward * camera->focalDistance.getValue();
    focalplane = SbPlane(forward, fp);

    // map mouse starting position onto the panning plane
    SbViewVolume    cameraVolume;
    SbLine          line;
    cameraVolume = camera->getViewVolume(sceneSize[0]/float(sceneSize[1]));
    cameraVolume.projectPointToLine(relLocator, line);
    focalplane.intersect(line, locator3D);
}


void
SoQtCameraController::rotateCamera(const SbRotation &rot)
{
    if (camera == nullptr) { return; }

    // get center of rotation
    SbRotation camRot = camera->orientation.getValue();
    float radius = camera->focalDistance.getValue();
    SbMatrix mx;
    mx = camRot;
    SbVec3f forward( -mx[2][0], -mx[2][1], -mx[2][2]);
    SbVec3f center = camera->position.getValue()
        + radius * forward;

    // apply new rotation to the camera
    camRot = rot * camRot;
    camera->orientation = camRot;

    // reposition camera to look at pt of interest
    mx = camRot;
    forward.setValue( -mx[2][0], -mx[2][1], -mx[2][2]);
    camera->position = center - radius * forward;
}



void
SoQtCameraController::zoomCamera (float amount)
{
    // NOTE: perhaps make minFocalDist and minCameraHeight configurable later
    static float minFocalDist    = 0.01f;
    static float minCameraHeight = 0.01f;

    if (camera == nullptr) { return; }

    if (camera->isOfType(SoOrthographicCamera::getClassTypeId())) {
        // change the ortho camera height
        SoOrthographicCamera *cam = (SoOrthographicCamera *) camera;
        float height = cam->height.getValue() * powf(2.0, amount);
        height = (height < minCameraHeight) ? minCameraHeight : height;
        cam->height = height;
    } else {
        // shorter/grow the focal distance given the mouse move
        float focalDistance = camera->focalDistance.getValue();;
        float newFocalDist = focalDistance * powf(2.0, amount);
        newFocalDist = (newFocalDist < minFocalDist) ? minFocalDist : newFocalDist;

        // finally reposition the camera
        SbMatrix mx;
        mx = camera->orientation.getValue();
        SbVec3f forward(-mx[2][0], -mx[2][1], -mx[2][2]);
        camera->position = camera->position.getValue() +
                           (focalDistance - newFocalDist) * forward;
        camera->focalDistance = newFocalDist;
    }
}



void
SoQtCameraController::panCamera(const SbVec2s &newPos)
{
    if (camera == nullptr) { return; }

    const SbVec2f newLocator =
      SbVec2f(newPos[0]/float(sceneSize[0]), newPos[1]/float(sceneSize[1]));
    // map new mouse location into the camera focal plane
    SbViewVolume    cameraVolume;
    SbLine          line;
    SbVec3f         newLocator3D;
    cameraVolume = camera->getViewVolume(sceneSize[0]/float(sceneSize[1]));
    cameraVolume.projectPointToLine(newLocator, line);
    focalplane.intersect(line, newLocator3D);

    // move the camera by the delta 3D position amount
    camera->position = camera->position.getValue() +
        (locator3D - newLocator3D);

    // You would think we would have to set locator3D to
    // newLocator3D here.  But we don't, because moving the camera
    // essentially makes locator3D equal to newLocator3D in the
    // transformed space, and we will project the next newLocator3D in
    // this transformed space.
}


void
SoQtCameraController::spinCamera(const SbVec2s &newPos)
{

    const SbVec2f newLocator =
      SbVec2f(newPos[0]/float(sceneSize[0]), newPos[1]/float(sceneSize[1]));
    // find rotation and rotate camera
    SbRotation rot;
    sphereSheet->projectAndGetRotation(newLocator, rot);
    rot.invert();

    rotateCamera(rot);

    // save rotation for animation
    lastIndex = ((lastIndex+1) % ROT_BUFF_SIZE);
    rotBuffer[lastIndex] = rot;
    computeAverage = TRUE;

    // check if queue is full
    if (((lastIndex+1) % ROT_BUFF_SIZE) == firstIndex) {
        firstIndex = ((firstIndex+1) % ROT_BUFF_SIZE);
    }
}


void
SoQtCameraController::dollyCamera(const SbVec2s &newPos)
{
    // moving the mouse up/down will move the camera futher/closer.
    // moving the mouse left/right will not move the camera at all
    zoomCamera ((newPos[1] - startPos[1]) * zoomSensitivity / 40.0);

    startPos = newPos;
}


bool
SoQtCameraController::doSpinAnimation()
{
    static float maxSpinAngle = float(5.0/180.0*3.1415927); // max. 5 degrees per step

    // check if average rotation needs to be computed
    if (computeAverage) {
        float averageAngle, angle;
        SbVec3f averageAxis, axis;

        // get number of samples
        int num = (((lastIndex - firstIndex) + 1 +
            ROT_BUFF_SIZE) % ROT_BUFF_SIZE);

        // check for not enough samples
        if (num < 2) {
            return false;
        }

        // get average axis of rotation
        // ??? right now only take one sample
        rotBuffer[firstIndex].getValue(averageAxis, angle);

        // get average angle of rotation
        averageAngle = 0;
        for (int i=0; i<num; i++) {
            int n = (firstIndex + i) % ROT_BUFF_SIZE;
            rotBuffer[n].getValue(axis, angle);
            averageAngle += angle;
        }
        averageAngle /= float(num);

        // make rotation slower:
        averageAngle *= 0.5;
        // restrict rotation speed:
        if (averageAngle > maxSpinAngle) { averageAngle = maxSpinAngle; }

        averageRotation.setValue(averageAxis, averageAngle);
        computeAverage = FALSE;
    }

    // rotate camera by average rotation
    rotateCamera(averageRotation);
    return true;
}

