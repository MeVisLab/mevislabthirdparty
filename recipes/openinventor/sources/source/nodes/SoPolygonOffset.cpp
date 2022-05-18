// **InsertLicense** code

#include <Inventor/nodes/SoPolygonOffset.h>
#include <Inventor/elements/SoOverrideElement.h>
#include <Inventor/elements/SoGLPolygonOffsetElement.h>
#include <Inventor/actions/SoGLRenderAction.h>
#include <Inventor/actions/SoCallbackAction.h>

SO_NODE_SOURCE(SoPolygonOffset);

SoPolygonOffset::SoPolygonOffset()
{
   SO_NODE_CONSTRUCTOR(SoPolygonOffset);

   SO_NODE_ADD_FIELD(factor, (1.f));
   SO_NODE_ADD_FIELD(units,  (1.f));
   SO_NODE_ADD_FIELD(styles, (FILLED));
   SO_NODE_ADD_FIELD(on,     (TRUE));

   SO_NODE_DEFINE_ENUM_VALUE(Style, FILLED);
   SO_NODE_DEFINE_ENUM_VALUE(Style, LINES);
   SO_NODE_DEFINE_ENUM_VALUE(Style, POINTS);

   SO_NODE_SET_SF_ENUM_TYPE(styles, Style);

   isBuiltIn = TRUE;
}

SoPolygonOffset::~SoPolygonOffset()
{
}

void
SoPolygonOffset::initClass()
{
   SO__NODE_INIT_CLASS(SoPolygonOffset, "PolygonOffset", SoNode);

   SO_ENABLE(SoGLRenderAction, SoGLPolygonOffsetElement);
   SO_ENABLE(SoGLRenderAction, SoOverrideElement);
   
   SO_ENABLE(SoCallbackAction, SoPolygonOffsetElement);
   SO_ENABLE(SoCallbackAction, SoOverrideElement);
}

void
SoPolygonOffset::doAction(SoAction * action)
{
   SoState *state= action->getState();

   if(SoOverrideElement::getPolygonOffsetOverride(state))
      return;

   SoPolygonOffsetElement::set(state, this, factor.getValue(), units.getValue(),
                               (SoPolygonOffsetElement::Style)styles.getValue(),
                               on.getValue());

   if(isOverride())
      SoOverrideElement::setPolygonOffsetOverride(state, this, TRUE);
}

void
SoPolygonOffset::GLRender(SoGLRenderAction * action)
{
   SoPolygonOffset::doAction((SoAction *)action);
}

void
SoPolygonOffset::callback(SoCallbackAction * action)
{
   SoPolygonOffset::doAction((SoAction *)action);
}
