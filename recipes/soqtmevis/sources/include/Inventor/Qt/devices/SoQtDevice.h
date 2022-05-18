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
 * Author(s): David Mott, Gavin Bell
 * Ported to Qt4 by MeVis (http://www.mevis.de), 2006
 */


#ifndef  _SO_QT_DEVICE_
#define  _SO_QT_DEVICE_

#include <Inventor/Qt/SoQtDLLInit.h>
#include <Inventor/SbLinear.h>
#include <Inventor/events/SoEvent.h>
#include <QWidget>
#include <QEvent>

class SoQtEventHandler;

class SOQT_MEVIS_EXPORT SoQtDevice {
  public:
    // returns typeId of this device
    virtual SoType getTypeId() const;

    // typeId of the class
    static SoType getClassTypeId() { return classTypeId; }

    // returns TRUE if device is of given type or is derived from it
    SbBool isOfType(SoType type) const;

    virtual ~SoQtDevice() {}

    // these functions will enable/disable this device for the passed widget.
    virtual void        enable(QWidget* /*widget*/, SoQtEventHandler* /*handler*/,
                               void* /*closure*/) {}
    virtual void        disable(QWidget* /*widget*/, SoQtEventHandler* /*handler*/,
                                void* /*closure*/) {}

    // this converts an X event into an SoEvent.
    // this returns NULL if the event is not from this device.
    virtual const SoEvent * translateEvent(QEvent* /*qevent*/) { return nullptr; }

    // set the window size so that the device can correctly convert X
    // window coordinates (origin at top,left) into Inventor window
    // coordinates (origin at bottom,left).
    void                setWindowSize(const SbVec2s &s) { winSize = s; }
    const SbVec2s &     getWindowSize() const           { return winSize; }

  SoEXTENDER public:
    //! Notify the device about the ratio between physical pixels and device-independent pixels of
    //! the viewer to which this device is attached. The value will be used for event translation.
    //! \ingroup HiDPIExtender
    void                setDevicePixelRatio(double scaleFactor) { devicePixelRatio = scaleFactor; }

  protected:
    SoQtDevice() : devicePixelRatio(1.0) {}
    // set the window coordinate from the passed x,y value. This will flip
    // the y value to convert from X coordinates to So coordinates.
    inline void         setEventPosition(SoEvent *event, int x, int y) const;

  SoINTERNAL public:
    // Initializes class
    static void         initClass();

  private:
    // base typeId
    static SoType       classTypeId;

    SbVec2s             winSize;    // size of the window this device works in
    double              devicePixelRatio;    // ratio between physical pixels and device-independent pixels
};

// Inline functions
inline void
SoQtDevice::setEventPosition(SoEvent *event, int x, int y) const
{
    event->setPosition(SbVec2s(x * devicePixelRatio, (winSize[1] - 1) - (y * devicePixelRatio)));
}

#endif /* _SO_QT_DEVICE_ */
