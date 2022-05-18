/*
*
*  Copyright (C) 2011 MeVis Medical Solutions AG  All Rights Reserved.
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
*  Contact information: MeVis, Center for Medical Diagnostic Systems and
*  Visualization GmbH, Universitätsallee 29, D-28359 Bremen, GERMANY, or:
*
*  http://www.mevis.de
*
*/

/*
 Author: Florian Link
 Date:   09-2011
*/

#ifndef _SO_GL_VBO_ELEMENT_
#define _SO_GL_VBO_ELEMENT_

#include <Inventor/system/SbSystem.h>
#include <Inventor/elements/SoSubElement.h>
#include <Inventor/misc/SoVBO.h>
#include <Inventor/SoMachine.h>

//! Manage the currently registered VBOs in the state (for coordinates, normals, colors and tex coords)
//! (MeVis ONLY)
SoEXTENDER class INVENTOR_API SoGLVBOElement : public SoElement
{
  typedef SoElement inherited;

  SO_ELEMENT_HEADER(SoGLVBOElement);

public:
  enum VBOType {
    VERTEX_VBO = 0,
    NORMAL_VBO = 1,
    COLOR_VBO  = 2,
    TEXCOORD_VBO = 3,
    MAX_VBO_TYPES = 4
  };

  virtual void      init(SoState *state);
  virtual void      push(SoState *state);
  virtual void      pop(SoState *state, const SoElement *childElt);

  //! get const instance
  static const SoGLVBOElement*   getInstance(SoState* state);

  //! remove the given VBO from element
  static void unsetVBO(SoState* state, VBOType type);
  //! remove the given VBO from element if the element is enabled in state.
  static void unsetVBOIfEnabled(SoState* state, VBOType type);

  //! creates or clear a VBO of given type. Passing the data in is optional and may be done later on
  //! the allocated vbo. The ownership of the VBO is passed to the called.
  static void updateVBO(SoState* state, VBOType type, SoVBO** vbo, int numBytes = 0, const void* data = NULL, SbNodeIdType nodeId = 0);

  //! get a vbo
  SoVBO* getVBO(VBOType type) const;

  bool              matches(const SoElement *elt) const;
  SoElement*        copyMatchInfo() const;

protected:

  //! Destructor.
  virtual           ~SoGLVBOElement();

SoINTERNAL public:

  //! Initializes the SoGLVBOElement class.
  static void       initClass();

private:
  SoVBO* _vbo[MAX_VBO_TYPES];

};

#endif  // _SO_GL_VBO_ELEMENT_
