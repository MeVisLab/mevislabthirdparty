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
 |      SoTextureQualityElement, SoTextureOverrideElement
 |
 |   Author(s)          : Gavin Bell
 |
 ______________  S I L I C O N   G R A P H I C S   I N C .  ____________
 _______________________________________________________________________
 */

#include <Inventor/elements/SoTextureQualityElement.h>

SO_ELEMENT_SOURCE(SoTextureQualityElement);

////////////////////////////////////////////////////////////////////////
//
// Description:
//    Destructor.
//
// Use: private

SoTextureQualityElement::~SoTextureQualityElement()
//
////////////////////////////////////////////////////////////////////////
{
}

////////////////////////////////////////////////////////////////////////
//
// Description:
//    Initializes element
//
// Use: public

void
SoTextureQualityElement::init(SoState *)
//
////////////////////////////////////////////////////////////////////////
{
    data = getDefault();
}

SO_ELEMENT_SOURCE(SoTextureOverrideElement);

////////////////////////////////////////////////////////////////////////
//
// Description:
//    Initializes element.  All flags are initialized to FALSE (0).
//
// Use: public

void
SoTextureOverrideElement::init(SoState *)
//
////////////////////////////////////////////////////////////////////////
{
    flags = 0;
}

////////////////////////////////////////////////////////////////////////
//
// Description:
//    Pushes element, copying flags from previous top instance.
//
// Use: public
void
SoTextureOverrideElement::push(SoState *state)
//
////////////////////////////////////////////////////////////////////////
{
    SoTextureOverrideElement *elt =
        (SoTextureOverrideElement *)getNextInStack();

    flags = elt->flags;
    elt->capture(state);  // Capture previous element
}

////////////////////////////////////////////////////////////////////////
//
// Description:
//    Set texture quality override flag
//
// Use: public, static
bool
SoTextureOverrideElement::getQualityOverride(SoState *state)
//
////////////////////////////////////////////////////////////////////////
{
    const SoTextureOverrideElement *elt;
    elt = (const SoTextureOverrideElement *)
        getConstElement(state, classStackIndex);
    return elt->flags & TEXTURE_QUALITY;
}

////////////////////////////////////////////////////////////////////////
//
// Description:
//    Set texture image override flag
//
// Use: public, static
bool
SoTextureOverrideElement::getImageOverride(SoState *state)
//
////////////////////////////////////////////////////////////////////////
{
    const SoTextureOverrideElement *elt;
    elt = (const SoTextureOverrideElement *)
        getConstElement(state, classStackIndex);
    return (elt->flags & TEXTURE_IMAGE)!=0;
}

////////////////////////////////////////////////////////////////////////
//
// Description:
//    Set texture quality override flag
//
// Use: public, static
void
SoTextureOverrideElement::setQualityOverride(SoState *state,
                                             bool override)
//
////////////////////////////////////////////////////////////////////////
{
    SoTextureOverrideElement    *elt;
    elt = (SoTextureOverrideElement *)getElement(state, classStackIndex);
    if (override)
        elt->flags |= TEXTURE_QUALITY;
    else
        elt->flags &= ~TEXTURE_QUALITY;
}

////////////////////////////////////////////////////////////////////////
//
// Description:
//    Set texture image override flag
//
// Use: public, static
void
SoTextureOverrideElement::setImageOverride(SoState *state,
                                           bool override)
//
////////////////////////////////////////////////////////////////////////
{
    SoTextureOverrideElement    *elt;
    elt = (SoTextureOverrideElement *)getElement(state, classStackIndex);
    if (override)
        elt->flags |= TEXTURE_IMAGE;
    else
        elt->flags &= ~TEXTURE_IMAGE;
}

////////////////////////////////////////////////////////////////////////
//
// Description:
//     Create a copy of this instance suitable for calling matches()
//     on.
//
// Use: protected

SoElement *
SoTextureOverrideElement::copyMatchInfo() const
//
////////////////////////////////////////////////////////////////////////
{
    SoTextureOverrideElement *result =
        (SoTextureOverrideElement *)getTypeId().createInstance();

    result->flags = flags;

    return result;
}

////////////////////////////////////////////////////////////////////////
//
// Description:
//    Returns TRUE if elements match
//
// Use: public

bool
SoTextureOverrideElement::matches(const SoElement *elt) const
//
////////////////////////////////////////////////////////////////////////
{
    return (flags == ((const SoTextureOverrideElement *) elt)->flags);
}

////////////////////////////////////////////////////////////////////////
//
// Description:
//    Prints element for debugging.
//
// Use: public
//
////////////////////////////////////////////////////////////////////////

#ifdef DEBUG
void
SoTextureOverrideElement::print(FILE *fp) const
{
    pFlag(fp, "TEXTURE_QUALITY", TEXTURE_QUALITY);
    pFlag(fp, "TEXTURE_IMAGE", TEXTURE_IMAGE);
    putc('\n', fp);
}
#else  /* DEBUG */
void
SoTextureOverrideElement::print(FILE *) const
{
}
#endif /* DEBUG */

void
SoTextureOverrideElement::pFlag(FILE *fp, const char *flagName,
                                int flagBit) const
{
    if (flags & flagBit)
        fprintf(fp, "%s\t", flagName);
}
