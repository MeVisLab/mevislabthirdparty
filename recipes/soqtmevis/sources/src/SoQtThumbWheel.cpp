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

#include <Inventor/Qt/SoQtThumbWheel.h>
#include <QFocusEvent>
#include <QKeyEvent>
#include <QMouseEvent>
#include <QPaintEvent>
#include <QResizeEvent>
#include <QStyle>
#include <QStyleOption>
#include <QStylePainter>
#include <cmath>
#include <cstdio>
#include <qdrawutil.h>

#define VIEWABLE_ANGLE 150
#define WHEEL_LONG_DIMENSION 122
#define WHEEL_NARROW_DIMENSION 16
#define BUTTON_SIZE 16
#define FOCUS_WIDTH 2
#define SHADOW_WIDTH 2
#define PHASE_MASK (PHASE_COUNT-1)
#define PI 3.1415927
#define HALFOFFSET

SoQtThumbWheel::SoQtThumbWheel (Qt::Orientation orientation,
    QWidget* parent, Qt::WindowFlags f)
: QWidget (parent, f)
, _orientation (orientation)
, _animate(true)
, _infinite(true)
, _wrapsAround(false)
, _showHomeButton(false)
, _lowerBound(0)
, _upperBound(0)
, _homePosition(0)
, _angleFactor(360)
, _value(0)
, _pixelsToUserUnitsFactor(1.0)

, _homeButtonPressed(false)
, _dragging(false)
, _wheelHighlighted(false)
, _buttonHighlighted(false)
, _startDragValue(0)
, _startWheelPhase(0)
, _wheelPhase(0)
, _red(0)   // denotes unset color
, _green(0) // denotes unset color
, _blue(0)  // denotes unset color
{
    int focus  = FOCUS_WIDTH;
    int shadow = SHADOW_WIDTH;
    bool horiz = (orientation == Qt::Horizontal);

    /* Private state - where the wheel and button will be drawn. */
    _wheelX = focus + shadow;
    _wheelY = focus + shadow;
    _buttonX = _wheelX + (horiz ? WHEEL_LONG_DIMENSION : 0) + 2*shadow;
    _buttonY = _wheelY + (horiz ? 0 : WHEEL_LONG_DIMENSION) + 2*shadow;

    sanitizeValues();

    setFocusPolicy (Qt::TabFocus);
    setMouseTracking (true);
}

SoQtThumbWheel::~SoQtThumbWheel()
{
}

void SoQtThumbWheel::setRange (double lower, double upper, bool wrapsAround)
{
    _upperBound = upper;
    _lowerBound = lower;
    _wrapsAround = wrapsAround;
    sanitizeValues();
}

void SoQtThumbWheel::unsetRange ()
{
    _upperBound = _lowerBound = 0;
    sanitizeValues();
}

void SoQtThumbWheel::setHomePosition (double home)
{
    _homePosition = home;
    sanitizeValues();
}

void SoQtThumbWheel::setAngleFactor (double factor)
{
    _angleFactor = factor;
    sanitizeValues();
}

void SoQtThumbWheel::setValue (double value, bool turnWheel)
{
    _value = value;
    sanitizeValues(turnWheel);
}

void SoQtThumbWheel::setAnimated (bool animate)
{
    _animate = animate;
}

void SoQtThumbWheel::showHomeButton (bool show)
{
    _showHomeButton = show;
    updateGeometry();
}

void SoQtThumbWheel::setWheelColor (const QColor& color)
{
    _red = color.red();
    _green = color.green();
    _blue = color.blue();
    // invalidate old pixmaps
    for (int i=0;i<PHASE_COUNT;i++) {
        _pix[i].detach();
        _pixHi[i].detach();
    }
    // force update (in case widget is already visible)
    update();
}


void SoQtThumbWheel::sanitizeValues(bool turnWheel)
{
    _infinite = false;

    // check value range:
    if (_lowerBound > _upperBound) {
        double tmp = _lowerBound;
        _lowerBound = _upperBound;
        _upperBound = tmp;
    } else if (_upperBound == _lowerBound) {
        _infinite = true;
    }

    if (!_infinite) {
        // Range checking of values
        if (_value < _lowerBound) {
            _value = _lowerBound;
        }
        if (_value > _upperBound) {
            _value = _upperBound;
        }
        if (_homePosition < _lowerBound) {
            _homePosition = _lowerBound;
        }
        if (_homePosition > _upperBound) {
            _homePosition = _upperBound;
        }
    }
    // calculate factor for turning pixels into user units
    _pixelsToUserUnitsFactor =
        ((double)VIEWABLE_ANGLE /(double)WHEEL_LONG_DIMENSION) *
        (_angleFactor / 360.0);
    if (turnWheel) {
        // animate is usually set from a setValue call - subsequent calls to setValue
        // should produce a smooth update behavior for the thumbwheel
        _wheelPhase = (_startWheelPhase +
                       convertUserUnitsToPixels(_value - _startDragValue)) & PHASE_MASK;
        update();
    } else {
        // if the value update is not animated, we take the current value
        // to make future changes relativ to the current position of the wheel
        _startDragValue = _value;
        _startWheelPhase = _wheelPhase;
    }
}

QSize SoQtThumbWheel::sizeHint() const
{
    int focus  = FOCUS_WIDTH;
    int shadow = SHADOW_WIDTH;
    bool horiz = (_orientation == Qt::Horizontal);

    // Set up geometry
    int width  = (horiz ? WHEEL_LONG_DIMENSION : WHEEL_NARROW_DIMENSION)
                 + 2 * (focus + shadow);
    int height = (horiz ? WHEEL_NARROW_DIMENSION : WHEEL_LONG_DIMENSION)
                 + 2 * (focus + shadow);
    if (_showHomeButton) {
        if (horiz) {
            width += BUTTON_SIZE + 2 * shadow;
        } else {
            height += BUTTON_SIZE + 2 * shadow;
        }
    }
    return QSize (width, height);
}

void SoQtThumbWheel::paintEvent (QPaintEvent* pe)
{
    int focus  = FOCUS_WIDTH;
    int shadow = SHADOW_WIDTH;
    bool horiz = (_orientation == Qt::Horizontal);

    // calculate wheel size
    int width  = horiz ? WHEEL_LONG_DIMENSION : WHEEL_NARROW_DIMENSION;
    int height = horiz ? WHEEL_NARROW_DIMENSION : WHEEL_LONG_DIMENSION;

    // check wheel position again (might be unnecessary)
    if (_wheelX < focus + shadow) {
        _wheelX = focus + shadow;
    }
    if (_wheelY < focus + shadow) {
        _wheelY = focus + shadow;
    }

    // check button position again (might be unnecessary)
    if (_buttonX < _wheelX + (horiz ? WHEEL_LONG_DIMENSION + 2 * shadow : 0)) {
        _buttonX = _wheelX + (horiz ? WHEEL_LONG_DIMENSION + 2 * shadow : 0);
    }
    if (_buttonX < _wheelY + (horiz ? 0 : WHEEL_LONG_DIMENSION + 2 * shadow)) {
        _buttonY = _wheelY + (horiz ? 0 : WHEEL_LONG_DIMENSION + 2 * shadow);
    }


    if (_pix[0].isNull()) {
        createAndRenderPixmaps();
    }

    QStylePainter paint (this);
    // draw shadow around wheel
    qDrawShadeRect (&paint, _wheelX-shadow, _wheelY-shadow,
                            width+2*shadow, height+2*shadow, palette(), true, 1, 1);
    // draw wheel
    if (_wheelHighlighted) {
        paint.drawPixmap (_wheelX, _wheelY, _pixHi[_wheelPhase & PHASE_MASK]);
    } else {
        paint.drawPixmap (_wheelX, _wheelY, _pix[_wheelPhase & PHASE_MASK]);
    }

    if (_showHomeButton) {
        // draw home button with current style
        QStyleOptionButton option;
        option.initFrom (this);
        option.features = QStyleOptionButton::None;
        option.rect = QRect (_buttonX, _buttonY, BUTTON_SIZE, BUTTON_SIZE);
        option.state = QStyle::State_Enabled |
                       (_homeButtonPressed ? QStyle::State_Sunken : QStyle::State_Raised) |
                       (_buttonHighlighted ? QStyle::State_MouseOver : QStyle::State_None);
        paint.drawControl (QStyle::CE_PushButton, option);

    }

    if (hasFocus()) {
        // draw focus rect with current style
        QStyleOptionFocusRect option;
        option.initFrom (this);
        option.rect = QRect (QPoint (0,0), minimumSizeHint());
        // draw focus border
        paint.drawPrimitive (QStyle::PE_FrameFocusRect, option);
    }
    pe->accept();
}

void SoQtThumbWheel::resizeEvent (QResizeEvent* pe)
{
    int focus  = FOCUS_WIDTH;
    int shadow = SHADOW_WIDTH;

    // if this widget is bigger than needed, center the wheel+button
    QSize minSize = minimumSizeHint();
    if (minSize.width() < pe->size().width()) {
        _wheelX = focus + shadow;
    } else {
        _wheelX = focus + shadow + (pe->size().width() - minSize.width()) / 2;
    }
    if (minSize.height() < pe->size().height()) {
        _wheelY = focus + shadow;
    } else {
        _wheelY = focus + shadow + (pe->size().height() - minSize.height()) / 2;
    }
    bool horiz = (_orientation == Qt::Horizontal);
    _buttonX = _wheelX + (horiz ? WHEEL_LONG_DIMENSION + 2*shadow: 0);
    _buttonY = _wheelY + (horiz ? 0 : WHEEL_LONG_DIMENSION + 2*shadow);
    pe->accept();
}

void SoQtThumbWheel::focusInEvent (QFocusEvent* fe)
{
    update();
    fe->accept();
}

void SoQtThumbWheel::focusOutEvent (QFocusEvent* fe)
{
    update();
    fe->accept();
}

void SoQtThumbWheel::keyPressEvent (QKeyEvent* ke)
{
    // this widget should handle key presses and focus
    switch (ke->key()) {
    case Qt::Key_Left:
    case Qt::Key_Up:
        turnDelta (-15); // turn by -15°
        ke->accept();
        break;
    case Qt::Key_Right:
    case Qt::Key_Down:
        turnDelta (15); // turn by 15°
        ke->accept();
        break;
    case Qt::Key_Home:
        if (_value != _homePosition) {
            _value = _homePosition;
            emit valueChanged (_value);
        }
        ke->accept();
        break;
    default:
        ke->ignore();
    }
}


void SoQtThumbWheel::mousePressEvent (QMouseEvent* me)
{
    if (me->button() == Qt::LeftButton) {
        if (inWheel (me)) {
            // Save this mouse position for later drag calculations
            bool horiz = (_orientation == Qt::Horizontal);
            _startMousePosition = horiz ? me->x() : me->y();
            // remember the value at the start of the dragging
            _startDragValue = _value;
            _startWheelPhase = _wheelPhase;
            // Button down in the wheel area starts a drag
            _dragging = true;
            // announce that a drag is started
            emit dragStart (_value);
        } else if (inHomeButton (me)) {
            _homeButtonPressed = true;
            update();
        }
        me->accept();
    }
}

void SoQtThumbWheel::mouseReleaseEvent (QMouseEvent* me)
{
    if (me->button() == Qt::LeftButton) {
        // update highlighting status
        _wheelHighlighted = inWheel (me);
        _buttonHighlighted = inHomeButton (me);
        if (_dragging) {
            _dragging = false;
            if (!_animate && _value != _startDragValue) {
                // notify user of value change since he wasn't during the drag
                emit valueChanged (_value);
            }
            // announce that a drag has ended
            emit dragStop (_value);
            update();
        } else if (_homeButtonPressed) {
            updateValueInternal (_homePosition);
            _homeButtonPressed = false;
            update();
        }
        me->accept();
    }
}

void SoQtThumbWheel::mouseMoveEvent (QMouseEvent* me)
{
    if (_dragging) {
        bool horiz = (_orientation == Qt::Horizontal);
        int new_pos = horiz ? me->x() : me->y();

        // find new value, always start from drag point so rounding errors
        // are not accumulated:
        double newValue = _startDragValue +
            convertPixelsToUserUnits (new_pos - _startMousePosition);
        // try to set new value:
        updateValueInternal (newValue, false);
        me->accept();
    } else {
        // update highlighting status
        if (inWheel (me)) {
            if (!_wheelHighlighted || _buttonHighlighted) {
                _wheelHighlighted = true;
                _buttonHighlighted = false;
                update();
            }
        } else if (inHomeButton (me)) {
            if (_wheelHighlighted || !_buttonHighlighted) {
                _wheelHighlighted = false;
                _buttonHighlighted = true;
                update();
            }
        } else {
            if (_wheelHighlighted || _buttonHighlighted) {
                _wheelHighlighted = false;
                _buttonHighlighted = false;
                update();
            }
        }
    }
}

void SoQtThumbWheel::wheelEvent (QWheelEvent* we)
{
    // using the mouse wheel should be possible...
    // documentation of QT 4.1.3 is a little bit unclear which delta we
    // get for which angle, but lets try this...
    turnDelta (we->angleDelta().y()/8.0);
    we->accept();
}


void SoQtThumbWheel::leaveEvent (QEvent* e)
{
    if (_dragging || (!_wheelHighlighted && !_buttonHighlighted)) { return; }
    _wheelHighlighted = false;
    _buttonHighlighted = false;
    update();
    e->accept();
}

void SoQtThumbWheel::turnDelta (double delta)
{
    double new_value = _value + (delta*_angleFactor)/360.0;
    updateValueInternal (new_value);
}

void SoQtThumbWheel::updateValueInternal (double newValue, bool final)
{
    // restrict new value to range (if not infinite):
    if (!_infinite) {
        if (_wrapsAround) {
            if (newValue < _lowerBound || newValue >= _upperBound) {
                double range = _upperBound - _lowerBound;
                if (range != 0) {
                    newValue -= floor((newValue - _lowerBound)/range)*range;
                } else {
                    // range is zero, prevent division by zero
                    newValue = _lowerBound;
                }
                // on wrap-around the display will probably jerk a little bit,
                // since we calculate the wheel position from the represented value...
            }
        } else if (newValue < _lowerBound) {
            newValue = _lowerBound;
        } else if (newValue > _upperBound) {
            newValue = _upperBound;
        }
    }
    if (newValue != _value) {
        // Change the current pixmap to reflect "spinning" the wheel.
        // We convert the value change back to pixels to show the correct motion:
        if (_dragging) {
            // When dragging we take the starting phase as reference, so we don't
            // accumulate rounding errors
            _wheelPhase = (_startWheelPhase +
                           convertUserUnitsToPixels (newValue - _startDragValue)) & PHASE_MASK;
        } else {
            _wheelPhase = (_wheelPhase +
                           convertUserUnitsToPixels (newValue - _value)) & PHASE_MASK;
        }
        _value = newValue;
        update();
        if (final || _animate) {
            emit valueChanged (_value);
        }
    }
}


bool SoQtThumbWheel::inWheel (QMouseEvent* me) const
{
    bool horiz = (_orientation == Qt::Horizontal);
    return (me->x() >= _wheelX) && (me->y() >= _wheelY) &&
           (me->x() < _wheelX + (horiz ? WHEEL_LONG_DIMENSION : WHEEL_NARROW_DIMENSION)) &&
           (me->y() < _wheelY + (horiz ? WHEEL_NARROW_DIMENSION : WHEEL_LONG_DIMENSION));
}

bool SoQtThumbWheel::inHomeButton (QMouseEvent* me) const
{
    return _showHomeButton &&
           (me->x() >= _buttonX) && (me->y() >= _buttonY) &&
           (me->x() < _buttonX + BUTTON_SIZE) &&
           (me->y() < _buttonY + BUTTON_SIZE);
}


/* Private functions */

double SoQtThumbWheel::convertPixelsToUserUnits (int pixels) const
{
    return ((double)pixels * _pixelsToUserUnitsFactor);
}

int SoQtThumbWheel::convertUserUnitsToPixels (double units) const
{
    double v = units / _pixelsToUserUnitsFactor;
    return (int)((v > 0) ? (v + 0.5) : (v - 0.5));
}


void SoQtThumbWheel::createAndRenderPixmaps()
{
    if (_red == 0 && _green == 0 && _blue == 0) {
        // take color from palette:
        QColor wheelColor = palette().color(QPalette::Light);
        if (wheelColor.value() < 64) {
          // if the color is too dark, use some mid dark grey (inverse display wouldn't be sensible)
          wheelColor = QColor(64, 64, 64);
        }
        _red = wheelColor.red();
        _green = wheelColor.green();
        _blue = wheelColor.blue();
    }
    bool horiz = (_orientation == Qt::Horizontal);
    int width  = (horiz ? WHEEL_LONG_DIMENSION : WHEEL_NARROW_DIMENSION);
    int height = (horiz ? WHEEL_NARROW_DIMENSION : WHEEL_LONG_DIMENSION);
    for (int i=0;i<PHASE_COUNT;i++) {
        _pix[i] = QPixmap (width, height);
        renderPixmap (&_pix[i], i, false);
        _pixHi[i] = QPixmap (width, height);
        renderPixmap (&_pixHi[i], i, true);
    }
}

inline static void wheelDrawLine (QPainter& paint, bool horiz,
                                  const QColor& color, int x1, int y1, int x2, int y2)
{
    paint.setPen (color);
    if (horiz) {
        paint.drawLine (y1, x1, y2, x2);
    } else {
        paint.drawLine (x1, y1, x2, y2);
    }
}

inline static void wheelDrawPoint (QPainter& paint, bool horiz,
                                   QColor& color, int x, int y)
{
    paint.setPen (color);
    if (horiz) {
        paint.drawPoint (y, x);
    } else {
        paint.drawPoint (x, y);
    }
}

QColor SoQtThumbWheel::getWheelColor (int greyValue)
{
    return QColor (greyValue*_red/255, greyValue*_green/255, greyValue*_blue/255);
}

void SoQtThumbWheel::renderPixmap (QPixmap* pixmap, int phase, bool hilited)
{
    QColor darkestColor   (0, 0, 0);
    QColor veryDarkColor  (42, 42, 42);
    QColor darkColor      = getWheelColor (85);
    int off = (phase % PHASE_COUNT) - 3;

    bool horiz = (_orientation == Qt::Horizontal);

    QPainter paint (pixmap);
    // The macro wheelDrawLine takes arguments similar to what we would use
    // for XDrawLine if the wheel were vertical.  If the wheel is horizontal,
    // the macro flips the arguments.
    int a = 0;
    int b = WHEEL_NARROW_DIMENSION-1;
    int start = 0;
    int end = WHEEL_LONG_DIMENSION;
    int visRadius = (end-start)/2;
    int mid = start+visRadius;
    int bg = (hilited ? 128 : 96);
    double radius = visRadius/cos ((180.0-VIEWABLE_ANGLE)/360.0*PI);
    double angleStep = tan (8.0/radius);
    // lines to either side of wheel
    wheelDrawLine (paint, horiz, veryDarkColor, a, start, a, end-1);
    wheelDrawLine (paint, horiz, darkestColor,  b, start, b, end-1);
    a++;
    b--;
    // shaded lines to left and right of wheel
    for (int i=start;i<end;i++) {
        double co = cos (((double)(i-mid))/radius*PI*0.5);
        int c=(int)(255.9 * co);
        QColor color = getWheelColor (c);
        wheelDrawPoint (paint, horiz, color, a, i);
        wheelDrawPoint (paint, horiz, color, b, i);
        c = bg + (int)(63.9 * co);
        wheelDrawLine (paint, horiz, getWheelColor (c), a+1, i, b-1, i);
    }

    // lines across wheel
    a++;
    b--;

    int x = mid+off;
    while (x < end) {
        double angle = asin ((x-mid)/radius);
        double width = cos (angle)*2.0;
        double co = cos (((double)(x-mid))/radius*PI*0.5);
        wheelDrawLine (paint, horiz, darkColor,     a, x-1, b, x-1);
        int c;
        if (width >= 1.0) {
            c=(int)(255.9 * co);
        } else {
            c=(int)((255.9 * co * (width)) +
                    (bg + (63.9 * co)) * (1.0-width));
        }
        wheelDrawLine (paint, horiz, getWheelColor (c), a, x, b, x);
        if (width > 1.0) {
            if (width >= 2.0) {
                c=(int)(255.9 * co);
            } else {
                c=(int)((255.9 * co * (width-1.0)) +
                        (bg + (63.9 * co)) * (2.0-width));
            }
            wheelDrawLine (paint, horiz, getWheelColor (c), a, x+1, b, x+1);
        }
        int x2 = (int) (sin (angle+angleStep) * radius + 0.5) + mid;
        if (x2 == x) break;
        x = x2;
    }
    x = mid+off-8;
    while (x > start) {
        double angle = asin ((x-mid)/radius);
        double width = cos (angle)*2.0;
        double co = cos (((double)(x-mid))/radius*PI*0.5);
        wheelDrawLine (paint, horiz, darkColor,     a, x-1, b, x-1);
        int c;
        if (width >= 1.0) {
            c=(int)(255.9 * co);
        } else {
            c=(int)((255.9 * co * (width)) +
                    (bg + (63.9 * co)) * (1.0-width));
        }
        wheelDrawLine (paint, horiz, getWheelColor (c), a, x, b, x);
        if (width > 1.0) {
            if (width >= 2.0) {
                c=(int)(255.9 * co);
            } else {
                c=(int)((255.9 * co * (width-1.0)) +
                        (bg + (63.9 * co)) * (2.0-width));
            }
            wheelDrawLine (paint, horiz, getWheelColor (c), a, x+1, b, x+1);
        }
        int x2 = (int) (sin (angle-angleStep) * radius - 0.5) + mid;
        if (x2 == x) break;
        x = x2;
    }
    a--;
    b++;
    wheelDrawLine (paint, horiz, veryDarkColor, a, start, b, start);
    wheelDrawLine (paint, horiz, darkestColor,  a, end-1, b, end-1);
}
