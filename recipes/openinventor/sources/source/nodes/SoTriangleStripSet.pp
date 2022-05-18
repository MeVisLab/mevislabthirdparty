
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
SoTriangleStripSet::
@ FuncName 
    (SoGLRenderAction* ) {

@?{ On
    // Send one normal, if there are any normals in vpCache:
    if (vpCache.getNumNormals() > 0)
        vpCache.sendNormal(vpCache.getNormals(0));
@?}
    const char *vertexPtr = vpCache.getVertices(startIndex.getValue());
    const int vertexStride = vpCache.getVertexStride();
    SoVPCacheFunc *const vertexFunc = vpCache.vertexFunc;
@?{ Pm | Fm
    const char *colorPtr = vpCache.getColors(0);
    const int colorStride = vpCache.getColorStride();
    SoVPCacheFunc *const colorFunc = vpCache.colorFunc;
@?}
@?{ Vm
    const char *colorPtr = vpCache.getColors(startIndex.getValue());
    const int colorStride = vpCache.getColorStride();
    SoVPCacheFunc *const colorFunc = vpCache.colorFunc;
@?}
@?{ Pn | Fn
    const char *normalPtr = vpCache.getNormals(0);
    const int normalStride = vpCache.getNormalStride();
    SoVPCacheFunc *const normalFunc = vpCache.normalFunc;
@?}
@?{ Vn
    const char *normalPtr = vpCache.getNormals(startIndex.getValue());
    const int normalStride = vpCache.getNormalStride();
    SoVPCacheFunc *const normalFunc = vpCache.normalFunc;
@?}
@?{ T
    const char *texCoordPtr = vpCache.getTexCoords(startIndex.getValue());
    const int texCoordStride = vpCache.getTexCoordStride();
    SoVPCacheFunc *const texCoordFunc = vpCache.texCoordFunc;
@?}
@?{ Fm | Fn
    glShadeModel(GL_FLAT);
@?}
    const int numStrips = numVertices.getNum();
    const int32_t *numVerts = numVertices.getValues(0);

    int v;
    for (int strip = 0; strip < numStrips; strip++) {
@?{ Pm
        (*colorFunc)(colorPtr); colorPtr += colorStride;
@?}
@?{ Pn
        (*normalFunc)(normalPtr); normalPtr += normalStride;
@?}
        const int nv = (*numVerts);
        glBegin(GL_TRIANGLE_STRIP);
        for (v = 0; v < nv-1; v+=2) {
@?{ Fm | Fn
            // Per-face cases:
            if (v) {
@?{ Fm
                (*colorFunc)(colorPtr); colorPtr += colorStride;
@?}
@?{ Fn
                (*normalFunc)(normalPtr); normalPtr += normalStride;
@?}
            }
@?}
@?{ Vm
            (*colorFunc)(colorPtr+0*colorStride);
@?}
@?{ Vn
            (*normalFunc)(normalPtr+0*normalStride);
@?}
@?{ T
            (*texCoordFunc)(texCoordPtr+0*texCoordStride);
@?}
            (*vertexFunc)(vertexPtr+0*vertexStride);
@?{ Fm | Fn
            // Per-face cases:
            if (v) {
@?{ Fm
                (*colorFunc)(colorPtr); colorPtr += colorStride;
@?}
@?{ Fn
                (*normalFunc)(normalPtr); normalPtr += normalStride;
@?}
            }
@?}
@?{ Vm
            (*colorFunc)(colorPtr+1*colorStride);
            colorPtr += 2*colorStride;
@?}
@?{ Vn
            (*normalFunc)(normalPtr+1*normalStride);
            normalPtr += 2*normalStride;
@?}
@?{ T
            (*texCoordFunc)(texCoordPtr+1*texCoordStride);
            texCoordPtr += 2*texCoordStride;
@?}
            (*vertexFunc)(vertexPtr+1*vertexStride);
            vertexPtr += 2*vertexStride;
        }
        if (v < nv) { // Leftovers
@?{ Fm
            (*colorFunc)(colorPtr); colorPtr += colorStride;
@?}
@?{ Fn
            (*normalFunc)(normalPtr); normalPtr += normalStride;
@?}
@?{ Vm
            (*colorFunc)(colorPtr); colorPtr += colorStride;
@?}
@?{ Vn
            (*normalFunc)(normalPtr); normalPtr += normalStride;
@?}
@?{ T
            (*texCoordFunc)(texCoordPtr); texCoordPtr += texCoordStride;
@?}
            (*vertexFunc)(vertexPtr); vertexPtr += vertexStride;
        }
        glEnd();
        ++numVerts;
    }
@?{ Fm | Fn
    glShadeModel(GL_SMOOTH);
@?}
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
SoTriangleStripSet::PMTSS SoTriangleStripSet::renderFunc[32] = {
    &SoTriangleStripSet::OmOn, &SoTriangleStripSet::OmOnT,
    &SoTriangleStripSet::OmPn, &SoTriangleStripSet::OmPnT,
    &SoTriangleStripSet::OmFn, &SoTriangleStripSet::OmFnT,
    &SoTriangleStripSet::OmVn, &SoTriangleStripSet::OmVnT,
    &SoTriangleStripSet::PmOn, &SoTriangleStripSet::PmOnT,
    &SoTriangleStripSet::PmPn, &SoTriangleStripSet::PmPnT,
    &SoTriangleStripSet::PmFn, &SoTriangleStripSet::PmFnT,
    &SoTriangleStripSet::PmVn, &SoTriangleStripSet::PmVnT,
    &SoTriangleStripSet::FmOn, &SoTriangleStripSet::FmOnT,
    &SoTriangleStripSet::FmPn, &SoTriangleStripSet::FmPnT,
    &SoTriangleStripSet::FmFn, &SoTriangleStripSet::FmFnT,
    &SoTriangleStripSet::FmVn, &SoTriangleStripSet::FmVnT,
    &SoTriangleStripSet::VmOn, &SoTriangleStripSet::VmOnT,
    &SoTriangleStripSet::VmPn, &SoTriangleStripSet::VmPnT,
    &SoTriangleStripSet::VmFn, &SoTriangleStripSet::VmFnT,
    &SoTriangleStripSet::VmVn, &SoTriangleStripSet::VmVnT,
    };

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
SoTriangleStripSet::FmVn(SoGLRenderAction *) {
    const char *vertexPtr = vpCache.getVertices(startIndex.getValue());
    const int vertexStride = vpCache.getVertexStride();
    SoVPCacheFunc *const vertexFunc = vpCache.vertexFunc;
    const char *colorPtr = vpCache.getColors(0);
    const int colorStride = vpCache.getColorStride();
    SoVPCacheFunc *const colorFunc = vpCache.colorFunc;
    const char *normalPtr = vpCache.getNormals(startIndex.getValue());
    const int normalStride = vpCache.getNormalStride();
    SoVPCacheFunc *const normalFunc = vpCache.normalFunc;
    const int numStrips = numVertices.getNum();
    const int32_t *numVerts = numVertices.getValues(0);

    int f;
    int v = 0;
    glBegin(GL_TRIANGLES);
    for (int strip = 0; strip < numStrips; strip++) {
        const int nf = (*numVerts)-2;

        v += 2;
        for (f = 0; f < nf; f++) {
            // Per-face:
            (*colorFunc)(colorPtr); colorPtr += colorStride;

            // Now three vertices, alternating ordering:
            if (f & 1) {
                (*normalFunc)(normalPtr+(v-0)*normalStride);
                (*vertexFunc)(vertexPtr+(v-0)*vertexStride);
                (*normalFunc)(normalPtr+(v-1)*normalStride);
                (*vertexFunc)(vertexPtr+(v-1)*vertexStride);
                (*normalFunc)(normalPtr+(v-2)*normalStride);
                (*vertexFunc)(vertexPtr+(v-2)*vertexStride);
            } else {
                (*normalFunc)(normalPtr+(v-2)*normalStride);
                (*vertexFunc)(vertexPtr+(v-2)*vertexStride);
                (*normalFunc)(normalPtr+(v-1)*normalStride);
                (*vertexFunc)(vertexPtr+(v-1)*vertexStride);
                (*normalFunc)(normalPtr+(v-0)*normalStride);
                (*vertexFunc)(vertexPtr+(v-0)*vertexStride);
            }
            ++v;
        }
        ++numVerts;
    }
    glEnd();
}

void
SoTriangleStripSet::FmVnT(SoGLRenderAction *) {
    const char *vertexPtr = vpCache.getVertices(startIndex.getValue());
    const int vertexStride = vpCache.getVertexStride();
    SoVPCacheFunc *const vertexFunc = vpCache.vertexFunc;
    const char *colorPtr = vpCache.getColors(0);
    const int colorStride = vpCache.getColorStride();
    SoVPCacheFunc *const colorFunc = vpCache.colorFunc;
    const char *normalPtr = vpCache.getNormals(startIndex.getValue());
    const int normalStride = vpCache.getNormalStride();
    SoVPCacheFunc *const normalFunc = vpCache.normalFunc;
    const char *texCoordPtr = vpCache.getTexCoords(startIndex.getValue());
    const int texCoordStride = vpCache.getTexCoordStride();
    SoVPCacheFunc *const texCoordFunc = vpCache.texCoordFunc;
    const int numStrips = numVertices.getNum();
    const int32_t *numVerts = numVertices.getValues(0);

    int f;
    int v = 0;
    glBegin(GL_TRIANGLES);
    for (int strip = 0; strip < numStrips; strip++) {
        const int nf = (*numVerts)-2;

        v += 2;
        for (f = 0; f < nf; f++) {
            // Per-face:
            (*colorFunc)(colorPtr); colorPtr += colorStride;

            // Now three vertices, alternating ordering:
            if (f & 1) {
                (*normalFunc)(normalPtr+(v-0)*normalStride);
                (*texCoordFunc)(texCoordPtr+(v-0)*texCoordStride);
                (*vertexFunc)(vertexPtr+(v-0)*vertexStride);
                (*normalFunc)(normalPtr+(v-1)*normalStride);
                (*texCoordFunc)(texCoordPtr+(v-1)*texCoordStride);
                (*vertexFunc)(vertexPtr+(v-1)*vertexStride);
                (*normalFunc)(normalPtr+(v-2)*normalStride);
                (*texCoordFunc)(texCoordPtr+(v-2)*texCoordStride);
                (*vertexFunc)(vertexPtr+(v-2)*vertexStride);
            } else {
                (*normalFunc)(normalPtr+(v-2)*normalStride);
                (*texCoordFunc)(texCoordPtr+(v-2)*texCoordStride);
                (*vertexFunc)(vertexPtr+(v-2)*vertexStride);
                (*normalFunc)(normalPtr+(v-1)*normalStride);
                (*texCoordFunc)(texCoordPtr+(v-1)*texCoordStride);
                (*vertexFunc)(vertexPtr+(v-1)*vertexStride);
                (*normalFunc)(normalPtr+(v-0)*normalStride);
                (*texCoordFunc)(texCoordPtr+(v-0)*texCoordStride);
                (*vertexFunc)(vertexPtr+(v-0)*vertexStride);
            }
            ++v;
        }
        ++numVerts;
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
SoTriangleStripSet::VmFn(SoGLRenderAction *) {
    const char *vertexPtr = vpCache.getVertices(startIndex.getValue());
    const int vertexStride = vpCache.getVertexStride();
    SoVPCacheFunc *const vertexFunc = vpCache.vertexFunc;
    const char *colorPtr = vpCache.getColors(startIndex.getValue());
    const int colorStride = vpCache.getColorStride();
    SoVPCacheFunc *const colorFunc = vpCache.colorFunc;
    const char *normalPtr = vpCache.getNormals(0);
    const int normalStride = vpCache.getNormalStride();
    SoVPCacheFunc *const normalFunc = vpCache.normalFunc;
    const int numStrips = numVertices.getNum();
    const int32_t *numVerts = numVertices.getValues(0);

    int f;
    int v = 0;
    glBegin(GL_TRIANGLES);
    for (int strip = 0; strip < numStrips; strip++) {
        const int nf = (*numVerts)-2;

        v += 2;
        for (f = 0; f < nf; f++) {
            // Per-face:
            (*normalFunc)(normalPtr); normalPtr += normalStride;

            // Now three vertices, alternating ordering:
            if (f & 1) {
                (*colorFunc)(colorPtr+(v-0)*colorStride);
                (*vertexFunc)(vertexPtr+(v-0)*vertexStride);
                (*colorFunc)(colorPtr+(v-1)*colorStride);
                (*vertexFunc)(vertexPtr+(v-1)*vertexStride);
                (*colorFunc)(colorPtr+(v-2)*colorStride);
                (*vertexFunc)(vertexPtr+(v-2)*vertexStride);
            } else {
                (*colorFunc)(colorPtr+(v-2)*colorStride);
                (*vertexFunc)(vertexPtr+(v-2)*vertexStride);
                (*colorFunc)(colorPtr+(v-1)*colorStride);
                (*vertexFunc)(vertexPtr+(v-1)*vertexStride);
                (*colorFunc)(colorPtr+(v-0)*colorStride);
                (*vertexFunc)(vertexPtr+(v-0)*vertexStride);
            }
            ++v;
        }
        ++numVerts;
    }
    glEnd();
}
void
SoTriangleStripSet::VmFnT(SoGLRenderAction *) {
    const char *vertexPtr = vpCache.getVertices(startIndex.getValue());
    const int vertexStride = vpCache.getVertexStride();
    SoVPCacheFunc *const vertexFunc = vpCache.vertexFunc;
    const char *colorPtr = vpCache.getColors(startIndex.getValue());
    const int colorStride = vpCache.getColorStride();
    SoVPCacheFunc *const colorFunc = vpCache.colorFunc;
    const char *normalPtr = vpCache.getNormals(0);
    const int normalStride = vpCache.getNormalStride();
    SoVPCacheFunc *const normalFunc = vpCache.normalFunc;
    const char *texCoordPtr = vpCache.getTexCoords(startIndex.getValue());
    const int texCoordStride = vpCache.getTexCoordStride();
    SoVPCacheFunc *const texCoordFunc = vpCache.texCoordFunc;
    const int numStrips = numVertices.getNum();
    const int32_t *numVerts = numVertices.getValues(0);

    int f;
    int v = 0;
    glBegin(GL_TRIANGLES);
    for (int strip = 0; strip < numStrips; strip++) {
        const int nf = (*numVerts)-2;

        v += 2;
        for (f = 0; f < nf; f++) {
            // Per-face:
            (*normalFunc)(normalPtr); normalPtr += normalStride;

            // Now three vertices, alternating ordering:
            if (f & 1) {
                (*colorFunc)(colorPtr+(v-0)*colorStride);
                (*texCoordFunc)(texCoordPtr+(v-0)*texCoordStride);
                (*vertexFunc)(vertexPtr+(v-0)*vertexStride);
                (*colorFunc)(colorPtr+(v-1)*colorStride);
                (*texCoordFunc)(texCoordPtr+(v-1)*texCoordStride);
                (*vertexFunc)(vertexPtr+(v-1)*vertexStride);
                (*colorFunc)(colorPtr+(v-2)*colorStride);
                (*texCoordFunc)(texCoordPtr+(v-2)*texCoordStride);
                (*vertexFunc)(vertexPtr+(v-2)*vertexStride);
            } else {
                (*colorFunc)(colorPtr+(v-2)*colorStride);
                (*texCoordFunc)(texCoordPtr+(v-2)*texCoordStride);
                (*vertexFunc)(vertexPtr+(v-2)*vertexStride);
                (*colorFunc)(colorPtr+(v-1)*colorStride);
                (*texCoordFunc)(texCoordPtr+(v-1)*texCoordStride);
                (*vertexFunc)(vertexPtr+(v-1)*vertexStride);
                (*colorFunc)(colorPtr+(v-0)*colorStride);
                (*texCoordFunc)(texCoordPtr+(v-0)*texCoordStride);
                (*vertexFunc)(vertexPtr+(v-0)*vertexStride);
            }
            ++v;
        }
        ++numVerts;
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
