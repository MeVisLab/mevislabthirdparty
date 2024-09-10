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
SoIndexedFaceSet::
@ FuncName 
    (SoGLRenderAction* ) {
    const int32_t *const vertexIndex = coordIndex.getValues(0);
@?{ On
    // Send one normal, if there are any normals in vpCache:
    if (vpCache.getNumNormals() > 0)
        vpCache.sendNormal(vpCache.getNormals(0));
@?}
@?{ Fm | Vm
    const int32_t *const colorIndx = getColorIndices();
@?}
@?{ Fn | Vn
    const int32_t *const normalIndx = getNormalIndices();
@?}
@?{ T
    const int32_t *const tCoordIndx = getTexCoordIndices();
@?}

    glBegin(GL_TRIANGLES);
    int vtxCtr = 0;
    for (int tri = 0; tri < numTris; tri++) {
@?{ Fm
        vpCache.sendColorAtIndex(colorIndx[tri]);
@?}
@?{ Fn
        vpCache.sendNormalAtIndex(normalIndx[tri]);
@?}

@?{ Vm
        vpCache.sendColorAtIndex(colorIndx[vtxCtr]);
@?}
@?{ Vn
        vpCache.sendNormalAtIndex(normalIndx[vtxCtr]);
@?}
@?{ T
        vpCache.sendTexCoordAtIndex(tCoordIndx[vtxCtr]);
@?}
        vpCache.sendVertexAtIndex(vertexIndex[vtxCtr]);

@?{ Vm
        vpCache.sendColorAtIndex(colorIndx[vtxCtr+1]);
@?}
@?{ Vn
        vpCache.sendNormalAtIndex(normalIndx[vtxCtr+1]);
@?}
@?{ T
        vpCache.sendTexCoordAtIndex(tCoordIndx[vtxCtr+1]);
@?}
        vpCache.sendVertexAtIndex(vertexIndex[vtxCtr+1]);

@?{ Vm
        vpCache.sendColorAtIndex(colorIndx[vtxCtr+2]);
@?}
@?{ Vn
        vpCache.sendNormalAtIndex(normalIndx[vtxCtr+2]);
@?}
@?{ T
        vpCache.sendTexCoordAtIndex(tCoordIndx[vtxCtr+2]);
@?}
        vpCache.sendVertexAtIndex(vertexIndex[vtxCtr+2]);
        vtxCtr += 4; // Skip past END_OF_FACE_INDEX
    }
    glEnd();
}

@=}

@@ ----------------------------------------------------------------------
@@ Quad rendering:
@@
@={ QuadRenderFunction
void
SoIndexedFaceSet::
@ FuncName 
    (SoGLRenderAction* ) {
    const int32_t *const vertexIndex = coordIndex.getValues(0);
@?{ On
    // Send one normal, if there are any normals in vpCache:
    if (vpCache.getNumNormals() > 0)
        vpCache.sendNormal(vpCache.getNormals(0));
@?}
@?{ Fm | Vm
    const int32_t *const colorIndx = getColorIndices();
@?}
@?{ Fn | Vn
    const int32_t *const normalIndx = getNormalIndices();
@?}
@?{ T
    const int32_t *const tCoordIndx = getTexCoordIndices();
@?}

    glBegin(GL_QUADS);
    int vtxCtr = numTris*4;
@?{ Fn | Fm
    int faceCtr = numTris;
@?}     
    for (int quad = 0; quad < numQuads; quad++) {
@?{ Fm
        vpCache.sendColorAtIndex(colorIndx[faceCtr]);
@?}
@?{ Fn
        vpCache.sendNormalAtIndex(normalIndx[faceCtr]);
@?}
@?{ Fn | Fm
        ++faceCtr;
@?}     

@?{ Vm
        vpCache.sendColorAtIndex(colorIndx[vtxCtr]);
@?}
@?{ Vn
        vpCache.sendNormalAtIndex(normalIndx[vtxCtr]);
@?}
@?{ T
        vpCache.sendTexCoordAtIndex(tCoordIndx[vtxCtr]);
@?}
        vpCache.sendVertexAtIndex(vertexIndex[vtxCtr]);

@?{ Vm
        vpCache.sendColorAtIndex(colorIndx[vtxCtr+1]);
@?}
@?{ Vn
        vpCache.sendNormalAtIndex(normalIndx[vtxCtr+1]);
@?}
@?{ T
        vpCache.sendTexCoordAtIndex(tCoordIndx[vtxCtr+1]);
@?}
        vpCache.sendVertexAtIndex(vertexIndex[vtxCtr+1]);

@?{ Vm
        vpCache.sendColorAtIndex(colorIndx[vtxCtr+2]);
@?}
@?{ Vn
        vpCache.sendNormalAtIndex(normalIndx[vtxCtr+2]);
@?}
@?{ T
        vpCache.sendTexCoordAtIndex(tCoordIndx[vtxCtr]+2);
@?}
        vpCache.sendVertexAtIndex(vertexIndex[vtxCtr+2]);

@?{ Vm
        vpCache.sendColorAtIndex(colorIndx[vtxCtr+3]);
@?}
@?{ Vn
        vpCache.sendNormalAtIndex(normalIndx[vtxCtr+3]);
@?}
@?{ T
        vpCache.sendTexCoordAtIndex(tCoordIndx[vtxCtr+3]);
@?}
        vpCache.sendVertexAtIndex(vertexIndex[vtxCtr+3]);
        vtxCtr += 5; // Skip past END_OF_FACE_INDEX
    }
    glEnd();
}

@=}

@@ ----------------------------------------------------------------------
@@ General polygon rendering:
@@
@={ GenRenderFunction
void
SoIndexedFaceSet::
@ FuncName 
    (SoGLRenderAction* )
{
    const int32_t *const vertexIndex = coordIndex.getValues(0);
    const int numVI = coordIndex.getNum();
@?{ On
    // Send one normal, if there are any normals in vpCache:
    if (vpCache.getNumNormals() > 0)
        vpCache.sendNormal(vpCache.getNormals(0));
@?}
@?{ Fm | Vm
    const int32_t *const colorIndx = getColorIndices();
@?}
@?{ Fn | Vn
    const int32_t *const normalIndx = getNormalIndices();
@?}
@?{ T
    const int32_t *const tCoordIndx = getTexCoordIndices();
@?}
    int vtxCtr = numQuads*5 + numTris*4;
@?{ Fn | Fm
    int faceCtr = numQuads + numTris;
@?}
    while (vtxCtr < numVI) {
@?{ Fm
        vpCache.sendColorAtIndex(colorIndx[faceCtr]);
@?}
@?{ Fn
        vpCache.sendNormalAtIndex(normalIndx[faceCtr]);
@?}
@?{ Fn | Fm
        ++faceCtr;
@?}     
        glBegin(GL_POLYGON);
        while (vtxCtr < numVI &&
               (vertexIndex[vtxCtr] != SO_END_FACE_INDEX)) {
@?{ Vm
            vpCache.sendColorAtIndex(colorIndx[vtxCtr]);
@?}
@?{ Vn
        vpCache.sendNormalAtIndex(normalIndx[vtxCtr]);
@?}
@?{ T
            vpCache.sendTexCoordAtIndex(tCoordIndx[vtxCtr]);
@?}
            vpCache.sendVertexAtIndex(vertexIndex[vtxCtr]);
            vtxCtr++;
        }
        vtxCtr++; // Skip over END_FACE_INDEX
        glEnd();
    }
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
SoIndexedFaceSet::PMFS SoIndexedFaceSet::TriRenderFunc[32] = {
    &SoIndexedFaceSet::TriOmOn, &SoIndexedFaceSet::TriOmOnT,
    &SoIndexedFaceSet::TriOmFn, &SoIndexedFaceSet::TriOmFnT,
    &SoIndexedFaceSet::TriOmFn, &SoIndexedFaceSet::TriOmFnT,
    &SoIndexedFaceSet::TriOmVn, &SoIndexedFaceSet::TriOmVnT,
    &SoIndexedFaceSet::TriFmOn, &SoIndexedFaceSet::TriFmOnT,
    &SoIndexedFaceSet::TriFmFn, &SoIndexedFaceSet::TriFmFnT,
    &SoIndexedFaceSet::TriFmFn, &SoIndexedFaceSet::TriFmFnT,
    &SoIndexedFaceSet::TriFmVn, &SoIndexedFaceSet::TriFmVnT,
    &SoIndexedFaceSet::TriFmOn, &SoIndexedFaceSet::TriFmOnT,
    &SoIndexedFaceSet::TriFmFn, &SoIndexedFaceSet::TriFmFnT,
    &SoIndexedFaceSet::TriFmFn, &SoIndexedFaceSet::TriFmFnT,
    &SoIndexedFaceSet::TriFmVn, &SoIndexedFaceSet::TriFmVnT,
    &SoIndexedFaceSet::TriVmOn, &SoIndexedFaceSet::TriVmOnT,
    &SoIndexedFaceSet::TriVmFn, &SoIndexedFaceSet::TriVmFnT,
    &SoIndexedFaceSet::TriVmFn, &SoIndexedFaceSet::TriVmFnT,
    &SoIndexedFaceSet::TriVmVn, &SoIndexedFaceSet::TriVmVnT,
    };
SoIndexedFaceSet::PMFS SoIndexedFaceSet::QuadRenderFunc[32] = {
    &SoIndexedFaceSet::QuadOmOn, &SoIndexedFaceSet::QuadOmOnT,
    &SoIndexedFaceSet::QuadOmFn, &SoIndexedFaceSet::QuadOmFnT,
    &SoIndexedFaceSet::QuadOmFn, &SoIndexedFaceSet::QuadOmFnT,
    &SoIndexedFaceSet::QuadOmVn, &SoIndexedFaceSet::QuadOmVnT,
    &SoIndexedFaceSet::QuadFmOn, &SoIndexedFaceSet::QuadFmOnT,
    &SoIndexedFaceSet::QuadFmFn, &SoIndexedFaceSet::QuadFmFnT,
    &SoIndexedFaceSet::QuadFmFn, &SoIndexedFaceSet::QuadFmFnT,
    &SoIndexedFaceSet::QuadFmVn, &SoIndexedFaceSet::QuadFmVnT,
    &SoIndexedFaceSet::QuadFmOn, &SoIndexedFaceSet::QuadFmOnT,
    &SoIndexedFaceSet::QuadFmFn, &SoIndexedFaceSet::QuadFmFnT,
    &SoIndexedFaceSet::QuadFmFn, &SoIndexedFaceSet::QuadFmFnT,
    &SoIndexedFaceSet::QuadFmVn, &SoIndexedFaceSet::QuadFmVnT,
    &SoIndexedFaceSet::QuadVmOn, &SoIndexedFaceSet::QuadVmOnT,
    &SoIndexedFaceSet::QuadVmFn, &SoIndexedFaceSet::QuadVmFnT,
    &SoIndexedFaceSet::QuadVmFn, &SoIndexedFaceSet::QuadVmFnT,
    &SoIndexedFaceSet::QuadVmVn, &SoIndexedFaceSet::QuadVmVnT,
    };
SoIndexedFaceSet::PMFS SoIndexedFaceSet::GenRenderFunc[32] = {
    &SoIndexedFaceSet::GenOmOn, &SoIndexedFaceSet::GenOmOnT,
    &SoIndexedFaceSet::GenOmFn, &SoIndexedFaceSet::GenOmFnT,
    &SoIndexedFaceSet::GenOmFn, &SoIndexedFaceSet::GenOmFnT,
    &SoIndexedFaceSet::GenOmVn, &SoIndexedFaceSet::GenOmVnT,
    &SoIndexedFaceSet::GenFmOn, &SoIndexedFaceSet::GenFmOnT,
    &SoIndexedFaceSet::GenFmFn, &SoIndexedFaceSet::GenFmFnT,
    &SoIndexedFaceSet::GenFmFn, &SoIndexedFaceSet::GenFmFnT,
    &SoIndexedFaceSet::GenFmVn, &SoIndexedFaceSet::GenFmVnT,
    &SoIndexedFaceSet::GenFmOn, &SoIndexedFaceSet::GenFmOnT,
    &SoIndexedFaceSet::GenFmFn, &SoIndexedFaceSet::GenFmFnT,
    &SoIndexedFaceSet::GenFmFn, &SoIndexedFaceSet::GenFmFnT,
    &SoIndexedFaceSet::GenFmVn, &SoIndexedFaceSet::GenFmVnT,
    &SoIndexedFaceSet::GenVmOn, &SoIndexedFaceSet::GenVmOnT,
    &SoIndexedFaceSet::GenVmFn, &SoIndexedFaceSet::GenVmFnT,
    &SoIndexedFaceSet::GenVmFn, &SoIndexedFaceSet::GenVmFnT,
    &SoIndexedFaceSet::GenVmVn, &SoIndexedFaceSet::GenVmVnT,
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
@= FuncName QuadOmOn
@ QuadRenderFunction
@= FuncName GenOmOn
@ GenRenderFunction

@= Om ON
@= On ON
@= Fm
@= Vm
@= Fn
@= Vn
@= T ON
@= FuncName TriOmOnT
@ TriRenderFunction
@= FuncName QuadOmOnT
@ QuadRenderFunction
@= FuncName GenOmOnT
@ GenRenderFunction

@= Om ON
@= On
@= Fm
@= Vm
@= Fn ON
@= Vn
@= T
@= FuncName TriOmFn
@ TriRenderFunction
@= FuncName QuadOmFn
@ QuadRenderFunction
@= FuncName GenOmFn
@ GenRenderFunction

@= Om ON
@= On
@= Fm
@= Vm
@= Fn ON
@= Vn
@= T ON
@= FuncName TriOmFnT
@ TriRenderFunction
@= FuncName QuadOmFnT
@ QuadRenderFunction
@= FuncName GenOmFnT
@ GenRenderFunction

@= Om ON
@= On
@= Fm
@= Vm
@= Fn
@= Vn ON
@= T
@= FuncName TriOmVn
@ TriRenderFunction
@= FuncName QuadOmVn
@ QuadRenderFunction
@= FuncName GenOmVn
@ GenRenderFunction

@= Om ON
@= On
@= Fm
@= Vm
@= Fn
@= Vn ON
@= T ON
@= FuncName TriOmVnT
@ TriRenderFunction
@= FuncName QuadOmVnT
@ QuadRenderFunction
@= FuncName GenOmVnT
@ GenRenderFunction


@= Om
@= On ON
@= Fm ON
@= Vm
@= Fn
@= Vn
@= T
@= FuncName TriFmOn
@ TriRenderFunction
@= FuncName QuadFmOn
@ QuadRenderFunction
@= FuncName GenFmOn
@ GenRenderFunction

@= Om
@= On ON
@= Fm ON
@= Vm
@= Fn
@= Vn
@= T ON
@= FuncName TriFmOnT
@ TriRenderFunction
@= FuncName QuadFmOnT
@ QuadRenderFunction
@= FuncName GenFmOnT
@ GenRenderFunction

@= Om
@= On
@= Fm ON
@= Vm
@= Fn ON
@= Vn
@= T
@= FuncName TriFmFn
@ TriRenderFunction
@= FuncName QuadFmFn
@ QuadRenderFunction
@= FuncName GenFmFn
@ GenRenderFunction

@= Om
@= On
@= Fm ON
@= Vm
@= Fn ON
@= Vn
@= T ON
@= FuncName TriFmFnT
@ TriRenderFunction
@= FuncName QuadFmFnT
@ QuadRenderFunction
@= FuncName GenFmFnT
@ GenRenderFunction

@= Om
@= On
@= Fm ON
@= Vm
@= Fn
@= Vn ON
@= T
@= FuncName TriFmVn
@ TriRenderFunction
@= FuncName QuadFmVn
@ QuadRenderFunction
@= FuncName GenFmVn
@ GenRenderFunction

@= Om
@= On
@= Fm ON
@= Vm
@= Fn
@= Vn ON
@= T ON
@= FuncName TriFmVnT
@ TriRenderFunction
@= FuncName QuadFmVnT
@ QuadRenderFunction
@= FuncName GenFmVnT
@ GenRenderFunction


@= Om
@= On ON
@= Fm
@= Vm ON
@= Fn
@= Vn
@= T
@= FuncName TriVmOn
@ TriRenderFunction
@= FuncName QuadVmOn
@ QuadRenderFunction
@= FuncName GenVmOn
@ GenRenderFunction

@= Om
@= On ON
@= Fm
@= Vm ON
@= Fn
@= Vn
@= T ON
@= FuncName TriVmOnT
@ TriRenderFunction
@= FuncName QuadVmOnT
@ QuadRenderFunction
@= FuncName GenVmOnT
@ GenRenderFunction

@= Om
@= On
@= Fm
@= Vm ON
@= Fn ON
@= Vn
@= T
@= FuncName TriVmFn
@ TriRenderFunction
@= FuncName QuadVmFn
@ QuadRenderFunction
@= FuncName GenVmFn
@ GenRenderFunction

@= Om
@= On
@= Fm
@= Vm ON
@= Fn ON
@= Vn
@= T ON
@= FuncName TriVmFnT
@ TriRenderFunction
@= FuncName QuadVmFnT
@ QuadRenderFunction
@= FuncName GenVmFnT
@ GenRenderFunction

@= Om
@= On
@= Fm
@= Vm ON
@= Fn
@= Vn ON
@= T
@= FuncName TriVmVn
@ TriRenderFunction
@= FuncName QuadVmVn
@ QuadRenderFunction
@= FuncName GenVmVn
@ GenRenderFunction

@= Om
@= On
@= Fm
@= Vm ON
@= Fn
@= Vn ON
@= T ON
@= FuncName TriVmVnT
@ TriRenderFunction
@= FuncName QuadVmVnT
@ QuadRenderFunction
@= FuncName GenVmVnT
@ GenRenderFunction

