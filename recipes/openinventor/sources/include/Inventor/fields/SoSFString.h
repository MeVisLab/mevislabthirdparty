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
 |      SoSFString
 |
 |   Author(s)          : Paul S. Strauss
 |
 ______________  S I L I C O N   G R A P H I C S   I N C .  ____________
 _______________________________________________________________________
 */

#ifndef  _SO_SF_STRING_
#define  _SO_SF_STRING_

#include <Inventor/fields/SoSubField.h>


////////////////////////////////////////////////////////////////////////////////
//! Field containing a string.
/*!
\class SoSFString
\ingroup Fields
A field containing an ASCII string (sequence of characters).  Inventor
does not support non-ASCII strings.


SoSFStrings are written to file as a sequence of ASCII characters
in double quotes (optional if the string doesn't contain any
whitespace).  Any characters (including newlines) may appear within
the quotes. To include a double quote character within the string,
precede it with a backslash.  For example:
\code
Testing
"One, Two, Three"
"He said, \"Immel did it!\""
\endcode
are all valid strings.

\par See Also
\par
SbString, SoField, SoSField, SoMFString
*/
////////////////////////////////////////////////////////////////////////////////

class INVENTOR_API SoSFString : public SoSField {
    //! Use standard field stuff
    SO_SFIELD_HEADER(SoSFString, SbString, const SbString &);

  public:
    //!
    //! Some additional convenience functions:
    //!

    //! Set value from character string
    void        setValue(const char *string);

  SoINTERNAL public:
    static void         initClass();
};

#endif /* _SO_SF_STRING_ */
