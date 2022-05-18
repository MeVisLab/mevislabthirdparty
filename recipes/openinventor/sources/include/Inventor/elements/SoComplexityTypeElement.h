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
 |   Description:
 |      This file defines the SoComplexityTypeElement class.
 |
 |   Author(s)          : Paul S. Strauss
 |
 ______________  S I L I C O N   G R A P H I C S   I N C .  ____________
 _______________________________________________________________________
 */

#ifndef  _SO_COMPLEXITY_TYPE_ELEMENT
#define  _SO_COMPLEXITY_TYPE_ELEMENT

#include <Inventor/elements/SoInt32Element.h>

///////////////////////////////////////////////////////////////////////////////
///
///  \class SoComplexityTypeElement
///  \ingroup Elements
///
///  Element that stores the current complexity type.
///
//////////////////////////////////////////////////////////////////////////////

SoEXTENDER class INVENTOR_API SoComplexityTypeElement : public SoInt32Element {

    SO_ELEMENT_HEADER(SoComplexityTypeElement);

  public:
    //! These are the available complexity types:
    enum Type {
        OBJECT_SPACE,           //!< Complexity computed in object space
        SCREEN_SPACE,           //!< Complexity computed in screen space
        BOUNDING_BOX            //!< Bounding box used to represent object
    };

    //! Initializes element
    virtual void        init(SoState *state);

    //! Sets the current complexity type in the state
    static void         set(SoState *state, Type type);

#ifndef IV_STRICT
    static void         set(SoState *state, SoNode *, Type type)
        { set(state, type); }
#endif

    //! Returns current complexity type from the state
    static Type         get(SoState *state)
        { return (Type)SoInt32Element::get(classStackIndex, state); }

    //! Returns the default complexity type
    static Type         getDefault()            { return OBJECT_SPACE; }

    //! Prints element (for debugging)
    virtual void        print(FILE *fp) const;

  SoINTERNAL public:
    //! Initializes the SoComplexityTypeElement class
    static void         initClass();

  protected:
    virtual ~SoComplexityTypeElement();
};

#endif /* _SO_COMPLEXITY_TYPE_ELEMENT */
