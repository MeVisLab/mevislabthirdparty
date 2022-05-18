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
 |      SoMFVec3f
 |
 |   Author(s)          : Paul S. Strauss
 |
 ______________  S I L I C O N   G R A P H I C S   I N C .  ____________
 _______________________________________________________________________
 */

#ifndef  _SO_MF_VEC3F_
#define  _SO_MF_VEC3F_

#include <Inventor/fields/SoSubField.h>
#include <Inventor/SbLinear.h>


////////////////////////////////////////////////////////////////////////////////
//! Multiple-value field containing any number of three-dimensional vectors.
/*!
\class SoMFVec3f
\ingroup Fields
A multiple-value field that contains any number of three-dimensional
vectors.


SoMFVec3fs are written to file as one or more triples of floating
point values separated by whitespace.


When more than one value is present, all of the
values are enclosed in square brackets and separated by commas; for
example:
\code
[ 0 0 0, 1.2 3.4 5.6, 98.6 -4e1 212 ]
\endcode

*/
////////////////////////////////////////////////////////////////////////////////

class INVENTOR_API SoMFVec3f : public SoMField {
    //! Use standard field stuff
    SO_MFIELD_HEADER(SoMFVec3f, SbVec3f, const SbVec3f &);

  public:

    //!
    //! Some additional convenience functions:
    //!

    //! Set values from array of arrays of 3 floats
    void        setValues(int start, int num, const float xyz[][3]);

    //! Set the \p index'th value to the given floating point values.
    void        set1Value(int index, float x, float y, float z);

    //! Set the \p index'th value to the given floating point values.
    void        set1Value(int index, const float xyz[3]);

    //! Sets the field to contain the given value and only the given value (if
    //! the array had multiple values before, they are deleted).
    void        setValue(float x, float y, float z);

    //! Sets the field to contain the given value and only the given value (if
    //! the array had multiple values before, they are deleted).
    void        setValue(const float xyz[3]);

  SoINTERNAL public:
    static void         initClass();

  private:

    //! Write the values out as a block of data
    virtual void        writeBinaryValues(SoOutput *out) const;
    virtual bool        readBinaryValues(SoInput *in, int numToRead);
};

#endif /* _SO_MF_VEC3F_ */
