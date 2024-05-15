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

#ifndef _SO_QT_GL_WIDGET_H_
#define _SO_QT_GL_WIDGET_H_

#include <Inventor/Qt/SoQtDLLInit.h>
#include <Inventor/SoType.h>
#include <QStackedWidget>
#include <QSurfaceFormat>
#include <QImage>
#include <QPixmap>

class SoQtRealQOpenGLWidget;
class SoQtOffscreenGLWidget;
class QBoxLayout;

//////////////////////////////////////////////////////////////////////////////
//
//  Class: SoQtGLWidget
//
//
//////////////////////////////////////////////////////////////////////////////

class SOQT_MEVIS_EXPORT SoQtGLWidget : public QWidget
{
    Q_OBJECT

public:
  typedef void (*MakeCurrentCB)(void*);
  typedef void (*DoneCurrentCB)(void*);

public:
    //! Default constructor, copied from QGLWidget. The real QGLWidget is created later
    //! when buildWidget is called.
    SoQtGLWidget (QWidget* parent = nullptr, Qt::WindowFlags f = Qt::WindowFlags{});

    //! Set the GL format. Same restrictions apply as above. This will replace the real
    //! QGLWidget since QGLWidget doesn't allow this change outside the constructor.
    virtual void setFormat (const QSurfaceFormat& format);

    //! Call this to create the real QGLWidget (and all surrounding widgets) after you
    //! have set the GL format/context. This also calls createBorderWidgets().
    void buildWidget();

    //! Returns the rendering widget, either the QOpenGLWidget or the offscreen widget;
    //! automatically calls buildWidget
    QWidget* getRenderingWidget();
    //! As above, but returns NULL if buildWidget has not been called before.
    QWidget* getRenderingWidget() const;
    //! returns true if the rendering widget was already created, false otherwise
    bool hasRenderingWidget() const;

    //@{ methods for cursor management on the real GL widget
    virtual void setGLCursor (const QCursor& cursor);
    virtual void unsetGLCursor();
    virtual QCursor glCursor() const;
    //@}

    //@{ a set of public pass-through functions to the real GL widget:
    QSurfaceFormat format() const;

    void makeCurrent();
    void doneCurrent();
    bool doubleBuffer() const;
    bool isValid() const;
    //@}

    //! typedef for event callback
    typedef SbBool eventCBType (void *userData, QEvent *anyevent);

    //! Set a callback method to which events for the viewer widget are passed
    //! first. This isn't the way things in QT are usually done (e.g. you can't
    //! set more than one callback), but is used for the sake of compatibility.
    // (This lived previously in SoQtRenderArea, but it is more convenient to
    // have it here)
    void setEventCallback (eventCBType* cb, void* data);

    // set/get auto-focus behavior. If on, the widget will automatically
    // get the keyboard focus if the mouse pointer is moved over the widget
    void        setAutoFocus(SbBool flag) { autoFocus = flag; }
    SbBool      hasAutoFocus() const { return autoFocus; }

    // set color bit depth of GL context - usually this will be 8, but one
    // might try for more precision
    void        setColorBitDepth (int depth);
    int         getColorBitDepth();

    static void setMakeCurrentCB(MakeCurrentCB cb, void* data);
    static void setDoneCurrentCB(DoneCurrentCB cb);

    //! return actual size of the GL widget drawing area
    SbVec2s getGlxSize() const;

    //! return ratio between physical pixels and device-independent pixels of GL widget drawing area
    //! \ingroup HiDPIExtender
    double getGlxDevicePixelRatio();

public slots:
    void updateGL();

    //! Show/hide a border around the glx widget. This is 0 by default, but turned
    //! on by the render area. Thickness should really be determined by the current
    //! style, but to be compatible...
    void        setBorder (int size);
    int         getBorder() const            { return borderSize; }

protected:
    // destructor
    ~SoQtGLWidget() override;

    //@{ A set of virtual functions with the same meaning as in QGLWidget, calls are
    //! redirected from the real QGLWidget
    virtual void initializeGL();
    virtual void paintGL() {}
    virtual void resizeGL (int /*width*/, int /*height*/) {}
    //@}

    // to be implemented by subclasses
    virtual void visibilityChanged (bool /*flag*/) {}

    //! These methods are called to create border widgets around the GL area.
    //! Override this to create decorations in your derived class.
    virtual QWidget* createUpperBorder (QWidget* /*parent*/) { return nullptr; }
    virtual QWidget* createLowerBorder (QWidget* /*parent*/) { return nullptr; }
    virtual QWidget* createLeftBorder  (QWidget* /*parent*/) { return nullptr; }
    virtual QWidget* createRightBorder (QWidget* /*parent*/) { return nullptr; }

    //! Routine which allows to dynamically change between single and double buffering.
    //! Ported from soXtLib.
    virtual void setDoubleBuffer (SbBool onOrOff);

    //! Added for compatibility with soXtLib.
    SbBool       isDoubleBuffer()           { return doubleBuffer(); }

    //! Set the minimum size of the real QGLWidget.
    void setMinGLSize (int width, int height);

    // set/get stereo buffering visual. This routine (like setDoubleBuffer)
    // can be called interactively, although slower since a new window
    // with the needed visual is always created on the fly.
    void        setStereoBuffer (SbBool flag);
    SbBool      isStereoBuffer()  { return false; } // { return format().stereo(); }

protected:
    //! handles events from the real QGLWidget, mostly mouse events
    virtual void        processEvent (QEvent *anyEvent);

    bool        autoFocus;        //! widget gets focus on mouse enter

private:
    //! replace main GL widget with a new one, the previous one is destroyed
    void replaceWidget (QWidget* newWidget);
    //! helper function for replaceWidget()
    void replaceRenderWidget(QWidget* newWidget, QWidget* oldWidget);
    //! returns the device widget, either the QGLwidget, or the offscreen widget, automatically calls buildWidget
    SoQtOffscreenGLWidget* getOffscreenGLWidget();

    //! the horiLayout is embedded into the vertLayout
    QBoxLayout* horiLayout;
    QBoxLayout* vertLayout;
    //! the direct parent widget of the real GL widget
    QStackedWidget* managerWidget;
    //! the real GL widget
    QWidget*  mainWidget;
    //! the GL format to use
    QSurfaceFormat glFormat;

    //! currently set cursor for the GL widget
    QCursor     _glCursor;
    bool        _glCursorIsSet;

    //@{ data for external event handling
    void*        eventCBData;
    eventCBType* eventCB;
    //@}

    //--------------------------
    int         minGLWidth, minGLHeight; // requested minimum size of real QGLWidget
    int         borderSize;

    //! indicates whether the real qglwidget or the offscreen gl widget should be used.
    bool _useOffscreenGLWidget;

    friend class SoQtRealQOpenGLWidget;
    friend class SoQtOffscreenGLWidget;
};


#endif // _SO_QT_GL_WIDGET_H_

