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
 |      SoMFPlaned
 |
 |   Author(s)          : originally by Ronen Barzel
 |                        adapted for double values by Wolf Spindler
 |
 ______________  S I L I C O N   G R A P H I C S   I N C .  ____________
 _______________________________________________________________________
 */

#ifndef  _SO_MF_PLANED_
#define  _SO_MF_PLANED_

#include <Inventor/fields/SoSubField.h>
#include <Inventor/SbLineard.h>


////////////////////////////////////////////////////////////////////////////////
//! Field containing several plane equations.
/*!
\class SoMFPlaned
\ingroup Fields
A field containing one or more plane equations.


SoMFPlaneds are written to file as groups of four floating point double
values separated by whitespace.  In each set of four values, the first
three are the normal direction of the plane, the fourth is the
distance of the plane from the origin (in the direction of the normal).


When more than one value is present, all of the
values are enclosed in square brackets and separated by commas; for
example:
\code
[ 1 0 0 0, .707 .707 0 100, ]
\endcode

*/
////////////////////////////////////////////////////////////////////////////////

class INVENTOR_API SoMFPlaned : public SoMField {
    //! Use standard field stuff
    SO_MFIELD_HEADER(SoMFPlaned, SbPlaned, SbPlaned);

  SoINTERNAL public:
    static void         initClass();

  private:
    //! Returns number of ASCII values to write per output line
    virtual int         getNumValuesPerLine() const;
};

#endif /* _SO_MF_PLANED_ */
