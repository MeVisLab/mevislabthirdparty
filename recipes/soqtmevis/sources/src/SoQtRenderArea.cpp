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

#include <Inventor/Qt/SoQt.h>
#include <Inventor/Qt/SoQtRenderArea.h>
#include <Inventor/Qt/devices/SoQtDevice.h>
#include <QEvent>
#include <QMouseEvent>
#include <QDate>
#include <QTime>

#include <Inventor/SoInteraction.h>
#include <Inventor/SoDB.h>
#include <Inventor/SbLinear.h>
#include <Inventor/errors/SoDebugError.h>
#include <Inventor/elements/SoWindowElement.h>
#include <Inventor/nodes/SoNode.h>
#include <Inventor/nodes/SoSelection.h>
#include <Inventor/nodes/SoLocateHighlight.h>
#include <Inventor/actions/SoHandleEventAction.h>
#include <Inventor/Qt/devices/SoQtDevice.h>
//#include <Inventor/Qt/devices/SoQtKeyboard.h>
//#include <Inventor/Qt/devices/SoQtMouse.h>
#include <cstdio>
#include <cstdlib>

// KeyPress/KeyRelease seem to be defined as Macros on Linux.
#ifdef KeyPress
#  undef KeyPress
#endif
#ifdef KeyRelease
#  undef KeyRelease
#endif

SoQtRenderArea::SoQtRenderArea (QWidget* parent, Qt::WindowFlags f, bool build)
: SoQtGLWidget (parent, f)
{
    SoQt::init("Dummy");

    // Inventor specific variables
    QGLFormat glf (QGL::Rgba | QGL::DoubleBuffer | QGL::DepthBuffer | QGL::DirectRendering);
    // Call setFormat from parent class to avoid early construction of decoration which will fail
    SoQtGLWidget::setFormat(glf);

    setBorder (TRUE);

    autoFocus = true;

    isGLinitialized = false;
    alwaysEnableRenderSignal = false;
    initialRendering = true;
    useSampleBuffers = false;
    numSampleBuffers = 0;

    if (build) {
        buildWidget();
    }
}

SoQtRenderArea::~SoQtRenderArea()
{
}

void
SoQtRenderArea::setFormat(const QGLFormat& format)
{
  // Since setting a new format will result in a new QGLWidget
  // we have to give the devices a chance to detach and reattach.

  detachAllDevices();

  SoQtGLWidget::setFormat(format);

  reattachAllDevices();
}

void
SoQtRenderArea::processEvent(QEvent *anyevent)
{
    processSceneEvent(anyevent);
}

void
SoQtRenderArea::setWindowElement(SoState* state)
{
    if (state) {
      // Note: Except for the GL render action, this sets highly system dependent
      //       context information that should not be used by typical Open Inventor nodes.
      //       We only provide this so that legacy FME code (AppVis2 and SoRL keep working).
      // Newer code should make use of SoViewerElement/SoViewerProxy, to also work on remote rendering.
      SoWindowElement::set (state, Window{}, nullptr, nullptr, getGLRenderAction());
    }
}


void
SoQtRenderArea::initializeGL()
{
    SoQtGLWidget::initializeGL();
    initializeScene(1); // share ID is always 1, because all contexts are shared
    isGLinitialized = true;
}

void
SoQtRenderArea::resizeGL (int width, int height)
{
    SoQtGLWidget::resizeGL (width, height);
    resizeScene(width, height, getGlxDevicePixelRatio(),
      qobject_cast<QGLWidget*>(const_cast<const SoQtRenderArea*>(this)->getRenderingWidget()));
}

void
SoQtRenderArea::paintGL()
{
    // char buffer[200];
    // sprintf (buffer, "SoQtRenderArea::paintGL, depth=%i %i\n", format().depth(), format().depthBufferSize());
    paintScene();
    initialRendering = false;
}

bool
SoQtRenderArea::setAntialiasing (SbBool smoothing, int numPasses)
{
    if (SoQtSceneHandler::setAntialiasing(smoothing, numPasses)) {

        QGLFormat format = this->format();
        if (format.accum() != (bool)smoothing) {
            format.setAccum ((bool)smoothing);
            setFormat (format);
        }
        return true;
    } else {
      return false;
    }
}

void SoQtRenderArea::setSampleBuffers( bool useSampleBuffers, int numSampleBuffers )
{
  if (useSampleBuffers != this->useSampleBuffers ||
    numSampleBuffers != this->numSampleBuffers) {

      this->useSampleBuffers = useSampleBuffers;
      this->numSampleBuffers = numSampleBuffers;

      QGLFormat format = this->format();
      format.setSampleBuffers(useSampleBuffers);
      if (useSampleBuffers) {
        if (numSampleBuffers <= 0) {
          if (format.samples()!=-1) {
            // unfortunately there is no way to remove the samplers from the format...
            format.setSamples(16);
          }
        } else {
          format.setSamples(numSampleBuffers);
        }
      }
      setFormat (format);
  }
}

double
SoQtRenderArea::getDevicePixelRatio() const
{
  const QWidget *renderingWidget = SoQtGLWidget::getRenderingWidget();
  return (renderingWidget) ? renderingWidget->devicePixelRatioF() : 1.0;
}

void SoQtRenderArea::visibilityChanged(bool visible)
{
    if (visible) {
      initialRendering = true;
    }
    if ((visible || alwaysEnableRenderSignal) && isAutoRedraw()) {
        activate();
    } else {
        deactivate();
    }
}


void
SoQtRenderArea::updateScene()
{
    emit redrawRequested();
    // if alwaysEnableRenderSignal is set, we might get a callback though
    // the widget is not visible, so check this first before rendering
    if (isVisible()) {
        updateGL();
    }
}

bool
SoQtRenderArea::isSceneVisible()
{
  return (isVisible() || alwaysEnableRenderSignal);
}


void
SoQtRenderArea::renderToCurrentContext (const SbViewportRegion& viewport, bool reinitialize)
{
    SoSceneManager* sceneMgr = getSceneManager();
    SbViewportRegion oldViewport = sceneMgr->getViewportRegion();
    const bool viewportDiffers =
        (  viewport.getWindowSize() != oldViewport.getWindowSize()
        || viewport.getViewportOriginPixels() != oldViewport.getViewportOriginPixels()
        || viewport.getViewportSizePixels() != oldViewport.getViewportSizePixels() );
    if (viewportDiffers) {
        // temporarily set new viewport (hopefully this is fast)
        sceneMgr->setViewportRegion(viewport);
    }
    if (!isGLinitialized || reinitialize) {
        // If initializeGL hasn't been called yet, we do it now. Since we set a context ID
        // in the scene manager, the current context should be shared with this widget.
        // Otherwise things could get confused.
        initializeGL();
    }
    // draw the scene
    paintScene();
    if (viewportDiffers) {
        // restore the old viewport
        sceneMgr->setViewportRegion(oldViewport);
    }
}

void
SoQtRenderArea::setRenderSignalAlwaysEnabled (bool enable)
{
    alwaysEnableRenderSignal = enable;
    if ((isVisible() || enable) && isAutoRedraw()) {
        activate();
    } else {
        deactivate();
    }
}

