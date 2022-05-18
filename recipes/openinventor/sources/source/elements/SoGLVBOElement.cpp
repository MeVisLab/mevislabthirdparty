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

#include <Inventor/elements/SoGLVBOElement.h>
#include <Inventor/system/SbOpenGL.h>

SO_ELEMENT_SOURCE(SoGLVBOElement);

SoGLVBOElement::~SoGLVBOElement()
{
}

void
SoGLVBOElement::initClass()
{
   SO_ELEMENT_INIT_CLASS(SoGLVBOElement, inherited);
}

void
SoGLVBOElement::init(SoState *state)
{
   inherited::init(state);
   
   for (int i = 0;i<MAX_VBO_TYPES; i++) {
     _vbo[i] = NULL;
   }
}

void
SoGLVBOElement::push(SoState *state)
{
   const SoGLVBOElement *prevElt = (const SoGLVBOElement*)getNextInStack();

   for (int i = 0;i<MAX_VBO_TYPES; i++) {
     _vbo[i] = prevElt->_vbo[i];
   }
}

void
SoGLVBOElement::pop(SoState * /*state*/, const SoElement * /*childElt*/)
{
  // no need to pop anything
}

bool SoGLVBOElement::matches( const SoElement *elt ) const
{
  // should not be called
  return TRUE;
}

SoElement* SoGLVBOElement::copyMatchInfo() const
{
  // should not be called
  return NULL;
}

const SoGLVBOElement* SoGLVBOElement::getInstance( SoState* state )
{
  return (const SoGLVBOElement*) state->getConstElement(classStackIndex);
}

void SoGLVBOElement::updateVBO( SoState* state, VBOType type, SoVBO** vbo, int numBytes /*= 0*/, const void* data /*= NULL*/, SbNodeIdType nodeId /*= 0*/ )
{
  // we always create/store a VBO object, since we may even use it for vertex array rendering
  // and we do not know if the user desires VBO usage or not in here...
  SoGLVBOElement* element = (SoGLVBOElement*) state->getElement(classStackIndex);
  if (!(*vbo)) {
    *vbo = new SoVBO(GL_ARRAY_BUFFER);
  }
  element->_vbo[type] = *vbo;
  if (numBytes!=0) {
    // store data and node id
    (*vbo)->setData(numBytes, data, nodeId, state);
  }
}

void SoGLVBOElement::unsetVBO( SoState* state, VBOType type )
{
  SoGLVBOElement* element = (SoGLVBOElement*) state->getElement(classStackIndex);
  element->_vbo[type] = NULL;
}

void SoGLVBOElement::unsetVBOIfEnabled( SoState* state, VBOType type )
{
  if (state->isElementEnabled(classStackIndex)) {
    SoGLVBOElement* element = (SoGLVBOElement*) state->getElement(classStackIndex);
    element->_vbo[type] = NULL;
  }
}

SoVBO* SoGLVBOElement::getVBO( VBOType type ) const
{
  return _vbo[type];
}