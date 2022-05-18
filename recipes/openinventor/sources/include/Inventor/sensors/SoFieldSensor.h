/*
 *
 *  Copyright (C) 2000 Silicon Graphics, Inc.  All Rights Reserved. 
 *
 *  This library is free software; you can redistribute it and/or
 *  modify it under the terms of the GNU Lesser General Public
 *  License as published by the Free Software Foundation; either
 *  version 2.1 of the License, or (at your option) any later version.
 *
 *  This library is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 *  Lesser General Public License for more details.
 *
 *  Further, this software is distributed without any warranty that it is
 *  free of the rightful claim of any third person regarding infringement
 *  or the like.  Any license provided herein, whether implied or
 *  otherwise, applies only to this software file.  Patent licenses, if
 *  any, provided herein do not apply to combinations of this program with
 *  other software, or any other product whatsoever.
 * 
 *  You should have received a copy of the GNU Lesser General Public
 *  License along with this library; if not, write to the Free Software
 *  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 *
 *  Contact information: Silicon Graphics, Inc., 1600 Amphitheatre Pkwy,
 *  Mountain View, CA  94043, or:
 * 
 *  http://www.sgi.com 
 * 
 *  For further information regarding this notice, see: 
 * 
 *  http://oss.sgi.com/projects/GenInfo/NoticeExplan/
 *
 */


/*
 * Copyright (C) 1990,91,92   Silicon Graphics, Inc.
 *
 _______________________________________________________________________
 ______________  S I L I C O N   G R A P H I C S   I N C .  ____________
 |
 |   $Revision: 1.1.1.1 $
 |
 |   Description:
 |      Data sensor that is attached to a field in a node or elsewhere.
 |      The sensor is scheduled when a change is made to that field. Note:
 |      the field must be contained within a node or function, or
 |      attachment will not work.
 |
 |   Author(s)          : Paul Strauss
 |
 ______________  S I L I C O N   G R A P H I C S   I N C .  ____________
 _______________________________________________________________________
 */

#ifndef  _SO_FIELD_SENSOR_
#define  _SO_FIELD_SENSOR_

#include <Inventor/sensors/SoDataSensor.h>

class SoFieldContainer;

////////////////////////////////////////////////////////////////////////////////
//! Sensor class that can be attached to Inventor fields.
/*!
\class SoFieldSensor
\ingroup Sensors
Field sensors detect changes to fields, calling a callback function
whenever the field changes.  The field may be part of a node, an input
of an engine, or a global field.

\par See Also
\par
SoNodeSensor, SoPathSensor, SoDataSensor
*/
////////////////////////////////////////////////////////////////////////////////

class INVENTOR_API SoFieldSensor : public SoDataSensor {

  public:

    //! Creation methods.  The second method takes the callback function and
    //! data to be called when the sensor is triggered.
    SoFieldSensor();
    //! Creation methods.  The second method takes the callback function and
    //! data to be called when the sensor is triggered.
    SoFieldSensor(SoSensorCB *func, void *data);

    //! Destroys the sensor, freeing up any memory associated with it after
    //! unscheduling it.
    virtual ~SoFieldSensor();

    //! Makes this sensor detect changes to the given
    //! field.
    void                attach(SoField *field);

    //! Unschedules this sensor (if it is
    //! scheduled) and makes it ignore changes to the scene graph.
    void                detach();

    //! Returns the field that this sensor is
    //! sensing, or NULL if it is not attached to any field.
    SoField *           getAttachedField() const        { return field; }

  SoINTERNAL public:
    //! Override trigger to evaluate the field we're connected to, just
    //! in case the trigger method doesn't get the value.
    virtual void trigger();

  private:
    SoField *           field;          //!< Field sensor is attached to

    //! Propagates modification notification through an instance. This
    //! checks to see if the field that triggered notification matches
    //! the field we are attached to. (It also checks indices if necessary.)
    virtual void        notify(SoNotList *list);

    //! Called by the attached path when it (the path) is about to be deleted
    virtual void        dyingReference();
};


//! Base class for typed field sensor callbacks.
class SoFieldSensorCallback : public SoFieldSensor
{
public:
  SoFieldSensorCallback() :SoFieldSensor(sensorCB, this)
  {
  }

  //! called when the SoFieldSensor is triggered.
  virtual void call(SoField* theField) = 0;

private:
  static void sensorCB(void * data, SoSensor* sensor) {
    ((SoFieldSensorCallback*)data)->call(((SoFieldSensor*)sensor)->getAttachedField());
  }
};

//! Typed field sensor that called given member function on object when triggered.
template<class Object, class Method>
class SoTypedFieldSensorCallback : public SoFieldSensorCallback {

public:

  SoTypedFieldSensorCallback(Object* object, Method method) :
    _object(object), _method(method)
  {}

  ~SoTypedFieldSensorCallback()
  {}

  virtual void call(SoField* theField) {
    (_object->*_method)(theField);
  }

private:
  Object* _object;
  Method  _method;
};

//! Helper method to create a field sensor by type inference.
template<class Object, class Method>
inline SoFieldSensor* SoCreateFieldSensor(Object* object, Method method, SoField& field)
{
  SoFieldSensor* sensor = new SoTypedFieldSensorCallback<Object, Method>(object, method);
  sensor->attach(&field);
  return sensor;
}

//! Adds a SoFieldSensor to the given field and calls the member function \p method when
//! the field changes/is touched.
#define SO_NODE_ADD_FIELD_CALLBACK(field, method) \
  this->addManagedSensor(SoCreateFieldSensor(this, &InventorThisClass::method, field));

//! Adds a SoFieldSensor to the given field and calls the member function \p method when
//! the field changes/is touched. The sensor has the given \p priority.
#define SO_NODE_ADD_FIELD_CALLBACK_WITH_PRIORITY(field, method, priority) \
  { SoFieldSensor* invInternalSen = SoCreateFieldSensor(this, &InventorThisClass::method, field); \
    invInternalSen->setPriority(priority); \
    this->addManagedSensor(invInternalSen); \
  }

#endif  /* _SO_FIELD_SENSOR_ */
