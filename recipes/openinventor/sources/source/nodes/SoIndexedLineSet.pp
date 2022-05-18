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
SoIndexedLineSet::
@ FuncName 
    (SoGLRenderAction* action ) {
    const int np = numPolylines;
    const int* numverts = numVertices;
    const int32_t *const vertexIndex = coordIndex.getValues(0);
    SbBool renderAsPoints = (SoDrawStyleElement::get(action->getState()) ==
                      SoDrawStyleElement::POINTS);
    SbBool sendAdj = sendAdjacency.getValue();

@?{ On
    // Send one normal, if there are any normals in vpCache:
    if (vpCache.getNumNormals() > 0)
        vpCache.sendNormal(vpCache.getNormals(0));
@?}
    const char *vertexPtr = vpCache.getVertices(0);
    const unsigned int vertexStride = vpCache.getVertexStride();
    SoVPCacheFunc *const vertexFunc = vpCache.vertexFunc;
@?{ Pm | Fm | Vm
    const char *colorPtr = vpCache.getColors(0);
    const unsigned int colorStride = vpCache.getColorStride();
    SoVPCacheFunc *const colorFunc = vpCache.colorFunc;
    const int32_t *const colorIndx = getColorIndices();
@?}
@?{ Pn
    int nrmCtr = 0;
@?}
@?{ Pm
    int clrCtr = 0;
@?}
@?{ Pn | Fn | Vn
    const char *normalPtr = vpCache.getNormals(0);
    const unsigned int normalStride = vpCache.getNormalStride();
    SoVPCacheFunc *const normalFunc = vpCache.normalFunc;
    const int32_t *const normalIndx = getNormalIndices();
@?}

@?{ T
    const char *texCoordPtr = vpCache.getTexCoords(0);
    const unsigned int texCoordStride = vpCache.getTexCoordStride();
    SoVPCacheFunc *const texCoordFunc = vpCache.texCoordFunc;
    const int32_t *const tCoordIndx = getTexCoordIndices();
@?} 
    int vtxCtr = 0;
    int v;
    for (int polyline = 0; polyline < np; polyline++) {
@?{ Fm
        (*colorFunc)(colorPtr+colorStride*colorIndx[polyline]);
@?}
@?{ Fn
        (*normalFunc)(normalPtr+normalStride*normalIndx[polyline]);
@?}
@?{ Pn | Pm
        const int nv = (*numverts) -1;
@?}
@?{ Fn | Vn | On
@?{ Fm | Vm | Om
        const int nv = (*numverts);      
@?}
@?}         
        if(renderAsPoints){
            glBegin(GL_POINTS);
        }
        else {
@?{ Pn | Pm
            glBegin(sendAdj?GL_LINES_ADJACENCY:GL_LINES);
@?{ Vm
            (*colorFunc)(colorPtr+colorStride*colorIndx[vtxCtr]);
@?}
@?{ Vn
            (*normalFunc)(normalPtr+normalStride*normalIndx[vtxCtr]);   
@?}     
@?}

@?{ Fn | Vn | On
@?{ Fm | Vm | Om
            glBegin(sendAdj?GL_LINE_STRIP_ADJACENCY:GL_LINE_STRIP);      
@?}
@?}         
        }
        for (v = 0; v < nv; v++) {                  
@?{ Pm | Pn
@?{ Pm
                (*colorFunc)(colorPtr+colorStride*colorIndx[clrCtr++]); 
@?}
@?{ Pn
                (*normalFunc)(normalPtr+normalStride*normalIndx[nrmCtr++]);             
@?}
@?{ T
                (*texCoordFunc)(texCoordPtr+texCoordStride*tCoordIndx[vtxCtr]);
@?}
                (*vertexFunc)(vertexPtr+vertexStride*vertexIndex[vtxCtr++]);
@?{ Vn
                (*normalFunc)(normalPtr+normalStride*normalIndx[vtxCtr]);
@?}
@?{ Vm
                (*colorFunc)(colorPtr+colorStride*colorIndx[vtxCtr]);              
@?}
@?{ T
                (*texCoordFunc)(texCoordPtr+texCoordStride*tCoordIndx[vtxCtr]);
@?}
                (*vertexFunc)(vertexPtr+vertexStride*vertexIndex[vtxCtr]);
@?}  //end Pm | Pn
@?{ Fn | Vn | On
@?{ Fm | Vm | Om
@?{ Vn
                (*normalFunc)(normalPtr+normalStride*normalIndx[vtxCtr]);
@?}
@?{ Vm
                (*colorFunc)(colorPtr+colorStride*colorIndx[vtxCtr]);              
@?}
@?{ T
                (*texCoordFunc)(texCoordPtr+texCoordStride*tCoordIndx[vtxCtr]);        
@?}
                (*vertexFunc)(vertexPtr+vertexStride*vertexIndex[vtxCtr++]);                     
@?}
@?}              
        }
        glEnd();
@?{ Fn | Vn | On
@?{ Fm | Vm | Om
        vtxCtr++;  //skip over -1 at end of polyline
@?}
@?}
@?{ Pm | Pn
        vtxCtr+=2;  // Skip over -1 at end of polyline, plus last vtx.
@?}
        ++numverts;
    }
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
@= Fn On
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
