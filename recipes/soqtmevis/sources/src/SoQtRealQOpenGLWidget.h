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

#include <QOpenGLWidget>
#include <QSurfaceFormat>


class SoQtRealQOpenGLWidget : public QOpenGLWidget
{
    Q_OBJECT
    friend class SoQtGLWidget;
    friend class SoQtContextShareManager;

public:
    SoQtRealQOpenGLWidget(const QSurfaceFormat& format, SoQtGLWidget* parent);

    ~SoQtRealQOpenGLWidget() override;

    bool event(QEvent* event) override;

    static bool handleEvent(QWidget* self, SoQtGLWidget* w, QEvent* event);

    void enterEvent (QEnterEvent* event) override;
    void leaveEvent (QEvent* event) override;

    void initializeGL() override;
    void paintGL() override;
    void resizeGL(int width, int height) override;

    //! to avoid redraws on focusIn and focusOut, these methods do nothing
    void focusInEvent (QFocusEvent*) override {}
    void focusOutEvent (QFocusEvent*) override {}

private:
    SoQtGLWidget* _w;
};
