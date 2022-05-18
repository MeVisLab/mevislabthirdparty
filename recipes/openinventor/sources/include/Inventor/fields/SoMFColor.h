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
 * Copyright (C) 1990,91   Silicon Graphics, Inc.
 *
 _______________________________________________________________________
 ______________  S I L I C O N   G R A P H I C S   I N C .  ____________
 |
 |   $Revision: 1.1.1.1 $
 |
 |   Classes:
 |      SoMFColor
 |
 |   Author(s)          : Paul S. Strauss
 |
 ______________  S I L I C O N   G R A P H I C S   I N C .  ____________
 _______________________________________________________________________
 */

#ifndef  _SO_MF_COLOR_
#define  _SO_MF_COLOR_

#include <Inventor/fields/SoSubField.h>
#include <Inventor/SbColor.h>
#include <Inventor/fields/SoMFVec3f.h>


////////////////////////////////////////////////////////////////////////////////
//! Multiple-value field containing any number of RGB colors stored as three floats.
/*!
\class SoMFColor
\ingroup Fields
A multiple-value field that contains any number of RGB colors, stored
as instances of SbColor.  Values may be set in either RGB (red,
green, blue) or HSV (hue, saturation, value) color spaces.


SoMFColors are written to file as one or more RGB triples of
floating point numbers in standard scientific notation.  When more
than one value is present, all of the values are enclosed in square
brackets and separated by commas.  For example:
\code
[ 1.0 0.0 0.0, 0 1 0, 0 0 1 ]
\endcode
represents the three colors red, green, and blue.

\par See Also
\par
SbColor
*/
////////////////////////////////////////////////////////////////////////////////

class INVENTOR_API SoMFColor : public SoMField {
    //! Use standard field stuff
    SO_MFIELD_HEADER(SoMFColor, SbColor, const SbColor &);

  public:
    //!
    //! Additional convenience functions
    //!

    //! Set RGB/HSV values from array of arrays of 3 floats
    void                setValues(int start, int num, const float rgb[][3]);
    //! Sets \p num values starting at index \p start to the RGB (or HSV) values
    //! specified by the given array of floats.  Each float should be in the
    //! range 0.0 to 1.0, and there must be 3*\p num floats in the array.
    void                setHSVValues(int start, int num, const float hsv[][3]);

    //! Sets the field to contain one and only one value, the given color
    //! (expressed as either RGB or HSV floating point values in the range 0.0
    //! to 1.0), and deletes the second and subsequent values.
    void                setValue(const SbVec3f &vec);
    //! \see setValue(const SbVec3f &vec)
    void                setValue(float r, float g, float b);
    //! \see setValue(const SbVec3f &vec)
    void                setValue(const float rgb[3]);

    //! Set to one HSV color from 3 floats or array of 3 floats
    void                setHSVValue(float h, float s, float v);
    //! Sets the field to contain one and only one value, the given color
    //! (expressed as either RGB or HSV floating point values in the range 0.0
    //! to 1.0), and deletes the second and subsequent values.
    void                setHSVValue(const float hsv[3]);

    //! Set one of N RGB colors from SbVec3f, 3 floats, or array of 3 floats
    void                set1Value(int index, const SbVec3f &vec);
    void                set1Value(int index, float r, float g, float b);
    void                set1Value(int index, const float rgb[3]);

    //! Set1 one of N HSV colors from 3 floats or array of 3 floats
    void                set1HSVValue(int index, float h, float s, float v);
    void                set1HSVValue(int index, const float hsv[3]);

  SoINTERNAL public:
    static void         initClass();

  private:
    virtual void        writeBinaryValues(SoOutput *out) const;
    virtual bool        readBinaryValues(SoInput *in, int numToRead);
};

#endif /* _SO_MF_COLOR_ */
