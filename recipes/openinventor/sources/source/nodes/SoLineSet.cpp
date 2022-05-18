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
|      SoLineSet
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
#include <Inventor/actions/SoGetBoundingBoxAction.h>
#include <Inventor/actions/SoRayPickAction.h>
#include <Inventor/bundles/SoMaterialBundle.h>
#include <Inventor/bundles/SoTextureCoordinateBundle.h>
#include <Inventor/caches/SoBoundingBoxCache.h>
#include <Inventor/details/SoLineDetail.h>
#include <Inventor/elements/SoDrawStyleElement.h>
#include <Inventor/elements/SoGLCoordinateElement.h>
#include <Inventor/elements/SoGLTextureCoordinateElement.h>
#include <Inventor/elements/SoGLNormalElement.h>
#include <Inventor/elements/SoLightModelElement.h>
#include <Inventor/elements/SoMaterialBindingElement.h>
#include <Inventor/elements/SoNormalBindingElement.h>
#include <Inventor/elements/SoGLCacheContextElement.h>
#include <Inventor/elements/SoGLVBOElement.h>
#include <Inventor/misc/SoState.h>
#include <Inventor/nodes/SoLineSet.h>
#include <Inventor/SoDebug.h>

// Constants for influencing auto-caching algorithm:

// If fewer than this many lines, AND not using the vertexProperty
// node, auto-cache.  

const int AUTO_CACHE_LS_MIN_WITHOUT_VP = 20;

// And the number above which we'll say caches definitely SHOULDN'T be
// built (because they'll use too much memory):
const int AUTO_CACHE_LS_MAX = OIV_AUTO_CACHE_DEFAULT_MAX;

// 32 different rendering loops; the 5 bits used to determine the
// rendering case are:
// 43210  BITS            Routine suffix
// -----  ----            --------------
// 00...  Overall mtl     (Om)
// 01...  Part mtl        (Pm)
// 10...  Face mtl        (Fm)
// 11...  Vtx mtl         (Vm)
// ..00.  Overall/No norm (On)
// ..01.  Part norm       (Pn)
// ..10.  Face norm       (Fn)
// ..11.  Vtx norm        (Vn)
// ....0  No texcoord     -none-
// ....1  Vtx texcoord    (T)

// Note that with line sets, Parts are line segments, 
// Faces are polylines.
//
SoLineSet::PMLS SoLineSet::renderFunc[32] = {
  &SoLineSet::OmOn, &SoLineSet::OmOnT,
  &SoLineSet::OmPn, &SoLineSet::OmPnT,
  &SoLineSet::OmFn, &SoLineSet::OmFnT,
  &SoLineSet::OmVn, &SoLineSet::OmVnT,
  &SoLineSet::PmOn, &SoLineSet::PmOnT,
  &SoLineSet::PmPn, &SoLineSet::PmPnT,
  &SoLineSet::PmFn, &SoLineSet::PmFnT,
  &SoLineSet::PmVn, &SoLineSet::PmVnT,
  &SoLineSet::FmOn, &SoLineSet::FmOnT,
  &SoLineSet::FmPn, &SoLineSet::FmPnT,
  &SoLineSet::FmFn, &SoLineSet::FmFnT,
  &SoLineSet::FmVn, &SoLineSet::FmVnT,
  &SoLineSet::VmOn, &SoLineSet::VmOnT,
  &SoLineSet::VmPn, &SoLineSet::VmPnT,
  &SoLineSet::VmFn, &SoLineSet::VmFnT,
  &SoLineSet::VmVn, &SoLineSet::VmVnT,
};

SO_NODE_SOURCE(SoLineSet);

////////////////////////////////////////////////////////////////////////
//
// Description:
//    Constructor
//
// Use: public

SoLineSet::SoLineSet()
//
////////////////////////////////////////////////////////////////////////
{
  SO_NODE_CONSTRUCTOR(SoLineSet);
  SO_NODE_ADD_FIELD(numVertices,  (SO_LINE_SET_USE_REST_OF_VERTICES));
  SO_NODE_ADD_FIELD(sendAdjacency, (FALSE));
  SO_NODE_ADD_FIELD(independentLines, (FALSE));
  isBuiltIn = TRUE;
  totalNumVertices = -1;
}

////////////////////////////////////////////////////////////////////////
//
// Description:
//    Destructor
//
// Use: private

SoLineSet::~SoLineSet()
//
////////////////////////////////////////////////////////////////////////
{
}



////////////////////////////////////////////////////////////////////////
//
// Description:
//    Generates line segments representing a line set.
//
// Use: protected

void
SoLineSet::generatePrimitives(SoAction *action)
//
////////////////////////////////////////////////////////////////////////
{
  SoState *state = action->getState();
  state->push();
  // put vertex property into state, if it exists:
  SoVertexProperty* vp = getVertexProperty();
  if(vp){
    vp->doAction(action);
  }

  // When generating primitives for picking, delay computing default
  // texture coordinates
  bool forPicking = action->isOfType(SoRayPickAction::getClassTypeId());

  SoPrimitiveVertex           pvs[2], *pv;
  SoLineDetail                detail;
  SoPointDetail               pd;
  SoTextureCoordinateBundle   tcb(action, FALSE, ! forPicking);
  const SoCoordinateElement   *ce;
  int                         curVert, curSeg, curNormal, curMaterial, vert;
  int                         line, numLines, vertsInLine;
  Binding                     materialBinding, normalBinding;


  materialBinding = getMaterialBinding(action);
  normalBinding   = getNormalBinding(action);

  // Test for auto-normal case
  const SoNormalElement *ne = SoNormalElement::getInstance(state);
  if (ne->getNum() == 0) {
    normalBinding = OVERALL;
  }

  curVert = (int) startIndex.getValue();
  curSeg  = 0;

  ce = SoCoordinateElement::getInstance(state);

  curMaterial = (materialBinding == PER_VERTEX ? curVert : 0);
  curNormal   = (normalBinding   == PER_VERTEX ? curVert : 0);

  if (forPicking) {
    SbVec4f tc(0.0, 0.0, 0.0, 0.0);
    pvs[0].setTextureCoords(tc);
    pvs[1].setTextureCoords(tc);
  }

  pvs[0].setDetail(&detail);
  pvs[1].setDetail(&detail);

  if (normalBinding == OVERALL) {
    if (ne->getNum() > 0) {
      pvs[0].setNormal(ne->get(0));
      pvs[1].setNormal(ne->get(0));
    } else {
      pvs[0].setNormal(SbVec3f(0,0,0));
      pvs[1].setNormal(SbVec3f(0,0,0));
    }           
  }

  // For each polyline
  bool independent = independentLines.getValue();
  numLines = independent ? (ce->getNum() - startIndex.getValue()) / 2 : numVertices.getNum();
  for (line = 0; line < numLines; line++) {

    detail.setLineIndex(line);

    // Figure out number of vertices in this line
    vertsInLine = independent ? 2 : (int) numVertices[line];
    if (vertsInLine == SO_LINE_SET_USE_REST_OF_VERTICES)
      vertsInLine = (int) ce->getNum() - curVert;

    for (vert = 0; vert < vertsInLine; vert++) {

      pv = &pvs[vert % 2];

      pv->setPoint(ce->get3(curVert));

      if (materialBinding == PER_VERTEX && vert > 0)
        pv->setMaterialIndex(++curMaterial);
      if (normalBinding == PER_VERTEX && vert > 0)
        pv->setNormal(ne->get(++curNormal));

      // Set up a point detail for the current vertex
      pd.setCoordinateIndex(curVert);
      pd.setMaterialIndex(curMaterial);
      pd.setNormalIndex(curNormal);
      pd.setTextureCoordIndex(curVert);

      // Replace the appropriate point detail in the line
      // detail, based on the vertex index
      if ((vert & 1) == 0)
        detail.setPoint0(&pd);
      else
        detail.setPoint1(&pd);

      if (tcb.isFunction()) {
        if (! forPicking)
          pv->setTextureCoords(tcb.get(pv->getPoint(),
          pv->getNormal()));
      }
      else
        pv->setTextureCoords(tcb.get(curVert));

      if (vert > 0) {
        detail.setPartIndex(curSeg++);

        invokeLineSegmentCallbacks(action,
          &pvs[(vert - 1) % 2],
          &pvs[(vert - 0) % 2]);

        if (materialBinding == PER_SEGMENT) {
          curMaterial++;
          pvs[0].setMaterialIndex(curMaterial);
          pvs[1].setMaterialIndex(curMaterial);
        }
        if (normalBinding == PER_SEGMENT) {
          curNormal++;
          pvs[0].setNormal(ne->get(curNormal));
          pvs[1].setNormal(ne->get(curNormal));
        }
      }

      curVert++;
    }

    if (materialBinding == PER_LINE) {
      curMaterial++;
      pvs[0].setMaterialIndex(curMaterial);
      pvs[1].setMaterialIndex(curMaterial);
    }
    if (normalBinding == PER_LINE) {
      curNormal++;
      pvs[0].setNormal(ne->get(curNormal));
      pvs[1].setNormal(ne->get(curNormal));
    }
  }
  state->pop();
}

////////////////////////////////////////////////////////////////////////
//
// Description:
//    Redefines this to tell open caches that they contain lines.
//
// Use: extender

void
SoLineSet::getBoundingBox(SoGetBoundingBoxAction *action)
//
////////////////////////////////////////////////////////////////////////
{
  // Let our parent class do the real work
  SoNonIndexedShape::getBoundingBox(action);

  // If there are any open bounding box caches, tell them that they
  // contain lines
  SoBoundingBoxCache::setHasLinesOrPoints(action->getState());
}

////////////////////////////////////////////////////////////////////////
//
// Description:
//    Computes bounding box of vertices of line set.
//
// Use: protected

void
SoLineSet::computeBBox(SoAction *action, SbBox3f &box, SbVec3f &center)
//
////////////////////////////////////////////////////////////////////////
{
  int numVerts = 0;
  if (independentLines.getValue()) {
    numVerts = -1;
  } else {
    // First, compute the number of vertices the line set uses
    int numLines = numVertices.getNum();
    if (numLines == 0)
      return;

    // Count up total number of vertices used. If the last entry in
    // numVertices is SO_LINE_SET_USE_REST_OF_VERTICES, then we need
    // to use all of the vertices.
    if (numVertices[numLines - 1] == SO_LINE_SET_USE_REST_OF_VERTICES) {
      numVerts = -1;
    }
    else
    {
      for (int i = 0; i < numLines; i++) {
        numVerts += (int)numVertices[i];
      }
    }
  }
  // Next, call the method on SoNonIndexedShape that computes the
  // bounding box and center of the given number of coordinates
  computeCoordBBox(action, numVerts, box, center);
}

////////////////////////////////////////////////////////////////////////
//
// Description:
//    Overrides standard method to create an SoLineDetail instance
//    representing a picked intersection with a vertex of a line set.
//
// Use: protected, virtual

SoDetail *
SoLineSet::createLineSegmentDetail(SoRayPickAction *action,
                                   const SoPrimitiveVertex *v1,
                                   const SoPrimitiveVertex *,
                                   SoPickedPoint *pp)
                                   //
                                   ////////////////////////////////////////////////////////////////////////
{
  SoLineDetail        *detail = new SoLineDetail;
  const SoLineDetail  *d;

  d = (const SoLineDetail *) v1->getDetail();

  detail->setPoint0(d->getPoint0());
  detail->setPoint1(d->getPoint1());

  // Compute texture coordinates at intersection point and store it
  // in the picked point
  SoTextureCoordinateBundle   tcb(action, FALSE);
  if (tcb.isFunction())
    pp->setObjectTextureCoords(tcb.get(pp->getObjectPoint(),
    pp->getObjectNormal()));

  // The face/part indices are in the incoming details
  detail->setLineIndex(d->getLineIndex());
  detail->setPartIndex(d->getPartIndex());

  return detail;
}

////////////////////////////////////////////////////////////////////////
//
// Description:
//    Returns current material binding from action's state.
//
// Use: private, static

SoLineSet::Binding
SoLineSet::getMaterialBinding(SoAction *action)
//
////////////////////////////////////////////////////////////////////////
{
  switch (SoMaterialBindingElement::get(action->getState())) {
      case SoMaterialBindingElement::OVERALL:
        return OVERALL;

      case SoMaterialBindingElement::PER_PART:
      case SoMaterialBindingElement::PER_PART_INDEXED:
        return PER_SEGMENT;

      case SoMaterialBindingElement::PER_FACE:
      case SoMaterialBindingElement::PER_FACE_INDEXED:
        return PER_LINE;

      case SoMaterialBindingElement::PER_VERTEX:
      case SoMaterialBindingElement::PER_VERTEX_INDEXED:
        return PER_VERTEX;
  }
  return OVERALL; // Shut up C++ compiler
}

////////////////////////////////////////////////////////////////////////
//
// Description:
//    Returns current normal binding from action's state.
//
// Use: private, static

SoLineSet::Binding
SoLineSet::getNormalBinding(SoAction *action)
//
////////////////////////////////////////////////////////////////////////
{
  switch (SoNormalBindingElement::get(action->getState())) {

      case SoNormalBindingElement::OVERALL:
        return OVERALL;

      case SoNormalBindingElement::PER_PART:
      case SoNormalBindingElement::PER_PART_INDEXED:
        return PER_SEGMENT;

      case SoNormalBindingElement::PER_FACE:
      case SoNormalBindingElement::PER_FACE_INDEXED:
        return PER_LINE;

      case SoNormalBindingElement::PER_VERTEX:
      case SoNormalBindingElement::PER_VERTEX_INDEXED:
        return PER_VERTEX;
  }
  return OVERALL; // Shut up C++ compiler
}

////////////////////////////////////////////////////////////////////////
//
// Description:
//    Returns TRUE if normal binding is AUTO and there aren't enough
//    PER_VERTEX normals, in which case we turn off lighting and draw
//    BASE_COLOR.
//
// Use: private, static

bool
SoLineSet::wouldGenerateNormals(SoState *state)
//
////////////////////////////////////////////////////////////////////////
{
  if (SoNormalBindingElement::get(state) ==
    SoNormalBindingElement::PER_VERTEX_INDEXED) {

      // Figure out how many normals we need:
      int numVerts = 0;
      if (independentLines.getValue()) {
        numVerts = (int)(SoCoordinateElement::getInstance(state))->getNum();
      }
      else {
        int numLines = (int)numVertices.getNum();

        if (numLines == 0)
          return FALSE;

        // Count up total number of vertices used. If the last entry in
        // numVertices is SO_LINE_SET_USE_REST_OF_VERTICES, then we need
        // to use all of the vertices.
        if (numVertices[numLines - 1] == SO_LINE_SET_USE_REST_OF_VERTICES)
          numVerts =
          (int)(SoCoordinateElement::getInstance(state))->getNum();
        else for (int i = 0; i < numLines; i++)
          numVerts += (int)numVertices[i];
      }
      const SoNormalElement *ne = SoNormalElement::getInstance(state);
      if (numVerts > ne->getNum()) return TRUE;
  }

  return FALSE;
}


////////////////////////////////////////////////////////////////////////
//
// Description:
//    Implements GL rendering.
//
// Use: extender

void
SoLineSet::GLRender(SoGLRenderAction *action)
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

  if (vp) {
    vp->putVBOsIntoState(state);
  }

  if (vpCache.mightNeedSomethingFromState(shapeStyle)) {
    // push state, in case we need to turn off lighting:
    state->push();
    vpCache.fillInCache(vp, state);

    if (vpCache.shouldGenerateNormals(shapeStyle)) {
      // turn off lighting
      SoGLLazyElement::setLightModel(state, SoLazyElement::BASE_COLOR);
      // reset shapeStyle
      shapeStyle =        
        (SoShapeStyleElement*)SoShapeStyleElement::get(state);
    }


    // If using USE_REST_OF_VERTICES (-1), need to figure out how
    // many vertices there are every time:
    bool usingUSE_REST = FALSE;
    bool nvNotifyEnabled = TRUE;
    int numPolylines = numVertices.getNum();
    if (independentLines.getValue()) {
      totalNumVertices = vpCache.numVerts - startIndex.getValue();
    }
    else {
      if (numPolylines && numVertices[numPolylines - 1] < 0) {
        usingUSE_REST = TRUE;
        nvNotifyEnabled = numVertices.enableNotify(FALSE);
        totalNumVertices = 0;
        for (int i = 0; i < numPolylines - 1; i++)
          totalNumVertices += numVertices[i];

        numVertices.set1Value(numPolylines - 1,
          vpCache.numVerts - totalNumVertices - startIndex.getValue());
        totalNumVertices = vpCache.numVerts - startIndex.getValue();
        vpCache.needFromState |=
          SoVertexPropertyCache::COORD_FROM_STATE_BIT;
      } else if (totalNumVertices < 0) {
        totalNumVertices = 0;
        for (int i = 0; i < numPolylines; i++)
          totalNumVertices += numVertices[i];
      }
    }

    SoTextureCoordinateBundle *tcb = NULL;
    uint32_t useTexCoordsAnyway = 0;
    if (vpCache.shouldGenerateTexCoords(shapeStyle)) {
      tcb = new SoTextureCoordinateBundle(action, TRUE, TRUE);
    }
    else if (shapeStyle->isTextureFunction() && vpCache.haveTexCoordsInVP()){    
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
    // Check for enough colors, normals, texcoords, vertices:
    if (vpCache.numVerts < startIndex.getValue()+totalNumVertices){
      SoDebugError::post("SoLineSet::GLRender",
        "Too few vertices specified;"
        " need %d, have %d", startIndex.getValue()+totalNumVertices,
        vpCache.numVerts);
    }
    int numNormalsNeeded = 0;
    if (shapeStyle->needNormals()) switch (vpCache.getNormalBinding()) {
    case SoNormalBindingElement::OVERALL:
      numNormalsNeeded = 1;
      break;
    case SoNormalBindingElement::PER_VERTEX:
    case SoNormalBindingElement::PER_VERTEX_INDEXED:
      numNormalsNeeded = totalNumVertices + startIndex.getValue();
      break;
    case SoNormalBindingElement::PER_PART:
    case SoNormalBindingElement::PER_PART_INDEXED:
      {
        for (int i = 0; i < numPolylines; i++) 
          numNormalsNeeded += numVertices[i]-1;
      }
      break;
    case SoNormalBindingElement::PER_FACE:
    case SoNormalBindingElement::PER_FACE_INDEXED:
      numNormalsNeeded = numPolylines;
      break;
    }
    if (vpCache.getNumNormals() < numNormalsNeeded)
      SoDebugError::post("SoLineSet::GLRender",
      "Too few normals specified;"
      " need %d, have %d", numNormalsNeeded,
      vpCache.getNumNormals());

    if ((shapeStyle->needTexCoords() || useTexCoordsAnyway) && 
      !vpCache.shouldGenerateTexCoords(shapeStyle)) {

        if (vpCache.getNumTexCoords() < 
          totalNumVertices+startIndex.getValue())
          SoDebugError::post("SoLineSet::GLRender",
          "Too few texture coordinates specified;"
          " need %d, have %d", totalNumVertices + startIndex.getValue(),
          vpCache.getNumTexCoords());
    }
    int numColorsNeeded = 0;
    switch (vpCache.getMaterialBinding()) {
    case SoMaterialBindingElement::OVERALL:
      break;
    case SoMaterialBindingElement::PER_VERTEX:
    case SoMaterialBindingElement::PER_VERTEX_INDEXED:
      numColorsNeeded = totalNumVertices+startIndex.getValue();
      break;
    case SoMaterialBindingElement::PER_PART:
    case SoMaterialBindingElement::PER_PART_INDEXED:
      {
        for (int i = 0; i < numPolylines; i++) 
          numColorsNeeded += numVertices[i]-1;
      }
      break;
    case SoMaterialBindingElement::PER_FACE:
    case SoMaterialBindingElement::PER_FACE_INDEXED:
      numColorsNeeded = numPolylines;
      break;
    }
    if (vpCache.getNumColors() < numColorsNeeded)
      SoDebugError::post("SoLineSet::GLRender",
      "Too few diffuse colors specified;"
      " need %d, have %d", numColorsNeeded,
      vpCache.getNumColors());
#endif

    GLRenderInternal(action, useTexCoordsAnyway, shapeStyle);

    // If doing multiple colors, turn off ColorMaterial:
    if (vpCache.getNumColors() > 1) {
      ((SoGLLazyElement *)SoLazyElement::getInstance(state))->
        reset(state, SoLazyElement::DIFFUSE_MASK);
      SoGLLazyElement::setColorMaterial(state, FALSE);
    }

    // Restore USE_REST_OF_VERTICES (-1)
    if (usingUSE_REST) {
      numVertices.set1Value(numPolylines-1, -1);
      numVertices.enableNotify(nvNotifyEnabled);
    }           

    // Influence auto-caching algorithm:
    if (totalNumVertices < AUTO_CACHE_LS_MIN_WITHOUT_VP &&
      vpCache.mightNeedSomethingFromState(shapeStyle)) {
        SoGLCacheContextElement::shouldAutoCache(state,
          SoGLCacheContextElement::DO_AUTO_CACHE);
    } else if (totalNumVertices > AUTO_CACHE_LS_MAX) {
        SoGLCacheContextElement::shouldAutoCache(state,
          SoGLCacheContextElement::DONT_AUTO_CACHE);
    }           

    if (tcb) {
      delete tcb;
    }
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
    if (totalNumVertices > AUTO_CACHE_LS_MAX) {

        SoGLCacheContextElement::shouldAutoCache(state,
          SoGLCacheContextElement::DONT_AUTO_CACHE);
    }           
  }

  return;
}


////////////////////////////////////////////////////////////////////////
//
// Description:
//    Redefines this to invalidate caches.
//
// Use: private 

void
SoLineSet::notify(SoNotList *list)
//
////////////////////////////////////////////////////////////////////////
{
  if ((list->getLastRec()->getType() == SoNotRec::CONTAINER) &&
    ((list->getLastField() == &vertexProperty) ||
    (list->getLastField() == &numVertices) ||
    (list->getLastField() == &independentLines))) {
      vpCache.invalidate();
      totalNumVertices = -1;
  }

  SoShape::notify(list);
}

void SoLineSet::GLRenderInternal( SoGLRenderAction * action, uint32_t useTexCoordsAnyway, const SoShapeStyleElement * shapeStyle )
{
  SoState * state = action->getState();

  SoGLLazyElement *lazyElt;
  lazyElt = (SoGLLazyElement *) SoLazyElement::getInstance(state);

  // check for cases where GL Vertex Arrays can be used:
  if ((totalNumVertices>0) && 
    SoVBO::isVertexArrayRenderingAllowed() &&
    (vpCache.getNumVertices()>0) &&
    (vpCache.getNumNormals()==0 || (vpCache.getNormalBinding()==SoNormalBindingElement::PER_VERTEX || vpCache.getNormalBinding()==SoNormalBindingElement::PER_VERTEX_INDEXED)) &&
    // VA rendering is only possible if there is a color VBO, since it manages the packed color swapping
    ((getMaterialBinding(action)!=PER_VERTEX) || SoGLVBOElement::getInstance(state)->getVBO(SoGLVBOElement::COLOR_VBO)) &&
    (vpCache.getNumTexCoords()==0 || (vpCache.getTexCoordBinding() == SoTextureCoordinateBindingElement::PER_VERTEX_INDEXED)) &&
    (SoDrawStyleElement::get(action->getState()) != SoDrawStyleElement::POINTS))
  {
    bool useVBO = beginVertexArrayRendering(action);

    int offset = startIndex.getValue();

    if (independentLines.getValue()) {
      SoGLLazyElement::drawArrays(state, GL_LINES, offset, totalNumVertices);
    }
    else {
      const int np = numVertices.getNum();
      const int32_t* numverts = numVertices.getValues(0);
      GLuint mode = sendAdjacency.getValue() ? GL_LINE_STRIP_ADJACENCY : GL_LINE_STRIP;

      for (int polyline = 0; polyline < np; polyline++) {
        const int nv = (*numverts);
        SoGLLazyElement::drawArrays(state, mode, offset, nv);
        ++numverts;
        offset += nv;
      }
    }

#ifdef DEBUG
    if (SoDebug::GetEnv("IV_DEBUG_VBO_RENDERING")) {
      SoDebugError::postInfo("GLRenderInternal", "%s VA Rendering: %d Vertices", getTypeId().getName().getString(), totalNumVertices);
    }
#endif

    endVertexArrayRendering(action, useVBO);
  } else {

    // Call the appropriate render loop:
    (this->*renderFunc[useTexCoordsAnyway | vpCache.getRenderCase(shapeStyle)])(action);

#ifdef DEBUG
    if (SoDebug::GetEnv("IV_DEBUG_LEGACY_RENDERING")) {
      SoDebugError::postInfo("GLRenderInternal", "%s Immediate Mode Rendering: %d Polylines", getTypeId().getName().getString(), totalNumVertices);
    }
#endif
  }
}

// include ppp generated source code:
#include "SoLineSet_generated.cpp"
