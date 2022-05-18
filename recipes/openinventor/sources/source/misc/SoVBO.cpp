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

#include <Inventor/misc/SoVBO.h>
#include <Inventor/misc/SoState.h>
#include <Inventor/elements/SoGLCacheContextElement.h>
#include <Inventor/elements/SoShapeHintsElement.h>
#include <stdlib.h>

int SoVBO::_vboMinimumSizeLimit = 20;
int SoVBO::_vboMaximumSizeLimit = 0x10000000;

bool SoVBO::isVertexArrayRenderingAllowed()
{
  static bool isVARenderingAllowed = (getenv("IV_NO_VERTEX_ARRAY")==NULL);
  return isVARenderingAllowed;
}

bool SoVBO::shouldUseVBO( SoState* state , int numData )
{
  static bool isVBORenderingAllowed = (getenv("IV_NO_VBO")==NULL);

  bool result = isVBORenderingAllowed && (GLEW_VERSION_1_5 || GLEW_ARB_vertex_buffer_object) && (numData > _vboMinimumSizeLimit) && (numData < _vboMaximumSizeLimit);
  if (state) {
    result = result && SoShapeHintsElement::isVBOUsed(state);
  }
  return result;
}

SoVBO::SoVBO( GLenum type )
{
  _type = type;
  _ownsData = false;
  _numBytes = 0;
  _data = NULL;
  _nodeId = 0;
  _glBuffer = NULL;
  _hasSwappedRGBAData = false;
  _hadGLError = false;
}

SoVBO::~SoVBO()
{
  clearData();
  freeGL();
}

void SoVBO::setData(int numBytes, const void* data, SbNodeIdType nodeId, SoState* state)
{
  // free previous data if it was owned
  if (_ownsData && _data) {
    free((void*)_data);
  }
  if (nodeId != _nodeId) {
    freeGL(state);
  }

  _numBytes = numBytes;
  _data = data;
  _nodeId = nodeId;
  _ownsData = false;
  _hasSwappedRGBAData = false;
}

void SoVBO::allocateData( int numBytes, SbNodeIdType nodeId , SoState* state)
{
  if (_ownsData && _data) {
    free((void*)_data);
  }
  freeGL(state);

  _numBytes = numBytes;
  _data = malloc(numBytes);
  _nodeId = nodeId;
  _ownsData = true;
  _hasSwappedRGBAData = false;
}

void SoVBO::clearData()
{
  if (_ownsData && _data) {
    free((void*)_data);
  }
  _data = NULL;
  _numBytes = 0;
  _ownsData = false;
  _hasSwappedRGBAData = false;
}

void SoVBO::copyAndSwapPackedRGBA( int numValues, const uint32_t* values, SbNodeIdType nodeId, SoState* state )
{
  allocateData(numValues * sizeof(uint32_t), nodeId, state);

  _hasSwappedRGBAData = true;

  uint32_t* dest = (uint32_t*)_data; 
  for (int i = 0; i < numValues; i++) {
    uint32_t value = values[i];
    dest[i] = 
      (value << 24) |
      ((value & 0xff00) << 8) |
      ((value & 0xff0000) >> 8) |
      (value >> 24);
  }
}

void SoVBO::copyAndSwapPackedRGBA( SoState* state )
{
  copyAndSwapPackedRGBA(_numBytes/4, (const uint32_t*)_data, _nodeId, state);
}

void SoVBO::freeGL(SoState* state)
{
  if (_glBuffer) {
    _glBuffer->unref(state);
    _glBuffer = NULL;
  }
}

bool SoVBO::bind(SoState* state)
{
  if (!isValid(state)) {
    if (_glBuffer) {
      _glBuffer->unref(state);
    }
    // clear GL error state to avoid getting errors from someone else
    glGetError();

    _glBuffer = new SoGLDisplayList(state, SoGLDisplayList::VERTEX_BUFFER_OBJECT);
    _glBuffer->ref();
    glBindBufferARB(_type, _glBuffer->getFirstIndex());
    glBufferDataARB(_type, _numBytes, _data, GL_STATIC_DRAW);
    _hadGLError = (glGetError() != GL_NO_ERROR);
    if (_hadGLError) {
      // unbind after error
      glBindBufferARB(_type, 0);
    }
  } else {
    if (!_hadGLError) {
      // data is still there, just bind it
      glBindBufferARB(_type, _glBuffer->getFirstIndex());
    } else {
      // unbind previous vbo
      glBindBufferARB(_type, 0);
    }
  }
  return !_hadGLError;
}

void SoVBO::unbind()
{
  glBindBufferARB(_type, 0);
}

void SoVBO::updateData( void* data )
{
  glBufferSubDataARB(_type, 0, _numBytes, data);
}

bool SoVBO::isValid(SoState* state)
{
  return (_glBuffer && SoGLCacheContextElement::get(state)==_glBuffer->getContext());
}
