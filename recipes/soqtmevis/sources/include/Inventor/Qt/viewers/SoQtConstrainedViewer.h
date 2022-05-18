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

#ifndef  _SO_QT_CONSTRAINED_VIEWER_
#define  _SO_QT_CONSTRAINED_VIEWER_

#include <Inventor/Qt/viewers/SoQtFullViewer.h>
#include <Inventor/SbBox.h>


//////////////////////////////////////////////////////////////////////////////
//
//  Class: SoQtConstrainedViewer
//
//////////////////////////////////////////////////////////////////////////////

class SoQtConstrainedViewer : public SoQtFullViewer
{
    Q_OBJECT
public:

    // Specifies the upward direction of the viewer. This up direction is
    // used by the viewers to constrain the camera when tilting up/down, and
    // also used when rotating the camera right/left.
    // The default is the +Y (0,1,0) direction.
    void            setUpDirection(const SbVec3f &newUpDirection);
    SbVec3f         getUpDirection()                { return upDirection; }

    // redefine these to add constrained viewer functionality
    void    setCamera(SoCamera *newCam, SbBool createdCamera) override;
    void    saveHomePosition() override;
    void    resetToHomePosition() override;
    void    recomputeSceneSize() override;

 protected:
    SoQtConstrainedViewer(
        SoQtFullViewer::BuildFlag flag,
        SoQtViewer::Type type,
        QWidget* parent, Qt::WindowFlags f);
    ~SoQtConstrainedViewer() override;

    SbVec3f         upDirection;
    float           sceneHeight;

    // Tilts the camera, restraining it to 180 degree rotation from the
    // up direction. A positive angle tilts the camera up.
    virtual void        tiltCamera(float deltaAngle);

    // Redefine these to do constrained viewing tasks.
    // The bottom wheel rotates the camera around the up direction, the
    // left wheel tilts the camera up/down constraning to 180 degree from
    // the up direction.
    void        bottomWheelMotion(double newVal) override;
    void        leftWheelMotion(double newVal) override;

    // This is called during a paste.
    // We redefine this to keep the right vector of the camera
    // in a parallel plane.
    void        changeCameraValues(SoCamera *newCamera) override;

    // this routine is called by subclasses to find and set the new
    // up direction given the current mouse position. If something is
    // picked, the normal to the object picked will be used to specify
    // the new up direction.
    void                findUpDirection(const SbVec2s &mouseLocation);

    // this routine checks the camera orientation and makes sure that the
    // current right vector and the ideal right vector (cross between the
    // view vector and world up direction) are the same (i.e. no unwanted
    // roll), else it fixes it. This keeps the up direction valid.
    void                checkForCameraUpConstrain();

    // Redefine this to keep the up vector when seeking
    void        computeSeekFinalOrientation() override;

 private:
    SbVec3f         origUpDirection; // used to save/reset
};

#endif  /* _SO_XT_CONSTRAINED_VIEWER_ */
