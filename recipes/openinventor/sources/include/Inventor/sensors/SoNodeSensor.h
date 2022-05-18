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
 |      Data sensor that is attached to a node in a scene graph. The
 |      sensor is scheduled when a change is made to the node or to any
 |      node below it in the graph.
 |
 |   Author(s)          : Nick Thompson, Paul Strauss
 |
 ______________  S I L I C O N   G R A P H I C S   I N C .  ____________
 _______________________________________________________________________
 */

#ifndef  _SO_NODE_SENSOR_
#define  _SO_NODE_SENSOR_

#include <Inventor/sensors/SoDataSensor.h>

////////////////////////////////////////////////////////////////////////////////
//! Sensor class that can be attached to Inventor nodes.
/*!
\class SoNodeSensor
\ingroup Sensors
Node sensors detect changes to nodes, calling a callback function
whenever any field of the node or, if the node is a group node, any
children of the node change.

\par See Also
\par
SoFieldSensor, SoPathSensor, SoDataSensor
*/
////////////////////////////////////////////////////////////////////////////////

class INVENTOR_API SoNodeSensor : public SoDataSensor {

  public:

    //! Creation methods.  The second method takes the callback function and
    //! data to be called when the sensor is triggered.
    SoNodeSensor();
    //! Creation methods.  The second method takes the callback function and
    //! data to be called when the sensor is triggered.
    SoNodeSensor(SoSensorCB *func, void *data);

    //! Destroys the sensor, freeing up any memory associated with it after
    //! unscheduling it.
    virtual ~SoNodeSensor();

    //! Makes this sensor detect changes to the given
    //! node.
    void                attach(SoNode *node);

    //! Unschedules this sensor (if it is
    //! scheduled) and makes it ignore changes to the scene graph.
    void                detach();

    //! Returns the node that this sensor is
    //! sensing, or NULL if it is not attached to any node.
    SoNode *            getAttachedNode() const         { return node; }

  private:
    SoNode *            node;           //!< Node sensor is attached to

    //! Called by the attached node when it (the node) is about to be deleted
    virtual void        dyingReference();
};

#endif  /* _SO_NODE_SENSOR_ */
