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
|      SoTriangleStripSet
|
|   Author(s)          : Paul S. Strauss
|
______________  S I L I C O N   G R A P H I C S   I N C .  ____________
_______________________________________________________________________
*/

#include <Inventor/system/SbSystem.h>
#include <Inventor/system/SbOpenGL.h>
#include <Inventor/SoPickedPoint.h>
#include <Inventor/SoPrimitiveVertex.h>
#include <Inventor/actions/SoGLRenderAction.h>
#include <Inventor/actions/SoRayPickAction.h>
#include <Inventor/bundles/SoTextureCoordinateBundle.h>
#include <Inventor/bundles/SoNormalBundle.h>
#include <Inventor/caches/SoNormalCache.h>
#include <Inventor/details/SoFaceDetail.h>
#include <Inventor/elements/SoGLCacheContextElement.h>
#include <Inventor/elements/SoGLCoordinateElement.h>
#include <Inventor/elements/SoGLTextureEnabledElement.h>
#include <Inventor/elements/SoGLTextureCoordinateElement.h>
#include <Inventor/elements/SoNormalBindingElement.h>
#include <Inventor/elements/SoNormalElement.h>
#include <Inventor/elements/SoShapeStyleElement.h>
#include <Inventor/elements/SoShapeHintsElement.h>
#include <Inventor/elements/SoCreaseAngleElement.h>
#include <Inventor/elements/SoGLLazyElement.h>
#include <Inventor/elements/SoDrawStyleElement.h>
#include <Inventor/nodes/SoMaterialBinding.h>
#include <Inventor/nodes/SoNormalBinding.h>
#include <Inventor/nodes/SoTriangleStripSet.h>
#include <Inventor/nodes/SoVertexProperty.h>
#include <Inventor/SoDebug.h>

// Constants for influencing auto-caching algorithm:

// If fewer than this many triangles, AND not using the vertexProperty
// node, auto-cache.
const int AUTO_CACHE_TSS_MIN_WITHOUT_VP = 20;

// And the number above which we'll say caches definitely SHOULDN'T be
// built (because they'll use too much memory):
const int AUTO_CACHE_TSS_MAX = OIV_AUTO_CACHE_DEFAULT_MAX;

SO_NODE_SOURCE(SoTriangleStripSet);

////////////////////////////////////////////////////////////////////////
//
// Description:
//    Constructor
//
// Use: public

SoTriangleStripSet::SoTriangleStripSet()
//
////////////////////////////////////////////////////////////////////////
{
  SO_NODE_CONSTRUCTOR(SoTriangleStripSet);
  SO_NODE_ADD_FIELD(numVertices,  (-1));

  totalNumVertices = -1;

  isBuiltIn = TRUE;
}

////////////////////////////////////////////////////////////////////////
//
// Description:
//    Destructor
//
// Use: private

SoTriangleStripSet::~SoTriangleStripSet()
//
////////////////////////////////////////////////////////////////////////
{
}

////////////////////////////////////////////////////////////////////////
//
// Description:
//    Implements GL rendering.
//
// Use: extender

void
SoTriangleStripSet::GLRender(SoGLRenderAction *action)
//
////////////////////////////////////////////////////////////////////////
{
  SoState *state = action->getState();

  // Get ShapeStyleElement
  const SoShapeStyleElement *shapeStyle = SoShapeStyleElement::get(state);

  SoVertexProperty* vp = getVertexProperty();
  
  // First see if the object is visible and should be rendered now:
  if (shapeStyle->mightNotRender()) {
    if (vpCache.mightNeedSomethingFromState(shapeStyle)) {
      vpCache.fillInColorAndTranspAvail(vp, state);
    }
    if (! shouldGLRender(action))
      return;
  }

  if (vpCache.mightNeedSomethingFromState(shapeStyle)) {
    vpCache.fillInCache(vp, state);

    // If using USE_REST_OF_VERTICES (-1), need to figure out how
    // many vertices there are every time:
    bool usingUSE_REST = FALSE;
    bool nvNotifyEnabled = TRUE;
    int nstrips = numVertices.getNum();
    if (nstrips && numVertices[nstrips-1] < 0) {
      usingUSE_REST = TRUE;
      nvNotifyEnabled = numVertices.enableNotify(FALSE);
      totalNumVertices = 0;
      for (int i = 0; i < nstrips-1; i++) 
        totalNumVertices += numVertices[i];
      numVertices.set1Value(nstrips-1, 
        vpCache.numVerts - totalNumVertices - startIndex.getValue());
      totalNumVertices = vpCache.numVerts - startIndex.getValue();
      vpCache.needFromState |=
        SoVertexPropertyCache::COORD_FROM_STATE_BIT;
    } else if (totalNumVertices < 0) {
      totalNumVertices = 0;
      for (int i = 0; i < nstrips; i++) 
        totalNumVertices += numVertices[i];
    }           

    if (vpCache.shouldGenerateNormals(shapeStyle)) {

      // See if there is a normal cache we can use. If not,
      // generate normals and cache them.
      SoNormalCache *normCache = getNormalCache();
      if (normCache == NULL || ! normCache->isValid(state)) {

        if (totalNumVertices < 0) {
          int nstrips = numVertices.getNum();
          totalNumVertices = 0;
          for (int i = 0; i < nstrips; i++) 
            totalNumVertices += numVertices[i];
        }           

        SoNormalBundle nb(action, FALSE);
        nb.initGenerator(totalNumVertices);
        generateDefaultNormals(state, &nb);             
        normCache = getNormalCache();   
      }
      vpCache.numNorms = normCache->getNum();
      vpCache.normalPtr = (const char *) normCache->getNormals();
    }

    SoTextureCoordinateBundle *tcb = NULL;
    uint32_t useTexCoordsAnyway = 0;
    if (vpCache.shouldGenerateTexCoords(shapeStyle)) {
      state->push();
      tcb = new SoTextureCoordinateBundle(action, TRUE, TRUE);
    }
    else if (shapeStyle->isTextureFunction() && vpCache.haveTexCoordsInVP()){
      state->push();
      useTexCoordsAnyway = SoVertexPropertyCache::TEXCOORD_BIT;
      SoGLTextureCoordinateElement::setTexGen(state, this, NULL);
    }           


    //If lighting or texturing is off, this vpCache and other things
    //need to be reconstructed when lighting or texturing is turned
    //on, so we set the bits in the VP cache:
    if(! shapeStyle->needNormals()) vpCache.needFromState |= 
      SoVertexPropertyCache::NORMAL_BITS;
    if(! shapeStyle->needTexCoords()) vpCache.needFromState |= 
      SoVertexPropertyCache::TEXCOORD_BIT;

    // If doing multiple colors, turn on ColorMaterial:
    if (vpCache.getNumColors() > 1) {
      SoGLLazyElement::setColorMaterial(state, TRUE);
    }
    //
    // Ask LazyElement to setup:
    //
    SoGLLazyElement *lazyElt = (SoGLLazyElement *)
      SoLazyElement::getInstance(state);

    if(vpCache.colorIsInVtxProp()){
      lazyElt->send(state, SoLazyElement::ALL_MASK);
      lazyElt->sendVPPacked(state, ( unsigned char*)
        vpCache.getColors(0));
    }
    else lazyElt->send(state, SoLazyElement::ALL_MASK);

#ifdef DEBUG
    // Check for enough vertices:
    if (vpCache.numVerts < totalNumVertices + startIndex.getValue()){
      SoDebugError::post("SoTriangleStripSet::GLRender",
        "Too few vertices specified;"
        " need %d, have %d", totalNumVertices+startIndex.getValue(),
        vpCache.numVerts);
    }
    // Check for enough colors, normals, texcoords:
    int numNormalsNeeded = 0;
    if (shapeStyle->needNormals()) switch (vpCache.getNormalBinding()) {
    case SoNormalBindingElement::OVERALL:
      numNormalsNeeded = 1;
      break;
    case SoNormalBindingElement::PER_VERTEX:
    case SoNormalBindingElement::PER_VERTEX_INDEXED:
      numNormalsNeeded = totalNumVertices + startIndex.getValue();
      break;
    case SoNormalBindingElement::PER_FACE:
    case SoNormalBindingElement::PER_FACE_INDEXED:
      {
        for (int i = 0; i < nstrips; i++) 
          numNormalsNeeded += numVertices[i]-2;
      }
      break;
    case SoNormalBindingElement::PER_PART:
    case SoNormalBindingElement::PER_PART_INDEXED:
      numNormalsNeeded = nstrips;
      break;
    }
    if (vpCache.getNumNormals() < numNormalsNeeded)
      SoDebugError::post("SoTriangleStripSet::GLRender",
      "Too few normals specified;"
      " need %d, have %d", numNormalsNeeded,
      vpCache.getNumNormals());

    if ((shapeStyle->needTexCoords() || useTexCoordsAnyway) && 
      !vpCache.shouldGenerateTexCoords(shapeStyle)) {

        if (vpCache.getNumTexCoords() < 
          totalNumVertices+startIndex.getValue())
          SoDebugError::post("SoTriangleStripSet::GLRender",
          "Too few texture coordinates specified;"
          " need %d, have %d", totalNumVertices+startIndex.getValue(),
          vpCache.getNumTexCoords());
    }
    int numColorsNeeded = 0;
    switch (vpCache.getMaterialBinding()) {
    case SoMaterialBindingElement::OVERALL:
      break;
    case SoMaterialBindingElement::PER_VERTEX:
    case SoMaterialBindingElement::PER_VERTEX_INDEXED:
      numColorsNeeded = totalNumVertices + startIndex.getValue();
      break;
    case SoMaterialBindingElement::PER_FACE:
    case SoMaterialBindingElement::PER_FACE_INDEXED:
      {
        for (int i = 0; i < nstrips; i++) 
          numColorsNeeded += numVertices[i]-2;
      }
      break;
    case SoMaterialBindingElement::PER_PART:
    case SoMaterialBindingElement::PER_PART_INDEXED:
      numColorsNeeded = nstrips;
      break;
    }
    if (vpCache.getNumColors() < numColorsNeeded)
      SoDebugError::post("SoTriangleStripSet::GLRender",
      "Too few diffuse colors specified;"
      " need %d, have %d", numColorsNeeded,
      vpCache.getNumColors());
#endif

    GLRenderInternal(action, useTexCoordsAnyway, shapeStyle);

    // If doing multiple colors, turn off ColorMaterial, invalidate
    // lazy-element diffuse color
    if (vpCache.getNumColors() > 1) {
      SoGLLazyElement::setColorMaterial(state, FALSE);
      ((SoGLLazyElement *)SoLazyElement::getInstance(state))->
        reset(state, SoLazyElement::DIFFUSE_MASK);
    }

    // Restore USE_REST_OF_VERTICES (-1)
    if (usingUSE_REST) {
      numVertices.set1Value(nstrips-1, -1);
      numVertices.enableNotify(nvNotifyEnabled);
    }           

    // Influence auto-caching algorithm:
    if (totalNumVertices < AUTO_CACHE_TSS_MIN_WITHOUT_VP &&
      vpCache.mightNeedSomethingFromState(shapeStyle)) {
        SoGLCacheContextElement::shouldAutoCache(state,
          SoGLCacheContextElement::DO_AUTO_CACHE);
    } else if (totalNumVertices > AUTO_CACHE_TSS_MAX) {
        SoGLCacheContextElement::shouldAutoCache(state,
          SoGLCacheContextElement::DONT_AUTO_CACHE);
    }           

    if (tcb) {
      delete tcb;
      state->pop();
    }
    else if (useTexCoordsAnyway) 
      state->pop();

  }
  else {
    // If doing multiple colors, turn on ColorMaterial:
    if (vpCache.getNumColors() > 1) {
      SoGLLazyElement::setColorMaterial(state, TRUE);
    }
    //
    // Ask LazyElement to setup:
    //
    SoGLLazyElement *lazyElt = (SoGLLazyElement *)
      SoLazyElement::getInstance(state);

    if(vpCache.colorIsInVtxProp()){
      lazyElt->send(state, SoLazyElement::ALL_MASK);
      lazyElt->sendVPPacked(state, (unsigned char*)
        vpCache.getColors(0));
    }
    else lazyElt->send(state, SoLazyElement::ALL_MASK);

    GLRenderInternal(action, 0, shapeStyle);

    // If doing multiple colors, turn off ColorMaterial:
    if (vpCache.getNumColors() > 1) {
      SoGLLazyElement::setColorMaterial(state, FALSE);
      ((SoGLLazyElement *)SoLazyElement::getInstance(state))->
        reset(state, SoLazyElement::DIFFUSE_MASK);
    }

    // Influence auto-caching algorithm:
    if (totalNumVertices > AUTO_CACHE_TSS_MAX) {

        SoGLCacheContextElement::shouldAutoCache(state,
          SoGLCacheContextElement::DONT_AUTO_CACHE);
    }           
  }

  return;
}

////////////////////////////////////////////////////////////////////////
//
// Description:
//    Generates triangles representing a triangle strip set.
//
// Use: protected

void
SoTriangleStripSet::generatePrimitives(SoAction *action)
//
////////////////////////////////////////////////////////////////////////
{
  SoState *state = action->getState();

  // Put vertexProperty stuff into state:
  SoVertexProperty* vp = getVertexProperty();
  state->push();
  if (vp) {
    vp->doAction(action);
  }

  // When generating primitives for picking, delay computing default
  // texture coordinates
  bool forPicking = action->isOfType(SoRayPickAction::getClassTypeId());

  SoPrimitiveVertex           pvs[3];
  SoFaceDetail                detail;
  SoTextureCoordinateBundle   tcb(action, FALSE, !forPicking);
  const SoCoordinateElement   *ce;
  int                         curVert, vert;
  int                         curNormal, curMaterial;
  int                         strip, numStrips;

  // Get bindings:
  SoMaterialBindingElement::Binding mbind =
    SoMaterialBindingElement::get(state);
  SoNormalBindingElement::Binding nbind =
    SoNormalBindingElement::get(state);

  curVert = (int) startIndex.getValue();

  ce = SoCoordinateElement::getInstance(state);

  // Do auto-normal generation, if necessary:
  SoNormalCache *normCache = NULL;
  const SoNormalElement *ne = SoNormalElement::getInstance(state);
  if (ne->getNum() == 0) {

    // See if there is a normal cache we can use. If not,
    // generate normals and cache them.
    normCache = getNormalCache();
    if (normCache == NULL || ! normCache->isValid(state)) {

      if (totalNumVertices < 0) {
        int nstrips = numVertices.getNum();
        totalNumVertices = 0;
        for (int i = 0; i < nstrips; i++) 
          totalNumVertices += numVertices[i];
      }       

      SoNormalBundle nb(action, FALSE);
      nb.initGenerator(totalNumVertices);
      generateDefaultNormals(state, &nb);
      normCache = getNormalCache();
    }

    nbind = SoNormalBindingElement::PER_VERTEX;
  }

  curNormal = 0;
  curMaterial = 0;

  if (forPicking) {
    SbVec4f tc(0.0, 0.0, 0.0, 0.0);
    pvs[0].setTextureCoords(tc);
    pvs[1].setTextureCoords(tc);
    pvs[2].setTextureCoords(tc);
  }

  detail.setNumPoints(3);
  SoPointDetail *pd = detail.getPoints();

  pvs[0].setDetail(&detail);
  pvs[1].setDetail(&detail);
  pvs[2].setDetail(&detail);

  // Do OVERALL stuff:
  if (mbind == SoMaterialBindingElement::OVERALL)
    curMaterial = 0;
  if (nbind == SoNormalBindingElement::OVERALL)
    curNormal = 0;

  numStrips = numVertices.getNum();

  // Handle USE_REST_OF_VERTICES:
  // If using USE_REST_OF_VERTICES (-1), need to figure out how
  // many vertices there are every time:
  bool usingUSE_REST = FALSE;
  bool nvNotifyEnabled = TRUE;
  if (numStrips && numVertices[numStrips-1] < 0) {
    usingUSE_REST = TRUE;
    nvNotifyEnabled = numVertices.enableNotify(FALSE);
    int nv = 0;
    for (int i = 0; i < numStrips-1; i++) nv += numVertices[i];
    numVertices.set1Value(numStrips-1, ce->getNum() - nv);
  }       

  for (strip = 0; strip < numStrips; strip++) {
    int vertsInStrip = numVertices[strip];

    detail.setPartIndex(strip);

    // Do PER_STRIP stuff:
    if (mbind == SoMaterialBindingElement::PER_PART ||
      mbind == SoMaterialBindingElement::PER_PART_INDEXED)
      curMaterial = strip;
    if (nbind == SoNormalBindingElement::PER_PART ||
      nbind == SoNormalBindingElement::PER_PART_INDEXED)
      curNormal = strip;

    for (vert = 0; vert < vertsInStrip; vert++) {
      // Do PER_VERTEX stuff
      if (mbind == SoMaterialBindingElement::PER_VERTEX ||
        mbind == SoMaterialBindingElement::PER_VERTEX_INDEXED)
        curMaterial = curVert;
      if (nbind == SoNormalBindingElement::PER_VERTEX ||
        nbind == SoNormalBindingElement::PER_VERTEX_INDEXED)
        curNormal = curVert;

      int thisVert = vert%3;

      pd[thisVert].setMaterialIndex(curMaterial);
      pd[thisVert].setNormalIndex(curNormal);
      pd[thisVert].setTextureCoordIndex(curVert);
      pd[thisVert].setCoordinateIndex(curVert);

      detail.setFaceIndex(vert);

      if (normCache != NULL)
        pvs[thisVert].setNormal(normCache->getNormals()[curNormal]);
      else
        pvs[thisVert].setNormal(ne->get(curNormal));

      pvs[thisVert].setPoint(ce->get3(curVert));
      pvs[thisVert].setMaterialIndex(curMaterial);
      if (tcb.isFunction()) {
        if (! forPicking)
          pvs[thisVert].setTextureCoords(
          tcb.get(pvs[thisVert].getPoint(),
          pvs[thisVert].getNormal()));
      }
      else
        pvs[thisVert].setTextureCoords(tcb.get(curVert));

      if (vert >= 2) {
        // Must handle per-triangle normals or materials
        // specially:
        if (mbind == SoMaterialBindingElement::PER_FACE ||
          mbind == SoMaterialBindingElement::PER_FACE_INDEXED) {
            int v = (vert-1)%3;
            pd[v].setMaterialIndex(curMaterial);
            pvs[v].setMaterialIndex(curMaterial);
            v = (vert-2)%3;
            pd[v].setMaterialIndex(curMaterial);
            pvs[v].setMaterialIndex(curMaterial);
            ++curMaterial;
        }
        if (nbind == SoNormalBindingElement::PER_FACE ||
          nbind == SoNormalBindingElement::PER_FACE_INDEXED) {
            int v = (vert-1)%3;
            pd[v].setNormalIndex(curNormal);
            pvs[v].setNormal(ne->get(curNormal));
            v = (vert-2)%3;
            pd[v].setNormalIndex(curNormal);
            pvs[v].setNormal(ne->get(curNormal));
            ++curNormal;
        }

        // Do three vertices of the triangle, being careful to
        // keep them oriented correctly (the orientation switches
        // on every other triangle):
        if (vert & 1) {
          invokeTriangleCallbacks(action, &pvs[0], &pvs[2],
            &pvs[1]);
        } else {
          invokeTriangleCallbacks(action, &pvs[0], &pvs[1],
            &pvs[2]);
        }
      }
      curVert++;
    }
  }

  // Restore USE_REST_OF_VERTICES (-1)
  if (usingUSE_REST) {
    numVertices.set1Value(numStrips-1, -1);
    numVertices.enableNotify(nvNotifyEnabled);
  }       

  state->pop();
}

////////////////////////////////////////////////////////////////////////
//
// Description:
//    Computes bounding box of vertices of triangle strips.
//
// Use: protected

void
SoTriangleStripSet::computeBBox(SoAction *action,
                                SbBox3f &box, SbVec3f &center)
                                //
                                ////////////////////////////////////////////////////////////////////////
{
  // First, compute the number of vertices the set uses
  int numStrips = (int) numVertices.getNum();
  int numVerts = 0;

  if (numStrips && numVertices[numStrips-1] < 0) {
    numVerts = -1;
  } else for (int i = 0; i < numStrips; i++) {
    numVerts += (int) numVertices[i];
  }
  computeCoordBBox(action, numVerts, box, center);
}

////////////////////////////////////////////////////////////////////////
//
// Description:
//    Overrides standard method to create an SoFaceDetail instance
//    representing a picked intersection with a triangle in the set.
//
// Use: protected, virtual

SoDetail *
SoTriangleStripSet::createTriangleDetail(SoRayPickAction *action,
                                         const SoPrimitiveVertex *v1,
                                         const SoPrimitiveVertex *,
                                         const SoPrimitiveVertex *,
                                         SoPickedPoint *pp)
                                         //
                                         ////////////////////////////////////////////////////////////////////////
{
  SoFaceDetail        *detail = new SoFaceDetail;
  const SoFaceDetail  *d;

  // Only triangles!
  detail->setNumPoints(3);

  d = (const SoFaceDetail *) v1->getDetail();

  // Copy the three point details
  detail->setPoint(0, d->getPoint(0));
  detail->setPoint(1, d->getPoint(1));
  detail->setPoint(2, d->getPoint(2));

  // The face/part indices are in the incoming details
  detail->setFaceIndex(d->getFaceIndex());
  detail->setPartIndex(d->getPartIndex());

  // Compute texture coordinates at intersection point and store it
  // in the picked point
  // Why is this only for isFunction TRUE ?
  SoTextureCoordinateBundle   tcb(action, FALSE, TRUE);
  if (tcb.isFunction())
    pp->setObjectTextureCoords(tcb.get(pp->getObjectPoint(),
    pp->getObjectNormal()));

  return detail;
}

////////////////////////////////////////////////////////////////////////
//
// Description:
//    Redefines this to invalidate caches.
//
// Use: private 

void
SoTriangleStripSet::notify(SoNotList *list)
//
////////////////////////////////////////////////////////////////////////
{
  if ((list->getLastRec()->getType() == SoNotRec::CONTAINER) &&
    ((list->getLastField() == &vertexProperty) ||
    (list->getLastField() == &numVertices))) {
      vpCache.invalidate();
      totalNumVertices = -1;
  }

  SoShape::notify(list);
}

////////////////////////////////////////////////////////////////////////
//
// Description:
//    Generates default normals using the given state and normal
//    bundle. Returns TRUE if normals were generated.
//
// Use: public

bool
SoTriangleStripSet::generateDefaultNormals(SoState *state, SoNormalBundle *nb)
//
////////////////////////////////////////////////////////////////////////
{
  int numStrips = (int) numVertices.getNum();
  int curCoord  = (int) startIndex.getValue();

  int numCoords = 0;
  SoVertexProperty* vp = getVertexProperty();
  const SoCoordinateElement *ce = NULL;
  const SbVec3f *coords = NULL;
  if (vp && (numCoords = vp->vertex.getNum()) > 0) {
    coords = vp->vertex.getValues(0);
  } else {
    ce = SoCoordinateElement::getInstance(state);
    numCoords = ce->getNum();
  }

  // Now pass the vertices from each strip to the normal bundle
  int strip, numVerts = 0;
  for (strip = 0; strip < numStrips; strip++) {
    // Figure out number of vertices in this strip
    int vertsInStrip = (int) numVertices[strip];

    // If we got USE_REST_OF_VERTICES, use the rest of the values
    // in the coordinate array:
    if (vertsInStrip < 0) {
      vertsInStrip = numCoords - numVerts;
    }

    numVerts += vertsInStrip;

    for (int vert = 0; vert < vertsInStrip-2; vert++) {
      SbVec3f coord0, coord1, coord2;
      if (coords) {
        coord0 = coords[curCoord];
        coord1 = coords[curCoord+1];
        coord2 = coords[curCoord+2];
      } else {
        coord0 = ce->get3(curCoord);
        coord1 = ce->get3(curCoord+1);
        coord2 = ce->get3(curCoord+2);
      }           
      if (vert & 1)
        nb->triangle(coord1, coord0, coord2);
      else
        nb->triangle(coord0, coord1, coord2);
      curCoord++;
    }
    curCoord += 2; // Skip last two vertices
  } /* for strip = .. */

  nb->generate(startIndex.getValue());

  // Ok, we now have more normals than we need because we sent
  // most vertices three times.  
  // rearrange things to correspond to TriStrip's idea of
  // per-vertex normals:

  int vertexAtStartOfStrip = 0;
  int numTrisAtStartOfStrip = 0;
  for (strip = 0; strip < numStrips; strip++) {
    SbVec3f n;

    // Figure out number of vertices in this strip
    int vertsInStrip = (int) numVertices[strip];

    for (int v = 0; v < vertsInStrip; v++) {
      if (v < 2) {
        n = nb->generator->getNormal(numTrisAtStartOfStrip*3+v);
        nb->generator->setNormal(vertexAtStartOfStrip+v, n);
      } else {
        n = nb->generator->getNormal(numTrisAtStartOfStrip*3+
          2+(v-2)*3);
        nb->generator->setNormal(vertexAtStartOfStrip+v, n);
      }
    }
    vertexAtStartOfStrip += vertsInStrip;
    numTrisAtStartOfStrip += vertsInStrip-2;
  }
  nb->generator->setNumNormals(numVerts+startIndex.getValue());

  // Cache the resulting normals
  setNormalCache(state, nb->getNumGeneratedNormals(),
    nb->getGeneratedNormals());

  return TRUE;
}

void SoTriangleStripSet::GLRenderInternal( SoGLRenderAction * action, uint32_t useTexCoordsAnyway, const SoShapeStyleElement * shapeStyle )
{
  // Call the appropriate render loop:
  (this->*renderFunc[useTexCoordsAnyway | 
    vpCache.getRenderCase(shapeStyle)])(action);

#ifdef DEBUG
  if (SoDebug::GetEnv("IV_DEBUG_LEGACY_RENDERING")) {
    SoDebugError::postInfo("GLRenderInternal", "%s Immediate Mode Rendering: %d Vertices", getTypeId().getName().getString(),
      totalNumVertices);
  }
#endif

}

// include ppp generated source code:
#include "SoTriangleStripSet_generated.cpp"
