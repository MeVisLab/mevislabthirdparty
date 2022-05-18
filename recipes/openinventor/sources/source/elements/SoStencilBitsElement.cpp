// **InsertLicense** code

#include <Inventor/elements/SoStencilBitsElement.h>
#include <Inventor/system/SbOpenGL.h>

SO_ELEMENT_SOURCE(SoStencilBitsElement)


SoStencilBitsElement::~SoStencilBitsElement()
{
}

void
SoStencilBitsElement::initClass()
{
   SO_ELEMENT_INIT_CLASS(SoStencilBitsElement, inherited);
}

void
SoStencilBitsElement::init(SoState *)
{
   data = getDefault();
   numGLBits = -1;
}

uint32_t
SoStencilBitsElement::acquireBits(SoState *state, SoNode *, int num)
{
   // Get an instance we can change (pushing if necessary)
   SoStencilBitsElement *elt = (SoStencilBitsElement *)getElement(state, classStackIndex);

   // Being overridden?
   if(elt == NULL)
      return 0x0;

   int max_num_bits = elt->getNumGLBits();
   
   uint32_t avail_bits = ~ (uint32_t)elt->data;
   uint32_t mask = 0x0;
   
   for(uint32_t bit_test = 0x1; num > 0 && bit_test < ((uint32_t)0x1 << max_num_bits); bit_test <<= 1) {
      if(avail_bits & bit_test) {       // Is this bit available?
         mask |= bit_test;
         
         num--;
      }
   }
   
   if(num > 0)  // Not enough bits remaining!
      return 0x0;

   elt->data = (uint32_t)elt->data | mask;
   
   return mask;
}

void
SoStencilBitsElement::releaseBits(SoState *state, uint32_t mask)
{
   // Get an instance we can change (pushing if necessary)
   SoStencilBitsElement *elt = (SoStencilBitsElement *)getElement(state, classStackIndex);

   // Being overridden?
   if(elt == NULL)
      return;

   elt->data = (uint32_t)elt->data ^ mask;
}

int
SoStencilBitsElement::getNumBitPositionsToShift(uint32_t mask, SoState *state)
{
   const SoStencilBitsElement *elt = (const SoStencilBitsElement *)getConstElement(state, classStackIndex);

   if(mask == 0x0)
      return 0;
   
   int max_num_bits = elt->getNumGLBits();
   int num = 0;
   
   for(uint32_t bit_test = 0x1; bit_test < ((uint32_t)0x1 << max_num_bits); bit_test <<= 1) {
      if(mask & bit_test) {       // Is this bit set in mask?
         break;
      }
      num++;
   }
   
   return num;
}

int
SoStencilBitsElement::getNumRemainingBits(SoState *state)
{
   const SoStencilBitsElement *elt = (const SoStencilBitsElement *)getConstElement(state, classStackIndex);

   int max_num_bits = elt->getNumGLBits();
   
   uint32_t avail_bits = ~ (uint32_t)elt->data;
   int remaining_bits = 0;
   
   for(uint32_t bit_test = 0x1; bit_test < ((uint32_t)0x1 << max_num_bits); bit_test <<= 1) {
      if(avail_bits & bit_test) // Is this bit available?
         remaining_bits++;
   }
   
   return remaining_bits;
}

void       
SoStencilBitsElement::clearBitsInUse(SoState *state)
{
   // Get an instance we can change (pushing if necessary)
   SoStencilBitsElement *elt = (SoStencilBitsElement *)getElement(state, classStackIndex);

   // Being overridden?
   if(elt == NULL)
      return;

   elt->data = 0;
   
   // Reevaluate the size of the stencil buffer
   elt->numGLBits = -1;
}

int
SoStencilBitsElement::getNumGLBits() const
{
   // Inquire GL if not already done
   if(numGLBits < 0) {
      GLint num;
      glGetIntegerv(GL_STENCIL_BITS, &num);

      numGLBits = num;
   }

   return numGLBits;
}


void
SoStencilBitsElement::push(SoState * /*state*/)
{
   // Copying current mask of stencil bits in use from
   // previous top instance.
   data = ((SoStencilBitsElement *)getNextInStack())->data;
  
   // Copy current number of available stencil bits
   numGLBits = ((SoStencilBitsElement *)getNextInStack())->numGLBits;
}
