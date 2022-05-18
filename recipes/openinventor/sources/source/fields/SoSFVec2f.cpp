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
 |      SoSFVec2f
 |
 |   Author(s)          : Paul S. Strauss
 |
 ______________  S I L I C O N   G R A P H I C S   I N C .  ____________
 _______________________________________________________________________
 */

#include <Inventor/fields/SoSFVec2f.h>

//////////////////////////////////////////////////////////////////////////////
//
// SoSFVec2f class
//
//////////////////////////////////////////////////////////////////////////////

// Use standard definitions of all basic methods
SO_SFIELD_SOURCE(SoSFVec2f, SbVec2f, const SbVec2f &);

////////////////////////////////////////////////////////////////////////
//
// Description:
//    Sets value from 2 separate floats. (Convenience function)
//
// Use: public

void
SoSFVec2f::setValue(float x, float y)   // The 2 floats
//
////////////////////////////////////////////////////////////////////////
{
    setValue(SbVec2f(x, y));
}

////////////////////////////////////////////////////////////////////////
//
// Description:
//    Sets value from array of 2 floats. (Convenience function)
//
// Use: public

void
SoSFVec2f::setValue(const float xy[2])          // Array of values
//
////////////////////////////////////////////////////////////////////////
{
    setValue(SbVec2f(xy));
}

////////////////////////////////////////////////////////////////////////
//
// Description:
//    Reads value from file. Returns FALSE on error.
//
// Use: private

bool
SoSFVec2f::readValue(SoInput *in)
//
////////////////////////////////////////////////////////////////////////
{
    return (in->read(value[0]) &&
            in->read(value[1]));
}

////////////////////////////////////////////////////////////////////////
//
// Description:
//    Writes value of field to file.
//
// Use: private

void
SoSFVec2f::writeValue(SoOutput *out) const
//
////////////////////////////////////////////////////////////////////////
{
    out->write(value[0]);

    if (! out->isBinary())
        out->write(' ');

    out->write(value[1]);
}
