// **InsertLicense** code

#ifndef _SO_GL_POLYGON_OFFSET_ELEMENT_
#define _SO_GL_POLYGON_OFFSET_ELEMENT_

#include <Inventor/system/SbSystem.h>
#include <Inventor/elements/SoPolygonOffsetElement.h>

SoEXTENDER class INVENTOR_API SoGLPolygonOffsetElement : public SoPolygonOffsetElement
{
   typedef SoPolygonOffsetElement inherited;

   SO_ELEMENT_HEADER(SoGLPolygonOffsetElement);

   public:

      //! Initializes element
      virtual void      init(SoState *state);

      //! Override push() method to copy state pointer and value of
      //! previous element, to avoid sending GL commands if the elements
      //! are the same.
      virtual void      push(SoState *state);

      //! Override pop() method so side effects can occur in GL
      virtual void      pop(SoState *state, const SoElement *childElt);
      
      friend bool operator ==(const SoGLPolygonOffsetElement &e1, const SoGLPolygonOffsetElement &e2);
      friend bool operator !=(const SoGLPolygonOffsetElement &e1, const SoGLPolygonOffsetElement &e2) {
         return !(e1 == e2);
      }

   protected:

      virtual void      setElt(float factor, float units, Style styles, bool on);

      //! Destructor.
      virtual           ~SoGLPolygonOffsetElement();

   SoINTERNAL public:

      //! Initializes the SoGLPolygonOffsetElement class.
      static void       initClass();

   private:

      //! This variable is TRUE if the value in this element was copied
      //! from our parent.  If set is called with the same value, no GL
      //! commands have to be done-- it is as if this element doesn't
      //! exist, and the parent's value is used.  Of course, a cache
      //! dependency will have to be added in this case (if the parent
      //! changes, the cache is not valid).  Set sets this flag to false.
      bool     _copiedFromParent;
      
      Style    _currentstyles;
      float    _currentoffsetfactor;
      float    _currentoffsetunits;

      //! We need to store the state.
      SoState *_state;

      //! Sends changes in element to GL
      void              send();
};

#endif  // _SO_GL_POLYGON_OFFSET_ELEMENT_
