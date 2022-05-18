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
 |      SoMFRotation
 |
 |   Author(s)          : Paul S. Strauss
 |
 ______________  S I L I C O N   G R A P H I C S   I N C .  ____________
 _______________________________________________________________________
 */

#ifndef  _SO_MF_ROTATION_
#define  _SO_MF_ROTATION_

#include <Inventor/fields/SoSubField.h>
#include <Inventor/SbLinear.h>


////////////////////////////////////////////////////////////////////////////////
//! Multiple-value field containing any number of SbRotations.
/*!
\class SoMFRotation
\ingroup Fields
multiple-value field that contains any number of SbRotations.


SoMFRotations are written to file as one or more sets of four
floating point values.  Each set of 4 values is an axis of rotation
followed by the amount of right-handed rotation about that axis, in
radians.


When more than one value is present, all of the
values are enclosed in square brackets and separated by commas; for
example:
\code
[ 1 0 0 0, -.707 -.707 0 1.57 ]
\endcode

\par See Also
\par
SbRotation
*/
////////////////////////////////////////////////////////////////////////////////

class INVENTOR_API SoMFRotation : public SoMField {
    //! Use standard field stuff
    SO_MFIELD_HEADER(SoMFRotation, SbRotation, const SbRotation &);

  public:

    //! Sets \p num values starting at index \p start to the values in \p newValues.
    //! The array will be automatically be made larger to accomodate the new
    //! values, if necessary.
    void        setValues(int start, int num, const float q[][4]);

    //! Sets the \p index'th value to the given quaternion.
    void        set1Value(int index, float q0, float q1, float q2, float q3);

    //! Sets the \p index'th value to the given quaternion.
    void        set1Value(int index, const float q[4]);

    //! Sets the \p index'th value to the given axis/angle.
    void        set1Value(int index, const SbVec3f &axis, float angle);

    //! Makes this field have exactly one value, given by the quaternion.
    void        setValue(float q0, float q1, float q2, float q3);

    //! Set to one value from 4 floats in array
    void        setValue(const float q[4]);

    //! Makes this field have exactly one value, given by \p axis and \p angle.
    void        setValue(const SbVec3f &axis, float angle);

  SoINTERNAL public:
    static void         initClass();
};

#endif /* _SO_MF_ROTATION_ */
