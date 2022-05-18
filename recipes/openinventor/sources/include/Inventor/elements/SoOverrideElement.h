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
 |      This file defines the SoOverrideElement class.
 |
 |   Author(s)          : Roger Chickering, Gavin Bell
 |
 ______________  S I L I C O N   G R A P H I C S   I N C .  ____________
 _______________________________________________________________________
 */

#ifndef  _SO_OVERRIDE_ELEMENT
#define  _SO_OVERRIDE_ELEMENT

#include <Inventor/elements/SoSubElement.h>

//!
//! Macro to implement get*Override inline methods.  There are a lot of
//! these methods, each of which has an identical implementation and
//! which needs to be inline to keep traversal fast.
//!
#define SO_GET_OVERRIDE(flag) \
    const SoOverrideElement *elt; \
    elt = (const SoOverrideElement *) \
        getConstElement(state, classStackIndex); \
    return (elt->flags & flag) != 0;

//!
//! Implement set*Override methods.
//!
#define SO_SET_OVERRIDE(flag) \
    SoOverrideElement   *elt; \
    elt = (SoOverrideElement *)getElement(state, classStackIndex); \
    if (override) \
        elt->flags |= flag; \
    else \
        elt->flags &= ~flag;

///////////////////////////////////////////////////////////////////////////////
///
///  \class SoOverrideElement
///  \ingroup Elements
///
///  Element that stores a flag for each type of element which can be
///  overridden.  Nodes implement override by setting the appropriate
///  bit if their override flag is on, and ignoring overridden elements
///  if the corresponding bit in the state's SoOverrideElement is set.
///  
//////////////////////////////////////////////////////////////////////////////

SoEXTENDER class INVENTOR_API SoOverrideElement : public SoElement {

    SO_ELEMENT_HEADER(SoOverrideElement);

    enum {
        AMBIENT_COLOR   = 0x1,
//        COLOR_INDEX     = 0x2,
        COMPLEXITY      = 0x4,
        COMPLEXITY_TYPE = 0x8,
        CREASE_ANGLE    = 0x10,
        DIFFUSE_COLOR   = 0x20,
        TRANSPARENCY    = 0x20, //!< TRANSPARENCY is same as diffuse color:  overriding one will override both.
        DRAW_STYLE      = 0x40,
        EMISSIVE_COLOR  = 0x80,
        FONT_NAME       = 0x100,
        FONT_SIZE       = 0x200,
        LIGHT_MODEL     = 0x400,
        LINE_PATTERN    = 0x800,
        LINE_WIDTH      = 0x1000,
        MATERIAL_BINDING= 0x2000, 
        POINT_SIZE      = 0x4000,
        PICK_STYLE      = 0x8000,
        SHAPE_HINTS     = 0x10000,
        SHININESS       = 0x20000,
        SPECULAR_COLOR  = 0x40000,
        POLYGON_OFFSET  = 0x80000
    };

  public:
    //! Initializes element
    virtual void        init(SoState *state);

    //! Comparison based on value of int32_ts
    virtual bool        matches(const SoElement *elt) const;

    //! Overrides push() method to copy values from next instance in
    //! the stack, and set up cache dependencies correctly
    virtual void        push(SoState *state);

    //!
    //! "get" methods for each element which can be overridden.
    //!

    //! Returns TRUE if SoAmbientColorElement is overridden.
    static bool         getAmbientColorOverride(SoState *state)
        { SO_GET_OVERRIDE(AMBIENT_COLOR); }

    //! Returns TRUE if SoComplexityElement is overridden.
    static bool         getComplexityOverride(SoState *state)
        { SO_GET_OVERRIDE(COMPLEXITY); }

    //! Returns TRUE if SoComplexityTypeElement is overridden.
    static bool         getComplexityTypeOverride(SoState *state)
        { SO_GET_OVERRIDE(COMPLEXITY_TYPE); }

    //! Returns TRUE if SoCreaseAngleElement is overridden.
    static bool         getCreaseAngleOverride(SoState *state)
        { SO_GET_OVERRIDE(CREASE_ANGLE); }

    //! Returns TRUE if SoDiffuseColorElement is overridden.
    static bool         getDiffuseColorOverride(SoState *state)
        { SO_GET_OVERRIDE(DIFFUSE_COLOR); }

    //! Returns TRUE if SoDrawStyleElement is overridden.
    static bool         getDrawStyleOverride(SoState *state)
        { SO_GET_OVERRIDE(DRAW_STYLE); }

    //! Returns TRUE if SoEmissiveColorElement is overridden.
    static bool         getEmissiveColorOverride(SoState *state)
        { SO_GET_OVERRIDE(EMISSIVE_COLOR); }

    //! Returns TRUE if SoFontNameElement is overridden.
    static bool         getFontNameOverride(SoState *state)
        { SO_GET_OVERRIDE(FONT_NAME); }

    //! Returns TRUE if SoFontSizeElement is overridden.
    static bool         getFontSizeOverride(SoState *state)
        { SO_GET_OVERRIDE(FONT_SIZE); }

    //! Returns TRUE if SoLightModelElement is overridden.
    static bool         getLightModelOverride(SoState *state)
        { SO_GET_OVERRIDE(LIGHT_MODEL); }

    //! Returns TRUE if SoLinePatternElement is overridden.
    static bool         getLinePatternOverride(SoState *state)
        { SO_GET_OVERRIDE(LINE_PATTERN); }

    //! Returns TRUE if SoLineWidthElement is overridden.
    static bool         getLineWidthOverride(SoState *state)
        { SO_GET_OVERRIDE(LINE_WIDTH); }
        
    //! Returns TRUE if SoMaterialBindingElement is overridden.
    static bool         getMaterialBindingOverride(SoState *state)
        { SO_GET_OVERRIDE(MATERIAL_BINDING); }

    //! Returns TRUE if SoPointSizeElement is overridden.
    static bool         getPointSizeOverride(SoState *state)
        { SO_GET_OVERRIDE(POINT_SIZE); }

    //! Returns TRUE if SoPickStyleElement is overridden.
    static bool         getPickStyleOverride(SoState *state)
        { SO_GET_OVERRIDE(PICK_STYLE); }

    //! Returns TRUE if SoShapeHintsElement is overridden.
    static bool         getShapeHintsOverride(SoState *state)
        { SO_GET_OVERRIDE(SHAPE_HINTS); }

    //! Returns TRUE if SoShininessElement is overridden.
    static bool         getShininessOverride(SoState *state)
        { SO_GET_OVERRIDE(SHININESS); }

    //! Returns TRUE if SoSpecularColorElement is overridden.
    static bool         getSpecularColorOverride(SoState *state)
        { SO_GET_OVERRIDE(SPECULAR_COLOR); }

    //! Returns TRUE if SoTransparencyElement is overridden.
    static bool         getTransparencyOverride(SoState *state)
        { SO_GET_OVERRIDE(TRANSPARENCY); }

    //! Returns TRUE if SoPolygonOffsetElement is overridden.
    static bool         getPolygonOffsetOverride(SoState *state)
        { SO_GET_OVERRIDE(POLYGON_OFFSET); }

    //!
    //! "set" methods for each element which can be overridden.
    //!

    //! set override flag for SoAmbientColorElement.
    static void         setAmbientColorOverride(SoState *state, SoNode *,
                                                bool override)
        { SO_SET_OVERRIDE(AMBIENT_COLOR); }

    //! set override flag for SoComplexityElement.
    static void         setComplexityOverride(SoState *state, SoNode *,
                                              bool override)
        { SO_SET_OVERRIDE(COMPLEXITY); }
    
    //! set override flag for SoComplexityTypeElement.
    static void         setComplexityTypeOverride(SoState *state, SoNode *,
                                                  bool override)
        { SO_SET_OVERRIDE(COMPLEXITY_TYPE); }
    
    //! set override flag for SoCreaseAngleElement.
    static void         setCreaseAngleOverride(SoState *state, SoNode *,
                                               bool override)
        { SO_SET_OVERRIDE(CREASE_ANGLE); }

    //! set override flag for SoDiffuseColorElement.
    static void         setDiffuseColorOverride(SoState *state, SoNode *,
                                                bool override);

    //! set override flag for SoDrawStyleElement.
    static void         setDrawStyleOverride(SoState *state, SoNode *,
                                             bool override)
        { SO_SET_OVERRIDE(DRAW_STYLE); }

    //! set override flag for SoEmissiveColorElement.
    static void         setEmissiveColorOverride(SoState *state, SoNode *,
                                                 bool override)
        { SO_SET_OVERRIDE(EMISSIVE_COLOR); }

    //! set override flag for SoFontNameElement.
    static void         setFontNameOverride(SoState *state, SoNode *,
                                            bool override)
        { SO_SET_OVERRIDE(FONT_NAME); }

    //! set override flag for SoFontSizeElement.
    static void         setFontSizeOverride(SoState *state, SoNode *,
                                            bool override)
        { SO_SET_OVERRIDE(FONT_SIZE); }

    //! set override flag for SoLightModelElement.
    static void         setLightModelOverride(SoState *state, SoNode *,
                                              bool override)
        { SO_SET_OVERRIDE(LIGHT_MODEL); }

    //! set override flag for SoLinePatternElement.
    static void         setLinePatternOverride(SoState *state, SoNode *,
                                               bool override)
        { SO_SET_OVERRIDE(LINE_PATTERN); }

    //! set override flag for SoLineWidthElement.
    static void         setLineWidthOverride(SoState *state, SoNode *,
                                             bool override)
        { SO_SET_OVERRIDE(LINE_WIDTH); }                                     
                                             
           //! set override flag for SoMaterialBinding.
    static void         setMaterialBindingOverride(SoState *state, SoNode *,
                                            bool override);                                
    
    //! set override flag for SoPickStyleElement.
    static void         setPickStyleOverride(SoState *state, SoNode *,
                                            bool override)
        { SO_SET_OVERRIDE(PICK_STYLE); }
    
    //! set override flag for SoPointSizeElement.
    static void         setPointSizeOverride(SoState *state, SoNode *,
                                             bool override)
        { SO_SET_OVERRIDE(POINT_SIZE); }

    //! set override flag for SoShapeHintsElement.
    static void         setShapeHintsOverride(SoState *state, SoNode *,
                                              bool override)
        { SO_SET_OVERRIDE(SHAPE_HINTS); }
    
    //! set override flag for SoShininessElement.
    static void         setShininessOverride(SoState *state, SoNode *,
                                             bool override)
        { SO_SET_OVERRIDE(SHININESS); }
    
    //! set override flag for SoSpecularColorElement.
    static void         setSpecularColorOverride(SoState *state, SoNode *,
                                                 bool override)
        { SO_SET_OVERRIDE(SPECULAR_COLOR); }
    
    //! set override flag for SoTransparencyElement.
    static void         setTransparencyOverride(SoState *state, SoNode *,
                                                 bool override);

    //! set override flag for SoPolygonOffsetElement.
    static void         setPolygonOffsetOverride(SoState *state, SoNode *,
                                                 bool override)
         { SO_SET_OVERRIDE(POLYGON_OFFSET); }

    //! Prints element (for debugging)
    virtual void        print(FILE *fp) const;

  SoINTERNAL public:
    //! Initializes the SoOverrideElement class
    static void         initClass();

    //! Copy method, copies flags
    virtual SoElement   *copyMatchInfo() const;
    
  private:
    //! Used by ::print method
    void pFlag(FILE *, const char *, int) const;

    uint32_t flags;
};

#endif /* _SO_OVERRIDE_ELEMENT */

