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
 * Copyright (C) 1990-95   Silicon Graphics, Inc.
 * Author(s): Alain Dumesny
 * Ported to Qt4 by MeVis (http://www.mevis.de), 2006
 */

#include <Inventor/SbTypeDefs.h>
#include <cstdlib>

#include <Inventor/SoDB.h>
#include <Inventor/SoInput.h>
#include <Inventor/nodes/SoOrthographicCamera.h>
#include <Inventor/nodes/SoPerspectiveCamera.h>
#include <Inventor/sensors/SoFieldSensor.h>
#include <Inventor/fields/SoSFTime.h>
#include <Inventor/nodes/SoScale.h>
#include <Inventor/nodes/SoSeparator.h>
#include <Inventor/nodes/SoSwitch.h>
#include <Inventor/nodes/SoTranslation.h>
#include <Inventor/actions/SoSearchAction.h>
#include <Inventor/Qt/SoQt.h>
#include <Inventor/Qt/SoQtIcons.h>
#include <Inventor/Qt/viewers/SoQtExaminerViewer.h>

#ifdef DEBUG
#include <Inventor/errors/SoDebugError.h>
#include <Inventor/SoDebug.h>
#endif

#include <QAction>
#include <QApplication>
#include <QBoxLayout>
#include <QCheckBox>
#include <QDoubleSpinBox>
#include <QEvent>
#include <QKeyEvent>
#include <QLabel>
#include <QMessageBox>
#include <QMouseEvent>
#include <QSettings>
#include <QTabWidget>
#include <QToolBar>
#include <Inventor/Qt/SoQtThumbWheel.h>

/*
 *  Defines
 */

// size of the rotation buffer, which is used to animate the spinning ball.
#define ROT_BUFF_SIZE 3

// The point of interest geometry description
const char *SoQtExaminerViewer::geometryBuffer = "\
#Inventor V2.0 ascii\n\
\
Separator { \
    PickStyle { style UNPICKABLE } \
    LightModel { model BASE_COLOR } \
    MaterialBinding { value PER_PART } \
    DrawStyle { lineWidth 2 } \
    Coordinate3 { point [0 0 0, 1 0 0, 0 1 0, 0 0 1] } \
    BaseColor { rgb [1 0 0, 0 1 0, 0 0 1] } \
    IndexedLineSet { coordIndex [1, 0, 2, -1, 0, 3] } \
     \
    LightModel { model PHONG } \
    MaterialBinding { value OVERALL } \
    Complexity { value .1 } \
    Separator { \
        Material { \
            diffuseColor    [ 0.5 0 0 ] \
            emissiveColor   [ 0.5 0 0 ] \
        } \
        Translation { translation 1 0 0 } \
        RotationXYZ { axis Z angle -1.570796327 } \
        Cone { bottomRadius .2 height .3 } \
    } \
    Separator { \
        Material { \
            diffuseColor    [ 0 0.5 0 ] \
            emissiveColor   [ 0 0.5 0 ] \
        } \
        Translation { translation 0 1 0 } \
        Cone { bottomRadius .2 height .3 } \
    } \
    Material { \
        diffuseColor    [ 0 0 0.5 ] \
        emissiveColor   [ 0 0 0.5 ] \
    } \
    Translation { translation 0 0 1 } \
    RotationXYZ { axis X angle 1.570796327 } \
    Cone { bottomRadius .2 height .3 } \
} ";


SoQtExaminerViewer::SoQtExaminerViewer (BuildFlag flag, Type type,
    QWidget* parent, Qt::WindowFlags f)
: SoQtFullViewer (flag, type, parent, f)
{
    commonConstructor();
}

SoQtExaminerViewer::SoQtExaminerViewer (QWidget* parent, const char *name,
    SbBool buildInsideParent, SoQtFullViewer::BuildFlag flag,
    SoQtViewer::Type type, SbBool buildNow)
: SoQtFullViewer (flag, type, parent, buildInsideParent ? Qt::SubWindow : Qt::Window)
{
    setObjectName (name);
    commonConstructor();
    if (buildNow) {
        buildWidget();
        updateCursor();
    }
}

void SoQtExaminerViewer::commonConstructor()
{
    nestingFlag = false;
    mouseInside = false;
    // init local vars
    modeCursorCount = INTERACT_MODE_COUNT;
    modeCursors     = new QCursor [modeCursorCount];
    setCursorShape (PICK_MODE,  QCursor());
    setCursorShape (SPIN_MODE,  SoQtIcons::getCursor (SoQtIcons::CURSOR_CURVED_HAND));
    setCursorShape (PAN_MODE,   SoQtIcons::getCursor (SoQtIcons::CURSOR_FLAT_HAND));
    setCursorShape (DOLLY_MODE, SoQtIcons::getCursor (SoQtIcons::CURSOR_POINTING_HAND));
    setCursorShape (SEEK_MODE,  SoQtIcons::getCursor (SoQtIcons::CURSOR_TARGET));
    setCursorShape (SPIN_MODE_ACTIVE,  getCursorShape (SPIN_MODE));
    setCursorShape (PAN_MODE_ACTIVE,   getCursorShape (PAN_MODE));
    setCursorShape (DOLLY_MODE_ACTIVE, getCursorShape (DOLLY_MODE));

    // axis of rotation feedback vars
    feedbackFlag = FALSE;
    feedbackRoot = nullptr;
    feedbackSwitch = nullptr;
    feedbackSize = 20.0;

    feedbackInput = nullptr;
    feedbackSizeWheel = nullptr;
    feedbackSizeWheelValue = 0.0;
    feedbackSizeWidgets = nullptr;

    // init animation variables
    animationEnabled = TRUE;
    animatingFlag = FALSE;
    animationSensor = new
        SoFieldSensor(SoQtExaminerViewer::animationSensorCB, this);
#ifdef DEBUG
    if (SoDebug::GetEnv("IV_DEBUG_SENSORS")) {
        SoDebug::NamePtr("examinerSpinSensor", animationSensor);
    }
#endif

    QString myTitle (tr("Examiner Viewer"));
    setPopupMenuTitle (myTitle);
    setWindowTitle (myTitle);
    setWindowIconText (myTitle);

    setBottomWheelTitle (tr("Roty"));
    setLeftWheelTitle (tr("Rotx"));

    lastMotionTime = QDateTime::currentDateTime().addSecs (-1);

    // this is probably unnecessary here, because a camera probably
    // doesn't exist at this moment - too lazy to think about it...
    QIcon icon = SoQtIcons::getIcon (
        isOrthographic()
        ? SoQtIcons::ICON_ORTHO
        : SoQtIcons::ICON_PERSP);

    perspAction = new QAction (icon, tr("Perspective"), this);
    connect (perspAction, SIGNAL (triggered(bool)), SLOT (toggleCameraTypeSlot()));
    perspAction->setCheckable (true);

    wheelZoomEnabled = true;
    wheelRotationEnabled = true;

    restoreInteractions();
}

SoQtExaminerViewer::~SoQtExaminerViewer()
{
    delete animationSensor;

    if (feedbackRoot) {
        feedbackRoot->unref();
    }
}

void
SoQtExaminerViewer::resetInteractions()
{
    for (int i=0;i<64;i++) {
        modeTable [i] = PICK_MODE;
    }
}

void
SoQtExaminerViewer::restoreInteractions()
{
    resetInteractions();
    setInteraction (int(Qt::LeftButton | Qt::MidButton), 0, DOLLY_MODE_ACTIVE);
    setInteraction (int(Qt::LeftButton) | int(Qt::SHIFT), 0, PAN_MODE_ACTIVE);
    setInteraction (int(Qt::LeftButton) | int(Qt::CTRL), 0, PAN_MODE_ACTIVE);
    setInteraction (int(Qt::LeftButton) | int(Qt::SHIFT | Qt::CTRL), 0, DOLLY_MODE_ACTIVE);
    setInteraction (int(Qt::LeftButton), 0, SPIN_MODE_ACTIVE);
    setInteraction (int(Qt::MidButton) | int(Qt::CTRL), 0, DOLLY_MODE_ACTIVE);
    setInteraction (int(Qt::MidButton), 0, PAN_MODE_ACTIVE);
    setInteraction (int(Qt::SHIFT | Qt::CTRL), 0, DOLLY_MODE);
    setInteraction (int(Qt::SHIFT), 0, PAN_MODE);
    setInteraction (int(Qt::CTRL), 0, PAN_MODE);
    setInteraction (0, 0, SPIN_MODE);
    mode = isViewing() ? modeTable[0] : PICK_MODE;
}


void
SoQtExaminerViewer::setInteraction (int inputState, int ignoreStateMask, ViewerModes mode)
{
    if (ignoreStateMask == 0) {
        modeTable [getModeIndex (inputState)] = mode;
    } else {
        // this is kind of overkill, since values are set more than once, but it's simple:
        for (int i=0;i<64;i++) {
            int state = (inputState & (0xffff ^ ignoreStateMask)) | (i & ignoreStateMask);
            modeTable [getModeIndex (state)] = mode;
        }
    }
}


SoQtExaminerViewer::ViewerModes
SoQtExaminerViewer::getInteraction (int inputState)
{
    return modeTable [getModeIndex (inputState)];
}

int
SoQtExaminerViewer::getModeIndex (int inputState)
{
    return ((inputState & Qt::LeftButton)      ? 1  : 0) |
           ((inputState & Qt::RightButton)     ? 2  : 0) |
           ((inputState & Qt::MidButton)       ? 4  : 0) |
           ((inputState & Qt::ShiftModifier)   ? 8  : 0) |
           ((inputState & Qt::ControlModifier) ? 16 : 0) |
           ((inputState & Qt::AltModifier)     ? 32 : 0);
}

void
SoQtExaminerViewer::setCursorShape (int viewingMode, const QCursor& shape)
{
    if (viewingMode >= PICK_MODE && viewingMode < modeCursorCount && modeCursors != nullptr) {
        // set new cursor shape for a_mode
        modeCursors [viewingMode] = shape;
        if (mouseInside && viewingMode == mode) {
            // update the currently shown cursor
            SoQtFullViewer::setGLCursor (shape);
        }
    }
}

QCursor
SoQtExaminerViewer::getCursorShape (int viewingMode) const
{
    if (viewingMode >= PICK_MODE && viewingMode < modeCursorCount && modeCursors != nullptr) {
        return modeCursors [viewingMode];
    } else {
        // return default cursor
        return QCursor();
    }
}


void
SoQtExaminerViewer::setFeedbackVisibility(SbBool insertFlag)
{
    // check for trivial return
    if (camera == nullptr || feedbackFlag == insertFlag) {
        feedbackFlag = insertFlag;
        return;
    }

    if (feedbackSizeWidgets) {
        feedbackSizeWidgets->setEnabled (insertFlag);
    }

    // find the camera parent to insert/remove the feedback root
    SoSearchAction sa;
    if (insertFlag) {
        sa.setNode(camera);
    } else {
        sa.setNode(feedbackRoot);
        sa.setSearchingAll(TRUE); // find under OFF switches for removal
    }
    sa.apply(sceneRoot);
    SoFullPath *fullPath = (SoFullPath *) sa.getPath();
    if (!fullPath) {
#if DEBUG
        SoDebugError::post("SoQtExaminerViewer::setFeedbackVisibility",
                            insertFlag ? "ERROR: cannot find camera in graph" :
                            "ERROR: cannot find axis feedback in graph");
#endif
        return;
    }
    SoGroup *parent = (SoGroup *) fullPath->getNodeFromTail(1);

    feedbackFlag = insertFlag;

    // make sure the feedback has been built
    if (!feedbackRoot) {
        createFeedbackNodes();
    }

    // inserts/remove the feedback axis group
    if (feedbackFlag) {
        int camIndex;

        // check to make sure that the camera parent is not a switch node
        // (VRML camera viewpoints are kept under a switch node). Otherwise
        // we will insert the feedback after the switch node.
        if (parent->isOfType(SoSwitch::getClassTypeId())) {
            SoNode *switchNode = parent;
            parent = (SoGroup *) fullPath->getNodeFromTail(2);
            camIndex = parent->findChild(switchNode);
        } else {
            camIndex = parent->findChild(camera);
        }

        // return if feedback is already there (this should be an error !)
        if (parent->findChild(feedbackRoot) >= 0) {
            return;
        }

        // insert the feedback right after the camera+headlight (index+2)
        if (camIndex >= 0) {
            if (isHeadlight()) {
                parent->insertChild(feedbackRoot, camIndex+2);
            } else {
                parent->insertChild(feedbackRoot, camIndex+1);
            }
        }

        // make sure the feedback switch is turned to the correct state now
        // that the feedback root has been inserted in the scene
        feedbackSwitch->whichChild.setValue(viewingFlag ? SO_SWITCH_ALL : SO_SWITCH_NONE);
    } else {
        if (parent->findChild(feedbackRoot) >= 0) {
            parent->removeChild(feedbackRoot);
        }
    }
}

void
SoQtExaminerViewer::setFeedbackSize (double newSize)
{
    if (feedbackSize == newSize) { return; }
    if (nestingFlag) { return; }
    nestingFlag = true;

    // assign new value and redraw (since it is not a field in the scene)
    feedbackSize = newSize;
    if (feedbackInput) {
        feedbackInput->setValue (newSize);
    }
    if (isFeedbackVisible() && isViewing()) {
        scheduleRedraw();
    }

    nestingFlag = false;
}

void
SoQtExaminerViewer::viewAll()
{
    // stop spinning
    if ( isAnimating() ) {
        stopAnimating();
    }

    // temporarily remove the feedback geometry
    if (feedbackFlag && isViewing() && feedbackSwitch) {
        feedbackSwitch->whichChild.setValue( SO_SWITCH_NONE );
    }

    // call the base class
    SoQtFullViewer::viewAll();

    // now add the geometry back in
    if (feedbackFlag && isViewing() && feedbackSwitch) {
        feedbackSwitch->whichChild.setValue( SO_SWITCH_ALL );
    }
}

void
SoQtExaminerViewer::resetToHomePosition()
{
    // stop spinning
    if ( isAnimating() ) {
        stopAnimating();
    }

    // call the base class
    SoQtFullViewer::resetToHomePosition();
}


void
SoQtExaminerViewer::setCamera(SoCamera *newCamera, SbBool createdCamera)
{
    if (camera == newCamera) { return; }

    // set the right thumbwheel label and toggle button image based on
    // the camera type
    if (newCamera != nullptr && (camera == nullptr ||
        newCamera->getTypeId() != camera->getTypeId()))
    {
        if (newCamera->isOfType(SoOrthographicCamera::getClassTypeId())) {
            perspAction->setIcon (SoQtIcons::getIcon (SoQtIcons::ICON_ORTHO));
            setRightWheelTitle(tr("Zoom"));
        } else {
            perspAction->setIcon (SoQtIcons::getIcon (SoQtIcons::ICON_PERSP));
            setRightWheelTitle(tr("Dolly"));
        }
    }
    perspAction->setEnabled(newCamera && createdCamera);

    // detach feedback which depends on camera
    if ( feedbackFlag ) {
        setFeedbackVisibility(FALSE);
        feedbackFlag = TRUE;  // can later be turned on
    }

    // call parent class
    SoQtFullViewer::setCamera(newCamera, createdCamera);

    // attach feedback back on
    if ( feedbackFlag ) {
        feedbackFlag = FALSE; // enables routine to be called
        setFeedbackVisibility(TRUE);
    }
}


void
SoQtExaminerViewer::setViewing(SbBool flag)
{
    if (flag == viewingFlag) { return; }

    // call the parent class
    SoQtFullViewer::setViewing(flag);

    updateViewerMode();

    // show/hide the feedback geometry based on the viewing state
    if (feedbackFlag && feedbackSwitch) {
        feedbackSwitch->whichChild.setValue(viewingFlag ? SO_SWITCH_ALL : SO_SWITCH_NONE);
    }
}


void
SoQtExaminerViewer::setCursorEnabled(SbBool flag)
{
    if (flag == cursorEnabledFlag) { return; }

    cursorEnabledFlag = flag;

    if (! isViewing()) { return; }

    updateCursor();
}

void
SoQtExaminerViewer::processEvent (QEvent *anyEvent)
{
    SbVec2s raSize = getGlxSize();
    qreal   raViewScale = getGlxDevicePixelRatio();

    if (anyEvent->type() == QEvent::MouseButtonPress)
    {
        QMouseEvent* me = (QMouseEvent*) anyEvent;
        // remember start position of mouse drag
        locator = SbVec2s(me->x() * raViewScale, raSize[1] - (me->y() * raViewScale));

        if ((me->button() == Qt::LeftButton || me->button() == Qt::MidButton) &&
            mode == SEEK_MODE)
        {
            // handle temporary seek mode
            stopAnimating();
            seekToPoint(locator);
            me->accept();
        } else {
            interactiveCountInc();
            stopAnimating();
        }
        updateViewerMode (me->modifiers(), me->buttons());
        if (mode != PICK_MODE) {
            me->accept();
        }
    } else if (anyEvent->type() == QEvent::KeyPress) {
        QKeyEvent *ke = (QKeyEvent *)anyEvent;
        updateViewerMode (ke->modifiers());
    } else if (anyEvent->type() == QEvent::MouseMove) {
        QMouseEvent* me = (QMouseEvent*) anyEvent;
        SbVec2s pos = SbVec2s(me->x() * raViewScale, raSize[1] - (me->y() * raViewScale));
        if (me->buttons() == 0) {
            // update viewer mode while we are not dragging - this allows us
            // to change the viewing mode depending on the cursor location
            updateViewerMode (me->modifiers(), me->buttons());
        }
        switch (mode) {
            case SPIN_MODE_ACTIVE:
                lastMotionTime = QDateTime::currentDateTime();
                spinCamera(pos);
                break;
            case PAN_MODE_ACTIVE:
                panCamera(pos);
                break;
            case DOLLY_MODE_ACTIVE:
                dollyCamera(pos);
                break;
            default:
                ;
        }
        if (mode != PICK_MODE) {
            me->accept();
        }
    } else if (anyEvent->type() == QEvent::Wheel) {
      QWheelEvent* we = (QWheelEvent*)anyEvent;
      QPoint angle = we->angleDelta();
      if (wheelZoomEnabled && (we->modifiers() == Qt::NoModifier)) {
        if (angle.y()) {
          zoomCamera(-angle.y() / (180 * 8.0)*M_PI);
        }
        we->accept();
      } else if (wheelRotationEnabled && ((we->modifiers() & ~Qt::ControlModifier) == Qt::ShiftModifier)) {
        if (we->modifiers() & Qt::ControlModifier) {
          // swap axes
          angle = QPoint(angle.y(), angle.x());
        }
        if (angle.x()) {
          SbRotation rotx(SbVec3f(0, 1, 0), angle.x() / (180 * 8.0)*M_PI);
          rotateCamera(rotx);
        }
        if (angle.y()) {
          SbRotation roty(SbVec3f(1, 0, 0), angle.y() / (180 * 8.0)*M_PI);
          rotateCamera(roty);
        }
        we->accept();
      }
    } else if (anyEvent->type() == QEvent::Enter) {
        updateViewerMode();
        updateCursor();
        mouseInside = true;
    } else if (anyEvent->type() == QEvent::Leave) {
        SoQtFullViewer::unsetGLCursor();
        mouseInside = false;
    }

    if (!anyEvent->isAccepted()) {
        SoQtFullViewer::processEvent (anyEvent);
    }

    // updates for button and key releases will be done _after_ the mouse event might
    // have been delivered to the inventor scene - otherwise we might swallow some needed
    // events
    if (anyEvent->type() == QEvent::KeyRelease) {
        QKeyEvent *ke = (QKeyEvent *)anyEvent;
        updateViewerMode (ke->modifiers());
    } else if (anyEvent->type() == QEvent::MouseButtonRelease) {
        QMouseEvent* me = (QMouseEvent*) anyEvent;
        if ((me->button() == Qt::LeftButton || me->button() == Qt::MidButton) &&
            mode == SEEK_MODE)
        {
            me->accept();
        } else { //... ButtonRelease
            // check if we need to start spinning
            if (mode == SPIN_MODE_ACTIVE && animationEnabled &&
                // Qt is missing a mechanism to obtain the time when
                // an event was generated (in contrast to processing time)
                lastMotionTime.addMSecs (100) >= QDateTime::currentDateTime())
            {
                animatingFlag = TRUE;
                animationSensor->attach(viewerRealTime);
                interactiveCountInc(); // will be decreased again in stopAnimating
            }
            interactiveCountDec();
            if (mode != PICK_MODE) {
                me->accept();
            }
        }
        updateViewerMode (me->modifiers(), me->buttons());
    }
}


void
SoQtExaminerViewer::updateViewerMode (int modifiers, int buttons)
{
    // obtain modifiers and buttons if they weren't given:
    if (modifiers == -1) {
        modifiers = QApplication::keyboardModifiers();
    }
    if (buttons == -1) {
        buttons = QApplication::mouseButtons();
    }
    if (buttons == 0 && isSeekMode()) {
        // seek mode needs special handling because it's only temporary
        switchMode (SEEK_MODE);
    } else if (!isViewing()) {
        switchMode (PICK_MODE);
    } else {
        if (isAltSwitchingEnabled()) {
            // since 'alt' switches between viewing and picking, we remove
            // 'alt' from the modifiers, since we want to handle it as if
            // it wasn't pressed:
            modifiers = (modifiers | Qt::ALT) ^ Qt::ALT;
        }
        switchMode (getInteraction (modifiers | buttons));
    }
}


void
SoQtExaminerViewer::switchMode(int newMode)
{
    if (mode == newMode) { return; }  //<- This wasn't there before - is this wrong?

    // assing new mode
    int prevMode = mode;
    mode = newMode;

    // update the cursor
    updateCursor();

    // switch to new viewer mode
    switch (newMode) {
        case PICK_MODE:
            if (mouseInside) {
                int buttons = QApplication::mouseButtons();
                if (prevMode != SEEK_MODE) {
                    // in SEEK_MODE the interactive count isn't increased
                    // by a mouse press!
                    if (buttons & Qt::LeftButton) { interactiveCountDec(); }
                    if (buttons & Qt::MidButton)  { interactiveCountDec(); }
                }
                if (buttons & Qt::RightButton) { interactiveCountDec(); }
            }
            stopAnimating();
            break;

        case DOLLY_MODE_ACTIVE:
        case SPIN_MODE_ACTIVE:
        case PAN_MODE_ACTIVE:
            startDrag(locator);
            break;
    }
}


void
SoQtExaminerViewer::updateCursor()
{
    // the viewer cursor are not enabled, then we don't set a new cursor.
    // Instead erase the old viewer cursor.
    if (! cursorEnabledFlag) {
        SoQtFullViewer::unsetGLCursor();
        return;
    } else {
        SoQtFullViewer::setGLCursor (getCursorShape (mode));
    }
}

void SoQtExaminerViewer::setGLCursor (const QCursor& cursor)
{
    setCursorShape (PICK_MODE, cursor);
}

void SoQtExaminerViewer::unsetGLCursor()
{
    setCursorShape (PICK_MODE, QCursor());
}

QCursor SoQtExaminerViewer::glCursor() const
{
    return getCursorShape(PICK_MODE);
}

void
SoQtExaminerViewer::actualRedraw()
{
    // place the feedback at the focal point
    // ??? we really only need to do this when the camera changes
    if (isViewing() && feedbackFlag && camera != nullptr && feedbackRoot) {

        // adjust the position to be at the focal point
        SbMatrix mx;
        mx = camera->orientation.getValue();
        SbVec3f forward(-mx[2][0], -mx[2][1], -mx[2][2]);
        feedbackTransNode->translation = camera->position.getValue() +
            camera->focalDistance.getValue() * forward;

        // adjust the size to be constant on the screen
        float height = 1.0;
        if (isPerspective()) {
            float angle = ((SoPerspectiveCamera *)camera)->heightAngle.getValue();
            height = camera->focalDistance.getValue() * tanf(angle/2);
        } else if (isOrthographic()) {
            height = ((SoOrthographicCamera *)camera)->height.getValue() / 2;
        }

        // ??? getGlxSize[1] == 0 the very first time, so return in that case
        // ??? else the redraws are 3 times slower from now on !! (alain)
        if (getGlxSize()[1] != 0) {
            float size = 2.0 * height * feedbackSize / float (getGlxSize()[1]);
            feedbackScaleNode->scaleFactor.setValue(size, size, size);
        }
    }

    // have the base class draw the scene
    SoQtFullViewer::actualRedraw();
}


void
SoQtExaminerViewer::setAnimationEnabled(SbBool flag)
{
    if (animationEnabled == flag) { return; }

    animationEnabled = flag;
    if ( !animationEnabled && isAnimating()) {
        stopAnimating();
    }
}


void
SoQtExaminerViewer::stopAnimating()
{
    if (animatingFlag) {
        animatingFlag = FALSE;
        animationSensor->detach();
        animationSensor->unschedule();
        interactiveCountDec();
    }
}


void
SoQtExaminerViewer::setSeekMode(SbBool flag)
{
    if ( !isViewing() ) { return; }

    // stop spinning
    if (isAnimating()) {
        stopAnimating();
    }

    // call the base class
    SoQtFullViewer::setSeekMode(flag);

    updateViewerMode();
    updateCursor();
}


QTabWidget*
SoQtExaminerViewer::createPrefSheet()
{
    QTabWidget* tab = SoQtFullViewer::createPrefSheet();
    tab->addTab (createExamPrefSheetGuts(), tr("Seek"));
    return tab;
}


QWidget*
SoQtExaminerViewer::createExamPrefSheetGuts()
{
    QWidget* sheet = new QWidget();
    QBoxLayout* box = new QVBoxLayout();
    sheet->setLayout (box);

    enableSpinToggle = new QCheckBox(tr("Enable spin animation"));
    enableSpinToggle->setCheckState (animationEnabled ? Qt::Checked : Qt::Unchecked);
    connect (enableSpinToggle, SIGNAL (stateChanged(int)),
             this, SLOT (setAnimationEnabledState(int)));
    //-> SoQtExaminerViewer::animPrefSheetToggleCB
    box->addWidget (enableSpinToggle);

    showRotPointToggle = new QCheckBox(tr("Show point of rotation axes"));
    showRotPointToggle->setEnabled (camera != nullptr);
    showRotPointToggle->setCheckState (feedbackFlag ? Qt::Checked : Qt::Unchecked);
    connect (showRotPointToggle, SIGNAL (stateChanged(int)),
             this, SLOT (setFeedbackVisibilityState(int)));
    //-> SoQtExaminerViewer::feedbackPrefSheetToggleCB
    box->addWidget (showRotPointToggle);

    feedbackSizeWidgets = new QWidget();
    QBoxLayout* hbox = new QHBoxLayout();
    feedbackSizeWidgets->setLayout (hbox);

    hbox->addWidget (new QLabel (tr("axes size:")));

    double value = (camera != nullptr) ? camera->nearDistance.getValue() : 0.0;
    SoQtThumbWheel* feedbackWheel = new SoQtThumbWheel (Qt::Horizontal);
    connect (feedbackWheel, SIGNAL (valueChanged(double)),
             this, SLOT (setFeedbackSizeWheelValue(double)));
    connect (feedbackWheel, SIGNAL (dragStart(double)),
             this, SLOT (interactiveCountInc()));
    connect (feedbackWheel, SIGNAL (dragStop(double)),
             this, SLOT (interactiveCountDec()));
    //-> SoQtFullViewer::feedbackSizeWheelCB
    hbox->addWidget (feedbackWheel);

    feedbackInput = new QDoubleSpinBox();
    feedbackInput->setDecimals (0);
    feedbackInput->setRange (0.0, 1000.0);
    feedbackInput->setValue (value);
    connect (feedbackInput, SIGNAL (valueChanged(double)),
             this, SLOT (setFeedbackSize(double)));
    //-> SoQtFullViewer::feedbackSizeFieldCB
    hbox->addWidget (feedbackInput);

    hbox->addWidget (new QLabel (tr("pixels")));
    feedbackSizeWidgets->setEnabled (feedbackFlag && camera);

    box->addWidget (feedbackSizeWidgets);

    return sheet;
}


void
SoQtExaminerViewer::bottomWheelStart()
{
    SoQtFullViewer::bottomWheelStart();
    stopAnimating();
}


void
SoQtExaminerViewer::leftWheelStart()
{
    SoQtFullViewer::bottomWheelStart();
    stopAnimating();
}


void
SoQtExaminerViewer::bottomWheelMotion(double newVal)
{
    // get rotation and apply to camera
    SbVec3f axis(0, 1, 0);
    SbRotation rot(axis, bottomWheelValue - newVal);
    rotateCamera(rot);

    bottomWheelValue = newVal;
}


void
SoQtExaminerViewer::leftWheelMotion(double newVal)
{
    // get rotation and apply to camera
    SbVec3f axis(1, 0, 0);
    SbRotation rot(axis, newVal - leftWheelValue);
    rotateCamera(rot);

    leftWheelValue = newVal;
}


void
SoQtExaminerViewer::rightWheelMotion(double newVal)
{
    zoomCamera (float (newVal - rightWheelValue));

    rightWheelValue = newVal;
}


void
SoQtExaminerViewer::loadSettings (const QSettings& settings)
{
    setAnimationEnabled (
        settings.value ("spinAnimation", animatingFlag).toBool());

    setFeedbackVisibility (
        settings.value ("pointOfRotationAxes", feedbackFlag).toBool());

    feedbackSize =
        settings.value ("axesSize", feedbackSize).toInt();
}

void
SoQtExaminerViewer::saveSettings (QSettings& settings)
{
    settings.setValue ("spinAnimation", animatingFlag);

    settings.setValue ("pointOfRotationAxes", feedbackFlag);

    settings.setValue ("axesSize", feedbackSize);
}


void
SoQtExaminerViewer::createViewerButtons(QToolBar* parent)
{
    // create the default buttons
    SoQtFullViewer::createViewerButtons(parent);
    parent->addAction (perspAction);
}

void
SoQtExaminerViewer::createFeedbackNodes()
{
    // make sure we havn't built this yet...
    if (feedbackRoot) { return; }

    feedbackRoot        = new SoSeparator(1);
    feedbackSwitch      = new SoSwitch(3);
    feedbackTransNode   = new SoTranslation;
    feedbackScaleNode   = new SoScale;
    feedbackRoot->ref();
    feedbackRoot->addChild( feedbackSwitch );
    feedbackSwitch->addChild( feedbackTransNode );
    feedbackSwitch->addChild( feedbackScaleNode );
    SoInput in;
    in.setBuffer((void *)geometryBuffer, (size_t) strlen(geometryBuffer));
    SoNode *node;
    SbBool ok = SoDB::read(&in, node);
    if (ok && node != nullptr) {
        feedbackSwitch->addChild(node);
#ifdef DEBUG
    } else {
        SoDebugError::post("SoQtExaminerViewer::createFeedbackNodes",
                            "couldn't read feedback axis geometry");
#endif
    }
}

////////////////////////////////////////////////////////////////////////
// static callbacks stubs
////////////////////////////////////////////////////////////////////////

void
SoQtExaminerViewer::animationSensorCB (void *v, SoSensor *)
{
  if (!static_cast<SoQtExaminerViewer*>(v)->doSpinAnimation()) {
      static_cast<SoQtExaminerViewer*>(v)->stopAnimating();
  }
}

void
SoQtExaminerViewer::setFeedbackSizeWheelValue (double value)
{
    // grow/shrink the feedback based on the wheel rotation
    setFeedbackSize (double (feedbackSize) *
                     pow (12.0, (value - feedbackSizeWheelValue) / 360.0));
    feedbackSizeWheelValue = value;

}

// called when the viewer becomes visible/hidden - when hidden, make
// sure to temporary stop any ongoing animation (and restart it as soon
// as we become visible).
//
void
SoQtExaminerViewer::hideEvent (QHideEvent* event)
{
    SoQtFullViewer::hideEvent (event);

    // only do this if we are/were spinning....
    if (! animatingFlag) { return; }

    // if hidden, detach the field sensor, but don't change the
    // animatingFlag var to let us know we need to turn it back on
    // when we become visible....
    animationSensor->detach();
    animationSensor->unschedule();
}

void
SoQtExaminerViewer::showEvent (QShowEvent* event)
{
    SoQtFullViewer::showEvent (event);

    // only do this if we are/were spinning....
    if (! animatingFlag) { return; }

    // we now are visible again so attach the field sensor
    animationSensor->attach (viewerRealTime);
}

bool
SoQtExaminerViewer::isCurrentlyPicking()
{
    return !isViewing() || (mode == PICK_MODE);
}
