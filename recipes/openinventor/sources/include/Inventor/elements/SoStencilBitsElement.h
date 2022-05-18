// **InsertLicense** code

#ifndef _SO_STENCIL_BITS_ELEMENT_
#define _SO_STENCIL_BITS_ELEMENT_

#include <Inventor/system/SbSystem.h>
#include <Inventor/elements/SoInt32Element.h>

SoEXTENDER class INVENTOR_API SoStencilBitsElement : public SoInt32Element
{
   typedef SoInt32Element inherited;
   
   SO_ELEMENT_HEADER(SoStencilBitsElement);
   
   public:

      //! Initializes element
      virtual void      init(SoState *state);

      //! Acquires a certain number of bits for stencil operations.
      //! This returns a mask of the acquired bits or 0x0 if there
      //! are not enough stencil bits available.
      static uint32_t   acquireBits(SoState *state, SoNode *node, int num);
      
      //! Releases the stencil bits specified by the mask.
      static void       releaseBits(SoState *state, uint32_t mask);
      
      //! Forget about the stencil bits in use. This is required e.g. for framebuffer
      //! objects which use the same GL context but have a different stencil buffer. In
      //! that case the currently aquired stencil bits are not valid for this buffer.
      //! The programmer must then clear the used stencil bits of the element.
      static void       clearBitsInUse(SoState *state);
      
      //! Returns a mask of the current stencil bits in use.
      static uint32_t   get(SoState *state) {
         return (uint32_t)SoInt32Element::get(classStackIndex, state);
      }

      //! Returns the default mask of stencil bits in use.
      static uint32_t   getDefault() {
         return 0x0;
      }
      
      //! Returns the number of stencil bits not currently used.
      static int        getNumRemainingBits(SoState *state);

      //! Overrides push() method to copy values from next instance in the stack.
      virtual void      push(SoState *state);

   protected:

      //! Number of positions a value must be shifted according to mask.
      static int        getNumBitPositionsToShift(uint32_t mask, SoState *state);
      
      //! Destructor.
      virtual           ~SoStencilBitsElement();

      //! Returns the number of bits supported by GL implementation.
      int               getNumGLBits() const;
      
   SoINTERNAL public:

      //! Initializes the SoStencilBitsElement class.
      static void       initClass();

   private:

      //! Stores number of bits supported by GL implementation.
      mutable int       numGLBits;
};

#endif  // _SO_STENCIL_BITS_ELEMENT_
