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
|      SoSphere
|
|   Author(s)          : Paul S. Strauss
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
#include <Inventor/elements/SoComplexityElement.h>
#include <Inventor/elements/SoComplexityTypeElement.h>
#include <Inventor/elements/SoGLTextureCoordinateElement.h>
#include <Inventor/elements/SoGLTextureEnabledElement.h>
#include <Inventor/elements/SoGLLazyElement.h>
#include <Inventor/elements/SoModelMatrixElement.h>
#include <Inventor/misc/SoState.h>
#include <Inventor/nodes/SoSphere.h>
#include <iostream>

#include <vector>

SO_NODE_SOURCE(SoSphere);

// Computes S and T texture coordinates from point on surface
#define COMPUTE_S_T(point, s, t)                                              \
  s = atan2f(point[0], point[2]) * .159 + .5;                               \
  t = atan2f(point[1],                                                      \
  sqrtf(point[0]*point[0] + point[2]*point[2])) * .318 + .5

;
// Adjusts S texture coordinate in unstable areas
#define ADJUST_S(s, octant)                                                   \
  if (s < .001 && (octant == 1 || octant == 3))                             \
  s = 1.0;                                                              \
    else if (s > .999 && (octant == 5 || octant == 7))                        \
    s = 0.0

////////////////////////////////////////////////////////////////////////
//
// Description:
//    Constructor
//
// Use: public

SoSphere::SoSphere()
//
////////////////////////////////////////////////////////////////////////
{
  SO_NODE_CONSTRUCTOR(SoSphere);
  SO_NODE_ADD_FIELD(radius, (1.0));
  SO_NODE_ADD_FIELD(subdivision, (0));
  isBuiltIn = TRUE;
}

////////////////////////////////////////////////////////////////////////
//
// Description:
//    Destructor
//
// Use: private

SoSphere::~SoSphere()
//
////////////////////////////////////////////////////////////////////////
{
}

////////////////////////////////////////////////////////////////////////
//
// Description:
//    Performs GL rendering of a sphere.
//
// Use: extender

void
SoSphere::GLRender(SoGLRenderAction *action)
//
////////////////////////////////////////////////////////////////////////
{
  // First see if the object is visible and should be rendered now
  if (! shouldGLRender(action))
    return;

  // Make sure the first current material is sent to GL
  SoMaterialBundle    mb(action);
  mb.sendFirst();

  // See if texturing is enabled
  bool doTextures = SoGLTextureEnabledElement::get(action->getState());

  // Render the sphere. The GLRenderGeneric() method handles any
  // case. The GLRenderNvertTnone() handles the case where we are
  // outputting normals but no texture coordinates. This case is
  // handled separately since it occurs often and warrants its own
  // method.
  if (SoVBO::isVertexArrayRenderingAllowed() && SoVBO::shouldUseVBO(action->getState(), SoVBO::getVboMinimumSizeLimit()+1 )) {
    GLRenderVertexArray(action, ! mb.isColorOnly(), doTextures);
  } else {
    if (! doTextures && ! mb.isColorOnly())
      GLRenderNvertTnone(action);
    else
      GLRenderGeneric(action, ! mb.isColorOnly(), doTextures);
  }
}

////////////////////////////////////////////////////////////////////////
//
// Description:
//    Implements ray picking
//
// Use: extender

void
SoSphere::rayPick(SoRayPickAction *action)
//
////////////////////////////////////////////////////////////////////////
{
  SbVec3f             enterPoint, exitPoint, normal;
  SbVec4f             texCoord(0.0, 0.0, 0.0, 1.0);
  SoPickedPoint       *pp;

  // First see if the object is pickable
  if (! shouldRayPick(action))
    return;

  // Compute the picking ray in our current object space
  computeObjectSpaceRay(action);

  // Create SbSphere with correct radius, centered at zero
  float       rad = (radius.isIgnored() ? 1.0 : radius.getValue());
  SbSphere    sph(SbVec3f(0., 0., 0.), rad);

  // Intersect with pick ray. If found, set up picked point(s)
  if (sph.intersect(action->getLine(), enterPoint, exitPoint)) {
    if (action->isBetweenPlanes(enterPoint) &&
      (pp = action->addIntersection(enterPoint)) != NULL) {

        normal = enterPoint;
        normal.normalize();
        pp->setObjectNormal(normal);
        COMPUTE_S_T(enterPoint, texCoord[0], texCoord[1]);
        pp->setObjectTextureCoords(texCoord);
    }

    if (action->isBetweenPlanes(exitPoint) &&
      (pp = action->addIntersection(exitPoint)) != NULL) {

        normal = exitPoint;
        normal.normalize();
        pp->setObjectNormal(normal);
        COMPUTE_S_T(exitPoint, texCoord[0], texCoord[1]);
        texCoord[2] = texCoord[3] = 0.0;
        pp->setObjectTextureCoords(texCoord);
    }
  }
}

////////////////////////////////////////////////////////////////////////
//
// Description:
//    Computes bounding box of sphere.
//
// Use: protected

void
SoSphere::computeBBox(SoAction *, SbBox3f &box, SbVec3f &center)
//
////////////////////////////////////////////////////////////////////////
{
  float       rad = (radius.isIgnored() ? 1.0 : radius.getValue());

  box.setBounds(-rad, -rad, -rad, rad, rad, rad);
  center.setValue(0.0, 0.0, 0.0);
}

// include ppp generated source code:
#include "SoSphere_generated.cpp"

////////////////////////////////////////////////////////////////////////
//
// Description:
//    Computes tesselation depth based on current complexity. Assumes
//    SoComplexityTypeElement and SoComplexityElement are enabled for
//    this action.
//
// Use: private

int
SoSphere::computeDepth(SoAction *action)
//
////////////////////////////////////////////////////////////////////////
{
  if (subdivision.getValue() > 0) {
    return subdivision.getValue();
  }

  float       complexity = SoComplexityElement::get(action->getState());
  int         depth;

  // In screen space, set the tesselation depth based on the
  // complexity and the size of the sphere when projected onto the screen.
  if (SoComplexityTypeElement::get(action->getState()) ==
    SoComplexityTypeElement::SCREEN_SPACE) {

      float   rad = (radius.isIgnored() ? 1.0 : radius.getValue());
      SbVec3f p(rad, rad, rad);
      SbVec2s rectSize;
      short   maxSize;

      getScreenSize(action->getState(), SbBox3f(-p, p), rectSize);

      maxSize = (rectSize[0] > rectSize[1] ? rectSize[0] : rectSize[1]);

      depth = 1 + (int) (.1 * complexity * maxSize);
  }

  //
  // In object space, compute tesselation depth based only on
  // complexity value. We want the following correspondences between
  // complexity and depth:
  //          0.0 -> 5
  //          0.5 -> 20
  //          1.0 -> 70
  // So we'll use linear ramps from 0 to .5 and from .5 to 1
  //
  else {
    if (complexity < 0.5)
      depth = 10 + (int) ((complexity) * 20.0);
    else
      depth = -30 + (int) ((complexity) * 100.0);
  }

  return depth;
}

void SoSphere::GLRenderVertexArray(SoGLRenderAction *action, bool sendNormals, bool doTextures)
{
  SoState* state = action->getState();

  float rad = (radius.isIgnored() ? 1.0 : radius.getValue());

  // Compute depth based on complexity
  int depth = computeDepth(action);

  bool cacheValid = _cache.radius == rad &&
                    _cache.depth == depth &&
                    _cache.useNormals == sendNormals &&
                    _cache.useTexCoords == doTextures &&
                    _cache.vbo.isValid(state);

  if (!cacheValid) {
    _cache.radius = rad;
    _cache.depth = depth;
    _cache.useNormals = sendNormals;
    _cache.useTexCoords = doTextures;

    std::vector<int> indices;
    std::vector<SbVec3f> points;
    std::vector<SbVec3f> normals;
    std::vector<SbVec2f> texCoords;
    int currentIndex = 0;

    int         i, j, k, s_x, s_y, s_z, order;
    float       botWidth, topWidth, yTop, yBot, tmp;
    SbVec3f     vec;
    float       s, t, sAvg;
    bool winding;

#define ADD_TRIANGLE \
    currentIndex = (int)points.size(); \
    indices.push_back(currentIndex-3); \
    indices.push_back(winding ? currentIndex-1 : currentIndex - 2); \
    indices.push_back(winding ? currentIndex-2 : currentIndex - 1); \
    winding = !winding; \


    for (int octant = 0; octant < 8; octant++) {
      s_x = -(((octant & 01) << 1) - 1);
      s_y = -( (octant & 02)       - 1);
      s_z = -(((octant & 04) >> 1) - 1);
      order = s_x * s_y * s_z;

      for (i = 0; i < depth - 1; i++) {
        yBot = (float) i      / depth;
        yTop = (float)(i + 1) / depth;

        botWidth = 1.0 - yBot;
        topWidth = 1.0 - yTop;

        winding = false;
        for (j = 0; j < depth - i; j++) {

          // First vertex
          k = order > 0 ? depth - i - j : j;
          tmp = (botWidth * k) / (depth - i);
          vec.setValue(s_x * tmp, s_y * yBot, s_z * (botWidth - tmp));
          vec.normalize();

          if (doTextures) {
            COMPUTE_S_T(vec, s, t);
            texCoords.push_back(SbVec2f(s,t));
          }
          if (sendNormals)
            normals.push_back(vec);
          points.push_back(vec*rad);

          if (j>0) {
            ADD_TRIANGLE
          }

          // Second vertex
          k = order > 0 ? (depth - i - 1) - j : j;
          tmp = (topWidth * k) / (depth - i - 1);
          vec.setValue(s_x * tmp, s_y * yTop, s_z * (topWidth - tmp));
          vec.normalize();

          if (doTextures) {
            COMPUTE_S_T(vec, s, t);
            ADJUST_S(s, octant);
            texCoords.push_back(SbVec2f(s,t));
          }
          if (sendNormals)
            normals.push_back(vec);
          points.push_back(vec*rad);

          if (j>0) {
            ADD_TRIANGLE
          }
        }

        // Last vertex
        k = order > 0 ? depth - i - j : j;
        tmp = (botWidth * k) / (depth - i);
        vec.setValue(s_x * tmp, s_y * yBot, s_z * (botWidth - tmp));
        vec.normalize();

        if (doTextures) {
          COMPUTE_S_T(vec, s, t);
          ADJUST_S(s, octant);
          texCoords.push_back(SbVec2f(s,t));
        }
        if (sendNormals)
          normals.push_back(vec);
        points.push_back(vec*rad);
        {
          ADD_TRIANGLE
        }
      }

      // Handle the top/bottom polygons specially, to avoid divide by zero
      winding = false;
      yBot = (float) i / depth;
      yTop = 1.0;
      botWidth = 1 - yBot;

      // First cap vertex
      if (order > 0)
        vec.setValue(0.0, s_y * yBot, s_z * botWidth);
      else
        vec.setValue(s_x * botWidth, s_y * yBot, 0.0);
      vec.normalize();

      if (doTextures) {
        COMPUTE_S_T(vec, s, t);
        ADJUST_S(s, octant);
        sAvg = s;
        texCoords.push_back(SbVec2f(s,t));
      }
      if (sendNormals)
        normals.push_back(vec);
      points.push_back(vec*rad);

      // Second cap vertex
      if (order > 0)
        vec.setValue(s_x * botWidth, s_y * yBot, 0.0);
      else
        vec.setValue(0.0, s_y * yBot, s_z * botWidth);
      vec.normalize();

      if (doTextures) {
        COMPUTE_S_T(vec, s, t);
        ADJUST_S(s, octant);
        sAvg = (sAvg + s) / 2;
        texCoords.push_back(SbVec2f(s,t));
      }
      if (sendNormals)
        normals.push_back(vec);
      points.push_back(vec*rad);

      // Third cap vertex
      vec.setValue(0.0, s_y, 0.0);

      if (doTextures) {
        s = sAvg;
        t = s_y * .5 + .5;
        texCoords.push_back(SbVec2f(s,t));
      }
      if (sendNormals)
        normals.push_back(vec);
      points.push_back(vec*rad);

      ADD_TRIANGLE
    }

    // vertex (3 floats) + normal (3 floats) + texcood (2 floats)
    const int numVertices = static_cast<int>(indices.size());
    const int numBytes = ((3+3+2) * 4) * numVertices; 
    char* data = new char[numBytes];
    float* verticesPtr = (float*)data;
    float* normalsPtr = verticesPtr + (numVertices*3);
    float* texCoordsPtr = normalsPtr + (numVertices*3);
    char* vertexOffset = (char*)verticesPtr; 
    char* normalOffset = (char*)normalsPtr; 
    char* texCoordOffset = (char*)texCoordsPtr; 

    for (int i = 0;i<numVertices;i++) {
      int index = indices[i];
      const SbVec3f& point = points[index];
      *verticesPtr++ = point[0];
      *verticesPtr++ = point[1];
      *verticesPtr++ = point[2];
      if (sendNormals) {
        const SbVec3f& normal = normals[index];
        *normalsPtr++ = normal[0];
        *normalsPtr++ = normal[1];
        *normalsPtr++ = normal[2];
      }
      if (doTextures) {
        const SbVec2f& texCoord = texCoords[index];
        *texCoordsPtr++ = texCoord[0];
        *texCoordsPtr++ = texCoord[1];
      }
    }

    _cache.vbo.freeGL(state);
    _cache.vbo.setData(numBytes, data, 0, state);
    // force upload
    _cache.vbo.bind(state);

    _cache.vertexOffset = (char*)(vertexOffset - data);
    _cache.normalOffset = (char*)(normalOffset - data);
    _cache.texCoordOffset = (char*)(texCoordOffset - data);
    _cache.numVertices = numVertices;

    delete[] data;
  }
  
  _cache.vbo.bind(state);
  _cache.drawArrays(this, action, GL_TRIANGLES);
  _cache.vbo.unbind();
}

#undef COMPUTE_S_T
#undef ADD_TRIANGLE