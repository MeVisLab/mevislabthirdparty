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
 |      This file defines the SoGLDrawStyleElement class.
 |
 |   Author(s)          : Paul S. Strauss
 |
 ______________  S I L I C O N   G R A P H I C S   I N C .  ____________
 _______________________________________________________________________
 */

#ifndef  _SO_GL_DRAW_STYLE_ELEMENT
#define  _SO_GL_DRAW_STYLE_ELEMENT

#include <Inventor/elements/SoDrawStyleElement.h>

///////////////////////////////////////////////////////////////////////////////
///
///  \class SoGLDrawStyleElement
///  \ingroup Elements
///
///  Element that changes the current draw style in GL. Overrides the
///  virtual methods on SoDrawStyleElement to send the draw style to GL
///  when necessary.
///
///  Note that this class relies on SoDrawStyleElement to store the
///  style in the instance.
///
///  Also note that this tells GL only how to draw polygons. Shapes
///  that contain lines still have to check for POINTS draw styles and
///  act accordingly.
///
//////////////////////////////////////////////////////////////////////////////

SoEXTENDER class INVENTOR_API SoGLDrawStyleElement : public SoDrawStyleElement {

    SO_ELEMENT_HEADER(SoGLDrawStyleElement);

  public:
    //! Initializes element
    virtual void        init(SoState *state);

    //! Override push() so we can remember the previous element's draw
    //! style, and perhaps avoid sending unnecessary GL calls if this
    //! element is the same.
    virtual void        push(SoState *state);

    //! Override pop() method so side effects can occur in GL
    virtual void        pop(SoState *state, const SoElement *prevTopElement);

  SoINTERNAL public:
    //! Initializes the SoGLDrawStyleElement class
    static void         initClass();

  protected:
    //! Sets the draw style in an instance. Has GL side effects.
    virtual void        setElt(int32_t style);

    virtual ~SoGLDrawStyleElement();

  private:
    //! We save the state to figure out if the lastPattern variable was
    //! copied from a parent element; if it was, then caches will have
    //! to depend on that element because if it changes we have to have
    //! a chance to change our decision about what GL calls to make.
    //! If this is NULL, then there are no cache dependencies.
    SoState *           copiedFromParent;

    //! Sends draw style in element to GL
    void                send();
};

#endif /* _SO_GL_DRAW_STYLE_ELEMENT */
