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
 |      This file defines the SoText2 node class.
 |
 |   Author(s)          : Thad Beier
 |
 ______________  S I L I C O N   G R A P H I C S   I N C .  ____________
 _______________________________________________________________________
 */

#ifndef _SO_TEXT_2_
#define _SO_TEXT_2_

#include <Inventor/fields/SoMFString.h>
#include <Inventor/fields/SoSFEnum.h>
#include <Inventor/fields/SoSFFloat.h>
#include <Inventor/nodes/SoShape.h>
#include <Inventor/system/SbSystem.h>

class SoBitmapFontCache; //!< Internal class


////////////////////////////////////////////////////////////////////////////////
//! Screen-aligned 2D text shape node.
/*!
\class SoText2
\ingroup Nodes
This node defines one or more strings of 2D text. The text is always
aligned horizontally with the screen and does not change size with
distance in a perspective projection. The text origin is at (0,0,0)
after applying the current transformation. Rotations and scales have
no effect on the orientation or size of 2D text, just the location.


SoText2 uses the current font to determine the typeface and size.
The text is always drawn with the diffuse color of the current
material; it is not lit, regardless of the lighting model.
Furthermore, 2D text can not be textured, and it ignores the current
drawing style and complexity.


Because 2D text is screen-aligned, it has some unusual
characteristics.  For example, the 3D bounding box surrounding a 2D
text string depends on the current camera and the current viewport
size, since changing the field of view or the mapping onto the window
changes the relative size of the text with respect to the rest of the
scene. This has implications for caching as well, since a render cache
in an SoSeparator that contains an SoText2 node depends on the
current camera.

\par File Format/Default
\par
\code
Text2 {
  string ""
  spacing 1
  justification LEFT
}
\endcode

\par Action Behavior
\par
SoGLRenderAction
<BR> Draws text based on the current font, at a location based on the current transformation.
\par
SoRayPickAction
<BR> Performs a pick on the text. Text will be picked if the picking ray intersects the bounding box
of the strings. The string index and character position are available from the SoTextDetail. \par
SoGetBoundingBoxAction
<BR> Computes the bounding box that encloses the text.

\par See Also
\par
SoFont, SoText3, SoTextDetail
*/
////////////////////////////////////////////////////////////////////////////////

class INVENTOR_API SoText2 : public SoShape
{

  SO_NODE_HEADER(SoText2);

public:
  //! Justification types
  enum Justification
  {
    LEFT = 0x01,
    RIGHT = 0x02,
    CENTER = 0x03
  };

  //! \name Fields
  //@{

  //! The text string(s) to display. Each string will appear on its own line.
  //! The string(s) can be ascii or UTF-8.
  SoMFString string;

  //! Defines the distance (in the negative y direction) between the base
  //! points of successive strings, measured with respect to the current
  //! font height. A value of 1 indicates single spacing, a value of 2
  //! indicates double spacing, and so on.
  SoSFFloat spacing;

  //! Indicates placement and alignment of strings. With <tt>LEFT</tt>
  //! justification, the left edge of the first line is at the (transformed)
  //! origin, and all left edges are aligned. <tt>RIGHT</tt> justification is
  //! similar. <tt>CENTER</tt> justification places the center of the first
  //! string at the (transformed) origin, with the centers of all remaining
  //! strings aligned under it.
  SoSFEnum justification;

  //@}

  //! Creates a 2D text node with default settings.
  SoText2();

  SoEXTENDER public : virtual void GLRender(SoGLRenderAction *action);
  virtual void rayPick(SoRayPickAction *action);

  SoINTERNAL public : static void initClass();

protected:
  //! This method is a no-op for SoText2, since there are no
  //! primitives it can generate
  virtual void generatePrimitives(SoAction *action);

  //! Computes bounding box of text
  virtual void computeBBox(SoAction *action, SbBox3f &box, SbVec3f &center);

  virtual ~SoText2();

private:
  //! Based on justification and line spacing, this returns the
  //! offset (in pixels) for one of the lines of text.
  SbVec3f getPixelStringOffset(int whichLine);

  //! Internal class that allows Text2 nodes to share font
  //! information, GL display lists, etc.
  SoBitmapFontCache *myFont;
};

#endif /* _SO_TEXT_2_ */
