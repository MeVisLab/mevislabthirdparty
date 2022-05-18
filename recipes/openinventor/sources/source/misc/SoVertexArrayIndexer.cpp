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

#include <Inventor/misc/SoVertexArrayIndexer.h>
#include <Inventor/elements/SoGLLazyElement.h>

SoVertexArrayIndexer::SoVertexArrayIndexer( GLenum type )
{
  _type = type;
  _nodeId = 0;
  _indexVbo = NULL;
  _indices = NULL;
  _numIndices = 0;
  _ownsIndices = false;
}

SoVertexArrayIndexer::~SoVertexArrayIndexer()
{
  clear();
  if (_indexVbo) {
    delete _indexVbo;
  }
}

void SoVertexArrayIndexer::clear()
{
  if (_indices && _ownsIndices) {
    delete[] _indices;
  }
  _indices = NULL;
  _numIndices = 0;
  _nodeId = 0;
  _ownsIndices = false;
}

void SoVertexArrayIndexer::freeGL(SoState* state)
{
  if (_indexVbo) {
    _indexVbo->freeGL(state);
  }
}

void SoVertexArrayIndexer::render(SoState* state, bool useVbo)
{
  void* dataPtr = _indices;
  if (useVbo) {
    if (!_indexVbo) {
      _indexVbo = new SoVBO(GL_ELEMENT_ARRAY_BUFFER);
    }
    _indexVbo->setData(_numIndices*sizeof(uint32_t), _indices, _nodeId, state);
    if (_indexVbo->bind(state)) {
      // if the VBO could be bound, use it.
      dataPtr = NULL;
    }
  }
  
  SoGLLazyElement::drawElements(state, _type, _numIndices, GL_UNSIGNED_INT, dataPtr);

  if (useVbo) {
    // unbind the VBO
    _indexVbo->unbind();
  }
}

void SoVertexArrayIndexer::setInventorTriangles( int numTriangles, const int32_t* inventorIndices, SbNodeIdType nodeId )
{
  clear();
  _ownsIndices = true;
  _nodeId = nodeId;
  _numIndices = numTriangles*3;
  _indices = new GLuint[_numIndices];
  GLuint* ptr = _indices;
  const int32_t* oivIndices = inventorIndices;
  for (int i=0; i < numTriangles; i++) {
    *ptr++ = *oivIndices++;
    *ptr++ = *oivIndices++;
    *ptr++ = *oivIndices++;
    // skip the -1
    oivIndices++;
  }
}

void SoVertexArrayIndexer::setInventorQuads( int numQuads, const int32_t* inventorIndices, SbNodeIdType nodeId )
{
  clear();
  _ownsIndices = true;
  _nodeId = nodeId;
  _numIndices = numQuads*4;
  _indices = new GLuint[_numIndices];
  GLuint* ptr = _indices;
  const int32_t* oivIndices = inventorIndices;
  for (int i=0; i < numQuads; i++) {
    *ptr++ = *oivIndices++;
    *ptr++ = *oivIndices++;
    *ptr++ = *oivIndices++;
    *ptr++ = *oivIndices++;
    // skip the -1
    oivIndices++;
  }
}

void SoVertexArrayIndexer::setInventorLines( int numLines, const int32_t* inventorIndices, SbNodeIdType nodeId )
{
  clear();
  _ownsIndices = true;
  _nodeId = nodeId;
  _numIndices = numLines*2;
  _indices = new GLuint[_numIndices];
  GLuint* ptr = _indices;
  const int32_t* oivIndices = inventorIndices;
  for (int i=0; i < numLines; i++) {
    *ptr++ = *oivIndices++;
    *ptr++ = *oivIndices++;
    // skip the -1
    oivIndices++;
  }
}

void SoVertexArrayIndexer::setIndices(int numIndices, const int32_t* indices, SbNodeIdType nodeId )
{
  clear();
  _ownsIndices = false;
  _nodeId = nodeId;
  _numIndices = numIndices;
  _indices = (uint32_t*)indices;
}
