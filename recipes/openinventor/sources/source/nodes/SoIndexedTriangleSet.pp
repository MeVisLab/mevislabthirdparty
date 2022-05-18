//////////////////////////////////////////////////////////////////////////
// Following preprocessor-generated routines handle all combinations of
// Normal binding (per vertex, per face, per part, overall/none)
// Color Binding (per vertex, per face, per part, overall)
// Textures (on or off)
//////////////////////////////////////////////////////////////////////////

@@ ----------------------------------------------------------------------
@@ Triangle rendering:
@@
@={ TriRenderFunction
void
SoIndexedTriangleSet::
@ FuncName 
    (SoGLRenderAction* ) {
    const int32_t *const vertexIndex = coordIndex.getValues(0);
    SbBool sendAdj = sendAdjacency.getValue();
@?{ On
    // Send one normal, if there are any normals in vpCache:
    if (vpCache.getNumNormals() > 0)
        vpCache.sendNormal(vpCache.getNormals(0));
@?}
    const char *vertexPtr = vpCache.getVertices(0);
    const int vertexStride = vpCache.getVertexStride();
    SoVPCacheFunc *const vertexFunc = vpCache.vertexFunc;
@?{ Fm | Vm
    const char *colorPtr = vpCache.getColors(0);
    const int colorStride = vpCache.getColorStride();
    SoVPCacheFunc *const colorFunc = vpCache.colorFunc;
    const int32_t *const colorIndx = getColorIndices();
@?}
@?{ Fn | Vn
    const char *normalPtr = vpCache.getNormals(0);
    const int normalStride = vpCache.getNormalStride();
    SoVPCacheFunc *const normalFunc = vpCache.normalFunc;
    const int32_t *const normalIndx = getNormalIndices();
@?}
@?{ T
    const char *texCoordPtr = vpCache.getTexCoords(0);
    const int texCoordStride = vpCache.getTexCoordStride();
    SoVPCacheFunc *const texCoordFunc = vpCache.texCoordFunc;
    const int32_t *const tCoordIndx = getTexCoordIndices();
@?}

    glBegin(sendAdj?GL_TRIANGLES_ADJACENCY:GL_TRIANGLES);
    int vtxCtr = 0;
    for (int tri = 0; tri < numTris; tri++) {
@?{ Fm
        (*colorFunc)(colorPtr+colorStride*colorIndx[tri]);
@?}
@?{ Fn
        (*normalFunc)(normalPtr+normalStride*normalIndx[tri]);
@?}

@?{ Vm
        (*colorFunc)(colorPtr+colorStride*colorIndx[vtxCtr]);
@?}
@?{ Vn
        (*normalFunc)(normalPtr+normalStride*normalIndx[vtxCtr]);
@?}
@?{ T
        (*texCoordFunc)(texCoordPtr+texCoordStride*tCoordIndx[vtxCtr]);
@?}
        (*vertexFunc)(vertexPtr+vertexStride*vertexIndex[vtxCtr]);

@?{ Vm
        (*colorFunc)(colorPtr+colorStride*colorIndx[vtxCtr+1]);
@?}
@?{ Vn
        (*normalFunc)(normalPtr+normalStride*normalIndx[vtxCtr+1]);
@?}
@?{ T
        (*texCoordFunc)(texCoordPtr+texCoordStride*tCoordIndx[vtxCtr+1]);
@?}
        (*vertexFunc)(vertexPtr+vertexStride*vertexIndex[vtxCtr+1]);

@?{ Vm
        (*colorFunc)(colorPtr+colorStride*colorIndx[vtxCtr+2]);
@?}
@?{ Vn
        (*normalFunc)(normalPtr+normalStride*normalIndx[vtxCtr+2]);
@?}
@?{ T
        (*texCoordFunc)(texCoordPtr+texCoordStride*tCoordIndx[vtxCtr+2]);
@?}
        (*vertexFunc)(vertexPtr+vertexStride*vertexIndex[vtxCtr+2]);
        vtxCtr += 3;
    }
    glEnd();
}

@=}


// 32 different rendering loops; the 5 bits used to determine the
// rendering case are:
// 43210  BITS            Routine suffix
// -----  ----            --------------
// 00...  Overall mtl     (Om)
// 01...  Part mtl        (Pm)  NOT GENERATED, Fm is same!
// 10...  Face mtl        (Fm)
// 11...  Vtx mtl         (Vm)
// ..00.  Overall/No norm (On)
// ..01.  Part norm       (Pn)  NOT GENERATED, Fn is same!
// ..10.  Face norm       (Fn)
// ..11.  Vtx norm        (Vn)
// ....0  No texcoord     -none-
// ....1  Vtx texcoord    (T)
//
SoIndexedTriangleSet::PMFS SoIndexedTriangleSet::TriRenderFunc[32] = {
    &SoIndexedTriangleSet::TriOmOn, &SoIndexedTriangleSet::TriOmOnT,
    &SoIndexedTriangleSet::TriOmFn, &SoIndexedTriangleSet::TriOmFnT,
    &SoIndexedTriangleSet::TriOmFn, &SoIndexedTriangleSet::TriOmFnT,
    &SoIndexedTriangleSet::TriOmVn, &SoIndexedTriangleSet::TriOmVnT,
    &SoIndexedTriangleSet::TriFmOn, &SoIndexedTriangleSet::TriFmOnT,
    &SoIndexedTriangleSet::TriFmFn, &SoIndexedTriangleSet::TriFmFnT,
    &SoIndexedTriangleSet::TriFmFn, &SoIndexedTriangleSet::TriFmFnT,
    &SoIndexedTriangleSet::TriFmVn, &SoIndexedTriangleSet::TriFmVnT,
    &SoIndexedTriangleSet::TriFmOn, &SoIndexedTriangleSet::TriFmOnT,
    &SoIndexedTriangleSet::TriFmFn, &SoIndexedTriangleSet::TriFmFnT,
    &SoIndexedTriangleSet::TriFmFn, &SoIndexedTriangleSet::TriFmFnT,
    &SoIndexedTriangleSet::TriFmVn, &SoIndexedTriangleSet::TriFmVnT,
    &SoIndexedTriangleSet::TriVmOn, &SoIndexedTriangleSet::TriVmOnT,
    &SoIndexedTriangleSet::TriVmFn, &SoIndexedTriangleSet::TriVmFnT,
    &SoIndexedTriangleSet::TriVmFn, &SoIndexedTriangleSet::TriVmFnT,
    &SoIndexedTriangleSet::TriVmVn, &SoIndexedTriangleSet::TriVmVnT,
    };

@= Om ON
@= On ON
@= Fm
@= Vm
@= Fn
@= Vn
@= T
@= FuncName TriOmOn
@ TriRenderFunction

@= Om ON
@= On ON
@= Fm
@= Vm
@= Fn
@= Vn
@= T ON
@= FuncName TriOmOnT
@ TriRenderFunction

@= Om ON
@= On
@= Fm
@= Vm
@= Fn ON
@= Vn
@= T
@= FuncName TriOmFn
@ TriRenderFunction

@= Om ON
@= On
@= Fm
@= Vm
@= Fn ON
@= Vn
@= T ON
@= FuncName TriOmFnT
@ TriRenderFunction

@= Om ON
@= On
@= Fm
@= Vm
@= Fn
@= Vn ON
@= T
@= FuncName TriOmVn
@ TriRenderFunction

@= Om ON
@= On
@= Fm
@= Vm
@= Fn
@= Vn ON
@= T ON
@= FuncName TriOmVnT
@ TriRenderFunction

@= Om
@= On ON
@= Fm ON
@= Vm
@= Fn
@= Vn
@= T
@= FuncName TriFmOn
@ TriRenderFunction

@= Om
@= On ON
@= Fm ON
@= Vm
@= Fn
@= Vn
@= T ON
@= FuncName TriFmOnT
@ TriRenderFunction

@= Om
@= On
@= Fm ON
@= Vm
@= Fn ON
@= Vn
@= T
@= FuncName TriFmFn
@ TriRenderFunction

@= Om
@= On
@= Fm ON
@= Vm
@= Fn ON
@= Vn
@= T ON
@= FuncName TriFmFnT
@ TriRenderFunction

@= Om
@= On
@= Fm ON
@= Vm
@= Fn
@= Vn ON
@= T
@= FuncName TriFmVn
@ TriRenderFunction

@= Om
@= On
@= Fm ON
@= Vm
@= Fn
@= Vn ON
@= T ON
@= FuncName TriFmVnT
@ TriRenderFunction

@= Om
@= On ON
@= Fm
@= Vm ON
@= Fn
@= Vn
@= T
@= FuncName TriVmOn
@ TriRenderFunction

@= Om
@= On ON
@= Fm
@= Vm ON
@= Fn
@= Vn
@= T ON
@= FuncName TriVmOnT
@ TriRenderFunction

@= Om
@= On
@= Fm
@= Vm ON
@= Fn ON
@= Vn
@= T
@= FuncName TriVmFn
@ TriRenderFunction

@= Om
@= On
@= Fm
@= Vm ON
@= Fn ON
@= Vn
@= T ON
@= FuncName TriVmFnT
@ TriRenderFunction

@= Om
@= On
@= Fm
@= Vm ON
@= Fn
@= Vn ON
@= T
@= FuncName TriVmVn
@ TriRenderFunction

@= Om
@= On
@= Fm
@= Vm ON
@= Fn
@= Vn ON
@= T ON
@= FuncName TriVmVnT
@ TriRenderFunction
