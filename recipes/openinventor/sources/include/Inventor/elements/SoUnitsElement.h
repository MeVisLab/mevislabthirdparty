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
 |      This file defines the SoUnitsElement class.
 |
 |   Author(s)          : Paul S. Strauss
 |
 ______________  S I L I C O N   G R A P H I C S   I N C .  ____________
 _______________________________________________________________________
 */

#ifndef  _SO_UNITS_ELEMENT
#define  _SO_UNITS_ELEMENT

#include <Inventor/elements/SoInt32Element.h>

///////////////////////////////////////////////////////////////////////////////
///
///  \class SoUnitsElement
///  \ingroup Elements
///
///  Element that stores the current units type.
///
//////////////////////////////////////////////////////////////////////////////

SoEXTENDER class INVENTOR_API SoUnitsElement : public SoInt32Element {

    SO_ELEMENT_HEADER(SoUnitsElement);

  public:
    //! These are the available types of units:
    enum Units {
        METERS,
        CENTIMETERS,
        MILLIMETERS,
        MICROMETERS,
        MICRONS,
        NANOMETERS,
        ANGSTROMS,
        KILOMETERS,
        FEET,
        INCHES,
        POINTS,
        YARDS,
        MILES,
        NAUTICAL_MILES
    };

    //! Initializes element
    virtual void        init(SoState *state);

    //! Sets the current units in the state
    static void         set(SoState *state, Units units)
        { SoInt32Element::set(classStackIndex, state, (int32_t)units); }

#ifndef IV_STRICT
    static void         set(SoState *state, SoNode *, Units units)
        { set(state, units); }
#endif

    //! Returns current units from the state
    static Units        get(SoState *state)
        { return (Units)SoInt32Element::get(classStackIndex, state); }

    //! Returns the default units
    static Units        getDefault()            { return METERS; }

    //! Prints element (for debugging)
    virtual void        print(FILE *fp) const;

  SoINTERNAL public:
    //! Initializes the SoUnitsElement class
    static void         initClass();

  protected:
    virtual ~SoUnitsElement();
};

#endif /* _SO_UNITS_ELEMENT */
