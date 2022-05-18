
@@===========================================================================
@@
@@ This is the main triangle-spewing method for the SoSphere class. It
@@ is used to generate primitives and to render.
@@
@@===========================================================================
@={ SpewTriangles
    int         i, j, k, s_x, s_y, s_z, order, octant;
    float       botWidth, topWidth, yTop, yBot, tmp;
    SbVec3f     vec;
    int         depth;
@?{ GeneratePrimitives
    float       rad, sAvg;
    SbVec4f     tex;
    SbBool      genTexCoords;
    SoPrimitiveVertex   pv;
    const SoTextureCoordinateElement    *tce;
@?}
@?{ RenderGeneric
    float       s, t, sAvg;
@?}

    // Compute depth based on complexity
    depth = computeDepth(action);

@?{ GeneratePrimitives
    rad = (radius.isIgnored() ? 1.0 : radius.getValue());

    // Determine whether we should generate our own texture coordinates
    switch (SoTextureCoordinateElement::getType(action->getState())) {
      case SoTextureCoordinateElement::EXPLICIT:
        genTexCoords = TRUE;
        break;
      case SoTextureCoordinateElement::FUNCTION:
        genTexCoords = FALSE;
        break;
    }

    // If we're not generating our own coordinates, we'll need the
    // texture coordinate element to get coords based on points/normals.
    if (! genTexCoords)
        tce = SoTextureCoordinateElement::getInstance(action->getState());
    else {
        tex[2] = 0.0;
        tex[3] = 1.0;
    }
@?}

    for (octant = 0; octant < 8; octant++) {
        s_x = -(((octant & 01) << 1) - 1);
        s_y = -( (octant & 02)       - 1);
        s_z = -(((octant & 04) >> 1) - 1);
        order = s_x * s_y * s_z;

        for (i = 0; i < depth - 1; i++) {
            yBot = (float) i      / depth;
            yTop = (float)(i + 1) / depth;

            botWidth = 1.0 - yBot;
            topWidth = 1.0 - yTop;

@?{ Render
            glBegin(GL_TRIANGLE_STRIP);
@?}
@?{ GeneratePrimitives
            beginShape(action, TRIANGLE_STRIP);
@?}

            for (j = 0; j < depth - i; j++) {

                // First vertex
                k = order > 0 ? depth - i - j : j;
                tmp = (botWidth * k) / (depth - i);
                vec.setValue(s_x * tmp, s_y * yBot, s_z * (botWidth - tmp));
                vec.normalize();

@?{ GeneratePrimitives
                if (genTexCoords) {
                    COMPUTE_S_T(vec, tex[0], tex[1]);
                }
                else
                    tex = tce->get(vec * rad, vec);
                pv.setPoint(vec * rad);
                pv.setNormal(vec);
                pv.setTextureCoords(tex);
                shapeVertex(&pv);
@?}
@?{ RenderGeneric
                if (doTextures) {
                    COMPUTE_S_T(vec, s, t);
                    glTexCoord2f(s, t);
                }
                if (sendNormals)
                    glNormal3fv(vec.getValue());
@?}
@?{ RenderNormalsNoTexture
                glNormal3fv(vec.getValue());
@?}    
@?{ Render
                glVertex3fv((vec*rad).getValue());
@?}

                // Second vertex
                k = order > 0 ? (depth - i - 1) - j : j;
                tmp = (topWidth * k) / (depth - i - 1);
                vec.setValue(s_x * tmp, s_y * yTop, s_z * (topWidth - tmp));
                vec.normalize();

@?{ GeneratePrimitives
                if (genTexCoords) {
                    COMPUTE_S_T(vec, tex[0], tex[1]);
                    ADJUST_S(tex[0], octant);
                }
                else
                    tex = tce->get(vec * rad, vec);
                pv.setPoint(vec * rad);
                pv.setNormal(vec);
                pv.setTextureCoords(tex);
                shapeVertex(&pv);
@?}
@?{ RenderGeneric
                if (doTextures) {
                    COMPUTE_S_T(vec, s, t);
                    ADJUST_S(s, octant);
                    glTexCoord2f(s, t);
                }
                if (sendNormals)
                    glNormal3fv(vec.getValue());
@?}
@?{ RenderNormalsNoTexture
                glNormal3fv(vec.getValue());
@?}    
@?{ Render
                glVertex3fv((vec*rad).getValue());
@?}
            }

            // Last vertex
            k = order > 0 ? depth - i - j : j;
            tmp = (botWidth * k) / (depth - i);
            vec.setValue(s_x * tmp, s_y * yBot, s_z * (botWidth - tmp));
            vec.normalize();

@?{ GeneratePrimitives
            if (genTexCoords) {
                COMPUTE_S_T(vec, tex[0], tex[1]);
            }
            else
                tex = tce->get(vec * rad, vec);
            pv.setPoint(vec * rad);
            pv.setNormal(vec);
            pv.setTextureCoords(tex);
            shapeVertex(&pv);

            endShape();
@?}
@?{ RenderGeneric
            if (doTextures) {
                COMPUTE_S_T(vec, s, t);
                ADJUST_S(s, octant);
                glTexCoord2f(s, t);
            }
            if (sendNormals)
                glNormal3fv(vec.getValue());
@?}
@?{ RenderNormalsNoTexture
            glNormal3fv(vec.getValue());
@?}    
@?{ Render
            glVertex3fv((vec*rad).getValue());

            glEnd();
@?}
        }

        // Handle the top/bottom polygons specially, to avoid divide by zero
@?{ Render
        glBegin(GL_TRIANGLE_STRIP);
@?}
@?{ GeneratePrimitives
        beginShape(action, TRIANGLE_STRIP);
@?}

        yBot = (float) i / depth;
        yTop = 1.0;
        botWidth = 1 - yBot;

        // First cap vertex
        if (order > 0)
            vec.setValue(0.0, s_y * yBot, s_z * botWidth);
        else
            vec.setValue(s_x * botWidth, s_y * yBot, 0.0);
        vec.normalize();

@?{ GeneratePrimitives
        if (genTexCoords) {
            COMPUTE_S_T(vec, tex[0], tex[1]);
            ADJUST_S(tex[0], octant);
            sAvg = tex[0];
        }
        else
            tex = tce->get(vec * rad, vec);
        pv.setPoint(vec * rad);
        pv.setNormal(vec);
        pv.setTextureCoords(tex);
        shapeVertex(&pv);
@?}
@?{ RenderGeneric
        if (doTextures) {
            COMPUTE_S_T(vec, s, t);
            ADJUST_S(s, octant);
            sAvg = s;
            glTexCoord2f(s, t);
        }
        if (sendNormals)
            glNormal3fv(vec.getValue());
@?}
@?{ RenderNormalsNoTexture
        glNormal3fv(vec.getValue());
@?}    
@?{ Render
        glVertex3fv((vec*rad).getValue());
@?}

        // Second cap vertex
        if (order > 0)
            vec.setValue(s_x * botWidth, s_y * yBot, 0.0);
        else
            vec.setValue(0.0, s_y * yBot, s_z * botWidth);
        vec.normalize();

@?{ GeneratePrimitives
        if (genTexCoords) {
            COMPUTE_S_T(vec, tex[0], tex[1]);
            ADJUST_S(tex[0], octant);
            sAvg = (sAvg + tex[0]) / 2;
        }
        else
            tex = tce->get(vec * rad, vec);
        pv.setPoint(vec * rad);
        pv.setNormal(vec);
        pv.setTextureCoords(tex);
        shapeVertex(&pv);
@?}
@?{ RenderGeneric
        if (doTextures) {
            COMPUTE_S_T(vec, s, t);
            ADJUST_S(s, octant);
            sAvg = (sAvg + s) / 2;
            glTexCoord2f(s, t);
        }
        if (sendNormals)
            glNormal3fv(vec.getValue());
@?}
@?{ RenderNormalsNoTexture
        glNormal3fv(vec.getValue());
@?}    
@?{ Render
        glVertex3fv((vec*rad).getValue());
@?}

        // Third cap vertex
        vec.setValue(0.0, s_y, 0.0);

@?{ GeneratePrimitives
        if (genTexCoords) {
            tex[0] = sAvg;
            tex[1] = s_y * .5 + .5;
        }
        else
            tex = tce->get(vec * rad, vec);
        pv.setPoint(vec * rad);
        pv.setNormal(vec);
        pv.setTextureCoords(tex);
        shapeVertex(&pv);

        endShape();
@?}
@?{ RenderGeneric
        if (doTextures) {
            s = sAvg;
            t = s_y * .5 + .5;
            glTexCoord2f(s, t);
        }
        if (sendNormals)
            glNormal3fv(vec.getValue());
@?}
@?{ RenderNormalsNoTexture
        glNormal3fv(vec.getValue());
@?}    
@?{ Render
        glVertex3fv((vec*rad).getValue());

        glEnd();
@?}
    }
@=}

////////////////////////////////////////////////////////////////////////
//
// Description:
//    Generates triangles representing a sphere.
//
// Use: protected

void
SoSphere::generatePrimitives(SoAction *action)
//
////////////////////////////////////////////////////////////////////////
{
    @= GeneratePrimitives       true
    @= Render
    @= RenderGeneric
    @= RenderNormalsNoTexture
    @SpewTriangles
}

////////////////////////////////////////////////////////////////////////
//
// Description:
//    Generic rendering of sphere with or without normals, with or
//    without texture coordinates.
//
// Use: private

void
SoSphere::GLRenderGeneric(SoGLRenderAction *action,
                          SbBool sendNormals, SbBool doTextures)
//
////////////////////////////////////////////////////////////////////////
{
    float rad = (radius.isIgnored() ? 1.0 : radius.getValue());

    @= GeneratePrimitives
    @= Render                   true
    @= RenderGeneric            true
    @= RenderNormalsNoTexture
    @SpewTriangles
}

////////////////////////////////////////////////////////////////////////
//
// Description:
//    Renders sphere with normals and without texture coordinates.
//
// Use: private

void
SoSphere::GLRenderNvertTnone(SoGLRenderAction *action)
//
////////////////////////////////////////////////////////////////////////
{
    float rad = (radius.isIgnored() ? 1.0 : radius.getValue());

    @= GeneratePrimitives
    @= Render                   true
    @= RenderGeneric
    @= RenderNormalsNoTexture   true
    @SpewTriangles
}
