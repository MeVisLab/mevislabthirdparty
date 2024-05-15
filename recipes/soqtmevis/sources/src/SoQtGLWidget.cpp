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
 * Author(s): Alain Dumesny, David Mott
 * Ported to Qt4 by MeVis (http://www.mevis.de), 2006
 */

#include <Inventor/errors/SoDebugError.h>
#include <Inventor/Qt/SoQt.h>

#include <Inventor/Qt/SoQtGLWidget.h>

#include "SoQtRealQOpenGLWidget.h"
#include "SoQtOffscreenGLWidget.h"

#include <QVBoxLayout>
#include <QStackedWidget>

#include <QApplication>
#include <QVariant>

#include "SoQtContextShareManager.h"


SoQtGLWidget::SoQtGLWidget (QWidget* parent, Qt::WindowFlags f)
: QWidget (parent, f)
, _glCursorIsSet (false)
{
    mainWidget = nullptr;
    borderSize = 0;
    minGLWidth  = 10;
    minGLHeight = 10;
    // we should use a BorderLayout, but a QHBoxLayout inside a QVBoxLayout
    // should do the same:
    vertLayout = new QVBoxLayout();
    vertLayout->setContentsMargins (0,0,0,0);
    vertLayout->setSpacing (0);
    setLayout (vertLayout);
    horiLayout = new QHBoxLayout();
    horiLayout->setContentsMargins(0,0,0,0);
    horiLayout->setSpacing (0);
    vertLayout->addLayout (horiLayout, 1);
    managerWidget = new QStackedWidget (this);
    managerWidget->layout()->setContentsMargins(0,0,0,0);
    horiLayout->addWidget (managerWidget, 1);
    // the managerWidget will contain the real GL widget... later
    autoFocus = false;
    eventCB = nullptr;
    eventCBData = nullptr;

    // the application property MLAB_CREATE_GUI_FOR_GRAPHICSVIEW is set in MLRemotePanelRendering and MLABGraphicsView
    // when MDL is created to make sure that the rendering code can cope with being inside a graphics proxy widget,
    // where no OpenGL is available.
    if (QApplication::instance()->property("MLAB_CREATE_GUI_FOR_GRAPHICSVIEW").toBool()) {
        _useOffscreenGLWidget = true;
    } else {
        _useOffscreenGLWidget = false;
    }
}

SoQtGLWidget::~SoQtGLWidget()
{
  if (mainWidget) {
    // delete the mainWidget, because it may try to access this instance before it is deleted
    delete mainWidget;
    mainWidget = nullptr;
  }
}

//! Set the GL format. Same restrictions apply as above.
void SoQtGLWidget::setFormat (const QSurfaceFormat& format)
{
    glFormat = format;
    if (!_useOffscreenGLWidget) {
        if (mainWidget) {
            qobject_cast<SoQtRealQOpenGLWidget*>(mainWidget)->setFormat(format);
        }
    } else {
        // the offscreen gl widget needs not to be re-created.
        if (mainWidget) {
            qobject_cast<SoQtOffscreenGLWidget*>(mainWidget)->setFormat(format);
        }
    }

}

void SoQtGLWidget::replaceRenderWidget(QWidget* newWidget, QWidget* toBeDeleted)
{
    newWidget->setMinimumSize (minGLWidth, minGLHeight);
    managerWidget->layout()->addWidget (newWidget);

    // Set widget pointer was already updated before calling replaceRenderWidget()
    // before deleting the old one here, because during deletion
    // events are emitted that trigger calls to this SoQtGLWidget again, e.g.
    // initializeGL() from the resizeEvent(). The widget pointer would already
    // be invalid then, but still accessed.
    if (toBeDeleted){
        delete toBeDeleted;
    }

    if (_glCursorIsSet) {
        newWidget->setCursor (_glCursor);
    } else {
        newWidget->unsetCursor();
    }
}

void SoQtGLWidget::replaceWidget (QWidget* newWidget)
{
    QWidget* toBeDeleted = mainWidget;
    mainWidget = newWidget;
    replaceRenderWidget(newWidget, toBeDeleted);
}


//! Call this to create the real QGLWidget (and all surrounding widgets) after you
//! have set the GL format/context. This also calls createXxxxWidget().
void SoQtGLWidget::buildWidget()
{
    if (!hasRenderingWidget()) {
        QWidget* borderWidget;
        borderWidget = createLowerBorder (this);
        if (borderWidget != nullptr) {
            vertLayout->addWidget (borderWidget);
        }
        borderWidget = createUpperBorder (this);
        if (borderWidget != nullptr) {
            vertLayout->insertWidget (0, borderWidget);
        }
        borderWidget = createRightBorder (this);
        if (borderWidget != nullptr) {
            horiLayout->addWidget (borderWidget);
        }
        borderWidget = createLeftBorder (this);
        if (borderWidget != nullptr) {
            horiLayout->insertWidget (0, borderWidget);
        }

        if (_useOffscreenGLWidget) {
            replaceWidget (new SoQtOffscreenGLWidget(this, glFormat));
        } else {
            replaceWidget (new SoQtRealQOpenGLWidget(glFormat, this));
        }
    }
}

void SoQtGLWidget::setGLCursor (const QCursor& cursor)
{
    _glCursorIsSet = true;
    _glCursor = cursor;
    if (hasRenderingWidget()) {
        getRenderingWidget()->setCursor (cursor);
    }
}

void SoQtGLWidget::unsetGLCursor()
{
    _glCursorIsSet = false;
    if (hasRenderingWidget()) {
        getRenderingWidget()->unsetCursor();
    }
}

QCursor SoQtGLWidget::glCursor() const
{
    if (_glCursorIsSet) {
        return _glCursor;
    } else {
        return QCursor();
    }
}

void SoQtGLWidget::initializeGL()
{
    if (format().depthBufferSize() > 0) {
        glEnable(GL_DEPTH_TEST);
    }
}


void SoQtGLWidget::updateGL()
{
    if (SoQtRealQOpenGLWidget* w = qobject_cast<SoQtRealQOpenGLWidget*>(mainWidget)) {
        w->update();
    }
    else if (SoQtOffscreenGLWidget* w = qobject_cast<SoQtOffscreenGLWidget*>(mainWidget)) {
        w->update();
    }
}

// Set the minimum size of the real QGLWidget.
void SoQtGLWidget::setMinGLSize (int width, int height)
{
    minGLWidth  = width;
    minGLHeight = height;
    if (hasRenderingWidget()) {
        getRenderingWidget()->setMinimumSize (minGLWidth, minGLHeight);
    }
    managerWidget->setMinimumSize (minGLWidth, minGLHeight); // Why is this necessary?
}

//! return actual size of the GL widget drawing area
SbVec2s SoQtGLWidget::getGlxSize() const
{
    if (hasRenderingWidget()) {
        // QGLWidget::size calls QWidget::size which returns the size in window coordinates
        // we need to scale this size by the device pixel ratio.
        QWidget* w = getRenderingWidget();
        QSize size = w->size() * (qobject_cast<SoQtOffscreenGLWidget*>(w) ? 1.0 : w->devicePixelRatioF());
        return SbVec2s (size.width(), size.height());
    } else {
        return SbVec2s (minGLWidth, minGLHeight);
    }
}

//! return ratio between physical pixels and device-independent pixels of GL widget drawing area
double SoQtGLWidget::getGlxDevicePixelRatio()
{
    if (hasRenderingWidget()) {
      QWidget* w = getRenderingWidget();
      return qobject_cast<SoQtOffscreenGLWidget*>(w) ? 1.0 : w->devicePixelRatioF();
    }
    return 1.0;
}

void SoQtGLWidget::setEventCallback (eventCBType* cb, void* data)
{
    // event callback handled in RealGLWidget
    eventCBData = data;
    eventCB = cb;
}

//! handles events from the real QGLWidget, mostly mouse events
void SoQtGLWidget::processEvent (QEvent* /*anyEvent*/)
{
    // default does nothing
}

//@{ a set of public pass-through functions to the real GL widget:
QSurfaceFormat SoQtGLWidget::format() const
{
    if (SoQtRealQOpenGLWidget* w = qobject_cast<SoQtRealQOpenGLWidget*>(mainWidget)) {
        return w->format();
    }
    else if (SoQtOffscreenGLWidget* w = qobject_cast<SoQtOffscreenGLWidget*>(mainWidget)) {
        return w->format();
    }
    return QSurfaceFormat();
}

void SoQtGLWidget::makeCurrent()
{
    // mba: makeCurrent() uses getGLWidget(), which lazily creates the RealGLWidget,
    // doneCurrent() prevents this by checking the mainWidget pointer. Is it required
    // that the RealGLWidget is lazily created here?

    QWidget* mw = getRenderingWidget();
    if (SoQtRealQOpenGLWidget* w = qobject_cast<SoQtRealQOpenGLWidget*>(mw)) {
        w->makeCurrent();
    }
    else if (SoQtOffscreenGLWidget* w = qobject_cast<SoQtOffscreenGLWidget*>(mw)) {
        w->makeCurrent();
    }
}

void SoQtGLWidget::doneCurrent()
{
    if (SoQtRealQOpenGLWidget* w = qobject_cast<SoQtRealQOpenGLWidget*>(mainWidget)) {
        w->doneCurrent();
    }
    else if (SoQtOffscreenGLWidget* w = qobject_cast<SoQtOffscreenGLWidget*>(mainWidget)) {
        w->doneCurrent();
    }
}

bool SoQtGLWidget::doubleBuffer() const
{
    return (format().swapBehavior() == QSurfaceFormat::DoubleBuffer) || (format().swapBehavior() == QSurfaceFormat::TripleBuffer);
}

bool SoQtGLWidget::isValid() const
{
    if (SoQtRealQOpenGLWidget* w = qobject_cast<SoQtRealQOpenGLWidget*>(mainWidget)) {
        return w->isValid();
    }
    else if (SoQtOffscreenGLWidget* w = qobject_cast<SoQtOffscreenGLWidget*>(mainWidget)) {
        return w->isValid();
    }
    else {
        return false;
    }
}


void
SoQtGLWidget::setDoubleBuffer (SbBool flag)
{
    if (flag != isDoubleBuffer()) {
        QSurfaceFormat newFormat = format();
        newFormat.setSwapBehavior(flag ? QSurfaceFormat::DoubleBuffer : QSurfaceFormat::SingleBuffer);
        setFormat (newFormat);
    }
}


void
SoQtGLWidget::setStereoBuffer (SbBool flag)
{
    if (flag != isStereoBuffer()) {
        QSurfaceFormat newFormat = format();
        newFormat.setOption (QSurfaceFormat::StereoBuffers, flag);
        setFormat (newFormat);
    }
}


void
SoQtGLWidget::setColorBitDepth (int depth)
{
    if (depth != getColorBitDepth()) {
        QSurfaceFormat newFormat = format();
        newFormat.setRedBufferSize (depth);
        newFormat.setGreenBufferSize (depth);
        newFormat.setBlueBufferSize (depth);
        setFormat (newFormat);
    }
}

int
SoQtGLWidget::getColorBitDepth()
{
    QSurfaceFormat currFormat = format();
    int depth = currFormat.redBufferSize();
    if (depth > currFormat.greenBufferSize()) { depth = currFormat.greenBufferSize(); }
    if (depth > currFormat.blueBufferSize())  { depth = currFormat.blueBufferSize();  }
    return depth;
}


void
SoQtGLWidget::setBorder (int size)
{
    if (size != borderSize) {
        // set the border size and update the widgets
        borderSize = size;
        managerWidget->setLineWidth (borderSize);
        managerWidget->setFrameStyle (size > 0 ? QFrame::Sunken | QFrame::Panel
                                               : QFrame::Plain | QFrame::NoFrame);
    }
}

bool SoQtGLWidget::hasRenderingWidget() const
{
  return mainWidget != nullptr;
}

QWidget* SoQtGLWidget::getRenderingWidget() const
{
  return mainWidget;
}

QWidget* SoQtGLWidget::getRenderingWidget()
{
  if (mainWidget == nullptr) {
    buildWidget();
  }
  return mainWidget;
}

void SoQtGLWidget::setMakeCurrentCB(MakeCurrentCB cb, void* data)
{
  SoQtOffscreenGLWidget::setMakeCurrentCB(cb, data);
}

void SoQtGLWidget::setDoneCurrentCB(MakeCurrentCB cb)
{
  SoQtOffscreenGLWidget::setDoneCurrentCB(cb);
}
