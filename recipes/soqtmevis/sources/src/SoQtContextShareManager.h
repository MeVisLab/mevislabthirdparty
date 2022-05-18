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


class QWidget;
class SoQtGLWidget;
class QGLWidget;
class QGLFormat;


//! The SoContextShareManager does automatic GL context sharing between
//! "share groups" with the same id. Since sharing isn't guaranteed to
//! succeed, the effective share id (which isn't the same as the group
//! id) - obtained by getShareID - must be compared.
class SoQtContextShareManager
{
public:
    //! Create new GL widget with given format and parent and try automatic
    //! context sharing with other widgets (created with this method)
    //! with the same shareGroup id. [Attention: Traverses linear list!]
    //! A shareGroup of -1 means no sharing.
    //!
    //! Depending on the result of useNewOpenGLWidget this returns a
    //! SoQtRealQOpenGLWidget or SoQtRealQGLWidget.
    static QWidget* createWidget(const QGLFormat& format, SoQtGLWidget* parent);

    //! Create a QGLWidget for sharing the context, and also set this context
    //! for sharing between new-style OpenGL widgets, if activated for the application.
    static void init();

    //! Return the QGLWidget to use for context sharing
    static QGLWidget* getContextSharingWidget() { return _shareWidget; }

private:
    //! internal list of widgets
    static QGLWidget* _shareWidget;
};
