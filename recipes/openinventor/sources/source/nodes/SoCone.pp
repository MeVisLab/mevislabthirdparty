
@@===========================================================================
@@
@@ Local definitions used with SpewTriangles to set up and send vertices.
@@
@@===========================================================================
@@
@={ SendSideVertices
    // Deal with normal
@?{ GeneratePrimitives
    pv.setNormal(sideNormals[side]);
@?}
@?{ RenderGeneric
    if (sendNormals)
        glNormal3fv(sideNormals[side].getValue());
@?}
@?{ RenderNormalsNoTexture
    glNormal3fv(sideNormals[side].getValue());
@?}

    // Point at bottom of section
    pt.setValue(outerRadius * baseCoords[side][0], yBot,
                outerRadius * baseCoords[side][1]);
@?{ GeneratePrimitives
    pt[0] *= radius;
    pt[1] *= halfHeight;
    pt[2] *= radius;
    if (genTexCoords) {
        tex[0] = s;
        tex[1] = tBot;
    }
    else
        tex = tce->get(pt, sideNormals[side]);
    pv.setPoint(pt);
    pv.setTextureCoords(tex);
    shapeVertex(&pv);
@?}
@?{ RenderGeneric
    if (doTextures)
        glTexCoord2f(s, tBot);
    glVertex3fv(SCALE(pt).getValue());
@?}
@?{ RenderNormalsNoTexture
    glVertex3fv(SCALE(pt).getValue());
@?}

    // Point at top of section
    pt.setValue(innerRadius * baseCoords[side][0], yTop,
                innerRadius * baseCoords[side][1]);
@?{ GeneratePrimitives
    pt[0] *= radius;
    pt[1] *= halfHeight;
    pt[2] *= radius;
    if (genTexCoords) {
        tex[0] = s;
        tex[1] = tTop;
    }
    else
        tex = tce->get(pt, sideNormals[side]);
    pv.setPoint(pt);
    pv.setTextureCoords(tex);
    shapeVertex(&pv);
@?}
@?{ RenderGeneric
    if (doTextures)
        glTexCoord2f(s, tTop);
    glVertex3fv(SCALE(pt).getValue());
@?}
@?{ RenderNormalsNoTexture
    glVertex3fv(SCALE(pt).getValue());
@?}
@?{ DoTextures
    s += ds;
@?}
@=}
@@
@@===========================================================================
@@
@={ SendBotVertex
@?{ GeneratePrimitives
    pt[0] *= radius;
    pt[2] *= radius;
    if (genTexCoords) {
        tex[0] = BOT_TEX_S(pt[0]);
        tex[1] = BOT_TEX_T(pt[2]);
    }
    else
        tex = tce->get(pt, norm);
    pv.setPoint(pt);
    pv.setTextureCoords(tex);
    shapeVertex(&pv);
@?}
@?{ RenderGeneric
    if (doTextures)
        glTexCoord2f(BOT_TEX_S(pt[0]), BOT_TEX_T(pt[2]));
    glVertex3fv(SCALE(pt).getValue());
@?}
@?{ RenderNormalsNoTexture
    glVertex3fv(SCALE(pt).getValue());
@?}
@=}
@@
@@===========================================================================
@@
@@ This is the main triangle-spewing method for the SoCone class. It
@@ is used to generate primitives and to render.
@@
@@===========================================================================
@={ SpewTriangles
    SbBool              materialPerPart;
    int                 curParts, numSides, numSections, side, section;
    float               yTop, yBot, dy;
@?{ DoTextures
    float               s, ds, tTop, tBot, dt;
@?}
    float               outerRadius, innerRadius, dRadius;
    SbVec2f             *baseCoords;
    SbVec3f             *sideNormals, pt, norm;
@?{ Render
    SoMaterialBundle    mb(action);
@?}
@?{ GeneratePrimitives
    float               radius, halfHeight;
    SbVec4f             tex;
    SbBool              genTexCoords;
    SoPrimitiveVertex   pv;
    SoConeDetail        detail;
    const SoTextureCoordinateElement    *tce;
@?}

    SoMaterialBindingElement::Binding mbe =
        SoMaterialBindingElement::get(action->getState());
    materialPerPart =
        (mbe == SoMaterialBindingElement::PER_PART_INDEXED ||
         mbe == SoMaterialBindingElement::PER_PART);

    curParts = (parts.isIgnored() ? ALL : parts.getValue());

    // Compute number of sides and sections to use to represent
    // cone, then compute ring of x,z coordinates around cone
    // and store in baseCoords.
    computeBase(action, numSides, numSections, baseCoords, sideNormals);

@?{ Render
    // Make sure first material is sent if necessary
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

    getSize(radius, halfHeight);
@?}

    dRadius = 1.0 / numSections;

    if (HAS_PART(curParts, SIDES)) {

        // Draw each section of sides as a triangle mesh, from top to bottom
        yTop = 1.0;
        dy   = -2.0 / numSections;
@?{ DoTextures
        tTop = 1.0;
        dt   = -1.0 / numSections;
        ds   =  1.0 / numSides;
@?}

        innerRadius = 0.0;

        for (section = 0; section < numSections; section++) {

            outerRadius = innerRadius + dRadius;
            yBot = yTop + dy;

@?{ DoTextures
            tBot = tTop + dt;
            s    = 0.0;
@?}

@?{ Render
            glBegin(GL_TRIANGLE_STRIP);
@?}
@?{ GeneratePrimitives
            detail.setPart(SIDES);

            beginShape(action, TRIANGLE_STRIP);
@?}

            for (side = 0; side < numSides; side++) {
                @ SendSideVertices
            }

            // Join end of strip back to beginning
            side = 0;
@?{ DoTextures
            s = 1.0;
@?}
            @ SendSideVertices

@?{ Render
            glEnd();
@?}
@?{ GeneratePrimitives
            endShape();
@?}

            // Prepare for next section down
            innerRadius = outerRadius;
            yTop = yBot;
@?{ DoTextures
            tTop = tBot;
@?}
        }
    }

    // Draw bottom face as a series of concentric rings. The number of
    // rings is the same as the number of sections of the sides of the
    // cone.
    if (HAS_PART(curParts, BOTTOM)) {
        norm.setValue(0.0, -1.0, 0.0);
@?{ GeneratePrimitives
        pt[1] = -halfHeight;
@?}
@?{ Render
        pt[1] = -1.0;
@?}

@?{ Render
        if (materialPerPart)
            mb.send(1, FALSE);
@?}
@?{ RenderGeneric
        if (sendNormals)
            glNormal3fv(norm.getValue());
@?}
@?{ RenderNormalsNoTexture
        glNormal3fv(norm.getValue());
@?}
@?{ GeneratePrimitives
        if (materialPerPart)
            pv.setMaterialIndex(1);
        pv.setNormal(norm);
        detail.setPart(BOTTOM);
@?}

        // Start at the outside and work in
        outerRadius = 1.0;
        for (section = numSections - 1; section >= 0; --section) {

            innerRadius = outerRadius - dRadius;

            // Innermost ring is drawn as a triangle fan. This not
            // only gets better shading (because the center vertex is
            // sent), but also avoids the problem of having a polygon
            // with too many vertices.
            if (section == 0) {
@?{ Render
                glBegin(GL_TRIANGLE_FAN);
@?}
@?{ GeneratePrimitives
                beginShape(action, TRIANGLE_FAN);
@?}

                // Center point comes first
                pt[0] = pt[2] = 0.0;
@?{ GeneratePrimitives
                if (genTexCoords)
                    tex[0] = tex[1] = 0.5;
                else
                    tex = tce->get(norm, norm);
                pv.setPoint(pt);
                pv.setTextureCoords(tex);
                shapeVertex(&pv);
@?}
@?{ RenderGeneric
                if (doTextures)
                    glTexCoord2f(0.5, 0.5);
@?}
@?{ Render
                glVertex3fv(SCALE(pt).getValue());
@?}

                // Send all vertices around ring
                for (side = 0; side < numSides; side++) {
                    pt[0] = outerRadius * baseCoords[side][0];
                    pt[2] = outerRadius * baseCoords[side][1];
                    @ SendBotVertex
                }
                // Send first vertex again
                pt[0] = outerRadius * baseCoords[0][0];
                pt[2] = outerRadius * baseCoords[0][1];
                @ SendBotVertex

@?{ Render
                glEnd();
@?}
@?{ GeneratePrimitives
                endShape();
@?}
            }

            // Other rings are triangle strips
            else {
@?{ Render
                glBegin(GL_TRIANGLE_STRIP);
@?}
@?{ GeneratePrimitives
                beginShape(action, TRIANGLE_STRIP);
@?}

                // Go in reverse order so that vertex ordering is correct
                for (side = numSides - 1; side >= 0; side--) {
                    // Send points on outer and inner rings
                    pt[0] = outerRadius * baseCoords[side][0];
                    pt[2] = outerRadius * baseCoords[side][1];
                    @ SendBotVertex
                    pt[0] = innerRadius * baseCoords[side][0];
                    pt[2] = innerRadius * baseCoords[side][1];
                    @ SendBotVertex
                }

                // Join end of strip back to beginning
                side = numSides - 1;
                pt[0] = outerRadius * baseCoords[side][0];
                pt[2] = outerRadius * baseCoords[side][1];
                @ SendBotVertex
                pt[0] = innerRadius * baseCoords[side][0];
                pt[2] = innerRadius * baseCoords[side][1];
                @ SendBotVertex

@?{ Render
                glEnd();
@?}
@?{ GeneratePrimitives
                endShape();
@?}

                // Prepare for next ring
                outerRadius = innerRadius;
            }
        }
    }
@=}

////////////////////////////////////////////////////////////////////////
//
// Description:
//    Generates triangles representing a cone.
//
// Use: protected

void
SoCone::generatePrimitives(SoAction *action)
//
////////////////////////////////////////////////////////////////////////
{
    @= GeneratePrimitives       true
    @= DoTextures               true
    @= Render
    @= RenderGeneric
    @= RenderNormalsNoTexture
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
//    Generic rendering of cone with or without normals, with or
//    without texture coordinates.
//
// Use: private

void
SoCone::GLRenderGeneric(SoGLRenderAction *action,
                        SbBool sendNormals, SbBool doTextures)
//
////////////////////////////////////////////////////////////////////////
{
    SbVec3f scale, tmp;
    getSize(scale[0], scale[1]);
    scale[2] = scale[0];

    @= GeneratePrimitives
    @= DoTextures               true
    @= Render                   true
    @= RenderGeneric            true
    @= RenderNormalsNoTexture
    @SpewTriangles
}

////////////////////////////////////////////////////////////////////////
//
// Description:
//    Renders cone with normals and without texture coordinates.
//
// Use: private

void
SoCone::GLRenderNvertTnone(SoGLRenderAction *action)
//
////////////////////////////////////////////////////////////////////////
{
    SbVec3f scale, tmp;
    getSize(scale[0], scale[1]);
    scale[2] = scale[0];

    @= GeneratePrimitives
    @= DoTextures
    @= Render                   true
    @= RenderGeneric
    @= RenderNormalsNoTexture   true
    @SpewTriangles
}

