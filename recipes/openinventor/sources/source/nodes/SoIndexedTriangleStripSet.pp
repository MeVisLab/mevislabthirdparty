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
SoIndexedTriangleStripSet::
@ FuncName 
    (SoGLRenderAction* ) {
    const int ns = numStrips;
    const int* numverts = numVertices;
    const int32_t *const vertexIndex = coordIndex.getValues(0);
@?{ On
    // Send one normal, if there are any normals in vpCache:
    if (vpCache.getNumNormals() > 0)
        vpCache.sendNormal(vpCache.getNormals(0));
@?}
    const char *vertexPtr = vpCache.getVertices(0);
    const int vertexStride = vpCache.getVertexStride();
    SoVPCacheFunc *const vertexFunc = vpCache.vertexFunc;
@?{ Pm | Fm
    const char *colorPtr = vpCache.getColors(0);
    const int colorStride = vpCache.getColorStride();
    SoVPCacheFunc *const colorFunc = vpCache.colorFunc;
    const int32_t *const colorIndx = getColorIndices();
@?}
@?{ Fm
    int clrCtr=0;
@?}
@?{ Vm
    const char *colorPtr = vpCache.getColors(0);
    const int colorStride = vpCache.getColorStride();
    SoVPCacheFunc *const colorFunc = vpCache.colorFunc;
    const int32_t *const colorIndx = getColorIndices();
@?}
@?{ Pn | Fn
    const char *normalPtr = vpCache.getNormals(0);
    const int normalStride = vpCache.getNormalStride();
    SoVPCacheFunc *const normalFunc = vpCache.normalFunc;
    const int32_t *const normalIndx = getNormalIndices();
@?}
@?{ Fn
    int nrmCtr=0;
@?}
@?{ Vn
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
@?{ Fm | Fn
    glShadeModel(GL_FLAT);
@?} 
    int v;
    int vtxCtr = 0;
    for (int strip = 0; strip < ns; strip++) {
@?{ Pm
        (*colorFunc)(colorPtr+colorStride*colorIndx[strip]);
@?}
@?{ Pn
        (*normalFunc)(normalPtr+normalStride*normalIndx[strip]);
@?}
        const int nv = (*numverts);
        glBegin(GL_TRIANGLE_STRIP);
        for (v = 0; v < nv-1; v+=2) {
@?{ Fm | Fn
            // Per-face cases:
            if (v) {
@?{ Fm
                (*colorFunc)(colorPtr+colorStride*colorIndx[clrCtr++]);                 
@?}
@?{ Fn
                (*normalFunc)(normalPtr+normalStride*normalIndx[nrmCtr++]);             
@?}
            }
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
            (*vertexFunc)(vertexPtr+vertexStride*vertexIndex[vtxCtr++]);
            
@?{ Fm | Fn
            // Per-face cases:
            if (v) {
@?{ Fm
                (*colorFunc)(colorPtr+colorStride*colorIndx[clrCtr++]);                  
@?}
@?{ Fn         
                (*normalFunc)(normalPtr+normalStride*normalIndx[nrmCtr++]);             
@?}
            }
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
            (*vertexFunc)(vertexPtr+vertexStride*vertexIndex[vtxCtr++]);           
        }
        if (v < nv) { // Leftovers
@?{ Fm
            (*colorFunc)(colorPtr+colorStride*colorIndx[clrCtr++]);     
@?}
@?{ Fn
            (*normalFunc)(normalPtr+normalStride*normalIndx[nrmCtr++]);    
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
            (*vertexFunc)(vertexPtr+vertexStride*vertexIndex[vtxCtr++]);         
        }
        glEnd();
        vtxCtr++;
        ++numverts;
    }
@?{ Fm | Fn
    glShadeModel(GL_SMOOTH);
@?}
}

@=}

// Material overall:

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

void
SoIndexedTriangleStripSet::FmVn(SoGLRenderAction *) {
    const char *vertexPtr = vpCache.getVertices(0);
    const int vertexStride = vpCache.getVertexStride();
    SoVPCacheFunc *const vertexFunc = vpCache.vertexFunc;
    const char *colorPtr = vpCache.getColors(0);
    const int colorStride = vpCache.getColorStride();
    SoVPCacheFunc *const colorFunc = vpCache.colorFunc;
    const char *normalPtr = vpCache.getNormals(0);
    const int normalStride = vpCache.getNormalStride();
    SoVPCacheFunc *const normalFunc = vpCache.normalFunc;
    const int ns = numStrips;
    const int *numverts = numVertices;
    const int32_t *const vertexIndex = coordIndex.getValues(0);
    const int32_t *const normalIndx = getNormalIndices();
    const int32_t *const colorIndx = getColorIndices();

    int f;
    int v = 0;
    int clrCtr = 0;
    glBegin(GL_TRIANGLES);
    for (int strip = 0; strip < ns; strip++) {
        const int nf = (*numverts)-2;

        v += 2;
        for (f = 0; f < nf; f++) {
            // Per-face:
            (*colorFunc)(colorPtr+colorStride*colorIndx[clrCtr++]); 

            // Now three vertices, alternating ordering:
            if (f & 1) {
                (*normalFunc)(normalPtr+normalIndx[(v-0)]*normalStride);
                (*vertexFunc)(vertexPtr+vertexIndex[(v-0)]*vertexStride);
                (*normalFunc)(normalPtr+normalIndx[(v-1)]*normalStride);
                (*vertexFunc)(vertexPtr+vertexIndex[(v-1)]*vertexStride);
                (*normalFunc)(normalPtr+normalIndx[(v-2)]*normalStride);
                (*vertexFunc)(vertexPtr+vertexIndex[(v-2)]*vertexStride);
            } else {
                (*normalFunc)(normalPtr+normalIndx[(v-2)]*normalStride);
                (*vertexFunc)(vertexPtr+vertexIndex[(v-2)]*vertexStride);
                (*normalFunc)(normalPtr+normalIndx[(v-1)]*normalStride);
                (*vertexFunc)(vertexPtr+vertexIndex[(v-1)]*vertexStride);
                (*normalFunc)(normalPtr+normalIndx[(v-0)]*normalStride);
                (*vertexFunc)(vertexPtr+vertexIndex[(v-0)]*vertexStride);
            }
            ++v;
        }
        ++numverts;
        ++v;
    }
    glEnd();
   
}

void
SoIndexedTriangleStripSet::FmVnT(SoGLRenderAction *) {
    const char *vertexPtr = vpCache.getVertices(0);
    const int vertexStride = vpCache.getVertexStride();
    SoVPCacheFunc *const vertexFunc = vpCache.vertexFunc;
    const char *colorPtr = vpCache.getColors(0);
    const int colorStride = vpCache.getColorStride();
    SoVPCacheFunc *const colorFunc = vpCache.colorFunc;
    const char *normalPtr = vpCache.getNormals(0);
    const int normalStride = vpCache.getNormalStride();
    SoVPCacheFunc *const normalFunc = vpCache.normalFunc;
    const char *texCoordPtr = vpCache.getTexCoords(0);
    const int texCoordStride = vpCache.getTexCoordStride();
    SoVPCacheFunc *const texCoordFunc = vpCache.texCoordFunc;
    const int ns = numStrips;
    const int *numverts = numVertices;
    const int32_t *const vertexIndex = coordIndex.getValues(0);
    const int32_t *const normalIndx = getNormalIndices();
    const int32_t *const colorIndx = getColorIndices();
    const int32_t *const tCoordIndx = getTexCoordIndices();

    int f;
    int v = 0;
    int clrCtr =0;
    glBegin(GL_TRIANGLES);
    for (int strip = 0; strip < ns; strip++) {
        const int nf = (*numverts)-2;

        v += 2;
        for (f = 0; f < nf; f++) {
            // Per-face:
            (*colorFunc)(colorPtr+colorStride*colorIndx[clrCtr++]);

            // Now three vertices, alternating ordering:
            if (f & 1) {
                (*normalFunc)(normalPtr+normalIndx[(v-0)]*normalStride);
                (*texCoordFunc)(texCoordPtr+tCoordIndx[(v-0)]*texCoordStride);
                (*vertexFunc)(vertexPtr+vertexIndex[(v-0)]*vertexStride);
                (*normalFunc)(normalPtr+normalIndx[(v-1)]*normalStride);
                (*texCoordFunc)(texCoordPtr+tCoordIndx[(v-1)]*texCoordStride);
                (*vertexFunc)(vertexPtr+vertexIndex[(v-1)]*vertexStride);
                (*normalFunc)(normalPtr+normalIndx[(v-2)]*normalStride);
                (*texCoordFunc)(texCoordPtr+tCoordIndx[(v-2)]*texCoordStride);
                (*vertexFunc)(vertexPtr+vertexIndex[(v-2)]*vertexStride);
            } else {
                (*normalFunc)(normalPtr+normalIndx[(v-2)]*normalStride);
                (*texCoordFunc)(texCoordPtr+tCoordIndx[(v-2)]*texCoordStride);
                (*vertexFunc)(vertexPtr+vertexIndex[(v-2)]*vertexStride);
                (*normalFunc)(normalPtr+normalIndx[(v-1)]*normalStride);
                (*texCoordFunc)(texCoordPtr+tCoordIndx[(v-1)]*texCoordStride);
                (*vertexFunc)(vertexPtr+vertexIndex[(v-1)]*vertexStride);
                (*normalFunc)(normalPtr+normalIndx[(v-0)]*normalStride);
                (*texCoordFunc)(texCoordPtr+tCoordIndx[(v-0)]*texCoordStride);
                (*vertexFunc)(vertexPtr+vertexIndex[(v-0)]*vertexStride);
            }
            ++v;
        }
        ++numverts;
        ++v;
    }
    glEnd();
   
}

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

void
SoIndexedTriangleStripSet::VmFn(SoGLRenderAction *) {
    const char *vertexPtr = vpCache.getVertices(0);
    const int vertexStride = vpCache.getVertexStride();
    SoVPCacheFunc *const vertexFunc = vpCache.vertexFunc;
    const char *colorPtr = vpCache.getColors(0);
    const int colorStride = vpCache.getColorStride();
    SoVPCacheFunc *const colorFunc = vpCache.colorFunc;
    const char *normalPtr = vpCache.getNormals(0);
    const int normalStride = vpCache.getNormalStride();
    SoVPCacheFunc *const normalFunc = vpCache.normalFunc;
    const int ns = numStrips;
    const int * numverts = numVertices;
    const int32_t *const vertexIndex = coordIndex.getValues(0);
    const int32_t *const normalIndx = getNormalIndices();
    const int32_t *const colorIndx = getColorIndices();

    int f;
    int v = 0;
    int nrmCtr=0;
    glBegin(GL_TRIANGLES);
    for (int strip = 0; strip < ns; strip++) {
        const int nf = (*numverts)-2;

        v += 2;
        for (f = 0; f < nf; f++) {
            // Per-face:
            (*normalFunc)(normalPtr+normalIndx[nrmCtr++]*normalStride);

            // Now three vertices, alternating ordering:
            if (f & 1) {
                (*colorFunc)(colorPtr+colorIndx[(v-0)]*colorStride);
                (*vertexFunc)(vertexPtr+vertexIndex[(v-0)]*vertexStride);
                (*colorFunc)(colorPtr+colorIndx[(v-1)]*colorStride);
                (*vertexFunc)(vertexPtr+vertexIndex[(v-1)]*vertexStride);
                (*colorFunc)(colorPtr+colorIndx[(v-2)]*colorStride);
                (*vertexFunc)(vertexPtr+vertexIndex[(v-2)]*vertexStride);
            } else {
                (*colorFunc)(colorPtr+colorIndx[(v-2)]*colorStride);
                (*vertexFunc)(vertexPtr+vertexIndex[(v-2)]*vertexStride);
                (*colorFunc)(colorPtr+colorIndx[(v-1)]*colorStride);
                (*vertexFunc)(vertexPtr+vertexIndex[(v-1)]*vertexStride);
                (*colorFunc)(colorPtr+colorIndx[(v-0)]*colorStride);
                (*vertexFunc)(vertexPtr+vertexIndex[(v-0)]*vertexStride);
            }
            ++v;
        }
        ++numverts;
        ++v;
    }
    glEnd();
    
}
void
SoIndexedTriangleStripSet::VmFnT(SoGLRenderAction *) {
    const char *vertexPtr = vpCache.getVertices(0);
    const int vertexStride = vpCache.getVertexStride();
    SoVPCacheFunc *const vertexFunc = vpCache.vertexFunc;
    const char *colorPtr = vpCache.getColors(0);
    const int colorStride = vpCache.getColorStride();
    SoVPCacheFunc *const colorFunc = vpCache.colorFunc;
    const char *normalPtr = vpCache.getNormals(0);
    const int normalStride = vpCache.getNormalStride();
    SoVPCacheFunc *const normalFunc = vpCache.normalFunc;
    const char *texCoordPtr = vpCache.getTexCoords(0);
    const int texCoordStride = vpCache.getTexCoordStride();
    SoVPCacheFunc *const texCoordFunc = vpCache.texCoordFunc;
    const int ns = numStrips;
    const int *numverts = numVertices;
    const int32_t *const vertexIndex = coordIndex.getValues(0);
    const int32_t *const normalIndx = getNormalIndices();
    const int32_t *const colorIndx = getColorIndices();
    const int32_t *const tCoordIndx = getTexCoordIndices();

    int f;
    int v = 0;
    int nrmCtr = 0;
    glBegin(GL_TRIANGLES);
    for (int strip = 0; strip < ns; strip++) {
        const int nf = (*numverts)-2;

        v += 2;
        for (f = 0; f < nf; f++) {
            // Per-face:
            
            (*normalFunc)(normalPtr+normalIndx[nrmCtr++]*normalStride);

            // Now three vertices, alternating ordering:
            if (f & 1) {
                (*colorFunc)(colorPtr+colorIndx[(v-0)]*colorStride);
                (*texCoordFunc)(texCoordPtr+tCoordIndx[(v-0)]*texCoordStride);
                (*vertexFunc)(vertexPtr+vertexIndex[(v-0)]*vertexStride);
                (*colorFunc)(colorPtr+colorIndx[(v-1)]*colorStride);
                (*texCoordFunc)(texCoordPtr+tCoordIndx[(v-1)]*texCoordStride);
                (*vertexFunc)(vertexPtr+vertexIndex[(v-1)]*vertexStride);
                (*colorFunc)(colorPtr+colorIndx[(v-2)]*colorStride);
                (*texCoordFunc)(texCoordPtr+tCoordIndx[(v-2)]*texCoordStride);
                (*vertexFunc)(vertexPtr+vertexIndex[(v-2)]*vertexStride);
            } else {
                (*colorFunc)(colorPtr+colorIndx[(v-2)]*colorStride);
                (*texCoordFunc)(texCoordPtr+tCoordIndx[(v-2)]*texCoordStride);
                (*vertexFunc)(vertexPtr+vertexIndex[(v-2)]*vertexStride);
                (*colorFunc)(colorPtr+colorIndx[(v-1)]*colorStride);
                (*texCoordFunc)(texCoordPtr+tCoordIndx[(v-1)]*texCoordStride);
                (*vertexFunc)(vertexPtr+vertexIndex[(v-1)]*vertexStride);
                (*colorFunc)(colorPtr+colorIndx[(v-0)]*colorStride);
                (*texCoordFunc)(texCoordPtr+tCoordIndx[(v-0)]*texCoordStride);
                (*vertexFunc)(vertexPtr+vertexIndex[(v-0)]*vertexStride);
            }
            ++v;
        }
        ++numverts;
        ++v;
    }
    glEnd();
   
}

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
@= Vn
@= T  ON
@ RenderFunction
