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

#ifndef _SO_VBO_
#define _SO_VBO_

#include <Inventor/SbBasic.h>
#include <Inventor/system/SbOpenGL.h>

class SoState;
class SoGLDisplayList;

//! SoVBO is used to manage OpenGL vertex buffer objects.
//! Note that the creation of a real OpenGL VBO is deferred until bind() is
//! called, so that the VBO is created lazily.
//! (MeVis ONLY)
class INVENTOR_API SoVBO
{
public:
  //! create VBO of type GL_ARRAY_BUFFER (for vertex/normal/color etc. data) or GL_ELEMENT_ARRAY_BUFFER for index data
  SoVBO(GLenum type);
  ~SoVBO();

  //! returns if a VBO should be used depending on given state and the number of data elements (not bytes)
  static bool shouldUseVBO(SoState* state, int numData);

  //! returns of vertex array rendering is allowed. Default is true, this can be disabled by setting
  //! the IV_NO_VERTEX_ARRAY environment variable. 
  static bool isVertexArrayRenderingAllowed();

  //! bind the buffer to GL, transfer data if not already done.
  //! Returns true if the VBO could be bound and false otherwise.
  //! If the bind call fails, this typically means an out of memory condition
  //! because the VBO does not fit on the graphics board.
  bool bind(SoState* state);

  //! unbind the VBO in the GL state
  void unbind();

  //! Returns if the VBO is valid and it's data is stored on the GPU.
  bool isValid(SoState* state);

  //! sets the client buffer data, ownership stays with the caller
  void setData(int numBytes, const void* data, SbNodeIdType nodeId, SoState* state);

  //! get the node id of the data
  SbNodeIdType getDataId() const { return _nodeId; }

  //! clears the data, freeing it when it is owned by VBO
  void clearData();

  //! get the data pointer
  const void* getData() const { return _data; }

  //! free the GL part of the VBO (if state is passed, the VBO may be deleted immediately)
  void freeGL(SoState* state = NULL);

  //! returns if the stored data has been swapped to be compatible to OpenGL on little endian machines
  bool hasSwappedRGBAData() const { return _hasSwappedRGBAData; }

  //! allocates new data buffer, copies the values set by setData() and swaps them bytewise, needed for little endian machines
  //! sets hasSwappedRGBAData() flag
  void copyAndSwapPackedRGBA(SoState* state);

  //! get the lower limit for VBO usage
  static int getVboMinimumSizeLimit() { return _vboMinimumSizeLimit; }

  //! update the VBO data from the current data (bind() needs to be called before).
  void updateData(void* data);

private:
  //! allocates the client buffer data, data is owned by VBO
  void allocateData(int numBytes, SbNodeIdType nodeId, SoState* state);

  //! allocates new data buffer, copies the given values and swaps them bytewise, needed for little endian machines
  //! sets hasSwappedRGBAData() flag
  void copyAndSwapPackedRGBA(int numValues, const uint32_t* values, SbNodeIdType nodeId, SoState* state);

  GLenum _type;

  const void* _data;
  int      _numBytes;
  SbNodeIdType _nodeId;

  SoGLDisplayList* _glBuffer;

  bool _ownsData;
  bool _hasSwappedRGBAData;
  bool _hadGLError;

  static int _vboMinimumSizeLimit;
  static int _vboMaximumSizeLimit;
};

#endif
