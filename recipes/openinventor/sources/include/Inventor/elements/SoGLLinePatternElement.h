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
 |      This file defines the SoGLLinePatternElement class.
 |
 |   Author(s)          : Paul S. Strauss
 |
 ______________  S I L I C O N   G R A P H I C S   I N C .  ____________
 _______________________________________________________________________
 */

#ifndef  _SO_GL_LINE_PATTERN_ELEMENT
#define  _SO_GL_LINE_PATTERN_ELEMENT

#include <Inventor/elements/SoLinePatternElement.h>

///////////////////////////////////////////////////////////////////////////////
///
///  \class SoGLLinePatternElement
///  \ingroup Elements
///
///  Element that stores the current line pattern in GL. Overrides the
///  virtual methods on SoLinePatternElement to send the line pattern
///  to GL when necessary.
///
///  Note that this class relies on SoLinePatternElement to store the
///  pattern in the instance.
///
//////////////////////////////////////////////////////////////////////////////

SoEXTENDER class INVENTOR_API SoGLLinePatternElement : public SoLinePatternElement {

    SO_ELEMENT_HEADER(SoGLLinePatternElement);

  public:
    //! Initializes element
    virtual void        init(SoState *state);

    //! Override push() so we can remember what line pattern the
    //! previous element set, and not send it again if it is the same.
    virtual void        push(SoState *state);

    //! Override pop() method so side effects can occur in GL
    virtual void        pop(SoState *state, const SoElement *prevTopElement);

  SoINTERNAL public:
    //! Initializes the SoGLLinePatternElement class
    static void         initClass();

  protected:
    //! Sets the line pattern in an instance. Has GL side effects.
    virtual void        setElt(int32_t pattern);

    virtual ~SoGLLinePatternElement();

  private:
    //! We save the state to figure out if the lastPattern variable was
    //! copied from a parent element; if it was, then caches will have
    //! to depend on that element because if it changes we have to have
    //! a chance to change our decision about what GL calls to make.
    //! If this is NULL, then there are no cache dependencies.
    SoState *           copiedFromParent;

    //! Sends line pattern in element to GL
    void                send();
};

#endif /* _SO_GL_LINE_PATTERN_ELEMENT */
