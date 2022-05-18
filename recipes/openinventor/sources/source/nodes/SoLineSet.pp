
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
SoLineSet::
@ FuncName 
    (SoGLRenderAction* action ) {
    bool independent = independentLines.getValue();
    const int np = independent ? totalNumVertices / 2 : numVertices.getNum();
    const int32_t* numverts = independent ? NULL : numVertices.getValues(0);
    SbBool renderAsPoints = (SoDrawStyleElement::get(action->getState()) ==
                      SoDrawStyleElement::POINTS);
    SbBool sendAdj = sendAdjacency.getValue();
    
@?{ On
    // Send one normal, if there are any normals in vpCache:
    if (vpCache.getNumNormals() > 0)
        vpCache.sendNormal(vpCache.getNormals(0));
@?}
    const char *vertexPtr = vpCache.getVertices(startIndex.getValue());
    const unsigned int vertexStride = vpCache.getVertexStride();
    SoVPCacheFunc *const vertexFunc = vpCache.vertexFunc;
@?{ Pm | Fm 
    const char *colorPtr = vpCache.getColors(0);
    const unsigned int colorStride = vpCache.getColorStride();
    SoVPCacheFunc *const colorFunc = vpCache.colorFunc;
@?}
@?{ Vm
    const char *colorPtr = vpCache.getColors(startIndex.getValue());
    const unsigned int colorStride = vpCache.getColorStride();
    SoVPCacheFunc *const colorFunc = vpCache.colorFunc;
@?}
@?{ Vn
    const char *normalPtr = vpCache.getNormals(startIndex.getValue());
    const unsigned int normalStride = vpCache.getNormalStride();
    SoVPCacheFunc *const normalFunc = vpCache.normalFunc;
@?}
@?{ Pn | Fn 
    const char *normalPtr = vpCache.getNormals(0);
    const unsigned int normalStride = vpCache.getNormalStride();
    SoVPCacheFunc *const normalFunc = vpCache.normalFunc;
@?}
@?{ T
    const char *texCoordPtr = vpCache.getTexCoords(startIndex.getValue());
    const unsigned int texCoordStride = vpCache.getTexCoordStride();
    SoVPCacheFunc *const texCoordFunc = vpCache.texCoordFunc;
@?} 
    int v;
    for (int polyline = 0; polyline < np; polyline++) {
@?{ Fm
        (*colorFunc)(colorPtr);
        colorPtr+=colorStride;
@?}
@?{ Fn
        (*normalFunc)(normalPtr);
        normalPtr += normalStride;
@?}
@?{ Pn | Pm
        const int nv = numverts ? (*numverts) -1 : 1;
@?}
@?{ Fn | Vn | On
@?{ Fm | Vm | Om
        const int nv = numverts ? (*numverts) : 2;
@?}
@?}         
        if(renderAsPoints){
            glBegin(GL_POINTS);
        }
        else {
@?{ Pn | Pm
            glBegin(sendAdj?GL_LINES_ADJACENCY:GL_LINES);
@?{ Vm
            (*colorFunc)(colorPtr);
            colorPtr += colorStride;
@?}
@?{ Vn
            (*normalFunc)(normalPtr);
            normalPtr += normalStride;  
@?}     
@?}// end Pn|Pm

@?{ Fn | Vn | On
@?{ Fm | Vm | Om
            glBegin(sendAdj?GL_LINE_STRIP_ADJACENCY:GL_LINE_STRIP);      
@?}
@?}         
        }
        for (v = 0; v < nv; v++) {                  
@?{ Pm | Pn
@?{ Pm
                (*colorFunc)(colorPtr);
                colorPtr += colorStride; 
@?}
@?{ Pn
                (*normalFunc)(normalPtr);
                normalPtr += normalStride;              
@?}
@?{ T
                (*texCoordFunc)(texCoordPtr);
                texCoordPtr += texCoordStride;
        
@?}
                (*vertexFunc)(vertexPtr);
                vertexPtr += vertexStride;
@?{ Vn
                (*normalFunc)(normalPtr);
                normalPtr += normalStride;
@?}
@?{ Vm
                (*colorFunc)(colorPtr);
                colorPtr += colorStride;                   
@?}
@?{ T
                (*texCoordFunc)(texCoordPtr);
@?}
                (*vertexFunc)(vertexPtr);
        
@?}  //end Pm | Pn
@?{ Fn | Vn | On
@?{ Fm | Vm | Om
@?{ Vn
                (*normalFunc)(normalPtr);
                normalPtr += normalStride;
@?}
@?{ Vm
                (*colorFunc)(colorPtr);
                colorPtr += colorStride;                   
@?}
@?{ T
                (*texCoordFunc)(texCoordPtr);
                texCoordPtr += texCoordStride;         
@?}
                (*vertexFunc)(vertexPtr);
                vertexPtr += vertexStride;                       
@?}
@?}              
        }
        glEnd();
@?{ Pn | Pm
        vertexPtr += vertexStride;
@?{ T
        texCoordPtr += texCoordStride;
@?}
@?}
        if (numverts) { ++numverts; }
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
