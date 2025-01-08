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
 |      This file defines the SoText3 node class.
 |
 |   Author(s)          : Gavin Bell
 |
 ______________  S I L I C O N   G R A P H I C S   I N C .  ____________
 _______________________________________________________________________
 */

#ifndef  _SO_TEXT_3_
#define  _SO_TEXT_3_

#include <Inventor/SbBox.h>
#include <Inventor/fields/SoMFString.h>
#include <Inventor/fields/SoSFEnum.h>
#include <Inventor/fields/SoSFBitMask.h>
#include <Inventor/fields/SoSFFloat.h>
#include <Inventor/nodes/SoShape.h>

#include <Inventor/system/SbOpenGL.h>   // For GLenum declaration


//!  GLU Library version dependency.
#ifndef gluTESSELATOR
#define gluTESSELATOR  GLUtriangulatorObj
#if defined(__glu_h__) && defined(GLU_VERSION_1_2)
#define gluTESSELATOR  GLUtesselator
#else
extern "C" struct GLUtriangulatorObj;
#endif
#endif



class SoOutlineFontCache;
class SoPrimitiveVertex;
class SoTextureCoordinateElement;

////////////////////////////////////////////////////////////////////////////////
//! 3D text shape node.
/*!
\class SoText3
\ingroup Nodes
This node defines one or more strings of 3D text. In contrast with
SoText2, 3D text can be rotated, scaled, lighted, and textured,
just like all other 3D shapes. Each character in a 3D text string is
created by extruding an outlined version of the character (in the
current typeface) along the current profile, as defined by nodes
derived from SoProfile. The default text profile, if none is
specified, is a straight line segment one unit long.


The text origin is at (0,0,0) after applying the current
transformation. The scale of the text is affected by the \b size 
field of the current SoFont as well as the current transformation.


SoText3 uses the current set of materials when rendering. If the
material binding is <tt>OVERALL</tt>, then the whole text is drawn with the
first material. If it is <tt>PER_PART</tt> or <tt>PER_PART_INDEXED</tt>, the
front part of the text is drawn with the first material, the sides
with the second, and the back with the third.


Textures are applied to 3D text as follows.  On the front and back
faces of the text, the texture origin is at the base point of the
first string; the base point is at the lower left for justification
<tt>LEFT</tt>, at the lower right for <tt>RIGHT</tt>, and at the lower center
for <tt>CENTER</tt>. The texture is scaled equally in both S and T
dimensions, with the font height representing 1 unit. S increases to
the right on the front faces and to the left on the back faces. On the
sides, the texture is scaled the same as on the front and back. S is
equal to 0 at the rear edge of the side faces. The T origin can occur
anywhere along each character, depending on how that character's
outline is defined.

\par File Format/Default
\par
\code
Text3 {
  string ""
  spacing 1
  justification LEFT
  parts FRONT
}
\endcode

\par Action Behavior
\par
SoGLRenderAction
<BR> Draws text based on the current font, profiles, transformation, drawing style, material, texture, complexity, and so on. 
\par
SoRayPickAction
<BR> Performs a pick on the text. The string index and character position are available from the SoTextDetail. 
\par
SoGetBoundingBoxAction
<BR> Computes the bounding box that encloses the text. 
\par
SoCallbackAction
<BR> If any triangle callbacks are registered with the action, they will be invoked for each successive triangle used to approximate the text geometry. 

\par See Also
\par
SoFont, SoProfile, SoText2, SoTextDetail
*/
////////////////////////////////////////////////////////////////////////////////

class INVENTOR_API SoText3 : public SoShape {

    SO_NODE_HEADER(SoText3);

  public:
    //! Justification types
    enum Justification {
        LEFT    = 0x01,
        RIGHT   = 0x02,
        CENTER  = 0x03
    };

    //! Justification types
    enum Part {
        FRONT   = 0x01,
        SIDES   = 0x02,
        BACK    = 0x04,
        ALL     = 0x07
    };

    //! \name Fields
    //@{

    //! The text string(s) to display. Each string will appear on its own line.
    //! The string(s) can be ascii or UTF-8.
    SoMFString          string;         

    //! Defines the distance (in the negative y direction) between the base
    //! points of successive strings, measured with respect to the current
    //! font height. A value of 1 indicates single spacing, a value of 2
    //! indicates double spacing, and so on.
    SoSFFloat           spacing;        

    //! Which parts of text are visible. Note that, for speed, the default for
    //! this field is <tt>FRONT</tt> only.
    SoSFBitMask         parts;          

    //! Indicates placement and alignment of strings. With <tt>LEFT</tt>
    //! justification, the left edge of the first line is at the (transformed)
    //! origin, and all left edges are aligned. <tt>RIGHT</tt> justification is
    //! similar.  <tt>CENTER</tt> justification places the center of the first
    //! string at the (transformed) origin, with the centers of all remaining
    //! strings aligned under it.
    SoSFEnum            justification;

    //@}

    //! Creates a 3D text node with default settings.
    SoText3();

  SoEXTENDER public:

    //! Method to get the bounds of the given character in the given
    //! string.  This must be called during the application of an
    //! action; use a callbackAction applied to a Path to the text node
    //! if you have to (this is really designed to be used in a Text3
    //! manipulator, which will have direct access to the state).
    //! The bounds are based on the font metric information, not the
    //! geometric bounding box of the character.  So, for example,
    //! while a space character has an empty bounding box,
    //! getCharacterBounds() will return a box as high as the font
    //! height, as wide as a space, and as deep as the profile.
    SbBox3f             getCharacterBounds(SoState *state,
                                int stringIndex, int charIndex);

    virtual void        GLRender(SoGLRenderAction *action);
    virtual void        rayPick(SoRayPickAction *action);

  SoINTERNAL public:
    static void         initClass();

  protected:
    //! Computes bounding box of text
    virtual void        computeBBox(SoAction *action, SbBox3f &box,
                                    SbVec3f &center);

    //! Generates primitives
    virtual void        generatePrimitives(SoAction *);
    
    virtual ~SoText3();

  private:
    //! Setup the internal font cache
    bool setupFontCache(SoState *state, bool forRender = FALSE);

    //! Return bounding box of the fronts of all characters.
    void getFrontBBox(SbBox2f &result);

    //! Figure out how much each line of text is offset (based on width
    //! of characters and justification)
    SbVec2f getStringOffset(int line);
    
    //! Figure out where a particular character in a particular line
    //! starts:
    SbVec2f getCharacterOffset(int line, int whichChar);

    //! Render the fronts of the characters
    void renderFront(SoGLRenderAction *action, int line,
                     GLUtriangulatorObj *tobj);
    
    //! Render the sides of the characters
    void renderSide(SoGLRenderAction *action, int line);

    //! Creates a text detail when picking:
    SoDetail * createTriangleDetail(SoRayPickAction *,
                                    const SoPrimitiveVertex *,
                                    const SoPrimitiveVertex *,
                                    const SoPrimitiveVertex *,
                                    SoPickedPoint *);

    //! Generates the fronts of the characters, by getting the outlines
    //! and calling the glu tessellation code:
    void generateFront(int line);
    
    //! Generates the sides (bevel) of the characters
    void generateSide(int line);

    //! Callback functions, so the same routines (inside the internal
    //! SoOutlineFontCache class) can be used to generate primitives
    //! and render.
    static void generateSideTris(int nPoints, const SbVec3f *p1,
                const SbVec3f *n1, const SbVec3f *p2,
                const SbVec3f *n2, const float *sTexCoords,
                const float *tTexCoords);
    static void renderSideTris(int nPoints, const SbVec3f *p1,
                const SbVec3f *n1, const SbVec3f *p2,
                const SbVec3f *n2, const float *sTexCoords,
                const float *tTexCoords);

    //! Static callbacks invoked by the glu tessellation code:
    static void CALLBACK beginCB(GLenum primType);
    static void CALLBACK endCB();
    static void CALLBACK vtxCB(void *vertex);
    
    //! Private data:
    //! SoOutlineFontCache is an internal, opaque class used to
    //! maintain gl display lists and other information for each
    //! character in a font.
    SoOutlineFontCache *myFont;

    //! All this stuff is used while generating primitives:
    static SoText3 *currentGeneratingNode;
    static SoPrimitiveVertex *genPrimVerts[3];
    static SbVec3f genTranslate;
    static int genWhichVertex;
    static uint32_t genPrimType;
    static SoAction *genAction;
    static bool genBack;
    static bool genTexCoord;
    static const SoTextureCoordinateElement *tce;
};

#endif /* _SO_TEXT_3_ */
