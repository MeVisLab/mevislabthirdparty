// **InsertLicense** code

#include "SoQtHeadlight.h"
#include <Inventor/elements/SoViewingMatrixElement.h>
#include <Inventor/actions/SoGLRenderAction.h>

SO_NODE_SOURCE(SoQtHeadlight)

void SoQtHeadlight::initClass()
{
  SO_NODE_INIT_CLASS(SoQtHeadlight, SoDirectionalLight, "DirectionalLight");
}

SoQtHeadlight::SoQtHeadlight()
{
  SO_NODE_CONSTRUCTOR(SoQtHeadlight);
  direction.enableContainerNotify(false);
  _stakeHolderCount = 0;
}

void SoQtHeadlight::GLRender(SoGLRenderAction* action)
{
  SbVec3f lightVector(.2, -.2, -.9797958971);
  SbVec3f worldLightVector;
  const SbMatrix& viewingMatrix = SoViewingMatrixElement::get(action->getState());
  SbMatrix transposed = viewingMatrix.transpose();
  transposed.multDirMatrix(lightVector, worldLightVector);
  worldLightVector.normalize();
  direction.setValue(worldLightVector);
  SoDirectionalLight::GLRender(action);
}
