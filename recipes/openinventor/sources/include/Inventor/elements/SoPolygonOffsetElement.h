// **InsertLicense** code

#ifndef  _SO_POLYGON_OFFSET_ELEMENT_
#define  _SO_POLYGON_OFFSET_ELEMENT_

#include <Inventor/system/SbSystem.h>
#include <Inventor/elements/SoReplacedElement.h>

SoEXTENDER class INVENTOR_API SoPolygonOffsetElement : public SoReplacedElement
{
   typedef SoReplacedElement inherited;

   SO_ELEMENT_HEADER(SoPolygonOffsetElement);

   public:

      enum Style {
         FILLED = 0x01,
         LINES  = 0x02,
         POINTS = 0x04,
         ALL    = 0xff
      };

      //! Initializes element
      virtual void      init(SoState * state);

      static void       set(SoState *state, SoNode *node, float factor, float units, Style styles, bool on);
     
      static void       get(SoState *state, float &factor, float &units, Style &styles, bool &on);
      
      static Style      getStyle(SoState *state);
      
      static void       getDefault(float &factor, float &units, Style &styles, bool &on);

   protected:

      Style  _style;
      bool _active;
      float  _offsetfactor;
      float  _offsetunits;

      //! Destructor.
      virtual           ~SoPolygonOffsetElement();

      virtual void      setElt(float factor, float units, Style styles, bool on);

   SoINTERNAL public:

      //! Initializes the SoPolygonOffsetElement class.
      static void       initClass();
};

#endif  // _SO_POLYGON_OFFSET_ELEMENT_
