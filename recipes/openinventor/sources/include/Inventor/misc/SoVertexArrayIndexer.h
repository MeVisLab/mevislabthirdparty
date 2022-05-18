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

#ifndef _SO_VERTEX_ARRAY_INDEXER_
#define _SO_VERTEX_ARRAY_INDEXER_

#include <Inventor/SbBasic.h>
#include <Inventor/system/SbOpenGL.h>
#include <Inventor/misc/SoVBO.h>

class SoState;
class SoGLDisplayList;

//! SoVertexArrayIndexer is a class that manages rendering of indexed primitives using
//! Vertex Array rendering. The indices can optionally be cached in a VBO, so that they
//! do not need to be send on each render call.
//! This class is mainly needed because the OIV index structures typically contain
//! -1 as marker for the end of each primitive, which is undesired for sending indices to
//! OpenGL. Currently a single indexer only manages the kind of primitives that are passed
//! in the constructor.
//! (MeVis ONLY)
class INVENTOR_API SoVertexArrayIndexer
{
public:
  //! create vertex array indexer for given GL primitives (GL_LINES, GL_TRIANGLES, GL_QUADS, ...)
  SoVertexArrayIndexer(GLenum type);
  ~SoVertexArrayIndexer();

  //! set the type
  void setType(GLenum type) { _type = type; }

  //! get the type
  GLenum getType() const { return _type; }

  //! frees the allocated data
  void clear();

  //! free the GL part of the SoVertexArrayIndexer (if state is passed, the VBO may be deleted immediately)
  void freeGL(SoState* state = NULL);

  //! render the primitives (uses a VBO if useVbo is passed in)
  void render(SoState* state, bool useVbo);

  //! get the node id of the data
  SbNodeIdType getDataId() const { return _nodeId; }

  //! set the triangles from inventor (3 indices separated by -1), does an internal copy without -1
  void setInventorTriangles(int numTriangles, const int32_t* inventorIndices, SbNodeIdType nodeId);

  //! set the triangles from inventor (4 indices separated by -1), does an internal copy without -1
  void setInventorQuads(int numQuads, const int32_t* inventorIndices, SbNodeIdType nodeId);

  //! set the triangles from inventor (2 indices separated by -1), does an internal copy without -1
  void setInventorLines(int numLines, const int32_t* inventorIndices, SbNodeIdType nodeId);

  //! set the indices, the ownership stays with the caller and the caller has to make sure
  //! that the indices still live when further methods of this instance are called.
  void setIndices(int numIndices, const int32_t* indices, SbNodeIdType nodeId );

private:
  GLenum _type;

  SbNodeIdType _nodeId;

  bool     _ownsIndices;
  int      _numIndices;
  GLuint*  _indices;
  
  SoVBO* _indexVbo;
};

#endif
