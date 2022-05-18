
@@===========================================================================
@@
@@ Local definitions used with SpewTriangles to set up and send vertices.
@@
@@===========================================================================
@@
@={ GenerateVertex
    pt.setValue((*verts[face][vert])[0] * w,
                (*verts[face][vert])[1] * h,
                (*verts[face][vert])[2] * d);
    if (genTexCoords) {
        tex[0] = texCoords[vert][0];
        tex[1] = texCoords[vert][1];
    }
    else
        tex = tce->get(pt, normals[face]);
    pv.setPoint(pt);
    pv.setTextureCoords(tex);
    shapeVertex(&pv);
@=}
@@
@@===========================================================================
@@
@={ SendStripVertices
@?{ GeneratePrimitives
    pt = topPoint;
    pt[0] *= w;
    pt[1] *= h;
    pt[2] *= d;
    if (genTexCoords) {
        tex[0] = s;
        tex[1] = (strip + 1) * di;
    }
    else
        tex = tce->get(pt, normals[face]);
    pv.setPoint(pt);
    pv.setTextureCoords(tex);
    shapeVertex(&pv);
    pt = botPoint;
    pt[0] *= w;
    pt[1] *= h;
    pt[2] *= d;
    if (genTexCoords) {
        tex[0] = s;
        tex[1] = strip * di;
    }
    else
        tex = tce->get(pt, normals[face]);
    pv.setPoint(pt);
    pv.setTextureCoords(tex);
    shapeVertex(&pv);
@?}
@?{ RenderGeneric
    if (doTextures) {
        glTexCoord2f(s, (strip + 1) * di);
        glVertex3fv(SCALE(topPoint).getValue());
        glTexCoord2f(s, strip * di);
        glVertex3fv(SCALE(botPoint).getValue());
    }
    else {
        glVertex3fv(SCALE(topPoint).getValue());
        glVertex3fv(SCALE(botPoint).getValue());
    }
@?}
@=}
@@
@@===========================================================================
@@
@@ This is the main triangle-spewing method for the SoCube class. It
@@ is used to generate primitives and to render.
@@
@@===========================================================================
@={ SpewTriangles
    SbBool              materialPerFace;
    int                 numDivisions, face, vert;
@?{ DoTextures
    float               s;
@?}
    SbVec3f             pt, norm;
@?{ Render
    SoMaterialBundle    mb(action);
@?}
@?{ GeneratePrimitives
    float               w, h, d;
    SbVec4f             tex;
    SbBool              genTexCoords;
    SoPrimitiveVertex   pv;
    SoCubeDetail        detail;
    const SoTextureCoordinateElement    *tce;
@?}

    materialPerFace = isMaterialPerFace(action);
    numDivisions    = computeNumDivisions(action);

@?{ Render
    // Make sure first material is sent if necessary
    if (materialPerFace)
        mb.setUpMultiple();
    mb.sendFirst();
@?}
@?{ GeneratePrimitives
    pv.setDetail(&detail);

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

    getSize(w, h, d);
@?}

@?{ Render
    if (numDivisions == 1)
        glBegin(GL_QUADS);
@?}

    for (face = 0; face < 6; face++) {

@?{ Render
        if (materialPerFace && face > 0)
            mb.send(face, numDivisions == 1);
@?}
@?{ RenderGeneric
        if (sendNormals)
            glNormal3fv(normals[face].getValue());
@?}
@?{ GeneratePrimitives
        if (face == 0 || materialPerFace)
            pv.setMaterialIndex(face);
        pv.setNormal(normals[face]);
        detail.setPart(face);
@?}

        // Simple case of one polygon per face 
        if (numDivisions == 1) {
@?{ Render
            for (vert = 0; vert < 4; vert++) {
@?{ RenderGeneric
                if (doTextures)
                    glTexCoord2fv(texCoords[vert].getValue());
@?}
                glVertex3fv(SCALE(*verts[face][vert]).getValue());
            }
@?}
@?{ GeneratePrimitives
            beginShape(action, TRIANGLE_STRIP);
            vert = 3;
            @ GenerateVertex
            vert = 0;
            @ GenerateVertex
            vert = 2;
            @ GenerateVertex
            vert = 1;
            @ GenerateVertex
            endShape();
@?}
        }

        // More than one polygon per face
        else {
            float       di = 1.0 / numDivisions;
            SbVec3f     topPoint,    botPoint,    nextBotPoint;
            SbVec3f     horizSpace, vertSpace;
            int         strip, rect;

            botPoint = *verts[face][0];

            // Compute spacing between adjacent points in both directions
            horizSpace = di * (*verts[face][1] - botPoint);
            vertSpace  = di * (*verts[face][3] - botPoint);

            // For each horizontal strip
            for (strip = 0; strip < numDivisions; strip++) {

                // Compute current top point. Save it to use as bottom
                // of next strip
                nextBotPoint = topPoint = botPoint + vertSpace;

@?{ Render
                glBegin(GL_TRIANGLE_STRIP);
@?}
@?{ GeneratePrimitives
                beginShape(action, TRIANGLE_STRIP);
@?}

                // Send points at left end of strip
@?{ DoTextures
                s = 0.0;
@?}
                @ SendStripVertices

                // For each rectangular piece of strip
                for (rect = 0; rect < numDivisions; rect++) {

                    // Go to next rect
                    topPoint += horizSpace;
                    botPoint += horizSpace;
@?{ DoTextures
                    s += di;
@?}

                    // Send points at right side of rect
                    @ SendStripVertices
                }

@?{ Render
                glEnd();
@?}
@?{ GeneratePrimitives
                endShape();
@?}

                // Get ready for next strip
                botPoint = nextBotPoint;
            }
        }
    }
@?{ Render

    if (numDivisions == 1)
        glEnd();
@?}
@=}
////////////////////////////////////////////////////////////////////////
//
// Description:
//    Generates triangles representing a cube.
//
// Use: protected

void
SoCube::generatePrimitives(SoAction *action)
//
////////////////////////////////////////////////////////////////////////
{
    @= GeneratePrimitives       true
    @= DoTextures               true
    @= Render
    @= RenderGeneric
    @SpewTriangles
}

//
// Macro to multiply out coordinates to avoid extra GL calls:
//
#define SCALE(pt) (tmp[0] = (pt)[0]*scale[0], tmp[1] = (pt)[1]*scale[1], \
                   tmp[2] = (pt)[2]*scale[2], tmp)

////////////////////////////////////////////////////////////////////////
//
// Description:
//    Generic rendering of cube with or without normals, with or
//    without texture coordinates.
//
// Use: private

void
SoCube::GLRenderGeneric(SoGLRenderAction *action,
                        SbBool sendNormals, SbBool doTextures)
//
////////////////////////////////////////////////////////////////////////
{
    SbVec3f scale, tmp;
    getSize(scale[0], scale[1], scale[2]);

    @= GeneratePrimitives
    @= DoTextures               true
    @= Render                   true
    @= RenderGeneric            true
    @SpewTriangles
}


