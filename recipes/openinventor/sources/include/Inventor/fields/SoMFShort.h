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
 |      SoMFShort
 |
 |   Author(s)          : Paul S. Strauss
 |
 ______________  S I L I C O N   G R A P H I C S   I N C .  ____________
 _______________________________________________________________________
 */

#ifndef  _SO_MF_SHORT_
#define  _SO_MF_SHORT_

#include <Inventor/fields/SoSubField.h>


////////////////////////////////////////////////////////////////////////////////
//! Multiple-value field containing any number of short integers.
/*!
\class SoMFShort
\ingroup Fields
A multiple-value field that contains any number of short (16-bit)
integers.


SoMFShorts are written to file as one or more short integer
values, represented as decimal, hexadecimal (beginning with '0x') or
octal (beginning with '0') values.
When more than one value is present, all of the
values are enclosed in square brackets and separated by commas; for
example:
\code
[ -7, 0xFF, -033 ]
\endcode

*/
////////////////////////////////////////////////////////////////////////////////

class INVENTOR_API SoMFShort : public SoMField {
    //! Use standard field stuff
    SO_MFIELD_HEADER(SoMFShort, short, short);

  SoINTERNAL public:
    static void         initClass();

  private:
    //! Returns number of ASCII values to write per output line
    virtual int         getNumValuesPerLine() const;
};

#endif /* _SO_MF_SHORT_ */
