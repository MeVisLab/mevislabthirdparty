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

#ifndef  _SO_QT_CAMERA_CONTROLLER_
#define  _SO_QT_CAMERA_CONTROLLER_

#include <Inventor/Qt/SoQtDLLInit.h>
#include <Inventor/SoType.h>
#include <Inventor/SbTime.h>

// classes
class   SoNode;
class   SoDirectionalLight;
class   SoQtHeadlight;
class   SoGroup;
class   SoSeparator;
class   SoRotation;
class   SoCamera;
class   SoFieldSensor;
class   SoNodeSensor;
class   SoGetBoundingBoxAction;
class   SoGroup;
class   SoSwitch;
class   SoSFTime;
class   SbSphereSheetProjector;

//!  This class encapsulates the camera (and headlight) handling functions
//!  for SoQtViewer and derived classes.
class SOQT_MEVIS_EXPORT SoQtCameraController
{
public:
    //! An EDITOR viewer will create a camera under the user supplied scene
    //! graph (specified in setSceneGraph()) if it cannot find one in the
    //! scene and will leave the camera behind when supplied with a new scene.
    //!
    //! A BROWSER viewer will also create a camera if it cannot find one in
    //! the scene, but will place it above the scene graph node (camera will
    //! not appear in the user supplied scene graph), and will automatically
    //! remove it when another scene is supplied to the viewer.
    enum Type {
        BROWSER, // default viewer type
        EDITOR
    };

    //! Constructor/Destructor
    SoQtCameraController(Type type = BROWSER);
    virtual ~SoQtCameraController();

    //! Set scene root node and at which index to insert the camera in BROWSER mode
    void setSceneRoot(SoGroup* root, int camIndex);

    //! Sets/gets the scene graph to render. Whenever a new scene is supplied
    //! the first camera encountered will be by default used as the edited
    //! camera, else a new camera will be created.
    virtual void    setSceneGraph (SoNode *newScene);
    virtual SoNode *getSceneGraph();

    void            setSceneSize(const SbVec2s& size) { sceneSize = size; }

    //! Set and get the edited camera. setCamera() is only needed if the
    //! first camera found when setSceneGraph() is called isn't the one
    //! the user really wants to edit.
    //! cameraCreated should be TRUE if the camera was only created for this viewer.
    virtual void    setCamera (SoCamera *cam, SbBool cameraCreated);
    SoCamera        *getCamera()        { return camera; }

    bool            isPerspective() const;
    bool            isOrthographic() const;
    bool            hasExternalCamera() const { return !createdCamera; }

    //! Set and get the camera type that will be created by the viewer if no
    //! cameras are found in the scene graph. Possible choices are :
    //!      - SoPerspectiveCamera::getClassTypeId()
    //!      - SoOrthographicCamera::getClassTypeId()
    //!
    //! NOTE: the set method will only take affect next time a scene graph
    //! is specified (and if no camera are found).
    //!
    //! By default a perspective camera will be created if needed.
    virtual void    setCameraType (SoType type);
    SoType          getCameraType()         { return cameraType; }

    //! This routine will toggle the current camera from perspective to
    //! orthographic, and from orthographic back to perspective.
    virtual void    toggleCameraType();

    //! Camera routines.
    virtual void    viewAll();
    virtual void    viewAll(const SbRotation &dir); // view all with new camera direction
    virtual void    saveHomePosition();
    virtual void    resetToHomePosition();

    //! Turns the headlight on/off. (default ON)
    virtual void    setHeadlight (SbBool onOrOff);
    SbBool          isHeadlight()       { return headlightFlag; }

    //! Set and get the auto clipping plane. When auto clipping is ON, the
    //! camera near and far planes are dynamically adjusted to be as tight
    //! as possible (least amount of stuff is clipped). When OFF, the user
    //! is expected to manually set those planes within the preference sheet.
    //! (default is ON).
    void            setAutoClipping(SbBool onOrOff);
    SbBool          isAutoClipping() const      { return autoClipFlag; }

    //! Seek methods
    //!
    //! Routine to determine whether or not to orient camera on
    //! picked point (detail on) or center of the object's bounding box
    //! (detail off). Default is detail on.
    virtual void    setDetailSeek(SbBool onOrOff)   { detailSeekFlag = onOrOff; };
    SbBool          isDetailSeek()              { return detailSeekFlag; }

    //! Set the time a seek takes to change to the new camera location.
    //! A value of zero will not animate seek. Default value is 2 seconds.
    void            setSeekTime(float seconds)      { seekAnimTime = seconds; }
    float           getSeekTime()           { return seekAnimTime; }

    void            setZoomSensitivity(float sensitivity) { zoomSensitivity = sensitivity; }
    float           getZoomSensitivity() const            { return zoomSensitivity; }

    //! Returns headlight node. Since the headlight is created on demand, this returns
    //! a prototype headlight if no headlight was created, or if the headlight was
    //! created by another instance. If a headlight is created by this instance, the
    //! current attributes of the prototype headlight are copied to the actual headlight.
    //!
    //! You shouldn't store a pointer to the headlight long-term.
    SoDirectionalLight *getHeadlight();
    void            updateHeadlight();

    //! saves starting position of mouse drag, prepares ground for subsequent calls
    //! to panCamera, spinCamera or dollyCamera:
    void            startDrag(const SbVec2s &pos);

    // methods extracted from SoQtExaminerViewer:
    void            rotateCamera(const SbRotation &rot);
    void            panCamera(const SbVec2s &newPos);
    void            spinCamera(const SbVec2s &newPos);
    void            dollyCamera(const SbVec2s &newPos);
    void            zoomCamera(float amount);
    bool            doSpinAnimation();

    //! some event handling:
    void            arrowKeyPressed (int key);

protected:
    //!
    //! This routine is used by subclasses to initiate the seek animation. Given a
    //! screen mouse location, this routine will return the picked point
    //! and the normal at that point. It will also schedule the sensor to animate
    //! if necessary. The routine retuns TRUE if something got picked...
    //!
    //! Note: if detailSeek is on, the point and normal correspond to the exact
    //!      3D location under the cursor.
    //!      if detailSeek if off, the object bbox center and the camera
    //!      orientation are instead returned.
    SbBool          seekToPoint(const SbVec2s &mouseLocation);

    //! Subclasses CAN redefine this to interpolate camera position/orientation
    //! while the seek animation is going on (called by animation sensor).
    //! The parameter t is a [0,1] value corresponding to the animation percentage
    //! completion. (i.e. a value of 0.25 means that animation is only 1/4 of the way
    //! through).
    virtual void    interpolateSeekAnimation(float t);
    virtual void    computeSeekFinalOrientation();

    //! variables used for interpolating seek animations
    float           seekDistance;
    SbBool          seekDistAsPercentage; //! percentage/absolute flag
    SbBool          computeSeekVariables;
    SbVec3f         seekPoint, seekNormal;
    SbRotation      oldCamOrientation, newCamOrientation;
    SbVec3f         oldCamPosition, newCamPosition;

    //! Externally set the viewer into/out off seek mode (default OFF). Actual
    //! seeking will not happen until the viewer decides to (ex: mouse click).
    //!
    //! Note: setting the viewer out of seek mode while the camera is being
    //! animated will stop the animation to the current location.
    virtual void    setSeekMode(SbBool onOrOff);
    SbBool          isSeekMode()                { return seekModeFlag; }

    //! This is called during a paste.
    //! Subclasses may wish to redefine this in a way that
    //! keeps their viewing paradigm intact.
    virtual void    changeCameraValues(SoCamera *newCamera);

    static SoSFTime *getRealTime();

protected:
    //! global vars
    Type            type;
    SoCamera        *camera;            //! camera being edited
    static SoSFTime *realTime;          //! pointer to "realTime" global field

    //! local tree variables
    SoGroup         *sceneRoot;         //! root node given to the RA
    SoNode          *sceneGraph;        //! user supplied scene graph
    int             cameraIndex;        //! where to insert the camera in the sceneRoot in BROWSER mode

    //! auto clipping vars and routines
    SbBool          autoClipFlag;
    float           minimumNearPlane;   //! minimum near plane as percentage of far
    SoGetBoundingBoxAction *autoClipBboxAction;
    virtual void    adjustCameraClippingPlanes();

    virtual void    animationStarted() {}
    virtual void    animationFinished() {}

    SbVec2s         getDragStartPos() const { return startPos; }

private:
    void            setHeadlightInternal(bool insertFlag);

    //! current state vars
    SoType          cameraType;

    SbVec2s         sceneSize;

    //! camera original values, used to restore the camera
    SbBool          createdCamera;
    SbVec3f         origPosition;
    SbRotation      origOrientation;
    float           origNearDistance;
    float           origFarDistance;
    float           origFocalDistance;
    float           origHeight;

    //! seek animation vars
    SbBool          seekModeFlag;       //! TRUE when seek turned on externally
    SoFieldSensor   *seekAnimationSensor;
    SbBool          detailSeekFlag;
    float           seekAnimTime;
    SbTime          seekStartTime;
    static void     seekAnimationSensorCB(void *p, SoSensor *);

    //! headlight variables
    SoQtHeadlight   *headlightNode;
    SoGroup         *headlightParent;
    SoQtHeadlight   *prototypeHeadlightNode;  //! headlight to return from getHeadlight if isPrimaryHeadlightOwner is false
    SbBool          isPrimaryHeadlightOwner;  //! true if the headlight was created by this instance
    SbBool          headlightFlag;    //! true when headlight in turned on
    static SbName   headlightName;    //! name of the headlightNode, used to identify pre-existing headlight
    SoNodeSensor    *headlightParentSensor;
    static void     headlightParentDeletedCB(void *p, SoSensor *);

    SbVec2s         startPos; // starting mouse position
    SbSphereSheetProjector *sphereSheet;
    float           zoomSensitivity;

    // variables used for doing spinning animation
    SbRotation      *rotBuffer;
    int             firstIndex, lastIndex;
    SbRotation      averageRotation;
    SbBool          computeAverage;

    // camera panning vars
    SbVec3f         locator3D;
    SbPlane         focalplane;

    // SoSeparator needed to fix/optimize bounding box calculation
    SoSeparator*    boundingBoxSeparator;
};


#endif  /* _SO_QT_CAMERA_CONTROLLER_ */
