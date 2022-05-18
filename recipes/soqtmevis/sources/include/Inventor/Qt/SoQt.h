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
 * Author(s): Nick Thompson, Paul Isaacs, David Mott, Gavin Bell
 *             Alain Dumesny
 * Ported to Qt4 by MeVis (http://www.mevis.de), 2006
 */


#ifndef _SO_QT_
#define _SO_QT_

#include <Inventor/Qt/SoQtDLLInit.h>
#include <Inventor/SbBasic.h>
#include <Inventor/SbTime.h>
#include <QObject>

#ifndef SOQT_MEVIS
#define SOQT_MEVIS
#endif
#define SOQT_MAJOR_VERSION 1
#define SOQT_MINOR_VERSION 1
#define SOQT_REVISION      0


class SoQtEventHandler;
class QTimer;
class QGLWidget;

class SOQT_MEVIS_EXPORT SoQt
{
public:
    // This binds Inventor with Qt so that they may work together.
    // It calls SoDB::init(), SoNodeKit::init(), SoInteraction::init()
    static void init (const char *appName = "MeVisLab", const char *className = "Inventor");

    static SoQtEventHandler* eventHandler() { return _eventHandler; }
    static bool loopDetected();

    //! Return if the new QOpenGLWidget should be used instead of the old,
    //! deprecated QGLWidget. The default is false for Windows and Linux,
    //! true for OS X (where it works better). This can be overridden by setting
    //! the environment variable MLAB_QT_OPENGL_WIDGET to either "new" or "old".
    static bool useNewOpenGLWidget();

    //! forward from SoQtContextShareManager:
    static QGLWidget* getContextSharingWidget();

private:
    static bool _initialized;
    static SoQtEventHandler*  _eventHandler;
};


// THIS CLASS SHOULD BE CONSIDERED PRIVATE
// this class ties Inventor sensors into Xt events
class SoQtEventHandler : public QObject
{
    Q_OBJECT

public:
    SoQtEventHandler();

    bool loopDetected() const;

private:
    QTimer*     qtTimer;
    SbTime      currentDeadline;

    QTimer*     qtWorkProc;

    int _zeroTimerCount;
    bool _isTriggeredByTimer;

    // Callback for changes to the sensor manager
    static void sensorManagerChangedCallback (void *data);

    void        setUpCallbacks();

signals:
    //! This is emitted if it is detected that OpenInventor is in a busy loop
    void        indicateLoop(bool detected);

private slots:
    // Callback used by the timer
    void        qtTimerCallback();

    // Callback used by the workproc
    void        qtWorkProcCallback();

};


#endif  /* _SO_QT_ */
