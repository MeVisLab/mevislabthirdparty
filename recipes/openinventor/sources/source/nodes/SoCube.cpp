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
|      SoCube
|
|   Author(s)          : Paul S. Strauss, Thad Beier
|
______________  S I L I C O N   G R A P H I C S   I N C .  ____________
_______________________________________________________________________
*/

#include <Inventor/system/SbSystem.h>
#include <Inventor/system/SbOpenGL.h>
#include <Inventor/SbBox.h>
#include <Inventor/SoPickedPoint.h>
#include <Inventor/SoPrimitiveVertex.h>
#include <Inventor/actions/SoGLRenderAction.h>
#include <Inventor/actions/SoRayPickAction.h>
#include <Inventor/bundles/SoMaterialBundle.h>
#include <Inventor/details/SoCubeDetail.h>
#include <Inventor/elements/SoDrawStyleElement.h>
#include <Inventor/elements/SoComplexityElement.h>
#include <Inventor/elements/SoComplexityTypeElement.h>
#include <Inventor/elements/SoGLTextureCoordinateElement.h>
#include <Inventor/elements/SoGLTextureEnabledElement.h>
#include <Inventor/elements/SoLightModelElement.h>
#include <Inventor/elements/SoMaterialBindingElement.h>
#include <Inventor/elements/SoModelMatrixElement.h>
#include <Inventor/misc/SoState.h>
#include <Inventor/nodes/SoCube.h>
#include <Inventor/SoMachine.h>
#include <Inventor/nodes/SoVertexShape.h>

SO_NODE_SOURCE(SoCube);

// Cube geometry
SbVec3f         SoCube::coords[8];      // Corner coordinates
SbVec2f         SoCube::texCoords[4];   // Face corner texture coordinates
SbVec3f         SoCube::normals[6];     // Face normals
const SbVec3f  *SoCube::verts[6][4];    // Vertex references to coords

////////////////////////////////////////////////////////////////////////
//
// Description:
//    Constructor
//
// Use: public

SoCube::SoCube()
//
////////////////////////////////////////////////////////////////////////
{
  SO_NODE_CONSTRUCTOR(SoCube);

  SO_NODE_ADD_FIELD(width,  (2.0));
  SO_NODE_ADD_FIELD(height, (2.0));
  SO_NODE_ADD_FIELD(depth,     (2.0));

  isBuiltIn = TRUE;

  if (SO_NODE_IS_FIRST_INSTANCE()) {
    // Initialize corner coordinate values
    coords[0].setValue(-1.0,  1.0, -1.0);   // Left  Top    Back
    coords[1].setValue( 1.0,  1.0, -1.0);   // Right Top    Back
    coords[2].setValue(-1.0, -1.0, -1.0);   // Left  Bottom Back
    coords[3].setValue( 1.0, -1.0, -1.0);   // Right Bottom Back
    coords[4].setValue(-1.0,  1.0,  1.0);   // Left  Top    Front
    coords[5].setValue( 1.0,  1.0,  1.0);   // Right Top    Front
    coords[6].setValue(-1.0, -1.0,  1.0);   // Left  Bottom Front
    coords[7].setValue( 1.0, -1.0,  1.0);   // Right Bottom Front

    // Initialize face vertices to point into coords. The order of
    // vertices around the faces is chosen so that the texture
    // coordinates match up: texture coord (0,0) is at the first
    // vertex and (1,1) is at the third. The vertices obey the
    // right-hand rule for each face.
    verts[1][2] = verts[2][3] = verts[4][3] = &coords[0];
    verts[1][3] = verts[3][2] = verts[4][2] = &coords[1];
    verts[1][1] = verts[2][0] = verts[5][0] = &coords[2];
    verts[1][0] = verts[3][1] = verts[5][1] = &coords[3];
    verts[0][3] = verts[2][2] = verts[4][0] = &coords[4];
    verts[0][2] = verts[3][3] = verts[4][1] = &coords[5];
    verts[0][0] = verts[2][1] = verts[5][3] = &coords[6];
    verts[0][1] = verts[3][0] = verts[5][2] = &coords[7];

    // Initialize texture coordinates. These are for the 4 corners of
    // each face, starting at the lower left corner
    texCoords[0].setValue(0.0, 0.0);
    texCoords[1].setValue(1.0, 0.0);
    texCoords[2].setValue(1.0, 1.0);
    texCoords[3].setValue(0.0, 1.0);

    // Initialize face normals
    normals[0].setValue( 0.0,  0.0,  1.0);  // Front
    normals[1].setValue( 0.0,  0.0, -1.0);  // Back
    normals[2].setValue(-1.0,  0.0,  0.0);  // Left
    normals[3].setValue( 1.0,  0.0,  0.0);  // Right
    normals[4].setValue( 0.0,  1.0,  0.0);  // Top
    normals[5].setValue( 0.0, -1.0,  0.0);  // Bottom

  }
}

////////////////////////////////////////////////////////////////////////
//
// Description:
//    Destructor
//
// Use: private

SoCube::~SoCube()
//
////////////////////////////////////////////////////////////////////////
{
}

////////////////////////////////////////////////////////////////////////
//
// Description:
//    Performs GL rendering of a cube.
//
// Use: extender

void
SoCube::GLRender(SoGLRenderAction *action)
//
////////////////////////////////////////////////////////////////////////
{
  // First see if the object is visible and should be rendered now
  if (! shouldGLRender(action))
    return;

  SoState* state = action->getState();
  // See if texturing is enabled
  bool doTextures = SoGLTextureEnabledElement::get(state);

  // Render the cube. The GLRenderGeneric() method handles any
  // case.
  bool sendNormals = (SoLightModelElement::get(state) !=
    SoLightModelElement::BASE_COLOR);

  if ((SoDrawStyleElement::get(state) == SoDrawStyleElement::FILLED) &&
      (SoVBO::isVertexArrayRenderingAllowed() && SoVBO::shouldUseVBO(state, SoVBO::getVboMinimumSizeLimit()+1 ))) {
    // only use vertex array rendering if VA/VBO is allowed and if draw style is FILLED.
    GLRenderVertexArray(action, sendNormals, doTextures);
  } else {
    GLRenderGeneric(action, sendNormals, doTextures);
  }
}

////////////////////////////////////////////////////////////////////////
//
// Description:
//    Implements ray picking. We could just use the default mechanism,
//    generating primitives, but this would be inefficient if the
//    complexity is above 0.5. Therefore, we make sure that the
//    complexity is low and then use the primitive generation.
//
// Use: extender

void
SoCube::rayPick(SoRayPickAction *action)
//
////////////////////////////////////////////////////////////////////////
{
  // First see if the object is pickable
  if (! shouldRayPick(action))
    return;

  // Save the state so we don't affect the real complexity
  action->getState()->push();

  // Change the complexity
  SoComplexityElement::set(action->getState(), 0.0);
  SoComplexityTypeElement::set(action->getState(),
    SoComplexityTypeElement::OBJECT_SPACE);

  // Pick using primitive generation. Make sure we know that we are
  // really picking on a real cube, not just a bounding box of
  // another shape.
  pickingBoundingBox = FALSE;
  SoShape::rayPick(action);

  // Restore the state
  action->getState()->pop();
}

////////////////////////////////////////////////////////////////////////
//
// Description:
//    Computes bounding box of cube.
//
// Use: protected

void
SoCube::computeBBox(SoAction *, SbBox3f &box, SbVec3f &center)
//
////////////////////////////////////////////////////////////////////////
{
  float       w, h, d;

  getSize(w, h, d);
  box.setBounds(-w, -h, -d, w, h, d);
  center.setValue(0.0, 0.0, 0.0);
}

// include ppp generated source code:
#include "SoCube_generated.cpp"

////////////////////////////////////////////////////////////////////////
//
// Description:
//    Overrides standard method to create an SoCubeDetail instance
//    representing a picked intersection with a triangle that is half
//    of the face of a cube.
//
// Use: protected, virtual

SoDetail *
SoCube::createTriangleDetail(SoRayPickAction *,
                             const SoPrimitiveVertex *v1,
                             const SoPrimitiveVertex *,
                             const SoPrimitiveVertex *,
                             SoPickedPoint *)
                             //
                             ////////////////////////////////////////////////////////////////////////
{
  SoCubeDetail        *detail;

  // Don't create a detail if the pick operation was performed on a
  // bounding box cube, not a real cube
  if (pickingBoundingBox)
    return NULL;

  detail = new SoCubeDetail;

  // The part code should be the same in all three details, so just use one
  detail->setPart(((const SoCubeDetail *) v1->getDetail())->getPart());

  return detail;
}

////////////////////////////////////////////////////////////////////////
//
// Description:
//    Returns TRUE if per face materials are specified.
//
// Use: private

bool
SoCube::isMaterialPerFace(SoAction *action) const
//
////////////////////////////////////////////////////////////////////////
{
  SoMaterialBindingElement::Binding binding;

  binding = SoMaterialBindingElement::get(action->getState());

  return (binding == SoMaterialBindingElement::PER_PART ||
    binding == SoMaterialBindingElement::PER_PART_INDEXED ||
    binding == SoMaterialBindingElement::PER_FACE ||
    binding == SoMaterialBindingElement::PER_FACE_INDEXED);
}

////////////////////////////////////////////////////////////////////////
//
// Description:
//    Computes number of divisions per side based on complexity.
//
// Use: private

int
SoCube::computeNumDivisions(SoAction *action) const
//
////////////////////////////////////////////////////////////////////////
{
  int         numDivisions;
  float       complexity;

  switch (SoComplexityTypeElement::get(action->getState())) {

      case SoComplexityTypeElement::OBJECT_SPACE:

        // In object space, the number of divisions is greater than 1
        // only for complexity values > 0.5. The maximum value is 16,
        // when complexity = 1.
        complexity = SoComplexityElement::get(action->getState());
        numDivisions = (complexity <= 0.5 ? 1 :
          -14 + (int) (complexity * 30.0));
        break;

      case SoComplexityTypeElement::SCREEN_SPACE:

        // In screen space, the number of divisions is based on the
        // complexity and the size of the cube when projected onto the
        // screen.
        short   maxSize;
        {
          SbVec3f     p;
          SbVec2s     rectSize;

          getSize(p[0], p[1], p[2]);
          getScreenSize(action->getState(), SbBox3f(-p, p), rectSize);
          maxSize = (rectSize[0] > rectSize[1] ? rectSize[0] : rectSize[1]);
        }

        // Square complexity to get a more even increase in the number
        // of tesselation squares. Maximum bound is 1/4 the number of
        // pixels per side.
        complexity = SoComplexityElement::get(action->getState());
        numDivisions = 1 + (int) (0.25 * maxSize * complexity * complexity);
        break;

      case SoComplexityTypeElement::BOUNDING_BOX:

        // Most shapes do not have to handle this case, since it is
        // handled for them. However, since it is handled by drawing
        // the shape as a cube, the SoCube class has to handle it.
        numDivisions = 1;
        break;
  }

  return numDivisions;
}

////////////////////////////////////////////////////////////////////////
//
// Description:
//    Computes real half-width, -height, -depth.
//
// Use: private

void
SoCube::getSize(float &hWidth, float &hHeight, float &hDepth) const
//
////////////////////////////////////////////////////////////////////////
{
  hWidth  = ( width.isIgnored() ? 1.0 :  width.getValue() / 2.0);
  hHeight = (height.isIgnored() ? 1.0 : height.getValue() / 2.0);
  hDepth  = ( depth.isIgnored() ? 1.0 :  depth.getValue() / 2.0);
}

////////////////////////////////////////////////////////////////////////
//
// Description:
//    Does GL rendering of a cube representing the given bounding box.
//    This is used for BOUNDING_BOX complexity. It does the minimum
//    work necessary.
//
// Use: private

void
SoCube::GLRenderBoundingBox(SoGLRenderAction *action, const SbBox3f &bbox)
//
////////////////////////////////////////////////////////////////////////
{
  int                 face, vert;
  SoMaterialBundle    mb(action);
  SbVec3f             scale, tmp;

  // Make sure textures are disabled, just to speed things up
  action->getState()->push();
  SoGLTextureEnabledElement::set(action->getState(), FALSE);

  // Make sure first material is sent if necessary
  mb.sendFirst();

  // Scale and translate the cube to the correct spot
  const SbVec3f       &translate = bbox.getCenter();
  SbVec3f size;
  bbox.getSize(size[0], size[1], size[2]);
  scale = 0.5 * size;

  for (face = 0; face < 6; face++) {

    if (! mb.isColorOnly())
      glNormal3fv(normals[face].getValue());

    glBegin(GL_POLYGON);

    for (vert = 0; vert < 4; vert++)
      glVertex3fv((SCALE(*verts[face][vert]) + translate).getValue());

    glEnd();
  }

  // Restore state
  action->getState()->pop();
}

////////////////////////////////////////////////////////////////////////
//
// Description:
//    Does picking of a cube representing the given bounding box. This
//    is used for BOUNDING_BOX complexity. It uses the same code as
//    for rayPick(), except that it makes sure the cube is transformed
//    first to where the bounding box is.
//
// Use: private

void
SoCube::rayPickBoundingBox(SoRayPickAction *action, const SbBox3f &bbox)
//
////////////////////////////////////////////////////////////////////////
{
  // Save the state so we don't affect the real complexity
  action->getState()->push();

  // Change the complexity
  SoComplexityElement::set(action->getState(), 0.0);
  SoComplexityTypeElement::set(action->getState(),
    SoComplexityTypeElement::OBJECT_SPACE);

  // Change the current matrix to scale and translate the cube to the
  // correct spot. (We can't just use an extra matrix passed to
  // computeObjectSpaceRay(), since the points generated by
  // generatePrimitives() have to be transformed, not just the ray.)
  SbVec3f             size;
  bbox.getSize(size[0], size[1], size[2]);

  // If any of the dimensions is 0, beef it up a little bit to avoid
  // scaling by 0
  if (size[0] == 0.0)
    size[0] = 0.00001;
  if (size[1] == 0.0)
    size[1] = 0.00001;
  if (size[2] == 0.0)
    size[2] = 0.00001;

  SoModelMatrixElement::translateBy(action->getState(), this,
    bbox.getCenter());
  SoModelMatrixElement::scaleBy(action->getState(), this,
    0.5 * size);

  // Compute the picking ray in the space of the shape
  computeObjectSpaceRay(action);

  // Pick using primitive generation. Make sure we know that we are
  // picking on just a bounding box of another shape, so details
  // won't be created.
  pickingBoundingBox = TRUE;
  generatePrimitives(action);

  // Restore the state
  action->getState()->pop();
}

void SoCube::GLRenderVertexArray(SoGLRenderAction *action,
                                 bool sendNormals, bool doTextures)
{
  SoState* state = action->getState();
  SbVec3f scale;
  getSize(scale[0], scale[1], scale[2]);

  SbBool              materialPerFace;
  SbVec3f             pt, norm;
  SoMaterialBundle    mb(action);

  materialPerFace = isMaterialPerFace(action);

  // Make sure first material is sent if necessary
  if (materialPerFace) {
    mb.setUpMultiple();
  }
  mb.sendFirst();

  _cache.useColors = true;
  _cache.useNormals = sendNormals;
  _cache.useTexCoords = doTextures;

  // 6 faces with 2 triangles
  const int numVertices = 6 * 2 * 3;
  
  _cache.numVertices = numVertices;

  // vertex (3 floats) + normal (3 floats) + texcood (2 floats) + color (1 uint32)
  const int numBytes = ((3+3+2) * 4 + 4) * numVertices; 
  char data[numBytes];
  float* verticesPtr = (float*)data;
  float* normalsPtr = verticesPtr + (numVertices*3);
  float* texCoordsPtr = normalsPtr + (numVertices*3);
  GLuint* colorsPtr = (GLuint*)(texCoordsPtr + (numVertices*2));
  char* vertexOffset = (char*)verticesPtr; 
  char* normalOffset = (char*)normalsPtr; 
  char* texCoordOffset = (char*)texCoordsPtr; 
  char* colorOffset = (char*)colorsPtr;

  const uint32_t* colors =  SoLazyElement::getPackedColors(state);
  uint32_t color = colors[0];
  SbVec3f normal;
  for (int face = 0; face < 6; face++) {
    if (materialPerFace && face > 0) {
      color = colors[face];
    }
    if (sendNormals) {
      normal = normals[face];
    }
    int indices[] = {0,1,2, 0,2,3};
    for (int tri = 0; tri < 6; tri++) {
      int vert = indices[tri];
      uint32_t swappedColor;
      DGL_HTON_INT32(swappedColor, color);
      *colorsPtr++ = swappedColor;
      if (doTextures) {
        const float *tmp = texCoords[vert].getValue();
        *texCoordsPtr++ = tmp[0]; 
        *texCoordsPtr++ = tmp[1]; 
      }
      if (sendNormals) {
        const float *tmp = normal.getValue();
        *normalsPtr++ = tmp[0]; 
        *normalsPtr++ = tmp[1]; 
        *normalsPtr++ = tmp[2]; 
      }
      *verticesPtr++ = (*verts[face][vert])[0]*scale[0];
      *verticesPtr++ = (*verts[face][vert])[1]*scale[1];
      *verticesPtr++ = (*verts[face][vert])[2]*scale[2];
    }
  }

  _cache.vbo.setData(numBytes, NULL, 0, state);
  _cache.vbo.bind(state);
  _cache.vbo.updateData(data);
  
  _cache.vertexOffset = (char*)(vertexOffset - data);
  _cache.colorOffset = (char*)(colorOffset - data);
  _cache.normalOffset = (char*)(normalOffset - data);
  _cache.texCoordOffset = (char*)(texCoordOffset - data);

  _cache.drawArrays(this, action, GL_TRIANGLES);
  _cache.vbo.unbind();
}
