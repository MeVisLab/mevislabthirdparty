// **InsertLicense** code

#ifndef  _SO_POLYGON_OFFSET_
#define  _SO_POLYGON_OFFSET_

#include <Inventor/system/SbSystem.h>
#include <Inventor/elements/SoPolygonOffsetElement.h>
#include <Inventor/nodes/SoSubNode.h>
#include <Inventor/fields/SoSFBitMask.h>
#include <Inventor/fields/SoSFBool.h>
#include <Inventor/fields/SoSFFloat.h>

class SoAction;
class SoCallbackAction;
class SoGLRenderAction;

class INVENTOR_API SoPolygonOffset : public SoNode
{
   SO_NODE_HEADER(SoPolygonOffset);
   
   typedef SoNode inherited;

   protected:

      virtual ~SoPolygonOffset();

   public:

      enum Style {
         FILLED = SoPolygonOffsetElement::FILLED,
         LINES  = SoPolygonOffsetElement::LINES, 
         POINTS = SoPolygonOffsetElement::POINTS,
         ALL    = SoPolygonOffsetElement::ALL
      };
      
      SoSFFloat    factor;
      SoSFFloat    units;
      SoSFBitMask  styles;
      SoSFBool     on;
      
      SoPolygonOffset();

   SoEXTENDER public:

      virtual void doAction(SoAction *action);
      virtual void callback(SoCallbackAction *action);
      virtual void GLRender(SoGLRenderAction *action);

   SoINTERNAL public:

      static void initClass() ;
};

#endif  // _SO_POLYGON_OFFSET_
