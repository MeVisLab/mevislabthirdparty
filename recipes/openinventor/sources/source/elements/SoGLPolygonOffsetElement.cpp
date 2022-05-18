// **InsertLicense** code

#include <Inventor/elements/SoGLPolygonOffsetElement.h>
#include <Inventor/system/SbOpenGL.h>

SO_ELEMENT_SOURCE(SoGLPolygonOffsetElement);

SoGLPolygonOffsetElement::~SoGLPolygonOffsetElement()
{
}

void
SoGLPolygonOffsetElement::initClass()
{
   SO_ELEMENT_INIT_CLASS(SoGLPolygonOffsetElement, inherited);
}

void
SoGLPolygonOffsetElement::init(SoState *state)
{
   inherited::init(state);
   
   _copiedFromParent= FALSE;
   
   // Save the state.
   _state = state;

   _currentstyles       = (Style)0;
   _currentoffsetfactor = 1.0f;
   _currentoffsetunits  = 1.0f;
}

void
SoGLPolygonOffsetElement::push(SoState *state)
{
   const SoGLPolygonOffsetElement *prevElt = (const SoGLPolygonOffsetElement*)getNextInStack();

   _offsetfactor = prevElt->_offsetfactor;
   _offsetunits  = prevElt->_offsetunits;
   _style        = prevElt->_style;
   _active       = prevElt->_active;
   
   _currentstyles= prevElt->_currentstyles;
   _currentoffsetfactor= prevElt->_currentoffsetfactor;
   _currentoffsetunits= prevElt->_currentoffsetunits;
   
   _copiedFromParent= TRUE;
   _state= state;
}

void
SoGLPolygonOffsetElement::pop(SoState *state, const SoElement *childElt)
{
   // Since popping this element has GL side effects, make sure any
   // open caches capture it.  We may not send any GL commands, but
   // the cache dependency must exist even if we don't send any GL
   // commands, because if the element changes, the _lack_ of GL
   // commands here is a bug (remember, GL commands issued here are
   // put inside the cache).
   capture(state);
   _copiedFromParent = FALSE;
   
   // If the previous element didn't have the same value...
   const SoGLPolygonOffsetElement *child = (const SoGLPolygonOffsetElement*)childElt;

   _currentstyles       = child->_currentstyles;
   _currentoffsetfactor = child->_currentoffsetfactor;
   _currentoffsetunits  = child->_currentoffsetunits;

   if(*this != *child)
      send();
}

void
SoGLPolygonOffsetElement::setElt(float factor, float units, Style styles, bool on)
{
   // Optimization:  on push, we copy the value from the previous
   // element.  If the element is set to the same value, we don't
   // bother sending it, but do add a cache dependency on the
   // previous element.

   if(   _style        != styles
      || _active       != on
      || _offsetfactor != factor
      || _offsetunits  != units
   ) {
       inherited::setElt(factor, units, styles, on);
       send();
       _copiedFromParent = FALSE;
   }
   else if(_copiedFromParent) {
       SoGLPolygonOffsetElement *parent = (SoGLPolygonOffsetElement *)getNextInStack();
       parent->capture(_state);
   }
}

void
SoGLPolygonOffsetElement::send()
{
   if(_active) {
      if(_style & FILLED) {
         if(!(_currentstyles & FILLED))
            glEnable(GL_POLYGON_OFFSET_FILL);
      }
      else {
         if(_currentstyles & FILLED)
            glDisable(GL_POLYGON_OFFSET_FILL);
      }
      if(_style & LINES) {
         if(!(_currentstyles & LINES))
            glEnable(GL_POLYGON_OFFSET_LINE);
      }
      else {
         if(_currentstyles & LINES)
            glDisable(GL_POLYGON_OFFSET_LINE);
      }
      if(_style & POINTS) {
         if(!(_currentstyles & POINTS))
            glEnable(GL_POLYGON_OFFSET_POINT);
      }
      else {
         if(_currentstyles & POINTS)
            glDisable(GL_POLYGON_OFFSET_POINT);
      }

      glPolygonOffset(_offsetfactor, _offsetunits);

      _currentstyles = _style;
   }
   else { // ! active
      if(_currentstyles & FILLED)
         glDisable(GL_POLYGON_OFFSET_FILL);
      if(_currentstyles & LINES)
         glDisable(GL_POLYGON_OFFSET_LINE);
      if(_currentstyles & POINTS)
         glDisable(GL_POLYGON_OFFSET_POINT);

      _currentstyles = (Style)0;
   }  

   // update current offset values before returning
   _currentoffsetfactor = _offsetfactor;
   _currentoffsetunits  = _offsetunits;
}

bool
operator ==(const SoGLPolygonOffsetElement &e1, const SoGLPolygonOffsetElement &e2)
{
   return(e1._style               == e2._style
       && e1._active              == e2._active
       && e1._offsetfactor        == e2._offsetfactor
       && e1._offsetunits         == e2._offsetunits

       && e1._currentstyles       == e2._currentstyles
       && e1._currentoffsetfactor == e2._currentoffsetfactor
       && e1._currentoffsetunits  == e2._currentoffsetunits);
}
