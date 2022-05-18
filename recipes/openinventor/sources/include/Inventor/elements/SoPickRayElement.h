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
 |      This file defines the SoPickRayElement class.
 |
 |   Author(s)          : Paul S. Strauss
 |
 ______________  S I L I C O N   G R A P H I C S   I N C .  ____________
 _______________________________________________________________________
 */

#ifndef  _SO_PICK_RAY_ELEMENT
#define  _SO_PICK_RAY_ELEMENT

#include <Inventor/SbLinear.h>
#include <Inventor/elements/SoSubElement.h>

///////////////////////////////////////////////////////////////////////////////
///
///  \class SoPickRayElement
///  \ingroup Elements
///
///  Element that stores the current ray to use for picking. It
///  contains the world space ray information in terms of an
///  SbViewVolume. The projection point and view direction of the
///  volume represent the ray itself. The width (which equals the
///  height) represents the diameter of the picking circle in the near
///  plane. The near and far planes represent the distances to the near
///  and far planes between which valid intersections must lie.
///
//////////////////////////////////////////////////////////////////////////////

SoEXTENDER class INVENTOR_API SoPickRayElement : public SoElement {

    SO_ELEMENT_HEADER(SoPickRayElement);

  public:
    //! Initializes element
    virtual void        init(SoState *state);

    //! Always returns FALSE, since this element should never be a
    //! criterion for cache invalidation.
    virtual bool        matches(const SoElement *elt) const;

    //! Create and return a copy of this element
    virtual SoElement   *copyMatchInfo() const;

    //! Sets the picking ray
    static void         set(SoState *state, const SbViewVolume &volume);

    //! Returns the current picking ray view volume from the state
    static const SbViewVolume & get(SoState *state);

    //! Prints element (for debugging)
    virtual void        print(FILE *fp) const;

  SoINTERNAL public:
    //! Initializes the SoPickRayElement class
    static void         initClass();

  protected:
    SbViewVolume        volume;         //!< Ray as view volume

    virtual ~SoPickRayElement();
};

#endif /* _SO_PICK_RAY_ELEMENT */
