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
 |      SoSFMatrixd
 |
 |   Author(s)          : originally by Paul S. Strauss
 |                        adapted for double values by Wolf Spindler
 |
 ______________  S I L I C O N   G R A P H I C S   I N C .  ____________
 _______________________________________________________________________
 */

#ifndef  _SO_SF_MATRIXD_
#define  _SO_SF_MATRIXD_

#include <Inventor/fields/SoSubField.h>
#include <Inventor/SbLineard.h>


////////////////////////////////////////////////////////////////////////////////
//! Field containing a 4x4 matrix of double values.
/*!
\class SoSFMatrixd
\ingroup Fields
A field containing a transformation matrix (an SbMatrixd).


SoSFMatrixds are written to file as 16 double floating point
numbers separated by whitespace.  For example, an identity matrix is
written as:
\code
1 0 0 0  0 1 0 0  0 0 1 0  0 0 0 1
\endcode

\par See Also
\par
SoField, SoSField, SoMFMatrix, SbMatrix, SbMatrixd, SoMFMatrixd, SoSFMatrix
*/
////////////////////////////////////////////////////////////////////////////////

class INVENTOR_API SoSFMatrixd : public SoSField {

    //! Use standard field stuff
    SO_SFIELD_HEADER(SoSFMatrixd, SbMatrixd, const SbMatrixd &);

  public:
    //! Set one value from 16 doubles
    void                setValue(double a11, double a12, double a13, double a14,
                                 double a21, double a22, double a23, double a24,
                                 double a31, double a32, double a33, double a34,
                                 double a41, double a42, double a43, double a44);

  SoINTERNAL public:
    static void         initClass();
};

#endif /* _SO_SF_MATRIXD_ */
