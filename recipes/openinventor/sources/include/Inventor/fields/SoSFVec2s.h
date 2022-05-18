// **InsertLicense** code

#ifndef  _SO_SF_VEC2S_
#define  _SO_SF_VEC2S_

#include <Inventor/system/SbSystem.h>
#include <Inventor/fields/SoSubField.h>
#include <Inventor/SbLinear.h>

class INVENTOR_API SoSFVec2s : public SoSField
{
   typedef SoSField inherited;
   
   SO_SFIELD_HEADER(SoSFVec2s, SbVec2s, const SbVec2s &);

   public:

      //! Set value from 2 shorts
      void         setValue(short x, short y);

      //! Set value from array of 2 shorts
      void         setValue(const short xy[2]);


   SoINTERNAL public:

      //! Initialize class with runtime type system.
      static void  initClass();
};

#endif  // _SO_SF_VEC2S_
