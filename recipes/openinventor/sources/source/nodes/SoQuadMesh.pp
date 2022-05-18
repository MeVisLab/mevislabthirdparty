@@================================================================
@@
@@ Sets pv to contain the vertex defined by curVert
@@
@@================================================================
@={ GenVertex
    matlIndex = getBindIndex(materialBinding, row, quadIndex, curVert);
    normIndex = getBindIndex(normalBinding,   row, quadIndex, curVert);
    tcIndex   = tcb.isFunction() ? 0 : curVert;

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
@=}

////////////////////////////////////////////////////////////////////////
//
// Description:
//    Generates triangles representing a quad mesh.
//
// Use: protected

void
SoQuadMesh::generatePrimitives(SoAction *action)
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
    SbBool forPicking = action->isOfType(SoRayPickAction::getClassTypeId());

    //put the vertexProperty into the state:
    SoState *state = action->getState();
    state->push();
    SoVertexProperty* vp = getVertexProperty();
    if(vp){
        vp->doAction(action);
    }


    SoPrimitiveVertex           pv;
    SoFaceDetail                fd;
    SoPointDetail               pd;
    const SoCoordinateElement   *ce;
    int                         topVert, botVert, curVert;
    int                         quadIndex, matlIndex, normIndex, tcIndex;
    int                         row, col, numRows, numCols;
    Binding                     materialBinding, normalBinding;
    SoNormalBundle              nb(action, FALSE);
    SoTextureCoordinateBundle   tcb(action, FALSE, ! forPicking);

    ce = SoCoordinateElement::getInstance(action->getState());

    materialBinding = getMaterialBinding(action);
    normalBinding   = getNormalBinding(action);

    // Get number of rows and columns (of quads, not vertices)
    numRows = (int) verticesPerColumn.getValue() - 1;
    numCols = (int) verticesPerRow.getValue()    - 1;

    topVert = (int) startIndex.getValue();
    botVert = topVert + numCols + 1;

    if (forPicking) {
        pv.setTextureCoords(SbVec4f(0.0, 0.0, 0.0, 0.0));
        pv.setDetail(&fd);
    }
    else
        pv.setDetail(&pd);

    // Generate default normals, if necessary:
    if (SoNormalElement::getInstance(state)->getNum() == 0) {
        figureNormals(action->getState(), &nb);
        normalBinding = PER_VERTEX;
    }

    for (row = 0; row < numRows; row++) {
            
        fd.setPartIndex(row);

        // If either material or normal binding is per quad, we have
        // to generate each quad separately, to get the materials and
        // normals in the details to be correct
        if (materialBinding == PER_QUAD || normalBinding == PER_QUAD) {

            for (col = -1; col < numCols; col++) {
                if (col >= 0) {
                    // Generate a triangle strip from the 4 vertices of the
                    // independent quad, in this order:
                    //          topVert-1, botVert-1, botVert, topVert

                    quadIndex = row * numCols + col;

                    fd.setFaceIndex(quadIndex);

                    beginShape(action, TRIANGLE_STRIP,
                               forPicking ? NULL : &fd);

                    curVert = topVert - 1;
                    @!GenVertex

                    curVert = botVert - 1;
                    @!GenVertex

                    curVert = topVert;
                    @!GenVertex

                    curVert = botVert;
                    @!GenVertex

                    endShape();
                }

                topVert++;
                botVert++;
            }
        }

        // We can generate triangle strips, which is a little easier
        else {
            beginShape(action, TRIANGLE_STRIP, forPicking ? NULL : &fd);

            for (col = -1; col < numCols; col++) {

                quadIndex = row * numCols + col;

                fd.setFaceIndex(quadIndex);

                // Generate two vertices for each column:
                //      topVert, then botVert

                curVert = topVert;
                @!GenVertex

                curVert = botVert;
                @!GenVertex

                topVert++;
                botVert++;
            }

            endShape();
        }
    }

    state->pop();
}

//////////////////////////////////////////////////////////////////////////
// Following preprocessor-generated routines handle all combinations of
// Normal binding (per vertex, per face, per part, overall/none)
// Color Binding (per vertex, per face, per part, overall)
// Textures (on or off)
//////////////////////////////////////////////////////////////////////////
@@ ----------------------------------------------------------------------
@@ General prototype of renderfunction is as follows:
@@
@={ RenderFunction
void
SoQuadMesh::
@ FuncName 
    (SoGLRenderAction* ) {

@?{ On
    // Send one normal, if there are any normals in vpCache:
    if (vpCache.getNumNormals() > 0)
        vpCache.sendNormal(vpCache.getNormals(0));
@?}
    const char *vertexPtr = vpCache.getVertices(startIndex.getValue());
    const unsigned int vertexStride = vpCache.getVertexStride();
    SoVPCacheFunc *const vertexFunc = vpCache.vertexFunc;
    const unsigned int vertexRowStride = vertexStride*
        verticesPerRow.getValue();
@?{ Pm | Fm
    const char *colorPtr = vpCache.getColors(0);
    const unsigned int colorStride = vpCache.getColorStride();
    SoVPCacheFunc *const colorFunc = vpCache.colorFunc;
@?}
@?{ Vm
    const char *colorPtr = vpCache.getColors(startIndex.getValue());
    const unsigned int colorStride = vpCache.getColorStride();
    const unsigned int colorRowStride = colorStride*
        verticesPerRow.getValue();
    SoVPCacheFunc *const colorFunc = vpCache.colorFunc;
@?}
@?{ Pn | Fn
    const char *normalPtr = vpCache.getNormals(0);
    const unsigned int normalStride = vpCache.getNormalStride();
    SoVPCacheFunc *const normalFunc = vpCache.normalFunc;
@?}
@?{ Vn
    const char *normalPtr = vpCache.getNormals(startIndex.getValue());
    const unsigned int normalStride = vpCache.getNormalStride();
    const unsigned int normalRowStride = normalStride*verticesPerRow.getValue();
    SoVPCacheFunc *const normalFunc = vpCache.normalFunc;
@?}
@?{ T
    const char *texCoordPtr = vpCache.getTexCoords(0);
    const unsigned int texCoordStride = vpCache.getTexCoordStride();
    SoVPCacheFunc *const texCoordFunc = vpCache.texCoordFunc;
    const unsigned int texCoordRowStride = texCoordStride*
        verticesPerRow.getValue();
@?}

    const int numRows = verticesPerColumn.getValue() - 1;
@?{ Fm | Fn
    const int nv = verticesPerRow.getValue() - 1;
@?}
@?{ Vm | Om | Pm
@?{ Vn | On | Pn
     const int nv = verticesPerRow.getValue();
@?}
@?}

    int v;
    for (int row = 0; row < numRows; row++) {
@?{ Pm
        (*colorFunc)(colorPtr); colorPtr += colorStride;
@?}
@?{ Pn
        (*normalFunc)(normalPtr); normalPtr += normalStride;
@?}
@?{ Fn | Fm
        glBegin(GL_QUADS);
        for(v = 0; v < nv; v++) {
@?{ Fm
            (*colorFunc)(colorPtr); colorPtr += colorStride;
@?}
@?{ Fn
            (*normalFunc)(normalPtr); normalPtr += normalStride;
@?}
@?{ Vm
            (*colorFunc)(colorPtr); 
@?}
@?{ Vn
            (*normalFunc)(normalPtr); 
@?}
@?{ T
            (*texCoordFunc)(texCoordPtr);
@?}
            (*vertexFunc)(vertexPtr);
@?{ Vm
            (*colorFunc)(colorPtr+colorRowStride); 
@?}
@?{ Vn
            (*normalFunc)(normalPtr+normalRowStride); 
@?}         
@?{ T
            (*texCoordFunc)(texCoordPtr+texCoordRowStride);
@?}                 
            (*vertexFunc)(vertexPtr+vertexRowStride);
@?{ Vm
            (*colorFunc)(colorPtr+colorStride+colorRowStride); 
@?}
@?{ Vn
            (*normalFunc)(normalPtr+normalStride+normalRowStride); 
@?}                 
@?{ T
            (*texCoordFunc)(texCoordPtr+texCoordStride+texCoordRowStride);
@?}                 
            (*vertexFunc)(vertexPtr+vertexStride+vertexRowStride);
@?{ Vm
            (*colorFunc)(colorPtr+colorStride); 
            colorPtr += colorStride;
@?}
@?{ Vn
            (*normalFunc)(normalPtr+normalStride);
            normalPtr += normalStride; 
@?}                         
@?{ T
            (*texCoordFunc)(texCoordPtr+texCoordStride);
            texCoordPtr += texCoordStride;
@?}                 
            (*vertexFunc)(vertexPtr+vertexStride); 
            vertexPtr += vertexStride;
        }
        glEnd(); //GL_QUADS
        //At the end of a row skip over last vertex:
        vertexPtr += vertexStride;
@?{ T
        texCoordPtr += texCoordStride;
@?}
@?{ Vm
        colorPtr += colorStride;
@?}
@?{ Vn
        normalPtr += normalStride; 
@?}        

@?} // end Fn | Fm (Quads)

//Do Strip rendering if both ~Fn and ~Fm
@?{ Vm | Om | Pm
@?{ Vn | On | Pn
        glBegin(GL_TRIANGLE_STRIP);
        for (v = 0; v < nv; v++) {

@?{ Vm
            (*colorFunc)(colorPtr);
@?}
@?{ Vn
            (*normalFunc)(normalPtr);
@?}
@?{ T
            (*texCoordFunc)(texCoordPtr);
@?}
            (*vertexFunc)(vertexPtr);

@?{ Vm
            (*colorFunc)(colorPtr+colorRowStride);
            colorPtr += colorStride;
@?}
@?{ Vn
            (*normalFunc)(normalPtr+normalRowStride);
            normalPtr += normalStride;
@?}
@?{ T
            (*texCoordFunc)(texCoordPtr+texCoordRowStride);
            texCoordPtr += texCoordStride;
@?}
            (*vertexFunc)(vertexPtr+vertexRowStride);
            vertexPtr += vertexStride;
        }

        glEnd();
@?}
@?}// end Strip rendering 

    }
}

@=}

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
//
SoQuadMesh::PMQM SoQuadMesh::renderFunc[32] = {
    &SoQuadMesh::OmOn, &SoQuadMesh::OmOnT,
    &SoQuadMesh::OmPn, &SoQuadMesh::OmPnT,
    &SoQuadMesh::OmFn, &SoQuadMesh::OmFnT,
    &SoQuadMesh::OmVn, &SoQuadMesh::OmVnT,
    &SoQuadMesh::PmOn, &SoQuadMesh::PmOnT,
    &SoQuadMesh::PmPn, &SoQuadMesh::PmPnT,
    &SoQuadMesh::PmFn, &SoQuadMesh::PmFnT,
    &SoQuadMesh::PmVn, &SoQuadMesh::PmVnT,
    &SoQuadMesh::FmOn, &SoQuadMesh::FmOnT,
    &SoQuadMesh::FmPn, &SoQuadMesh::FmPnT,
    &SoQuadMesh::FmFn, &SoQuadMesh::FmFnT,
    &SoQuadMesh::FmVn, &SoQuadMesh::FmVnT,
    &SoQuadMesh::VmOn, &SoQuadMesh::VmOnT,
    &SoQuadMesh::VmPn, &SoQuadMesh::VmPnT,
    &SoQuadMesh::VmFn, &SoQuadMesh::VmFnT,
    &SoQuadMesh::VmVn, &SoQuadMesh::VmVnT,
    };



@= FuncName OmOn
@= Om ON
@= On ON
@= Pm
@= Fm
@= Vm
@= Pn
@= Fn
@= Vn
@= T
@ RenderFunction

@= FuncName OmOnT
@= Om ON
@= On ON
@= Pm
@= Fm
@= Vm
@= Pn
@= Fn
@= Vn
@= T  ON
@ RenderFunction

@= FuncName OmPn
@= Om ON
@= On
@= Pm
@= Fm
@= Vm
@= Pn ON
@= Fn
@= Vn
@= T
@ RenderFunction

@= FuncName OmPnT
@= Om ON
@= On
@= Pm
@= Fm
@= Vm
@= Pn ON
@= Fn
@= Vn
@= T  ON
@ RenderFunction

@= FuncName OmFn
@= Om ON
@= On
@= Pm
@= Fm
@= Vm
@= Pn
@= Fn ON
@= Vn    
@= T
@ RenderFunction

@= FuncName OmFnT
@= Om ON
@= On
@= Pm
@= Fm
@= Vm
@= Pn
@= Fn ON
@= Vn
@= T  ON
@ RenderFunction

@= FuncName OmVn
@= Om ON
@= On
@= Pm
@= Fm
@= Vm
@= Pn
@= Fn
@= Vn ON
@= T
@ RenderFunction

@= FuncName OmVnT
@= Om ON
@= On
@= Pm
@= Fm
@= Vm
@= Pn
@= Fn
@= Vn ON
@= T  ON
@ RenderFunction

@= FuncName PmOn
@= Om
@= On ON
@= Pm ON
@= Fm
@= Vm
@= Pn
@= Fn
@= Vn
@= T
@ RenderFunction

@= FuncName PmOnT
@= Om
@= On ON
@= Pm ON
@= Fm
@= Vm
@= Pn
@= Fn
@= Vn
@= T  ON
@ RenderFunction

@= FuncName PmPn
@= Om
@= On
@= Pm ON
@= Fm
@= Vm
@= Pn ON
@= Fn
@= Vn
@= T
@ RenderFunction

@= FuncName PmPnT
@= Om
@= On
@= Pm ON
@= Fm
@= Vm
@= Pn ON
@= Fn
@= Vn
@= T  ON
@ RenderFunction

@= FuncName PmFn
@= Om
@= On
@= Pm ON
@= Fm
@= Vm
@= Pn
@= Fn ON
@= Vn
@= T
@ RenderFunction

@= FuncName PmFnT
@= Om
@= On
@= Pm ON
@= Fm
@= Vm
@= Pn
@= Fn ON
@= Vn
@= T  ON
@ RenderFunction

@= FuncName PmVn
@= Om
@= On
@= Pm ON
@= Fm
@= Vm
@= Pn
@= Fn
@= Vn ON
@= T
@ RenderFunction

@= FuncName PmVnT
@= Om
@= On
@= Pm ON
@= Fm
@= Vm
@= Pn
@= Fn
@= Vn ON
@= T  ON
@ RenderFunction

@= FuncName FmOn
@= Om
@= On ON
@= Pm
@= Fm ON
@= Vm
@= Pn
@= Fn
@= Vn
@= T
@ RenderFunction

@= FuncName FmOnT
@= Om
@= On ON
@= Pm
@= Fm ON
@= Vm
@= Pn
@= Fn
@= Vn
@= T  ON
@ RenderFunction

@= FuncName FmPn
@= Om
@= On
@= Pm
@= Fm ON
@= Vm
@= Pn ON
@= Fn
@= Vn
@= T
@ RenderFunction

@= FuncName FmPnT
@= Om
@= On
@= Pm
@= Fm ON
@= Vm
@= Pn ON
@= Fn
@= Vn
@= T  ON
@ RenderFunction

@= FuncName FmFn
@= Om
@= On
@= Pm
@= Fm ON
@= Vm
@= Pn
@= Fn ON
@= Vn
@= T
@ RenderFunction

@= FuncName FmFnT
@= Om
@= On
@= Pm
@= Fm ON
@= Vm
@= Pn
@= Fn ON
@= Vn
@= T  ON
@ RenderFunction

@= FuncName FmVn
@= Om
@= On
@= Pm
@= Fm ON
@= Vm
@= Pn
@= Fn  
@= Vn ON
@= T   
@ RenderFunction
 
@= FuncName FmVnT
@= Om
@= On
@= Pm
@= Fm ON
@= Vm
@= Pn
@= Fn  
@= Vn ON
@= T  ON   
@ RenderFunction


@= FuncName VmOn
@= Om
@= On ON
@= Pm
@= Fm
@= Vm ON
@= Pn
@= Fn
@= Vn
@= T
@ RenderFunction

@= FuncName VmOnT
@= Om
@= On ON
@= Pm
@= Fm
@= Vm ON
@= Pn
@= Fn
@= Vn
@= T  ON
@ RenderFunction

@= FuncName VmPn
@= Om
@= On
@= Pm
@= Fm
@= Vm ON
@= Pn ON
@= Fn
@= Vn
@= T
@ RenderFunction

@= FuncName VmPnT
@= Om
@= On
@= Pm
@= Fm
@= Vm ON
@= Pn ON
@= Fn
@= Vn
@= T  ON
@ RenderFunction

@= FuncName VmFn
@= Om
@= On
@= Pm
@= Fm  
@= Vm ON
@= Pn  
@= Fn ON
@= Vn
@= T   
@ RenderFunction
  
@= FuncName VmFnT
@= Om
@= On
@= Pm
@= Fm  
@= Vm ON
@= Pn  
@= Fn ON
@= Vn
@= T  ON   
@ RenderFunction 

@= FuncName VmVn
@= Om
@= On
@= Pm
@= Fm
@= Vm ON
@= Pn
@= Fn
@= Vn ON
@= T
@ RenderFunction

@= FuncName VmVnT
@= Om
@= On
@= Pm
@= Fm
@= Vm ON
@= Pn
@= Fn
@= Vn ON
@= T  ON
@ RenderFunction

