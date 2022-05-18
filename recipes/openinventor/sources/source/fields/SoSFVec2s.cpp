// **InsertLicense** code

#include <Inventor/fields/SoSFVec2s.h>

SO_SFIELD_SOURCE(SoSFVec2s, SbVec2s, const SbVec2s &);

void
SoSFVec2s::initClass()
{
   SO_SFIELD_INIT_CLASS(SoSFVec2s, inherited);
}

void
SoSFVec2s::setValue(short x, short y)
{
   setValue(SbVec2s(x, y));
}

void
SoSFVec2s::setValue(const short xy[2])
{
   setValue(SbVec2s(xy));
}

bool
SoSFVec2s::readValue(SoInput *in)
{
   return(in->read(value[0]) && in->read(value[1]));
}

void
SoSFVec2s::writeValue(SoOutput *out) const
{
   out->write(value[0]);

   if(!out->isBinary())
      out->write(' ');

   out->write(value[1]);
}
