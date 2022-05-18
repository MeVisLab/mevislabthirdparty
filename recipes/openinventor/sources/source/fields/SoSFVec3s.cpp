// **InsertLicense** code

#include <Inventor/fields/SoSFVec3s.h>

SO_SFIELD_SOURCE(SoSFVec3s, SbVec3s, const SbVec3s &);

void
SoSFVec3s::initClass()
{
   SO_SFIELD_INIT_CLASS(SoSFVec3s, inherited);
}

void
SoSFVec3s::setValue(short x, short y, short z)
{
   setValue(SbVec3s(x, y, z));
}

void
SoSFVec3s::setValue(const short xyz[3])
{
   setValue(SbVec3s(xyz));
}

bool
SoSFVec3s::readValue(SoInput *in)
{
   return(in->read(value[0]) && in->read(value[1]) && in->read(value[2]));
}

void
SoSFVec3s::writeValue(SoOutput *out) const
{
   out->write(value[0]);

   if(!out->isBinary())
      out->write(' ');

   out->write(value[1]);

   if(!out->isBinary())
      out->write(' ');
   
   out->write(value[2]);
}
