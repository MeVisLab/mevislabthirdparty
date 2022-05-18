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
|      SoFaceSet
|
|   Author(s)          : Gavin Bell
|
______________  S I L I C O N   G R A P H I C S   I N C .  ____________
_______________________________________________________________________
*/


///////////////////////////////////////////////////////////////////////////
#include <Inventor/system/SbSystem.h>
#include <Inventor/system/SbOpenGL.h>
#include <Inventor/SoPickedPoint.h>
#include <Inventor/SoPrimitiveVertex.h>
#include <Inventor/actions/SoGLRenderAction.h>
#include <Inventor/actions/SoRayPickAction.h>
#include <Inventor/bundles/SoMaterialBundle.h>
#include <Inventor/bundles/SoNormalBundle.h>
#include <Inventor/bundles/SoTextureCoordinateBundle.h>
#include <Inventor/caches/SoNormalCache.h>
#include <Inventor/details/SoFaceDetail.h>
#include <Inventor/elements/SoGLCoordinateElement.h>
#include <Inventor/elements/SoGLTextureCoordinateElement.h>
#include <Inventor/elements/SoNormalBindingElement.h>
#include <Inventor/elements/SoShapeHintsElement.h>
#include <Inventor/elements/SoGLLazyElement.h>
#include <Inventor/elements/SoGLCacheContextElement.h>
#include <Inventor/nodes/SoFaceSet.h>
#include <Inventor/nodes/SoMaterialBinding.h>
#include <Inventor/nodes/SoNormalBinding.h>
#include <Inventor/elements/SoGLVBOElement.h>
#include <Inventor/SoDebug.h>

// Constants for influencing auto-caching algorithm:
const int AUTO_CACHE_FS_MIN_WITHOUT_VP = 20;

// And the number above which we'll say caches definitely SHOULDN'T be
// built (because they'll use too much memory):
const int AUTO_CACHE_FS_MAX = OIV_AUTO_CACHE_DEFAULT_MAX;


SO_NODE_SOURCE(SoFaceSet);

////////////////////////////////////////////////////////////////////////
//
// Description:
//    Constructor
//
// Use: public

SoFaceSet::SoFaceSet()
//
////////////////////////////////////////////////////////////////////////
{

  SO_NODE_CONSTRUCTOR(SoFaceSet);
  SO_NODE_ADD_FIELD(numVertices, (SO_FACE_SET_USE_REST_OF_VERTICES));
  SO_NODE_ADD_FIELD(sendAdjacency, (FALSE));

  isBuiltIn = TRUE;
  numTris = numQuads = numFaces = -1;
}

////////////////////////////////////////////////////////////////////////
//
// Description:
//    Destructor
//
// Use: private

SoFaceSet::~SoFaceSet()
//
////////////////////////////////////////////////////////////////////////
{
}

////////////////////////////////////////////////////////////////////////
//
// Description:
//    Performs GL rendering of a FaceSet.
//
// Use: protected

void
SoFaceSet::GLRender(SoGLRenderAction *action)
//
////////////////////////////////////////////////////////////////////////
{
  SoState *state = action->getState();

  // Get ShapeStyleElement
  const SoShapeStyleElement *shapeStyle = SoShapeStyleElement::get(state);

  SoVertexProperty *vp = getVertexProperty();
  
  // First see if the object is visible and should be rendered now:
  if (shapeStyle->mightNotRender()) {
    if (vpCache.mightNeedSomethingFromState(shapeStyle)) {
      vpCache.fillInColorAndTranspAvail(vp, state);
    }
    if (! shouldGLRender(action))
      return;
  }

  if (vp) {
    vp->putVBOsIntoState(state);
  }

  if (vpCache.mightNeedSomethingFromState(shapeStyle)) {

    vpCache.fillInCache(vp,  state);

    // Set up numTris/Quads/Faces and count vertices if necessary
    if (numTris < 0)
      setupNumTrisQuadsFaces();

    // If faces might be concave, we have to send them through GLU:
    SoShapeHintsElement::VertexOrdering vo;
    SoShapeHintsElement::ShapeType st;
    SoShapeHintsElement::FaceType ft;
    SoShapeHintsElement::get(state, vo, st, ft);

    if ((numQuads > 0 || numFaces > 0)
      && ft != SoShapeHintsElement::CONVEX) {

        // Use generatePrimitives for now...
        SoShape::GLRender(action);
        return;
    }


    if (vpCache.shouldGenerateNormals(shapeStyle)) {
      // See if there is a valid normal cache. If so, use it:
      SoNormalCache *normCache = getNormalCache();
      if (normCache == NULL || !normCache->isValid(state)) {
        SoNormalBundle nb(action, FALSE);
        nb.initGenerator(totalNumVertices);
        generateDefaultNormals(state, &nb);
        normCache = getNormalCache();
      }
      vpCache.numNorms = normCache->getNum();
      vpCache.normalPtr = (const char *)normCache->getNormals();
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

    if (vpCache.colorIsInVtxProp()) {
      lazyElt->send(state, SoLazyElement::ALL_MASK);
      lazyElt->sendVPPacked(state, (const unsigned char*)
        vpCache.getColors(0));
    }
    else lazyElt->send(state, SoLazyElement::ALL_MASK);

#ifdef DEBUG
    // Check for enough vertices:
    if (vpCache.numVerts < totalNumVertices + startIndex.getValue()){
      SoDebugError::post("SoFaceSet::GLRender",
        "Too few vertices specified;"
        " need %d, have %d", totalNumVertices + startIndex.getValue(),
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
    case SoNormalBindingElement::PER_PART:
    case SoNormalBindingElement::PER_PART_INDEXED:
      numNormalsNeeded = numTris + numQuads + numFaces;              
      break;
    }
    if (vpCache.getNumNormals() < numNormalsNeeded)
      SoDebugError::post("SoFaceSet::GLRender",
      "Too few normals specified;"
      " need %d, have %d", numNormalsNeeded,
      vpCache.getNumNormals());

    if ((shapeStyle->needTexCoords() || useTexCoordsAnyway) && 
      !vpCache.shouldGenerateTexCoords(shapeStyle)) {

        if (vpCache.getNumTexCoords() < 
          totalNumVertices+startIndex.getValue())
          SoDebugError::post("SoFaceSet::GLRender",
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
    case SoMaterialBindingElement::PER_PART:
    case SoMaterialBindingElement::PER_PART_INDEXED:
      numColorsNeeded = numTris + numQuads + numFaces;
      break;
    }
    if (vpCache.getNumColors() < numColorsNeeded)
      SoDebugError::post("SoFaceSet::GLRender",
      "Too few diffuse colors specified;"
      " need %d, have %d", numColorsNeeded,
      vpCache.getNumColors());
#endif

    GLRenderInternal(action, useTexCoordsAnyway, shapeStyle);

    // If doing multiple colors, turn off ColorMaterial:
    if (vpCache.getNumColors() > 1) {
      SoGLLazyElement::setColorMaterial(state, FALSE);
      ((SoGLLazyElement *)SoLazyElement::getInstance(state))->
        reset(state, SoLazyElement::DIFFUSE_MASK);
    }

    if (totalNumVertices < AUTO_CACHE_FS_MIN_WITHOUT_VP &&
      vpCache.mightNeedSomethingFromState(shapeStyle)) {
        SoGLCacheContextElement::shouldAutoCache(state,
          SoGLCacheContextElement::DO_AUTO_CACHE);
    } else if (totalNumVertices > AUTO_CACHE_FS_MAX) {
        SoGLCacheContextElement::shouldAutoCache(state,
          SoGLCacheContextElement::DONT_AUTO_CACHE);
    }           

    if (tcb) {
      delete tcb;
      state->pop();
    } else if (useTexCoordsAnyway) 
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
      lazyElt->sendVPPacked(state, (const unsigned char*)
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
    if (totalNumVertices > AUTO_CACHE_FS_MAX ) {

        SoGLCacheContextElement::shouldAutoCache(state,
          SoGLCacheContextElement::DONT_AUTO_CACHE);
    }

    // restore USE_REST_OF_VERTICES (-1)
    if (usingUSE_REST){
      numVertices.set1Value(numVertices.getNum()-1, -1);
      numVertices.enableNotify(nvNotifyEnabled);
    }           
  }
  return;
}




////////////////////////////////////////////////////////////////////////
//
// Description:
//    invalidate vpCache when notified
//
// Use: private 

void
SoFaceSet::notify(SoNotList *list)
//
////////////////////////////////////////////////////////////////////////
{
  if (list->getLastRec()->getType() == SoNotRec::CONTAINER &&
    ((list->getLastField() == &numVertices) ||
    (list->getLastField() == &vertexProperty)) ) {
      numTris = numQuads = numFaces = totalNumVertices = -1;
      vpCache.invalidate();
  }

  SoShape::notify(list);
}

///////////////////////////////////////////////////////////////////////////
//
// Description:
//      Find out how many tris, quads, and polygons there are,
//      also deal with SO_USE_REST_OF_VERTICES
//
// use: private
//
///////////////////////////////////////////////////////////////////////////
void 
SoFaceSet::setupNumTrisQuadsFaces()
{
  numTris = numQuads = numFaces = 0;
  usingUSE_REST = FALSE;
  nvNotifyEnabled = TRUE;
  const int nfaces = numVertices.getNum();
  if(nfaces && numVertices[nfaces-1]<0) {
    usingUSE_REST = TRUE;
    nvNotifyEnabled = numVertices.enableNotify(FALSE);
    totalNumVertices = 0;
    for(int i = 0; i<nfaces -1; i++)
      totalNumVertices += numVertices[i];
    numVertices.set1Value(nfaces-1, 
      vpCache.numVerts - totalNumVertices - startIndex.getValue());       
    vpCache.needFromState |=
      SoVertexPropertyCache::COORD_FROM_STATE_BIT;
    totalNumVertices = vpCache.numVerts - startIndex.getValue();    
  }
  else if (totalNumVertices <0 ){
    totalNumVertices = 0;
    for (int i=0; i< nfaces; i++){
      totalNumVertices += numVertices[i];
    }
  }

  int i = 0;

  while ((i < nfaces) && (numVertices[i] == 3)) {
    ++numTris;
    ++i; 
  }
  while ((i < nfaces) && (numVertices[i] == 4) ) {
    ++numQuads;
    ++i; 
  }
  while (i < nfaces) {
    ++numFaces;
    ++i;
  }
}    

////////////////////////////////////////////////////////////////////////
//
// Description:
//    Generates primitives (triangles) for face set
//
// Use: protected

void
SoFaceSet::generatePrimitives(SoAction *action)
//
////////////////////////////////////////////////////////////////////////
{
  // When generating primitives for picking, there is no need to
  // create details now, since they will be created in
  // createTriangleDetail() when an intersection is found (but we
  // need to use the face detail to figure out the rest of it).
  // Otherwise, we create a face detail containing the 3 points of
  // the generated triangle, using the stuff in SoShape.
  // We also delay computing default texture coordinates.
  bool forPicking = action->isOfType(SoRayPickAction::getClassTypeId());

  SoState *state = action->getState();
  // put vertex property into state, if it exists:
  state->push();
  SoVertexProperty* vp = getVertexProperty();
  if(vp){
    vp->doAction(action);
  }

  SoPrimitiveVertex           pv;
  SoFaceDetail                fd;
  SoPointDetail               pd;
  SoNormalBundle              nb(action, FALSE);
  SoTextureCoordinateBundle   tcb(action, FALSE, ! forPicking);
  const SoCoordinateElement   *ce;
  int                         curVert, vert;
  int                         face, numFaces, vertsInFace;
  Binding                     materialBinding, normalBinding;

  ce = SoCoordinateElement::getInstance(action->getState());

  materialBinding = getMaterialBinding(action);
  normalBinding   = getNormalBinding(action, &nb);

  curVert = (int) startIndex.getValue();

  if (forPicking) {
    pv.setTextureCoords(SbVec4f(0.0, 0.0, 0.0, 0.0));
    pv.setDetail(&fd);
  }
  else
    pv.setDetail(&pd);

  numFaces = numVertices.getNum();


  // For each face
  for (face = 0; face < numFaces; face++) {

    // Figure out number of vertices in this face
    vertsInFace = (int) numVertices[face];
    if (vertsInFace == SO_FACE_SET_USE_REST_OF_VERTICES)
      vertsInFace = (int) ce->getNum() - curVert;

    if (forPicking) {
      fd.setFaceIndex(face);
      fd.setPartIndex(face);
    }

    beginShape(action, POLYGON, forPicking ? NULL : &fd);

    for (vert = 0; vert < vertsInFace; vert++) {

      int matlIndex = (materialBinding == PER_VERTEX ? curVert :
        materialBinding == PER_FACE   ? face : 0);
      int normIndex = (normalBinding   == PER_VERTEX ? curVert :
        normalBinding   == PER_FACE   ? face : 0);
      int tcIndex   = tcb.isFunction() ? 0 : curVert;

      pv.setPoint(ce->get3(curVert));
      pv.setNormal(nb.get(normIndex));
      pv.setMaterialIndex(matlIndex);

      if (! tcb.isFunction())
        pv.setTextureCoords(tcb.get(tcIndex));

      if (! forPicking) {
        if (tcb.isFunction())
          pv.setTextureCoords(tcb.get(pv.getPoint(),
          pv.getNormal()));
        pd.setCoordinateIndex(curVert);
        pd.setMaterialIndex(matlIndex);
        pd.setNormalIndex(normIndex);
        pd.setTextureCoordIndex(tcIndex);
      }

      shapeVertex(&pv);

      curVert++;
    }

    endShape();
  }
  state->pop();
}

////////////////////////////////////////////////////////////////////////
//
// Description:
//    Computes bounding box of vertices of face set.
//
// Use: protected

void
SoFaceSet::computeBBox(SoAction *action, SbBox3f &box, SbVec3f &center)
//
////////////////////////////////////////////////////////////////////////
{
  // First, compute the number of vertices the face set uses

  int numFaces = numVertices.getNum();
  int numVerts = 0;

  if (numFaces == 0)
    return;

  // Count up total number of vertices used. If the last entry in
  // numVerts is SO_FACE_SET_USE_REST_OF_VERTICES, then we need
  // to use all of the vertices.
  if (numVertices[numFaces-1] == SO_FACE_SET_USE_REST_OF_VERTICES)
    numVerts = -1;
  else
    for (int i = 0; i < numFaces; i++)
      numVerts += (int) numVertices[i];

  // Next, call the method on SoNonIndexedShape that computes the
  // bounding box and center of the given number of coordinates
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
SoFaceSet::createTriangleDetail(SoRayPickAction *action,
                                const SoPrimitiveVertex *v1,
                                const SoPrimitiveVertex *,
                                const SoPrimitiveVertex *,
                                SoPickedPoint *pp)
                                //
                                ////////////////////////////////////////////////////////////////////////
{
  // When we get here, the detail in each vertex already points to an
  // SoFaceDetail (on the stack in generatePrimitives()). This detail
  // contains the correct face/part index for the intersected face.
  // However, this face detail does not contain any point details.
  // We have to create a new SoFaceDetail instance and set up the
  // SoPointDetail instances inside it to contain the vertices of
  // the picked face. We also need to compute texture coordinates.

  SoFaceDetail        *newFD = new SoFaceDetail;
  const SoFaceDetail  *oldFD = (const SoFaceDetail *) v1->getDetail();

  // Find out which face was hit
  int hitFace = (int) oldFD->getFaceIndex();

  // Find the index of the first vertex of the face: add up the
  // number of vertices in each previous face
  int curVert = (int) startIndex.getValue();
  for (int face = 0; face < hitFace; face++)
    curVert += (int) numVertices[face];

  // Figure out how many vertices are in the hit face
  int vertsInFace = (int) numVertices[hitFace];
  if (vertsInFace == SO_FACE_SET_USE_REST_OF_VERTICES) {
    const SoCoordinateElement *ce = 
      SoCoordinateElement::getInstance(action->getState());
    vertsInFace = (int) ce->getNum() - curVert;
  }

  // Make room in the detail for vertices
  newFD->setNumPoints(vertsInFace);

  // We need the bindings to set up the material/normals stuff
  Binding materialBinding = getMaterialBinding(action);
  Binding normalBinding   = getNormalBinding(action, NULL);

  // Store each vertex in the detail
  SoPointDetail               pd;
  SoTextureCoordinateBundle   tcb(action, FALSE);
  for (int vert = 0; vert < vertsInFace; vert++) {
    pd.setCoordinateIndex(curVert);
    pd.setMaterialIndex(materialBinding == PER_VERTEX ? curVert :
      materialBinding == PER_FACE   ? hitFace : 0);
    pd.setNormalIndex(normalBinding == PER_VERTEX ? curVert :
      normalBinding == PER_FACE   ? hitFace : 0);
    pd.setTextureCoordIndex(tcb.isFunction() ? 0 : curVert);

    newFD->setPoint(vert, &pd);

    curVert++;
  }

  // Compute texture coordinates at intersection point and store it
  // in the picked point
  if (tcb.isFunction())
    pp->setObjectTextureCoords(tcb.get(pp->getObjectPoint(),
    pp->getObjectNormal()));

  // The face/part indices are in the incoming details
  newFD->setFaceIndex(hitFace);
  newFD->setPartIndex(hitFace);

  return newFD;
}

////////////////////////////////////////////////////////////////////////
//
// Description:
//    Returns current material binding from action's state.
//
// Use: private, static

SoFaceSet::Binding
SoFaceSet::getMaterialBinding(SoAction *action)
//
////////////////////////////////////////////////////////////////////////
{
  switch (SoMaterialBindingElement::get(action->getState())) {
      case SoMaterialBindingElement::OVERALL:
        return OVERALL;

      case SoMaterialBindingElement::PER_PART:
      case SoMaterialBindingElement::PER_PART_INDEXED:
      case SoMaterialBindingElement::PER_FACE:
      case SoMaterialBindingElement::PER_FACE_INDEXED:
        return PER_FACE;

      case SoMaterialBindingElement::PER_VERTEX:
      case SoMaterialBindingElement::PER_VERTEX_INDEXED:
        return PER_VERTEX;
  }
  return OVERALL; // Shut up SGI C++ compiler
}

////////////////////////////////////////////////////////////////////////
//
// Description:
//    Returns current normal binding from action's state.
//
// Use: private, static

SoFaceSet::Binding
SoFaceSet::getNormalBinding(SoAction *action, SoNormalBundle *nb)
//
////////////////////////////////////////////////////////////////////////
{
  // Do automatic normal generation, if necessary:
  if (nb != NULL && figureNormals(action->getState(), nb))
    return PER_VERTEX;

  switch (SoNormalBindingElement::get(action->getState())) {
      case SoNormalBindingElement::OVERALL:
        return OVERALL;

      case SoNormalBindingElement::PER_PART:
      case SoNormalBindingElement::PER_PART_INDEXED:
      case SoNormalBindingElement::PER_FACE:
      case SoNormalBindingElement::PER_FACE_INDEXED:
        return PER_FACE;

      case SoNormalBindingElement::PER_VERTEX:
      case SoNormalBindingElement::PER_VERTEX_INDEXED:
        return PER_VERTEX;
  }
  return OVERALL; // Shut up SGI C++ compiler
}

////////////////////////////////////////////////////////////////////////
//
// Description:
//    Figures out normals, if necessary.  Returns TRUE if it was
//    necessary.
//
// Use: private

bool
SoFaceSet::figureNormals(SoState *state, SoNormalBundle *nb)
//
////////////////////////////////////////////////////////////////////////
{
  // See if there is a valid normal cache. If so, tell the normal
  // bundle to use it.
  SoNormalCache *normCache = getNormalCache();
  if (normCache != NULL && normCache->isValid(state)) {
    nb->set(normCache->getNum(), normCache->getNormals());
    return TRUE;
  }

  int numNeeded = 0, numFaces = (int) numVertices.getNum();

  if (numFaces == 0)
    return FALSE;

  // Count number of vertices:
  if (numVertices[numFaces - 1] == SO_FACE_SET_USE_REST_OF_VERTICES) {
    const SoCoordinateElement *ce =
      SoCoordinateElement::getInstance(state);
    numNeeded = (int) ce->getNum();
  }
  else
    for (int i = 0; i < numFaces; i++)
      numNeeded += (int) numVertices[i];

  if (nb->shouldGenerate(numNeeded)) {
    generateDefaultNormals(state, nb);
    return TRUE;
  }
  return FALSE;
}

////////////////////////////////////////////////////////////////////////
//
// Description:
//    Generates default normals using the given state and normal
//    bundle. Returns TRUE if normals were generated.
//
// Use: extender, virtual

bool
SoFaceSet::generateDefaultNormals(SoState *state, SoNormalBundle *nb)
//
////////////////////////////////////////////////////////////////////////
{
  int                         numFaces, curCoord, vertsInFace, i, j;
  int                         startInd;
  const SoCoordinateElement   *ce = NULL;
  const SbVec3f               *vpCoords = NULL;

  int numCoords = 0;
  SoVertexProperty* vp = getVertexProperty();
  if (vp && (numCoords = vp->vertex.getNum()) > 0) {
    vpCoords = vp->vertex.getValues(0);
  } else {
    ce = SoCoordinateElement::getInstance(state);
    numCoords = ce->getNum();
  }


  numFaces = (int) numVertices.getNum();
  curCoord = startInd = (int) startIndex.getValue();

  for (i = 0; i < numFaces; i++) {
    nb->beginPolygon();

    vertsInFace = (int) numVertices[i];
    if (vertsInFace == SO_FACE_SET_USE_REST_OF_VERTICES)
      vertsInFace = numCoords - curCoord;

    for (j = 0; j < vertsInFace; j++) {
      if(ce)  nb->polygonVertex(ce->get3(curCoord));
      else    nb->polygonVertex(vpCoords[curCoord]); 
      curCoord++;
    }
    nb->endPolygon();
  }
  nb->generate(startInd);

  // Cache the resulting normals
  setNormalCache(state, nb->getNumGeneratedNormals(),
    nb->getGeneratedNormals());

  return TRUE;
}

void SoFaceSet::GLRenderInternal( SoGLRenderAction * action, uint32_t useTexCoordsAnyway, const SoShapeStyleElement * shapeStyle )
{
  SoState* state = action->getState();
  SoGLLazyElement* lazyElt = NULL;
  lazyElt = (SoGLLazyElement *)SoLazyElement::getInstance(state);

  bool fastPathTaken = false;
  // check for cases where GL Vertex Arrays can be used:
  if (SoVBO::isVertexArrayRenderingAllowed() &&
    (vpCache.getNumVertices()>0) &&
    (vpCache.getNumNormals()==0 || (vpCache.getNormalBinding()==SoNormalBindingElement::PER_VERTEX || vpCache.getNormalBinding()==SoNormalBindingElement::PER_VERTEX_INDEXED)) &&
    // VA rendering is only possible if there is a color VBO, since it manages the packed color swapping
    ((getMaterialBinding(action)!=PER_VERTEX) || SoGLVBOElement::getInstance(state)->getVBO(SoGLVBOElement::COLOR_VBO)) &&
    (vpCache.getNumTexCoords()==0 || (vpCache.getTexCoordBinding() == SoTextureCoordinateBindingElement::PER_VERTEX_INDEXED)))
  {
    fastPathTaken = true;
    if (numTris > 0 || numQuads > 0) {
      bool useVBO = beginVertexArrayRendering(action);
      if (numTris > 0) {
        SoGLLazyElement::drawArrays(state, sendAdjacency.getValue()?GL_TRIANGLES_ADJACENCY:GL_TRIANGLES, startIndex.getValue(), numTris*3);
      }
      if (numQuads > 0) {
        SoGLLazyElement::drawArrays(state, GL_QUADS, startIndex.getValue() + numTris*3, numQuads*4);
      }

#ifdef DEBUG
      if (SoDebug::GetEnv("IV_DEBUG_VBO_RENDERING")) {
        SoDebugError::postInfo("GLRenderInternal", "%s VA Rendering: %d Tris %d Quads", getTypeId().getName().getString(), numTris, numQuads);
      }
#endif

      endVertexArrayRendering(action, useVBO);
    }
  }
  // Call the appropriate render loops:
  if (numTris > 0 && !fastPathTaken) {
    (this->*TriRenderFunc[useTexCoordsAnyway | vpCache.getRenderCase(shapeStyle)])(action);
#ifdef DEBUG
    if (SoDebug::GetEnv("IV_DEBUG_LEGACY_RENDERING")) {
      SoDebugError::postInfo("GLRenderInternal", "%s Immediate Mode Rendering: %d Triangles", getTypeId().getName().getString(), numTris);
    }
#endif
  }
  if (numQuads > 0 && !fastPathTaken) {
    (this->*QuadRenderFunc[useTexCoordsAnyway | vpCache.getRenderCase(shapeStyle)])(action);
#ifdef DEBUG
    if (SoDebug::GetEnv("IV_DEBUG_LEGACY_RENDERING")) {
      SoDebugError::postInfo("GLRenderInternal", "%s Immediate Mode Rendering: %d Quads", getTypeId().getName().getString(),
        numQuads);
    }
#endif
  }
  if (numFaces > 0) {
    (this->*GenRenderFunc[useTexCoordsAnyway | vpCache.getRenderCase(shapeStyle)])(action);
#ifdef DEBUG
    if (SoDebug::GetEnv("IV_DEBUG_LEGACY_RENDERING")) {
      SoDebugError::postInfo("GLRenderInternal", "%s Immediate Mode Rendering: %d Faces", getTypeId().getName().getString(),
        numFaces);
    }
#endif
  }
}

// include ppp generated source code:
#include "SoFaceSet_generated.cpp"
