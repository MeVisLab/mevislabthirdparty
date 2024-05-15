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


#ifndef  _SO_QT_EXAMINER_VIEWER_
#define  _SO_QT_EXAMINER_VIEWER_

#include <Inventor/Qt/SoQtDLLInit.h>
#include <Inventor/Qt/viewers/SoQtFullViewer.h>
#include <Inventor/SbLinear.h>

#include <QCursor>
#include <QDateTime>

// classes used
class SoFieldSensor;
class SoSeparator;
class SoSwitch;
class SoTranslation;
class SoScale;
class SoXtBitmapButton;

//////////////////////////////////////////////////////////////////////////////
//
//  Class: SoXtExaminerViewer
//
//      Examiner viewer - allows the user to change the camera position
//  by spinning a sphere in front of the viewpoint.
//
//
//      Keys used by this viewer:
//      -------------------------
//
//      Left Mouse: Tumbles the virtual trackball.
//
//      Middle Mouse:
//      Ctrl + Left Mouse: Translate up, down, left and right.
//
//      Ctrl + Middle Mouse:
//      Left + Middle Mouse: Dolly in and out (gets closer to and further
//                          away from the object).
//
//      <s> + click: Alternative to the Seek button. Press (but do not hold
//                  down) the <s> key, then click on a target object.
//
//      Right Mouse: Open the popup menu.
//
//////////////////////////////////////////////////////////////////////////////

// C-api: prefix=SoXtExamVwr
class SOQT_MEVIS_EXPORT SoQtExaminerViewer : public SoQtFullViewer
{
    Q_OBJECT
public:
    //! Constructor/Destructor
    SoQtExaminerViewer (BuildFlag flag, Type type = BROWSER,
                        QWidget* parent = nullptr, Qt::WindowFlags f = Qt::WindowFlags{});

    //! compatibility constructor
    SoQtExaminerViewer(
        QWidget* parent = nullptr,
        const char *name = nullptr,
        SbBool buildInsideParent = TRUE,
        SoQtFullViewer::BuildFlag flag = BUILD_ALL,
        SoQtViewer::Type type = BROWSER,
        SbBool buildNow = TRUE);

    ~SoQtExaminerViewer() override;

    void loadSettings (const QSettings& settings);
    void saveSettings (QSettings& settings);

    // interaction modes offered by this viewer:
    enum ViewerModes {
        PICK_MODE,          // interacts directly with the OpenInventor scene
        SPIN_MODE,          // spin scene
        SPIN_MODE_ACTIVE,   //   ...when active
        PAN_MODE,           // pan scene
        PAN_MODE_ACTIVE,    //   ...when active
        DOLLY_MODE,         // zoom scene
        DOLLY_MODE_ACTIVE,  //   ...when active
        SEEK_MODE,          // zoom/move to clicked point
        INTERACT_MODE_COUNT
    };

    // With these methods the keyboard/mouse bindings can be changed:
    // Reset all interactions to PICK_MODE:
    void resetInteractions();
    // Restore all interactions to their defaults:
    void restoreInteractions();
    // Set interaction mode for specific input states:
    // inputState and ignoreStateMask are a flag mask consisting of
    // Qt::KeyboardModifiers and Qt::MouseButtons. (Please set corresponding
    // modes on input states with the same keyboard modifiers and the
    // left mouse button unset or set (e.g. SPIN_MODE and SPIN_MODE_ACTIVE),
    // because the cursor should indicate what function is obtained when the
    // left mouse button is pressed.)
    void setInteraction (int inputState, int ignoreStateMask, ViewerModes mode);
    // Get interaction mode for given input state:
    ViewerModes getInteraction (int inputState);

    // Set/get the cursor shape for a given viewing mode
    virtual void setCursorShape (int viewingMode, const QCursor& shape);
    virtual QCursor getCursorShape (int viewingMode) const;

public slots:
    // Show/hide the point of rotation feedback, which only appears while
    // in Viewing mode. (default OFF)
    void        setFeedbackVisibility(SbBool onOrOff);
    SbBool      isFeedbackVisible() const       { return feedbackFlag; }

    // Set/get the point of rotation feeedback size in pixels (default 20).
    void        setFeedbackSize(double newSize);
    int         getFeedbackSize() const         { return (int) feedbackSize; }

    // Enable/disable the animation feature of the viewer.
    // (enabled by default)
    void        setAnimationEnabled(SbBool onOrOff);
    SbBool      isAnimationEnabled()            { return animationEnabled; }

    // Stop animation, if it is occurring, and queuery if the viewer is
    // currently animating.
    void        stopAnimating();
    SbBool      isAnimating()                   { return animatingFlag; }

    void        setWheelZoomEnabled(bool flag)  { wheelZoomEnabled = flag;  }
    SbBool      isWheelZoomEnabled() const      { return wheelZoomEnabled;  }

    void        setWheelRotationEnabled(bool flag) { wheelRotationEnabled = flag;  }
    SbBool      isWheelRotationEnabled() const     { return wheelRotationEnabled;  }

    //@{ since the normal cursor gets changed at many opportunities, divert these methods to act on the PICK_MODE cursor
    void setGLCursor (const QCursor& cursor) override;
    void unsetGLCursor() override;
    QCursor glCursor() const override;
    //@}

    // redefine these to add Examiner viewer functionality
    void        viewAll() override;
    void        resetToHomePosition() override;
    void        setCamera(SoCamera *cam, SbBool createdCamera) override;
    void        setViewing(SbBool onOrOff) override;
    void        setCursorEnabled(SbBool onOrOff) override;

protected:
    // redefine those routines to do viewer specific stuff
    void        processEvent (QEvent *anyevent) override;
    void        setSeekMode(SbBool onOrOff) override;
    void        actualRedraw() override;

    // Define those thumb wheels to rotate the object
    void        bottomWheelMotion(double newVal) override;
    void        leftWheelMotion(double newVal) override;
    void        rightWheelMotion(double newVal) override;

    // redefine those routines to also stop animation if any
    void        bottomWheelStart() override;
    void        leftWheelStart() override;

    // add viewer preference stuff
    QTabWidget* createPrefSheet() override;

    // add some viewer buttons
    void        createViewerButtons (QToolBar* parent) override;

    // viewer toolbar actions
    QAction*        perspAction;

    // react to visibility changes
    void        hideEvent (QHideEvent* event) override;
    void        showEvent (QShowEvent* event) override;

    // overridden to allow picking with unused button/modifier combinations:
    bool    isCurrentlyPicking() override;

protected slots:
    void setFeedbackSizeWheelValue (double value);
    void setFeedbackVisibilityState (int state) {
        setFeedbackVisibility (state == Qt::Checked);
    }
    void setAnimationEnabledState (int state) {
        setAnimationEnabled (state == Qt::Checked);
    }

private:
    void            commonConstructor();

    // return modeTable index for given pressed keyboard modifiers and mouse buttons
    int             getModeIndex (int inputState);

    // viewer state variables
    ViewerModes     modeTable[64]; // contains viewing mode depending on
                                   // keyboard modifiers and mouse buttons
    int             mode;
    QCursor*        modeCursors;
    int             modeCursorCount;
    SbVec2s         locator; // mouse position
    SbBool          firstBuild; // set FALSE after buildWidget called once

    // point of rotation feedback vars
    SbBool          feedbackFlag;
    double          feedbackSize;
    SoSeparator     *feedbackRoot;
    SoSwitch        *feedbackSwitch;
    SoTranslation   *feedbackTransNode;
    SoScale         *feedbackScaleNode;
    static const char *geometryBuffer;
    void            createFeedbackNodes();

    // variables used for doing spinning animation
    SbBool          animationEnabled, animatingFlag;
    SoFieldSensor   *animationSensor;
    QDateTime       lastMotionTime;
    static void     animationSensorCB(void *v, SoSensor *s);

    void            updateViewerMode (int modifiers = -1, int buttons = -1);
    void            switchMode(int newMode);
    void            updateCursor();
    void            defineCursors();

    // preference sheet stuff
    QWidget*        createExamPrefSheetGuts();

    // point of rotation pref sheet stuff
    double          feedbackSizeWheelValue;
    QWidget*        feedbackSizeWidgets;
    QCheckBox*      enableSpinToggle;
    QCheckBox*      showRotPointToggle;
    QDoubleSpinBox* feedbackInput;
    SoQtThumbWheel*     feedbackSizeWheel;

    bool            nestingFlag;
    bool            mouseInside; // set to true after mouse enter event
    SbBool          wheelZoomEnabled;
    SbBool          wheelRotationEnabled;
};

#endif  /* _SO_QT_EXAMINER_VIEWER_ */
