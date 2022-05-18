// **InsertLicense** code

#include <Inventor/elements/SoGLStencilBitsElement.h>
#include <Inventor/elements/SoViewportRegionElement.h>
#include <Inventor/system/SbOpenGL.h>

SO_ELEMENT_SOURCE(SoGLStencilBitsElement)

SoGLStencilBitsElement::~SoGLStencilBitsElement()
{
}

void
SoGLStencilBitsElement::initClass()
{
   SO_ELEMENT_INIT_CLASS(SoGLStencilBitsElement, inherited);
}

void
SoGLStencilBitsElement::clear(SoState *state, uint32_t mask, int32_t value)
{
   if(mask == 0x0)
      return;
   
   value <<= getNumBitPositionsToShift(mask, state);
   
   const SoGLStencilBitsElement *elt = (const SoGLStencilBitsElement *)getConstElement(state, classStackIndex);
   
   // If no other node has stencil bits in use, then
   if((mask & (uint32_t)elt->data) == (uint32_t)elt->data) {
      glClearStencil((GLint)value);
      glClear(GL_STENCIL_BUFFER_BIT);
   }
   else {
      const SbViewportRegion &vp = SoViewportRegionElement::get(state);
      SbVec2s vpSize = vp.getViewportSizePixels();

      glPushAttrib(GL_STENCIL_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);

      glEnable(GL_STENCIL_TEST);
      
      glStencilFunc(GL_ALWAYS, (GLint)value, mask);
      glStencilOp(GL_REPLACE, GL_REPLACE, GL_REPLACE);

      glDisable(GL_DEPTH_TEST);
      glColorMask(GL_FALSE, GL_FALSE, GL_FALSE, GL_FALSE);

      glMatrixMode(GL_PROJECTION);
      glPushMatrix();
      glLoadIdentity();
      glOrtho(0, vpSize[0], 0, vpSize[1], -1, 1);
      glMatrixMode(GL_MODELVIEW);
      glPushMatrix();
      glLoadIdentity();

      glBegin(GL_QUADS);
      glVertex2i(0, 0);
      glVertex2i(vpSize[0], 0);
      glVertex2i(vpSize[0], vpSize[1]);
      glVertex2i(0, vpSize[1]);
      glEnd();

      glMatrixMode(GL_PROJECTION);
      glPopMatrix();
      glMatrixMode(GL_MODELVIEW);
      glPopMatrix();

      glPopAttrib();
   }
}
