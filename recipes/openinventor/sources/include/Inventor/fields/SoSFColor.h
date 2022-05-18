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
 |      SoSFColor
 |
 |   Author(s)          : Paul S. Strauss
 |
 ______________  S I L I C O N   G R A P H I C S   I N C .  ____________
 _______________________________________________________________________
 */

#ifndef  _SO_SF_COLOR_
#define  _SO_SF_COLOR_

#include <Inventor/fields/SoSubField.h>
#include <Inventor/SbColor.h>


////////////////////////////////////////////////////////////////////////////////
//! Field containing an RGB color.
/*!
\class SoSFColor
\ingroup Fields
A single-value field containing an SbColor.
Values may be set in either RGB (red,
green, blue) or HSV (hue, saturation, value) color spaces.


SoSFColors are written to file as an RGB triple of
floating point numbers in standard scientific notation, in the range
0.0 to 1.0.

\par See Also
\par
SoField, SoSField, SoMFColor, SbColor
*/
////////////////////////////////////////////////////////////////////////////////

class INVENTOR_API SoSFColor : public SoSField {

    //! Use standard field stuff
    SO_SFIELD_HEADER(SoSFColor, SbColor, const SbColor &);

  public:

    //! Convenience methods for setting the value.
    void                setValue(const SbVec3f &vec);

    //! Set RGB/HSV value from 3 floats
    void                setValue(float r, float g, float b);

    void                setHSVValue(float h, float s, float v);

    //! Convenience methods for setting the value.
    void                setValue(const float rgb[3]);

    //! Convenience methods for setting the value.
    void                setHSVValue(const float hsv[3]);

  SoINTERNAL public:
    static void         initClass();
};

#endif /* _SO_SF_COLOR_ */
