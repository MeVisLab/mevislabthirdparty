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

#include "SoQtOffscreenGLWidget.h"
#include "SoQtRealQOpenGLWidget.h"

#include <QOpenGLFramebufferObject>
#include <QResizeEvent>
#include <QOpenGLContext>
#include <QPainter>


void* SoQtOffscreenGLWidget::_makeCurrentCBData;
SoQtGLWidget::MakeCurrentCB SoQtOffscreenGLWidget::_makeCurrentCB;
SoQtGLWidget::DoneCurrentCB SoQtOffscreenGLWidget::_doneCurrentCB;


SoQtOffscreenGLWidget::SoQtOffscreenGLWidget(SoQtGLWidget* parent, const QSurfaceFormat& format)
  : QWidget(parent->managerWidget), _w(parent), _fbo(nullptr), _isGLInitialized(false)
{
  setFormat(format);
  setMouseTracking (true);
  setFocusPolicy(Qt::WheelFocus);
}

SoQtOffscreenGLWidget::~SoQtOffscreenGLWidget()
{
  delete _fbo;
}

void SoQtOffscreenGLWidget::setFormat(const QSurfaceFormat& format)
{
  _format = format;
  // depth and stencil is always enabled
  // QUESTION: should an error be printed, if the given format hasn't enabled them?
  _format.setDepthBufferSize(8);
  _format.setStencilBufferSize(1);
  createFBO(size());
}

void SoQtOffscreenGLWidget::makeCurrent()
{
  (*_makeCurrentCB)(_makeCurrentCBData);
  _fbo->bind();
}

void SoQtOffscreenGLWidget::doneCurrent()
{
  _fbo->release();
  (*_doneCurrentCB)(_makeCurrentCBData);
}

bool SoQtOffscreenGLWidget::isValid() const
{
  return _fbo && _fbo->isValid();
}

bool SoQtOffscreenGLWidget::event(QEvent* e)
{
  if (e->type() == QEvent::Resize) {
      // Don't interfere with resize event,
      // we have a separate resizeGL callback for this!
      return QWidget::event(e);
  }
  bool ignoreEvent = !SoQtRealQOpenGLWidget::handleEvent(this, _w, e);
  if (ignoreEvent) { return false; }
  bool result = e->isAccepted() || QWidget::event(e);
  if (e->type() == QEvent::MouseButtonPress) {
      // mouse press must be accepted, otherwise Qt::MouseMove + any button will be ignored
      e->setAccepted (true);
  }
  return result || e->isAccepted();
}

void SoQtOffscreenGLWidget::setMakeCurrentCB(SoQtGLWidget::MakeCurrentCB cb, void* data)
{
  _makeCurrentCB = cb;
  _makeCurrentCBData = data;
}

void SoQtOffscreenGLWidget::setDoneCurrentCB(SoQtGLWidget::MakeCurrentCB cb)
{
  _doneCurrentCB = cb;
}

void SoQtOffscreenGLWidget::enterEvent (QEnterEvent*)
{
  if (_w->autoFocus) {
    setFocus (Qt::OtherFocusReason);
  }
}

void SoQtOffscreenGLWidget::leaveEvent (QEvent*)
{
  if (_w->autoFocus) {
    clearFocus();
  }
}

void SoQtOffscreenGLWidget::paintEvent(QPaintEvent*)
{
  QOpenGLContext* previousContext = QOpenGLContext::currentContext();
  QSurface* previousSurface = previousContext ? previousContext->surface() : nullptr;
  makeCurrent();
  // always call initializeGL(), because we use the global GL context, which is shared by other renderers
  glPushAttrib(GL_ALL_ATTRIB_BITS);
  glPushClientAttrib(GL_CLIENT_ALL_ATTRIB_BITS);
  _w->initializeGL();
  _w->paintGL();
  glPopClientAttrib();
  glPopAttrib();

  QImage image = _fbo->toImage();
  doneCurrent();

  QPainter painter(this);
  painter.drawImage(0, 0, image);
  painter.end();
  if (previousContext && QOpenGLContext::currentContext() != previousContext) {
    previousContext->makeCurrent(previousSurface);
  }
}

void SoQtOffscreenGLWidget::resizeEvent(QResizeEvent* event)
{
  QWidget::resizeEvent(event);
  createFBO(event->size());
}

void SoQtOffscreenGLWidget::createFBO(const QSize& size)
{
  if (!_fbo || _fbo->size() != size) {
    QOpenGLContext* previousContext = QOpenGLContext::currentContext();
    QSurface* previousSurface = previousContext ? previousContext->surface() : nullptr;
    delete _fbo;
    (*_makeCurrentCB)(_makeCurrentCBData);
    _w->resizeGL(size.width(), size.height());
    if (_format.samples() > 1) {
      QOpenGLFramebufferObjectFormat format;
      format.setAttachment(QOpenGLFramebufferObject::CombinedDepthStencil);
      format.setInternalTextureFormat(GL_RGB8);
      format.setSamples(_format.samples());
      _fbo = new QOpenGLFramebufferObject(size, format);
    } else {
      _fbo = new QOpenGLFramebufferObject(size, QOpenGLFramebufferObject::CombinedDepthStencil, GL_TEXTURE_2D, GL_RGB8);
    }
    (*_doneCurrentCB)(_makeCurrentCBData);
    if (previousContext && QOpenGLContext::currentContext() != previousContext) {
      previousContext->makeCurrent(previousSurface);
    }
  }
}
