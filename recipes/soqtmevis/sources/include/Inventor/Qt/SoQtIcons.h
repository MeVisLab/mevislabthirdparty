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
 * Author(s): Alain Dumesny
 * Ported to Qt4 by MeVis (http://www.mevis.de), 2006
 */

#ifndef  _SO_QT_ICON_
#define  _SO_QT_ICON_

#include <Inventor/Qt/SoQtDLLInit.h>
#include <QIcon>
#include <QCursor>

class SOQT_MEVIS_EXPORT SoQtIcons
{
public:

    enum IconNum {
        ICON_PICK,
        ICON_VIEW,
        ICON_HELP,
        ICON_HOME,
        ICON_SET_HOME,
        ICON_VIEW_ALL,
        ICON_SEEK,
        ICON_ORTHO,
        ICON_PERSP,
        ICON_X,
        ICON_Y,
        ICON_Z,
        ICON_COUNT
    };

    enum CursorNum {
        CURSOR_VIEWING,
        CURSOR_CURVED_HAND,
        CURSOR_FLAT_HAND,
        CURSOR_POINTING_HAND,
        CURSOR_ROLL,
        CURSOR_TARGET,
        CURSOR_NORMAL_VEC,
        CURSOR_WALK,
        CURSOR_PAN,
        CURSOR_TILT,
        CURSOR_COUNT
    };

    static QIcon getIcon (int number);

    static QCursor getCursor (int number);
};

#endif /* _SO_QT_ICON_ */
