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
 |      This file contains the implementation of the
 |      various composition and decomposition engines
 |
 |   Classes:
 |       SoComposeVec2f 
 |       SoComposeVec3f 
 |       SoComposeVec4f 
 |       SoComposeRotation 
 |       SoComposeRotationFromTo
 |       SoDecomposeVec2f 
 |       SoDecomposeVec3f 
 |       SoDecomposeVec4f 
 |       SoDecomposeRotation 
 |
 |   Author(s)          : Ronen Barzel
 |
 ______________  S I L I C O N   G R A P H I C S   I N C .  ____________
 _______________________________________________________________________
 */

#ifndef  _SO_COMPOSE_
#define  _SO_COMPOSE_

#include <Inventor/system/SbSystem.h>
#include <Inventor/engines/SoSubEngine.h>
#include <Inventor/fields/SoMFFloat.h>
#include <Inventor/fields/SoMFMatrix.h>
#include <Inventor/fields/SoMFRotation.h>
#include <Inventor/fields/SoMFVec2f.h>
#include <Inventor/fields/SoMFVec3f.h>
#include <Inventor/fields/SoMFVec4f.h>

//! This internal macro defines the standard methods for the composition
//! engines.  These are just basic engine declarations, nothing fancy. 
//! The macro leaves the class header in "public:" state so it can be
//! followed immediately with the composition input and output declarations.
#define SO_COMPOSE__HEADER(Name)                \
            SO_ENGINE_HEADER(Name);             \
          private:                              \
            ~Name();                            \
            virtual void evaluate();            \
          public:                               \
            Name();                             \
            static void initClass()                             

////////////////////////////////////////////////////////////
/// 
///  Vector composition engines
/// 
////////////////////////////////////////////////////////////////////////////////
//! Composes 2D vectors from floating-point values.
/*!
\class SoComposeVec2f
\ingroup Engines
This engine takes two floating-point inputs and composes a
2D floating-point vector.


The input fields can have multiple values, allowing the engine to 
compose several vectors in parallel.
One of the inputs may have more values than others.  In such cases,
the last value of the shorter input will be repeated as necessary.

\par File Format/Default
\par
\code
ComposeVec2f {
  x 0
  y 0
}
\endcode

\par See Also
\par
SoDecomposeVec2f, SoEngineOutput
*/
////////////////////////////////////////////////////////////////////////////////

class INVENTOR_API SoComposeVec2f : public SoEngine {
    SO_COMPOSE__HEADER(SoComposeVec2f);
public:
    //! \name Inputs
    //@{

    //! The x component.
    SoMFFloat           x;      

    //! The y component.
    SoMFFloat           y;      

    //@}

    //! \name Outputs
    //@{

    //! Vector composed of x and y components.
    SoEngineOutput      vector; 

    //@}

};
////////////////////////////////////////////////////////////////////////////////
//! Composes 3D vectors from floating-point values.
/*!
\class SoComposeVec3f
\ingroup Engines
This engine takes three floating-point inputs and composes 
a 3D vector.


The input fields can have multiple values, allowing the engine to 
compose several vectors in parallel.
Some inputs may have more values than others.  In such cases,
the last value of the shorter inputs will be repeated as necessary.

\par File Format/Default
\par
\code
ComposeVec3f {
  x 0
  y 0
  z 0
}
\endcode

\par See Also
\par
SoDecomposeVec3f, SoEngineOutput
*/
////////////////////////////////////////////////////////////////////////////////

class INVENTOR_API SoComposeVec3f : public SoEngine {
    SO_COMPOSE__HEADER(SoComposeVec3f);
public:
    //! \name Inputs
    //@{

    //! The x component
    SoMFFloat           x;      

    //! The y component
    SoMFFloat           y;      

    //! The z component.
    SoMFFloat           z;      

    //@}

    //! \name Outputs
    //@{

    //! Vector composed of x, y, and z.
    SoEngineOutput      vector; 

    //@}

};
////////////////////////////////////////////////////////////////////////////////
//! Composes 4D vectors from floating-point values.
/*!
\class SoComposeVec4f
\ingroup Engines
This engine takes four floating-point inputs and composes a 
4D vector.


The input fields can have multiple values, allowing the engine to 
compose several vectors in parallel.
Some inputs may have more values than others.  In such cases,
the last value of the shorter inputs will be repeated as necessary.

\par File Format/Default
\par
\code
ComposeVec4f {
  x 0
  y 0
  z 0
  w 0
}
\endcode

\par See Also
\par
SoDecomposeVec4f, SoEngineOutput
*/
////////////////////////////////////////////////////////////////////////////////

class INVENTOR_API SoComposeVec4f : public SoEngine {
    SO_COMPOSE__HEADER(SoComposeVec4f);
public:
    //! \name Inputs
    //@{

    //! The x component.
    SoMFFloat           x;      

    //! The y component.
    SoMFFloat           y;      

    //! The z component.
    SoMFFloat           z;      

    //! The w component.
    SoMFFloat           w;      

    //@}

    //! \name Outputs
    //@{

    //! Vector composed of x, y, z, and w.
    SoEngineOutput      vector; 

    //@}

};

////////////////////////////////////////////////////////////
/// 
///  Vector decomposition engines
/// 
////////////////////////////////////////////////////////////////////////////////
//! Decomposes 2D vectors into floating-point values.
/*!
\class SoDecomposeVec2f
\ingroup Engines
This engine takes as input a 2D vector, 
and decomposes it into two single floating-point values. 


The input can have multiple values, allowing the engine to decompose
several vectors in parallel.

\par File Format/Default
\par
\code
DecomposeVec2f {
  vector 0 0
}
\endcode

\par See Also
\par
SoComposeVec2f, SoEngineOutput
*/
////////////////////////////////////////////////////////////////////////////////

class INVENTOR_API SoDecomposeVec2f : public SoEngine {
    SO_COMPOSE__HEADER(SoDecomposeVec2f);
public:
    //! \name Inputs
    //@{

    //! Vector to be decomposed.
    SoMFVec2f           vector; 

    //@}

    //! \name Outputs
    //@{

    //! First component of the vector.
    SoEngineOutput      x;      

    //! Second component of the vector.
    SoEngineOutput      y;      

    //@}

};
////////////////////////////////////////////////////////////////////////////////
//! Decomposes 3D vectors into floating-point values.
/*!
\class SoDecomposeVec3f
\ingroup Engines
This engine takes as input a 3D vector,
and decomposes it into three single floating-point values. 


The input can have multiple values, allowing the engine to decompose
several vectors in parallel.

\par File Format/Default
\par
\code
DecomposeVec3f {
  vector 0 0 0
}
\endcode

\par See Also
\par
SoComposeVec3f, SoEngineOutput
*/
////////////////////////////////////////////////////////////////////////////////

class INVENTOR_API SoDecomposeVec3f : public SoEngine {
    SO_COMPOSE__HEADER(SoDecomposeVec3f);
public:
    //! \name Inputs
    //@{

    //! Vector to be decomposed.
    SoMFVec3f           vector; 

    //@}

    //! \name Outputs
    //@{

    //! First component of the vector.
    SoEngineOutput      x;      

    //! Second component of the vector.
    SoEngineOutput      y;      

    //! Third component of the vector.
    SoEngineOutput      z;      

    //@}

};
////////////////////////////////////////////////////////////////////////////////
//! Decomposes 4D vectors into floating-point values.
/*!
\class SoDecomposeVec4f
\ingroup Engines
This engine takes as input a 4D vector,
and decomposes it into four single floating-point values. 


The input can have multiple values, allowing the engine to decompose
several vectors in parallel.

\par File Format/Default
\par
\code
DecomposeVec4f {
  vector 0 0 0 0
}
\endcode

\par See Also
\par
SoComposeVec4f, SoEngineOutput
*/
////////////////////////////////////////////////////////////////////////////////

class INVENTOR_API SoDecomposeVec4f : public SoEngine {
    SO_COMPOSE__HEADER(SoDecomposeVec4f);
public:
    //! \name Inputs
    //@{

    //! Vector to be decomposed.
    SoMFVec4f           vector; 

    //@}

    //! \name Outputs
    //@{

    //! First component of the vector.
    SoEngineOutput      x;      

    //! Second component of the vector.
    SoEngineOutput      y;      

    //! Third component of the vector.
    SoEngineOutput      z;      

    //! Fourth component of the vector.
    SoEngineOutput      w;      

    //@}

};

////////////////////////////////////////////////////////////
/// 
///  Rotation composition engines
/// 
////////////////////////////////////////////////////////////////////////////////
//! Composes a rotation from axis and angle values.
/*!
\class SoComposeRotation
\ingroup Engines
This engine has two inputs, representing an \b axis  of rotation
and a rotation \b angle  in radians.  As output, the engine composes the
inputs into a rotation field.


The input fields can have multiple values, allowing the engine to 
compose several rotations in parallel.
Some inputs may have more values than others.  In such cases,
the last value of the shorter inputs will be repeated as necessary.

\par File Format/Default
\par
\code
ComposeRotation {
  axis 0 0 1
  angle 0
}
\endcode

\par See Also
\par
SoComposeRotationFromTo, SoDecomposeRotation, SoEngineOutput
*/
////////////////////////////////////////////////////////////////////////////////

class INVENTOR_API SoComposeRotation : public SoEngine {
    SO_COMPOSE__HEADER(SoComposeRotation);
public:
    //! \name Inputs
    //@{

    //! Axis of rotation.
    SoMFVec3f           axis;           

    //! Angle of rotation.
    SoMFFloat           angle;          

    //@}

    //! \name Outputs
    //@{

    //! Rotation field, defined by the inputs.
    SoEngineOutput      rotation;       

    //@}

};
////////////////////////////////////////////////////////////////////////////////
//! Composes a rotation that rotates from one vector into another.
/*!
\class SoComposeRotationFromTo
\ingroup Engines
This engine takes two inputs, representing a vector before
and after a rotation has been applied.
As output, it produces the rotation value that would cause the first
vector to transform into the other.


The input fields can have multiple values, allowing the engine to 
compose several rotations in parallel.
Some inputs may have more values than others.  In such cases,
the last value of the shorter inputs will be repeated as necessary.

\par File Format/Default
\par
\code
ComposeRotationFromTo {
  from 0 0 1
  to 0 0 1
}
\endcode

\par See Also
\par
SoComposeRotation, SoDecomposeRotationFromTo, SoEngineOutput
*/
////////////////////////////////////////////////////////////////////////////////

class INVENTOR_API SoComposeRotationFromTo : public SoEngine {
    SO_COMPOSE__HEADER(SoComposeRotationFromTo);
public:
    //! \name Inputs
    //@{

    //! Vector before the rotation.
    SoMFVec3f           from;           

    //! Vector after the rotation.
    SoMFVec3f           to;             

    //@}

    //! \name Outputs
    //@{

    //! A rotation that transforms one vector into another.
    SoEngineOutput      rotation;       

    //@}

};


////////////////////////////////////////////////////////////
/// 
///  Rotation decomposition engine
/// 
////////////////////////////////////////////////////////////////////////////////
//! Decomposes rotation values.
/*!
\class SoDecomposeRotation
\ingroup Engines
This engine takes as input a rotation, and 
decomposes it into an axis value and a rotation angle (in radians).


The input can have multiple values, allowing the engine to decompose
several rotations in parallel.

\par File Format/Default
\par
\code
DecomposeRotation {
  rotation 0 0 1  0
}
\endcode

\par See Also
\par
SoDecomposeRotationFromTo, SoComposeRotation, SoEngineOutput
*/
////////////////////////////////////////////////////////////////////////////////

class INVENTOR_API SoDecomposeRotation : public SoEngine {
    SO_COMPOSE__HEADER(SoDecomposeRotation);
public:
    //! \name Inputs
    //@{

    //! Rotation to be decomposed.
    SoMFRotation        rotation;       

    //@}

    //! \name Outputs
    //@{

    //! Axis of rotation derived from the input.
    SoEngineOutput      axis;           

    //! Angle (in radians) derived from the input.
    SoEngineOutput      angle;          
};

    //@}


////////////////////////////////////////////////////////////
/// 
///  Matrix composition engine
/// 
////////////////////////////////////////////////////////////////////////////////
//! Composes a transformation matrix.
/*!
\class SoComposeMatrix
\ingroup Engines
This engine has inputs that specify values for translation, rotation,
scale, and center of transformation.  
As output, it produces a transformation matrix that 
transforms objects into the space specified by the scale, rotation,
and translation inputs (in that order).


The input fields can have multiple values, allowing the engine to 
compose several matrices in parallel.
Some inputs may have more values than others.  In such cases,
the last value of the shorter inputs will be repeated as necessary.

\par File Format/Default
\par
\code
ComposeMatrix {
  translation 0 0 0
  rotation 0 0 1  0
  scaleFactor 1 1 1
  scaleOrientation 0 0 1  0
  center 0 0 0
}
\endcode

\par See Also
\par
SoDecomposeMatrix, SoEngineOutput
*/
////////////////////////////////////////////////////////////////////////////////

class INVENTOR_API SoComposeMatrix : public SoEngine {
    SO_COMPOSE__HEADER(SoComposeMatrix);
public:
    //! \name Inputs
    //@{

    //! Translation in x, y, and z.
    SoMFVec3f           translation;    

    //! Rotation.
    SoMFRotation        rotation;       

    //! Scale factors in x, y, and z.
    SoMFVec3f           scaleFactor;    

    //! Rotational space for scaling.
    SoMFRotation        scaleOrientation;

    //! Center point for scaling and rotating.
    SoMFVec3f           center;         

    //@}

    //! \name Outputs
    //@{

    //! Transformation matrix that transforms from
    //! object space into the space specified by the inputs.
    SoEngineOutput      matrix;         

    //@}

};


////////////////////////////////////////////////////////////
/// 
///  Matrix decomposition engine
///
///  Note: a matrix decomposition depends on the choice of
///  center. So a "center" input is provided (with default 
///  value 0,0,0) and there is no "center" output.
/// 
////////////////////////////////////////////////////////////////////////////////
//! Decomposes transformation matrices into values 
//! for translation, rotation, and scale.
/*!
\class SoDecomposeMatrix
\ingroup Engines
This engine takes as input a transformation matrix and a center of transformation.
As output the engine produces the translation, rotation and scale values
derived from the matrix.


The input fields can have multiple values, allowing the engine to 
decompose several matrices in parallel.
One of the inputs may have more values than the other.  In that case,
the last value of the shorter input will be repeated as necessary.

\par File Format/Default
\par
\code
DecomposeMatrix {
  matrix 1 0 0 0
	0 1 0 0
	0 0 1 0
	0 0 0 1
  center 0 0 0
}
\endcode

\par See Also
\par
SoComposeMatrix, SoEngineOutput
*/
////////////////////////////////////////////////////////////////////////////////

class INVENTOR_API SoDecomposeMatrix : public SoEngine {
    SO_COMPOSE__HEADER(SoDecomposeMatrix);
public:
    //! \name Inputs
    //@{

    //! The 4x4 transformation matrix.
    SoMFMatrix          matrix;         

    //! The center of transformations.
    SoMFVec3f           center;         

    //@}

    //! \name Outputs
    //@{

    //! Derived translation in x, y, and z.
    SoEngineOutput      translation;    

    //! Derived rotation.
    SoEngineOutput      rotation;       

    //! Derived scale values in x, y, and z.
    SoEngineOutput      scaleFactor;    

    //! Derived rotational space for scaling.
    SoEngineOutput      scaleOrientation;

    //@}

};

#endif  /* _SO_COMPOSE_ */
