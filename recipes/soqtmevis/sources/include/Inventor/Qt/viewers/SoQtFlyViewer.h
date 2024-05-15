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

#ifndef  _SO_QT_FLY_VIEWER_
#define  _SO_QT_FLY_VIEWER_

#include <Inventor/Qt/viewers/SoQtConstrainedViewer.h>
#include <Inventor/SbLinear.h>
#include <Inventor/SbTime.h>

class   SoFieldSensor;

//////////////////////////////////////////////////////////////////////////////
//
//  Class: SoQtFlyViewer
//
//
//      Keys used by this viewer:
//      -------------------------
//
//  Left Mouse: Click to increase speed.
//
//  <s> + Left Mouse: Alternative to the Seek button. Press (but do not
//      hold down) the <s> key, then click on a target object.
//
//  <u> + Left Mouse: Press (but do not hold down) the <u> key, then
//      click on a target object to set the "up" direction to the surface normal.
//      By default +y is the "up" direction.
//
//  Middle Mouse: Click to decrease speed.
//
//  Left and Middle Mouse: Click boths simultaneously to stop.
//
//  Ctrl: Hold the key down to temporary stop and rotate the viewpoint.
//
//  Right Mouse: Open the popup menu.
//
//////////////////////////////////////////////////////////////////////////////

// C-api: prefix=SoQtFlyVwr
class SoQtFlyViewer : public SoQtConstrainedViewer
{
    Q_OBJECT
public:

    // constructor
    SoQtFlyViewer (
        SoQtFullViewer::BuildFlag flag = BUILD_ALL,
        SoQtViewer::Type type = BROWSER,
        QWidget* parent = nullptr,
        Qt::WindowFlags f = Qt::WindowFlags{});

    // compatibility constructor
    SoQtFlyViewer(
        QWidget* parent,
        const char *name = nullptr,
        SbBool buildInsideParent = TRUE,
        SoQtFullViewer::BuildFlag flag = BUILD_ALL,
        SoQtViewer::Type type = BROWSER,
        SbBool buildNow = TRUE);
    ~SoQtFlyViewer() override;

    // redefine these to add fly viewer functionality
    void    setViewing(SbBool onOrOff) override;
    void    resetToHomePosition() override;
    void    setCamera(SoCamera *cam, SbBool createdCamera) override;
    void    setCursorEnabled(SbBool onOrOff) override;

    // This is redefined to prevent the camera type from being changed
    void    setCameraType(SoType type) override;

protected:
    // redefine those routines to do viewer specific stuff
    void        processEvent(QEvent *anyevent) override;
    void        setSeekMode(SbBool onOrOff) override;
    void        actualRedraw() override;
    void        rightWheelMotion (double) override;

    // add viewer preference stuff
    QTabWidget* createPrefSheet() override;

protected slots:
    void increaseFlySpeed();
    void decreaseFlySpeed();

private:
    // viewer state variables
    int             mode;
    QCursor         viewerCursor, seekCursor, upCursor;
    SbVec2s         locator; // mouse position
    SbVec2s         startPos; // mouse starting position
    SbRotation      camStartOrientation;

    // variables used for doing moving animation
    SoFieldSensor   *animationSensor;
    SbTime          prevAnimTime;
    float           speed, maxSpeed, maxStraightSpeed;
    float           speedLimit, speedLimitFactor;

    // preference sheet stuff
    QWidget*        createFlyPrefSheetGuts();

    void            drawViewerFeedback();
    void            switchMode(int newMode);
    void            changeMaxStraightSpeed(SbBool increase);
    void            calculateMaxSpeed();
    static void     animationSensorCB(void *, SoSensor *);
    void            doCameraAnimation();

    // this is called by both constructors
    void constructorCommon();
};

#endif  /* _SO_XT_FLY_VIEWER_ */
