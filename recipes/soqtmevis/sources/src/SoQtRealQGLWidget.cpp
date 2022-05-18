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

#include "SoQtRealQGLWidget.h"
#include "SoQtContextShareManager.h"

#include <QEvent>

SoQtRealQGLWidget::SoQtRealQGLWidget (SoQtGLWidget* parent, QGLWidget* shareWidget)
: QGLWidget (parent->managerWidget, shareWidget)
{
    _w = parent;
    setMouseTracking (true);
    setFocusPolicy(Qt::WheelFocus);
}

SoQtRealQGLWidget::SoQtRealQGLWidget (QGLContext* context, SoQtGLWidget* parent, QGLWidget* shareWidget)
: QGLWidget (context, parent->managerWidget, shareWidget)
{
    _w = parent;
    setMouseTracking (true);
    setFocusPolicy(Qt::WheelFocus);
}

SoQtRealQGLWidget::SoQtRealQGLWidget (const QGLFormat& format, SoQtGLWidget* parent, QGLWidget* shareWidget)
: QGLWidget (format, parent->managerWidget, shareWidget)
{
    _w = parent;
    setMouseTracking (true);
    setFocusPolicy(Qt::WheelFocus);
}

SoQtRealQGLWidget::~SoQtRealQGLWidget()
{
}

bool SoQtRealQGLWidget::event ( QEvent * e )
{
    if (e->type() == QEvent::Resize) {
        // Don't interfere with resize event,
        // we have a separate resizeGL callback for this!
        return QGLWidget::event(e);
    }
    bool ignoreEvent = !handleEvent(this, _w, e);
    if (ignoreEvent) { return false; }
    return e->isAccepted() || QGLWidget::event(e);
}

bool SoQtRealQGLWidget::handleEvent (QWidget* self, SoQtGLWidget* w, QEvent* e)
{
    if (e->type() == QEvent::Show) {
        w->visibilityChanged(true);
    } else if (e->type() == QEvent::Hide) {
        w->visibilityChanged(false);
    }

    // ignore mouse events when disabled
    if (!self->isEnabled()) {
      switch(e->type()) {
        case QEvent::TabletPress:
        case QEvent::TabletRelease:
        case QEvent::TabletMove:
        case QEvent::MouseButtonPress:
        case QEvent::MouseButtonRelease:
        case QEvent::MouseButtonDblClick:
        case QEvent::MouseMove:
        case QEvent::TouchBegin:
        case QEvent::TouchUpdate:
        case QEvent::TouchEnd:
        case QEvent::ContextMenu:
        case QEvent::Wheel:
          return false;
        default:
          break;
      }
    }

    // first give event to external callback:
    if (w->eventCB && w->eventCB (w->eventCBData, e)) {
        // consume event if it was handled
        e->setAccepted (true);
    } else {
        e->ignore();
        w->processEvent(e);

        // Added focus setting because of bug 2833.
        if (e->type() == QEvent::MouseButtonPress) {
          self->setFocus();
        }
    }
    return true;
}

void SoQtRealQGLWidget::enterEvent (QEvent*)
{
    if (_w->autoFocus) {
        setFocus (Qt::OtherFocusReason);
    }
}

void SoQtRealQGLWidget::leaveEvent (QEvent*)
{
    if (_w->autoFocus) {
        clearFocus();
    }
}

void SoQtRealQGLWidget::initializeGL()
{
    _w->initializeGL();
}

void SoQtRealQGLWidget::paintGL()
{
    _w->paintGL();
}

void SoQtRealQGLWidget::resizeGL (int width, int height)
{
    _w->resizeGL (width, height);
}

void SoQtRealQGLWidget::setAutoBufferSwap (bool on)
{
    QGLWidget::setAutoBufferSwap (on);
}

bool SoQtRealQGLWidget::autoBufferSwap()
{
    return QGLWidget::autoBufferSwap();
}
