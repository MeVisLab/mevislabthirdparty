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
 |      SoSFBitMask
 |
 |   Author(s)          : Paul S. Strauss
 |
 ______________  S I L I C O N   G R A P H I C S   I N C .  ____________
 _______________________________________________________________________
 */

#ifndef  _SO_SF_BIT_MASK_
#define  _SO_SF_BIT_MASK_

#include <Inventor/fields/SoSFEnum.h>


////////////////////////////////////////////////////////////////////////////////
//! Single-value field containing a set of bit flags.
/*!
\class SoSFBitMask
\ingroup Fields
A single-value field that contains a mask of bit flags,
stored as an integer. Nodes that use this field class define mnemonic
names for the bit flags. These names should be used when setting or testing
the values of the field, even though the values are treated as
integers in the methods.


The bit-wise "&" and "|" operators should be used when testing and
setting flags in a mask.  For example, to turn on the sides of a 3D
text node and turn off the back you would write:
\code
text3->parts = text3->parts.getValue() | SoText3::SIDES;
text3->parts = text3->parts.getValue() & ~SoText3::BACK;
\endcode
SoSFBitMasks are written to file as one or more mnemonic enumerated type
names, in this format:
\code
( flag1 | flag2 | ... )
\endcode
If only one flag is used in a mask, the parentheses are optional.
These names differ among uses of this field in various node or engine
classes.  See their man pages for the names.


The field values may also be represented as integers, but this is not
guaranteed to be portable.

\par See Also
\par
SoField, SoSField, SoMFBitMask
*/
////////////////////////////////////////////////////////////////////////////////

class INVENTOR_API SoSFBitMask : public SoSFEnum {

    //! Use standard field stuff for derived class;
    //! the rest is inherited from SoSFEnum
    SO_SFIELD_DERIVED_HEADER(SoSFBitMask, int, int);

    //! Inherits other stuff from Enum field

  protected:
    //! Looks up enum name, returns value. Returns FALSE if not found.
    virtual bool        findEnumValue(const SbName &name, int &val);

  SoINTERNAL public:
    static void         initClass();
};

#endif /* _SO_SF_BIT_MASK_ */
