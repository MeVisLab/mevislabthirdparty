// **InsertLicense** code

#include <Inventor/elements/SoPolygonOffsetElement.h>

SO_ELEMENT_SOURCE(SoPolygonOffsetElement);

SoPolygonOffsetElement::~SoPolygonOffsetElement()
{
}

void
SoPolygonOffsetElement::initClass()
{
   SO_ELEMENT_INIT_CLASS(SoPolygonOffsetElement, inherited);
}

void
SoPolygonOffsetElement::init(SoState * state)
{
   SoPolygonOffsetElement::getDefault(_offsetfactor, _offsetunits, _style, _active);
}

void
SoPolygonOffsetElement::set(SoState *state, SoNode *node, float factor, float units, Style styles, bool on)
{
   SoPolygonOffsetElement *elem = (SoPolygonOffsetElement *)SoReplacedElement::getElement(state, classStackIndex, node);
   
   if(elem != NULL)
      elem->setElt(factor, units, styles, on);
}

void
SoPolygonOffsetElement::get(SoState *state, float &factor, float &units, Style &styles, bool &on)
{
   const SoPolygonOffsetElement *elem= (const SoPolygonOffsetElement *)SoElement::getConstElement(state, classStackIndex);

   factor = elem->_offsetfactor;
   units  = elem->_offsetunits;
   styles = elem->_style;
   on     = elem->_active;
}

SoPolygonOffsetElement::Style
SoPolygonOffsetElement::getStyle(SoState *state)
{
   const SoPolygonOffsetElement *elem= (const SoPolygonOffsetElement *)SoElement::getConstElement(state, classStackIndex);

   return elem->_style;
}

void
SoPolygonOffsetElement::setElt(float factor, float units, Style styles, bool on)
{
   _offsetfactor = factor;
   _offsetunits  = units;
   _style        = styles;
   _active       = on;
}

void
SoPolygonOffsetElement::getDefault(float &factor, float &units, Style &styles, bool &on)
{
   factor = 0.0f;
   units  = 0.0f;
   styles = SoPolygonOffsetElement::FILLED;
   on     = FALSE;
}
