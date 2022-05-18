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

#pragma once

#include <Inventor/Qt/SoQtGLWidget.h>

#include <QGLFormat>


class QOpenGLFramebufferObject;



class SoQtOffscreenGLWidget : public QWidget
{
  Q_OBJECT
public:
  SoQtOffscreenGLWidget(SoQtGLWidget* parent, const QGLFormat& format);
  ~SoQtOffscreenGLWidget() override;

  void setFormat(const QGLFormat& format);
  QGLFormat format() const { return _format; }

  void makeCurrent();
  void doneCurrent();

  bool isValid() const;

  bool event(QEvent* event) override;

  static void setMakeCurrentCB(SoQtGLWidget::MakeCurrentCB cb, void* data);
  static void setDoneCurrentCB(SoQtGLWidget::MakeCurrentCB cb);

protected:
  void enterEvent(QEvent* event) override;
  void leaveEvent(QEvent* event) override;
  void paintEvent(QPaintEvent*) override;
  void resizeEvent(QResizeEvent* event) override;

  void createFBO(const QSize& size);

private:
  SoQtGLWidget* _w;
  QOpenGLFramebufferObject* _fbo;
  bool _isGLInitialized;
  QGLFormat _format;

  static void* _makeCurrentCBData;
  static SoQtGLWidget::MakeCurrentCB _makeCurrentCB;
  static SoQtGLWidget::DoneCurrentCB _doneCurrentCB;
};
