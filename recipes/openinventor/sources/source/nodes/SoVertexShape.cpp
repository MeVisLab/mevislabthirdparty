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
 |   Classes:
 |      SoVertexShape
 |
 |   Author(s)          : Paul S. Strauss
 |
 ______________  S I L I C O N   G R A P H I C S   I N C .  ____________
 _______________________________________________________________________
 */

#include <Inventor/caches/SoNormalCache.h>
#include <Inventor/elements/SoCoordinateElement.h>
#include <Inventor/elements/SoCreaseAngleElement.h>
#include <Inventor/elements/SoShapeHintsElement.h>
#include <Inventor/nodes/SoVertexShape.h>
#include <Inventor/elements/SoDrawStyleElement.h>
#include <Inventor/elements/SoComplexityTypeElement.h>
#include <Inventor/elements/SoGLVBOElement.h>
#include <Inventor/elements/SoGLLazyElement.h>
#include <Inventor/actions/SoGLRenderAction.h>
#include <Inventor/errors/SoDebugError.h>
#include <Inventor/SoDebug.h>
#include <Inventor/SoMachine.h>

SO_NODE_ABSTRACT_SOURCE(SoVertexShape);

////////////////////////////////////////////////////////////////////////
//
// Description:
//    Constructor
//
// Use: protected

SoVertexShape::SoVertexShape()
//
////////////////////////////////////////////////////////////////////////
{
    SO_NODE_CONSTRUCTOR(SoVertexShape);
    SO_NODE_ADD_FIELD(vertexProperty, (NULL));

    normalCache = NULL;
}

////////////////////////////////////////////////////////////////////////
//
// Description:
//    Destructor
//
// Use: private

SoVertexShape::~SoVertexShape()
//
////////////////////////////////////////////////////////////////////////
{
    if (normalCache != NULL)
        delete normalCache;
}

////////////////////////////////////////////////////////////////////////
//
// Description:
//    Subclasses may define this method to generate normals to use
//    when the normal binding is DEFAULT and there aren't enough
//    normals in the state. This should use the given SoNormalBundle
//    to generate the normals. Returns TRUE if normals were generated.
//
//    The default method returns TRUE.
//
// Use: extender, virtual

bool
SoVertexShape::generateDefaultNormals(SoState *, SoNormalBundle *)
//
////////////////////////////////////////////////////////////////////////
{
    return FALSE;
}

////////////////////////////////////////////////////////////////////////
//
// Description:
//    Sets up a cache to hold normals. This assumes the cache depends
//    on only the current coordinates, shape hints, and crease angle.
//
// Use: protected

void
SoVertexShape::setNormalCache(SoState *state,
                              int numNormals, const SbVec3f *normals)
//
////////////////////////////////////////////////////////////////////////
{
    if (normalCache != NULL)
        normalCache->unref();

    normalCache = new SoNormalCache(state);
    normalCache->ref();

    normalCache->set(numNormals, normals);

    // Set up the dependencies
#define ADD_DEPENDENCY(elt)                                                   \
    normalCache->addElement(state->getConstElement(elt::getClassStackIndex()))

    ADD_DEPENDENCY(SoCoordinateElement);
    ADD_DEPENDENCY(SoCreaseAngleElement);
    ADD_DEPENDENCY(SoShapeHintsElement);

#undef ADD_DEPENDENCY
}

////////////////////////////////////////////////////////////////////////
//
// Description:
//    Passes on notification after invalidating any caches.
//
// Use: internal

void
SoVertexShape::notify(SoNotList *list)
//
////////////////////////////////////////////////////////////////////////
{
    // Destroy cache, if present
    if (normalCache != NULL) {
        normalCache->unref();
        normalCache = NULL;
    }
    vpCache.invalidate();

    // Then do the usual stuff
    SoShape::notify(list);
}

////////////////////////////////////////////////////////////////////////
//
// Description:
//    Returns TRUE if the shape should be rendered now.  Does more then
//    the method in SoShape, because of possible transparency in vertex
//    property node.
//
// Use: protected
//
//////////////////////////////////////////////////////////////////////////
bool
SoVertexShape::shouldGLRender(SoGLRenderAction *action)
//
////////////////////////////////////////////////////////////////////////
{

    // Check if the shape is invisible
    if (SoDrawStyleElement::get(action->getState()) ==
        SoDrawStyleElement::INVISIBLE)
        return FALSE;

    // If the shape is transparent and transparent objects are being
    // delayed, don't render now
    // if there is transparency in the vertex property node, the object is
    // transparent.  If there are no colors in the vertexProperty node,
    // we have to check the state.
    if (!vpCache.colorIsInVtxProp()){
        if (action->handleTransparency())
                return FALSE;
    }
    else if (vpCache.transpIsInVtxProp()){
        if (action->handleTransparency(TRUE))
                return FALSE;
    }
    else
            SoLazyElement::setBlending(action->getState(), FALSE);        

    // If the current complexity is BOUNDING_BOX, just render the
    // cuboid surrounding the shape and tell the shape to stop
    if (SoComplexityTypeElement::get(action->getState()) ==
        SoComplexityTypeElement::BOUNDING_BOX) {
        GLRenderBoundingBox(action);
        return FALSE;
    }

    // Otherwise, go ahead and render the object
    return TRUE;
}

bool SoVertexShape::beginVertexArrayRendering( SoGLRenderAction* action )
{
  SoState* state = action->getState();
  bool useVertexAttributes = SoLazyElement::shouldUseVertexAttributes(state);

  const SoGLVBOElement* vboElement = SoGLVBOElement::getInstance(action->getState());

  // check if VBOs should be used
  bool shouldUseVBO = SoVBO::shouldUseVBO(state, vpCache.getNumVertices());

  bool vertexVBOUsed = false;
  bool colorVBOUsed = false;
  bool normalVBOUsed = false;
  bool texCoordVBOUsed = false;

  bool vboBound = false;
  { // Vertices:
    const void* dataPtr = vpCache.getVertices(0);
    SoVBO* vbo = vboElement->getVBO(SoGLVBOElement::VERTEX_VBO);
    if (vbo && shouldUseVBO) {
      if (vbo->bind(state)) {
        // if the VBO could be bound, we use it
        vertexVBOUsed = true;
        vboBound = true;
        dataPtr = NULL;
      }
    }
    if (useVertexAttributes) {
      glVertexAttribPointer(SoLazyElement::ATTRIB_VERTEX, (vpCache.getVertexStride() == sizeof(SbVec3f))?3:4, GL_FLOAT,false, 0, dataPtr);
      glEnableVertexAttribArray(SoLazyElement::ATTRIB_VERTEX);
    } else {
      glVertexPointer((vpCache.getVertexStride() == sizeof(SbVec3f))?3:4, GL_FLOAT, 0, dataPtr);
      glEnableClientState(GL_VERTEX_ARRAY);
    }
  }

  // Normals:
  bool perVertexNormals = vpCache.getNumNormals()>0 && (vpCache.getNormalBinding() == SoNormalBindingElement::PER_VERTEX_INDEXED || vpCache.getNormalBinding() == SoNormalBindingElement::PER_VERTEX);
  if (perVertexNormals) {
    const void* dataPtr = vpCache.getNormals(0);
    SoVBO* vbo = vboElement->getVBO(SoGLVBOElement::NORMAL_VBO);
    if (vbo && shouldUseVBO) {
      if (vbo->bind(state)) {
        // if the VBO could be bound, we use it
        normalVBOUsed = true;
        vboBound = true;
        dataPtr = NULL;
      }
    } else {
      if (vboBound) {
        glBindBufferARB(GL_ARRAY_BUFFER, 0);
        vboBound = false;
      }
    }
    if (useVertexAttributes) {
      glVertexAttribPointer(SoLazyElement::ATTRIB_NORMAL, 3, GL_FLOAT,false, 0, dataPtr);
      glEnableVertexAttribArray(SoLazyElement::ATTRIB_NORMAL);
    } else {
      glNormalPointer(GL_FLOAT, 0, dataPtr);
      glEnableClientState(GL_NORMAL_ARRAY);
    }
  }

  // Colors:
  bool perVertexColors = vpCache.getNumColors()>0 && (vpCache.getMaterialBinding() == SoMaterialBindingElement::PER_VERTEX_INDEXED || vpCache.getMaterialBinding() == SoMaterialBindingElement::PER_VERTEX);
  if (perVertexColors) {
    const void* dataPtr = NULL;
    SoVBO* vbo = vboElement->getVBO(SoGLVBOElement::COLOR_VBO);
    if (vbo) {
      // fill vbo with data even if no VBO rendering is desired, since we want
      // to use/cache the flipped colors on little endian machines
      if (vpCache.colorIsInVtxProp()) {
        if (vertexProperty.getValue()->getNodeId() != vbo->getDataId()) {
          // take colors from vertex property
          vbo->setData(vpCache.getNumColors() * sizeof(uint32_t), vpCache.getColors(0), vertexProperty.getValue()->getNodeId(), state);
        }
      } else {
        // take colors from state      
        SoGLLazyElement *lazyElement = (SoGLLazyElement*) SoLazyElement::getInstance(state);
        lazyElement->updateColorVBO(state, vbo);
      }
#if MACHINE_WORD_FORMAT == DGL_LITTLE_ENDIAN
      if (!vbo->hasSwappedRGBAData()) {
        vbo->copyAndSwapPackedRGBA(state);
      }
#endif
      if (shouldUseVBO && vbo->bind(state)) {
        // if the VBO should and could be bound, we use it
        colorVBOUsed = true;
        vboBound = true;
        dataPtr = NULL;
      } else {
        // use data pointer from VBO, since it is swapped on little endian machines
        dataPtr = vbo->getData();
      }
    } else {
      // we do not have a VBO, but we need swapped color data
      SoError::post("SoVertexShape: Vertex Array rendering was started but not color VBO was set.");
      dataPtr = vpCache.getColors(0);
    }
    if (!shouldUseVBO) {
      if (vboBound) {
        glBindBufferARB(GL_ARRAY_BUFFER, 0);
        vboBound = false;
      }
    }
    if (useVertexAttributes) {
      glVertexAttribPointer(SoLazyElement::ATTRIB_COLOR, 4, GL_UNSIGNED_BYTE,true, 0, dataPtr);
      glEnableVertexAttribArray(SoLazyElement::ATTRIB_COLOR);
    } else {
      glColorPointer(4, GL_UNSIGNED_BYTE, 0, dataPtr);
      glEnableClientState(GL_COLOR_ARRAY);
    }
  } else {
    if (useVertexAttributes) {
      // we need to send the single color on the correct vertex attribute...
      float v[4];
      SbColor color = SoGLLazyElement::getDiffuse(state, 0);
      color.getValue(v[0], v[1], v[2]);
      v[3] = SoGLLazyElement::getTransparency(state, 0);
      glVertexAttrib4fv(SoLazyElement::ATTRIB_COLOR, v);
    }
  }
  bool perVertexTexCoords = vpCache.getNumTexCoords()>0;
  if (perVertexTexCoords) {
    const void* dataPtr = vpCache.getTexCoords(0);
    SoVBO* vbo = vboElement->getVBO(SoGLVBOElement::TEXCOORD_VBO);
    if (vbo && shouldUseVBO) {
      if (vbo->bind(state)) {
        // if the VBO could be bound, we use it
        texCoordVBOUsed = true;
        vboBound = true;
        dataPtr = NULL;
      }
    } else {
      if (vboBound) {
        glBindBufferARB(GL_ARRAY_BUFFER, 0);
        vboBound = false;
      }
    }
    if (useVertexAttributes) {
      glVertexAttribPointer(SoLazyElement::ATTRIB_TEXCOORD, (vpCache.getTexCoordStride() == sizeof(SbVec2f))?2:4, GL_FLOAT,false, 0, dataPtr);
      glEnableVertexAttribArray(SoLazyElement::ATTRIB_TEXCOORD);
    } else {
      glTexCoordPointer((vpCache.getTexCoordStride() == sizeof(SbVec2f))?2:4, GL_FLOAT, 0, dataPtr);
      glEnableClientState(GL_TEXTURE_COORD_ARRAY);
    }
  }

#ifdef DEBUG
  if (SoDebug::GetEnv("IV_DEBUG_VBO_RENDERING")) {
    SoDebugError::postInfo("beginVertexArrayRendering", "%s Vertex Array used: Vertices: %d %s Color: %s %s Normals: %s %s TexCoord: %s %s", getTypeId().getName().getString(),
      vpCache.getNumVertices(), vertexVBOUsed?"VBO":"VA", perVertexColors?"PerVertex":"Overall", perVertexColors?(colorVBOUsed?"VBO":"VA"):"",
      perVertexNormals?"PerVertex":"Overall", perVertexNormals?(normalVBOUsed?"VBO":"VA"):"",
      perVertexTexCoords?"PerVertex":"NONE",  perVertexTexCoords?(texCoordVBOUsed?"VBO":"VA"):"");
  }
#endif

  if (_preVertexArrayRenderingCB) {
    (*_preVertexArrayRenderingCB)(this, action, shouldUseVBO, vpCache.getNumVertices());
  }

  return shouldUseVBO;
}

void SoVertexShape::endVertexArrayRendering( SoGLRenderAction* action, bool vboWasUsed )
{
  if (vboWasUsed) {
    glBindBufferARB(GL_ARRAY_BUFFER, 0);
  }
  bool useVertexAttributes = SoLazyElement::shouldUseVertexAttributes(action->getState());
  if (useVertexAttributes) {
    glDisableVertexAttribArray(SoLazyElement::ATTRIB_VERTEX);
    glDisableVertexAttribArray(SoLazyElement::ATTRIB_NORMAL);
    glDisableVertexAttribArray(SoLazyElement::ATTRIB_COLOR);
    glDisableVertexAttribArray(SoLazyElement::ATTRIB_TEXCOORD);
  } else {
    glDisableClientState(GL_VERTEX_ARRAY);
    glDisableClientState(GL_NORMAL_ARRAY);
    glDisableClientState(GL_COLOR_ARRAY);
    glDisableClientState(GL_TEXTURE_COORD_ARRAY);
  }
  if (_postVertexArrayRenderingCB) {
    (*_postVertexArrayRenderingCB)(this, action, vboWasUsed, vpCache.getNumVertices());
  }
}

SoVertexProperty* SoVertexShape::getVertexProperty()
{
  SoNode* node = vertexProperty.getValue();
  if (node) {
    if (node->isOfType(SoVertexProperty::getClassTypeId())) {
      return static_cast<SoVertexProperty*>(node);
    } else {
      SoError::post("Expected a SoVertexProperty as vertexPropery field value, got %s instead.", node->getTypeId().getName().getString());
      return NULL;
    }
  } else {
    return NULL;
  }
}
