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
 * Copyright (C) 1990,91   Silicon Graphics, Inc.
 *
 _______________________________________________________________________
 ______________  S I L I C O N   G R A P H I C S   I N C .  ____________
 |
 |   $Revision: 1.1.1.1 $
 |
 |   Description:
 |      This file defines the SoCallback node class.
 |
 |   Author(s)          : Paul S. Strauss, Nick Thompson, Gavin Bell
 |
 ______________  S I L I C O N   G R A P H I C S   I N C .  ____________
 _______________________________________________________________________
 */

#ifndef  _SO_CALLBACK_
#define  _SO_CALLBACK_

#include <Inventor/SbLinear.h>
#include <Inventor/nodes/SoSubNode.h>


//! Callback functions registered with this node should be of this type.
typedef void INVENTOR_API SoCallbackCB(void *userData, SoAction *action);

////////////////////////////////////////////////////////////////////////////////
//! Provides custom behavior during actions.
/*!
\class SoCallback
\ingroup Nodes
This node provides a general mechanism for inserting callback functions
into a scene graph. The callback function registered with the node is
called each time the node is traversed while performing any scene graph
action. The callback function is passed a pointer to the action being
performed and a user data pointer registered with the callback function.
You can use this node to make nonstandard OpenGL calls while rendering. If
you do, be careful not to interfere with Inventor's use of OpenGL.


If you use a callback node for GL rendering, you should be careful
to follow render caching rules. If your callback node can make
different rendering calls each time it is traversed, it cannot be
cached. In such a case, the node should invalidate any open caches,
as in the following example:

<tt>\code
void
myCallbackFunc(void *d, SoAction *action) {
    if (action->isOfType(SoGLRenderAction::getClassTypeId())) {
	// Make my custom GL calls
	((MyClass *) d)->myRender();
	
	// Invalidate the state so that a cache is not made
	SoCacheElement::invalidate(action->getState());
    }
}
\endcode
</tt>

\par Action Behavior
\par
SoGLRenderAction, SoBoundingBoxAction, SoPickAction
<BR> Calls the specified callback function for all actions. 

\par See Also
\par
SoAction, SoCallbackAction, SoEventCallback
*/
////////////////////////////////////////////////////////////////////////////////

class INVENTOR_API SoCallback : public SoNode {

    SO_NODE_HEADER(SoCallback);

  public:

    //! Creates a callback node with default settings.
    SoCallback();

    //! Sets pointer to callback function and user data. By default, the
    //! function pointer in the node is NULL and does nothing.
    void        setCallback(SoCallbackCB *func, void *userData = NULL)
        { callbackFunc = func; callbackData = userData; }

  SoEXTENDER public:
    //! Traversal methods for all the actions:
    virtual void        doAction(SoAction *action);
    virtual void        callback(SoCallbackAction *action);
    virtual void        GLRender(SoGLRenderAction *action);
    virtual void        getBoundingBox(SoGetBoundingBoxAction *action);
    virtual void        getMatrix(SoGetMatrixAction *action);
    virtual void        handleEvent(SoHandleEventAction *action);
    virtual void        pick(SoPickAction *action);
    virtual void        search(SoSearchAction *action);
    virtual void        write(SoWriteAction *action);

  SoINTERNAL public:
    static void         initClass();

  protected:
    virtual ~SoCallback();

    //! Copies the contents of the given node into this instance
    virtual void        copyContents(const SoFieldContainer *fromFC,
                                     bool copyConnections);

  private:
    SoCallbackCB        *callbackFunc;          //!< Function to call
    void                *callbackData;          //!< User data to pass it
};

#endif /* _SO_CALLBACK_ */
