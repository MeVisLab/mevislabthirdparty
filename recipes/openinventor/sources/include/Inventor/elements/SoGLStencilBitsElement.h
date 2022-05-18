// **InsertLicense** code

#ifndef _SO_GL_STENCIL_BITS_ELEMENT_
#define _SO_GL_STENCIL_BITS_ELEMENT_

#include <Inventor/system/SbSystem.h>
#include <Inventor/elements/SoStencilBitsElement.h>

SoEXTENDER class INVENTOR_API SoGLStencilBitsElement : public SoStencilBitsElement
{
   typedef SoStencilBitsElement inherited;
   
   SO_ELEMENT_HEADER(SoGLStencilBitsElement);
   
   public:

      //! Clears only the masked bits (which must be adjacent) to value.
      //! Value is shifted automatically to fit in the masked bits.
      static void       clear(SoState *state, uint32_t mask, int32_t value = 0);
      
   protected:

      //! Destructor.
      virtual           ~SoGLStencilBitsElement();

   SoINTERNAL public:

      //! Initializes the SoGLStencilBitsElement class.
      static void       initClass();
};

#endif  // _SO_GL_STENCIL_BITS_ELEMENT_
