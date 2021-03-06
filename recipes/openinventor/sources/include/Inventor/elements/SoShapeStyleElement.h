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
 * Copyright (C) 1995-96   Silicon Graphics, Inc.
 *
 _______________________________________________________________________
 ______________  S I L I C O N   G R A P H I C S   I N C .  ____________
 |
 |   $Revision: 1.1.1.1 $
 |
 |   Description:
 |      This file defines the SoShapeStyleElement class.
 |      It takes values from the following: 
 |      SoDrawStyleElement
 |      SoComplexityTypeElement
 |      SoGLTextureEnabledElement
 |      SoLazyElement
 |      TransparencyType field of SoGLRenderAction
 |      CoordType of SoTextureCoordinateElement
 |      number and value of SoTransparencyElement
 |              to determine 
 |          whether to use fast-path rendering, and
 |          which fast-path rendering code to use
 |
 |   Author(s)          : Alan Norton,  Gavin Bell
 |
 ______________  S I L I C O N   G R A P H I C S   I N C .  ____________
 _______________________________________________________________________
 */

#ifndef  _SO_SHAPE_STYLE_ELEMENT
#define  _SO_SHAPE_STYLE_ELEMENT

#include <Inventor/elements/SoInt32Element.h>
#include <Inventor/elements/SoLazyElement.h>



///////////////////////////////////////////////////////////////////////////////
///
///  \class SoShapeStyleElement
///  \ingroup Elements
///
///  This elements stores some information shapes need to quickly
///  determine whether or not they should render, and, if they should
///  render, how they should render.  Specifically, it stores:
///
///  NeedNormals:   TRUE if lighting is on
///  NeedTexCoords: TRUE if texturing and texcoords not generated by GL
///
///  MightNotRender:  TRUE if:
///           -- bounding box complexity
///           -- invisible drawstyle
///           -- render abort callback registered
///
//////////////////////////////////////////////////////////////////////////////

SoEXTENDER class INVENTOR_API SoShapeStyleElement : public SoElement {

    SO_ELEMENT_HEADER(SoShapeStyleElement);

  public:

    //!
    //! API USED BY SHAPES:
    //!

    //! Get a readable instance:
    static const SoShapeStyleElement *  get(SoState *state);

    //! Returns TRUE if shapes may not render for some reason:
    bool                mightNotRender() const { return delayFlags!=0; }

    //! Returns TRUE if need normals:
    bool                needNormals() const { return needNorms; }
    
    //! Returns TRUE if need texture coordinates:
    bool                needTexCoords() const
        { return (texEnabled && (!texFunc)); }

    //! Returns a mask that can be used by the SoVertexPropertyCache
    //! class (see SoVertexProperty.h for the SoRenderInfo class) to
    //! quickly mask out the normal or texture coordinate cases if
    //! normals or texture coordinates aren't needed.
    int                 getRenderCaseMask() const
        { return renderCaseMask; }

    //! API USED BY OTHER ELEMENTS:

    static void         setDrawStyle(SoState *state, int32_t value);
    static void         setComplexityType(SoState *state, int32_t value);
    static void         setTransparencyType(SoState *state, int32_t value);
    static void         setTextureEnabled(SoState *state, bool value);
    static void         setTextureFunction(SoState *state, bool value);
    static void         setLightModel(SoState *state, int32_t value);
    //! Set value is TRUE if either diffuse, transparency, or materialbinding
    //! are overridden; otherwise FALSE.
    static void         setOverrides(SoState *state, bool value);
   
    static bool         isScreenDoor(SoState *state);

  SoINTERNAL public:
    bool        isTextureFunction() const
        {return texFunc;}
    virtual void        init(SoState *state);
    virtual bool        matches(const SoElement *elt) const;
    virtual void        push(SoState *state);
    virtual SoElement   *copyMatchInfo() const;
    static void         initClass();
    virtual void        print(FILE *fp) const;

  protected:
    virtual             ~SoShapeStyleElement();

  private:
    int                 delayFlags; //!< True if rendering might be delayed
    bool                needNorms;
    bool                texEnabled, texFunc;
    int                 renderCaseMask;
};

#endif /* _SO_SHAPE_STYLE_ELEMENT */
