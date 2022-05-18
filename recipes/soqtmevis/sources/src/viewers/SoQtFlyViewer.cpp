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

#include <Inventor/SbTypeDefs.h>

#include <Inventor/SoDB.h>
#include <Inventor/SoPickedPoint.h>
#include <Inventor/sensors/SoFieldSensor.h>
#include <Inventor/fields/SoSFTime.h>
#include <Inventor/nodes/SoCamera.h>
#include <Inventor/nodes/SoOrthographicCamera.h>
#include <Inventor/nodes/SoPerspectiveCamera.h>
#include <Inventor/Qt/SoQtIcons.h>
#include <Inventor/Qt/viewers/SoQtFlyViewer.h>

#include <QTabWidget>
#include <QBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QKeyEvent>
#include <QMouseEvent>

/*
 * Defines
 */
enum ViewerModes {
    STILL_MODE,
    FLY_MODE,
    TILT_MODE,
    SEEK_MODE,
    SET_UP_MODE
};

// color used in feedback
#define DARK_COLOR      glColor3ub(90, 90, 90)
#define TEXT_COLOR      glColor3ub(255, 255, 90)
#define MAX_SPEED_COL   glColor3ub(0, 200, 200)
#define CUR_SPEED_COL   glColor3ub(255, 0, 0)

#define CROSS       12  // cross feedback size
#define CIRCLE_RAD  15  // center circle radius
#define TEXT_DX     0.05
#define TEXT_DY     0.03
#define DECOR_DX    0.15

#define MIN_SPEED   0.02
#define MAX_INC     1.5
#define TURN_SPEED  .8*M_PI    // radians/second

#define WHEEL_DOLLY_FACTOR  0.5


SoQtFlyViewer::SoQtFlyViewer (
    SoQtFullViewer::BuildFlag flag, SoQtViewer::Type type,
    QWidget* parent, Qt::WindowFlags f)
: SoQtConstrainedViewer (flag, type, parent, f)
{
    constructorCommon();
}

SoQtFlyViewer::SoQtFlyViewer(
        QWidget* parent, const char *name, SbBool buildInsideParent,
        SoQtFullViewer::BuildFlag flag, SoQtViewer::Type type,
        SbBool buildNow)
: SoQtConstrainedViewer (flag, type, parent, buildInsideParent ? Qt::SubWindow : Qt::Window)

{
    setObjectName (name);
    // In this case, render area is what the app wants, so buildNow = TRUE
    constructorCommon();
    if (buildNow) {
        buildWidget();
    }
}


void
SoQtFlyViewer::constructorCommon()
{
    // init vars
    mode = STILL_MODE;
    viewerCursor = SoQtIcons::getCursor (SoQtIcons::CURSOR_VIEWING);
    seekCursor = SoQtIcons::getCursor (SoQtIcons::CURSOR_TARGET);
    upCursor = SoQtIcons::getCursor (SoQtIcons::CURSOR_NORMAL_VEC);
    setGLCursor (viewerCursor);
    speedLimitFactor = 0.5;

    // init animation variables
    animationSensor = new SoFieldSensor(SoQtFlyViewer::animationSensorCB, this);

    // assign decoration names
    QString myTitle (tr("Fly Viewer"));
    setPopupMenuTitle (myTitle);
    setWindowTitle (myTitle);
    setWindowIconText (myTitle);
    setPrefSheetTitle (tr("Fly Viewer Preference Sheet"));

}


SoQtFlyViewer::~SoQtFlyViewer()
{
}


void
SoQtFlyViewer::setViewing (SbBool flag)
{
    if (flag == viewingFlag) { return; }

    // call the base class
    SoQtConstrainedViewer::setViewing(flag);

    // set the right cursor
        if (isViewing()) {
            setGLCursor (viewerCursor);
        } else {
            unsetGLCursor();
        }

    // erase viewer feedback
    if (mode != STILL_MODE) {
        switchMode(STILL_MODE);
    } else {
        scheduleRedraw();
    }
}


void
SoQtFlyViewer::setCursorEnabled(SbBool flag)
{
    if (flag == cursorEnabledFlag) { return; }

    cursorEnabledFlag = flag;

    if (! isViewing()) { return; }

    // now set the right cursor on the window
    if (flag) {

        switch(mode) {
            case STILL_MODE:
            case FLY_MODE:
            case TILT_MODE:
                setGLCursor (viewerCursor);
                break;
            case SEEK_MODE:
                setGLCursor (seekCursor);
                break;
            case SET_UP_MODE:
                setGLCursor (upCursor);
                break;
        }
    } else {
        unsetGLCursor();
    }
}


void
SoQtFlyViewer::setCamera(SoCamera *newCamera, SbBool createdCamera)
{
    if (camera == newCamera) { return; }

    // call parent class
    SoQtConstrainedViewer::setCamera(newCamera, createdCamera);

    // now make sure the camera is not orthographic, else switch to
    // perspective.
    if (camera != nullptr &&
        camera->isOfType(SoOrthographicCamera::getClassTypeId()))
    {
        toggleCameraType();
    }
}


#ifdef DEBUG
void
SoQtFlyViewer::setCameraType(SoType type)
{
    if (! type.isDerivedFrom(SoPerspectiveCamera::getClassTypeId())) {
        SoDebugError::post("SoQtFlyViewer::setCameraType()",
                        "ignored - must be perspective camera");
    }
}
#else
void SoQtFlyViewer::setCameraType(SoType) {}
#endif


void
SoQtFlyViewer::setSeekMode(SbBool flag)
{
    if (!isViewing()) { return; }

    // call the base class
    SoQtConstrainedViewer::setSeekMode(flag);

    // set the new viewer mode
    if (isSeekMode()) {
        switchMode(SEEK_MODE);
    } else {
        switchMode(STILL_MODE);
    }
}


void
SoQtFlyViewer::resetToHomePosition()
{
    // call the base class
    SoQtConstrainedViewer::resetToHomePosition();

    // set the new viewer mode
    switchMode(STILL_MODE);
}


QTabWidget*
SoQtFlyViewer::createPrefSheet()
{
    QTabWidget* tab = SoQtFullViewer::createPrefSheet();
    tab->addTab (createFlyPrefSheetGuts(), tr("Flying speed"));
    return tab;
}



QWidget*
SoQtFlyViewer::createFlyPrefSheetGuts()
{
    QWidget* sheet = new QWidget();
    QBoxLayout* box = new QHBoxLayout();
    sheet->setLayout (box);

    box->addWidget (new QLabel (tr("Flying speed:")));

    QPushButton* incSpeedButton = new QPushButton (tr("increase"));
    connect (incSpeedButton, SIGNAL (clicked(bool)), this, SLOT (increaseFlySpeed()));
    //-> SoQtFlyViewer::incPrefSheetButtonCB
    box->addWidget (incSpeedButton);

    QPushButton* decSpeedButton = new QPushButton (tr("decrease"));
    connect (decSpeedButton, SIGNAL (clicked(bool)), this, SLOT (decreaseFlySpeed()));
    //-> SoQtFlyViewer::decPrefSheetButtonCB
    box->addWidget (decSpeedButton);

    return sheet;
}


void
SoQtFlyViewer::increaseFlySpeed()
{
    speedLimitFactor *= 2.0;
    speedLimit *= 2.0;
    maxStraightSpeed *= 2.0;
}

void
SoQtFlyViewer::decreaseFlySpeed()
{
    speedLimitFactor /= 2.0;
    speedLimit /= 2.0;
    maxStraightSpeed /= 2.0;
}


void
SoQtFlyViewer::processEvent(QEvent *anyEvent)
{
    // check for leave and enter  notify, in which case the viewer
    // temporaly stops flying and resume flying if it was flying.
    if (isViewing() && mode == FLY_MODE) {
        if (anyEvent->type() == QEvent::Leave) {
            animationSensor->detach();
            animationSensor->unschedule();
            interactiveCountDec();
        }
        else if (anyEvent->type() == QEvent::Enter) {
            animationSensor->attach(viewerRealTime);
            animationSensor->schedule();
            prevAnimTime = viewerRealTime->getValue();
            interactiveCountInc();
        }
    }

    SbVec2s raSize = getGlxSize();
    qreal   raViewScale = getGlxDevicePixelRatio();
    QMouseEvent     *me;
    QKeyEvent       *ke;

    switch(anyEvent->type()) {
    case QEvent::MouseButtonPress:
        {
            me = (QMouseEvent*) anyEvent;
            if (me->button() != Qt::LeftButton && me->button() != Qt::MidButton) {
                break;
            }
            locator[0] = me->x() * raViewScale;
            locator[1] = raSize[1] - (me->y() * raViewScale);
            // check if both buttons are down
            bool both = (me->button() == Qt::LeftButton && me->buttons() & Qt::MidButton) ||
                        (me->button() == Qt::MidButton  && me->buttons() & Qt::LeftButton);
            switch(mode) {
                case STILL_MODE:
                    // check if both buttons are down
                    if (both) { break; }
                    switchMode(FLY_MODE);
                    changeMaxStraightSpeed (me->button() == Qt::LeftButton);
                    speed = maxSpeed;
                    break;
                case FLY_MODE:
                    // check if both buttons are down
                    if (both) {
                        switchMode(STILL_MODE);
                    } else {
                        changeMaxStraightSpeed (me->button() == Qt::LeftButton);
                    }
                    break;
                case SEEK_MODE:
                    if (me->button() == Qt::LeftButton)
                        seekToPoint(locator);
                    break;
                case SET_UP_MODE:
                    if (me->button() == Qt::LeftButton) {
                        findUpDirection(locator);
                        switchMode(STILL_MODE);
                    }
                    break;
            }
        }
        break;

    case QEvent::MouseMove:
        me = (QMouseEvent*) anyEvent;
        locator[0] = me->x() * raViewScale;
        locator[1] = raSize[1] - (me->y() * raViewScale);
        switch(mode) {
            case FLY_MODE:
                // find new max speed based on curvature
                calculateMaxSpeed();
                break;
            case TILT_MODE:
                // reset the camera orientation
                camera->orientation = camStartOrientation;

                // rotate right/left
                if (locator[0] != startPos[0]) {
                    float angle = (startPos[0] - locator[0]) / float(raSize[0]);
                    SbRotation rot(upDirection, angle * 2 * M_PI);
                    camera->orientation = camera->orientation.getValue() * rot;
                }

                // tilt up/down
                if (locator[1] != startPos[1]) {
                    float angle = (locator[1] - startPos[1]) / float(raSize[1]);
                    tiltCamera(angle * 2 * M_PI);
                }
                break;
        }
        break;

    case QEvent::KeyPress:
        ke = (QKeyEvent *) anyEvent;
        switch (ke->key()) {
            case Qt::Key_U:
                if (isSeekMode()) {
                    setSeekMode(FALSE);
                }
                switchMode( (mode == SET_UP_MODE) ? STILL_MODE : SET_UP_MODE );
                break;
            case Qt::Key_Control:
                if (mode == STILL_MODE || mode == FLY_MODE) {
                    interactiveCountInc();
                    switchMode(TILT_MODE);
                }
                break;
        }
        break;

    case QEvent::KeyRelease:
        ke = (QKeyEvent *) anyEvent;
        switch (ke->key()) {
            case Qt::Key_Control:
                if (mode == TILT_MODE) {
                    switchMode(STILL_MODE);
                    interactiveCountDec();
                }
                break;
        }
        break;
    default: // to avoid warning
        ;
    }
}


void
SoQtFlyViewer::switchMode(int newMode)
{
    if (mode == newMode) { return; }

    // assing new mode
    SbBool redrawNeeded = TRUE;
    int prevMode = mode;
    mode = newMode;

    // check the old viewer mode
    switch(prevMode) {
        case FLY_MODE:
            animationSensor->detach();
            animationSensor->unschedule();
            interactiveCountDec();
            break;
    }

    // switch to new viewer mode
    switch(newMode) {
        case STILL_MODE:
            setGLCursor (viewerCursor);
            break;
        case FLY_MODE:
            animationSensor->attach(viewerRealTime);
            animationSensor->schedule();
            prevAnimTime = viewerRealTime->getValue();
            interactiveCountInc();
            speed = maxSpeed = maxStraightSpeed = 0;
            speedLimit = sceneSize * speedLimitFactor;
            redrawNeeded = FALSE; // wait for sensor to fire
            setGLCursor (viewerCursor);
            break;
        case TILT_MODE:
            // save mouse and camera starting values
            startPos = locator;
            camStartOrientation = camera->orientation.getValue();
            setGLCursor (viewerCursor);
            break;
        case SEEK_MODE:
            setGLCursor (seekCursor);
            break;
        case SET_UP_MODE:
            setGLCursor (upCursor);
            break;
    }

    if (redrawNeeded) {
        scheduleRedraw();
    }
}


void
SoQtFlyViewer::actualRedraw()
{
    // have the base class draw the scene
    SoQtConstrainedViewer::actualRedraw();

    // now draw the viewer feedback
    if (isViewing() && camera != nullptr) {

        setFeedbackOrthoProjection(getGlxSize());

        drawViewerFeedback();

        // now restore state
        restoreGLStateAfterFeedback();
    }
}


void
SoQtFlyViewer::drawViewerFeedback()
{
    // draw the current action text
    SbVec2s raSize = getGlxSize();
    short tx = short(raSize[0] * TEXT_DX);
    short ty = short(raSize[1] * TEXT_DY);
    glRasterPos2s(tx, ty);
    TEXT_COLOR;
// ???alain
#if 0
    char str[10];
    switch(mode) {
        case STILL_MODE: charstr(tr("Still"));   break;
        case TILT_MODE:  charstr(tr("Tilting")); break;
        case SEEK_MODE:  charstr(tr("Seeking")); break;
        case SET_UP_MODE: charstr(tr("Set Up Direction")); break;
        case FLY_MODE:
            charstr(tr("Flying  %1").arg(speed));
            break;
    }
#endif

    // draw the current speed feedback stuff
    short x0 = short(raSize[0] * DECOR_DX);
    short x1 = raSize[0] / 2;
    short x2 = raSize[0] - x0;
    short y = ty + 30;
    glLineWidth(1);
    DARK_COLOR;
    glBegin(GL_LINES);
    glVertex2s(x0, y); glVertex2s(x2, y);
    glVertex2s(x0, y-5); glVertex2s(x0, y+5);
    glVertex2s(x1, y-5); glVertex2s(x1, y+5);
    glVertex2s(x2, y-5); glVertex2s(x2, y+5);
    glEnd();
#if 0
    cmov2s(x0-15, y-5); charstr("-");
    cmov2s(x2+10, y-5); charstr("+");
#endif
    if (mode == FLY_MODE) {
        // draw the maximum speed bar
        short l = short((x2-x1) * maxStraightSpeed / speedLimit);
        MAX_SPEED_COL;
        glLineWidth(5);
        glBegin(GL_LINES);
        glVertex2s(x1, y); glVertex2s(x1+l, y);
        glEnd();

        // draw the current speed bar
        l = short((x2-x1) * speed / speedLimit);
        CUR_SPEED_COL;
        glLineWidth(3);
        glBegin(GL_LINES);
        glVertex2s(x1, y); glVertex2s(x1+l, y);
        glEnd();
    }

    // draw mode specific stuff
    glLineWidth(1);
    if (mode == TILT_MODE) {
        // draw cross at starting point
        DARK_COLOR;
        glBegin(GL_LINES);
        glVertex2s(startPos[0] - CROSS, startPos[1]);
        glVertex2s(startPos[0] + CROSS, startPos[1]);
        glVertex2s(startPos[0], startPos[1] - CROSS);
        glVertex2s(startPos[0], startPos[1] + CROSS);
        glEnd();
    }
    else {
#if 0
        static GLUquadricObj *quad = NULL;
        if (! quad) { quad = gluNewQuadric(); }

        // draw small circle at screen center
        DARK_COLOR;
        circi(raSize[0]/2, raSize[1]/2, CIRCLE_RAD);
#endif
    }

    // finally draw the small directional axis
#if 0
#define DRAW_AXIS(color, x, y, z) \
    cpack(color); \
    axis.setValue(x, y, z); \
    bgnline(); \
    v3f(center.getValue()); \
    v3f(axis.getValue()); \
    endline();

    SbVec3f axis, center(0, 0, 0);
    SbVec2s pos(raSize[0]/2, raSize[1]/3);
    short min = (raSize[0] < raSize[1]) ? raSize[0] : raSize[1];
    short size = short(min * 0.08);
    SbMatrix mx;
    mx = camera->orientation.getValue().inverse();
    SbVec3f bboxDir(sceneBbox.getCenter() - camera->position.getValue());
    bboxDir.normalize();
    SbVec3f viewVector(-mx[2][0], -mx[2][1], -mx[2][2]);

    ortho(-1, 1, -1, 1, -1, 1);
    viewport(pos[0]-size, pos[0]+size, pos[1]-size, pos[1]+size);
    zbuffer(TRUE);
    zclear();
    pushmatrix();
    multmatrix((Matrix) (float *) mx);
    DRAW_AXIS(0x6666ff, 1, 0, 0)
    DRAW_AXIS(0x66ff66, 0, 1, 0)
    DRAW_AXIS(0xff6666, 0, 0, 1)
    (viewVector.dot(bboxDir) < 0) ? cpack(0x66ffff) : cpack(0xff66ff);
    bgnline(); v3f(center.getValue()); v3f(bboxDir.getValue()); endline();
    popmatrix();
    zbuffer(FALSE);
#undef DRAW_AXIS
#endif
}


void
SoQtFlyViewer::doCameraAnimation()
{
    if (camera == nullptr) { return; }

    // get time interval since last call
    SbTime time = viewerRealTime->getValue();
    float sec = float((time - prevAnimTime).getValue());
    prevAnimTime = time;

    // make sure to have at least a delta time for the first call.
    if (sec == 0.0) {
        sec = 1.0/72.0;
    }

    // turn the camera left/right using the distance^2 which gives a nice
    // gradual speedup.
    SbVec2s raSize = getGlxSize();
    float dist = (locator[0] - raSize[0]/2) / float(raSize[0]);
    float angle = TURN_SPEED * (dist * dist) * sec;
    if (angle != 0.0) {
        if (dist < 0) {
            angle = -angle;
        }
        SbRotation rot(upDirection, -angle);
        camera->orientation = camera->orientation.getValue() * rot;
    }

    // tilt camera up/down using the distance^2 which gives a nice
    // gradual speedup.
    dist = (locator[1] - raSize[1]/2) / float(raSize[1]);
    angle = TURN_SPEED * (dist * dist) * sec;
    if (dist < 0) {
        angle = -angle;
    }
    if (angle != 0.0) {
        tiltCamera(angle);
    }

    // move the camera forward
    float dollyDist = speed * sec;
    if (dollyDist > 0.0) {
        // get camera forward direction
        SbMatrix mx;
        mx = camera->orientation.getValue();
        SbVec3f forward(-mx[2][0], -mx[2][1], -mx[2][2]);

        // now move camera foward by distance
        camera->position = camera->position.getValue() + forward * dollyDist;
    }

    // increase the current speed if we havn't reach max speed yet
    if ((speed > 0 && speed < maxSpeed) || (speed < 0 && speed > maxSpeed)) {
        speed *= powf(3.0, sec);

        // clip the value to the maxSpeed
        if ((speed > 0 && speed > maxSpeed) || (speed < 0 && speed < maxSpeed)) {
            speed = maxSpeed;
        }
    }
}


void
SoQtFlyViewer::rightWheelMotion(double newVal)
{
    float dist = (newVal - rightWheelValue) * sceneSize * viewerSpeed
            * WHEEL_DOLLY_FACTOR;

    // get camera forward direction
    SbMatrix mx;
    mx = camera->orientation.getValue();
    SbVec3f forward(-mx[2][0], -mx[2][1], -mx[2][2]);

    // now move camera foward by distance
    camera->position = camera->position.getValue() + forward * dist;
    camera->focalDistance = camera->focalDistance.getValue() - dist;

    rightWheelValue = newVal;
}


void
SoQtFlyViewer::changeMaxStraightSpeed(SbBool increase)
{
    // check if we are just starting
    if (maxStraightSpeed == 0) {
        maxStraightSpeed = increase ? MIN_SPEED * speedLimit : - MIN_SPEED * speedLimit;
    } else {

        // find the new maxStraightSpeed
        if ((maxStraightSpeed > 0 && increase) ||
            (maxStraightSpeed < 0 && !increase))
        {
            maxStraightSpeed *= MAX_INC;
        } else {
            maxStraightSpeed /= MAX_INC;
        }

        // clip to speedLimit boundaries
        if (maxStraightSpeed > speedLimit) {
            maxStraightSpeed = speedLimit;
        } else if (maxStraightSpeed < -speedLimit) {
            maxStraightSpeed = -speedLimit;
        }

        // check if we are less than the minimum speed, in which
        // case we just stop flying
        float min = MIN_SPEED * speedLimit;
        if (maxStraightSpeed > -min && maxStraightSpeed < min) {
            switchMode(STILL_MODE);
            return;
        }
    }

    // given the new maxStraightSpeed, calculate the maxSpeed
    calculateMaxSpeed();
}


void
SoQtFlyViewer::calculateMaxSpeed()
{
    // get the x and y normalized distances from screen center
    SbVec2s raSize = getGlxSize();
    float dx = 2.0 * (locator[0] - raSize[0]/2) / float(raSize[0]);
    if (dx < 0.0) dx = -dx;
    if (dx > 1.0) dx = 1.0;
    float dy = 2.0 * (locator[1] - raSize[1]/2) / float(raSize[1]);
    if (dy < 0.0) dy = -dy;
    if (dy > 1.0) dy = 1.0;

    // assign new maxSpeed and clip the current speed if needed
    maxSpeed = (dx > dy) ? (1.0 - dx) * maxStraightSpeed :
                            (1.0 - dy) * maxStraightSpeed;
    if ((speed > 0 && speed > maxSpeed) || (speed < 0 && speed < maxSpeed)) {
        speed = maxSpeed;
    }
}


//
////////////////////////////////////////////////////////////////////////
// static callbacks stubs
////////////////////////////////////////////////////////////////////////
//

void
SoQtFlyViewer::animationSensorCB(void *v, SoSensor *)
{ ((SoQtFlyViewer *) v)->doCameraAnimation(); }

