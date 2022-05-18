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
 |      SoMFRotationd
 |
 |   Author(s)          : originally by Ronen Barzel
 |                        adapted for double values by Wolf Spindler
 |
 ______________  S I L I C O N   G R A P H I C S   I N C .  ____________
 _______________________________________________________________________
 */

#include <Inventor/fields/SoMFRotationd.h>
#include <stdlib.h>

//////////////////////////////////////////////////////////////////////////////
//
// SoMFRotationd class
//
//////////////////////////////////////////////////////////////////////////////

// Use standard definitions of all basic methods
SO_MFIELD_SOURCE_MALLOC(SoMFRotationd, SbRotationd, const SbRotationd &);

////////////////////////////////////////////////////////////////////////
//
// Description:
//    Sets values from array of arrays of 4 doubles. This can be useful
//    in some applications that have quaternions stored in this manner and
//    want to keep them that way for efficiency.
//
// Use: public

void
SoMFRotationd::setValues(int start,                 // Starting index
                         int num,                   // Number of values to set
                         const double q[][4])       // Array of quaternion values
//
////////////////////////////////////////////////////////////////////////
{
    int newNum = start + num;
    int i;

    if (newNum > getNum())
        makeRoom(newNum);

    for (i = 0; i < num; i++)
        values[start + i].setValue(q[i]);

    valueChanged();
}

////////////////////////////////////////////////////////////////////////
//
// Description:
//    Sets one quaternion value from 4 separate doubles. (Convenience function)
//
// Use: public

void
SoMFRotationd::set1Value(int index, double q0, double q1, double q2, double q3)
//
////////////////////////////////////////////////////////////////////////
{
    set1Value(index, SbRotationd(q0, q1, q2, q3));
}

////////////////////////////////////////////////////////////////////////
//
// Description:
//    Sets one quaternion value from an array of 4 doubles. (Convenience function)
//
// Use: public

void
SoMFRotationd::set1Value(int index, const double q[4])
//
////////////////////////////////////////////////////////////////////////
{
    set1Value(index, SbRotationd(q));
}

////////////////////////////////////////////////////////////////////////
//
// Description:
//    Sets one rotation value from an axis and angle. (Convenience function)
//
// Use: public

void
SoMFRotationd::set1Value(int index, const SbVec3d &axis, double angle)
//
////////////////////////////////////////////////////////////////////////
{
    set1Value(index, SbRotationd(axis, angle));
}

////////////////////////////////////////////////////////////////////////
//
// Description:
//    Sets to one quaternion value from 4 separate doubles. (Convenience function)
//
// Use: public

void
SoMFRotationd::setValue(double q0, double q1, double q2, double q3)
//
////////////////////////////////////////////////////////////////////////
{
    setValue(SbRotationd(q0, q1, q2, q3));
}

////////////////////////////////////////////////////////////////////////
//
// Description:
//    Sets to one quaternion value from an array of 4 doubles. (Convenience function)
//
// Use: public

void
SoMFRotationd::setValue(const double q[4])
//
////////////////////////////////////////////////////////////////////////
{
    setValue(SbRotationd(q));
}

////////////////////////////////////////////////////////////////////////
//
// Description:
//    Sets to one rotation value from an axis and angle. (Convenience function)
//
// Use: public

void
SoMFRotationd::setValue(const SbVec3d &axis, double angle)
//
////////////////////////////////////////////////////////////////////////
{
    setValue(SbRotationd(axis, angle));
}

////////////////////////////////////////////////////////////////////////
//
// Description:
//    Reads one (indexed) value from file. Returns FALSE on error.
//
// Use: private

bool
SoMFRotationd::read1Value(SoInput *in, int index)
//
////////////////////////////////////////////////////////////////////////
{
    SbVec3d     axis;
    double      angle;

    if (! (in->read(axis[0]) &&
           in->read(axis[1]) &&
           in->read(axis[2]) &&
           in->read(angle)))
        return FALSE;

    set1Value(index, axis, angle);

    return TRUE;
}

////////////////////////////////////////////////////////////////////////
//
// Description:
//    Writes one (indexed) value to file.
//
// Use: private

void
SoMFRotationd::write1Value(SoOutput *out, int index) const
//
////////////////////////////////////////////////////////////////////////
{
    SbVec3d     axis;
    double      angle;

    values[index].getValue(axis, angle);

    out->write(axis[0]);

    if (! out->isBinary())
        out->write(' ');

    out->write(axis[1]);

    if (! out->isBinary())
        out->write(' ');

    out->write(axis[2]);

    if (! out->isBinary()) {
        out->write(' ');
        out->write(' ');
    }

    out->write(angle);
}
