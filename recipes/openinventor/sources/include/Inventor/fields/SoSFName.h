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
 |      SoSFName
 |
 |   Author(s)          : Paul S. Strauss
 |
 ______________  S I L I C O N   G R A P H I C S   I N C .  ____________
 _______________________________________________________________________
 */

#ifndef  _SO_SF_NAME_
#define  _SO_SF_NAME_

#include <Inventor/SbString.h>
#include <Inventor/fields/SoSubField.h>


////////////////////////////////////////////////////////////////////////////////
//! Field containg a name.
/*!
\class SoSFName
\ingroup Fields
A field containing a name.  Names are short series of characters
generally used for labels or names, and are stored in a special table
designed to allow fast lookup and comparison.  For most purposes, an
SoSFString field is probably more appropriate.


SoSFNames are written to file as a string of
characters.  Names must begin with an underscore or alphabetic
character, and must consist entirely of underscores, alphabetic
characters, or numbers.

\par See Also
\par
SoField, SoSField, SoMFName
*/
////////////////////////////////////////////////////////////////////////////////

class INVENTOR_API SoSFName : public SoSField {

    //! Use standard field stuff
    SO_SFIELD_HEADER(SoSFName, SbName, const SbName &);

  public:

    //! Set this field to the name equivalent to the given string.
    void        setValue(const char *string);

  SoINTERNAL public:
    static void         initClass();
};

#endif /* _SO_SF_NAME_ */
