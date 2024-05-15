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
 * Author(s): David Mott, Alain Dumesny
 * Ported to Qt4 by MeVis (http://www.mevis.de), 2006
 */

#ifndef _SO_QT_SCENE_HANDLING_H_
#define _SO_QT_SCENE_HANDLING_H_

#include <Inventor/Qt/SoQtDLLInit.h>
#include <Inventor/SbColor.h>
#include <Inventor/sensors/SoNodeSensor.h>
#include <Inventor/SoSceneManager.h>
#include <Inventor/actions/SoGLRenderAction.h>
#include <Inventor/nodes/SoCallback.h>
#include <Inventor/Qt/SoQtStandardEventTranslator.h>

#include <QPoint>
#include <QList>

class   SoHandleEventAction;
class   SoQtDevice;
class   SoNode;
class   SoGroup;
class   SoSelection;

class QInputEvent;

//////////////////////////////////////////////////////////////////////////////
//
//  Class: SoQtSceneHandler
//
//  Class to provide scene handling, core rendering and event translation
//  (Extracted from SoQtRenderArea)
//
//////////////////////////////////////////////////////////////////////////////

class SOQT_MEVIS_EXPORT SoQtSceneHandler
{
public:
    SoQtSceneHandler();
    virtual ~SoQtSceneHandler();

    //! Set the scene graph to render
    virtual void    setSceneGraph (SoNode *newScene);

    //! Get the rendered scene graph
    virtual SoNode* getSceneGraph();

    //! Adds a SoCallback node on top of the scene. If afterScene is set, the node is inserted
    //! to be called last (after the scene has been traversed), otherwise to be called first
    SoCallback* addSceneCallback (SoCallbackCB* func, void* userData = nullptr, bool afterScene = false);
    //! Removes a SoCallback node from the scene, returns false if it wasn't there
    bool removeSceneCallback (SoCallback* callbackNode);

    //@{ Handle/Unhandle devices.
    //! When registerDevice is called, the
    //! render area will register interest in events which that device
    //! generates, and pass those events into the scene graph.
    void        registerDevice(SoQtDevice *d);
    //! unregisterDevice means the render area will no longer listen
    //! to events from the passed device.
    void        unregisterDevice(SoQtDevice *d);
    //@}

    //! Register input devices whose runtime type names are passed in a space separated list.
    //! The input devices must be derived from SoQtDevice.
    void        registerNamedDevices(const SbString &devicesList);

    //! Detach all registered devices from the widget.
    void        detachAllDevices();
    //! Reattach all registered devices with the widget.
    void        reattachAllDevices();

    //! Set the window background color when in RGB mode (defaults to black (0,0,0))
    virtual void setBackgroundColor (const SbColor &c)
                                { sceneMgr->setBackgroundColor(c); }
    //! Get the window background color when in RGB mode
    const SbColor&  getBackgroundColor() const
                                { return sceneMgr->getBackgroundColor(); }

    //! Set current viewport region to use for rendering
    void        setViewportRegion (const SbViewportRegion &newRegion)
                    { sceneMgr->getGLRenderAction()->setViewportRegion(newRegion); }
    //! Get current viewport region to use for rendering
    const SbViewportRegion &getViewportRegion() const
                    { return sceneMgr->getGLRenderAction()->getViewportRegion(); }

    //! Transparency level setting methods which specifies how
    //! transparent objects are rendered (quality/speed trade off).
    void        setTransparencyType (SoGLRenderAction::TransparencyType type);
    //! Get transparency level setting
    SoGLRenderAction::TransparencyType  getTransparencyType() const
                    { return sceneMgr->getGLRenderAction()->getTransparencyType(); }


    //! Set anti-aliasing hints, returns true if the values have indeed changed
    virtual bool setAntialiasing (SbBool smoothing, int numPasses);
    //! Get anti-aliasing hints
    void        getAntialiasing (SbBool &smoothing, int &numPasses) const
                            { sceneMgr->getAntialiasing(smoothing, numPasses); }

    //! Enable/prevent window clearing from happening before a rendering
    //! starts (default is clearBeforeRender TRUE).
    void        setClearBeforeRender(SbBool trueOrFalse) { clearFirst = trueOrFalse; }
    //! get window clearing setting
    SbBool      isClearBeforeRender() const { return clearFirst; }

    //! The render area will automatically redraw whenever something
    //! in the scene graph changes. Passing FALSE to setAutoRedraw()
    //! will disable this feature. NOTE: the render area will always
    //! redraw in response to window system events (e.g. resize, exposure)
    //! regardless of the setting of the auto redraw flag.
    void        setAutoRedraw (SbBool trueOrFalse);

    //! get auto redraw setting
    SbBool      isAutoRedraw() const { return autoRedraw; }

    //! Set the priority of the redraw sensor
    void        setRedrawPriority(uint32_t priority)
                                { sceneMgr->setRedrawPriority(priority); }
    //! Get the priority of the redraw sensor
    uint32_t    getRedrawPriority() const
                                { return sceneMgr->getRedrawPriority(); }
    //! get the default priority number.
    static uint32_t getDefaultRedrawPriority()
                                { return SoSceneManager::getDefaultRedrawPriority(); }

    //! Schedule a redraw to happen sometime soon. This will schedule the redraw sensor
    //! if auto-redraw is TRUE (default) else cause an immediate redraw of the scene if
    //! auto-redraw if FALSE.
    void        scheduleRedraw();

    //! Call this convenience method to have this render area redraw
    //! whenever the selection list changes in the passed node. This
    //! is useful if using a highlight render action like the
    //! SoBoxHighlightRenderAction to correctly render whenever the
    //! selection changes. Pass NULL to turn this off.
    void        redrawOnSelectionChange (SoSelection* s);

    //! set the scene manager
    void        setSceneManager (SoSceneManager *sm) { sceneMgr = sm; }
    //! get scene manager
    SoSceneManager* getSceneManager() const { return sceneMgr; }

    //! Set GL render action
    void        setGLRenderAction (SoGLRenderAction *ra)
                            { sceneMgr->setGLRenderAction(ra); }
    //! Get GL render action
    SoGLRenderAction* getGLRenderAction() const
                            { return sceneMgr->getGLRenderAction(); }

    //! This method translates Qt key and mouse events into Inventor events.
    //! It returns null if another event type was given.
    virtual const SoEvent* translateStdEvent (QEvent *xe);

    //! This method translates Qt events into Inventor events via the installed
    //! devices, falling back to translateStdEvent if no device matched.
    //! It returns null if translation failed completely.
    const SoEvent* translateEvent (QEvent *xe);

protected:
    //! override this to set the SoWindowElement for the scene
    virtual void setWindowElement(SoState* /*state*/) {}

    //! override this to enable/disable devices for the correct widget
    virtual QWidget* getDeviceWidget() { return nullptr; }

    //! override this to initiate a redraw of the scene
    virtual void updateScene() = 0;

    //! override this to tell if the scene should be considered visible
    //! (also look at the comments of activate/deactivate)
    virtual bool isSceneVisible() = 0;

public:
    //! activate/deactivate scene update sensors, call this if the return value
    //! of isSceneVisible changes (you will probably have to call activate()
    //! at least once!)
    void        activate();             // connects the sensor
    void        deactivate();           // disconnects the sensor

    //! Call these methods when the OpenGL context is created or has changed
    virtual void initializeScene(int shareID);

    //! Call this if the size of the rendering surface changed
    virtual void resizeScene (int width, int height, double devicePixelRatio = 1.0, bool sizeIncorporatesRatio = false);

    //! Paint/render the Inventor scene using the current OpenGL context.
    //! It also resets the lazy element and resends the last mouse position.
    //! After this, actualRedraw() is called.
    virtual void paintScene();

    //! This must be called to pass events to the scene
    virtual void processSceneEvent (QEvent *anyEvent);

    //! Re-sends the last mouse position as a mouse move event, e.g. because the scene
    //! layout has changed spontaneously and the mouse positions needs to be re-evaluated.
    void resendLastMousePosition();

protected:
    //! This method renders the scene to OpenGL and should not be called directly,
    //! use paintScene() instead. It can (and is) overloaded in sub-classes (e.g. Viewers)
    //! to implement rendering details (like stereo camera rendering etc.).
    virtual void actualRedraw();

    // subclasses have access to the device list for event processing
    QList<SoQtDevice*> deviceList;        // list of devices

private:
    // these make rendering/redrawing happen
    SoSceneManager *sceneMgr;   // this manages rendering and events
    SoGroup        *sceneContainer;  // used to take on SoCallback nodes
    SoNode         *mainScene;       // this is the scene set with setSceneGraph
    int            preCallbackCount; // number of pre-scene callback nodes

    SbBool         clearFirst;       // call clear() before rendering
    SbBool         autoRedraw;  // if TRUE, then we automatically redraw

    void           reinstallDevices (QWidget newWidget);

    static void    selectionChangeCB (void *userData, SoSelection *s);
    SoSelection    *selection;

    // static callbacks
    SbBool         firstEvent; // used to init the action SoWindowElement
    static void    renderCB (void *, SoSceneManager *);

    // current size of the rendering surface:
    SbVec2s        currentSize;

    SoQtStandardEventTranslator standardEventTranslator;

    //! some event handling:
    void            translateAndSendEvent(QEvent *anyevent);

    void            synthesizeCurrentButtonState (QMouseEvent* me);
    void            synthesizeButtonState (Qt::MouseButtons newButtons,
                                           Qt::MouseButton button, QMouseEvent* me, bool press);
    void            synthesizeCurrentModifierState (Qt::KeyboardModifiers modifiers);
    void            synthesizeModifierState (Qt::KeyboardModifiers newModifiers,
                                             Qt::KeyboardModifier modifier,
                                             Qt::Key keyCode, bool press);
    double devicePixelRatio;
    Qt::MouseButtons storedButtonState;
    Qt::KeyboardModifiers storedModifierState;
    static SoQtSceneHandler* lastPositionEventHandler; // last event handler that had a mouse event
    QPoint lastEventPosition;
    bool lastEventPositionValid;
    bool lockEventHandling; // make sure events can't be handled recursively
};


#endif /* _SO_QT_SCENE_HANDLING_H_ */


