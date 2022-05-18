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

#ifndef _SO_QT_RENDER_AREA_H_
#define _SO_QT_RENDER_AREA_H_

#include <Inventor/Qt/SoQtDLLInit.h>
#include <Inventor/Qt/SoQtGLWidget.h>
#include <Inventor/Qt/SoQtSceneHandler.h>
#include <Inventor/SbColor.h>
#include <Inventor/SoSceneManager.h>

class   SoNode;

//////////////////////////////////////////////////////////////////////////////
//
//  Class: SoQtRenderArea
//
//  Class to do Inventor rendering in a QGLWidget.
//
//////////////////////////////////////////////////////////////////////////////

// C-api: prefix=SoQtRA
class SOQT_MEVIS_EXPORT SoQtRenderArea
  : public SoQtGLWidget, public SoQtSceneHandler
{
    Q_OBJECT

public:
    SoQtRenderArea (QWidget* parent = nullptr, Qt::WindowFlags f = nullptr, bool build = true);
    ~SoQtRenderArea() override;

    //! Set old-school anti-aliasing hints (setting smoothing to TRUE will turn on
    //! anti-aliasing. If numPasses is 1, GL_*_SMOOTH_HINT are set to GL_NICEST.
    //! If numPasses is >1, Open Inventor does multiple renderings into the
    //! accumulation buffer (see SoGLRenderAction for details).
    bool setAntialiasing (SbBool smoothing, int numPasses) override;

    //! Enable/disable GL sample buffers on the framebuffer of the render area.
    //! If numSampleBuffers is set to 0, the maximum available sample buffers are used.
    virtual void setSampleBuffers(bool useSampleBuffers, int numSampleBuffers);

    //! Returns the current ratio between physical pixels and device-independent pixels
    //! of the GL widget drawing area.
    //! \ingroup HiDPIPublic
    virtual double getDevicePixelRatio() const;

    //! Calling this forces the render area to be redrawn now.
    //! It is not necessary to call this method if auto redraw is enabled
    //! (which is the default).
    void        render()        { updateGL(); }

    //! Render scene to whichever OpenGL context is currently active (but this context
    //! should be shared with the one from this widget).
    //! Set reinitialize to true if the GL context needs to be initialized in every call.
    void renderToCurrentContext (const SbViewportRegion& viewport, bool reinitialize = false);

    //! Set this to true if you need to get redrawRequested signals from the scene
    //! even if the widget is not visible, e.g. because you use renderToCurrentContext.
    void setRenderSignalAlwaysEnabled (bool enable = true);

    //! Returns value of flag.
    bool isRenderSignalAlwaysEnabled() const { return alwaysEnableRenderSignal; }

    //! returns true if the viewer does the initial rendering after it became visible
    bool isInitialRendering() const { return initialRendering; }

signals:
    //! this is emitted when the scene manager requests a redraw of the scene
    void redrawRequested();

protected:

    //! Set the GL format.
    void setFormat(const QGLFormat& format) override;

    void visibilityChanged (bool flag) override;

    //! Redefine these to do Inventor-specific things
    void processEvent (QEvent *anyEvent) override;
    void paintGL() override;
    void initializeGL() override;
    void resizeGL (int width, int height) override;

    //! overridden from SoQtSceneHandler
    void setWindowElement(SoState* state) override;
    QWidget* getDeviceWidget() override { return SoQtGLWidget::getRenderingWidget(); }
    bool isSceneVisible() override;
    void updateScene() override;

private:
    //! this will be set to true when initializeGL is called the first time
    bool isGLinitialized;

    //! if this is true, the scene manager will stay activated, even if the
    //! widget is not visible (but only if autoRedraw is true).
    bool alwaysEnableRenderSignal;

    //! flag that stores that the rendering is the first one after the viewer became visible.
    bool initialRendering;

    //! flag that indicates that sample buffers are used
    bool useSampleBuffers;
    //! number of sample buffers that should be used (0 = automatic)
    int  numSampleBuffers;
};


#endif /* _SO_QT_RENDER_AREA_H_ */


