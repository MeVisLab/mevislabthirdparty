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

#ifndef  _SO_QT_VIEWER_
#define  _SO_QT_VIEWER_

#include <Inventor/Qt/SoQtDLLInit.h>
#include <Inventor/SoType.h>
#include <Inventor/Qt/SoQtRenderArea.h>
#include <Inventor/Qt/SoQtCameraController.h>
#include <Inventor/misc/SoCallbackList.h>
#include <Inventor/SbTime.h>
#include <Qt>

// classes
class   SoNode;
class   SoDirectionalLight;
class   SoGroup;
class   SoRotation;
class   SoCamera;
class   SoDrawStyle;
class   SoLightModel;
class   SoFieldSensor;
class   SoQtViewer;
class   SoGetBoundingBoxAction;
class   SbPList;
class   SoSeparator;
class   SoSwitch;
class   SoComplexity;
class   SoPackedColor;
class   SoMaterialBinding;
class   SoSFTime;

//! callback function prototypes
typedef void SoQtViewerCB (void *userData, SoQtViewer *viewer);

//!      The Viewer component is the abstract base class for all viewers.
//!  It is subclassed from renderArea, adding viewing semantics to Inventor
//!  rendering.
class SOQT_MEVIS_EXPORT SoQtViewer
  : public SoQtRenderArea, public SoQtCameraController
{
    Q_OBJECT

public:

    //! list of possible drawing styles
    //!
    //! Note: Refer to the SoQtViewer man pages for a complete
    //! description of those draw styles.
    enum DrawStyle {
        VIEW_AS_IS,             //! unchanged
        VIEW_HIDDEN_LINE,       //! render only the front most lines
        VIEW_NO_TEXTURE,        //! render withought textures
        VIEW_LOW_COMPLEXITY,    //! render low complexity and no texture
        VIEW_LINE,              //! wireframe draw style
        VIEW_POINT,             //! point draw style
        VIEW_BBOX,              //! bounding box draw style
        VIEW_LOW_RES_LINE,      //! low complexity wireframe + no depth clearing
        VIEW_LOW_RES_POINT,     //! low complexity point + no depth clearing
        VIEW_SAME_AS_STILL,     //! forces the INTERACTIVE draw style to match STILL
        VIEW_WIREFRAME_OVERLAY  //! currently same effect as VIEW_LINE
    };
    enum DrawType {
        STILL,                  //! default to VIEW_NO_TEXTURE (or VIEW_AS_IS)
        INTERACTIVE             //! default to VIEW_SAME_AS_STILL
    };

    //! list of different buffering types
    enum BufferType {
        BUFFER_SINGLE,
        BUFFER_DOUBLE,
        BUFFER_INTERACTIVE      //! changes to double only when interactive
    };

    //! Sets/gets the scene graph to render. Whenever a new scene is supplied
    //! the first camera encountered will be by default used as the edited
    //! camera, else a new camera will be created.
    void    setSceneGraph (SoNode *newScene) override;
    SoNode *getSceneGraph() override;

    //! Set and get the edited camera. setCamera() is only needed if the
    //! first camera found when setSceneGraph() is called isn't the one
    //! the user really wants to edit.
    void    setCamera (SoCamera *cam, SbBool createdCamera) override;

    //! Set and get the feature that the alt key switches between viewing
    //! and picking mode. Default is ON
    virtual void    setAltSwitchingEnabled (SbBool on);
    bool            isAltSwitchingEnabled() { return altSwitchingEnabled; };

    //! Set and get the feature that the cursor keys manipulate the camera,
    //! S requests seek mode, and ESC switches picking mode. Default is ON
    virtual void    setKeyCommandsEnabled (SbBool on);
    bool            isKeyCommandsEnabled() { return keyCommandsEnabled; };


public slots:
    //! Proxy slots for methods in SoQtCameraController:
    void    toggleCameraTypeSlot()    { SoQtCameraController::toggleCameraType();    }
    void    viewAllSlot()             { SoQtCameraController::viewAll();             }
    void    saveHomePositionSlot()    { SoQtCameraController::saveHomePosition();    }
    void    resetToHomePositionSlot() { SoQtCameraController::resetToHomePosition(); }

    //! Sets/gets the current drawing style in the main view - The user
    //! can specify the INTERACTIVE draw style (draw style used when
    //! the scene changes) independently from the STILL style.
    //!
    //! STILL defaults to VIEW_AS_IS.
    //! INTERACTIVE defaults to VIEW_NO_TEXTURE on machine that do not support
    //! fast texturing, VIEW_SAME_AS_STILL otherwise.
    //!
    //! Refer to the SoQtViewer man pages for a complete description
    //! of those draw styles.
    virtual void    setDrawStyle (SoQtViewer::DrawType type,
                                  SoQtViewer::DrawStyle style);
    SoQtViewer::DrawStyle getDrawStyle (SoQtViewer::DrawType type);

    //! Sets/gets the current buffering type in the main view.
    //! (default BUFFER_DOUBLE)
    virtual void    setBufferingType (SoQtViewer::BufferType type);
    SoQtViewer::BufferType getBufferingType()       { return bufferType; }

    //! redefine this to call the viewer setBufferingType() method instead.
    void    setDoubleBuffer (SbBool onOrOff) override;

    //! Set/get whether the viewer is turned on or off. When turned off
    //! events over the renderArea are sent down the sceneGraph
    //! (picking can occurs). (default viewing is ON)
    virtual void    setViewing (SbBool onOrOff);
    SbBool          isViewing() const       { return viewingFlag; };

    //! Set/get whether the viewer is allowed to change the cursor over
    //! the renderArea window. When disabled, the cursor is undefined
    //! by the viewer and will not change as the mode of the viewer changes.
    //! When re-enabled, the viewer will reset it to the appropriate icon.
    //!
    //! Disabling the cursor enables the application to set the cursor
    //! directly on the viewer window or on any parent widget of the viewer.
    //! This can be used when setting a busy cursor on the application shell.
    //!
    //! Subclasses should redefine this routine to call setGLCursor()
    //! or unsetGLCursor() with the appropariate glyph. The base class
    //! routine only sets the flag.
    virtual void    setCursorEnabled (SbBool onOrOff);
    SbBool          isCursorEnabled() const   { return cursorEnabledFlag; }

    //! Set and get the auto clipping plane. When auto clipping is ON, the
    //! camera near and far planes are dynamically adjusted to be as tight
    //! as possible (least amount of stuff is clipped). When OFF, the user
    //! is expected to manually set those planes within the preference sheet.
    //! (default is ON).
    void            setAutoClipping(SbBool onOrOff);
    //! Turns stereo viewing on/off on the viewer (default off). When in
    //! stereo mode, which may not work on all machines, the scene is rendered
    //! twice (in the left and right buffers) with an offset between the
    //! two views to simulate stereo viewing. Stereo classes have to be used
    //! to see the affect and /usr/gfx/setmon needs to be called to set the
    //! monitor in stereo mode.
    //!
    //! The user can also specify what the offset between the two views
    //! should be.
    virtual void    setStereoViewing(SbBool onOrOff);
    virtual SbBool  isStereoViewing();
    void            setStereoOffset(float dist) { stereoOffset = dist; }
    float           getStereoOffset()   { return stereoOffset; }

public:
    //! add/remove start and finish callback routines on the viewer. Start callbacks will
    //! be called whenever the user starts doing interactive viewing (ex: mouse
    //! down), and finish callbacks are called when user is done doing
    //! interactive work (ex: mouse up).
    //!
    //! Note: The viewer pointer 'this' is passed as callback data
    void    addStartCallback(SoQtViewerCB *f, void *userData = nullptr)
            { startCBList->addCallback((SoCallbackListCB *)f, userData); }
    void    addFinishCallback(SoQtViewerCB *f, void *userData = nullptr)
            { finishCBList->addCallback((SoCallbackListCB *)f, userData); }
    void    removeStartCallback(SoQtViewerCB *f, void *userData = nullptr)
            { startCBList->removeCallback((SoCallbackListCB *)f, userData); }
    void    removeFinishCallback(SoQtViewerCB *f, void *userData = nullptr)
            { finishCBList->removeCallback((SoCallbackListCB *)f, userData); }

    //! This can be used to let the viewer know that the scene graph
    //! has changed so that the viewer can recompute things like speed which
    //! depend on the scene graph size.
    //!
    //! NOTE: This routine is automatically called whenever setSceneGraph()
    //! is called.
    virtual void    recomputeSceneSize();

public: // was protected
    //! Constructor/Destructor
    SoQtViewer (Type type = BROWSER, QWidget* parent = nullptr, Qt::WindowFlags f = Qt::WindowFlags{});
protected:
    ~SoQtViewer() override;

    //! global vars
    SbBool          viewingFlag;        //! FALSE when the viewer is off
    SbBool          altSwitchBack;      //! flag to return to PICK after an Alt release
    SbBool          cursorEnabledFlag;
    static SoSFTime *viewerRealTime;    //! pointer to "realTime" global field
    float           sceneSize;          //! the larger of the X,Y,Z scene BBox
    float           viewerSpeed;        //! default to 1.0 - SoXtFullViewer add UI to inc/dec

    //! local tree variables
    SoSeparator     *sceneRoot;         //! root node given to the RA

    //! Subclasses can call this routine to handle a common set of events. A Boolean
    //! is returned to specify whether the event was handled by the base class.
    //! Currently handled events and functions are :
    //!      'Esc' key - toggles viewing on/off
    //!      When viewing OFF - send all events down the scene graph
    //!      When camera == NULL - Discard all viewing events
    //!      'home' Key - calls resetToHomePosition()
    //!      's' Key - toggles seek on/off
    //!      Arrow Keys - moves the camera up/down/right/left in the viewing plane
    void            processEvent (QEvent* anyEvent) override;

    void    animationStarted() override  { interactiveCountInc(); }
    void    animationFinished() override { interactiveCountDec(); }

protected slots:
    //! Invokes the start and finish viewing callbacks. Subclasses NEED to call
    //! those routines when they start and finish doing interactive viewing
    //! operations so that correct interactive drawing style and buffering
    //! types, as well as application callbacks, gets set and called properly.
    //!
    //! Those routines simply increment and decrement a counter. When the counter
    //! changes from 0->1 the start viewing callbacks are called. When the counter
    //! changes back from 1->0 the finish viewing callbacks are called.
    //! The counter approach enables different parts of a viewer to call those
    //! routines withough having to know about each others (which is not
    //!
    void            interactiveCountInc();
    void            interactiveCountDec();
    int             getInteractiveCount()   { return interactiveCount; }

protected:
    //! update cameraController about widget size changes
    void resizeGL (int width, int height) override;

    //! Externally set the viewer into/out off seek mode (default OFF). Actual
    //! seeking will not happen until the viewer decides to (ex: mouse click).
    //!
    //! Note: setting the viewer out of seek mode while the camera is being
    //! animated will stop the animation to the current location.
    void    setSeekMode(SbBool onOrOff) override;

    //! redefine this routine to adjust the camera clipping planes just
    //! before doing a redraw. The sensor will be unschedule after the camera
    //! is changed in the base class to prevent a second redraw from occuring.
    void    actualRedraw() override;

    //! Convenience routines which subclasses can use when drawing viewer
    //! feedback which may be common across multiple viewers. There is for
    //! example a convenience routine which sets an orthographics projection
    //! and a method to draw common feedback like the roll anchor (used by
    //! a couple of viewers).
    //!
    //! All drawing routines assume that the window and projection is
    //! already set by the caller.
    //!
    //! set an ortho projection of the glx window size - this also turns
    //! zbuffering off and lighting off (if necessary).
    static void     setFeedbackOrthoProjection (const SbVec2s &glxSize);
    //! restores the zbuffer and lighting state that was changed when
    //! setFeedbackOrthoProjection() was last called.
    static void     restoreGLStateAfterFeedback();
    //! draws a simple 2 colored cross at given position
    static void     drawViewerCrossFeedback(SbVec2s loc);
    //! draws the anchor feedback given center of rotation and mouse location
    static void     drawViewerRollFeedback(SbVec2s center, SbVec2s loc);

    // This method was used to check if textures should be used.
    // Since we have 2006, and any decent graphics card has sufficient texture
    // facilities, this check was removed
    // virtual void    afterRealizeHook();

    //! this method was introduced so that mouse events can be used for picking even
    //! if the viewer is nominally in viewing mode (but the mouse events are otherwise
    //! unused)
    virtual bool    isCurrentlyPicking() { return !isViewing(); }

 private:
    //! current state vars
    BufferType      bufferType;
    SbBool          interactiveFlag;    //! TRUE while doing interactive work
    float           stereoOffset;
    SbBool          altSwitchingEnabled; // if true, alt key switches between viewing and picking
    SbBool          keyCommandsEnabled;  // if true, cursor keys manipulate camera (and S sets seek mode)

    //! draw style vars
    DrawStyle       stillDrawStyle, interactiveDrawStyle;
    SoSwitch        *drawStyleSwitch;   //! on/off draw styles
    SoDrawStyle     *drawStyleNode;     //! LINE vs POINT
    SoLightModel    *lightModelNode;    //! BASE_COLOR vs PHONG
    SoPackedColor   *colorNode;         //! hidden line first pass
    SoMaterialBinding   *matBindingNode; //! hidden line first pass
    SoComplexity    *complexityNode;    //! low complexity & texture off
    void            setCurrentDrawStyle (SoQtViewer::DrawStyle style);
    void            doRendering();

    //! interactive viewing callbacks
    int             interactiveCount;
    SoCallbackList  *startCBList;
    SoCallbackList  *finishCBList;
    static void     drawStyleStartCallback  (void *, SoQtViewer *v);
    static void     drawStyleFinishCallback (void *, SoQtViewer *v);
    static void     bufferStartCallback     (void *, SoQtViewer *v);
    static void     bufferFinishCallback    (void *, SoQtViewer *v);

    //! set the zbuffer on current window to correct state
    void            setZbufferState();
    SbBool          isZbufferOff();
};


#endif  /* _SO_XT_VIEWER_ */
