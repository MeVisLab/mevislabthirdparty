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

#include <Inventor/Qt/SoQt.h>

#include "SoQtContextShareManager.h"
#include "SoQtRealQGLWidget.h"
#include "SoQtRealQOpenGLWidget.h"

#include <QGLFormat>
#include <QOpenGLContext>


QGLWidget* SoQtContextShareManager::_shareWidget = nullptr;


QWidget* SoQtContextShareManager::createWidget (const QGLFormat& theFormat,
    SoQtGLWidget* parent)
{
    QGLFormat format = theFormat;
//  Use these to enable core profile without deprecated functions (Experimental!)
//    format.setProfile(QGLFormat::CoreProfile);
//    format.setOption(QGL::NoDeprecatedFunctions);
    format.setProfile(QGLFormat::CompatibilityProfile);
    format.setOption(QGL::DeprecatedFunctions);

    if (SoQt::useNewOpenGLWidget()) {
        return new SoQtRealQOpenGLWidget(format, parent);
    }
    else {
        return new SoQtRealQGLWidget(format, parent, _shareWidget);
    }
}

void SoQtContextShareManager::init()
{
    if (_shareWidget == nullptr) {
        _shareWidget = new QGLWidget();
    }
    // set shared context also for new OpenGL widgets (if context sharing is enabled for these):
    QOpenGLContext* shareContext = QOpenGLContext::globalShareContext();
    if (shareContext) {
        shareContext->setShareContext(_shareWidget->context()->contextHandle());
        shareContext->create();
    }
}

