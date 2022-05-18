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
 |      Abstract base camera node class
 |
 |   Author(s)          : Paul S. Strauss
 |
 ______________  S I L I C O N   G R A P H I C S   I N C .  ____________
 _______________________________________________________________________
 */

#ifndef  _SO_CAMERA_
#define  _SO_CAMERA_

#include <Inventor/SbBox.h>
#include <Inventor/SbViewportRegion.h>
#include <Inventor/nodes/SoSubNode.h>
#include <Inventor/fields/SoSFFloat.h>
#include <Inventor/fields/SoSFRotation.h>
#include <Inventor/fields/SoSFVec3f.h>
#include <Inventor/fields/SoSFEnum.h>

class SbViewportRegion;


////////////////////////////////////////////////////////////////////////////////
//! Abstract base class for camera nodes.
/*!
\class SoCamera
\ingroup Nodes
This is the abstract base class for all camera nodes. It defines the
common methods and fields that all cameras have. Cameras are used to
view a scene. When a camera is encountered during rendering, it sets
the projection and viewing matrices and viewport appropriately; it
does not draw geometry. Cameras should be placed before any shape
nodes or light nodes in a scene graph; otherwise, those shapes or
lights cannot be rendered properly. Cameras are affected by the
current transformation, so you can position a camera by placing a
transformation node before it in the scene graph . The default
position and orientation of a camera is at (0,0,1) looking along the
negative z-axis.


You can also use a node kit to create a camera; see the reference page for
SoCameraKit.

\par See Also
\par
SoOrthographicCamera, SoPerspectiveCamera, SoCameraKit
*/
////////////////////////////////////////////////////////////////////////////////

class INVENTOR_API SoCamera : public SoNode {

    SO_NODE_ABSTRACT_HEADER(SoCamera);

  public:
    //! What will happen if the camera and
    enum ViewportMapping {
                                //! viewport aspect ratios differ?
        
                                       //! The first 3 adjust the viewport
                                       //! to fit the camera.
        CROP_VIEWPORT_FILL_FRAME = 0,  //!< Draw filled frame around vp.
        CROP_VIEWPORT_LINE_FRAME = 1,  //!< Draw frame in lines.
        CROP_VIEWPORT_NO_FRAME   = 2,  //!< Draw no frame.

        ADJUST_CAMERA            = 3,  //!< Adjust camera to fit viewport.
        LEAVE_ALONE              = 4   //!< Do nothing. Camera image may
                                       //! become stretched out of proportion
    };

    //! NOTE: These fields are here so that all camera subclasses do
    //! not have to define them separately. However, all subclasses
    //! DO have to set up field data with these fields in them to make
    //! things work properly.

    //! \name Fields
    //@{

    //! Defines how to map the rendered image into the current viewport, when the
    //! aspect ratio of the camera differs from that of the viewport.
    SoSFEnum            viewportMapping;

    //! The location of the camera viewpoint.
    SoSFVec3f           position;       

    //! The orientation of the camera viewpoint, defined as a rotation of the
    //! viewing direction from its default (0,0,-1) vector.
    SoSFRotation        orientation;    

    //! The ratio of camera viewing width to height. This value must be greater
    //! than 0.0. There are several standard camera aspect ratios defined
    //! in SoCamera.h.
    SoSFFloat           aspectRatio;    
    //! Distance from viewpoint to view plane
    SoSFFloat           nearDistance;   
    //! Distance from viewpoint to far clipping plane
    SoSFFloat           farDistance;    

    //! The distance from the viewpoint to the point of focus. This is
    //! typically ignored during rendering, but may be used by some viewers to
    //! define a point of interest.
    SoSFFloat           focalDistance;  

    //@}

    //! Sets the orientation of the camera so that it points toward the
    //! given target point while keeping the "up" direction of the
    //! camera parallel to the positive y-axis. If this is not
    //! possible, it uses the positive z-axis as "up."
    void                pointAt(const SbVec3f &targetPoint);

    //! Scales the height of the camera. Perspective cameras scale their
    //! \b heightAngle  fields, and orthographic cameras scale their
    //! \b height  fields.
    virtual void        scaleHeight(float scaleFactor) = 0;

    //! Returns a view volume structure, based on the camera's viewing
    //! parameters. If the \p useAspectRatio argument is not 0.0 (the default),
    //! the camera uses that ratio instead of the one it has.
    virtual SbViewVolume getViewVolume(float useAspectRatio = 0.0) const = 0;

    //! Sets the camera up to view the scene under the given node or
    //! defined by the given path. The near and far clipping planes
    //! will be positioned 'slack' bounding sphere radii away from the
    //! bounding box's center. A value of 1.0 will make the clipping
    //! planes the tightest around the bounding sphere.
    void                viewAll(SoNode *sceneRoot,
                                const SbViewportRegion &vpRegion,
                                float slack = 1.0);
    void                viewAll(SoPath *path,
                                const SbViewportRegion &vpRegion,
                                float slack = 1.0);

    //! Returns the viewport region this camera would use to render into the
    //! given viewport region, accounting for cropping.
    SbViewportRegion    getViewportBounds(const SbViewportRegion &region) const;

  SoEXTENDER public:
    virtual void        doAction(SoAction *action);
    virtual void        callback(SoCallbackAction *action);
    virtual void        GLRender(SoGLRenderAction *action);
    virtual void        getBoundingBox(SoGetBoundingBoxAction *action);
    virtual void        handleEvent(SoHandleEventAction *action);
    virtual void        rayPick(SoRayPickAction *action);

  SoINTERNAL public:
    static void         initClass();

  protected:
    SoCamera();                         //!< Makes this abstract
    virtual ~SoCamera();

    //! Subclasses must define this method, which changes the position
    //! and clipping planes of a camera to view the passed bounding box
    //! using the given aspect ratio, without changing the height
    //! scaling.
    virtual void        viewBoundingBox(const SbBox3f &box,
                                        float aspect, float slack) = 0;

    //! Returns amount to jitter camera in normalized device
    //! coordinates (after projection) for anti-aliasing during
    //! multi-pass rendering
    virtual void        jitter(int numPasses, int curPass,
                               const SbViewportRegion &vpReg,
                               SbVec3f &jitterAmount) const;

  private:
    //! Computes the view volume the camera represents, given a viewport region
    void                computeView(const SbViewportRegion &vpReg,
                                    SbViewVolume &viewVol,
                                    bool &changeRegion);

    //! Sets relevant info in elements in state
    void                setElements(SoAction *action,
                                    SbViewVolume &viewVol,
                                    bool setRegion,
                                    const SbViewportRegion &vpReg,
                                    bool doJitter,
                                    const SbVec3f &jitterAmount);

    //! Draws cropping frame when rendering
    void                drawFrame(SoGLRenderAction *action,
                                  const SbViewportRegion &vpReg,
                                  const SbViewportRegion &croppedReg);

    //! Returns a 2D sample point within a pixel
    static void         getJitterSample(int numPasses, int curPass,
                                        SbVec2f &samplePoint);
};

///////////////////////////////////////////////////////////////////////////////
///
/// Commonly used camera aspect ratios
///

#define SO_ASPECT_SQUARE        1.00         /* Square (1.000)               */
#define SO_ASPECT_VIDEO         1.333333333  /* Video (0.75)                 */
#define SO_ASPECT_35mm_ACADEMY  1.371        /* 35mm, Academy ap (.72939460) */
#define SO_ASPECT_16mm          1.369        /* 16mm cinema (.730460189)     */
#define SO_ASPECT_35mm_FULL     1.33333      /* 35mm cinema, full ap (0.75)  */
#define SO_ASPECT_70mm          2.287        /* 70 mm unsqueezed (.43725404) */
#define SO_ASPECT_CINEMASCOPE   2.35         /* Cinemascope (.425531914)     */
#define SO_ASPECT_HDTV          1.777777777  /* HDTV (16:9)                  */
#define SO_ASPECT_PANAVISION    2.361        /* Panavision (.423549343)      */
#define SO_ASPECT_35mm          1.5          /* 35mm still camera (.666666)  */
#define SO_ASPECT_VISTAVISION   2.301        /* Vistavision (.434593654)     */

#endif /* _SO_CAMERA_ */
