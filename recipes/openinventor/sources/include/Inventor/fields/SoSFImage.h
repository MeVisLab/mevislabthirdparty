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
 |      SoSFImage
 |
 |   Author(s)          : Gavin Bell
 |
 ______________  S I L I C O N   G R A P H I C S   I N C .  ____________
 _______________________________________________________________________
 */

#ifndef  _SO_SF_IMAGE_
#define  _SO_SF_IMAGE_

#include <Inventor/fields/SoSubField.h>
#include <Inventor/SbLinear.h>


////////////////////////////////////////////////////////////////////////////////
//! Field containing a 2D image.
/*!
\class SoSFImage
\ingroup Fields
A field containing a two-dimensional image.  Images can be greyscale
(intensity), greyscale with transparency information, RGB, or RGB with
transparency.  Each component of the image (intensity, red, green,
blue or transparency (alpha)) can have an unsigned one-byte value from
0 to 255.


Values are returned as arrays of unsigned chars.  The image is stored
in this array starting at the bottom left corner of the image with the
intensity or red component of that pixel, followed by either the alpha,
the green and blue, or the green, blue and alpha components (depending
on the number of components in the image).  The next value is the
first component of the next pixel to the right.


SoSFImages are written to file as three integers representing the
width, height and number of components in the image, followed by
width*height hexadecimal values representing the pixels in the
image, separated by whitespace.  A one-component image will have
one-byte hexadecimal values representing the intensity of the image.
For example, 0xFF is full intensity, 0x00 is no intensity.  A two-component
image puts the intensity in the first (high) byte and the transparency
in the second (low) byte.  Pixels in a three-component image have the red
component in the first (high) byte, followed by the green and blue
components (so 0xFF0000 is red).  Four-component images put the
transparency byte after red/green/blue (so 0x0000FF80 is
semi-transparent blue).  Note:  each pixel is actually read as a single
unsigned number, so a 3-component pixel with value "0x0000FF" can also
be written as "0xFF" or "255" (decimal).


For example,
\code
1 2 1 0xFF 0x00
\endcode
is a 1 pixel wide by 2 pixel high greyscale image, with the bottom pixel 
white and the top pixel black.  And:
\code
2 4 3 0xFF0000 0xFF00   0 0   0 0   0xFFFFFF 0xFFFF00
\endcode
is a 2 pixel wide by 4 pixel high RGB image, with the bottom left pixel red, 
the bottom right pixel green, the two middle rows of pixels black, the top
left pixel white, and the top right pixel yellow.

\par See Also
\par
SoField, SoSField
*/
////////////////////////////////////////////////////////////////////////////////

class INVENTOR_API SoSFImage : public SoSField {
    //! Uses only some of the standard field stuff (because there is no
    //! SbImage type):
    SO_SFIELD_REQUIRED_HEADER(SoSFImage);
    SO_SFIELD_CONSTRUCTOR_HEADER(SoSFImage);

  public:
    //! getValue returns the size, number of components and a constant
    //! pointer to the image.
    const unsigned char *       getValue(SbVec2s &size, int &nc) const;

    //! Sets the value of this field to be an image of the given size, with
    //! the given number of components, and with the given pixel values.
    //! \p size[0]*\p size[1]*\p nc bytes from the given array will be copied into
    //! internal storage maintained by the SoSFImage field.
    void                        setValue(const SbVec2s &size, int nc,
                                         const unsigned char *bytes);
    
    //! Equality/inequality tests
    bool                           operator ==(const SoSFImage &f) const;
    bool                           operator !=(const SoSFImage &f) const
        { return ! ((*this) == f); }

    //! This method can be used to efficiently edit the values in an image
    //! field.  startEditing() returns the size of the image in the \p size 
    //! and \p nc  arguments; writing past the end of the array returned is a 
    //! good way to cause hard-to-find core dumps.
    //! Do not forget to call finishEditing() after the modification has been done.
    unsigned char *             startEditing(SbVec2s &size, int &nc);
    //! Finish the editing of the field values.
    void                        finishEditing();

  SoINTERNAL public:
    static void         initClass();

  private:
    SbVec2s             size;           //!< Width and height of image
    int                 numComponents;  //!< Number of components per pixel
    unsigned char *     bytes;          //!< Array of pixels

    //! Reading and writing
    virtual bool        readValue(SoInput *in);
    virtual void        writeValue(SoOutput *out) const;
};

#endif /* _SO_SF_IMAGE_ */
