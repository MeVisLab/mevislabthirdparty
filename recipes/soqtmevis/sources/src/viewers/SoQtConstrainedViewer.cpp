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
 * Author(s): Alain Dumesny
 * Ported to Qt4 by MeVis (http://www.mevis.de), 2006
 */


#include <Inventor/SoPickedPoint.h>
#include <Inventor/actions/SoGetBoundingBoxAction.h>
#include <Inventor/actions/SoRayPickAction.h>
#include <Inventor/nodes/SoCamera.h>
#include <Inventor/nodes/SoSeparator.h>
#include <Inventor/Qt/viewers/SoQtConstrainedViewer.h>


#define MIN_ANGLE       (5*M_PI/180.)   // minimum angle between look at
                                        // direction and up direction (in rad)


SoQtConstrainedViewer::SoQtConstrainedViewer(
    SoQtFullViewer::BuildFlag flag, SoQtViewer::Type type,
    QWidget* parent, Qt::WindowFlags f)
: SoQtFullViewer(flag, type, parent, f)
{
    // init local vars
    upDirection.setValue(0, 1, 0);
    sceneHeight = 0.0;

    // assign decoration titles
    setBottomWheelTitle(tr("Rotate"));
    setLeftWheelTitle(tr("Tilt"));
    setRightWheelTitle(tr("Dolly"));
}


SoQtConstrainedViewer::~SoQtConstrainedViewer()
{
}


void
SoQtConstrainedViewer::recomputeSceneSize()
{
    if (! sceneGraph || ! sceneRoot) {
        sceneSize = sceneHeight = 0.0;
        return;
    }

    // Use assignment notation to disambiguate from expression (edison)
    SoGetBoundingBoxAction bboxAct = SoGetBoundingBoxAction(SbViewportRegion(getGlxSize()));
    bboxAct.apply(sceneRoot);
    SbBox3f bbox = bboxAct.getBoundingBox();

    if (bbox.isEmpty()) {
        sceneSize = sceneHeight = 0.0;
        return;
    }

    // ??? this assumes Y is up right now (for sceneHeight)
    float x, z;
    bbox.getSize(x, sceneHeight, z);
    sceneSize = (x > z) ? x : z;

    if (sceneSize <= 0.0) {
        sceneSize = 0.0;
    }
    if (sceneHeight <= 0.0) {
        sceneHeight = 0.0;
    }
}


void
SoQtConstrainedViewer::setUpDirection(const SbVec3f &newUpDirection)
{
    SbRotation rot(upDirection, newUpDirection);
    upDirection = newUpDirection;

    // rotate the camera and check for constrain
    if (camera != nullptr) {
        camera->orientation = rot * camera->orientation.getValue();
        checkForCameraUpConstrain();
    }
}


void
SoQtConstrainedViewer::setCamera(SoCamera *newCamera, SbBool createdCamera)
{
    // call base class routine
    SoQtFullViewer::setCamera(newCamera, createdCamera);

    // now check for constrains
    if (camera != nullptr)
        checkForCameraUpConstrain();
}


void
SoQtConstrainedViewer::saveHomePosition()
{
    // call the parent class
    SoQtFullViewer::saveHomePosition();

    origUpDirection = upDirection;
}


void
SoQtConstrainedViewer::resetToHomePosition()
{
    // call the parent class
    SoQtFullViewer::resetToHomePosition();

    upDirection = origUpDirection;
}


void
SoQtConstrainedViewer::bottomWheelMotion(double newVal)
{
    if (camera == nullptr) { return; }

    // get rotation and apply to camera
    SbRotation rot(upDirection, bottomWheelValue - newVal);
    camera->orientation = camera->orientation.getValue() * rot;

    bottomWheelValue = newVal;
}


void
SoQtConstrainedViewer::leftWheelMotion(double newVal)
{
    tiltCamera(leftWheelValue - newVal);

    leftWheelValue = newVal;
}


void
SoQtConstrainedViewer::tiltCamera(float deltaAngle)
{
    if (camera == nullptr) { return; }

    // get camera forward direction
    SbMatrix mx;
    mx = camera->orientation.getValue();
    SbVec3f forward(-mx[2][0], -mx[2][1], -mx[2][2]);

    // get the angle between the foward and up direction
    // as well as the axis of rotation
    SbRotation rot(forward, upDirection);
    SbVec3f axis;
    float angle;
    rot.getValue(axis, angle);
    // make angle in [-PI,PI] range
    if (angle > M_PI) {
        angle -= 2*M_PI;
    } else if (angle < -M_PI) {
        angle += 2*M_PI;
    }
    // make rotation toward up direction positive angle
    if (angle < 0.0) {
        angle = -angle;
        axis = -axis;
    }

    // check if we are already looking almost along the up direction
    if ( (angle <= MIN_ANGLE && deltaAngle > 0) ||
         (angle >= (M_PI - MIN_ANGLE) && deltaAngle < 0) )
    { return; }

    // clamp the angle change as to not get too close along the up direction
    if (deltaAngle > 0 && deltaAngle > (angle - MIN_ANGLE)) {
        deltaAngle = angle - MIN_ANGLE;
    } else if (deltaAngle < 0 && deltaAngle < (angle + MIN_ANGLE - M_PI)) {
        deltaAngle = angle + MIN_ANGLE - M_PI;
}

    // finally rotate the camera by the given angle
    rot.setValue(axis, deltaAngle);
    camera->orientation = camera->orientation.getValue() * rot;
}


void
SoQtConstrainedViewer::computeSeekFinalOrientation()
{
    SbMatrix mx;
    SbVec3f viewVector;

    // find the camera final orientation
    if ( isDetailSeek() ) {

        // get the camera unconstrained new orientation
        mx = camera->orientation.getValue();
        viewVector.setValue(-mx[2][0], -mx[2][1], -mx[2][2]);
        SbRotation changeOrient;
        changeOrient.setValue(viewVector, seekPoint - camera->position.getValue());
        newCamOrientation = camera->orientation.getValue() * changeOrient;

        // check for constrains
        camera->orientation = newCamOrientation;
        checkForCameraUpConstrain();
        newCamOrientation = camera->orientation.getValue();
    } else {
        newCamOrientation = camera->orientation.getValue();
    }
}


void
SoQtConstrainedViewer::checkForCameraUpConstrain()
{
    if (camera == nullptr) { return; }

    // adjust the camera if necessary so that the new right vector
    // lies in a plane parallel to our old right vector
    SbMatrix mx;
    mx = camera->orientation.getValue();
    SbVec3f newForward(-mx[2][0], -mx[2][1], -mx[2][2]);
    SbVec3f newRight(mx[0][0], mx[0][1], mx[0][2]);

    // idealRight is the right vector computed from the pasted forward
    // and the existing world up vector
    SbVec3f idealRight = newForward.cross(upDirection);
    idealRight.normalize();

    // if idealRight is 0, then the newForward is looking in the
    // same direction as the world up. In this case, we have to choose
    // a right vector, so we choose the newRight. Otherwise, we have
    // to rotate our orientation from the newRight to the idealRight.
    if (idealRight != SbVec3f(0.0, 0.0, 0.0)) {
        // rotate to idealRight!
        SbRotation rot(newRight, idealRight);
        camera->orientation.setValue(
            camera->orientation.getValue() * rot);
    }
}


void
SoQtConstrainedViewer::changeCameraValues(SoCamera *newCamera)
{
    if (camera == nullptr) { return; }

    // only paste cameras of the same type
    if (camera->getTypeId() != newCamera->getTypeId()) {
        return;
    }

    // let the base class copy camera values
    SoQtFullViewer::changeCameraValues(newCamera);

    // now check for constrains
    checkForCameraUpConstrain();
}


void
SoQtConstrainedViewer::findUpDirection(const SbVec2s &mouseLocation)
{
    if (camera == nullptr) { return; }

    // do the picking
    SbVec2s size = getGlxSize();
    SoRayPickAction pick( size );
    pick.setPoint(mouseLocation);
    pick.setRadius(1.0);
    pick.setPickAll(FALSE);
    pick.apply(sceneRoot);

    // makes sure something got picked, then
    // get the picked point.
    SoPickedPoint *pp = pick.getPickedPoint();
    if (pp == nullptr) { return; }
    SbVec3f normal = pp->getNormal();

    // check whether the normal is pointing toward the camera, else
    // flip the normal around.
    SbVec3f point = pp->getPoint();;
    if ( normal.dot(camera->position.getValue() - point) < 0 ) {
        normal.negate();
    }

//printf("%f %f %f\n", normal[0], normal[1], normal[2]);

    setUpDirection(normal);
}
