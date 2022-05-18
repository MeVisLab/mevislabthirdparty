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
 |      This file defines the SoLazyElement and SoColorPacker classes.
 |
 |   Author(s)          : Alan Norton, Gavin Bell
 |
 ______________  S I L I C O N   G R A P H I C S   I N C .  ____________
 _______________________________________________________________________
 */

#ifndef  _SO_LAZY_ELEMENT
#define  _SO_LAZY_ELEMENT

#include <Inventor/system/SbSystem.h>
#include <Inventor/SbColor.h>
#include <Inventor/elements/SoElement.h>
#include <Inventor/elements/SoSubElement.h>
#include <Inventor/system/SbOpenGL.h>
#include <math.h>

class SoMFFloat; class SoMFColor; class SoColorPacker;

///////////////////////////////////////////////////////////////////////////////
///
///  \class SoLazyElement
///  \ingroup Elements
///
///  Element that manages several properties such as colors, that need to
///  be lazily tracked by GL.  Also includes:
///      Transparencies
///      GLColorMaterial
///      GLBlendEnablement 
///      PolygonStipple
///      Light model
///      Color index
///
//////////////////////////////////////////////////////////////////////////////
//! defines used in this element:

//! threshold to ignore changes in shininess:
#define SO_LAZY_SHINY_THRESHOLD         0.005

//! number of components (subelements) in this element:
#define SO_LAZY_NUM_COMPONENTS          9

typedef void SoDrawElementsCallback(void* userData, SoState* state, GLenum mode,
                    GLsizei count,
                    GLenum type,
                    const GLvoid * indices);

typedef void SoDrawArraysCallback(void* userData, SoState* state, GLenum mode,
                                  GLint first,
                                  GLsizei count);

SoEXTENDER class INVENTOR_API SoLazyElement : public SoElement {

    SO_ELEMENT_HEADER(SoLazyElement);

  public:   
        //! Following masks and cases define the components of the
        //! lazy element.  Masks are needed by SoEXTENDER apps that
        //! need to use SoGLLazyElement::reset(bitmask) to invalidate
        //! GL values of particular components.
        //! NOTE: the order of these cases should not be changed without
        //! careful consideration of dependencies in the reallySend method.
    enum cases{ 
        LIGHT_MODEL_CASE        =   0,
        COLOR_MATERIAL_CASE     =   1,
        DIFFUSE_CASE            =   2, 
        AMBIENT_CASE            =   3,
        EMISSIVE_CASE           =   4,
        SPECULAR_CASE           =   5,
        SHININESS_CASE          =   6,
        BLENDING_CASE           =   7, 
        TRANSPARENCY_CASE       =   8
    }; 
    enum masks{
        LIGHT_MODEL_MASK        = 1<<LIGHT_MODEL_CASE, 
        COLOR_MATERIAL_MASK     = 1<<COLOR_MATERIAL_CASE,  
        DIFFUSE_MASK            = 1<<DIFFUSE_CASE, 
        AMBIENT_MASK            = 1<<AMBIENT_CASE, 
        EMISSIVE_MASK           = 1<<EMISSIVE_CASE,
        SPECULAR_MASK           = 1<<SPECULAR_CASE,
        SHININESS_MASK          = 1<<SHININESS_CASE,
        TRANSPARENCY_MASK       = 1<<TRANSPARENCY_CASE,
        BLENDING_MASK           = 1<<BLENDING_CASE, 
        ALL_MASK                = (1<<SO_LAZY_NUM_COMPONENTS)-1
    };

    //!Enum values to be used in setting/getting light model: 
    enum LightModel {
        BASE_COLOR      = 0, 
        PHONG           = 1
    };
    
    //! Initializes element
    virtual void        init(SoState *state);

    //! static set methods:
 
    static void setDiffuse(SoState *state, SoNode *node, int32_t numColors, 
            const SbColor *colors, SoColorPacker *cPacker);                 
    static void setTransparency(SoState *state, SoNode *node, int32_t numTransp, 
            const float *transp, SoColorPacker *cPacker);                              
    static void         setPacked(SoState *state, SoNode *node,
            int32_t numColors, const uint32_t *colors);    
    static void         setAmbient(SoState *state, const SbColor* color);                   
    static void         setEmissive(SoState *state, const SbColor* color);          
    static void         setSpecular(SoState *state, const SbColor* color);                  
    static void         setShininess(SoState *state, float value);                  
    static void         setColorMaterial(SoState *state, bool value);                     
    static void         setBlending(SoState *state,  bool value);
    //! This method allows to enable overriding of the blending mode.
    //! When this method is called with flag == true, any further call to setBlending() will have no effect.
    //! This can be turned off again with flag == false.
    static void         setOverrideBlending(SoState *state,  bool flag);             
    static void         setLightModel(SoState *state, const int32_t model);
    
    //! get() methods get value from Inventor state.  The public methods are
    //! static, they get an instance of the element.  If there is a cache,
    //! the appropriate virtual registerGetDependence is called.
    static const SbColor &      getDiffuse(SoState* state, int index);  
    static float                getTransparency(SoState*, int index);
    static const uint32_t       *getPackedColors(SoState*);       
    static const SbColor &      getAmbient(SoState*);   
    static const SbColor &      getEmissive(SoState*);  
    static const SbColor &      getSpecular(SoState*);  
    static float                getShininess(SoState*);
    static bool                 getColorMaterial(SoState*);
    static bool                 getBlending(SoState*);
    static int32_t              getLightModel(SoState*);
    
    //! Methods to inquire about current colors:
    int32_t                     getNumDiffuse() const
        {return ivState.numDiffuseColors;} 
    int32_t                     getNumTransparencies() const
        {return ivState.numTransparencies;}
    bool                        isPacked() const
        {return ivState.packed;}                
    bool                        isTransparent() const
        {return(ivState.packedTransparent ||
            (ivState.numTransparencies > 1)||
            (ivState.transparencies[0]>0.0));}
    
    //! Returns the top (current) instance of the element in the state
    //! Note that the cache dependencies associated with this element
    //! are managed differently from other elements:
    //! this replaces the SoElement::getConstElement that is used by
    //! standard elements, but which causes cache dependency.  Note
    //! that this element is not const; however modifications to it
    //! can cause problems.  SoEXTENDER apps should use only SoEXTENDER
    //! methods on this element.
    static  SoLazyElement * getInstance(SoState *state)
    {  return (SoLazyElement *) 
        (state->getElementNoPush(classStackIndex));}
         
    //!Specify inventor defaults for colors, etc.
    static SbColor      getDefaultDiffuse()
            {return SbColor(0.8f, 0.8f, 0.8f);}
    static SbColor      getDefaultAmbient()
            {return SbColor(0.2f, 0.2f, 0.2f);}
    static SbColor      getDefaultSpecular()
            {return SbColor(0.0f, 0.0f, 0.0f);}
    static SbColor      getDefaultEmissive()
            {return SbColor(0.0f, 0.0f, 0.0f);}
    static float        getDefaultShininess()
            {return 0.2f;}
    static uint32_t     getDefaultPacked()
            {return (0xccccccff);}          
    static float        getDefaultTransparency()
            {return 0.0f;}
    static int32_t      getDefaultLightModel()
            {return PHONG;}
   
    SoINTERNAL public:
    
    //! set method for use in SoMaterial nodes:
    static void setMaterials(SoState *state, SoNode *node, uint32_t bitmask,
        SoColorPacker *cPacker,   
        const SoMFColor& diffuse, const SoMFFloat& transp, 
        const SoMFColor& ambient, const SoMFColor& emissive, 
        const SoMFColor& specular, const SoMFFloat& shininess);
                          
    //! push (for non-GL elements)
    virtual void        push(SoState *state);

    //! note: matches, copyMatchinfo not used by this element.
    //! they are replaced by lazyMatches, copyLazyMatchInfo, on
    //! SoGLLazyElement.
    virtual bool        matches(const SoElement *) const; 
        
    virtual SoElement   *copyMatchInfo() const; 
                
    //!Get a Writable instance, so will force a push if needed:
    static SoLazyElement * getWInstance(SoState *state)
        {return (SoLazyElement *)
        (state->getElement(classStackIndex));}
    
    //! Prints element (for debugging)
    virtual void        print(FILE *fp) const;

    //! Initializes the SoLazyElement class
    static void         initClass();
    
    //!Following SoINTERNAL get() methods do NOT cause cache dependency, should
    //!only be invoked by nodes that use the reallySend method on SoGLLazyElement
    //!to establish correct cache dependencies by tracking what was actually
    //!sent to GL.
    const uint32_t *getPackedPointer() const
        {return ivState.packedColors;}
        
    const SbColor*      getDiffusePointer() const
        {return ivState.diffuseColors; }
                 
    const float         *getTransparencyPointer() const
        {return ivState.transparencies;}
        
    //! set method for transparency type is SoINTERNAL, because it should
    //! only be invoked by SoGLRenderAction
    static void setTransparencyType(SoState *state, int32_t type);

    //! Set a callback for drawElements().
    static void setDrawElementsCallback(SoState* state, SoDrawElementsCallback* cb, void* userData);

    // Fixed positions for attributes, shaders need to use these fixed attribute locations:
    enum VertexAttribs {
      ATTRIB_VERTEX = 0,
      ATTRIB_NORMAL = 1,
      ATTRIB_COLOR  = 2,
      ATTRIB_TEXCOORD = 3
    };

    //! Sets if vertex attributes should be used instead of old style glVertexPointer/glNormalPointer etc.
    static void setUseVertexAttributes( SoState* state, bool flag );
    //! Returns if vertex attributes should be used instead of old style glVertexPointer/glNormalPointer etc.
    static bool shouldUseVertexAttributes( SoState* state );
 
    //! Set a callback for drawElements().
    static void setDrawArraysCallback(SoState* state, SoDrawArraysCallback* cb, void* userData);

    //! Draws the given data using glDrawArrays() or via a callback if one has been set.
    static void drawArrays(SoState* state, GLenum mode, GLint first, GLsizei count);

    //! Draws the given data using glDrawElements() or via a callback if one has been set.
    static void drawElements(SoState* state, GLenum mode, GLsizei count,
                             GLenum type, const GLvoid * indices);

    enum internalMasks{
        OTHER_COLOR_MASK        = AMBIENT_MASK|EMISSIVE_MASK|SPECULAR_MASK|SHININESS_MASK,   
        ALL_COLOR_MASK          = OTHER_COLOR_MASK|DIFFUSE_MASK, 
        NO_COLOR_MASK           = ALL_MASK & (~ALL_COLOR_MASK), 
        ALL_BUT_DIFFUSE_MASK    =       ALL_MASK &(~ DIFFUSE_MASK), 
        DIFFUSE_ONLY_MASK       =  ALL_MASK &(~ OTHER_COLOR_MASK)
        };
   
  protected:

    //! method to tell the cache that a redundant set was issued.
    //! only the GL version does any work.               
    virtual void        registerRedundantSet(SoState *, uint32_t);
    
    //! method to register dependence due to get().  
    //! only the GL version does any work
    virtual void        registerGetDependence(SoState *, uint32_t);             
     
    //!Struct to hold the inventor state:
    struct ivStateStruct { 
        //!Keep nodeID to compare diffuse GL and diffuse inventor state:
        //!0 is initial value, 1 is invalid    
        SbNodeIdType          diffuseNodeId;
        
        //! for transparency, keep either nodeid, or 0 if opaque.  Value of
        //! 1 indicates invalid.
        SbNodeIdType          transpNodeId;
            
        //! store a value of each  color component; ambient, emissive,
        //! specular, shininess, or appropriate info to identify state.
        SbColor             ambientColor;
        SbColor             emissiveColor;
        SbColor             specularColor;
        float               shininess;
        bool                colorMaterial;
        bool                blending;
        int32_t             lightModel;
        int32_t             stippleNum;
        
        //! following are not used for matching GL & IV, but must
        //! be copied on push:   
        bool                packed;
        bool                packedTransparent;
        int32_t             numDiffuseColors;
        int32_t             numTransparencies;
        const SbColor       *diffuseColors;
        const float         *transparencies;
        const uint32_t      *packedColors;
        int32_t             transpType;
        uint32_t            cacheLevelSetBits;
        uint32_t            cacheLevelSendBits;
        bool                overrideBlending;

        bool                useVertexAttributes;

        SoDrawArraysCallback*   drawArraysCallback;
        void*                   drawArraysCallbackUserData;
        SoDrawElementsCallback* drawElementsCallback;
        void*                   drawElementsCallbackUserData;
    };

    ivStateStruct ivState;

    virtual ~SoLazyElement();
    
    //! This is more convenient here, but might logically be kept with
    //! SoGLLazyElement.  This is a bitmask indicating what components
    //! have not been sent to GL.
    uint32_t invalidBits;
 
  
    //!  store pointers to the default color, transp so that we can set
    //!  point to them if no other color or transp has been set.
    
    static SbColor      *defaultDiffuseColor;
    static float        *defaultTransparency;
    static uint32_t     *defaultPackedColor;
    
    //! Returns number of transparency levels supported with stipple
    //! patterns. (Add one - solid - that is not included in this number.)
    static int          getNumPatterns()        { return 64; }
    
    private:
        //! Virtual setElt methods, to be overridden by GL versions.  
    virtual void        setDiffuseElt(SoNode*,  int32_t numColors, 
        const SbColor *colors, SoColorPacker *cPacker);   
    virtual void        setPackedElt( SoNode *, int32_t numColors, 
        const uint32_t *colors);
    virtual void        setTranspElt(SoNode *, int32_t numTrans, 
        const float *trans, SoColorPacker *cPacker);
        
    virtual void        setTranspTypeElt(int32_t type);
    virtual void        setAmbientElt(const SbColor* color);
    virtual void        setEmissiveElt(const SbColor* color);
    virtual void        setSpecularElt(const SbColor* color);
    virtual void        setShininessElt(float value);
    virtual void        setColorMaterialElt(bool value);
    virtual void        setBlendingElt(bool value);
    virtual void        setLightModelElt(SoState *state, int32_t model);
    virtual void        setMaterialElt(SoNode *, uint32_t bitmask, 
        SoColorPacker *cPacker, const SoMFColor&, const SoMFFloat&, 
        const SoMFColor&, const SoMFColor&, const SoMFColor&, const SoMFFloat&);

};

////////////////////////////////////////////////////////////////////////////
///
////  \class SoColorPacker
/// This class is meant to be used by all property nodes that set either
/// a diffuse color or transparency in the lazy element.  It maintains
/// a cache of the current diffuse color and transparency in a packed
/// color array.
//////////////////////////////////////////////////////////////////////////

class INVENTOR_API SoColorPacker {
    public:
    //!Constructor, makes a colorPacker with NULL packedColor pointer:
    SoColorPacker();
    
     //! destructor, deletes packed color array
    ~SoColorPacker();
    
    uint32_t* getPackedColors() const
    { return packedColors;}
    
    bool diffuseMatch(SbNodeIdType nodeId)
    { return (nodeId == diffuseNodeId);}
    
    bool transpMatch(SbNodeIdType nodeId)
    { return (nodeId == transpNodeId);}
    
    void setNodeIds(SbNodeIdType diffNodeId, SbNodeIdType tNodeId)
    {diffuseNodeId = diffNodeId; transpNodeId = tNodeId;}

    int32_t getSize()
    { return packedArraySize;}
    
    void reallocate(int32_t size);
    
    private:
    //! nodeids are used for testing cache validity
    SbNodeIdType    transpNodeId;
    SbNodeIdType    diffuseNodeId;
    //! array of packed colors, or NULL if empty
    uint32_t*   packedColors;
    //! size of packed color array (not necessarily number of valid colors)
    int32_t     packedArraySize;
};
    

#endif /* _SO_LAZY_ELEMENT */

