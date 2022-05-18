// **InsertLicense** code

#ifndef  _SO_SF_VEC3S_
#define  _SO_SF_VEC3S_

#include <Inventor/system/SbSystem.h>
#include <Inventor/fields/SoSubField.h>
#include <Inventor/SbLinear.h>

class INVENTOR_API SoSFVec3s : public SoSField
{
   typedef SoSField inherited;
   
   SO_SFIELD_HEADER(SoSFVec3s, SbVec3s, const SbVec3s &);

   public:

      //! Set value from 3 shorts
      void         setValue(short x, short y, short z);

      //! Set value from array of 3 shorts
      void         setValue(const short xyz[3]);


   SoINTERNAL public:

      //! Initialize class with runtime type system.
      static void  initClass();
};

#endif  // _SO_SF_VEC3S_
