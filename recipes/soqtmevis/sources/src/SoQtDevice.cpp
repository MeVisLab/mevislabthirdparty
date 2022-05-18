// **InsertLicense** code

#include <Inventor/Qt/devices/SoQtDevice.h>

SoType SoQtDevice::classTypeId;

void
SoQtDevice::initClass()
{
  classTypeId = SoType::createType(SoType::badType(), "SoQtDevice");
}

SbBool
SoQtDevice::isOfType(SoType type) const
{
  return getTypeId().isDerivedFrom(type);
}

SoType
SoQtDevice::getTypeId() const
{
  return classTypeId;
}
