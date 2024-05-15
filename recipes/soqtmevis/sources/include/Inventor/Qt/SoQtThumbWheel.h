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
 * Ported to Qt4 by MeVis (http://www.mevis.de), 2006
 */

/*
 * SoQtThumbWheel.c : Thumbwheel ("infinite scrollbar") widget.
 */

#include <Inventor/Qt/SoQtDLLInit.h>
#include <QWidget>
#include <QPixmap>
#include <QColor>

#define PHASE_COUNT 8

class SOQT_MEVIS_EXPORT SoQtThumbWheel : public QWidget
{
    Q_OBJECT

public:
    //! default constructor, main argument is the orientation of the wheel
    SoQtThumbWheel (Qt::Orientation orientation = Qt::Horizontal,
                    QWidget* parent = nullptr, Qt::WindowFlags f = Qt::WindowFlags{});
    ~SoQtThumbWheel() override;

    //! the SoQtThumbWheel widget has a fixed size
    QSize sizeHint() const override;
    virtual QSize maximumSizeHint() const { return sizeHint(); }
    QSize minimumSizeHint() const override { return sizeHint(); }

public slots:
    //! returns the orientation of this widget
    Qt::Orientation orientation() const { return _orientation; }

    //! returns if this SoQtThumbWheel has no upper and lower bounds
    bool infinite()        const { return _infinite; }

    //! returns the lower bound of the value range (if not infinite range)
    double lowerBound()       const { return _lowerBound; }

    //! returns the upper bound of the value range (if not infinite range)
    double upperBound()       const { return _upperBound; }

    //! return if the value wraps around at the range boundaries
    bool wrapsAround()        const { return _wrapsAround; }

    //! the home position (the value that is set by the home button)
    double homePosition()     const { return _homePosition; }

    //! The angle factor is a scaling factor between perceived rotation
    //! and effective values. Default is 360.
    double angleFactor()      const { return _angleFactor; }

    //! Current value of the SoQtThumbWheel
    double value()            const { return _value; }

    //! Returns true if valueChanged signals are emitted during a mouse drag
    //! (otherwise one signal is emitted when the mouse is released)
    bool isAnimated()      const { return _animate; }

    //! Returns true if a small home button is shown beside the wheel
    bool showsHomeButton() const { return _showHomeButton; }

    //! Set a value range for this SoQtThumbWheel. Current value and
    //! home position are automatically forced into this range.
    //! If wrapsAround is set, the value automatically wraps around
    //! if the wheel is dragged.
    void setRange        (double lower, double upper, bool wrapsAround = false);

    //! Remove value range, possible values are now unrestricted
    void unsetRange      ();

    //! Set value which is set when the "home" button is pressed
    void setHomePosition (double home);

    //! set scaling factor for SoQtThumbWheel rotation (see angleFactor)
    void setAngleFactor  (double factor);

    //! set current value of SoQtThumbWheel; if turnWheel is set, the wheel
    //! is animated (moves to the new position)
    void setValue        (double value, bool turnWheel = false);

    //! set if valueChanged signals are emitted during mouse drags
    void setAnimated     (bool animated);

    //! set if a small home button is shown beside the wheel
    void showHomeButton  (bool show = true);

    //! set base color of the wheel - at least one component should have a high value -
    //! or set to black to restore to default value according to palette of widget
    void setWheelColor (const QColor& color);

signals:
    //! this signal is emitted when the current value of this widget changes
    void valueChanged (double value);

    //! this signal is emitted at the start of a mouse drag
    void dragStart (double value);

    //! this signal is emitted at the end of a mouse drag, additional to any
    //! valueChanged you might have get
    void dragStop (double value);

protected:
    //! Check if the current range is infinite and restrict current value
    //! and home position if necessary. If turnWheel is set, the wheel
    //! is animated (moved to new position), if not, the current value is
    //! set as new starting value for animations.
    virtual void sanitizeValues(bool turnWheel = false);

    //@{ event handling for this widget
    void paintEvent (QPaintEvent* pe) override;
    void resizeEvent (QResizeEvent* re) override;
    void focusInEvent (QFocusEvent* fe) override;
    void focusOutEvent (QFocusEvent* fe) override;
    void keyPressEvent (QKeyEvent* ke) override;
    void mousePressEvent (QMouseEvent* me) override;
    void mouseReleaseEvent (QMouseEvent* me) override;
    void mouseMoveEvent (QMouseEvent* me) override;
    void wheelEvent (QWheelEvent* we) override;
    void leaveEvent (QEvent* me) override;
    //@}

    //! turn thumb wheel by a certain angle (e.g. in reaction to mouse wheel)
    void turnDelta (double delta);

    //! returns true if mouse is in wheel area
    virtual bool inWheel (QMouseEvent* me) const;

    //! returns true if mouse is in home button area
    virtual bool inHomeButton (QMouseEvent* me) const;

    //! create the pre-rendered wheel pixmaps
    void createAndRenderPixmaps();

    //! render a wheel at a certain phase into the pixmap
    virtual void renderPixmap (QPixmap* pixmap, int phase, bool hilited);

    //! get a drawing color for the wheel from a given grey value
    //! (might be used to produced colored wheels by multiplying with a RGB value)
    virtual QColor getWheelColor (int greyValue);

    //! turn a pixel difference into a value difference
    double convertPixelsToUserUnits (int pixels) const;

    //! turn a value difference into a pixel difference
    int convertUserUnitsToPixels (double units) const;

    //! set a new current value, clipped to the the value range (if not infinite),
    //! then update the wheel image and emit a valueChanged signal if final is
    //! true or animate is set to true
    void updateValueInternal (double newValue, bool final = true);

private:
    Qt::Orientation _orientation;
    bool _animate;                     //! emit valueChanged signal while dragging
    bool _infinite;                    //! unrestricted value range
    bool _wrapsAround;                 //! if not _infinite, wrap around at range bounds
    bool _showHomeButton;
    double _lowerBound;
    double _upperBound;
    double _homePosition;
    double _angleFactor;               //! scaling factor
    double _value;
    double _pixelsToUserUnitsFactor;   //! internal scaling factor, depends on _angleFactor

    int _wheelX;                       //! horizontal position of wheel
    int _wheelY;                       //! vertical position of wheel
    int _buttonX;                      //! horizontal position of home button
    int _buttonY;                      //! vertical position of home button
    bool _homeButtonPressed;           //! home button is currently pressed down
    bool _dragging;                    //! wheel is currently dragged with mouse
    bool _wheelHighlighted;            //! mouse is over wheel
    bool _buttonHighlighted;           //! mouse is over home button
    int _startMousePosition;           //! horizontal/vertical position of mouse at drag start
    double _startDragValue;            //! current value at drag start
    int _startWheelPhase;              //! phase the wheel was in at drag start
    int _wheelPhase;                   //! current visible wheel phase (0<=phase<PHASE_COUNT)

    int _red, _green, _blue;           //! base color of wheel
    QPixmap _pix   [PHASE_COUNT];      //! pre-rendered wheel images
    QPixmap _pixHi [PHASE_COUNT];      //! pre-rendered wheel images of highlighted wheel
};
