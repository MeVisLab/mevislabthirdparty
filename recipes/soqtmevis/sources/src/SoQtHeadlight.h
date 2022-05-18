// **InsertLicense** code

#pragma once

#include <Inventor/Qt/SoQtDLLInit.h>
#include <Inventor/nodes/SoDirectionalLight.h>

class SOQT_MEVIS_EXPORT SoQtHeadlight : public SoDirectionalLight
{
  SO_NODE_HEADER(SoQtHeadlight);

public:
  SoQtHeadlight();

  static void initClass();

  void GLRender(SoGLRenderAction* action) override;

  // interface used by SoQtCameraController:
  void increaseStakeHolderCount() { _stakeHolderCount++; }
  void decreaseStakeHolderCount() { _stakeHolderCount--; }
  int stakeHolderCount() const { return _stakeHolderCount; }

private:
  int _stakeHolderCount;
};
